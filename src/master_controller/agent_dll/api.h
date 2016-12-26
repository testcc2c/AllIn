#ifndef MC_AGENT_API_H_
#define MC_AGENT_API_H_

#include <string>

#ifdef MASTERCTRL_AGENT_EXPORTS
#define MASTERCTRL_AGENT_API _declspec(dllexport)
#else
#define MASTERCTRL_AGENT_API _declspec(dllimport)
#ifdef _DEBUG
#pragma comment(lib, "agentd.lib")
#else
#pragma comment(lib, "agent.lib")
#endif
#endif

#ifdef __cplusplus
extern "C"{
#endif

// ��ȡӡ���Ǳ��
MASTERCTRL_AGENT_API int QueryMachine(
    std::string& sn);

// ����ӡ�ػ����
MASTERCTRL_AGENT_API int SetMachine(
    const std::string& sn);

// ��ʼ��ӡ�ػ�
MASTERCTRL_AGENT_API int InitMachine(
    const std::string& key);

// ��ѯMAC��ַ
MASTERCTRL_AGENT_API int QueryMAC(
    std::string& mac1, 
    std::string& mac2);

// ����:     ��MAC��ַ
//
// �������:
//		const std::string & mac     --- ����MAC��ַ
//
// �������:
//		
// ����ֵ:
MASTERCTRL_AGENT_API int BindMAC(
    const std::string& mac);

// ����:     ���MAC��ַ
//
// �������:
//		const std::string & mac     --- �����MAC��ַ
//
// �������:
//		
// ����ֵ:
MASTERCTRL_AGENT_API int UnbindMAC(
    const std::string& mac);

// ����:     ׼����ӡ
//
// �������:
//		char stamp_num          --- �²ۺ�, ��1��ʼ
//		int timeout             --- ��ֽ�ų�ʱδ�ر�ʱ��, ��λ��
//
// �������:
//		std::string & task_id   --- �����, ����ʹ��һ��
//
// ����ֵ:
MASTERCTRL_AGENT_API int PrepareStamp(
    char            stamp_num, 
    int             timeout, 
    std::string&    task_id);

// ����:     ��ѯ��ֽ��״̬
//
// �������:
//
// �������:
//		int & status        --- 0-��, 1-��
//
// ����ֵ:
MASTERCTRL_AGENT_API int QueryPaper(
    int& status);

// ����
MASTERCTRL_AGENT_API int Snapshot(
    int                 ori_dpi, 
    int                 cut_dpi, 
    const std::string&  ori_path, 
    const std::string&  cut_path);

// �ϳ���Ƭ
MASTERCTRL_AGENT_API int MergePhoto(
    const std::string& p1, 
    const std::string& p2,
    const std::string& merged);

// ���桢��֤��ʶ��
// path         --- ��ͼ·��
// template_id  --- ģ��ID
// trace_num    --- ׷����
MASTERCTRL_AGENT_API int RecognizeImage(
    const std::string&  path, 
    std::string&        template_id, 
    std::string&        trace_num);

// Ҫ��ʶ��
// path         --- ��ͼ·��
MASTERCTRL_AGENT_API int IdentifyElement(
    const           std::string& path, 
    int             x, 
    int             y, 
    int             width, 
    int             height,
    int             angle, 
    std::string&    result);

// ��ͨ��ӡ
MASTERCTRL_AGENT_API int OrdinaryStamp(
    const std::string&  task,
    const std::string&  voucher,
    int                 num, 
    int                 x,          // ����λ��x����, ԭʼͼƬ�е�����
    int                 y,          // ����λ��y����, ԭʼͼƬ�е�����
    int                 angle);     // ӡ����ת�Ƕ�, ���ڵ���0��С��360��

// �Զ���ӡ
MASTERCTRL_AGENT_API int AutoStamp(
    const std::string&  task,
    const std::string&  voucher, 
    int                 num);

// ������ӡ
MASTERCTRL_AGENT_API int FinishStamp(
    const std::string& task);

// �ͷ�ӡ�ػ�
MASTERCTRL_AGENT_API int ReleaseStamp(
    const std::string& machine);

// ӡ��У׼
// slot     --- ���ۺ�, ��1��ʼ
MASTERCTRL_AGENT_API int Calibrate(
    int slot);

// ��ѯӡ��״̬
// status   --- 0-����, 1-����, ��"001101"
MASTERCTRL_AGENT_API int QueryStampers(
    int* status);

// ��ȫ��״̬
// status   --- 0-��,1-��
MASTERCTRL_AGENT_API int QuerySafe(
    int& status);

// ���ذ�ȫ��
// ctrl     --- 0 - ��, 1 - ��
MASTERCTRL_AGENT_API int ControlSafe(
    int ctrl);

// ����������
// ctrl     --- 0 - ��, 1 - ��
MASTERCTRL_AGENT_API int ControlBeep(
    int ctrl);

// ����������
//alarm     --- 0(���ű�����)
//              1(�񶯱�����)
//switches  --- ����������
//              1(����);
//              0(�ر�)
MASTERCTRL_AGENT_API int ControlAlarm(
    int alarm, 
    int switches);

// ����������ѯ
// num      --- ʵ��ӡ����
MASTERCTRL_AGENT_API int QuerySlot(
    int& num);

// ��ȡ��ϸ������Ϣ
MASTERCTRL_AGENT_API int GetError(
    int             err_code,
    std::string&    err_msg,
    std::string&    err_resolver);

#ifdef __cplusplus
}
#endif

#endif // MC_AGENT_API_H_
