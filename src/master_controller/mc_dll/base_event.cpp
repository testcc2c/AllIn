#include "stdafx.h"
#include "tool.h"
#include "log.h"
#include "base_event.h"

MC::BaseEvent::BaseEvent(std::string des) : des_(des), exception_(EC_SUCC)
{
}

MC::BaseEvent::~BaseEvent()
{

}

void MC::BaseEvent::Execute()
{
    // �쳣����
    bool conn = Tool::GetInst()->Connected();
    if (!conn) {
        Log::WriteLog(LL_DEBUG, "BaseEvent::Execute->�豸δ����");
        exception_ = EC_DEV_DISCONN;
        goto NOR;
    }

    MC::ConnStatus status = Tool::GetInst()->GetStatus();
    if (CS_OPEN_FAIL == status) {
        Log::WriteLog(LL_DEBUG, "BaseEvent::Execute->����--���豸ʧ��");
        exception_ = EC_CONN_OPEN_FAIL;
        goto NOR;
    }

    if (CS_RECON_FAIL == status) {
        Log::WriteLog(LL_DEBUG, "BaseEvent::Execute->�����豸ʧ��");
        exception_ = EC_RECONN_FAIL;
        goto NOR;
    }

    if (CS_STAMPER_DROP == status) {
        Log::WriteLog(LL_DEBUG, "BaseEvent::Execute->����--ӡ�µ���, ӡ�ػ�������״̬");
        exception_ = EC_STAMPER_DROP;
        goto NOR;
    }

NOR:
    SpecificExecute();
}
