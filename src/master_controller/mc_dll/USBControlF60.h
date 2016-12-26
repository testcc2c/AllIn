#ifndef USBCONTROLF60_API_H
#define USBCONTROLF60_API_H

#include <string>

// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� USBCONTROLF60_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// USBCONTROLF60_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifdef USBCONTROLF60_EXPORTS
#define USBCONTROLF60_API _declspec(dllexport)
#else
#define USBCONTROLF60_API _declspec(dllimport)
#endif


//�豸��ʧ�ܣ��������ݴ��󣬣�Ӧ��������������ļ�������λ��У�����
//�������ݷ���ʧ�ܣ�ϵͳ����

// ��������ֵ����
#define STF_SUCCESS									((int)0)  //�����ɹ�
#define STF_ERR_OPENDEVFAIL					        ((int)-1) //�豸��ʧ��
#define STF_ERR_SENDFAIL						    ((int)-2) //�������ݴ���
#define STF_ERR_RECVFAIL						    ((int)-3) //Ӧ�����
#define STF_ERR_COMMUNICATION				        ((int)-4) //Ӧ���������
#define STF_ERR_INVLIDATEBINFILE		            ((int)-5) //�����ļ�����
#define STF_ERR_FIREWARE_FILECHECK	                ((int)-6) //��λ��У�����
#define STF_INVALID_PARAMETER                       ((int)-7) //�����Ƿ�
#define STF_ERR_INTERNEL						    ((int)-99) //����ϵͳ����
#define STF_STAMPER_LOSS                            ((int)-100)//ȱ��
#define STF_INVALID_STAMPER                         ((int)-101)//�Ǳ�����ӡ��
#define STF_DUPLICATE_STAMPER                       ((int)-102)//ӡ��ID�ظ�
#define STF_STAMPER_SEQ_CHANGE                      ((int)-103)//ӡ��˳�����ı�
#define STF_ALLOCATE_MEM_FAIL                       ((int)-104)//�����ڴ�ʧ��
#define STF_WRITE_MAC_FAIL                          ((int)-105)//����MAC��ַʧ��
#define STF_READ_MAC_FAIL                           ((int)-106)//��ȡMAC��ַʧ��

#define OUT

//RFID���޸�
typedef struct _stamperparam{
    unsigned int        serial_number;  //������ˮ��
	char				seal[4];
	char				isPadInk; 

	unsigned short		x_point; 
	unsigned short		y_point; 
	unsigned short		angle;
	unsigned short		w_time; 
    unsigned char       type;           //���·�ʽ(0---��ͨ����, 1---�����)

	_stamperparam()
	{
        this->serial_number = 0;
		this->seal[0]		= 0;
		this->seal[1]		= 0;
		this->seal[2]		= 0;
		this->seal[3]		= 0;
		this->seal[4]		= 0;
		this->isPadInk		= 0;
		this->x_point		= 0; 
		this->y_point		= 0;
		this->angle			= 0;
		this->w_time		= 0;
        this->type          = 0;
	}

	_stamperparam& operator= (_stamperparam &p)
	{
        this->serial_number     = p.serial_number;
		strcpy_s(this->seal, p.seal);
		this->isPadInk			= p.isPadInk;
		this->x_point			= p.x_point; 
		this->y_point			= p.y_point;
		this->angle				= p.angle;
		this->w_time			= p.w_time;
        this->type              = p.type;
		return *this;
	}

}STAMPERPARAM, *PSTAMPERPARAM;

//�豸����״̬�ص�����
//DevPath   �豸·��
//uMsg		1 ����, 0 �Ͽ�
typedef int ( _stdcall *pDevConnectCallBack)(const char* DevPath, unsigned int uMsg);

/*USBͨ�Żص�����
	uMsg:
		0xA0:���¹�������ѹ֪ͨ
		0xA1:���¹����л�е�ֱۻص�ӡ���ߣ���ʾ��������
		0xA2:�������֪ͨ��wParam 0 �ɹ��� 1 ʧ��
		0xA3:���¹����� ӡ�µ���֪ͨ
		0xA4:ֽ�Źر�֪ͨ, (wParamΪ0��ʾ�Źر�֪ͨ)
        0xA5:���¹��̴���֪ͨ
        0xA6:���Źر�֪ͨ, (wParamΪ0��ʾ���Źر�֪ͨ; 1��ʾ���Ŵ�֪ͨ)
        0xA7:�����Źر�֪ͨ, (wParamΪ0��ʾ���ǹر�֪ͨ; 1��ʾ���Ǵ�֪ͨ)
        0xA8:����������֪ͨ
*/
#define STAMPER_DOWN				        (unsigned char)0xA0
#define STAMPER_ARMBACK						(unsigned char)0xA1
#define STAMPER_COMPLETE					(unsigned char)0xA2
#define STAMPER_SEALERR						(unsigned char)0xA3
#define STAMPER_PAPERDOORCLOSE		        (unsigned char)0xA4
#define STAMPER_ERROR                       (unsigned char)0xA5
#define STAMPER_SIDEDOOR_CLOSE              (unsigned char)0xA6
#define STAMPER_TOP_CLOSE                   (unsigned char)0xA7
#define STAMPER_ELEC_LOCK                   (unsigned char)0xA8

//����uMsg==STAMPER_COMPLETE(�������)ʱ, data��Ϊ��, lenΪ46, ���ӿ�Э���ĵ�����data,
//���Եõ�����ˮ�š�, "ӡ��ID��"��.
typedef int (_stdcall *pfnDevMsgCallBack)(unsigned int uMsg, unsigned int wParam, long lParam,
                                        unsigned char* data, unsigned char len);

#ifdef __cplusplus
extern "C"{
#endif

/** 
*  @brief    ע���豸�ص�����(�豸������Ͽ�֪ͨ)
*  @details  
*  @param    [pDevConnectCallBack] func   �ص�����
*  @return   =STF_SUCCESS
*  @remark
*/
USBCONTROLF60_API int F_RegisterDevCallBack(pDevConnectCallBack func);

/** 
*  @brief    ��־��¼
*  @details  
*  @param    level,��־�ȼ�
*            1--����
*            2--��ʾ
*            3--����
*            4--����
*  @param    [const char*] szLog   ��־����
*  @return   =STF_SUCCESS
*  @remark
*/
USBCONTROLF60_API void F_RecordLog(int level, const char* szLog);

 // �����Ǵ� USBControlF60.dll ������
 class USBCONTROLF60_API CUSBControlF60 {
 public:
	 CUSBControlF60(void);
	 ~CUSBControlF60(void);
 };

 extern USBCONTROLF60_API int nUSBControlF60;
 USBCONTROLF60_API int fnUSBControlF60(void);

 /** 
 *  @brief    ע��ص�����(���½��, ֽ�Źر�֪ͨ)
 *  @details  
 *  @param    [pfnDevMsgCallBack] pfn   �ص�������ַ
 *  @return   =STF_SUCCESS
 *  @remark
 */
USBCONTROLF60_API int FRegisterDevCallBack(pfnDevMsgCallBack pfn);

//���豸, ������Ч
USBCONTROLF60_API	int FOpenDev(const char *file);

//�ر��豸
USBCONTROLF60_API	int FCloseDev(void);

//0x01, �˳�ά��ģʽ
USBCONTROLF60_API	int FQuitMaintainMode(void);

//0x02, ����ӡ�ػ�����
USBCONTROLF60_API int FRestart(void);

//0x03, ��ȡϵͳ��Ϣ, ����Э��
USBCONTROLF60_API int FGetSystemMsg(char *pRtn, int nLen);

//0x04, ��ȡ�豸�̼��汾��(strVer, len=8)
USBCONTROLF60_API	int FGetFirwareVer(OUT char* strVer, int len);

//0x05, �����豸���к�(len=14)
USBCONTROLF60_API	int FSetFirwareSN(char* strSN, int len);

//0x06, ��ȡ�豸���к�(len=15)
//len       --- ����15���ֽڿռ�
USBCONTROLF60_API	int FGetFirwareSN(OUT char* strSN, int len);

//0x07, ��ѯ�豸״̬(len=14, ��ϸ��Э��)
USBCONTROLF60_API	int FGetDevStatus(OUT unsigned char* strStatus, int len);

//0x08, ����ά��ģʽ
USBCONTROLF60_API	int FMaintenanceMode(void);

//0x09, ��ȡ����״̬,len��Э��
USBCONTROLF60_API	int FGetInfraRedStatus(OUT char* strInfraRed, int len);

//0x0A, ��ȡӡ��״̬(len=30)
USBCONTROLF60_API int FGetSealPresent(OUT char* strSealStatus, int len);

//0x0B, ��ȡ��״̬(len = 4)
//P1:   ��ֽ��״̬  0 �رգ�1 ������ 2������
//P2:   ������״̬��ͬ��
//P3:   ��е��״̬��ͬ��
//P4:   ����״̬��ͬ��
USBCONTROLF60_API int FGetDoorsPresent(OUT char* strDoorsStatus, int len);

//0x0C, ����ֽ��
USBCONTROLF60_API	int FOpenDoorPaper();

//0x0D, �򿪰�ȫ��
USBCONTROLF60_API	int FOpenDoorSafe(void);

//0x0E, �رհ�ȫ��
USBCONTROLF60_API	int FCloseDoorSafe(void);

//0x0F, ����ƿ���
//light     --- ���������
//              1 -- ��ȫ���ԱߵĲ����; 
//              2 -- ƾ֤����ͷ�ԱߵĲ����
//op        --- ����(0 -- ��; 1 -- ��)
USBCONTROLF60_API	int FLightCtrl(char light, int op);

//0x10, X�ƶ�, ��Ҫ�ڲ���ģʽ��
USBCONTROLF60_API	int FMoveX(unsigned short x_point);

//0x11, Y�ƶ�
USBCONTROLF60_API	int FMoveY(unsigned short y_point);

//0x12, ת��
USBCONTROLF60_API	int FTurnSeal(unsigned short angle);

//0x13, ��ͨ����
USBCONTROLF60_API	int FStartStamperstrc(STAMPERPARAM *pstamperparam);

//����
USBCONTROLF60_API	int FStartStamper(
    unsigned int serial,
    char *seal, 
    char isPadInk,
    unsigned short x_point, 
    unsigned short y_point,
    unsigned short angle, 
    unsigned short w_time,
    unsigned char type = 0);

//ũ�нӿڸ���
//serial    --- ��ӡ��ˮ��
//id        --- ӡ�µ��ӱ�ǩ(STDZ + 8λ���)
//isPadInk  --- �Ƿ�ʹ��ӡ��
//x_point   --- ��ӡX����
//y_point   --- ��ӡY����
//angle     --- ��ӡ�Ƕ�
//w_time    --- ��ӡʱ��
//type      --- ��������(0---Ĭ����ͨ��, 1---�����)
USBCONTROLF60_API int FStartStamperABC(
    unsigned int serial,
    char* abc_id,
    char isPadInk,
    short x_point,
    short y_point,
    short angle,
    short w_time,
    unsigned char type = 0);

//��ӡ
//serial    --- ��ӡ��ˮ��
//sealNo    --- ӡ�±��[1-6]
//isPadInk  --- �Ƿ�ʹ��ӡ��
//x_point   --- ��ӡX����
//y_point   --- ��ӡY����
//angle     --- ��ӡ�Ƕ�
//w_time    --- ��ӡʱ��
//type      --- ��������(0---Ĭ����ͨ��, 1---�����)
USBCONTROLF60_API int FStartStamperEx(
    unsigned int serial,
    char sealNo, 
    char isPadInk,
    short x_point, 
    short y_point,
    short angle, 
    short w_time,
    unsigned char type = 0);

//0x14, ѡ�º��Ƿ�մӡ��
//serial    --- ��ӡ��ˮ��
//seal_id   --- ӡ��ID
//isPadInk  --- �Ƿ�պӡ��
USBCONTROLF60_API int FSelectStamper(
    unsigned int serial, 
    unsigned int seal_id, 
    char isPadInk);

//0x15, ȡ������
USBCONTROLF60_API int FCancleStamper(void);

//0x16, ����������
//beep      --- 0 �ر�; 1 ����; 2 �����
//interval  --- ��beep=2ʱ��ֵ��Ч, �����ʱ��(��λ��)
USBCONTROLF60_API	int FBeepCtrl(char beep, char interval);

//0x17, ��������ȵ���
//light         --- ���������
//                  1 ��ȫ���ԱߵĲ����
//                  2 ƾ֤����ͷ�ԱߵĲ����
//brightness    --- ����ֵ(���鷶Χ 1-100, 1Ϊ����, 100Ϊ����)
USBCONTROLF60_API	int FLightBrightness(char light, char brightness);

//0x18, ӡ�¹�λ
USBCONTROLF60_API	int FSealBack(void);

//0x19, ���빦�ܲ���ģʽ
USBCONTROLF60_API	int FInTestMode(void);

//0x1A, �˳����ܲ���ģʽ, �豸���Զ�����
USBCONTROLF60_API	int FOutTestMode(void);

//0x1B, ��ȡMac��ַ
//num       --- 1(��ȡ��һ��MAC��ַ),
//              2(�ڶ���MAC��ַ)
//strmac    --- ���ؾ����MAC��ַ
//len       --- ���MAC��ַ����, MAC��ַ���18���ֽ�
USBCONTROLF60_API int GetMacAdress(char num, OUT char* strmac, int len);

//0x1C, ��Mac��ַ
//op        --- 1(��MAC)
//              0(���MAC)
//num       --- ��ʾ�����ĸ�MAC(1, 2)
//strmac    --- MAC��ַ��
USBCONTROLF60_API	int FBindMac(char op, char num, char* strmac, int len);

//0x1D, ���ñ�������
//alarm     --- 0(���ű�����)
//              1(�񶯱�����)
//switchs   --- ����������
//              1(����);
//              0(�ر�)
USBCONTROLF60_API int SetAlarm(char alarm, char operation);

//0x1E, �����豸��֤��
//���֧������10���ֽڵ���֤��
USBCONTROLF60_API int SetDevCode(char* code, int len);

//0x1F, ��ȡ�豸��֤��
//��֤�������10���ֽ�
USBCONTROLF60_API int GetDevCode(OUT char* code, int len);

//0x20, �������ݵ�ӡ�»��洢����(���֧��512�ֽ�)
//������øýӿ����ƫ����150�Ժ�ʼд.
//
//offset    --- дƫ����
//data      --- ��д������
//len       --- ��д�����ݳ���
USBCONTROLF60_API int WriteIntoStamper(
    unsigned short offset,
    const unsigned char* data,
    unsigned char len);

//0x21, ��ȡӡ�»��ڵĴ洢������
//������øýӿ����ƫ����150�Ժ�ʼ��.
//
//offset    --- ��ƫ����
//size      --- ��������ݳ���
//data      --- ��Ŷ�ȡ��������
//len       --- ʵ�ʷ������ݳ���
USBCONTROLF60_API int ReadStamperMem(
    unsigned short offset,
    unsigned short size,
    unsigned char* data,
    unsigned char& len);

//0x22, �洢���汾�ż����ÿռ��С
//
//version   --- �洢���汾��
//memz_size --- �洢�����ÿռ�
USBCONTROLF60_API int GetStorageCapacity(unsigned char& version, unsigned short& mem_size);

//0x23, ������֤״̬, ĿǰĬ�Ϸ���-1(ʧ��)
USBCONTROLF60_API int EnterAuthMode();

//0x24, �˳���֤״̬, ĿǰĬ�Ϸ���-1(ʧ��)
USBCONTROLF60_API int ExitAuthMode();

//0x25, ѡȡӡ��
//�ýӿڹ���дӡ��RFIDʱ����
//
//stamper  --- ӡ�²�λ��,��0��ʼ
USBCONTROLF60_API int SelectStamper(unsigned char stamper);

//0x26, ����ӡ�²�λ�Ż�ȡ��Ӧ��RFID��
//
//stamper   --- ӡ�²�λ��, (�±��0��ʼ)
//rfid      --- ��Ӧ��rfid��
USBCONTROLF60_API int GetStamperID(unsigned char stamper, unsigned int& rfid);

//����ӡ�²�λ�Ż�ȡ��ũ��ָ�������ӡ�µ��ӱ�ǩ(STDZ + 8λ���ȱ��)
//
//stamper   --- ӡ�²�λ��, ��1��ʼ
//id        --- ũ��ӡ�µ��ӱ�ǩ, STDZ00000001, 12���ֽ�
//len       --- ũ�е��ӱ�ǩ����, ����13���ֽ�
//
//����ֵ:
//      0   --- �ɹ�
//      1   --- ��ȡũ��ӡ�µ��ӱ�ǩʧ��
//      2   --- ָ��ӡ�º�δ��ũ��Ҫ��д���ӡ�±��
USBCONTROLF60_API int GetABCStamper(unsigned char stamper, char* id, unsigned char len);

//����ũ��ָ�������ӡ�µ��ӱ�ǩ��ȡӡ�²�λ��
//
//id        --- ũ�е��ӱ�ǩ, ��'STDZ00000002'
//index     --- ӡ�²�λ��, ��1��ʼ
//
//����ֵ:
//      0   --- �ɹ�
//      1   --- ʧ��
USBCONTROLF60_API int GetABCStamperIndex(const char* abc_id, char* index);

//0x27, ����ָ����ľ���, ������ʱҪ������������:
//1. ��ѡ��(SelectStamper),
//2. ������(GetStamperID),
//3. ���õ�ַ(OperateBlock),
//4. ����Ƚ�(VerifyKey),
//5. ����д(WriteBlock, ReadBlock)
USBCONTROLF60_API int OperateBlock(unsigned char block);

//0x28, ��֤��Կ
//
//key_type  --- ��Կ����(A��B����)
//              0��ӦA����
//              1��ӦB����
//key       --- key_type��Ӧ����Կ
//len       --- ��Կ���ݳ���(6�ֽ�)
USBCONTROLF60_API int VerifyKey(char key_type, const unsigned char* key, unsigned char len = 6);

//0x29, ��ָ����
//block     --- ���
//data      --- ��ȡ�ɹ��󱣴��ȡ������
//len       --- ���ݳ���(Ӧ����17���ֽ�)
USBCONTROLF60_API int ReadBlock(unsigned char block, unsigned char* data, unsigned char len);

//0x2A, дָ����
//block     --- ���
//data      --- ��д������
//len       --- ���ݳ���(���֧��д17���ֽ�)
USBCONTROLF60_API int WriteBlock(unsigned char block, unsigned char* data, unsigned char len);

//0x2B, ��ȡ������·�Χ, ���������Э��
USBCONTROLF60_API int   GetPhsicalRange(char * phsicalOut, int len);

//0x2C, ����ӡ��ӳ���ϵ
USBCONTROLF60_API int   SetStampMap();

//0x2D, ��ȡӡ��ӳ���ϵ
//len       --- ���ݳ���, 52�ֽ�, ÿ���²�ռ��8���ֽ�(ǰ4���ֽ�Ϊ��ID, ��4���ֽ�Ϊ������Ϣ),
//              ���4�ֽ�Ϊ32λ���ͺ�У����ȡ��ֵ
USBCONTROLF60_API int   GetStampMap(char* mapout, int len);

//0x30, ��ȡ��ǰ����RFID, ��������, ��7��rfid, rfidֵΪ���ֽ��޷�������
//rfids     --- ���rfidֵ, Ԫ��ֵΪ0��ʾ����, ��0Ϊ��Ӧ��RFID��
//len       --- rfid����, ����7��rfid(��7��Ϊ����rfid)
//stampers  --- ����ʵ�ʵ�rfid�¸���
USBCONTROLF60_API int ReadAllRFID(unsigned int* rfids, unsigned char len, unsigned char* stampers);

//0x31, ����������ص�ѹֵ
//
//����ֵΪ0ʱ��ѹֵ��Ч, ��λΪ0.1��
USBCONTROLF60_API int ReadAlarmVoltage(unsigned char* voltage);

//0x32, ͳ����Ϣ����
USBCONTROLF60_API int ClearStatistic();

//0x33, ��λ, USB����Ͽ�
USBCONTROLF60_API int Reset();

//0x34, ȷ�ϸ���
//��ѡ��, ��ȷ�ϸ���
//�ȵ��ýӿ�GetStamperID��ӡ�ºŵõ�ӡ��RFID, �ٵ��ýӿ�FSelectStamper���ѡ��, ���
//���øýӿ�Confirmʵ�ָ���ȷ����ɸ���.
//
//serial    --- ��ˮ��,����ˮ����ӿ�FSelectStamper�������ˮ�ű���һ��
//rfid      --- ӡ��ID��,���ýӿ�GetStamperID���
USBCONTROLF60_API int Confirm(
    unsigned int serial,
    unsigned int rfid,
    char isPadInk,
    short x_point,
    short y_point,
    short angle,
    short w_time,
    unsigned char type = 0);

//0x35, ��������Ϣ, ��ϸ���ݸ�ʽ��Э��
USBCONTROLF60_API int ReadStamp(unsigned char* info, unsigned char len = 47);

//0x36, ���ò��ſ�����ʾ��Ϣ
//keep_open     --- �򿪲��ź������ִ򿪵�ʱ��, ��λ��
//timeout       --- ָ��ʱ����δ�رղ���, ��������ʾ, ��λ��
USBCONTROLF60_API int SetSideDoor(unsigned short keep_open, unsigned short timeout);

//0x37, ������ֽ�ſ�����ʱ��ʾʱ��
//timeout   --- ��ʱδ������ʾ,Ĭ��30��
USBCONTROLF60_API int SetPaperDoor(unsigned short timeout = 30);

//0x38, ��ȡ����������״̬(�����񶯱������ű���)
//
//door          --- �ű���, 0�ǹ�, 1�ǿ�
//vibration     --- �񶯱���, 0�ǹ�, 1�ǿ�
//
//����ֵ:
//      0: ��������״̬�ɹ�
//      1: ʧ��
//      2: æ
USBCONTROLF60_API int ReadAlarmStatus(char* door, char* vibration);

//0x39, ��ȡӲ���汾���ַ���, ��ʵ�ʰ汾������������"master_2.41"
//version       --- �汾���ַ���
//len           --- ��汾�ų���(255���ֽ�)
USBCONTROLF60_API int GetHardwareVer(char* version, unsigned char len = 255);

//0x51, ��������ģʽ, ��������Ҫ����Ҳ��ѭ�����²���
//enable    --- 1(��������ģʽ), 0(�رչ���ģʽ)
USBCONTROLF60_API int EnableFactoryMode(unsigned char enable);

//0x52, USB������Ϣ�������
//op    --- 1 ��; 0 ��
USBCONTROLF60_API int FDebugLogSwitch(char op);

//(0xB1~0xB5) �������ݽӿ�
// ������ݣ����ݳ���
USBCONTROLF60_API int FfirewareUpdate(unsigned char cmd, unsigned char* data, int len);

//0xD0, �����ð����к�, Ŀǰ����Ҳ����ʹ�ø�����
USBCONTROLF60_API int ReadBackupSN(unsigned char* sn, unsigned char len = 48);

//0xD1, д���ð����к�, Ŀǰ����Ҳ����ʹ�ø�����
USBCONTROLF60_API int WriteBackupSN(const unsigned char* sn, unsigned char len = 48);

//ӡ��У׼ 
USBCONTROLF60_API  int Calibration( char* points, int len);

USBCONTROLF60_API int  CalculatePos(double* x1, double* y1, double* x2, double* y2, 
    double* scalex,double*scaley);

USBCONTROLF60_API int  CalculatePosition(int stamperPointX,int stanperPointY,char* points,int len);

USBCONTROLF60_API  int  CalibrationMutiple(char * points,int len);

//ӡ��У׼ũ�� 
//pStampid      --- ӡ��ID
USBCONTROLF60_API int CalibrationEx(char * pStampid, char *points, int len);

//�洢MAC��ַ, ��������β�ַ�('\0')
//MAC��ַ��: "30-3A-64-D6-FD-30"
//֧��ֱ��д��(ռ��17���ֽ�), ����ת��Ϊʮ����д��"48-58-100-214-253-48"(ռ��11���ֽ�)
USBCONTROLF60_API int WriteMAC(
    const unsigned char* mac1, 
    const unsigned char* mac2, 
    unsigned char max_mac1_len = 17,
    unsigned char max_mac2_len = 17);

//��ȡMAC��ַ
//mac1,mac2     --- ��Ŷ�ȡ���Ķ�ӦMAC��ַ
//max_len       --- ���鳤��, ����Ϊ18(MAC��ַ���֧��17���ַ�, �����Զ����һ����β�ַ�)
USBCONTROLF60_API int ReadMAC(
    unsigned char* mac1, 
    unsigned char* mac2, 
    unsigned char max_len = 18);

//�洢�豸keyֵ
USBCONTROLF60_API int WriteKey(const unsigned char* key, unsigned char key_len = 16);

//��ȡ�豸Key
//key_len       --- ����17���ֽڿռ�
USBCONTROLF60_API int ReadKey(unsigned char* key, unsigned char key_len = 17);

//�洢ͼ��ת������
//x,y����, 8�ֽڸ�����
USBCONTROLF60_API int WriteImageConvRatio(float* x, float* y);

//��ȡͼ��ת������
USBCONTROLF60_API int ReadImageConvRatio(float* x, float* y);

//����ӡ��RFID�Ż�ȡ��Ӧ�Ĳ�λ��
//
//rfid      --- rfid��
//stamper   --- rfid��Ӧ��ӡ�²�λ��, ��1��ʼ
USBCONTROLF60_API int GetStamper(unsigned int rfid, unsigned char& stamper);

//�洢У׼������
//����Ӳ���ߴ��С,ÿ��У׼���x,yֵ��2���ֽڴ�ż���, ��5��У׼��.
//points    --- ˳����ÿ�����x,yֵ,��x1,y1,x2,y2...x5,y5
//len       --- ���ݳ���
USBCONTROLF60_API int WriteCalibrationPoint(unsigned short* points, unsigned char len = 10);

//��ȡУ׼������
//���ݸ�ʽ�μ��洢У׼�����ݽӿ�
USBCONTROLF60_API int CalibrationPoint(unsigned short* points, unsigned char len = 10);

//���ӡ����Ϣ
//����ǰӡ��id���豸�洢��ӡ��id��Ϣ���бȶԣ�
//���ݷ���ֵ����֪����ǰ�豸�Ƿ����,�������õľ���ԭ��,�ϲ��������Ĳ���
//����ֵ:
//      STF_STAMPER_LOSS        //ȱ��
//      STF_INVALID_STAMPER     //���ַǱ�����ӡ��
//      STF_DUPLICATE_STAMPER   //ӡ��ID�ظ�
//      STF_STAMPER_SEQ_CHANGE  //ӡ��˳�����ı�,�������⴦��
USBCONTROLF60_API int CheckStampers();

//ӡ��������״̬
USBCONTROLF60_API bool IsLocked();

//����ӡ����
USBCONTROLF60_API int Lock();

//����ӡ����
USBCONTROLF60_API int Unlock();

//дӡ���Ǳ��
//id        --- ӡ���Ǳ��
//len       --- ��ų���, ���֧��20���ֽ�
USBCONTROLF60_API int WriteStamperIdentifier(const unsigned char* id, unsigned char len);

//��ȡӡ���Ǳ��
//id        --- ����ӡ���Ǳ��
//len       --- ��СҪ��20���ֽڿռ�
USBCONTROLF60_API int ReadStamperIdentifier(unsigned char* id, unsigned char len);

#ifdef __cplusplus
 }
#endif

#endif
