#ifndef CONTROLLER_BOC_API_H_
#define CONTROLLER_BOC_API_H_

#include <string>
#include <iostream>
#include <boost/timer.hpp>
#include <boost/asio.hpp>
#include "common_definitions.h"
#include "base_api.h"

#pragma warning(disable:4251)

namespace MC {

// ͳһ�첽֪ͨ����
class MASTERCTRL_API NotifyResult {
public:
    virtual void Notify(
        ErrorCode ec,               // ���崦����
        std::string data1 = "",
        std::string data2 = "",
        std::string ctx1 = "",
        std::string ctx2 = "") = 0;

    virtual ~NotifyResult() {}
};

// ����API
class MASTERCTRL_API BOCApi: public BaseAPI {
public:
    static BOCApi* GetInst() {
        if (NULL == inst_) {
            inst_ = new (std::nothrow) MC::BOCApi("����");
        }

        return inst_;
    }

private:
    BOCApi(std::string des) : BaseAPI(des) {
        int out_x;
        int out_y;
        double out_angle;
        int ret = STSeachSealPoint(
            "K:\\pj\\src\\master_controller\\bin\\ori.jpg",
            100,
            100,
            0,
            out_x,
            out_y,
            out_angle);

        std::string        out_model_type;
        std::string        voucher_no;
        std::string       trace_no;
        int               x;
        int               y;
        int               angle;
        ret = IdentifyImage(
            "K:\\pj\\src\\master_controller\\bin\\cut.jpg",
            "������ʡһ��",
            out_model_type,
            voucher_no,
            trace_no,
            x,
            y,
            angle);
    }

private:
    static MC::BOCApi* inst_;  // ����

public:
    // ��ȡ��ӡ�����
    void QueryMachine(NotifyResult* notify);

    // ����ӡ�ػ����
    void SetMachine(const std::string& sn, NotifyResult* notify);

    // ��ʼ����ӡ��
    // key   --- ��ӡ����֤��
    void InitMachine(std::string key, NotifyResult* notify);

    // ��MAC��ַ
    // mac   --- ����MAC��ַ
    void BindMAC(std::string mac, NotifyResult* notify);

    // ���MAC��ַ
    // mac   --- �����MAC��ַ, ��MAC��ַӦ���Ѱ�MAC��ַ�б���
    void UnbindMAC(std::string mac, NotifyResult* notify);

    // ׼����ӡ
    // stamp_num    --- ӡ�º�(1-6)
    // timeout      --- ��ֽ�ų�ʱδ�ر�(��)
    void PrepareStamp(int stamp_num, int timeout, NotifyResult* notify);

    // ��ѯ��ֽ��״̬
    void QueryPaperDoor(NotifyResult* notify);

    // ����
    // ori_dpi      --- ԭʼͼ��DPI
    // cut_dpi      --- ���к�ͼ��DPI
    void Snapshot(
        int ori_dpi, 
        int cut_dpi, 
        const std::string& ori_path, 
        const std::string& cut_path,
        NotifyResult* notify);

    // �ϳ���Ƭ
    void MergePhoto(
        const std::string& photo1, 
        const std::string& photo2,
        const std::string& merged,
        NotifyResult* notify);

    // ���桢��֤��ʶ��
    void RecognizeImage(
        const std::string& img,
        NotifyResult* notify);

    // Ҫ��ʶ��
    void IdentifyElement(
        const std::string& path,
        int x,
        int y,
        int width,
        int height,
        int angle_,
        NotifyResult* notify);

    // ��ͨ��ӡ
    void OrdinaryStamp(
        const std::string& task,
        const std::string& voucher, 
        int num, 
        int x, 
        int y, 
        int angle, 
        NotifyResult* notify);

    // �Զ���ӡ
    void AutoStamp(
        const std::string& task,
        const std::string& voucher, 
        int num, 
        NotifyResult* notify);

    // ������ӡ
    void FinishStamp(
        const std::string& task, 
        NotifyResult* notify);

    // �ͷ�ӡ�ػ�
    // ����ӡ����, ����������ʱ�̵���
    void ReleaseStamp(
        const std::string& machine, 
        NotifyResult* notify);

    // ��ȡ������Ϣ
    void GetError(
        int err_code, 
        NotifyResult* notify);

    // У׼ӡ��
    // num      --- ӡ�¿��ۺ�, ��1��ʼ
    void CalibrateMachine(
        int num, 
        NotifyResult* notify);

    // ӡ��״̬��ѯ
    void QueryStampers(NotifyResult* notify);

    // ��ȫ��״̬��ѯ
    void QuerySafeDoor(NotifyResult* notify);

    // ���ذ�ȫ��(������)
    // operation        --- 0--��, 1--��
    // timeout          --- ��ʱ��δ�رհ�ȫ��, ����������, ��λ:��
    void OperateSafeDoor(int operation, int timeout, NotifyResult* notify);

    // ���ط�����
    // operation        --- 0--��, 1--��
    void OperateBeep(int operation, NotifyResult* notify);

    // ����������ѯ
    void QuerySlot(NotifyResult* notify);

    // ����������
    void OperateAlarm(int alarm, int ctrl, NotifyResult* notify);

    // ��ѯ�Ѱ�MAC��ַ
    void QueryMAC(NotifyResult* notify);

private:
    std::string des_;
};

}

#endif // CONTROLLER_STAMPER_API_H_
