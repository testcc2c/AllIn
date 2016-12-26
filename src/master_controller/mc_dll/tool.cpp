#include "stdafx.h"
#include "log.h"
#include "tool.h"

MC::Tool* MC::Tool::g_inst = NULL;

MC::Tool* MC::Tool::GetInst()
{
    if (NULL == g_inst)
        g_inst = new (std::nothrow) MC::Tool;

    return g_inst;
}

void MC::Tool::SetStat(const DeviceStat& stat)
{
    boost::lock_guard<boost::mutex> lk(mutex_);
    device_stat_.conn_ = stat.conn_;
    device_stat_.status_ = stat.status_;
    device_stat_.cause_ = stat.cause_;

    Log::WriteLog(LL_DEBUG, "Tool::SetStat->�����豸״̬ = (%s, %s, %s)",
        device_stat_.conn_ ? "����" : "�Ͽ�",
        MC::ConnDes[device_stat_.status_].c_str(),
        device_stat_.cause_.c_str());
}

bool MC::Tool::Connected()
{
    boost::lock_guard<boost::mutex> lk(mutex_);
    return device_stat_.conn_;
}

MC::ConnStatus MC::Tool::GetStatus()
{
    boost::lock_guard<boost::mutex> lk(mutex_);
    return device_stat_.status_;
}

std::string MC::Tool::GetCause()
{
    boost::lock_guard<boost::mutex> lk(mutex_);
    return device_stat_.cause_;
}

// 0--��, 1--��
void MC::Tool::SetTop(int top)
{
    boost::lock_guard<boost::mutex> lk(door_mtx_);
    doors_stat_.top_door_closed_ = top == 0;
    Log::WriteLog(LL_DEBUG, "MC::Tool::SetTop->������%s", top == 0? "�ر�": "��");
}

void MC::Tool::SeteSafe(int safe)
{
    boost::lock_guard<boost::mutex> lk(door_mtx_);
    doors_stat_.safe_door_closed_ = safe == 0;
    Log::WriteLog(LL_DEBUG, "MC::Tool::SeteSafe->��ȫ��%s", safe == 0 ? "�ر�" : "��");
}

void MC::Tool::SetPaper(int paper)
{
    boost::lock_guard<boost::mutex> lk(door_mtx_);
    doors_stat_.paper_door_closed_ = paper == 0;
    Log::WriteLog(LL_DEBUG, "MC::Tool::SetPaper->��ֽ��%s", paper == 0 ? "�ر�" : "��");
    if (0 == paper)
        SetEvent(paper_door_ev_);
}

const MC::AllDoorStat& MC::Tool::GetDoors()
{
    boost::lock_guard<boost::mutex> lk(door_mtx_);
    //0x0B, ��ȡ��״̬(len = 4)
    //P1:   ��ֽ��״̬  0 �رգ�1 ������ 2������
    //P2:   ������״̬��ͬ��
    //P3:   ��е��״̬��ͬ��
    //P4:   ����״̬��ͬ��
    char doors[4] = { 0 };
    int ret = FGetDoorsPresent(doors, 4);
    if (0 == ret) {
        doors_stat_.top_door_closed_ = 0 == doors[3];
        doors_stat_.safe_door_closed_ = 0 == doors[2];
        doors_stat_.paper_door_closed_ = 0 == doors[0];
    }

    return doors_stat_;
}

/////////////////////////////// ����ӡ�ػ����첽�ص� /////////////////////////////////

int PrepareCamera() 
{
    int ret = FLightCtrl(2, 1);
    if (0 != ret)
        Log::WriteLog(LL_ERROR, "PrepareCamera->��ƾ֤�����ʧ��, er: %d", ret);

    ret = FLightBrightness(2, MC::SvrConfig::GetInst()->brightness_);
    if (0 != ret)
        Log::WriteLog(LL_ERROR, "PrepareCamera->ƾ֤��������ȵ���ʧ��, er: %d", ret);

    ret = OpenCamera(PAPERCAMERA);
    if (0 != ret)
        Log::WriteLog(LL_ERROR, "PrepareCamera->��ƾ֤����ͷʧ��, er: %d", ret);

    ret = SetResolution(
        PAPERCAMERA,
        MC::SvrConfig::GetInst()->resolution_width_,
        MC::SvrConfig::GetInst()->resolution_height_);
    if (0 != ret)
        Log::WriteLog(LL_ERROR, "PrepareCamera->����ƾ֤����ͷ�ֱ���ʧ��, er: %d", ret);

    Log::WriteLog(LL_DEBUG, "PrepareCamera->ƾ֤����ͷ��׼����, ret: %d", ret);
    return ret;
}

void DisableCamera()
{
    CloseCamera(PAPERCAMERA);
}

int _stdcall ConnectCallBack(const char* dev_path, unsigned int msg)
{
    switch (msg) {
    case 0: {
        int ret = ::FCloseDev();
        MC::DeviceStat stat;
        stat.conn_ = !(0 == ret);
        stat.status_ = 0 == ret ? MC::CS_DISCONN_SUC : MC::CS_RECONN_FAIL;
        stat.cause_ = "�Ͽ��豸";
        MC::Tool::GetInst()->SetStat(stat);

        DisableCamera();
    }
        break;
    case 1: {
        int ret = ::FOpenDev(NULL);
        MC::DeviceStat stat;
        stat.conn_ = 0 == ret;
        stat.status_ = 0 == ret ? MC::CS_RECON_SUC : MC::CS_RECON_FAIL;
        stat.cause_ = "�����豸";
        MC::Tool::GetInst()->SetStat(stat);

        PrepareCamera();
    }
        break;
    default:
        break;
    }

    return 0;
}

int _stdcall DevMsgCallBack(
    unsigned int uMsg,
    unsigned int wParam,
    long lParam,
    unsigned char* data,
    unsigned char len)
{
    switch (uMsg) {
    case 0xA3:  {
        // ӡ�µ���֪ͨ
        MC::DeviceStat stat;
        stat.conn_ = true;
        stat.status_ = MC::CS_STAMPER_DROP;
        stat.cause_ = "ӡ�µ���";
        MC::Tool::GetInst()->SetStat(stat);
    }
        break;
    case 0xA4: // ֽ���ź�
        MC::Tool::GetInst()->SetPaper(wParam);
        break;
    case 0xA6: // �����ź�
        MC::Tool::GetInst()->SeteSafe(wParam);
        break;
    case 0xA7: // �������ź�
        MC::Tool::GetInst()->SetTop(wParam);
        break;
    default:
        break;
    }

    return 0;
}
