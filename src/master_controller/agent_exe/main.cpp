#include <stdio.h>
#include <conio.h>
#include <tchar.h>
#include "agent_cmd.h"
#include "api.h"

int main(int argc, TCHAR *argv[])
{
    // ��ȡӡ���Ǳ��
    std::string sn;
    int ret = QueryMachine(sn);
    printf("main->��ȡӡ���Ǳ��: %d, ���:%s\n", ret, sn.c_str());

    // ��ʼ��
    ret = InitMachine("51534sDf");
    printf("main->��ʼ��ӡ�ػ�: %d\n", ret);

    // ��MAC
    int bind_times = 1;
    while (bind_times--) {
        ret = BindMAC("FFDE03AB");
        printf("main->��MAC��ַ: %d\n", ret);
    }

    // ���MAC
    ret = UnbindMAC("30-3A-64-D6-FD-30");
    printf("main->���MAC��ַ: %d\n", ret);

    // ׼����ӡ
    std::string task_id;
//     ret = PrepareStamp(1, 20, task_id);
//     printf("main->׼����ӡ: %d, �����: %s\n",
//         ret,
//         task_id.c_str());

    // ����
    std::string ori = "G:\\pj\\src\\master_controller\\bin\\ori.jpg";
    std::string cut = "G:\\pj\\src\\master_controller\\bin\\cut.jpg";
    ret = Snapshot(200, 109, ori, cut);
    printf("main->����: %d\n", ret);

    // ��Ƭ�ϳ�
    std::string p1 = "G:\\pj\\src\\master_controller\\bin\\ori.jpg";
    std::string p2 = "G:\\pj\\src\\master_controller\\bin\\cut.jpg";
    std::string merged = "G:\\pj\\src\\master_controller\\bin\\merged.jpg";
    ret = MergePhoto(p1, p2, merged);
    printf("main->�ϳ���Ƭ: %d\n", ret);

    // ��֤��ʶ��
    std::string template_id;
    std::string trace_num;
    ret = RecognizeImage(p1, template_id, trace_num);
    printf("main->��֤��ʶ��: %d\n", ret);

    // Ҫ��ʶ��
    std::string result;
    ret = IdentifyElement(p1,
        100,
        220,
        40,
        30,
        90, 
        result);
    printf("main->Ҫ��ʶ��: %d\n", ret);

    // ��ͨ��ӡ
    ret = OrdinaryStamp("OrdinaryStamp001", "��Ʊ", 2, 200, 100, 180);
    printf("main->��ͨ��ӡ: %d\n", ret);

    // �Զ���ӡ
    ret = AutoStamp("AutoStamp001", "��Ʊ", 1);
    printf("main->�Զ���ӡ: %d\n", ret);

    // ��ӡ����
    ret = FinishStamp("FinishStamp001");
    printf("main->��ӡ����: %d\n", ret);

    // �ͷ�ӡ�ػ�
    ret = ReleaseStamp("STDZ_RELEASE_STAMPER_20161019_001");
    printf("main->�ͷ�ӡ�ػ�: %d\n", ret);

    // ��ȡ������Ϣ
    std::string err_msg;
    std::string err_resolver;
    ret = GetError(10, err_msg, err_resolver);
    printf("main->��ȡ������Ϣ: %d, ��������: %s, �������: %s\n", 
        ret, 
        err_msg.c_str(), 
        err_resolver.c_str());

    // У׼ӡ��
    ret = Calibrate(1);
    printf("main->У׼ӡ��: %d\n", ret);

    // ӡ��״̬��ѯ
    int stamper_status[7] = { 0 };
    ret = QueryStampers(stamper_status);
    printf("main->ӡ��״̬��ѯ: %d\n", ret);

    // ��ȫ��״̬��ѯ
    int safe_status;
    ret = QuerySafe(safe_status);
    printf("main->��ȫ��״̬��ѯ: %d\n", ret);

    // ���ذ�ȫ��
    ret = ControlSafe(1);
    printf("main->���ذ�ȫ��: %d\n", ret);

    // ���Ʒ�����
    ret = ControlBeep(0);
    printf("main->���Ʒ�����: %d\n", ret);

    // ��ȡ������
    int slot_num = 0;
    ret = QuerySlot(slot_num);
    printf("main->��ȡ������: %d, ������: %d\n", ret, slot_num);

    getchar();
    return ret;
}
