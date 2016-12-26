#include "boc_api.h"

//////////////////////////// ��ʼ��ӡ�ػ� /////////////////////////////////

class InitMachNT:public MC::NotifyResult {

public:
    void Notify(
        MC::ErrorCode ec,
        std::string data1 = "",
        std::string data2 = "",
        std::string ctx1 = "",
        std::string ctx2 = "")
    {
        std::cout << "��ʼ��ӡ�ػ�, ec: " << ec << ", ��֤��: " << data1.c_str() << std::endl;
    }
};

void boc_test()
{
    MC::BOCApi boc("����");

    MC::NotifyResult* notify = new (std::nothrow) InitMachNT();
    boc.InitMachine("boc_stamper", notify);
}
