#include <windows.h> 
#include <stdio.h>
#include <tchar.h>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/interprocess/ipc/message_queue.hpp>
#include <boost/typeof/typeof.hpp>
#include <boost/exception/all.hpp>
#include "recver.h"
#include "log.h"
#include "pipe_server.h"
#include "common_definitions.h"

Recver g_recver;

VOID DisconnectAndClose(LPPIPEINST);
BOOL CreateAndConnectInstance(LPOVERLAPPED);
BOOL ConnectToNewClient(HANDLE, LPOVERLAPPED);
VOID GetAnswerToRequest(LPPIPEINST);
VOID WINAPI CompletedWriteRoutine(DWORD, DWORD, LPOVERLAPPED);
VOID WINAPI CompletedReadRoutine(DWORD, DWORD, LPOVERLAPPED);

HANDLE hPipe;

int StartServer()
{
    if (!g_recver.Start()) {
        Log::WriteLog(LL_ERROR, "StartPipe->fails to start recver");
        return -1;
    }

    if (MC::CT_PIPE == g_recver.CnnType()) {
        HANDLE hConnectEvent;
        OVERLAPPED oConnect;
        LPPIPEINST lpPipeInst;
        DWORD dwWait, cbRet;
        BOOL fSuccess, fPendingIO;

        // �������Ӳ������¼����� 
        hConnectEvent = CreateEvent(
            NULL,    // Ĭ������
            TRUE,    // �ֹ�reset
            TRUE,    // ��ʼ״̬ signaled 
            NULL);   // δ����

        if (hConnectEvent == NULL)
        {
            printf("CreateEvent failed with %d.\n", GetLastError());
            return 0;
        }
        // OVERLAPPED �¼�
        oConnect.hEvent = hConnectEvent;

        // ��������ʵ�����ȴ�����
        fPendingIO = CreateAndConnectInstance(&oConnect);

        while (1) {
            // �ȴ��ͻ������ӻ��д������� 
            dwWait = WaitForSingleObjectEx(
                hConnectEvent,  // �ȴ��ͻ������ӵ��¼� 
                INFINITE,       // ���޵ȴ�
                TRUE);

            switch (dwWait)
            {
            case 0:
                // pending
                if (fPendingIO) {
                    // ��ȡ Overlapped I/O �Ľ��
                    fSuccess = GetOverlappedResult(
                        hPipe,     // pipe ���
                        &oConnect, // OVERLAPPED �ṹ
                        &cbRet,    // �Ѿ����͵�������
                        FALSE);    // ���ȴ�
                    if (!fSuccess) {
                        printf("ConnectNamedPipe (%d)\n", GetLastError());
                        return 0;
                    }
                }

                // �����ڴ�
                lpPipeInst = (LPPIPEINST)HeapAlloc(GetProcessHeap(), 0, sizeof(PIPEINST));
                if (lpPipeInst == NULL) {
                    printf("GlobalAlloc failed (%d)\n", GetLastError());
                    return 0;
                }
                lpPipeInst->hPipeInst = hPipe;

                // ����д, ע��CompletedWriteRoutine��CompletedReadRoutine���໥����
                lpPipeInst->cbToWrite = 0;
                CompletedWriteRoutine(0, 0, (LPOVERLAPPED)lpPipeInst);

                // �ٴ���һ������ʵ��, ����Ӧ��һ���ͻ��˵�����
                fPendingIO = CreateAndConnectInstance(&oConnect);
                break;

                // ��д��� 
            case WAIT_IO_COMPLETION:
                break;

            default: {
                printf("WaitForSingleObjectEx (%d)\n", GetLastError());
                return 0;
            }
            }
        }
    }

    return 0;
}

VOID WINAPI CompletedWriteRoutine(
    DWORD dwErr,
    DWORD cbWritten,
    LPOVERLAPPED lpOverLap)
{
    LPPIPEINST lpPipeInst;
    BOOL fRead = FALSE;
    // ����overlapʵ��
    lpPipeInst = (LPPIPEINST)lpOverLap;

    // ���û�д���
    if ((dwErr == 0) && (cbWritten == lpPipeInst->cbToWrite)) {
        fRead = ReadFileEx(
            lpPipeInst->hPipeInst,
            lpPipeInst->chRequest,
            CMD_BUF_SIZE * sizeof(TCHAR),
            (LPOVERLAPPED)lpPipeInst,
            // д��������ɺ�, ����CompletedReadRoutine
            (LPOVERLAPPED_COMPLETION_ROUTINE)CompletedReadRoutine);
    }

    if (!fRead) {
        // ����, �Ͽ�����
        printf("ReadFileEx fails (%ld)\n", GetLastError());
        DisconnectAndClose(lpPipeInst);
    }
}

/* ************************************
* CompletedReadRoutine
*     ��ȡpipe��������ɺ���
*    �ӿڲμ�FileIOCompletionRoutine�ص���������
*
*    �����������ʱ�����ã�д��ظ�
**************************************/
VOID WINAPI CompletedReadRoutine(
    DWORD dwErr,
    DWORD cbBytesRead,
    LPOVERLAPPED lpOverLap)
{
    LPPIPEINST lpPipeInst;
    BOOL fWrite = FALSE;

    // ����overlapʵ��
    lpPipeInst = (LPPIPEINST)lpOverLap;

    // ���û�д���
    if ((dwErr == 0) && (cbBytesRead != 0))
    {
        // ���ݿͻ��˵��������ɻظ�
        GetAnswerToRequest(lpPipeInst);

//         DWORD avail = 0;
//         PeekNamedPipe(lpPipeInst->hPipeInst);
        // ���ظ�д�뵽pipe
        fWrite = WriteFileEx(
            lpPipeInst->hPipeInst,
            lpPipeInst->chReply,    //����Ӧд��pipe
            lpPipeInst->cbToWrite,
            (LPOVERLAPPED)lpPipeInst,
            // д����ɺ󣬵���CompletedWriteRoutine
            (LPOVERLAPPED_COMPLETION_ROUTINE)CompletedWriteRoutine);
    }

    if (!fWrite)
        // �����Ͽ�����
        DisconnectAndClose(lpPipeInst);
}

/* ************************************
* VOID DisconnectAndClose(LPPIPEINST lpPipeInst)
* ����    �Ͽ�һ�����ӵ�ʵ��
* ����    lpPipeInst���Ͽ����رյ�ʵ�����
**************************************/
VOID DisconnectAndClose(LPPIPEINST lpPipeInst)
{
    // �ر�����ʵ��
    if (!DisconnectNamedPipe(lpPipeInst->hPipeInst))
    {
        printf("DisconnectNamedPipe failed with %d.\n", GetLastError());
    }
    // �ر� pipe ʵ���ľ�� 
    CloseHandle(lpPipeInst->hPipeInst);
    // �ͷ�
    if (lpPipeInst != NULL)
        HeapFree(GetProcessHeap(), 0, lpPipeInst);
}

/* ************************************
* BOOL CreateAndConnectInstance(LPOVERLAPPED lpoOverlap)
* ����    ��������ʵ��
* ����    lpoOverlap������overlapped IO�Ľṹ
* ����ֵ    �Ƿ�ɹ�
**************************************/
BOOL CreateAndConnectInstance(LPOVERLAPPED lpoOverlap)
{
    std::string path;
    if (!MC::GetMoudulePath(path))
        return FALSE;

    std::string xml_path = path + "server.xml";
    std::string type;
    std::string name;
    try {
        boost::property_tree::ptree pt;
        boost::property_tree::xml_parser::read_xml(xml_path, pt);
        type = pt.get<std::string>("con.type");
        name = pt.get<std::string>("con.name");
    } catch (...) {
        boost::exception_ptr e = boost::current_exception();
        std::cout << boost::current_exception_diagnostic_information();
        //printf("read_xml fails\n");
        system("pause");
        return FALSE;
    }

    char cnn_name[1024] = { 0 };
    sprintf_s(cnn_name, "\\\\.\\pipe\\%s", name.c_str());
    LPTSTR lpszPipename = TEXT(cnn_name);
    // ����named pipe     
    hPipe = CreateNamedPipe(
        lpszPipename,             // pipe�� 
        PIPE_ACCESS_DUPLEX |      // �ɶ���д
        FILE_FLAG_OVERLAPPED,     // overlapped ģʽ
        // pipeģʽ
        PIPE_TYPE_BYTE |       // ��Ϣ����pipe
        PIPE_READMODE_BYTE |   // ��Ϣ��ģʽ
        PIPE_WAIT,                // ����ģʽ
        PIPE_UNLIMITED_INSTANCES, // ������ʵ��
        PIPE_MAX_BUF * sizeof(TCHAR),  // ��������С
        PIPE_MAX_BUF * sizeof(TCHAR),  // ���뻺���С
        PIPE_TIMEOUT,             // �ͻ��˳�ʱ
        NULL);                    // Ĭ�ϰ�ȫ����
    if (hPipe == INVALID_HANDLE_VALUE) {
        printf("CreateNamedPipe failed with %d.\n", GetLastError());
        return 0;
    }

    Log::WriteLog(LL_DEBUG, "CreateAndConnectInstance->CreateNamedPipe, hPipe: %d, err: %d",
        (int)hPipe,
        GetLastError());

    // ���ӵ��µĿͻ���
    return ConnectToNewClient(hPipe, lpoOverlap);
}

/* ************************************
* BOOL ConnectToNewClient(HANDLE hPipe, LPOVERLAPPED lpo)
* ����    ��������ʵ��
* ����    lpoOverlap������overlapped IO�Ľṹ
* ����ֵ    �Ƿ�ɹ�
**************************************/
BOOL ConnectToNewClient(HANDLE hPipe, LPOVERLAPPED lpo)
{
    BOOL fConnected, fPendingIO = FALSE;

    // ��ʼһ�� overlapped ����, ����lpo�ǿ�, ���ú����������;
    // ��ʱ, ��ܵ���δ����, �ͻ�ͬ�ܵ�����ʱ�ͻᴥ��lpOverlapped�ṹ�е��¼�����.
    // ���, ����һ���ȴ���������������.
    fConnected = ConnectNamedPipe(hPipe, lpo);
    if (fConnected) {
        printf("ConnectNamedPipe failed with %d.\n", GetLastError());
        return 0;
    }

    printf("�ɹ����ܿͻ�������, err:%d\n", GetLastError());
    switch (GetLastError()) {
        // overlapped���ӽ�����.
    case ERROR_IO_PENDING:
        fPendingIO = TRUE;
        break;
        // �Ѿ����ӣ����Eventδ��λ 
    case ERROR_PIPE_CONNECTED:
        if (SetEvent(lpo->hEvent))
            break;
        // error
    default:
    {
        printf("ConnectNamedPipe failed with %d.\n", GetLastError());
        return 0;
    }
    }

    return fPendingIO;
}

// TODO���ݿͻ��˵����󣬸�����Ӧ
VOID GetAnswerToRequest(LPPIPEINST pipe)
{
/*    _tprintf(TEXT("[%d] %s\n"), pipe->hPipeInst, pipe->chRequest);*/
    RecvMsg* msg = new (std::nothrow) RecvMsg();
    if (NULL == msg)
        return;

    msg->pipe_inst = pipe;
    memcpy(msg->msg, pipe->chRequest, sizeof(msg->msg));
    g_recver.Insert(msg);
    g_recver.Signal();
}
