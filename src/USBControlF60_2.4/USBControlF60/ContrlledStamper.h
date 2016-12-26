#pragma once
#include "WLock.h"
#include "USBProtocol.h"
#include "USBControlF60.h"
#include <map>

struct spoint 
{
   double  _x;
   double  _y;
};
//����

class CCommunicateToUSB;
class CContrlledStamper
{
public:
	CContrlledStamper(void);
	~CContrlledStamper(void);

private:
private:
    Mutex send_mtx_;

	CRITICAL_SECTION m_csIORes;
static	CCommunicateToUSB* m_USB;
	string m_strFileBin;

	int SendCommand(SendPackage* sPackage, ReceivePackage* rPackage);
	int SendCommand(unsigned char cmd, unsigned char paramlen = 0, unsigned char *params = 0, void* pRetData = NULL, int len=0);
	int GetStamperStatus();
public:
	int firewareUpdate(unsigned char cmd, unsigned char* data=NULL, int len=0);
	static int _stdcall DevConnectCallBack(const char* DevPath, unsigned int uMsg);
public:
	int RegisterDevCallBack(pfnDevMsgCallBack pfn);
	int OpenDev(const char *file);
	int CloseDev(void);
	int QuitMaintainMode(void);
	int Restart(void);
	int GetSystemMsg(char* pRtn, int nLen);
	int GetFirwareVer(OUT char* strVer, int len);
	int SetFirwareSN(char* strSN, int len);
	int GetFirwareSN(OUT char* strSN, int len);
	int GetDevStatus(OUT unsigned char* strStatus, int len);
	int MaintenanceMode(void);
	int GetInfraRedStatus(OUT char* strInfraRed, int len);
	int GetSealPresent(OUT char* strSealStatus, int len);
	int GetDoorsPresent(OUT char* strDoorsStatus, int len);
	int OpenDoorPaper(void);
	int OpenDoorSafe(void);
	int CloseDoorSafe(void);
	int LinghtCtrl(char light, int op);
	int MoveX(unsigned short x_point);
	int MoveY(unsigned short y_point);
	int TurnSeal(unsigned short angle);
	int StartStamper(STAMPERPARAM *pstamperparam);
	int SelectStamper(unsigned int serial, unsigned int seal_id, char isPadInk);
	int CancleStamper(void);
	int BeepCtrl(char beep, char interval);
	int LightBrightness(char light, char brightness);
	int SealBack(void);
	int InTestMode(void);
	int OutTestMode(void);
	int GetMacAdress(char num, OUT unsigned char* strmac, int len);	
	int BindMac(char op, char num, char* strmac, int len);

	int SetDevCode(char* code, int len);
	int GetDevCode(OUT char* code, int len);

	//RFID����
	int GetRfidInfor(char* code, int len);

	int CContrlledStamper::DebugLogSwitch(char op);

	//ӡ��У׼
	int Calibration( char* points,int len);
	int CalculatePos(double* x1, double* y1, double* x2, double* y2, double* scalex,double*scaley);
	int STCalculatePosition(int stamperPointX,int stanperPointY,char* points,int len);
	int CalculatePosition(int stamperPointX,int stanperPointY,char* points,int len);
	// �����������
	int CalculateStampePoints();
	int CalibrationMutiple(char * points,int len);
	int CalibrationEx(char * pStampid,char *points,int len);
	int SetAlarm(char alarm,char operation);
	//����ӡ��ӳ���
	int SetStampMap(unsigned char* mapin,int len);
	//��ȡӡ��ӳ���
	int  GetStampMap(char* mapout,int len);

	//��ȡӡ����Ч��Χ
	int GetPhsicalRange(char * phsicalOut,int len);

    int GetStorageCapacity(unsigned char& version, unsigned short& mem_size);
    int WriteIntoStamper(unsigned short offset, const unsigned char* data, unsigned short len);
    int ReadStamperMem(unsigned short offset, unsigned short size,
        unsigned char* data, unsigned char& len);
    int SelectStamper(unsigned char stamper);
    int GetStamperID(unsigned char stamper, unsigned int& rfid);

    int GetStamper(unsigned int rfid, unsigned char& stamper);

    int EnterAuthMode();

    int ExitAuthMode();

    int EnableFactory(unsigned char enable);

    int VerifyKey(char key_type, const unsigned char* key, unsigned char len = 6);

    int OperateBlock(unsigned char block);

    int ReadBlock(unsigned char block, char* data, unsigned char len);

    int WriteBlock(unsigned char block, char* data, unsigned char len);

    int ReadAllRFID(unsigned int* rfids, unsigned char len, unsigned char* stampers);

    int ReadAlarmVoltage(unsigned char* voltage);

    int ClearStatistic();

    int Reset();

    int Confirm(
        unsigned int serial,
        unsigned int rfid,
        char isPadInk,
        short x_point,
        short y_point,
        short angle,
        short w_time,
        unsigned char type = 0); //������Ϣȷ��
    
    int ReadStamp(unsigned char* info, unsigned char len = 47); //��������Ϣ

    //���ò��ſ�����ʾ��Ϣ
    int SetSideDoor(unsigned short keep_open, unsigned short timeout);

    //������ֽ�ſ�������ʱ��ʾ, ��λ��
    int SetPaperDoor(unsigned short timeout = 30);
    
    int ReadBackupSN(unsigned char* sn, unsigned char len = 48);

    int WriteBackupSN(const unsigned char* sn, unsigned char len = 48);

    int ReadAlarmStatus(char* door, char* vibration);

    int GetHardwareVer(char* version, unsigned char len = 255);

    int GetABCStamper(unsigned char stamper, char* id, unsigned char len);

    //����ũ�е��ӱ�ǩ��ȡ��Ӧ��rfid
    int GetRFID(const std::string& abc_id, unsigned int& rfid);

    int GetABCIndex(const std::string& abc_id, char& index);

private:
    std::map<int, std::string> stamper_abc_;    //stamper id(��1��ʼ)��ũ��Ҫ���ӡ��id��Ķ�Ӧ��ϵ

    std::map<std::string, unsigned int> abc_rfid_;  //ũ��Ҫ���ӡ��id��ʵ��ӡ��id���Ӧ��ϵ

    //index     --- ��1��ʼ
    std::string GetStamperABC(unsigned char index);
};

