#ifndef CONTROLLER_ERROR_CODE_H_
#define CONTROLLER_ERROR_CODE_H_

#include <string>

namespace MC {

enum ErrorCode {
    EC_SUCC,                    // �ɹ�
    EC_FAIL,                    // ʧ��
    EC_TIMEOUT,                 // ��ʱ
    EC_PAPER_TIMEOUT,           // ��ֽ�ų�ʱδ�ر�
    EC_DRIVER_FAIL,             // ���������ӿ�ʧ��
    EC_CON_DISCONN,             // ͨ�����ӶϿ�
    EC_DEV_DISCONN,             // �豸�ѶϿ�
    EC_CONN_OPEN_FAIL,          // �ɹ�����, ���豸ʧ��
    EC_RECONN_FAIL,             // �����豸ʧ��
    EC_STAMPER_DROP,            // ӡ�µ���
    EC_ALREADY_BOUND,           // MAC��ַ�Ѱ�
    EC_MAC_MAX,                 // �Ѱ����2��MAC
    EC_INVALID_PARAMETER,       // �����Ƿ�
    EC_ALLOCATE_FAILURE,        // �����ڴ�ʧ��
    EC_CODE_MISMATCH,           // ��֤�벻ƥ��
    EC_SUC_CALL_BIND,           // �ɹ�, ����ֻ���ȵ��ð�MAC��ַ
    EC_NOT_BOUND,               // ��MAC��ַδ��
    EC_MERGE_FAIL,              // �ϳ���Ƭʧ��
    EC_MODEL_TYPE_FAIL,         // ģ�����͡��Ƕ�ʶ��ʧ��
    EC_RECOG_FAIL,              // ���桢��֤��ʶ��ʧ��
    EC_ELEMENT_FAIL,            // Ҫ��ʶ��ʧ��
    EC_QUERY_DOORS_FAIL,        // ��ѯ��״̬ʧ��
    EC_SAFE_CLOSED,             // ��ȫ���ѹر�
    EC_SAFE_OPENED,             // ��ȫ���Ѵ�
    EC_OPEN_CAMERA_FAIL,        // ��ƾ֤����ͷʧ��
    EC_CAPTURE_FAIL,            // ����ʧ��
    EC_PROCESS_IMG_FAIL,        // ��ƫȥ�ڱ�ʧ��
    EC_TASK_CONSUMED,           // ������ѱ�ʹ��
    EC_TASK_NON_EXIST,          // ����Ų�����
    EC_LOCK_MACHINE_FAIL,       // ����ӡ����ʧ��
    EC_MACHINE_UNLOCKED,        // ӡ����δ����
    EC_MACHINE_LOCKED,          // ӡ���Ǵ�������״̬
    EC_MAX
};

static std::string ErrorMsg[] = {
    "�ɹ�",
    "ʧ��",
    "��ʱ����",
    "��ֽ�ų�ʱδ�ر�",
    "���������ӿ�ʧ��",
    "ͨ�����ӶϿ�",
    "�豸�ѶϿ�",
    "�ɹ�����, ���豸ʧ��",
    "�����豸ʧ��",
    "ӡ�µ���",
    "��MAC��ַ�Ѱ�",
    "�Ѱ����2��MAC��ַ",
    "�����Ƿ�",
    "�����ڴ�ʧ��",
    "��֤�벻ƥ��",
    "�ɹ�, ����ֻ���ȵ��ð�MAC��ַ",
    "��MAC��ַδ��",
    "�ϳ���Ƭʧ��",
    "ģ�����͡��Ƕ�ʶ��ʧ��",
    "���桢��֤��ʶ��ʧ��",
    "Ҫ��ʶ��ʧ��",
    "��ѯ��״̬ʧ��",
    "��ȫ���ѹر�",
    "��ȫ���Ѵ�",
    "��ƾ֤����ͷʧ��",
    "����ʧ��",
    "��ƫȥ�ڱ�ʧ��",
    "������ѱ�ʹ��",
    "����Ų�����",
    "����ӡ����ʧ��",
    "ӡ����δ����",
    "ӡ���Ǵ�������״̬"
};

static std::string GetErrMsg(enum ErrorCode err)
{
    return ErrorMsg[err];
}

static std::string ErrorResolver[] = {
    "�ɹ�",
    "ʧ��",
    "��ʱ����",
    "��ֽ�ų�ʱδ�ر�",
    "���������ӿ�ʧ��",
    "ͨ�����ӶϿ�",
    "�豸�ѶϿ�",
    "�ɹ�����, ���豸ʧ��",
    "�����豸ʧ��",
    "ӡ�µ���",
    "��MAC��ַ�Ѱ�",
    "�Ѱ����2��MAC��ַ",
    "�����Ƿ�",
    "�����ڴ�ʧ��",
    "��֤�벻ƥ��",
    "�ɹ�, ����ֻ���ȵ��ð�MAC��ַ",
    "��MAC��ַδ��",
    "�ϳ���Ƭʧ��",
    "��ѯ��״̬ʧ��",
    "��ȫ���ѹر�",
    "��ȫ���Ѵ�",
    "��ƾ֤����ͷʧ��",
    "����ʧ��",
    "��ƫȥ�ڱ�ʧ��",
    "������ѱ�ʹ��",
    "����Ų�����",
    "����ӡ����ʧ��",
    "ӡ����δ����",
    "ӡ���Ǵ�������״̬"
};

static std::string GetErrResolver(enum ErrorCode err)
{
    return ErrorResolver[err];
}

}   // namespace MC

#endif // CONTROLLER_ERROR_CODE_H_
