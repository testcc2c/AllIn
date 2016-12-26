#ifndef AGENT_CMD_H_
#define AGENT_CMD_H_

#include <string>
#include <windows.h>
#include <boost/uuid/uuid.hpp>            // uuid class
#include <boost/uuid/uuid_generators.hpp> // generators
#include <boost/uuid/uuid_io.hpp>         // streaming operators etc.
#include <boost/lexical_cast.hpp>
#include "common_definitions.h"
#include "seria.h"

#define TASK_ID_SIZE        48
#define VOUCHER_TYPE_SIZE   16
#define KEY_SIZE            64
#define MAC_SIZE            64
#define ERROR_SIZE          64
#define SEND_TIME_SIZE      37  // null terminated.
#define SN_SIZE             30
#define MAX_STAMPER_NUM     6

enum CmdType {
    CT_INIT_MACHINE = 1,    // ��ʼ��
    CT_BIND_MAC,            // ��MAC
    CT_UNBIND_MAC,          // ���MAC
    CT_PREPARE_STAMP,       // ׼����ӡ
    CT_PAPER_DOOR,          // ��ѯ��ֽ��״̬
    CT_SNAPSHOT,            // ����
    CT_PHOTO_SYNTHESIS,     // ��Ƭ�ϳ�
    CT_RECOGNITION,         // ������֤��ʶ��
    CT_ELEMENT_IDENTI,      // Ҫ��ʶ��
    CT_ORDINARY_STAMP,      // ��ͨ��ӡ
    CT_AUTO_STAMP,          // �Զ���ӡ
    CT_FINISH_STAMP,        // ������ӡ
    CT_RELEASE_STAMPER,     // �ͷ���ӡ��
    CT_GET_ERROR,           // ��ȡ������Ϣ
    CT_HEART_BEAT,          // ��������
    CT_QUERY_MACHINE,       // ��ȡӡ�ػ����
    CT_SET_MACHINE,         // ����ӡ�ػ����
    CT_CALIBRATION,         // У׼ӡ��
    CT_QUERY_STAMPERS,      // ӡ��״̬��ѯ
    CT_QUERY_SAFE,          // ��ȫ��״̬��ѯ
    CT_SAFE_CTL,            // ���ذ�ȫ��
    CT_BEEP_CTL,            // ����������
    CT_QUERY_SLOT,          // ����������ѯ
    CT_ALARM_CTL,           // ����������
    CT_QUERY_MAC,           // ��ѯ�Ѱ�MAC��ַ
};

static std::string cmd_des[] = 
{
    "����", 
    "��ʼ��ӡ�ػ�", 
    "��MAC", 
    "���MAC",
    "׼����ӡ",
    "��ѯ��ֽ��״̬",
    "����",
    "��Ƭ�ϳ�",
    "������֤��ʶ��",
    "Ҫ��ʶ��",
    "��ͨ��ӡ",
    "�Զ���ӡ",
    "������ӡ",
    "�ͷ���ӡ��",
    "��ȡ������Ϣ",
    "��������",
    "��ȡӡ�ػ����",
    "����ӡ�ػ����",
    "У׼ӡ��",
    "ӡ��״̬��ѯ",
    "��ȫ��״̬��ѯ",
    "���ذ�ȫ��",
    "����������",
    "����������ѯ",
    "����������",
    "��ѯ�Ѱ�MAC��ַ"
};

class BaseCmd {
public:
    BaseCmd() {
        boost::uuids::uuid uuid = boost::uuids::random_generator()();
        std::string uuid_str = boost::lexical_cast<std::string>(uuid);
        strcpy(send_time_, uuid_str.c_str());
    }

    virtual void Ser();
    virtual void Unser();

public:
    enum        CmdType ct_;               //�������ݳ�Ա����ct_��, ���л�ʱҲ�������к�ct_
    char        send_time_[SEND_TIME_SIZE];
    XSpace      xs_;
};

class InitMachineCmd : public BaseCmd {
public:
    InitMachineCmd(): ret_(MC::EC_SUCC)
    {
        ct_ = CT_INIT_MACHINE;
        memset(key_, 0, KEY_SIZE);
    }

    virtual void Ser();
    virtual void Unser();

public:
    char            key_[KEY_SIZE];
    MC::ErrorCode   ret_;
};

class BindMACCmd : public BaseCmd {
public:
    BindMACCmd() : ret_(MC::EC_SUCC)
    {
        ct_ = CT_BIND_MAC;
        memset(mac_, 0, MAC_SIZE);
    }

    virtual void Ser();
    virtual void Unser();

public:
    char            mac_[MAC_SIZE];
    MC::ErrorCode   ret_;
};

class UnbindCmd : public BaseCmd {
public:
    UnbindCmd() : ret_(MC::EC_SUCC)
    {
        ct_ = CT_UNBIND_MAC;
        memset(mac_, 0, MAC_SIZE);
    }

    virtual void Ser();
    virtual void Unser();

public:
    char            mac_[MAC_SIZE];
    MC::ErrorCode   ret_;
};

class PrepareStampCmd : public BaseCmd {
public:
    PrepareStampCmd() : ret_(MC::EC_SUCC), stamper_id_(-1), timeout_(0) {
        ct_ = CT_PREPARE_STAMP;
        memset(task_id_, 0x0, TASK_ID_SIZE);
    }

    virtual void Ser();
    virtual void Unser();

public:
    char            stamper_id_;                //ӡ�¿��۱��(1-6)
    int             timeout_;                   //��ʱʱ��, ��λ: ��
    char            task_id_[TASK_ID_SIZE];     //��ӡ����ID
    MC::ErrorCode ret_;
};

class ViewPaperCmd : public BaseCmd {
public:
    ViewPaperCmd() : ret_(MC::EC_SUCC), status_(-1) {
        ct_ = CT_PAPER_DOOR;
    }

    virtual void Ser();
    virtual void Unser();

public:
    int             status_;            //��ֽ��״̬, 0-��, 1-��, -1--δ��ȡ����ֽ��״̬
    MC::ErrorCode   ret_;
};

class SnapshotCmd : public BaseCmd {
public:
    SnapshotCmd() : ret_(MC::EC_SUCC) {
        ct_ = CT_SNAPSHOT;
    }

    virtual void Ser();
    virtual void Unser();

public:
    int             original_dpi_;              // ���յķֱ���
    int             cut_dpi_;

    char            original_path_[MAX_PATH];  // ����ԭʼͼ��·��
    char            cut_path_[MAX_PATH];       // ���о�ƫ��ͼ��·��

    MC::ErrorCode   ret_;
};

class SynthesizePhotoCmd : public BaseCmd {
public:
    SynthesizePhotoCmd() : ret_(MC::EC_SUCC) {
        ct_ = CT_PHOTO_SYNTHESIS;
    }

    virtual void Ser();
    virtual void Unser();

public:
    char            photo1_[MAX_PATH];
    char            photo2_[MAX_PATH];
    char            merged_[MAX_PATH];

    MC::ErrorCode   ret_;
};

class RecognitionCmd : public BaseCmd {
public:
    RecognitionCmd() : ret_(MC::EC_SUCC) {
        ct_ = CT_RECOGNITION;
    }

    virtual void Ser();
    virtual void Unser();

public:
    char            path_[MAX_PATH];       // ��ʶ��ͼƬ·��

    char            template_id_[4];       // ģ��ID
    char            trace_num_[20];        // ʶ�������֤��

    MC::ErrorCode   ret_;
};

class IdentifyElementCmd : public BaseCmd {
public:
    IdentifyElementCmd() : ret_(MC::EC_SUCC) {
        ct_ = CT_ELEMENT_IDENTI;
    }

    virtual void Ser();
    virtual void Unser();

public:
    char            path_[MAX_PATH];        // ͼƬ·��
    int             x_;                     // ʶ����������x(����)
    int             y_;                     // ʶ����������y(����)
    int             width_;                 // ʶ��������(����)
    int             height_;                // ʶ������߶�(����)
    int             angle_;                 // ��ת�Ƕ�(0, 90, 180, 270)

    char            content_str_[64];       // ʶ����

    MC::ErrorCode   ret_;
};

class OridinaryStampCmd : public BaseCmd {
public:
    OridinaryStampCmd() : ret_(MC::EC_SUCC), stamper_num_(-1),
        x_(-1), y_(-1), angle_(0) {
        ct_ = CT_ORDINARY_STAMP;
    }

    virtual void Ser();
    virtual void Unser();

public:
    char            task_id_[TASK_ID_SIZE];    // ����ID
    char            type_[VOUCHER_TYPE_SIZE];  // ƾ֤����
    int             stamper_num_;               // ӡ�¿��ۺ�
    int             x_;                         // ӡ��λ��X(����)
    int             y_;                         // ӡ��λ��Y(����)
    int             angle_;                     // ����ת�Ƕ�(˳ʱ��: 0, 90, 180, 270)

    MC::ErrorCode   ret_;
};

class AutoStampCmd : public BaseCmd {
public:
    AutoStampCmd() : ret_(MC::EC_SUCC), stamper_num_(-1) {
        ct_ = CT_AUTO_STAMP;
    }

    virtual void Ser();
    virtual void Unser();

public:
    char            task_id_[TASK_ID_SIZE];    // ����ID
    char            type_[VOUCHER_TYPE_SIZE];  // ƾ֤����
    int             stamper_num_;              // ӡ�¿��ۺ�

    MC::ErrorCode   ret_;
};

class FinishStampCmd : public BaseCmd {
public:
    FinishStampCmd() : ret_(MC::EC_SUCC) {
        ct_ = CT_FINISH_STAMP;
    }

    virtual void Ser();
    virtual void Unser();

public:
    char            task_id_[TASK_ID_SIZE];    // ����ID
    MC::ErrorCode   ret_;
};

class ReleaseStamperCmd : public BaseCmd {
public:
    ReleaseStamperCmd() : ret_(MC::EC_SUCC) {
        ct_ = CT_RELEASE_STAMPER;
    }

    virtual void Ser();
    virtual void Unser();

public:
    char            stamp_id_[KEY_SIZE];       // ��ӡ��Ψһ���
    MC::ErrorCode   ret_;
};

class GetErrorCmd : public BaseCmd {
public:
    GetErrorCmd() : ret_(MC::EC_SUCC) {
        ct_ = CT_GET_ERROR;
    }

    virtual void Ser();
    virtual void Unser();

public:
    int             err_;
    char            err_msg_[ERROR_SIZE];
    char            err_resolver_[ERROR_SIZE];

    MC::ErrorCode   ret_;
};

class HeartCmd : public BaseCmd {
public:
    HeartCmd(): ret_(MC::EC_SUCC) {
        ct_ = CT_HEART_BEAT;
    }

    HeartCmd(char* buf) {
        memcpy(xs_.buf_, buf, CMD_BUF_SIZE);
    }

    virtual void Ser();
    virtual void Unser();

public:
    MC::ErrorCode ret_;
};

class QueryMachineCmd : public BaseCmd {
public:
    QueryMachineCmd() : ret_(MC::EC_SUCC) {
        ct_ = CT_QUERY_MACHINE;
        memset(sn_, 0x0, SN_SIZE);
    }

    virtual void Ser();
    virtual void Unser();

public:
    char            sn_[SN_SIZE];
    MC::ErrorCode   ret_;
};

class SetMachineCmd : public BaseCmd {
public:
    SetMachineCmd() : ret_(MC::EC_SUCC) {
        ct_ = CT_SET_MACHINE;
//        memset(sn_, 0x0, SN_SIZE);
    }

    virtual void Ser();
    virtual void Unser();

public:
    char            sn_[SN_SIZE];
    MC::ErrorCode   ret_;
};

class CalibrateCmd : public BaseCmd {
public:
    CalibrateCmd() : ret_(MC::EC_SUCC), slot_(-1) {
        ct_ = CT_CALIBRATION;
    }

    virtual void Ser();
    virtual void Unser();

public:
    int             slot_;      // ӡ�º�
    MC::ErrorCode   ret_;
};

class QueryStampersCmd : public BaseCmd {
public:
    QueryStampersCmd() : ret_(MC::EC_SUCC) {
        ct_ = CT_QUERY_STAMPERS;
        memset(stamper_status_, 0x0, sizeof(int) * MAX_STAMPER_NUM);
    }

    virtual void Ser();
    virtual void Unser();

public:
    int             stamper_status_[MAX_STAMPER_NUM];
    MC::ErrorCode   ret_;
};

class QuerySafeCmd : public BaseCmd {
public:
    QuerySafeCmd() : ret_(MC::EC_SUCC), status_(-1) {
        ct_ = CT_QUERY_SAFE;
    }

    virtual void Ser();
    virtual void Unser();

public:
    int             status_;      // 0-��, 1-��
    MC::ErrorCode   ret_;
};

class SafeCtrlCmd : public BaseCmd {
public:
    SafeCtrlCmd() : ret_(MC::EC_SUCC), ctrl_(-1), timeout_(0) {
        ct_ = CT_SAFE_CTL;
    }

    virtual void Ser();
    virtual void Unser();

public:
    int             ctrl_;      // 0-��, 1-��
    int             timeout_;   // ��ʱδ�ر�ʱ��, ��λ: ��
    MC::ErrorCode   ret_;
};

class BeepCtrlCmd : public BaseCmd {
public:
    BeepCtrlCmd(): ret_(MC::EC_SUCC), ctrl_(-1) {
        ct_ = CT_BEEP_CTL;
    }

    virtual void Ser();
    virtual void Unser();

public:
    int             ctrl_;      // 0-��, 1-��
    MC::ErrorCode   ret_;
};

class QuerySlotCmd : public BaseCmd {
public:
    QuerySlotCmd() : ret_(MC::EC_SUCC), num_(0) {
        ct_ = CT_QUERY_SLOT;
    }

    virtual void Ser();
    virtual void Unser();

public:
    int             num_;
    MC::ErrorCode   ret_;
};

class AlarmCtrlCmd : public BaseCmd {
public:
    AlarmCtrlCmd() : ret_(MC::EC_SUCC), alarm_(-1), ctrl_(-1) {
        ct_ = CT_ALARM_CTL;
    }

    virtual void Ser();
    virtual void Unser();

public:
    int             alarm_; // ����������, 0-���ű���, 1-�񶯱���
    int             ctrl_;  // ���ƿ���, 0-��, 1-��
    MC::ErrorCode   ret_;
};

class QueryMACCmd : public BaseCmd {
public:
    QueryMACCmd() : ret_(MC::EC_SUCC) {
        ct_ = CT_QUERY_MAC;
        memset(mac1_, 0, MAC_SIZE);
        memset(mac2_, 0, MAC_SIZE);
    }

    virtual void Ser();
    virtual void Unser();

public:
    char mac1_[MAC_SIZE];
    char mac2_[MAC_SIZE];

    MC::ErrorCode ret_;
};

#endif // AGENT_CMD_H_
