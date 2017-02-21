// PSBC_STAMP.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include <time.h>
#include <ctime>
#include "SealLog.h"
#include "USBControlF60.h"
#include "PSBC_STAMP.h"
#include "ImgProcAndReco.h"
#include "parse.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//TODO: If this DLL is dynamically linked against the MFC DLLs,
//		any functions exported from this DLL which call into
//		MFC must have the AFX_MANAGE_STATE macro added at the
//		very beginning of the function.
//
//		For example:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// normal function body here
//		}
//
//		It is very important that this macro appear in each
//		function, prior to any calls into MFC.  This means that
//		it must appear as the first statement within the 
//		function, even before any object variable declarations
//		as their constructors may generate calls into the MFC
//		DLL.
//
//		Please see MFC Technical Notes 33 and 58 for additional
//		details.
//

#ifdef _DEBUG
#pragma comment(lib, "ABC.STDZ.Device.STAMP.USBF60APID.lib")
#pragma comment(lib, "ABC.STDZ.Device.STAMP.SealLog.lib")
#pragma comment(lib, "ABC.STDZ.Device.STAMP.RZCamera.lib")
#pragma comment(lib, "ImageProcess.lib")
#else
#pragma comment(lib, "ABC.STDZ.Device.STAMP.USBF60API.lib")
#pragma comment(lib, "ABC.STDZ.Device.STAMP.SealLog.lib")
#pragma comment(lib, "ABC.STDZ.Device.STAMP.RZCamera.lib")
#pragma comment(lib, "ImageProcess.lib")
#endif

bool PSBCSTDZDeviceSTAMPDeviceApp::connected_ = false;

HANDLE PSBCSTDZDeviceSTAMPDeviceApp::notify_finish = CreateEvent(NULL, TRUE, FALSE, NULL);

BEGIN_MESSAGE_MAP(PSBCSTDZDeviceSTAMPDeviceApp, CWinApp)

END_MESSAGE_MAP()


PSBCSTDZDeviceSTAMPDeviceApp::PSBCSTDZDeviceSTAMPDeviceApp()
{
    // TODO: �ڴ˴���ӹ�����룬
    // ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}

// Ψһ��һ�� CABCSTDZDeviceSTAMPDeviceApp ����
PSBCSTDZDeviceSTAMPDeviceApp theApp;


// CABCSTDZDeviceSTAMPDeviceApp ��ʼ��

BOOL PSBCSTDZDeviceSTAMPDeviceApp::InitInstance()
{
    CWinApp::InitInstance();
    PSBCConfig::GetInst()->Parse();

    F_RegisterDevCallBack(PSBCSTDZDeviceSTAMPDeviceApp::DevConnCallBack);
    FRegisterDevCallBack(PSBCSTDZDeviceSTAMPDeviceApp::DevMessageCallBack);
    FOpenDev(NULL); // ��ֹ��̬���ؿ�(�ӳټ���)�����µĴ���

    init_                               = false;
    across_page_seal_called_            = false;
    video_opened_                       = false;
    querySealInfo_str_                  = NULL;
    querySloatInfo_str_                 = NULL;
    getMachineNum_str_                  = NULL;
    readOpenBackDoorExceptionInfo_str_  = NULL;
    getMachineType_str_                 = NULL;

    return TRUE;
}

int PSBCSTDZDeviceSTAMPDeviceApp::ExitInstance()
{
    CWinApp::ExitInstance();

//     F_RegisterDevCallBack(NULL);
//     FRegisterDevCallBack(NULL);
    delete[] querySealInfo_str_;
    delete[] querySloatInfo_str_;
    delete[] getMachineNum_str_;
    delete[] readOpenBackDoorExceptionInfo_str_;
    delete[] getMachineType_str_;
    DisableCamera();

    return 0;
}

int PSBCSTDZDeviceSTAMPDeviceApp::Test()
{
    return 0;
}

//////////////////////////////////////////////////////////////////////////

int PrepareCamera()
{
    FOpenDev(NULL);
    int ret = FLightCtrl(2, 1);
    if (0 != ret)
        WriteLog(3, "PrepareCamera->��ƾ֤�����ʧ��, er: %d", ret);

    ret = FLightBrightness(2, PSBCConfig::GetInst()->brightness_);
    if (0 != ret)
        WriteLog(3, "PrepareCamera->ƾ֤��������ȵ���ʧ��, er: %d", ret);

    ret = OpenCamera(PAPERCAMERA);
    if (0 != ret)
        WriteLog(3, "PrepareCamera->��ƾ֤����ͷʧ��, er: %d", ret);

    ret = SetResolution(
        PAPERCAMERA,
        PSBCConfig::GetInst()->resolution_width_,
        PSBCConfig::GetInst()->resolution_height_);
    if (0 != ret)
        WriteLog(3, "PrepareCamera->����ƾ֤����ͷ�ֱ���ʧ��, er: %d", ret);

    WriteLog(4, "PrepareCamera->ƾ֤����ͷ��׼����, ret: %d", ret);
    return ret;
}

void DisableCamera()
{
    //CloseCamera(PAPERCAMERA);
}

int PSBCSTDZDeviceSTAMPDeviceApp::DevConnCallBack(
    const char*     DevPath,
    unsigned int    uMsg)
{
    // uMsg: 1 ����, 0 �Ͽ�
    switch (uMsg) {
    case 0: {
        ::FCloseDev();
        connected_ = false;
        DisableCamera();

        WriteLog(4, "DevConnCallBack->�豸�Ͽ����ر��豸, %s", 
            connected_ ? "����" : "�Ͽ�");
    }
        break;
    case 1: {
        ::FOpenDev(DevPath);
        connected_ = true;
/*        PrepareCamera();*/

        WriteLog(4, "DevConnCallBack->�豸���������豸, %s",
            connected_ ? "����" : "�Ͽ�");
    }
        break;
    default:
        break;
    }

    return 0;
}

int PSBCSTDZDeviceSTAMPDeviceApp::DevMessageCallBack(
    unsigned int    uMsg,
    unsigned int    wParam,
    long            lParam,
    unsigned char*  data,
    unsigned char   len)
{
    switch (uMsg) {
    case STAMPER_DOWN: {            // ������ѹ֪ͨ
        WriteLog(4, "DevMessageCallBack->����ѹ֪ͨ");
    }
        break;
    case STAMPER_COMPLETE: {        // �������֪ͨ
        WriteLog(4, "DevMessageCallBack->�������֪ͨ, ���: %s",
            wParam == 0 ? "�ɹ�": "ʧ��");
        SetEvent(notify_finish);
    }
        break;
    case STAMPER_SEALERR: {         // ӡ�µ���֪ͨ
        WriteLog(4, "DevMessageCallBack->ӡ�µ���֪ͨ");
    }
        break;
    case STAMPER_SIDEDOOR_CLOSE: {
        if (0 == wParam) {
             WriteLog(4, "DevMessageCallBack->��е���ر�֪ͨ");
             SetStampMap();
             FCloseDoorSafe();   // �ص�����
             FQuitMaintainMode();
       }
    }
        break;
    default:
        break;
    }

    return 0;
}

void WriteLog(int level, const char * fmt, ...)
{
#define LOG_SIZE 2048

    char buf[LOG_SIZE] = { 0 };
    va_list val;
    va_start(val, fmt);
    _vsnprintf_s(buf, LOG_SIZE, fmt, val);
    va_end(val);

    WriteSealLog(level, buf);
}

//////////////////////// ӡ�ػ�-�ʴ��ӿ�ʵ�� /////////////////////////////////////

int PSBCSTDZDeviceSTAMPDeviceApp::InitializeMachine(void)
{
    WriteLog(4, "InitializeMachine->IN");

    // ����:	��ӡ���Լ�
    // ˵�� : ������״̬�Ƿ����������磺���ӡ��
    // �豸��һ��ʹ�û����ӡ��ʱ����

    ExitIfInMaintain();

    // ���ȴ��豸
    int ret = FOpenDev(NULL);
    if (0 != ret) {
        WriteLog(3, "InitializeMachine->�豸��ʧ��, er: %d", ret);
        return EC_OPEN_FAIL;
    }

    init_ = true;

    // ������ӳ�� 
    ret = SetStampMap();
    if (0 != ret) {
        WriteLog(3, "InitializeMachine->������ӳ��ʧ��, er: %d", ret);
        return EC_QUERY_STAMP_FAIL;
    }

    // ��λӡ�ػ�
    Reset();

    // ���ϵͳ״̬
    unsigned char status[24] = { 0 };
    ret = FGetDevStatus(status, 24);
    if (0 != ret) {
        WriteLog(3, "InitializeMachine->�����ϵͳʧ��, er: %d", ret);
        return EC_QUERY_DEVICE_FAIL;
    }

    WriteLog(4, "InitializeMachine->��ǰϵͳ״̬: %d", status[1]);
    WriteLog(4, "InitializeMachine->OUT");

    switch (status[1]) {
    case 0:
        return EC_NOT_INIT;
    case 1:
        return EC_STARTUP_EXAM;
    case 3:
        return EC_SUC;
    case 4:
        return EC_TEST;
    case 5:
        return EC_BREAKDOWN;
    case 6:
        return EC_STAMPING;
    case 7:
        return EC_MAINTAIN;
    default:
        return EC_FAIL;
    }
}

char* PSBCSTDZDeviceSTAMPDeviceApp::querySealInfo(const char* machineNum)
{
    if (querySealInfo_str_ == NULL)
        querySealInfo_str_ = new char[MAX_SLOT_STAMPER_SIZE + 1];

    memset(querySealInfo_str_, 0x0, MAX_SLOT_STAMPER_SIZE + 1);

    if (NULL == machineNum) {
        WriteLog(3, "PSBCSTDZDeviceSTAMPDeviceApp::querySealInfo->�������Ϊ��");
        return querySealInfo_str_;
    }

    WriteLog(4, "querySealInfo->IN, (machineNum) = (%s)",
        machineNum);

    ExitIfInMaintain();

    // ��ʽ: ��λ�� : ӡ��ID; ��λ��:ӡ��ID(0 ��ʾ����)...
    // ��(1:00000000001a; 2:00000000002b; 3:0...)

    // ��У���豸���
    ErrorCode ec = CheckMachineNum(machineNum);
    if (EC_SUC != ec)
        return querySealInfo_str_;

    // �豸�����ȷ, ����λ����ӡ��ID
    // �����ζ���
    int ret1, ret2;
    unsigned char len = 0;
    unsigned char data[] = { 0 };
    ret1 = ReadStamperMem(
        SLOT_STAMPER_WRITTEN_OFFSET,
        SLOT_STAMPER_WRITTEN_SIZE,
        data,
        len);

    int read_expected = (ret1 == 0 ? data[0] : 90);
    char* str = querySealInfo_str_;
    ret1 = ReadStamperMem(
        SLOT_STAMPER_OFFSET,
        read_expected > 45 ? 45 : read_expected,
        (unsigned char*)str,
        len);

    if (read_expected > 45) {
        ret2 = ReadStamperMem(
            SLOT_STAMPER_OFFSET + 46,
            read_expected - 45,
            (unsigned char*)(str + 45),
            len);
    }

    WriteLog(4, "querySealInfo->OUT, sealInfo: %s",
        str);
    return str;
}

char* PSBCSTDZDeviceSTAMPDeviceApp::querySloatInfo(const char* machineNum)
{
    if (querySloatInfo_str_ == NULL)
        querySloatInfo_str_ = new char[25];

    memset(querySloatInfo_str_, 0x0, 25);

    if (NULL == machineNum) {
        WriteLog(3, "querySloatInfo->����Ϊ��");
        return querySloatInfo_str_;
    }

    WriteLog(4, "querySloatInfo->IN, (machineNum) = (%s)",
        machineNum);

    ExitIfInMaintain();

    // ��ʽ: ��λ��:ӡ���Ƿ����;��λ��:ӡ���Ƿ���� (0 ��ʾ����,1 ��ʾ����)...
    // ��(1:0; 2:1; 3:0...)
    
    // У���豸���
    ErrorCode ec = CheckMachineNum(machineNum);
    if (EC_SUC != ec)
        return querySloatInfo_str_;

    // ���豸���ƥ��
    char* seal_info = querySealInfo(machineNum);
    if (strlen(seal_info) == 0) {
        WriteLog(3, "querySloatInfo->��ȡӡ����Ϣʧ��");
        return querySloatInfo_str_;
    }

    std::map<int, std::string> slot_stamper;
    if (!ParseSlotAndStamperID(seal_info, slot_stamper)) {
        WriteLog(3, "querySloatInfo->���ظ����²ۺ�");
        return querySloatInfo_str_;
    }

    char* str = querySloatInfo_str_;
    for (int i = 0; i < 6; ++i) {
        std::map<int, std::string>::iterator it = slot_stamper.find(i + 1);
        sprintf(str + i * 4, "%d:%d;", i + 1, atoi(it->second.c_str()) == 0 ? 0 : 1);
    }

    WriteLog(4, "querySloatInfo->OUT, sloatInfo: %s",
        str);
    return str;
}

int PSBCSTDZDeviceSTAMPDeviceApp::initStamp(
    const char* machineNum, 
    const char* slotNumAndStampId)
{
    // �������
    if (NULL == machineNum || NULL == slotNumAndStampId) {
        WriteLog(3, "initStamp->����Ϊ��");
        return EC_INVALID_PARAMETER;
    }

    WriteLog(4, "initStamp->IN, (machineNum, slotNumAndStampId) = (%s, %s)",
        machineNum,
        slotNumAndStampId);

    // ��λ����ӡ��IDѭ����
    // ��(1:00000000001a; 2:00000000002b; 3:0...), ���Ȳ�����15*��������

    std::map<int, std::string> slot_stamper;
    if (!ParseSlotAndStamperID(slotNumAndStampId, slot_stamper)) {
        WriteLog(3, "initStamp->���ظ����²ۺ�");
        return EC_DUP_SLOT_NUM;
    }

    std::map<int, std::string>::iterator it = slot_stamper.begin();
    for (; it != slot_stamper.end(); ++it) {
        // �ж��²ۺ��Ƿ�Ϸ�
        if (it->first < 1 || it->first > 6) {
            WriteLog(3, "initStamp->�зǷ��²ۺ�: %d", it->first);
            return EC_INVALID_PARAMETER;
        }

        // �ж�ÿ���²ۺŶ�Ӧ��ӡ����Ϣ�Ƿ�Ϸ�
        if (it->second.length() > 12) {
            WriteLog(3, "initStamp->�зǷ�����Ϣ(%d, %s)", 
                it->first,
                it->second.c_str());
            return EC_INVALID_PARAMETER;
        }
    }

    // �����Ϸ�
    ExitIfInMaintain();

    // У���豸���
    ErrorCode ec = CheckMachineNum(machineNum);
    if (EC_SUC != ec)
        return ec;

    // �豸���ƥ��, ������д��ӡ�ػ��洢��
    int ret1, ret2;
    // ���ݹ���, ������д��
    if (strlen(slotNumAndStampId) > 45) {
        ret1 = WriteIntoStamper(
            SLOT_STAMPER_OFFSET,
            (unsigned char*)slotNumAndStampId,
            45);

        ret2 = WriteIntoStamper(
            SLOT_STAMPER_OFFSET + 46,
            (unsigned char*)(slotNumAndStampId + 45),
            strlen(slotNumAndStampId) - 45 + 1);
        if (EC_SUC == ret1 && EC_SUC == ret2) {
            unsigned char len = strlen(slotNumAndStampId);
            WriteIntoStamper(
                SLOT_STAMPER_WRITTEN_OFFSET,
                &len,
                SLOT_STAMPER_WRITTEN_SIZE);
            return EC_SUC;
        } else {
            WriteLog(3, "initStamp->д����Ϣʧ��");
            return EC_FAIL;
        }
    }

    // ������45�ֽڿ�һ����д��
    ret1 = WriteIntoStamper(
        SLOT_STAMPER_OFFSET,
        (unsigned char*)slotNumAndStampId,
        strlen(slotNumAndStampId) + 1);
    if (0 != ret1)
        return EC_API_FAIL;

    unsigned char len = strlen(slotNumAndStampId);
    WriteIntoStamper(
        SLOT_STAMPER_WRITTEN_OFFSET,
        &len,
        SLOT_STAMPER_WRITTEN_SIZE);

    WriteLog(4, "initStamp->OUT, (machineNum, slotNumAndStampId) = (%s, %s)",
        machineNum,
        slotNumAndStampId);
    return EC_SUC;
}

int PSBCSTDZDeviceSTAMPDeviceApp::setAcrossPageSeal(void)
{
    WriteLog(4, "setAcrossPageSeal->IN");

    ExitIfInMaintain();

    across_page_seal_called_ = true;
    WriteLog(4, "setAcrossPageSeal->OUT");
    return 0;
}

int PSBCSTDZDeviceSTAMPDeviceApp::setMachineNum(const char* machineNum)
{
    if (NULL == machineNum) {
        WriteLog(3, "setMachineNum->����Ϊ��");
        return EC_INVALID_PARAMETER;
    }

    WriteLog(4, "setMachineNum->IN, (machineNum) = (%s)", machineNum);

    ExitIfInMaintain();

    // �������, ���20λ�ַ���
    if (strlen(machineNum) > 20) {
        WriteLog(3, "setMachineNum->��������ָ������(%d)", 20);
        return EC_INVALID_PARAMETER;
    }

    int ret = WriteStamperIdentifier(
        (unsigned char*)machineNum, 
        strlen(machineNum) + 1); // ��0��β�ַ�д��ȥ
    if (0 != ret) {
        WriteLog(3, "setMachineNum->���������ӿ�ʧ��, er: %d", ret);
        return EC_API_FAIL;
    }

    WriteLog(4, "setMachineNum->OUT, (machineNum) = (%s)", machineNum);
    return 0;
}

int PSBCSTDZDeviceSTAMPDeviceApp::openPaperDoor(void)
{
    WriteLog(4, "openPaperDoor->IN");

    ExitIfInMaintain();

    unsigned char status[24] = { 0 };
    while (true) {
        int ret = FGetDevStatus(status, 24);
        if (0 != ret) {
            WriteLog(3, "openPaperDoor->�����ϵͳʧ��, er: %d", ret);
            break;
        }

        // ���Ǹ��¹�����, �˳�
        if (status[1] != 6)
            break;
    }
    
    // �رձ�����
    SetAlarm(0, 0);
    SetAlarm(1, 0);
    
    int ret = FOpenDoorPaper();
    if (0 != ret) {
        WriteLog(3, "openPaperDoor->���������ӿ�ʧ��, er: %d", ret);
        return EC_API_FAIL;
    }

    WriteLog(4, "openPaperDoor->OUT");
    return 0;
}

char* PSBCSTDZDeviceSTAMPDeviceApp::geterrMsg(int errNo)
{
    WriteLog(4, "geterrMsg->IN, (errNo) = (%d)", errNo);

    ExitIfInMaintain();

    if (errNo >= EC_MAX || errNo < 0)
        return "δ����Ĵ�����";
    
    WriteLog(4, "geterrMsg->OUT, (errNo) = (%d)", errNo);
    return (char*)ec_des[errNo].c_str();
}

// ��ͼ��������, pointX, pointY
int PSBCSTDZDeviceSTAMPDeviceApp::checkManualPrintPara(int pointX, int pointY, int angle)
{
    WriteLog(4, "checkManualPrintPara->IN, (pointX, pointY, angle)"
        " = (%d, %d, %d)",
        pointX,
        pointY,
        angle);

    ExitIfInMaintain();

    // ����ת��
    int ori_x = -1;
    int ori_y = -1;
    int ori_angle = 0;
    int ret = SearchImgStampPointForPSBC(
        src_image_.c_str(),      // ԭͼ�ļ�
        pointX,                  // ��ͼ��ӡ��
        pointY,
        angle,
        ori_x,
        ori_y,
        ori_angle);
    if (0 != ret) {
        WriteLog(3, "checkManualPrintPara->��ͼתԭͼ����ʧ��");
        return EC_CUT_TO_ORI_FAIL;
    }

    ret = FOpenDev(NULL);
    if (0 != ret)
        WriteLog(3, "checkManualPrintPara->���豸ʧ��");

    WriteLog(4, "checkManualPrintPara->��ͼתԭͼ����(%d, %d)���سɹ�",
        ori_x,
        ori_y);

    // ��ԭͼ��������ת������������
    struct Point* pt = GetSealCoord(ori_x, ori_y);
    WriteLog(3, "checkManualPrintPara->ԭͼ:(%d, %d)ת��������:(%d, %d)",
        ori_x,
        ori_y,
        pt->x,
        pt->y);

    WriteLog(4, "checkManualPrintPara->OUT, (pointX, pointY, angle)"
        " = (%d, %d, %d)",
        pointX,
        pointY,
        angle);
    delete pt;
    return EC_SUC;
}

// ����(�Ƿ�պӡ��)
// pointX, pointY   --- ��ӡ��ͼ��������
int PSBCSTDZDeviceSTAMPDeviceApp::ManualStart(
    int printNum,
    int pointX,
    int pointY,
    int angle,
    int ink)        // �Ƿ�պӡ��
{
    WriteLog(4, "ManualStart->IN");

    // ��ӡ�������
    if (printNum <= 0 || printNum > 6 || angle < 0 || angle > 360 || pointX < 0 || pointY < 0) {
        WriteLog(3, "ManualStart->�����Ƿ�");
        return EC_INVALID_PARAMETER;
    }

    ExitIfInMaintain();

    // ��ֽ��״̬
    if (1 == checkPaperDoorState()) {
        WriteLog(4, "ManualStart->��ֽ��δ�ر�");
        return EC_PAPER_OPEN;
    }

    // ��ȫ��״̬
    if (1 == checkBackDoorState()) {
        WriteLog(4, "ManualStart->��ȫ��δ�ر�");
        return EC_SAFE_OPEN;
    }

    // �²ۺ��Ƿ���Ч
    unsigned int rfids[7] = { 0 };
    unsigned char stampers = 0;
    if (0 == ReadAllRFID(rfids, 7, &stampers)) {
        if (rfids[printNum - 1] == 0) {
            WriteLog(3, "ManualStart->%d���²�����", printNum);
            return EC_NO_SEAL;
        }
    }

    // ��ӡԭͼ·��
    WriteLog(4, "ManualStart->ƾ֤ԭͼ·��: %s, Ѱ��ԭͼ����",
        src_image_.c_str());

    // ����ת��
    int ori_x = -1;
    int ori_y = -1;
    int ori_angle = 0;
    int ret = SearchImgStampPointForPSBC(
        src_image_.c_str(),      // ԭͼ�ļ�
        pointX,                  // ��ͼ��ӡ��
        pointY,
        angle,
        ori_x,
        ori_y,
        ori_angle);
    if (0 != ret) {
        WriteLog(3, "ManualStart->��ͼתԭͼ����ʧ��");
        return EC_CUT_TO_ORI_FAIL;
    }

    ret = FOpenDev(NULL);
    if (0 != ret)
        WriteLog(3, "ManualStart->���豸ʧ��");

    WriteLog(4, "ManualStart->��ͼ(%d, %d)תΪԭͼ����(%d, %d)���سɹ�",
        pointX,
        pointY,
        ori_x,
        ori_y);

    struct Point* pt = GetSealCoord(ori_x, ori_y);
    WriteLog(4, "ManualStart->ԭͼת��������:(%d, %d)���׳ɹ�, ��ʽ: %s",
        pt->x,
        pt->y,
        across_page_seal_called_ ? "�������" : "����ͨ��");

    StampPara para;
    para.stamp_idx = printNum;
    ret = GetStamperID(para.stamp_idx - 1, para.rfid);
    if (0 != ret) {
        WriteLog(3, "ManualStart->��ȡӡ��(%d)��rfidʧ��", para.stamp_idx);
        return EC_GET_RFID_FAIL;
    }

    STAMPERPARAM pa;
    memcpy(&pa.seal, &para.rfid, 4);
    std::srand(std::time(0));
    unsigned int serial = std::rand();
    pa.serial_number = serial;
    pa.isPadInk = ink;
    pa.x_point = pt->x;
    pa.y_point = pt->y;
    para.wait = PSBCConfig::GetInst()->wait_time_;
    pa.w_time = para.wait;
    pa.type = across_page_seal_called_ ? 1 : 0;
    across_page_seal_called_ = false;

    // �ȹر��𶯱���
    ret = SetAlarm(1, 0);
    if (0 != ret)
        WriteLog(3, "ManualStart->���𶯱���ʧ��");

    // ����һ����ʾ����
    FBeepCtrl(2, 1);
    FBeepCtrl(0, 0);
    Sleep(500);
    ret = FStartStamperstrc(&pa);
    if (0 != ret) {
        WriteLog(3, "ManualStart->�������ʧ��, er: %d", ret);
        delete pt;
        return EC_FAIL;
    }

    // 20���ڸ������
    DWORD finish = WaitForSingleObject(notify_finish, 20 * 1000);
    switch (finish) {
    case WAIT_OBJECT_0: {
       ResetEvent(notify_finish);
       ret = 0;
       WriteLog(4, "ManualStart->�ȴ�������ɳɹ�");
    }
        break;
    case WAIT_TIMEOUT: {
       ret = 0;
       WriteLog(4, "ManualStart->�ȴ�������ɳ�ʱ");
    }
        break;
    default: {
       ret = 0;
       WriteLog(4, "ManualStart->�ȴ�������ɴ���");
    }
        break;
    }

    WriteLog(4, "ManualStart->OUT");
    delete pt;
    return ret;
}

// printNum         --- �²ۺ�(1~6)
// pointX, pointY   --- ��������, ����ͼƬ���Ͻ�
int PSBCSTDZDeviceSTAMPDeviceApp::manualPrintStart(
    int printNum, 
    int pointX, 
    int pointY, 
    int angle)
{
    WriteLog(4, "manualPrintStart->IN, (printNum, pointX, pointY, "
        "angle) = (%d, %d, %d, %d)",
        printNum,
        pointX,
        pointY,
        angle);

    return ManualStart(printNum, pointX, pointY, angle, 1);
}

// ��������ӡ(��պӡ��)
// pointX, pointY   --- ��������
int PSBCSTDZDeviceSTAMPDeviceApp::manualPrintStartByLight(
    int printNum, 
    int pointX, 
    int pointY, 
    int angle)
{
    WriteLog(4, "manualPrintStartByLight->IN, (printNum, pointX,"
        " pointY, angle) = (%d, %d, %d, %d)",
        printNum,
        pointX,
        pointY,
        angle);

    return ManualStart(printNum, pointX, pointY, angle, 0);
}

// �Զ���ӡ
// pointX, pointY   --- ��ӡ��������, ��λ����
int PSBCSTDZDeviceSTAMPDeviceApp::autoPrintStart(
    int printNum, 
    int pointX, 
    int pointY, 
    int angle)
{
    WriteLog(4, "autoPrintStart->IN, (printNum, pointX,"
        " pointY, angle) = (%d, %d, %d, %d)",
        printNum,
        pointX,
        pointY,
        angle);

    // ����ת����
    int x_in_pixel = 0;
    int ret = ConvertMM2Dpi(
        pointX,
        PSBCConfig::GetInst()->dpi_,
        x_in_pixel);
    if (0 != ret) {
        WriteLog(3, "autoPrintStart->x��������(%d)ת��������ʧ��, er: %d",
            pointX,
            ret);
        return EC_FAIL;
    }

    int y_in_pixel = 0;
    ret = ConvertMM2Dpi(
        pointY,
        PSBCConfig::GetInst()->dpi_,
        y_in_pixel);
    if (0 != ret) {
        WriteLog(3, "autoPrintStart->y��������(%d)ת��������ʧ��, er: %d",
            pointY,
            ret);
        return EC_FAIL;
    }

    WriteLog(4, "autoPrintStart->��������(%d, %d)ת��������ֵ(%d, %d)�ɹ�",
        pointX,
        pointY,
        x_in_pixel,
        y_in_pixel);

    ret = ManualStart(printNum, x_in_pixel, y_in_pixel, angle, 1);
    WriteLog(4, "autoPrintStart->OUT, (printNum, pointX,"
        " pointY, angle) = (%d, %d, %d, %d)",
        printNum,
        pointX,
        pointY,
        angle);
    return ret;
}

int PSBCSTDZDeviceSTAMPDeviceApp::openMachineBackDoor(void)
{
    WriteLog(4, "openMachineBackDoor->IN");

    ExitIfInMaintain();

    // ���ȹر��𶯱���
    SetAlarm(0, 0);
    SetAlarm(1, 0);

    // ����ά��ģʽ
    int ret = FMaintenanceMode();
    if (0 != ret) {
        WriteLog(3, "openMachineBackDoor->����ά��ģʽʧ��, er: %d", ret);
        return EC_INTO_MAINTAIN_FAIL;
    }

    // ��ǰ�ǡ�ά��ģʽ��
    ret = FOpenDoorSafe();  // �򿪵�����
    if (0 != ret) {
        WriteLog(3, "openMachineBackDoor->�򿪵�����ʧ��, er: %d", ret);
        return EC_QUIT_MAINTAIN_FAIL;
    }

    WriteLog(4, "openMachineBackDoor->OUT");
    return EC_SUC;
}

int PSBCSTDZDeviceSTAMPDeviceApp::openMachineBackDoorUnNormal(const char* openInfo)
{
    if (NULL == openInfo) {
        WriteLog(3, "openMachineBackDoorUnNormal->����Ϊ��");
        return EC_INVALID_PARAMETER;
    }

    WriteLog(4, "openMachineBackDoorUnNormal->IN, (openInfo) = (%s)",
        openInfo);

    // �쳣������Ϣ���15���ַ�, ������0��β�ַ�
    if (strlen(openInfo) > 15) {
        WriteLog(3, "openMachineBackDoorUnNormal->�������ȳ����涨����󳤶�%d", 15);
        return EC_INVALID_PARAMETER;
    }

    unsigned char data[2] = { 0 };
    unsigned char len = 0;
    // �Ѽ�¼�쳣������Ϣ����
    int ret = ReadStamperMem(
        OPEN_SAFE_DOOR_EXCEPTION_MARK_OFFSET,
        OPEN_SAFE_DOOR_EXCEPTION_MARK_SIZE,
        data,
        len);
    if (0 != ret)
        return EC_API_FAIL;

    // �ж��Ƿ��Ѿ�д����쳣������¼
    int recorded = strtol((char*)&data[0], NULL, 16);
    if (recorded > MAX_EXCEPTION_OPEN_COUNT - 1) {
        WriteLog(3, "openMachineBackDoorUnNormal->�Ѿ�д����쳣������¼");
        return EC_UPTO_MAX_EXCEPTION;
    }

    // ������ȷ������д��
    ExitIfInMaintain();

    ret = openMachineBackDoor();
    if (EC_SUC != ret) {
        WriteLog(3, "openMachineBackDoorUnNormal->�򿪰�ȫ��ʧ��, er: %d",
            ret);
        return ret;
    }
    
    char open_info[17] = { 0 };
    strcpy(open_info, openInfo);
    strcat(open_info, ";");
    ret = WriteIntoStamper(
        OPEN_SAFE_DOOR_EXCEPTION_OFFSET + recorded * OPEN_SAFE_DOOR_EXCEPTION_SIZE,
        (unsigned char*)open_info,
        strlen(open_info));
    if (0 != ret)
        return ret;

    // д�쳣������Ϣ�ɹ�, ���¼�¼�쳣������Ϣ��Ŀ
    data[0] += 1;
    ret = WriteIntoStamper(
        OPEN_SAFE_DOOR_EXCEPTION_MARK_OFFSET,
        data,
        1);

    WriteLog(4, "openMachineBackDoorUnNormal->OUT, (openInfo) = (%s)",
        openInfo);
    return ret;
}

char* PSBCSTDZDeviceSTAMPDeviceApp::getMachineNum(void)
{
    WriteLog(4, "getMachineNum->IN");

    ExitIfInMaintain();

    if (getMachineNum_str_ == NULL) {
        getMachineNum_str_ = new unsigned char[21];
    }

    memset(getMachineNum_str_, 0x0, 21);

    int ret = ReadStamperIdentifier(getMachineNum_str_, 21);
    if (0 != ret) {
        WriteLog(3, "getMachineNum->ReadStamperIdentifierʧ��, er: %d",
            ret);
        return (char*)getMachineNum_str_;
    }

    WriteLog(4, "getMachineNum->OUT");
    return (char*)getMachineNum_str_;
}

char* PSBCSTDZDeviceSTAMPDeviceApp::getMachineType(void)
{
    WriteLog(4, "getMachineType->IN");

    ExitIfInMaintain();

    if (getMachineType_str_ == NULL) {
        getMachineType_str_ = new char[512];
    }

    memset(getMachineType_str_, 0x0, 512);

    unsigned char sn[49] = { 0 };
    int ret = ReadBackupSN(sn, 48);
    if (0 != ret) {
        WriteLog(3, "getMachineType->ReadBackupSNʧ��, er: %d", ret);
        sprintf(getMachineType_str_, "-@#%d", ret);
        return getMachineType_str_;
    }

    strcpy(getMachineType_str_, (char*)sn);
    return getMachineType_str_;
}

int PSBCSTDZDeviceSTAMPDeviceApp::checkPaperDoorState(void)
{
    WriteLog(4, "checkPaperDoorState->IN");

    ExitIfInMaintain();

    // ��ȡ��״̬(len = 4)
    // P1:   ��ֽ��״̬  0 �رգ�1 ������ 2������
    // P2:   ������״̬��ͬ��
    // P3:   ��е��״̬��ͬ��
    // P4:   ����״̬��ͬ��

    char doors[4] = { 0 };
    int ret = FGetDoorsPresent(doors, sizeof(doors));
    if (0 != ret)
        return EC_API_FAIL;

    return doors[0] == 0 ? 2 : 1;
}

int PSBCSTDZDeviceSTAMPDeviceApp::checkBackDoorState(void)
{
    WriteLog(4, "checkBackDoorState->IN");

    // �ýӿڲ��ܵ���ExitIfInMaintain(����ȵ��ÿ���ȫ�Žӿ�, ��ᱻ�Զ��ر�, ��ô�жϰ�ȫ��״̬�����).

    char doors[4] = { 0 };
    int ret = FGetDoorsPresent(doors, sizeof(doors));
    if (0 != ret)
        return EC_API_FAIL;

    // �Ե�����Ϊ�ж�����
    return doors[1] == 0 ? 2 : 1;
}

int PSBCSTDZDeviceSTAMPDeviceApp::lockPrinter(void)
{
    WriteLog(4, "lockPrinter->IN");

    ExitIfInMaintain();

    return Lock();
}

int PSBCSTDZDeviceSTAMPDeviceApp::unLockPrinter(void)
{
    WriteLog(4, "unLockPrinter->IN");
    ExitIfInMaintain();

    return Unlock();
}

int PSBCSTDZDeviceSTAMPDeviceApp::checkLockState(void)
{
    WriteLog(4, "checkLockState->IN");
    ExitIfInMaintain();

    return IsLocked() ? 0 : -1;
}

// ������ͷ������
int PSBCSTDZDeviceSTAMPDeviceApp::openVideoCapLight(void)
{
    WriteLog(4, "openVideoCapLight->IN");

    ExitIfInMaintain();

    // ����ƿ���
    // light     --- ���������
    //              1 -- ��ȫ���ԱߵĲ����; 
    //              2 -- ƾ֤����ͷ�ԱߵĲ����
    // op        --- ����(0 -- ��; 1 -- ��)

    // ��������ȵ���
    // light         --- ���������
    //                  1 ��ȫ���ԱߵĲ����
    //                  2 ƾ֤����ͷ�ԱߵĲ����
    // brightness    --- ����ֵ(���鷶Χ 1-100, 1Ϊ����, 100Ϊ����)
    // int FLightBrightness(char light, char brightness);
    
    int ret = FLightCtrl(2, 1);
    if (0 != ret) {
        WriteLog(3, "openVideoCapLight->����ƴ�ʧ��, er: %d", ret);
        return EC_OPEN_CAMERA_LED_FAIL;
    }

    // ������ͷ����Ҫ��������
    return 0 != FLightBrightness(2, PSBCConfig::GetInst()->brightness_) ? EC_ADJUST_LED_FAIL : EC_SUC;
}

int PSBCSTDZDeviceSTAMPDeviceApp::closeVideoCapLight(void)
{
    WriteLog(4, "closeVideoCapLight->IN");

    ExitIfInMaintain();
    return 0 != FLightCtrl(2, 0) ? EC_CLOSE_CAMERA_LED_FAIL : EC_SUC;
}

int PSBCSTDZDeviceSTAMPDeviceApp::connMachine(const char* seriaID)
{
    if (NULL == seriaID) {
        WriteLog(3, "connMachine->����Ϊ��");
        return EC_INVALID_PARAMETER;
    }

    WriteLog(4, "connMachine->IN, (seriaID) = (%s)", seriaID);

    ExitIfInMaintain();
    int ret = FOpenDev(NULL);
    if (0 != ret) {
        WriteLog(3, "connMachine->���豸ʧ��, er: %d", ret);
        return EC_OPEN_FAIL;
    }

    connected_ = true;

//     // �����к�д��ӡ�ػ�
//     ret = WriteBackupSN((unsigned char*)seriaID, strlen(seriaID));
//     if (0 != ret) {
//         WriteLog(3, "PSBCSTDZDeviceSTAMPDeviceApp::connMachine->д���к�ʧ��, er: %d", ret);
//         return EC_API_FAIL;
//     }

    return EC_SUC;
}

int PSBCSTDZDeviceSTAMPDeviceApp::disconnMachine(void)
{
    WriteLog(4, "disconnMachine->IN");

    ExitIfInMaintain();
    connected_ = false;
    return FCloseDev();
}

int PSBCSTDZDeviceSTAMPDeviceApp::isConnMachine(void)
{
    WriteLog(4, "isConnMachine->IN");

    ExitIfInMaintain();
    return connected_ ? 0 : -1;
}

char* PSBCSTDZDeviceSTAMPDeviceApp::readOpenBackDoorExceptionInfo(void)
{
    WriteLog(4, "readOpenBackDoorExceptionInfo->IN");

    ExitIfInMaintain();
    if (NULL == readOpenBackDoorExceptionInfo_str_)
        readOpenBackDoorExceptionInfo_str_ =
            new unsigned char[OPEN_SAFE_DOOR_EXCEPTION_SIZE * MAX_EXCEPTION_OPEN_COUNT + 1];

    memset(
        readOpenBackDoorExceptionInfo_str_,
        0x0,
        OPEN_SAFE_DOOR_EXCEPTION_SIZE * MAX_EXCEPTION_OPEN_COUNT + 1);

    // ���Ѽ�¼����
    unsigned char len = 0;
    unsigned char mark[2] = { 0 };
    int ret = ReadStamperMem(
        OPEN_SAFE_DOOR_EXCEPTION_MARK_OFFSET,
        OPEN_SAFE_DOOR_EXCEPTION_MARK_SIZE,
        mark,
        len);
    if (0 != ret)
        return (char*)readOpenBackDoorExceptionInfo_str_;

    // ����ת��
    int recorded = strtol((char*)&mark[0], NULL, 16);

    // ����쳣��¼�Ѿ����
    if (0 == recorded) {
        WriteLog(3, "readOpenBackDoorExceptionInfo->�쳣��¼��Ϣ�ѱ����");
        return (char*)readOpenBackDoorExceptionInfo_str_;
    }

    unsigned char* data = readOpenBackDoorExceptionInfo_str_;
    for (int i = 0; i < recorded; ++i) {
        unsigned char tmp[17] = { 0 };
        ret = ReadStamperMem(
            OPEN_SAFE_DOOR_EXCEPTION_OFFSET + i * OPEN_SAFE_DOOR_EXCEPTION_SIZE,
            OPEN_SAFE_DOOR_EXCEPTION_SIZE,
            tmp,
            len);
        if (0 == ret) {
            strcat((char*)data, (char*)tmp);
        }
    }

    return (char*)data;
}

int PSBCSTDZDeviceSTAMPDeviceApp::delOpenBackDoorExceptionInfo(void)
{
    WriteLog(4, "delOpenBackDoorExceptionInfo->IN");

    ExitIfInMaintain();
    char data[] = { 0x30 };
    int ret = WriteIntoStamper(
        OPEN_SAFE_DOOR_EXCEPTION_MARK_OFFSET,
        (unsigned char*)data,
        1);

    unsigned char buf[30] = { 0 };
    ret = WriteIntoStamper(
        OPEN_SAFE_DOOR_EXCEPTION_OFFSET,
        buf,
        24);

    return ret;
}

//////////////////////////// ����ͷAPI //////////////////////////////////

// ������ͷ
int PSBCSTDZDeviceSTAMPDeviceApp::openVideoCap(void)
{
    WriteLog(4, "openVideoCap->IN");

    if (video_opened_)
        return 0;

    int ret1 = OpenCamera(PAPERCAMERA);
    if (0 != ret1)
        WriteLog(3, "openVideoCap->��ƾ֤����ͷʧ��, er: %d", 
            ret1);

    int ret2 = SetResolution(
        PAPERCAMERA,
        PSBCConfig::GetInst()->resolution_width_,
        PSBCConfig::GetInst()->resolution_height_);
    if (0 != ret2)
        WriteLog(3, "openVideoCap->����ƾ֤����ͷ�ֱ���ʧ��, er: %d",
            ret2);

    if (0 == ret1 && 0 == ret2)
        video_opened_ = true;

    return 0;
}

int PSBCSTDZDeviceSTAMPDeviceApp::setVedioProperties(
    int brightness,
    int constrast,
    int hue,
    int saturation,
    int sharpness,
    int whitebalance,
    int gain)
{
    WriteLog(4, "setVedioProperties->IN");

    int set_bright = SetParameter(
        PAPERCAMERA, 
        CAMPARAM::brightness,
        brightness);

    int set_con = SetParameter(
        PAPERCAMERA,
        CAMPARAM::contrast,
        contrast);

    int set_hue = SetParameter(
        PAPERCAMERA,
        CAMPARAM::hue,
        hue);

    int set_saturation = SetParameter(
        PAPERCAMERA,
        CAMPARAM::saturation,
        saturation);

    int set_sharpness = SetParameter(
        PAPERCAMERA,
        CAMPARAM::sharpness,
        sharpness);

    int set_whilebalance = SetParameter(
        PAPERCAMERA,
        CAMPARAM::whitebalance,
        whitebalance);

    int set_exposure = SetParameter(
        PAPERCAMERA,
        CAMPARAM::expouse,
        gain);

    return 0 == (set_bright | set_con | set_hue | set_saturation | set_sharpness | 
        set_whilebalance | set_exposure) ? EC_SUC : EC_SET_CAMERA_PARAM_FAIL;
}

int getSystemTime(int& year, int& month, int& date)
{
    time_t timer;
    time(&timer);
    tm* t_tm = localtime(&timer);

    year = t_tm->tm_year + 1900;
    month = t_tm->tm_mon + 1;
    date = t_tm->tm_mday;
    return 0;
}

int PSBCSTDZDeviceSTAMPDeviceApp::getImageFormat(
    const char* filePath,   // ��ͼ·��
    int type,
    int isEraseBorder)
{
    if (NULL == filePath) {
        WriteLog(3, "getImageFormat->·��Ϊ��");
        return EC_INVALID_PARAMETER;
    }

    if (type != 0 && type != 1 && type != 2) {
        WriteLog(3, "getImageFormat->ͼƬ���Ͳ���(%d)�Ƿ�", type);
        return EC_INVALID_PARAMETER;
    }

    if (isEraseBorder != 0 && isEraseBorder != 1) {
        WriteLog(3, "getImageFormat->ͼƬ�������(%d)�Ƿ�", isEraseBorder);
        return EC_INVALID_PARAMETER;
    }

    WriteLog(4, "getImageFormat->IN, (filePaht, type, isEraseBorder)"
        " = (%s, %d, %d)",
        filePath,
        type,
        isEraseBorder);

    // ������ͷ��������ͷ�����
    openVideoCap();
    openVideoCapLight();

    // ��ʱ��Ϊ�ļ���
    int year = 0;
    int month = 0;
    int date = 0;
    getSystemTime(year, month, date);
    char file_name[32] = { 0 };
    sprintf_s(file_name, "%d%d%d", year, month, date);

    std::string working_path;
    GetMoudulePath(working_path);
    char file_path[MAX_PATH] = { 0 };
    sprintf_s(file_path, "%s\\tmp\\%s.jpg", working_path.c_str(), file_name);

	std::string src_path(file_path); // Դͼ·����
    src_image_ = src_path;

	int ret = CapturePhoto(
		PAPERCAMERA, 
		CvtType(type), 
		(char*)src_path.c_str());
    if (0 != ret) {
        WriteLog(3, "getImageFormat->ԭͼ·��: %s, ����ʧ��, er: %d", 
            src_path.c_str(),
            ret);
        return EC_CAPTURE_FAIL;
    }

    char dst_path[MAX_PATH] = { 0 };
    memcpy(dst_path, filePath, strlen(filePath));
    // ͼƬ�����д���, ֻ�Ǹ���ͼƬ
    if (isEraseBorder == 0) {
        CopyFile(src_path, dst_path);
    } else {
        // ��ƫȥ�ڱ�
        ret = CutImgEdgeEx(src_path.c_str(), dst_path);
        if (0 != ret) {
            WriteLog(3, "getImageFormat->��ƫȥ�ڱ�ʧ��, er: %d", ret);
            return EC_IMG_PROCESS_FAIL;
        }
    }

	return EC_SUC;
}

int PSBCSTDZDeviceSTAMPDeviceApp::revolveImg(
    const char*     filePath, 
    const char*     targetPath, 
    int             angle)
{
    WriteLog(4, "revolveImg->IN");

    return RotateImg(filePath, angle, targetPath);
}

// �ر�ƾ֤����ͷ
int PSBCSTDZDeviceSTAMPDeviceApp::closeVideoCap(void)
{
    WriteLog(4, "closeVideoCap->IN");

    video_opened_ = false;
    return 0;
}

int PSBCSTDZDeviceSTAMPDeviceApp::checkVideoState(void)
{
    WriteLog(4, "checkVideoState->IN");

    return video_opened_ ? 1 : 2;
}

//////////////////////////////////////////////////////////////////////////

// slotNumAndStampId    --- ����: (1:00000000001a;2:00000000002b;3:0...)
bool PSBCSTDZDeviceSTAMPDeviceApp::ParseSlotAndStamperID(
    const char* slotNumAndStampId,
    std::map<int, std::string>& slot_stamper)
{
    char buf[128] = { 0 };
    strcpy(buf, slotNumAndStampId);
    char *token = std::strtok(buf, ";"); // strtok��ı�buf
    while (token != NULL) {
        std::string str = token;
        size_t comma = str.find_first_of(":");
        if (comma != std::string::npos) {
            int slot = atoi(str.substr(0, comma + 1).c_str());
            std::string stamper = str.substr(comma + 1, std::string::npos);
            std::pair<std::map<int, std::string>::iterator, bool> ret = 
                slot_stamper.insert(std::make_pair(slot, stamper));
            if (!ret.second)
                return false;
        }

        token = std::strtok(NULL, ";");
    }

    return true;
}

// ��ԭͼ��ӡ��������ת��Ϊ�豸(ӡ�ػ�)��ӡ����(����)
Point* PSBCSTDZDeviceSTAMPDeviceApp::GetSealCoord(int nX, int nY)
{
    int dminx = 3;          //2//6
    int dminy = 60;         //56//60
    int dmaxx = 260;        //270//270
    int dmaxy = 230;        // 250//239
    int w = dmaxx - dminx;  //--ӡ��У׼λ�����X-ӡ��У׼λ����СX ����=239
    int h = dmaxy - dminy;  //--ӡ��У׼λ�����Y-ӡ��У׼λ����СY ����=182
    int x0 = nX;            //--ԭ������X����
    int y0 = nY;            //--ԭ������Y����

    const PSBCConfig* config = PSBCConfig::GetInst();
    int x1 = /*config->check_pt1_.x*/1929;              //--A4������СX���� ���� ���Ͻ�����
    int y1 = /*config->check_pt1_.y*/139;              //--A4������СY���� ����

    int x2 = /*config->check_pt3_.x*/296;              //--[===[A4�������X���� ����]===] ���½�����
    int y2 = /*config->check_pt3_.y*/1221;              //--[===[A4�������Y���� ����]===]
    WriteLog(4, "GetSealCoord->���Ͻ�(%d, %d), ���½�(%d, %d)",
        x1, y1,
        x2, y2);

    // ��ȡУ׼������
    //         std::vector<struct Point*> VerifyPoists;
    //         unsigned short buffer[10] = { 0 };
    //         int ret = CalibrationPoint(buffer, 10);
    //         if (ret == 0) {
    //             for (int i = 0; i < 5; ++i) {
    //                 struct Point* pt = new Point;
    //                 pt->x = buffer[i];
    //                 pt->y = buffer[i + 1];
    //                 VerifyPoists.push_back(pt);
    //             }
    //         } else {
    //             Log::WriteLog(LL_DEBUG, "δ��ȡ��У׼������,ʹ��ϵͳĬ��ֵ");
    //         }
    // 
    //         if (VerifyPoists.size() > 4 && VerifyPoists.at(1)->x != 65535 &&
    //             VerifyPoists.at(1)->y != 65535) {
    //             // ����, ����(1), ����, ����(3), �м�
    //             x1 = VerifyPoists[1]->x;
    //             y1 = VerifyPoists[1]->y;
    //             x2 = VerifyPoists[3]->x;
    //             y2 = VerifyPoists[3]->y;
    // 
    //             for (int i = 0; i < VerifyPoists.size(); ++i) {
    //                 delete VerifyPoists.at(i);
    //             }
    //         } else {
    //             x1 = MC::SvrConfig::GetInst()->check_pt2_.x;
    //             y1 = MC::SvrConfig::GetInst()->check_pt2_.y;
    //             x2 = MC::SvrConfig::GetInst()->check_pt4_.x;;
    //             y2 = MC::SvrConfig::GetInst()->check_pt4_.y;
    //         }

    // ��������
    double dRateX = (double)(fabs(float(x2 - x1)) * 1000) / (double)(fabs(float(dmaxx - dminx)) * 1000); // 7.85
    double dRateY = (double)(fabs(float(y2 - y1)) * 1000) / (double)(fabs(float(dmaxy - dminy)) * 1000); // 7.88
    double devX = (double)(fabs(float(x1 - nX)) * 1000) / (double)(dRateX * 1000) + dminx;
    double devY = (double)(fabs(float(y1 - nY)) * 1000) / (double)(dRateY * 1000) + dminy;
    int x = ceil(devX);
    int y = ceil(devY);

    bool bFix = false;
    if (x < 1) {
        x = 3;
        bFix = true;
    }
    if (x > 260) {
        x = 260;
        bFix = true;
    }
    if (y < 56) {
        y = 60;
        bFix = true;
    }
    if (y > 230) {
        y = 230;
        bFix = true;
    }

    if (bFix) {
        WriteLog(4, "�����豸��ӡλ��, Device({2},{3})", nX, nY, x, y);
    }

    return new Point(x, y);
}

ErrorCode PSBCSTDZDeviceSTAMPDeviceApp::CheckMachineNum(const char* machine)
{
    unsigned char id[22] = { 0 };
    int ret = ReadStamperIdentifier(id, 21);
    if (0 != ret)
        return EC_API_FAIL;

    if (0 != strcmp((char*)id, machine)) {
        WriteLog(3, "CheckMachineNum->�豸��Ų�ƥ��, ����: %s, ����: %s",
            id,
            machine);
        return EC_MACHINE_MISMATCH;
    }

    return EC_SUC;
}

void PSBCSTDZDeviceSTAMPDeviceApp::ExitIfInMaintain()
{
    if (!init_)
        FOpenDev(NULL);

    unsigned char status[24] = { 0 };
    int ret = FGetDevStatus(status, 24);
    if (0 != ret)
        return;

    // �����ά��ģʽ
    if (status[1] == 7) {
        SetStampMap();
        FCloseDoorSafe();   //  �ص�����
        FQuitMaintainMode();
    }
}

bool PSBCSTDZDeviceSTAMPDeviceApp::CopyFile(std::string strFrom,std::string strTo)
{
	int nFromLen = strFrom.length();
    int nToLen = strTo.length();
    char* pFrom = new char[nFromLen+2];
    char* pTo = new char[nToLen+2];
    strcpy(pFrom,strFrom.c_str());
    strcpy(pTo,strTo.c_str());
    pFrom[nFromLen+1]='\0';
    pTo[nToLen+1]='\0';

    SHFILEOPSTRUCT FileOp={0};
    FileOp.fFlags = FOF_NOCONFIRMATION|   //������ȷ�϶Ի���
        FOF_NOCONFIRMMKDIR ; //��Ҫʱֱ�Ӵ���һ���ļ���,�����û�ȷ��
    FileOp.pFrom = pFrom;
    FileOp.pTo = pTo;
    FileOp.wFunc = FO_COPY;
    bool bResult = (SHFileOperation(&FileOp) == 0);
    delete []pFrom;
    delete []pTo;
    return bResult;
}
