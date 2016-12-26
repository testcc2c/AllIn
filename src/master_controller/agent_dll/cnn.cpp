#include <windows.h>
#include <TlHelp32.h>
#include <shellapi.h>
#include <boost/exception/all.hpp>
#include "common_definitions.h"
#include "log.h"
#include "parse.h"
#include "cnn.h"

MC::Cnn* MC::Cnn::cnn_inst = NULL;

bool MC::Cnn::StartPipe(const char* cnn_name)
{
    if (pipe_ != INVALID_HANDLE_VALUE)
        return true;

    LPTSTR lpszPipename = TEXT((char*)cnn_name);
    pipe_ = CreateFile(
        lpszPipename,           // pipe �� 
        GENERIC_READ | GENERIC_WRITE,        // �ɶ���д
        0,                      // ������
        NULL,                   // Ĭ�ϰ�ȫ����
        OPEN_EXISTING,          // �Ѿ�����(�ɷ���˴���)
        FILE_FLAG_OVERLAPPED,   // Ĭ������
        NULL);
    if (pipe_ != INVALID_HANDLE_VALUE)
        goto NOR;

    // ������� ERROR_PIPE_BUSY ����, ֱ���˳�  
    if (GetLastError() != ERROR_PIPE_BUSY) {
        printf("1->Could not open pipe, err: %d\n", GetLastError());
        return false;
    }

    // �������pipeʵ�������ڷ�æ״̬, �ȴ�2��
    if (!WaitNamedPipe(lpszPipename, PIPE_BUSY_WAIT)) {
        printf("2->Could not open pipe\n");
        return false;
    }

    BOOL fSuccess;
    DWORD dwMode;
    // pipe�Ѿ�����, ����Ϊ��Ϣ��״̬
    dwMode = PIPE_READMODE_MESSAGE;
    fSuccess = SetNamedPipeHandleState(
        pipe_,    // ���
        &dwMode,  // ��״̬
        NULL,     // ��������󻺴�
        NULL);    // �������ʱ��
    if (!fSuccess) {
        printf("SetNamedPipeHandleState failed, err: %d\n", GetLastError());
        return false;
    }

NOR:
    Log::WriteLog(LL_DEBUG, "AsynAPISet::StartPipe->CreateFile, pipe: %d", (int)pipe_);
    pipe_inst_ = (LPPIPEINST)HeapAlloc(GetProcessHeap(), 0, sizeof(PIPEINST));
    if (pipe_inst_ == NULL) {
        printf("APISet::Start->HeapAlloc failed, err: (%d)\n", GetLastError());
        CloseHandle(pipe_);
        return false;
    }

    pipe_inst_->hPipeInst = pipe_;
    pipe_inst_->cbToWrite = 0;
    return true;
}

bool MC::Cnn::StartMQ(
    const std::string& send_mq_name,
    const std::string& recv_mq_name)
{
    try {
        send_mq_ = new (std::nothrow) boost::interprocess::message_queue(
            boost::interprocess::open_only,
            send_mq_name.c_str());
        recv_mq_ = new (std::nothrow) boost::interprocess::message_queue(
            boost::interprocess::open_only,
            recv_mq_name.c_str());
    } catch (boost::interprocess::interprocess_exception &ex) {
        Log::WriteLog(LL_ERROR, "MC::Cnn::StartMQ->����Ϣ����(send: %s, recv: %s)ʧ��, er: %s",
            send_mq_name.c_str(),
            recv_mq_name.c_str(),
            boost::current_exception_diagnostic_information().c_str());
        return false;
    }

    return true;
}

bool MC::Cnn::Start()
{
    if (running_)
        return true;

    if (!ProcessExisted(MC::SERVER_NAME)) {
        bool ret = StartSvc(MC::SERVER_NAME);
        Log::WriteLog(LL_DEBUG, "AsynAPISet::Start->�����������\"%s\"%s",
            MC::SERVER_NAME.c_str(),
            ret ? "�ɹ�" : "ʧ��");
    }

    Sleep(2000); // �ʵ���ʱ, �Ա���Ϣ����׼����

    bool ret;
    if (Config::GetInst()->conn_type_ == CT_PIPE)
        ret = StartPipe(Config::GetInst()->pipe_name_.c_str());
    else if (Config::GetInst()->conn_type_ == CT_MQ)
        ret = StartMQ(Config::GetInst()->send_mq_name_, Config::GetInst()->recv_mq_name_);

    running_ = true;
    // ����Ϣ�߳�
    recver_thread_ =
        new (std::nothrow) boost::thread(boost::bind(&Cnn::ReceiveFunc, this));
    // ����Ϣ�߳�
    sender_thread_ =
        new (std::nothrow) boost::thread(boost::bind(&Cnn::SendFunc, this));

    heart_ev_ = CreateEvent(
        NULL,
        FALSE,
        TRUE,      // default signaled 
        NULL);
    // �����߳�
    heart_thread_ =
        new (std::nothrow) boost::thread(boost::bind(&Cnn::HeartBeatingFunc, this));

    return true;
}

void MC::Cnn::Stop()
{
    running_ = false;
    recver_thread_->join();
    sender_thread_->join();
    heart_thread_->join();

    delete send_mq_;
    delete recv_mq_;
    CloseHandle(pipe_);
    if (NULL != pipe_inst_)
        HeapFree(GetProcessHeap(), 0, pipe_inst_);
}

bool MC::Cnn::PushCmd(BaseCmd* cmd)
{
    return send_cmd_queue_.Push(cmd);
}

bool MC::Cnn::RecvBuf(TCHAR* buf, int buf_len, DWORD* actual_read)
{
    bool fSuccess;
    if (MC::CT_PIPE == Config::GetInst()->conn_type_) {      // �չܵ���Ϣ
        fSuccess = ReadFile(
            pipe_,                          // ���
            buf,                            // ��ȡ���ݵĻ���
            CMD_BUF_SIZE * sizeof(TCHAR),   // �����С
            actual_read,                    // ʵ�ʶ����ֽ�
            NULL) == 0? false: true;        // �� overlapped
    } else {                                                // ��Ϣ����
        unsigned int priority;
        boost::interprocess::message_queue::size_type recvd_size;
        try {
            heart_mtx_.lock();
            fSuccess = recv_mq_->try_receive(buf, buf_len, recvd_size, priority);
            heart_mtx_.unlock();

            *actual_read = recvd_size;
        } catch (boost::interprocess::interprocess_exception &ex) {
            std::cout << ex.what() << std::endl;
            Log::WriteLog(LL_ERROR, "AsynAPISet::ReceiverFunc->��Ϣ�����쳣: %s", ex.what());
            *actual_read = 0;
            fSuccess = false;
        }
    }

    return fSuccess;
}

void MC::Cnn::ReceiveFunc()
{
    TCHAR chBuf[CMD_BUF_SIZE] = { 0 };
    DWORD cbRead;
    while (true) {
        RecvBuf(chBuf, sizeof(chBuf), &cbRead);
        // ��ʵ�ʶ��ֽ�Ϊ0, ��������ѭ��
        if (0 == cbRead)
            continue;

        // ������Ϣͷ, �жϾ�����Ϣ����
        char cmd_type;
        memcpy(&cmd_type, chBuf, sizeof(char));
        switch (cmd_type) {
        case CT_QUERY_MACHINE:
            asyn_api_->HandleQueryMachine(chBuf);
            break;
        case CT_SET_MACHINE:
            asyn_api_->HandleSetMachine(chBuf);
            break;
        case CT_INIT_MACHINE:
            asyn_api_->HandleInitMachine(chBuf);
            break;
        case CT_BIND_MAC:
            asyn_api_->HandleBindMac(chBuf);
            break;
        case CT_UNBIND_MAC:
            asyn_api_->HandleUnbindMAC(chBuf);
            break;
        case CT_PREPARE_STAMP:
            asyn_api_->HandlePrepareStamp(chBuf);
            break;
        case CT_PAPER_DOOR:
            asyn_api_->HandleQueryPaper(chBuf);
            break;
        case CT_SNAPSHOT:
            asyn_api_->HandleSnapshot(chBuf);
            break;
        case CT_PHOTO_SYNTHESIS:
            asyn_api_->HandleMergePhoto(chBuf);
            break;
        case CT_RECOGNITION:
            asyn_api_->HandleRecognition(chBuf);
            break;
        case CT_ELEMENT_IDENTI:
            asyn_api_->HandleIdentify(chBuf);
            break;
        case CT_ORDINARY_STAMP:
            asyn_api_->HandleOrdinary(chBuf);
            break;
        case CT_AUTO_STAMP:
            asyn_api_->HandleAuto(chBuf);
            break;
        case CT_FINISH_STAMP:
            asyn_api_->HandleFinish(chBuf);
            break;
        case CT_RELEASE_STAMPER:
            asyn_api_->HandleRelease(chBuf);
            break;
        case CT_GET_ERROR:
            asyn_api_->HandleGetError(chBuf);
            break;
        case CT_CALIBRATION:
            asyn_api_->HandleCalibrate(chBuf);
            break;
        case CT_QUERY_STAMPERS:
            asyn_api_->HandleQueryStampers(chBuf);
            break;
        case CT_QUERY_SAFE:
            asyn_api_->HandleQuerySafe(chBuf);
            break;
        case CT_SAFE_CTL:
            asyn_api_->HandleSafeControl(chBuf);
            break;
        case CT_BEEP_CTL:
            asyn_api_->HandleBeepControl(chBuf);
            break;
        case CT_QUERY_SLOT:
            asyn_api_->HandleQuerySlot(chBuf);
            break;
        case CT_ALARM_CTL:
            asyn_api_->HandleAlarmControl(chBuf);
            break;
        case CT_QUERY_MAC:
            asyn_api_->HandleQueryMAC(chBuf);
            break;
        case CT_HEART_BEAT:
            HandleHeartBeating(chBuf);
            break;
        default:
            printf("AsynAPISet::ReceiverFunc->Unknown cmd: %d", cmd_type);
            break;
        }

        chBuf[0] = 0x0;
    }

    Log::WriteLog(LL_DEBUG, "AsynAPISet::ReceiverFunc->thread exited, %s.",
        running_? "running_Ϊtrue": "running_Ϊfalse");
}

int MC::Cnn::WritePipe(BaseCmd* cmd)
{
    // �ӻ�����, ������߳�д�ܵ���������.
    boost::lock_guard<boost::mutex> lk(write_ctx_);

    if (!running_) {
        //AsynErrorNotify(cmd, MC::EC_PIPE_STOPPED);
        return MC::EC_CON_DISCONN;
    }

    if (NULL == cmd)
        return MC::EC_INVALID_PARAMETER;

    cmd->Ser();
    // д��pipe
    LPTSTR lpvMessage = TEXT(cmd->xs_.GetBuf());
    BOOL fSuccess = WriteFileEx(
        pipe_,
        lpvMessage,
        (lstrlen(lpvMessage) + 1) * sizeof(TCHAR), // д�����ݵĳ���
        (LPOVERLAPPED)pipe_inst_,
        (LPOVERLAPPED_COMPLETION_ROUTINE)CompletedWriteRoutine);
    if (!fSuccess) {
        Log::WriteLog(LL_ERROR, "APISet::WritePipe->WriteFileEx failed, err: %d",
            GetLastError());
        return -1;
    }

    return 0;
}

int MC::Cnn::WriteMQ(BaseCmd* cmd)
{
    // message queue ����֧�ֶ��߳�, ����Ҫ�Լ��ټ���
    /*    boost::lock_guard<boost::mutex> lk(write_ctx_);*/

    if (!running_)
        return MC::EC_CON_DISCONN;

    if (NULL == cmd)
        return MC::EC_INVALID_PARAMETER;

    cmd->Ser();
    LPTSTR lpvMessage = TEXT(cmd->xs_.GetBuf());
    int msg_size = (lstrlen(lpvMessage) + 1) * sizeof(TCHAR);
    try {
        if (ProcessExisted(MC::SERVER_NAME)) {
            heart_mtx_.lock();
            bool succ = send_mq_->try_send(lpvMessage, msg_size, 0);
            heart_mtx_.unlock();

            // ����������Ϣ
            if (cmd->ct_ != CT_HEART_BEAT)
                Log::WriteLog(LL_DEBUG, "AsynAPISet::WriteMQ->Cmd: %s, ��Ϣ��С: %d, ���ͽ��: %s",
                    cmd_des[cmd->ct_].c_str(),
                    msg_size,
                    succ ? "�ɹ�" : "ʧ��");
        } else {
            Log::WriteLog(LL_ERROR, "AsynAPISet::WriteMQ->����ͨ���Ͽ�");
            return MC::EC_CON_DISCONN;
        }
    } catch (boost::interprocess::interprocess_exception &ex) {
        std::cout << "AsynAPISet::WriteMQ->msg size: " << msg_size << ", exception: "
            << ex.what() << std::endl;
    }

    return MC::EC_SUCC;
}

int MC::Cnn::WriteCnn(BaseCmd* cmd)
{
    if (MC::CT_PIPE == Config::GetInst()->conn_type_)
        return WritePipe(cmd);
    else if (MC::CT_MQ == Config::GetInst()->conn_type_)
        return WriteMQ(cmd);
    else
        return -1;
}

void MC::Cnn::SendFunc()
{
    BaseCmd* cmd = NULL;
    while (running_) {
        if (0 == send_cmd_queue_.WaitForRead(SEND_QUEUE_WAIT)) {
            send_cmd_queue_.Pop(cmd);
            WriteCnn(cmd);
            delete cmd;
        }
    }
}

// �յ�������̷��ͻص�������Ӧ
void MC::Cnn::HandleHeartBeating(char* chBuf)
{
    SetEvent(heart_ev_);
}

void MC::Cnn::HeartBeatingFunc()
{
    while (running_) {
        DWORD ret = WaitForSingleObject(heart_ev_, HEART_BEATING_WAIT);
        switch (ret) {
        case WAIT_OBJECT_0: {
            HeartCmd heart_cmd;
            WriteCnn(&heart_cmd);
        }
            break;
        case WAIT_TIMEOUT: {    // ��ʱδ�յ�������Ӧ
            Log::WriteLog(LL_DEBUG, "AsynAPISet::HeartBeatingFunc->timeout heart beating");

            if (ProcessExisted(MC::SERVER_NAME))
                continue;

            // ��������
            if (StartSvc(MC::SERVER_NAME)) {
                Log::WriteLog(LL_DEBUG, "AsynAPISet::HeartBeatingFunc->����%s�ɹ�",
                    MC::SERVER_NAME.c_str());

                Sleep(1000);
                // �������ֹͣ, ��Ҫ���½��������ڴ�ͨ������, ���������ͺͽ��չ����ڴ����
                heart_mtx_.lock();
                delete recv_mq_;
                delete send_mq_;

                try {
                    send_mq_ = new (std::nothrow) boost::interprocess::message_queue(
                        boost::interprocess::open_only,
                        Config::GetInst()->send_mq_name_.c_str());

                    recv_mq_ = new (std::nothrow) boost::interprocess::message_queue(
                        boost::interprocess::open_only,
                        Config::GetInst()->recv_mq_name_.c_str());
                }  catch (boost::interprocess::interprocess_exception &ex) {
                    std::cout << "AsynAPISet::HeartBeatingFunc->����Ϣ����ʧ��: " 
                        << ex.what() << std::endl;
                    Log::WriteLog(LL_ERROR, "AsynAPISet::HeartBeatingFunc->����Ϣ����ʧ��: %s", 
                        ex.what());
                }

                heart_mtx_.unlock();

                // �����ɹ�����Ҫ����һ������
                HeartCmd heart_cmd;
                WriteCnn(&heart_cmd);
            } else {
                Log::WriteLog(LL_ERROR, "AsynAPISet::HeartBeatingFunc->����%sʧ��",
                    MC::SERVER_NAME.c_str());
            }
        }
            break;
        default:
            break;
        }
    }
}


bool MC::Cnn::StartSvc(const std::string& svc)
{
    std::string root_path;
    if (!MC::GetMoudulePath(root_path))
        return false;

    char buf[512] = { 0 };
    sprintf_s(buf, "%s%s exe",
        root_path.c_str(),
        svc.c_str());

    if (31 < WinExec(buf, SW_HIDE))
        return true;

    return false;

    // ����ָ������
    SC_HANDLE hSC = ::OpenSCManager(
        NULL,
        NULL,
        GENERIC_EXECUTE);
    if (hSC == NULL)
        return false;

    SC_HANDLE hSvc = ::OpenService(
        hSC,
        svc.c_str(),
        SERVICE_START | SERVICE_QUERY_STATUS | SERVICE_STOP);
    if (hSvc == NULL) {
        ::CloseServiceHandle(hSC);
        return false;
    }

    // ��÷����״̬  
    SERVICE_STATUS status;
    if (::QueryServiceStatus(hSvc, &status) == FALSE) {
        ::CloseServiceHandle(hSvc);
        ::CloseServiceHandle(hSC);
        return false;
    }

    if (status.dwCurrentState == SERVICE_STOPPED) {
        // ��������  
        if (::StartService(hSvc, NULL, NULL) == FALSE) {
            ::CloseServiceHandle(hSvc);
            ::CloseServiceHandle(hSC);
            return false;
        }

        return true;
    }
    else if (status.dwCurrentState == SERVICE_RUNNING) {
        return true;
    }
    else {
        Log::WriteLog(LL_DEBUG, "AsynAPISet::StartSvc->��ǰ����״̬��: %d", status.dwCurrentState);
        return false;
    }
}

//////////////////////////////////////////////////////////////////////////

bool MC::ProcessExisted(const std::string& process_name)
{
    PROCESSENTRY32 pe32;
    pe32.dwSize = sizeof(pe32);
    HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hProcessSnap == INVALID_HANDLE_VALUE) {
        std::cout << "CreateToolhelp32Snapshot Error!" << std::endl;;
        return false;
    }

    BOOL bResult = Process32First(hProcessSnap, &pe32);
    bool ret = false;
    while (bResult) {
        std::string name = pe32.szExeFile;      // process name
        int id = pe32.th32ProcessID;            // process id
        if (process_name == name) {
            ret = true;
            break;
        }

        bResult = Process32Next(hProcessSnap, &pe32);
    }

    CloseHandle(hProcessSnap);
    return ret;
}

VOID WINAPI CompletedWriteRoutine(
    DWORD dwErr,
    DWORD cbWritten,
    LPOVERLAPPED lpOverLap)
{
    Log::WriteLog(LL_DEBUG, "CompletedWriteRoutine->Agentд�ܵ�, Err: %d, ʵ��д��: %d",
        dwErr,
        cbWritten);
}
