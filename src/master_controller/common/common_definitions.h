#ifndef CONTROLLER_COMMON_DEFINITIONS_H_
#define CONTROLLER_COMMON_DEFINITIONS_H_

#include <string>
#include "err_code.h"

#define PIPE_MAX_BUF    4096
#define PIPE_BUSY_WAIT  2000
#define CMD_BUF_SIZE    1024

namespace MC {

enum ConnType {
    CT_PIPE,
    CT_MQ,
    CT_MAX
};

enum ConnStatus {
    CS_FREE         = 0,    // �ɹ����豸������
    CS_OPEN_FAIL    = 1,    // ���豸ʧ��
    CS_CLOSE_SUC    = 2,    // �ɹ��ر��豸
    CS_CLOSE_FAIL   = 3,    // �ر��豸ʧ��
    CS_RECON_SUC    = 4,    // �����豸�ɹ�
    CS_RECON_FAIL   = 5,    // �����豸ʧ��
    CS_DISCONN_SUC  = 6,    // �豸�Ͽ����رճɹ�
    CS_RECONN_FAIL  = 7,    // �豸�Ͽ����ر��豸ʧ��
    CS_STAMPER_DROP = 8,    // ӡ�µ���,�������ģʽ
};

static std::string ConnDes[] = 
{ 
    "�ɹ����豸������", 
    "���豸ʧ��",
    "�ɹ��ر��豸",
    "�ر��豸ʧ��",
    "�����豸�ɹ�",
    "�����豸ʧ��",
    "�豸�Ͽ����رճɹ�",
    "�豸�Ͽ����ر��豸ʧ��",
    "ӡ�µ���,�������ģʽ"
};

// ӡ�ػ���PC����״̬����
struct DeviceStat {
    bool        conn_;             //PC��ӡ�ػ��Ƿ�ɹ�����
    ConnStatus  status_;
    std::string cause_;
};

// ӡ�ػ���״̬����
struct AllDoorStat {
    bool top_door_closed_;      // �������Ƿ�ر�
    bool safe_door_closed_;     // ��е���Ƿ�ر�
    bool elec_door_closed_;     // �������Ƿ�ر�
    bool paper_door_closed_;    // ��ֽ���Ƿ�ر�
};

// �����״̬
enum TaskState {
    TS_ALIVE,
    TS_DEAD,
    TS_NON_EXIST
};

#ifndef PATHSPLIT_CHAR
#define PATHSPLIT_CHAR      '\\'
#endif

bool GetMoudulePath(std::string& path);

#ifdef _DEBUG
static const std::string SERVER_NAME = "mc_exed.exe";
#else
static const std::string SERVER_NAME = "mc_exe.exe";
#endif

static const int MQ_MAX_MSG_NUM = 512;
static const int MQ_MAX_MSG_SIZE = 1024;    // 1K

} // namespace MC

#endif // CONTROLLER_COMMON_DEFINITIONS_H_
