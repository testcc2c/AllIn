#include "stdafx.h"
#include <stdlib.h>
#include <math.h>
#include <vector>
#include "event_cpu.h"
#include "tool.h"
#include "boc_api.h"
#include "task_mgr.h"

MC::BOCApi* MC::BOCApi::inst_ = NULL;

//////////////////////////// ��ȡ��ӡ����� ///////////////////////////////

class QueryMachEv : public MC::BaseEvent {

public:
    QueryMachEv(std::string des, MC::NotifyResult* notify)
        : BaseEvent(des),
        notify_(notify) {

    }

    virtual void SpecificExecute() {
        // ��ȡ��ӡ�����
        // ������������κ�ʱ�䣬���κ�PC����
        unsigned char sn[23] = { 0 };
        MC::ErrorCode ec = exception_;
        if (MC::EC_SUCC != ec)
            goto NT;

        // ����-��ȡӡ���Ǳ��
        int ret = ReadStamperIdentifier(sn, sizeof(sn));
        if (0 != ret) {
            ec = MC::EC_DRIVER_FAIL;
            goto NT;
        }

        ec = MC::EC_SUCC;

    NT:
        notify_->Notify(ec, (char*)sn);
        Log::WriteLog(LL_DEBUG, "MC::QueryMachEv::SpecificExecute->ec: %s, ӡ���Ǳ��: %s",
            MC::ErrorMsg[ec].c_str(),
            (char*)sn);
        delete this;
    }

private:
    MC::NotifyResult*   notify_;
};

void MC::BOCApi::QueryMachine(MC::NotifyResult* notify)
{
    BaseEvent* ev = new (std::nothrow) QueryMachEv("��ȡ��ӡ�����" + des_, notify);
    if (NULL == ev)
        return notify->Notify(MC::EC_ALLOCATE_FAILURE);

    EventCPUCore::GetInstance()->PostEvent(ev);
}

////////////////////////// ����ӡ�ػ���� //////////////////////////////////

class SetMachEv : public MC::BaseEvent {

public:
    SetMachEv(std::string des, std::string sn, MC::NotifyResult* notify)
        : BaseEvent(des), sn_(sn),
        notify_(notify) {

    }

    virtual void SpecificExecute() {
        MC::ErrorCode ec = exception_;
        if (MC::EC_SUCC != ec)
            goto NT;

        // ����-����ӡ�ػ����
        int ret = WriteStamperIdentifier((unsigned char*)sn_.c_str(), sn_.size());
        if (0 != ret) {
            ec = MC::EC_DRIVER_FAIL;
            goto NT;
        }

        ec = MC::EC_SUCC;

    NT:
        notify_->Notify(ec, sn_);
        Log::WriteLog(LL_DEBUG, "MC::QueryMachEv::SpecificExecute->ec: %s, ������ӡ���Ǳ��: %s",
            MC::ErrorMsg[ec].c_str(),
            sn_.c_str());
        delete this;
    }

private:
    std::string sn_;
    MC::NotifyResult*   notify_;
};

void MC::BOCApi::SetMachine(const std::string& sn, NotifyResult* notify)
{
    BaseEvent* ev = new (std::nothrow) SetMachEv("����ӡ�ػ����" + des_, sn, notify);
    if (NULL == ev)
        return notify->Notify(MC::EC_ALLOCATE_FAILURE);

    EventCPUCore::GetInstance()->PostEvent(ev);
}

/////////////////////////// ��ʼ��ӡ�ػ� ////////////////////////////////

class InitMachEv : public MC::BaseEvent {

public:
    InitMachEv(std::string des, std::string code, MC::NotifyResult* notify)
        : BaseEvent(des),
        code_(code),
        notify_(notify) {

    }

    virtual void SpecificExecute() {
        //1��	ִ�б�����ʱ����ӡ���Ⱥ˶�key�Ƿ������ӡ������ʱ�ṩ��һ�£���һ�£�����ʧ��.
        //2��	��ӡ���жϵ��ñ������PC��MAC��ַ�Ƿ�����ӡ�����б��У�
        //      A�������б��У�������سɹ������������ӿڶ�����ʹ�á�
        //      B���������б��У����жϰ󶨵�PC��MAC��ַ��������ַ�� < 2, ������سɹ���
        //      ����PCֻ�ܵ��á���ӡ����PC���ӿڣ����������ӿ�ʱ����ʧ�ܣ�����ַ�� >= 2, �������ʧ�ܡ�
        //3��   ��ָ��Ӧ����������ָ������κ�ʱ�򣨰���δ�ͷ���ӡ��ʱ��ִ�к󣬶�Ӧ��ȷ���ء�

        std::string local_mac;  // ����MAC��ַ(to-do)
        char code[512] = { 0 }; // ����ʱ�趨��֤��
        MC::ErrorCode ec = exception_;
        if (MC::EC_SUCC != ec)
            goto NT;

        //����-��ʼ��ӡ�ػ�
        int ret = GetDevCode(code, 511);
        if (0 != ret) {
            ec = MC::EC_DRIVER_FAIL;
            goto NT;
        }

        // У����֤��, ��һ���򷵻�ʧ��
        if (0 != strcmp(code_.c_str(), code)) {
            ec = MC::EC_CODE_MISMATCH;
            goto NT;
        }

        // һ��������ж�MAC��ַ
        unsigned char mac1[18] = { 0 };
        unsigned char mac2[18] = { 0 };
        ret = ReadMAC(mac1, mac2);
        if (0 != ret) {
            ec = MC::EC_DRIVER_FAIL;
            goto NT;
        }

        // mac��ַ���б���, ���سɹ�
        if (0 == strcmp(local_mac.c_str(), (char*)mac1) ||
            0 == strcmp(local_mac.c_str(), (char*)mac2)) {
            ec = MC::EC_SUCC;
            goto NT;
        }

        // mac��ַ�����б���, �ж��Ѱ�MAC��ַ��
        int bound_count = 0;
        for (int i = 0; i < 18; ++i) {
            if (mac1[i] != 0x0) {
                ++bound_count;
                break;
            }
        }

        for (int i = 0; i < 18; ++i) {
            if (mac2[i] != 0x0) {
                ++bound_count;
                break;
            }
        }

        if (bound_count >= 2) {
            ec = MC::EC_FAIL;
            goto NT;
        }

        // mac ��ַ�����б���, �Ұ�MAC��ַ��С��2
        ec = MC::EC_SUC_CALL_BIND;

    NT:
        notify_->Notify(ec, code_);
        Log::WriteLog(LL_DEBUG, "MC::InitMachEv::SpecificExecute->ec: %s, ����֤��֤��: %s, "
            "����ʱ��֤��: %s",
            MC::ErrorMsg[ec].c_str(), 
            code_.c_str(),
            code);
        delete this;
    }

private:
    std::string         code_;      // ����֤��ӡ����֤��
    MC::NotifyResult*   notify_;
};

void MC::BOCApi::InitMachine(std::string key, NotifyResult* notify)
{
    BaseEvent* ev = new (std::nothrow) InitMachEv("��ʼ��ӡ�ػ�" + des_, key, notify);
    if (NULL == ev)
        return notify->Notify(MC::EC_ALLOCATE_FAILURE, key);

    EventCPUCore::GetInstance()->PostEvent(ev);
}

/////////////////////////// ��ӡ����MAC��ַ ///////////////////////////

class BindMACEv : public MC::BaseEvent {

public:
    BindMACEv(std::string des, std::string mac, MC::NotifyResult* notify)
        : BaseEvent(des),
        mac_(mac),
        notify_(notify) {

    }

    virtual void SpecificExecute() {
        // һ̨��ӡ�����ֻ�ܰ�2��MAC��ַ.

        unsigned char mac1[32] = { 0 };
        unsigned char mac2[32] = { 0 };
        MC::ErrorCode ec = exception_;
        if (MC::EC_SUCC != ec)
            goto NT;

        int ret = ReadMAC(mac1, mac2, 18);
        if (0 != ret) {
            ec = MC::EC_DRIVER_FAIL;
            goto NT;
        }

        // MAC��ַ�Ѿ��󶨹�
        if (0 == strcmp(mac_.c_str(), (char*)mac1) ||
            0 == strcmp(mac_.c_str(), (char*)mac2)) {
            ec = MC::EC_ALREADY_BOUND;
            goto NT;
        }

        // �Ѿ��ﵽ��MAC��ַ����
        size_t mac1_len = strlen((char*)mac1);
        size_t mac2_len = strlen((char*)mac2);
        if (0 != mac1_len && 0 != mac2_len) {
            ec = MC::EC_MAC_MAX;
            goto NT;
        }

        // ��MAC��ַ
        if ((0 == mac1_len && 0 == mac2_len) || 
            (0 == mac1_len && 0 != mac2_len)) {         // ���浽��һ���洢MAC��ַλ��
            int ret = WriteMAC(
                (unsigned char*)mac_.c_str(),
                NULL);
            if (0 != ret) {
                ec = MC::EC_DRIVER_FAIL;
                goto NT;
            }
        }
        else if (0 != mac1_len && 0 == mac2_len) {    // ���浽�ڶ����洢MAC��ַλ��
            int ret = WriteMAC(
                NULL,
                (unsigned char*)mac_.c_str());
            if (0 != ret) {
                ec = MC::EC_DRIVER_FAIL;
                goto NT;
            }
        }

        ec = MC::EC_SUCC;

    NT:
        notify_->Notify(ec, mac_);
        Log::WriteLog(LL_DEBUG, "MC::BindMACEv::SpecificExecute->��MAC��ַ, ec: %d, ����MAC: %s, "
            "�Ѱ󶨵�ַ1: %s, �Ѱ󶨵�ַ2: %s",
            ec,
            mac_.c_str(),
            mac1,
            mac2);
        delete this;
    }

private:
    std::string         mac_;           // ����MAC��ַ
    MC::NotifyResult*   notify_;
};

void MC::BOCApi::BindMAC(std::string mac, NotifyResult* notify)
{
    BaseEvent* ev = new (std::nothrow) BindMACEv("��ӡ����MAC��ַ" + des_, mac, notify);
    if (NULL == ev)
        return notify->Notify(MC::EC_ALLOCATE_FAILURE, mac);

    EventCPUCore::GetInstance()->PostEvent(ev);
}

/////////////////////////// ��ӡ�����MAC ///////////////////////////

class UnbindMACEv : public MC::BaseEvent {

public:
    UnbindMACEv(std::string des, std::string mac, MC::NotifyResult* notify)
        : BaseEvent(des),
        mac_(mac),
        notify_(notify) {

    }

    virtual void SpecificExecute() {
        // ���ڰ󶨺��PC�Ͻ��
        unsigned char mac1[18] = { 0 };
        unsigned char mac2[18] = { 0 };
        MC::ErrorCode ec = exception_;
        if (MC::EC_SUCC != ec)
            goto NT;

        // ��ӡ�����MAC
        // ���Ȼ�ȡ�����Ѱ󶨵�MAC
        int ret = ReadMAC(mac1, mac2);
        if (0 != ret) {
            ec = MC::EC_DRIVER_FAIL;
            goto NT;
        }

        // �����MAC��ַδ�󶨵���ӡ�ػ�
        int mac1_cmp = strcmp(mac_.c_str(), (char*)mac1);
        int mac2_cmp = strcmp(mac_.c_str(), (char*)mac2);
        if (0 != mac1_cmp && 0 != mac2_cmp) {
            ec = MC::EC_NOT_BOUND;
            goto NT;
        }

        // ���MAC��ַԭ��:  ���ض���MAC��ַд������"���MAC"��ַ��PC��
        if (0 == mac1_cmp) {
            ret = WriteMAC(
                (unsigned char*)"",
                NULL,
                1,
                0);
            if (0 != ret) {
                ec = MC::EC_DRIVER_FAIL;
                goto NT;
            }
        } else {
            ret = WriteMAC(
                NULL,
                (unsigned char*)"",
                0,
                1);
            if (0 != ret) {
                ec = MC::EC_DRIVER_FAIL;
                goto NT;
            }
        }

        ec = MC::EC_SUCC;

    NT:
        notify_->Notify(ec, mac_);
        Log::WriteLog(LL_DEBUG, "MC::UnbindMACEv::SpecificExecute->���MAC��ַ, ec: %s, �����MAC: %s,"
            "�Ѱ󶨵�ַ1: %s, �Ѱ󶨵�ַ2: %s",
            MC::ErrorMsg[ec].c_str(), 
            mac_.c_str(),
            mac1,
            mac2);
        delete this;
    }

private:
    std::string         mac_;
    MC::NotifyResult*   notify_;
};

void MC::BOCApi::UnbindMAC(std::string mac, NotifyResult* notify)
{
    BaseEvent* ev = new (std::nothrow) UnbindMACEv("��ӡ�����MAC��ַ" + des_, mac, notify);
    if (NULL == ev)
        return notify->Notify(MC::EC_ALLOCATE_FAILURE, mac);

    EventCPUCore::GetInstance()->PostEvent(ev);
}

/////////////////////////// ׼����ӡ ////////////////////////////

class PrepareStampEv : public MC::BaseEvent {

public:
    PrepareStampEv(std::string des, int num, int timeout, MC::NotifyResult* notify)
        : BaseEvent(des),
        running_(false),
        paper_thread(NULL),
        num_(num),
        timeout_(timeout),
        notify_(notify) {

    }

    virtual void SpecificExecute() {
        // ��ӡ������������ӡ���Զ�������ֽ�Ź��û����������Ʊ�ݣ�
        // �û��������Ʊ�ݲ��ر���ӡ����ֽ�ţ���ӡ�����ر��θ������������ID��
        // ��ӡ����ǰ����Ӧ��׼������ӡ����������ʱʱ�䣬��ӡ��������
        // �Զ���ӡ���˹���ӡ����Ҫ�����

        char num_str[5] = { 0 };
        char timeout_str[5] = { 0 };
        MC::ErrorCode ec = exception_;
        if (ec != MC::EC_SUCC)
            goto NT;

        // ӡ���Ǵ�������״̬�²���׼����ӡ, ��Ҫ�Ƚ���ӡ����
        if (IsLocked()) {
            ec = MC::EC_MACHINE_LOCKED;
            goto NT;
        }

        // ��ӡ׼��ʱ����ӡ����
        if (0 != Lock()) {
            ec = MC::EC_LOCK_MACHINE_FAIL;
            goto NT;
        }

        // ������ֽ�ſ�����ʱ��ʾʱ��, Ĭ��30��
        int ret = SetPaperDoor(timeout_);
        if (-1 == ret) {
            ec = MC::EC_DRIVER_FAIL;
            goto NT;
        }

        // ����ֽ��
        ret = FOpenDoorPaper();
        if (-1 == ret) {
            ec = MC::EC_DRIVER_FAIL;
            goto NT;
        }

        // �����̼߳���ֽ��״̬
        running_ = true;
        paper_thread =
            new (std::nothrow) boost::thread(boost::bind(&PrepareStampEv::ThreadFunc, this));
        return;

    NT:
        notify_->Notify(ec, _itoa(num_, num_str, 10), _itoa(timeout_, timeout_str, 10));
        Log::WriteLog(LL_DEBUG, "MC::PrepareStampEv::SpecificExecute->׼����ӡ, ec: %s, �²ۺ�: %d, "
            "��ʱ: %d",
            MC::ErrorMsg[ec].c_str(),
            num_,
            timeout_);
    }

private:
    int                 num_;       // �²ۺ�
    int                 timeout_;   // ��ֽ�ų�ʱδ�ر�ʱ��(�ݶ�15��)
    MC::NotifyResult*   notify_;

private:
    bool                running_;
    boost::thread*      paper_thread;
    void                ThreadFunc();
};

void PrepareStampEv::ThreadFunc()
{
    while (running_) {
        ResetEvent(MC::Tool::GetInst()->paper_door_ev_);
        DWORD ret = WaitForSingleObject(MC::Tool::GetInst()->paper_door_ev_, timeout_ * 1000);
        char num_str[5] = { 0 };
        char timeout_str[5] = { 0 };
        _itoa(num_, num_str, 10);
        _itoa(timeout_, timeout_str, 10);

        switch (ret) {
            // ��ʱʱ�����յ�ֽ�Źر��ź�, ֽ�Źر��ź��Զ���λ
        case WAIT_OBJECT_0: {
            boost::this_thread::interruption_point();

            MC::ErrorCode ec = MC::EC_SUCC;
            std::string task_id = MC::TaskMgr::GetInst()->GeneTask();
            notify_->Notify(
                ec,
                num_str,
                timeout_str,
                task_id);
            running_ = false;

            Log::WriteLog(LL_DEBUG, "PrepareStampEv::ThreadFunc->׼����ӡ�ɹ�, "
                "ec: %s, �����: %s", 
                MC::ErrorMsg[ec].c_str(),
                task_id.c_str());
        }
            break;
            // ��ʱ��ֽ��δ�ر�
        case WAIT_TIMEOUT: {
            boost::this_thread::interruption_point();

            MC::ErrorCode ec = MC::EC_PAPER_TIMEOUT;
            std::string task_id;
            notify_->Notify(
                ec,
                num_str,
                timeout_str,
                task_id);
            running_ = false;

            Log::WriteLog(LL_DEBUG, "PrepareStampEv::ThreadFunc->׼����ӡ��ʱ, "
                "ec: %s, �����: %s", 
                MC::ErrorMsg[ec].c_str(),
                task_id.c_str());
        }
            break;
        default:
            break;
        }

        Log::WriteLog(LL_DEBUG, "PrepareStampEv::ThreadFunc->����ֽ�Źر��߳��˳�");
        paper_thread->interrupt();
        delete paper_thread;
        delete this;
    }
}

void MC::BOCApi::PrepareStamp(int stamp_num, int timeout, NotifyResult* notify)
{
    BaseEvent* ev = new (std::nothrow) PrepareStampEv("׼����ӡ" + des_, stamp_num, timeout, notify);
    if (NULL == ev)
        return notify->Notify(MC::EC_ALLOCATE_FAILURE);

    EventCPUCore::GetInstance()->PostEvent(ev);
}

///////////////////////////// ��ѯ��ֽ�� /////////////////////////////////

class QueryPaperEv : public MC::BaseEvent {
public:
    QueryPaperEv(std::string des, MC::NotifyResult* notify)
        : BaseEvent(des),
        notify_(notify) {

    }

    virtual void SpecificExecute() {
        char paper_str[5] = { 0 };
        MC::ErrorCode ec = exception_;
        if (ec != MC::EC_SUCC)
            goto NT;

        // ����-��ѯ��ֽ��
        char doors[4] = { 0 };
        int ret = FGetDoorsPresent(doors, sizeof(doors));
        if (0 != ret) {
            ec = MC::EC_DRIVER_FAIL;
            goto NT;
        }

        sprintf_s(paper_str, "%d", doors[0]);
        ec = MC::EC_SUCC;

    NT:
        notify_->Notify(
            ec,
            paper_str);
        Log::WriteLog(LL_DEBUG, "MC::QueryPaperEv::SpecificExecute->��ѯ��ֽ��, ec: %s, ״̬: %s",
            MC::ErrorMsg[ec].c_str(),
            paper_str);
        delete this;
    }

private:
    MC::NotifyResult* notify_;
};

void MC::BOCApi::QueryPaperDoor(MC::NotifyResult* notify)
{
    BaseEvent* ev = new (std::nothrow) QueryPaperEv(
        "��ѯ��ֽ��" + des_,
        notify);
    if (NULL == ev)
        notify->Notify(MC::EC_ALLOCATE_FAILURE);

    EventCPUCore::GetInstance()->PostEvent(ev);
}

/////////////////////////////////// ���� /////////////////////////////////

class SnapshotEv : public MC::BaseEvent {

public:
    SnapshotEv(std::string des, int original_dpi, int cut_dpi, 
        const std::string& ori_path, const std::string& cut_path,
        MC::NotifyResult* notify)
        : BaseEvent(des),
        ori_dpi_(original_dpi),
        cut_dpi_(cut_dpi),
        ori_(ori_path),
        cut_(cut_path),
        notify_(notify) {

    }

    virtual void SpecificExecute() {
        char ori_dpi_str[5] = { 0 };
        char cut_dpi_str[5] = { 0 };
        // ����ʱ����Ҫ���ӡ�ػ�״̬
        MC::ErrorCode ec = exception_;
        if (ec != MC::EC_SUCC) {
            Log::WriteLog(LL_MSG, "SnapshotEv::SpecificExecute->����ʱ�豸״̬: %s",
                MC::ErrorMsg[ec].c_str());
        }

        int ret = CapturePhoto(
            PAPERCAMERA,
            enum IMAGEFORMAT(MC::SvrConfig::GetInst()->img_format_),
            (char*)ori_.c_str());
        if (0 != ret) {
            Log::WriteLog(LL_ERROR, "SnapshotEv::SpecificExecute->����ʧ��, er: %d", ret);
            ec = MC::EC_CAPTURE_FAIL;
            goto NT;
        }

        // ��ƫȥ�ڱ�
        ret = MC::CutImage(ori_, cut_);
        if (0 != ret) {
            Log::WriteLog(LL_ERROR, "SnapshotEv::SpecificExecute->��ƫȥ�ڱ�ʧ��, er: %d", ret);
            ec = MC::EC_PROCESS_IMG_FAIL;
            goto NT;
        }

        ec = MC::EC_SUCC;

    NT:
        notify_->Notify(
            ec, 
            _itoa(ori_dpi_, ori_dpi_str, 10),
            _itoa(cut_dpi_, cut_dpi_str, 10), 
            ori_,
            cut_);
        Log::WriteLog(LL_DEBUG, "MC::SnapshotEv::SpecificExecute->����, ec: %s, ԭͼ·��: %s, "
            "��ͼ·��: %s",
            MC::ErrorMsg[ec].c_str(),
            ori_.c_str(), 
            cut_.c_str());
        delete this;
    }

private:
    int ori_dpi_;
    int cut_dpi_;
    std::string ori_;
    std::string cut_;

    MC::NotifyResult* notify_;
};

void MC::BOCApi::Snapshot(
    int original_dpi, 
    int cut_dpi, 
    const std::string& ori_path,
    const std::string& cut_path,
    NotifyResult* notify)
{
    BaseEvent* ev = new (std::nothrow) SnapshotEv(
        "����" + des_, 
        original_dpi, 
        cut_dpi, 
        ori_path,
        cut_path,
        notify);
    if (NULL == ev)
        notify->Notify(MC::EC_ALLOCATE_FAILURE);

    EventCPUCore::GetInstance()->PostEvent(ev);
}

///////////////////////////// ��Ƭ�ϳ� //////////////////////////////////

class MergePhotoEv : public MC::BaseEvent {

public:
    MergePhotoEv(
        std::string des, 
        std::string photo1, 
        std::string photo2, 
        std::string merged,
        MC::NotifyResult* notify)
        : BaseEvent(des),
        photo1_(photo1),
        photo2_(photo2),
        merged_(merged),
        notify_(notify) {

    }

    virtual void SpecificExecute() {
        MC::ErrorCode ec = exception_;
        if (ec != MC::EC_SUCC)
            goto NT;

        // ����-��Ƭ�ϳ�
        int ret = MC::MergeImage(
            photo1_,
            photo2_,
            merged_);
        if (0 != ret) {
            ec = MC::EC_MERGE_FAIL;
            goto NT;
        }

        ec = MC::EC_SUCC;

    NT:
        notify_->Notify(
            ec,
            photo1_,
            photo2_,
            merged_.c_str());
        Log::WriteLog(LL_DEBUG, "MC::MergePhotoEv::SpecificExecute->��Ƭ�ϳ�, ec: %d, �ϳɺ�·��: %s", 
            ec, 
            merged_.c_str());
        delete this;
    }

private:
    std::string photo1_;
    std::string photo2_;
    std::string merged_;

    MC::NotifyResult* notify_;
};

void MC::BOCApi::MergePhoto(
    const std::string& photo1, 
    const std::string& photo2, 
    const std::string& merged,
    NotifyResult* notify)
{
    BaseEvent* ev = new (std::nothrow) MergePhotoEv("��Ƭ�ϳ�" + des_, photo1, photo2, merged, notify);
    if (NULL == ev)
        notify->Notify(MC::EC_ALLOCATE_FAILURE);

    EventCPUCore::GetInstance()->PostEvent(ev);
}

/////////////////////////// ������֤��ʶ�� ////////////////////////////////

class RecognitionEv : public MC::BaseEvent {

public:
    RecognitionEv(std::string des, std::string img, MC::NotifyResult* notify)
        : BaseEvent(des),
        img_(img),
        notify_(notify) {

    }

    virtual void SpecificExecute() {
        std::string voucher_no; // ƾ֤���
        std::string trace_no;   // ׷����
        double angle = 0;
        int x = 0;
        int y = 0;
        std::string model_type;
        std::string out_model_type;
        MC::ErrorCode ec = exception_;
        if (ec != MC::EC_SUCC)
            goto NT;

        // ����-������֤��ʶ��
        // ģ�����͡��Ƕȡ���ӡ��ʶ��
        int ret = MC::GetModelTypeAnglePoint(img_, model_type, angle, x, y);
        if (0 != ret) {
            ec = MC::EC_MODEL_TYPE_FAIL;
            goto NT;
        }

        int out_angle = 0;
        ret = MC::IdentifyImage(
            img_,
            model_type,
            out_model_type,
            voucher_no,
            trace_no,
            x,
            y,
            out_angle);
        if (0 != ret) {
            ec = MC::EC_RECOG_FAIL;
            goto NT;
        }

        ec = MC::EC_SUCC;

    NT:
        notify_->Notify(
            ec,
            img_,
            "",
            voucher_no,
            trace_no);
        Log::WriteLog(LL_DEBUG, "MC::RecognitionEv::SpecificExecute->������֤��ʶ��, ec: %s, "
            "ģ��ID: %s, ׷����: %s", 
            MC::ErrorMsg[ec].c_str(),
            voucher_no.c_str(),
            trace_no.c_str());
        delete this;
    }

private:
    std::string img_;

    MC::NotifyResult* notify_;
};

void MC::BOCApi::RecognizeImage(const std::string& img, NotifyResult* notify)
{
    BaseEvent* ev = new (std::nothrow) RecognitionEv("������֤��ʶ��" + des_, img, notify);
    if (NULL == ev)
        notify->Notify(MC::EC_ALLOCATE_FAILURE);

    EventCPUCore::GetInstance()->PostEvent(ev);
}

///////////////////////// Ҫ��ʶ�� //////////////////////////////////////

class IdentifyEleEv : public MC::BaseEvent {

public:
    IdentifyEleEv(
        std::string des, 
        std::string path, 
        int x, 
        int y, 
        int width,
        int height, 
        int angle, 
        MC::NotifyResult* notify)
        : BaseEvent(des),
        path_(path),
        x_(x),
        y_(y),
        width_(width),
        height_(height),
        angle_(angle),
        notify_(notify) {

    }

    virtual void SpecificExecute() {
        std::string result;
        MC::ErrorCode ec = exception_;
        if (ec != MC::EC_SUCC)
            goto NT;

        // ����-Ҫ��ʶ��
        int ret = MC::IdentifyArea(path_, x_, y_, width_, height_, angle_, result);
        if (0 != ret) {
            ec = MC::EC_ELEMENT_FAIL;
            goto NT;
        }

        ec = MC::EC_SUCC;

    NT:
        notify_->Notify(
            ec,
            path_,
            result);
        Log::WriteLog(LL_DEBUG, "MC::IdentifyEleEv::SpecificExecute->Ҫ��ʶ��, ec: %s, ���: %s",
            MC::ErrorMsg[ec].c_str(),
            result.c_str());
        delete this;
    }

private:
    std::string path_;
    int x_;
    int y_;
    int width_;
    int height_;
    int angle_;

    MC::NotifyResult* notify_;
};

void MC::BOCApi::IdentifyElement(
    const std::string& path,
    int x,
    int y,
    int width,
    int height,
    int angle_,
    NotifyResult* notify)
{
    BaseEvent* ev = new (std::nothrow) IdentifyEleEv(
        "Ҫ��ʶ��" + des_, 
        path, 
        x,
        y,
        width,
        height,
        angle_,
        notify);
    if (NULL == ev)
        notify->Notify(MC::EC_ALLOCATE_FAILURE);

    EventCPUCore::GetInstance()->PostEvent(ev);
}

/////////////////////// ��ͨ��ӡ ////////////////////////////////////////

class OridinaryEv : public MC::BaseEvent {

public:
    OridinaryEv(std::string des, std::string t, std::string v, int num, 
        int x, int y, int angle, MC::NotifyResult* notify): BaseEvent(des), 
        task_(t), 
        voucher_(v), 
        num_(num),
        x_(x),
        y_(y),
        angle_(angle),
        notify_(notify) {

    }

    virtual void SpecificExecute() {
        MC::ErrorCode ec = exception_;
        if (ec != MC::EC_SUCC)
            goto NT;

        // ����-��ͨ��ӡ
        MC::TaskState ts = MC::TaskMgr::GetInst()->QueryTaskState(task_);
        if (ts ==  MC::TS_ALIVE) {
            // ��ԭͼ��ӡ����(����)ת��Ϊ�豸��ӡ����(����)
            MC::Point* ptSeal = MC::GetSealCoord(x_, y_);
            unsigned int rfid;
            int ret = GetStamperID(num_ - 1, rfid);
   
            STAMPERPARAM pa;
            memcpy(&pa.seal, &rfid, sizeof(rfid));
            pa.serial_number = atoi(task_.c_str());
            pa.isPadInk = 1;
            pa.x_point = ptSeal->x;
            pa.y_point = ptSeal->y;
            pa.w_time = MC::SvrConfig::GetInst()->wait_time_;
            pa.angle = 270;
            pa.type = 0;

            Log::WriteLog(LL_DEBUG, "MC::OridinaryEv::SpecificExecute->��ͨ��ӡ, ������ӡ��(%d, %d)",
                ptSeal->x,
                ptSeal->y);
            ret = FStartStamperstrc(&pa);

        } else if (ts == MC::TS_DEAD) {
            ec = MC::EC_TASK_CONSUMED;
            goto NT;
        } else {
            ec = MC::EC_TASK_NON_EXIST;
            goto NT;
        }

        ec = MC::EC_SUCC;

    NT:
        notify_->Notify(ec, task_);
        Log::WriteLog(LL_DEBUG, "OridinaryEv::SpecificExecute->��ͨ��ӡ, ec: %s, �����: %s",
            MC::ErrorMsg[ec].c_str(),
            task_.c_str());
        delete this;
    }

private:
    std::string task_;
    std::string voucher_;
    int         num_;
    int         x_;         // ����λ��x����, ԭʼͼƬ�е�����
    int         y_;
    int         angle_;

    MC::NotifyResult* notify_;
};

void MC::BOCApi::OrdinaryStamp(
    const std::string& task,
    const std::string& voucher,
    int num, 
    int x, 
    int y, 
    int angle,
    NotifyResult* notify)
{
    BaseEvent* ev = new (std::nothrow) OridinaryEv(
        "��ͨ��ӡ" + des_,
        task,
        voucher,
        num, 
        x,
        y,
        angle,
        notify);
    if (NULL == ev)
        notify->Notify(MC::EC_ALLOCATE_FAILURE);

    EventCPUCore::GetInstance()->PostEvent(ev);
}

//////////////////////// �Զ���ӡ ////////////////////////////////////////

class AutoEv : public MC::BaseEvent {
public:
    AutoEv(std::string des, std::string t, std::string v, int num, MC::NotifyResult* notify) :
        BaseEvent(des), task_(t), voucher_(v), num_(num), notify_(notify) {

    }

    virtual void SpecificExecute() {
        MC::ErrorCode ec = exception_;
        if (ec != MC::EC_SUCC)
            goto NT;

        // ����-�Զ���ӡ
        MC::TaskState ts = MC::TaskMgr::GetInst()->QueryTaskState(task_);
        if (ts == MC::TS_ALIVE) {
            // to-do �Զ���ӡ



        }
        else if (ts == MC::TS_DEAD) {
            ec = MC::EC_TASK_CONSUMED;
            goto NT;
        }
        else {
            ec = MC::EC_TASK_NON_EXIST;
            goto NT;
        }

        ec = MC::EC_SUCC;
        
    NT:
        notify_->Notify(ec, task_);
        Log::WriteLog(LL_DEBUG, "MC::AutoEv::SpecificExecute->�Զ���ӡ, ec: %s, �����: %s",
            MC::ErrorMsg[ec].c_str(),
            task_.c_str());
        delete this;
    }

private:
    std::string task_;
    std::string voucher_;
    int         num_;

    MC::NotifyResult* notify_;
};

void MC::BOCApi::AutoStamp(const std::string& task,
    const std::string& voucher, int num, NotifyResult* notify)
{
    BaseEvent* ev = new (std::nothrow) AutoEv(
        "�Զ���ӡ" + des_,
        task,
        voucher,
        num,
        notify);
    if (NULL == ev)
        notify->Notify(MC::EC_ALLOCATE_FAILURE);

    EventCPUCore::GetInstance()->PostEvent(ev);
}

/////////////////////////// ��ӡ���� /////////////////////////////////////

class FinishEv : public MC::BaseEvent {
public:
    FinishEv(std::string des, std::string t, MC::NotifyResult* notify) :
        BaseEvent(des),
        task_(t), 
        notify_(notify) {

    }

    virtual void SpecificExecute() {
        MC::ErrorCode ec = exception_;
        if (ec != MC::EC_SUCC)
            goto NT;

        // ����-��ӡ����
        MC::TaskState ts = MC::TaskMgr::GetInst()->QueryTaskState(task_);
        // ������ѱ�����
        if (MC::TS_DEAD == ts) {
            ec = MC::EC_TASK_CONSUMED;
            goto NT;
        }

        // ����Ų�����
        if (MC::TS_NON_EXIST == ts) {
            ec = MC::EC_TASK_NON_EXIST;
            goto NT;
        }

        // ɾ�������
        if (!MC::TaskMgr::GetInst()->RemoveTask(task_))
            Log::WriteLog(LL_ERROR, "FinishEv::SpecificExecute->ɾ�������%sʧ��", task_.c_str());

        // ����ֽ��
        int ret = FOpenDoorPaper();
        if (0 != ret) {
            ec = MC::EC_DRIVER_FAIL;
            goto NT;
        }
        
        ec = MC::EC_SUCC;

    NT:
        notify_->Notify(ec, task_);
        Log::WriteLog(LL_DEBUG, "MC::FinishEv::SpecificExecute->��ӡ����, ec: %s, �����: %s", 
            MC::ErrorMsg[ec].c_str(),
            task_.c_str());
        delete this;
    }

private:
    std::string task_;

    MC::NotifyResult* notify_;
};

void MC::BOCApi::FinishStamp(const std::string& task, NotifyResult* notify)
{
    BaseEvent* ev = new (std::nothrow) FinishEv(
        "��ӡ����" + des_,
        task,
        notify);
    if (NULL == ev)
        notify->Notify(MC::EC_ALLOCATE_FAILURE);

    EventCPUCore::GetInstance()->PostEvent(ev);
}

/////////////////////////// �ͷ�ӡ�ػ� //////////////////////////////////

class ReleaseEv : public MC::BaseEvent {
public:
    ReleaseEv(std::string des, std::string machine, MC::NotifyResult* notify) : BaseEvent(des),
        machine_(machine), notify_(notify) {

    }

    virtual void SpecificExecute() {
        MC::ErrorCode ec = exception_;
        if (ec != MC::EC_SUCC)
            goto NT;

        // ����-�ͷ�ӡ�ػ�
        // �Ƿ�����
        if (!IsLocked()) {
            ec = MC::EC_MACHINE_UNLOCKED;
            goto NT;
        }

        // �����������ӡ�ػ�
        int ret = Unlock();
        if (0 != ret) {
            ec = MC::EC_DRIVER_FAIL;
            goto NT;
        }

        ec = MC::EC_SUCC;

    NT:
        notify_->Notify(ec, machine_);
        Log::WriteLog(LL_DEBUG, "MC::ReleaseEv::SpecificExecute->�ͷ�ӡ�ػ�, ec: %s", 
            MC::ErrorMsg[ec].c_str());
        delete this;
    }

private:
    std::string machine_;

    MC::NotifyResult* notify_;
};

void MC::BOCApi::ReleaseStamp(const std::string& machine, NotifyResult* notify)
{
    BaseEvent* ev = new (std::nothrow) ReleaseEv(
        "�ͷ�ӡ�ػ�" + des_,
        machine,
        notify);
    if (NULL == ev)
        notify->Notify(MC::EC_ALLOCATE_FAILURE);

    EventCPUCore::GetInstance()->PostEvent(ev);
}

//////////////////////////// ��ȡ������Ϣ /////////////////////////////////

class GetErrEv : public MC::BaseEvent {
public:
    GetErrEv(std::string des, int err, MC::NotifyResult* notify) : BaseEvent(des),
        err_(err), notify_(notify) {

    }

    virtual void SpecificExecute() {
        char err_code_str[64] = { 0 };
        std::string msg;
        std::string resolver;
        MC::ErrorCode ec = exception_;
        if (ec != MC::EC_SUCC)
            goto NT;

        if (err_ < 0 || err_ > MC::EC_MAX) {
            msg = "δ����Ĵ�����";
            goto NT;
        }

        // ����-��ȡ������Ϣ
        msg = MC::GetErrMsg((MC::ErrorCode)err_);
        resolver = MC::GetErrResolver((MC::ErrorCode)err_);
        ec = MC::EC_SUCC;

    NT:
        notify_->Notify(ec, msg, resolver, _itoa(err_, err_code_str, 10));
        Log::WriteLog(LL_DEBUG, "MC::GetErrEv::SpecificExecute->��ȡ������Ϣ: ec: %s, ������: %d, "
            "��������: %s, �������: %s", 
            MC::ErrorMsg[ec].c_str(),
            err_, 
            msg.c_str(),
            resolver.c_str());
        delete this;
    }

private:
    int err_;   // ������

    MC::NotifyResult* notify_;
};

void MC::BOCApi::GetError(int err_code, NotifyResult* notify)
{
    BaseEvent* ev = new (std::nothrow) GetErrEv(
        "��ȡ������Ϣ" + des_,
        err_code,
        notify);
    if (NULL == ev)
        notify->Notify(MC::EC_ALLOCATE_FAILURE);

    EventCPUCore::GetInstance()->PostEvent(ev);
}

//////////////////////////////// У׼ӡ�� //////////////////////////////

class CaliStamperEv : public MC::BaseEvent {
public:
    CaliStamperEv(std::string des, int num, MC::NotifyResult* notify) : BaseEvent(des),
        num_(num), notify_(notify) {

    }

    virtual void SpecificExecute() {
        MC::ErrorCode ec = exception_;
        if (ec != MC::EC_SUCC)
            goto NT;

        // ����-У׼ӡ��
        unsigned int rfid = 0;
        int ret = GetStamperID(num_ - 1, rfid);
        if (0 != ret) {
            ec = MC::EC_DRIVER_FAIL;
            goto NT;
        }

        ret = CalibrationEx((char*)&rfid, NULL, 0);
        if (0 != ret) {
            ec = MC::EC_DRIVER_FAIL;
            goto NT;
        }

        ec = MC::EC_SUCC;

    NT:
        notify_->Notify(ec);
        Log::WriteLog(LL_DEBUG, "MC::CaliStamperEv::SpecificExecute->У׼ӡ��, ec: %s", 
            MC::ErrorMsg[ec].c_str());
        delete this;
    }

private:
    int num_;   // ӡ�¿��ۺ�

    MC::NotifyResult* notify_;
};

void MC::BOCApi::CalibrateMachine(int num, NotifyResult* notify)
{
    BaseEvent* ev = new (std::nothrow) CaliStamperEv(
        "У׼ӡ��" + des_,
        num,
        notify);
    if (NULL == ev)
        notify->Notify(MC::EC_ALLOCATE_FAILURE);

    EventCPUCore::GetInstance()->PostEvent(ev);
}

///////////////////////// ӡ��״̬��ѯ /////////////////////////////////////

class QueryStampersEv : public MC::BaseEvent{
public:
    QueryStampersEv(std::string des, MC::NotifyResult* notify) : 
        BaseEvent(des),
        notify_(notify) {

    }

    virtual void SpecificExecute() {
        char stampers_sta[7] = { 0 };
        MC::ErrorCode ec = exception_;
        if (ec != MC::EC_SUCC)
            goto NT;

        // ����-ӡ��״̬��ѯ
        unsigned int rfids[7] = { 0 };
        unsigned char stampers = 0;
        int ret = ReadAllRFID(rfids, 7, &stampers);
        if (0 != ret) {
            ec = MC::EC_DRIVER_FAIL;
            goto NT;
        }

        for (int i = 0; i < 6; ++i) {
            if (rfids[i] == 0)
                stampers_sta[i] = 0x30;
            else if (rfids[i] != 0)
                stampers_sta[i] = 0x31;
        }

        ec = MC::EC_SUCC;

    NT:
        notify_->Notify(ec, stampers_sta);
        Log::WriteLog(LL_DEBUG, "QueryStampersEv::SpecificExecute->ӡ��״̬��ѯ, ec: %s", 
            MC::ErrorMsg[ec].c_str());
        delete this;
    }

private:
    MC::NotifyResult* notify_;
};

void MC::BOCApi::QueryStampers(NotifyResult* notify)
{
    BaseEvent* ev = new (std::nothrow) QueryStampersEv(
        "ӡ��״̬��ѯ" + des_,
        notify);
    if (NULL == ev)
        notify->Notify(MC::EC_ALLOCATE_FAILURE);

    EventCPUCore::GetInstance()->PostEvent(ev);
}

////////////////////////// ��ȫ��״̬��ѯ ////////////////////////////////////

class QuerySafeEv : public MC::BaseEvent {
public:
    QuerySafeEv(std::string des, MC::NotifyResult* notify) :
        BaseEvent(des),
        notify_(notify) {

    }

    virtual void SpecificExecute() {
        char safe_str[5] = { 0 };
        MC::ErrorCode ec = exception_;
        if (ec != MC::EC_SUCC)
            goto NT;

        // ����-��ȫ��״̬��ѯ
        char doors[4] = { 0 };
        int ret = FGetDoorsPresent(doors, sizeof(doors));
        if (0 != ret) {
            ec = MC::EC_DRIVER_FAIL;
            goto NT;
        }

        sprintf_s(safe_str, "%d", doors[1]);
        ec = MC::EC_SUCC;

    NT:
        notify_->Notify(ec, safe_str);
        Log::WriteLog(LL_DEBUG, "MC::QuerySafeEv::SpecificExecute->��ȫ��״̬��ѯ, ec: %s, ��ȫ��״̬: %s",
            MC::ErrorMsg[ec].c_str(),
            safe_str);
        delete this;
    }

private:
    MC::NotifyResult* notify_;
};

void MC::BOCApi::QuerySafeDoor(NotifyResult* notify)
{
    BaseEvent* ev = new (std::nothrow) QuerySafeEv(
        "��ȫ��״̬��ѯ" + des_,
        notify);
    if (NULL == ev)
        notify->Notify(MC::EC_ALLOCATE_FAILURE);

    EventCPUCore::GetInstance()->PostEvent(ev);
}

/////////////////////// ���ذ�ȫ�� /////////////////////////////////////

class OperateSafeEv : public MC::BaseEvent {
public:
    OperateSafeEv(std::string des, int operation, int timeout, MC::NotifyResult* notify) :
        BaseEvent(des),
        operation_(operation),
        timeout_(timeout),
        notify_(notify) {

    }

    virtual void SpecificExecute() {
        char ctrl_str[5] = { 0 };
        char timeout_str[5] = { 0 };
        MC::ErrorCode ec = exception_;
        if (ec != MC::EC_SUCC)
            goto NT;

        // ����-���ذ�ȫ��
        //0x0B, ��ȡ��״̬(len = 4)
        //P1:   ��ֽ��״̬  0 �رգ�1 ������ 2������
        //P2:   ������״̬��ͬ��
        //P3:   ��е��״̬��ͬ��
        //P4:   ����״̬��ͬ��
        char doors[4] = { 0 };
        int ret = FGetDoorsPresent(doors, sizeof(doors));
        if (0 != ret) {
            ec = MC::EC_DRIVER_FAIL;
            goto NT;
        }
        
        switch (operation_) {
        case 0: { // �ذ�ȫ��
            if (doors[1] == 0) {
                ec = MC::EC_SAFE_CLOSED;
                goto NT;
            }

            // �˳�ά��ģʽ
            ret = FQuitMaintainMode();
            if (0 != ret) {
                ec = MC::EC_DRIVER_FAIL;
                goto NT;
            }

            ret = FCloseDoorSafe();
            if (0 != ret) {
                ec = MC::EC_DRIVER_FAIL;
                goto NT;
            }
        }
            break;
        case 1: { // ����ȫ��
            if (doors[1] == 1) {
                ec = MC::EC_SAFE_OPENED;
                goto NT;
            }

            // ����ά��ģʽ
            ret = FMaintenanceMode();
            if (0 != ret) {
                ec = MC::EC_DRIVER_FAIL;
                goto NT;
            }

            ret = FOpenDoorSafe();
            if (0 != ret) {
                ec = MC::EC_DRIVER_FAIL;
                goto NT;
            }
        }
            break;
        default:
            break;
        }

        ec = MC::EC_SUCC;

    NT:
        sprintf_s(ctrl_str, "%d", operation_);
        sprintf_s(timeout_str, "%d", timeout_);
        notify_->Notify(ec, ctrl_str, timeout_str);
        Log::WriteLog(LL_DEBUG, "MC::OperateSafeEv::SpecificExecute->���ذ�ȫ��, ec: %s", 
            MC::ErrorMsg[ec].c_str());
        delete this;
    }

private:
    int operation_;
    int timeout_;

    MC::NotifyResult* notify_;
};

void MC::BOCApi::OperateSafeDoor(int operation, int timeout, NotifyResult* notify)
{
    BaseEvent* ev = new (std::nothrow) OperateSafeEv(
        "���ذ�ȫ��" + des_,
        operation,
        timeout,
        notify);
    if (NULL == ev)
        notify->Notify(MC::EC_ALLOCATE_FAILURE);

    EventCPUCore::GetInstance()->PostEvent(ev);
}

////////////////////// ���������� ///////////////////////////////////////

class OperateBeepEv : public MC::BaseEvent {
public:
    OperateBeepEv(std::string des, int operation, MC::NotifyResult* notify) :
        BaseEvent(des),
        operation_(operation),
        notify_(notify) {

    }

    virtual void SpecificExecute() {
        MC::ErrorCode ec = exception_;
        if (ec != MC::EC_SUCC)
            goto NT;

        // ����-����������
        //0x16, ����������
        //beep      --- 0 �ر�; 1 ����; 2 �����
        //interval  --- ��beep=2ʱ��ֵ��Ч, �����ʱ��(��λ��)
        int ret = FBeepCtrl(operation_, 0);
        if (0 != ret) {
            ec = MC::EC_DRIVER_FAIL;
            goto NT;
        }

        ec = MC::EC_SUCC;

    NT:
        notify_->Notify(ec);
        Log::WriteLog(LL_DEBUG, "MC::OperateBeepEv::SpecificExecute->����������, ec: %s", 
            MC::ErrorMsg[ec].c_str());
        delete this;
    }

private:
    int operation_;

    MC::NotifyResult* notify_;
};

void MC::BOCApi::OperateBeep(int operation, NotifyResult* notify)
{
    BaseEvent* ev = new (std::nothrow) OperateBeepEv(
        "���ذ�ȫ��" + des_,
        operation,
        notify);
    if (NULL == ev)
        notify->Notify(MC::EC_ALLOCATE_FAILURE);

    EventCPUCore::GetInstance()->PostEvent(ev);
}

/////////////////////// ����������ѯ ///////////////////////////////////

class QuerySlotEv : public MC::BaseEvent {
public:
    QuerySlotEv(std::string des, MC::NotifyResult* notify) :
        BaseEvent(des),
        notify_(notify) {

    }

    virtual void SpecificExecute() {
        char slots_str[4] = { 0 };
        MC::ErrorCode ec = exception_;
        if (ec != MC::EC_SUCC)
            goto NT;

        // ����-����������ѯ
        unsigned int rfids[7] = { 0 };
        unsigned char stampers = 0;
        int ret = ReadAllRFID(rfids, 7, &stampers);
        if (0 != ret) {
            ec = MC::EC_DRIVER_FAIL;
            goto NT;
        }

        sprintf_s(slots_str, "%d", stampers);
        ec = MC::EC_SUCC;

    NT:
        notify_->Notify(ec, slots_str);
        Log::WriteLog(LL_DEBUG, "MC::QuerySlotEv::SpecificExecute->����������ѯ, ec: %s, ������: %s",
            MC::ErrorMsg[ec].c_str(),
            slots_str);
        delete this;
    }

private:
    MC::NotifyResult* notify_;
};

void MC::BOCApi::QuerySlot(NotifyResult* notify)
{
    BaseEvent* ev = new (std::nothrow) QuerySlotEv(
        "����������ѯ" + des_,
        notify);
    if (NULL == ev)
        notify->Notify(MC::EC_ALLOCATE_FAILURE);

    EventCPUCore::GetInstance()->PostEvent(ev);
}

/////////////////////////// ���������� //////////////////////////////////

class AlarmCtrlEv : public MC::BaseEvent {
public:
    AlarmCtrlEv(std::string des, int alarm, int ctrl, MC::NotifyResult* notify) :
        BaseEvent(des),
        alarm_(alarm),
        ctrl_(ctrl),
        notify_(notify) {

    }

    virtual void SpecificExecute() {
        char alarm_str[5] = { 0 };
        char ctrl_str[5] = { 0 };
        MC::ErrorCode ec = exception_;
        if (ec != MC::EC_SUCC)
            goto NT;

        // ����-����������
        //alarm     --- 0(���ű�����)
        //              1(�񶯱�����)
        //switchs   --- ����������
        //              1(����);
        //              0(�ر�)
        int ret = SetAlarm(alarm_, ctrl_);
        if (0 != ret) {
            ec = MC::EC_DRIVER_FAIL;
            goto NT;
        }

        sprintf_s(alarm_str, "%d", alarm_);
        sprintf_s(ctrl_str, "%d", ctrl_);
        ec = MC::EC_SUCC;

    NT:
        notify_->Notify(ec, alarm_str, ctrl_str);
        Log::WriteLog(LL_DEBUG, "MC::QuerySlotEv::SpecificExecute->����������, ec: %s, ����������: %s, "
            "����: %s",
            MC::ErrorMsg[ec].c_str(),
            alarm_str,
            ctrl_str);
        delete this;
    }

private:
    int                 alarm_;
    int                 ctrl_;
    MC::NotifyResult*   notify_;
};

void MC::BOCApi::OperateAlarm(int alarm, int ctrl, MC::NotifyResult* notify)
{
    BaseEvent* ev = new (std::nothrow) AlarmCtrlEv(
        "����������" + des_,
        alarm,
        ctrl,
        notify);
    if (NULL == ev)
        notify->Notify(MC::EC_ALLOCATE_FAILURE);

    EventCPUCore::GetInstance()->PostEvent(ev);
}

////////////////////////// ��ѯ�Ѱ�MAC��ַ //////////////////////////////////

class QueryMACEv : public MC::BaseEvent {
public:
    QueryMACEv(std::string des, MC::NotifyResult* notify) :
        BaseEvent(des),
        notify_(notify) {

    }

    virtual void SpecificExecute() {
        unsigned char mac1[24] = { 0 };
        unsigned char mac2[24] = { 0 };
        MC::ErrorCode ec = exception_;
        if (MC::EC_SUCC != ec)
            goto NT;

        // ����-��ѯMAC��ַ
        int ret = ReadMAC(mac1, mac2, 18);
        if (0 != ret) {
            ec = MC::EC_DRIVER_FAIL;
            goto NT;
        }

        ec = MC::EC_SUCC;

    NT:
        notify_->Notify(ec, (char*)mac1, (char*)mac2);
        Log::WriteLog(LL_DEBUG, "MC::QueryMACEv::SpecificExecute->��ѯMAC��ַ, ec: %s, MAC1: %s, "
            "MAC2: %s",
            MC::ErrorMsg[ec].c_str(),
            mac1,
            mac2);
        delete this;
    }

private:
    MC::NotifyResult*   notify_;
};

void MC::BOCApi::QueryMAC(NotifyResult* notify)
{
    BaseEvent* ev = new (std::nothrow) QueryMACEv(
        "��ѯ�Ѱ�MAC��ַ" + des_,
        notify);
    if (NULL == ev)
        notify->Notify(MC::EC_ALLOCATE_FAILURE);

    EventCPUCore::GetInstance()->PostEvent(ev);
}

//////////////////////////////////////////////////////////////////////////
