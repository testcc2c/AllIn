#ifndef PSBC_STAMP_COMMON_H_
#define PSBC_STAMP_COMMON_H_

#include <string>

enum ErrorCode {
    EC_SUC,                     // �ɹ�
    EC_FAIL,                    // ��ͨʧ��
    EC_OPEN_FAIL,               // ���豸ʧ��
    EC_QUERY_STAMP_FAIL,        // �����ʧ��
    EC_API_FAIL,                // ���������ӿ�ʧ��
    EC_MACHINE_MISMATCH,        // �豸��Ų�ƥ��
    EC_INVALID_PARAMETER,       // �����Ƿ�
    EC_UPTO_MAX_EXCEPTION,      // ����¼�쳣������Ϣ��Ŀ(4��)
    EC_INTO_MAINTAIN_FAIL,      // ����ά��ģʽʧ��
    EC_QUIT_MAINTAIN_FAIL,      // �˳�ά��ģʽʧ��
    EC_QUERY_DEVICE_FAIL,       // ��ѯϵͳ״̬ʧ��
    EC_NOT_INIT,                // δ��ʼ��
    EC_STARTUP_EXAM,            // �����Լ�
    EC_FREE,                    // ����״̬
    EC_TEST,                    // ����ģʽ
    EC_BREAKDOWN,               // ����ģʽ
    EC_STAMPING,                // ����ģʽ
    EC_MAINTAIN,                // ά��ģʽ
    EC_FILE_NOT_EXIST,          // �ļ�������
    EC_OPEN_VIDEO_FAIL,         // ������ͷʧ��
    EC_CLOSE_VIDEO_FAIL,        // �ر�����ͷʧ��
    EC_SET_CAMERA_PARAM_FAIL,   // ��������ͷ����ʧ��
    EC_OPEN_CAMERA_LED_FAIL,    // ���������ʧ��
    EC_ADJUST_LED_FAIL,         // ��������ȵ���ʧ��
    EC_CLOSE_CAMERA_LED_FAIL,   // �رղ����ʧ��
    EC_DUP_SLOT_NUM,            // ��ͬ�Ĳ�λ��
    EC_CAPTURE_FAIL,            // ����ʧ��
    EC_IMG_PROCESS_FAIL,        // ��ƫȥ�ڱ�ʧ��
    EC_CUT_TO_ORI_FAIL,         // ��ͼתԭͼ����ʧ��
    EC_PAPER_OPEN,              // ��ֽ��δ�ر�
    EC_SAFE_OPEN,               // ��ȫ��δ�ر�
    EC_GET_RFID_FAIL,           // ��ȡӡ��RFIDʧ��
    EC_NO_SEAL,                 // ��ӡ��
    EC_MAX
};

static std::string ec_des[EC_MAX] = 
{
    "�ɹ�",
    "��ͨʧ��",
    "���豸ʧ��",
    "�����ʧ��",
    "���������ӿ�ʧ��",
    "�豸��Ų�ƥ��",
    "�����Ƿ�", 
    "����¼�쳣������Ϣ��Ŀ(4��)",
    "����ά��ģʽʧ��",
    "�˳�ά��ģʽʧ��",
    "��ѯϵͳ״̬ʧ��",
    "δ��ʼ��",
    "�����Լ�",
    "����״̬",
    "����ģʽ",
    "����ģʽ",
    "����ģʽ",
    "ά��ģʽ",
    "�ļ�������",
    "������ͷʧ��",
    "�ر�����ͷʧ��",
    "��������ͷ����ʧ��",
    "���������ʧ��",
    "��������ȵ���ʧ��",
    "�رղ����ʧ��",
    "��ͬ�Ĳ�λ��",
    "����ʧ��",
    "��ƫȥ�ڱ�ʧ��",
    "��ͼתԭͼ����ʧ��",
    "��ֽ��δ�ر�",
    "��ȫ��δ�ر�",
    "��ȡӡ��RFIDʧ��",
    "��ӡ��"
};

#endif // PSBC_STAMP_COMMON_H_
