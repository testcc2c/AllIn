#ifndef _PSBC_STAMP_H
#define _PSBC_STAMP_H
#include <map>
#include <string>
using namespace std;




typedef int (*pinitializationMachine)(void);

/** No.2
* ����:	querySloatInfo	
* ����:	��ȡӡ����Ϣ
* ˵��:	0 ��ʾ����,�����ʾӡ�º�.
*
* ����:	
* @parm const char* machineNum ��ӡ�����
* @return	ʧ��:����ʧ����
*				�ɹ�:�����ַ��� ��ʽ: ��λ��:ӡ��ID;��λ��:ӡ��ID(0 ��ʾ����)... 
*				��(1:00000000001a;2:00000000002b;3:0...)
*/
typedef  char * (* pquerySealInfo)(const char* machineNum);

/** No.3
* ����:	querySloatInfo	
* ����:	��ȡ������Ϣ
* ˵��:	0 ��ʾ����,1 ��ʾ����
*
* ����:	
* @parm const char* machineNum ��ӡ�����
* @return	ʧ��:����ʧ����
*				�ɹ�:�����ַ��� ��ʽ: ��λ��:ӡ���Ƿ����;��λ��:ӡ���Ƿ���� (0 ��ʾ����,1 ��ʾ����)...
*				 ��(1:0;2:1;3:0...)
*/
typedef char* (*pquerySlotInfo)(const char* machineNum);

/** No.4
* ����:	initStamp	
* ����:	����ӡ����Ϣ
* ˵��:	slotNumAndStampId���Ȳ�����15*��������
*			
*
* ����:	
* @parm const char* machineNum ��ӡ�����
* @parm const char* slotNumAndStampId ��λ����ӡ��IDѭ����
*		��(1:00000000001a;2:00000000002b;3:0...)
* @return	�ɹ�: 0
*				ʧ��:-1
*/
typedef int (*pinitStamp)(const char* machineNum,const char* slotNumAndStampId);

/** No.5
* ����:	setAcrossPageSeal	
* ����:	���ñ��θ������,������Ч
* ˵��:	���ñ��θ��µ������������,ֻ�б����趨��Ч
*			
*
* ����:	
* @parm void
* @return	�ɹ�: 0
*				ʧ��:��0
*/
typedef int (*psetAcrossPageSeal)(void);

/** No.6
* ����:	setMachineNum	
* ����:	�����豸���
* ˵��:	�豸������ſ������޸�,�����޸Ŀ��ڵ��ô˽ӿ�ʱ����20λ���ڵ��ַ�����Ϊ�������
*
* ����:	
* @parm const char* machineNum �豸���(������12 λ)
* @return	�ɹ�: 0
*				ʧ��:��0
*/
typedef int (*psetMachineNum)(const char* machineNum);

/** No.7
* ����:	openPaperDoor	
* ����:	��ֽ��
* ˵��:	���豸ֽ���Ա����ƾ֤
*
* ����:	
* @parm void
* @return	�ɹ�: 0
*				ʧ��:��0
*/
typedef int (*popenPaperDoor)(void);

/** No.8
* ����:	checkManualPrintPara	
* ����:	��ӡ���ֹ���ӡ�����Ϸ����ж�
* ˵��:	�ֹ���ӡ�ĸ��������Ϊӡ�µ����ĵ����ͼƬ���Ͻ�,������Ϊ��λ
*			�������ж��ֹ���ӡ�����Ƿ���ֽ����Ч��Χ��,�������ֹ���ӡ����������ӡ
*			
*
* ����:	
* @parm int pointX ��ӡX����,��λΪ����
* @parm int pointY ��ӡY����,��λΪ����
* @parm int angle  ת�½Ƕ�(0-360)˳ʱ��
* @return	�Ϸ�: 0
*				�Ƿ�:-1
*/
typedef int (*pcheckManualPrintPara)( int pointX, int pointY, int angle);

/** No.9
* ����:	manualPrintStart	
* ����:	��ӡ���ֹ�
* ˵��:	ת����ĸ��������ͨ����������
*			�ֹ���ӡ���ü��ú�jpgͼ��ĸ��������Ϊӡ�µ����ĵ����ͼƬ���Ͻ�,������Ϊ��λ
*			
*
* ����:	
* @parm int printNum ���ۺ�
* @parm int pointX ��ӡX����,��λΪ����
* @parm int pointY ��ӡY����,��λΪ����
* @parm int angle  ת�½Ƕ�(0-360)˳ʱ��
* @return	�ɹ�: 0
*				ʧ��: ��0
*/
typedef int (*pmanualPrintStart)(int printNum, int pointX, int pointY, int angle);

/** No.10
* ����:	manualPrintStartByLight	
* ����:	��ӡ����������ӡ
* ˵��:	�ֹ���ӡ���ü��ú� jpg ͼ��ĸ��������Ϊӡ�µ����ĵ����ͼƬ���Ͻ�,������Ϊ��λ
*			���ӿ�Ϊ��������ӡ�ӿ�,��ӡʱ����պӡ��
*			�ֹ���ӡ���ü��ú�jpgͼ��ĸ��������Ϊӡ�µ����ĵ����ͼƬ���Ͻ�,������Ϊ��λ
*			ת����ĸ��������ͨ����������
* ����:	
* @parm int printNum ���ۺ�
* @parm int pointX ��ӡX����,��λΪ����
* @parm int pointY ��ӡY����,��λΪ����
* @parm int angle  ת�½Ƕ�(0-360)˳ʱ��
* @return	�ɹ�: 0
*				ʧ��: ��0
*/
typedef int (*pmanualPrintStartByLight)(int printNum, int pointX, int pointY, int angle);

/** No.11
* ����:	autoPrintStart	
* ����:	��ӡ���Զ�
* ˵��:	�Զ���ӡ�ĸ��������Ϊӡ�µ����ĵ����ƾ֤���Ͻ�,��mmΪ��λ.
*			��ӡ����֧���Զ���������½Ƕ�
* ����:	
* @parm int printNum ���ۺ�
* @parm int pointX ��ӡX����,��λΪ mm
* @parm int pointY ��ӡY����,��λΪ mm
* @parm int angle  ��ת�Ƕ�
* @return	�ɹ�: 0
*				ʧ��: ��0
*/
typedef int (*pautoPrintStart)(int printNum, int pointX, int pointY, int angle);

/** No.12
* ����:	openMachineBackDoor	
* ����:	�򿪺�����
* ˵��:	�򿪺������Ա��ӡ�ػ��е�ӡ��,ӡ��Ȳ�������ά��
*
* ����:	
* @parm void
* @return	�ɹ�: 0
*				ʧ��: ��0
*/
typedef int (*popenMachineBackDoor)(void);

/** No.13
* ����:	openMachineBackDoorUnNormal	
* ����:	�򿪺�����(�쳣����)
* ˵��:	�쳣����ʱ��¼�쳣������Ϣ
*
* ����:	
* @parm const char* openInfo �쳣��Ϣ��������ӡ����,������¼��";"�ָ�,
*                           ��ӡ������ౣ�� 4 ���쳣��Ϣ,ÿ���쳣��Ϣ 15 ���ַ�
* @return	�ɹ�: 0
*				ʧ��: ��0
*/
typedef int (*popenMachineBackDoorUnNormal)(const char* openInfo);

/** No.14
* ����:	getMachineNum	
* ����:	��ѯ�豸���
* ˵��:	��ȡ�豸���, ����ֵΪ 20 λ���ڵ��ַ���
*
* ����:	
* @parm void
* @return	�ɹ�: �ɹ����ر��,ʧ�ܷ��ظ�ֵ
*/
typedef char* (*pgetMachineNum)(void);

/** No.15
* ����:	getMachineType	
* ����:	��ȡ�豸�ͺ�
* ˵��:	��ȡ�豸�ͺ�,���ͺ�����ӡ�������ͺ�һ��
*
* ����:	
* @parm void
* @return	�ɹ�: �ɹ������ͺ�,ʧ�ܷ���"-@#"+������
*/
typedef char* (*pgetMachineType)(void);

/** No.16
* ����:	checkPaperDoorState	
* ����:	��ѯֽ���Ƿ�ر�
* ˵��:	��ӡǰ���ֽ���Ƿ�ر�
*
* ����:	
* @parm void
* @return	1---δ�ر�, 2---�ر�,����---����
*/
typedef int (*pcheckPaperDoorState)(void);

/** No.17
* ����:	checkBackDoorState	
* ����:	��ѯ������ ״̬
* ˵��:	��ȡ��������״̬(���ڹرջ��ǿ���)
*
* ����:	
* @parm void
* @return	1---δ�ر�, 2---�ر�, ����---����
*/
typedef int (*pcheckBackDoorState)(void);

/** No.18
* ����:	lockPrinter	
* ����:	��ӡ������
* ˵��:	��ӡ������ʱ��������������ʹ����ӡ����ӡ
*
* ����:	
* @parm void
* @return	0---�ɹ�, -1---ʧ��
*/
typedef int (*plockPrinter)(void);

/** No.19
* ����:	unLockPrinter	
* ����:	��ӡ���������
* ˵��:	��ӡ���������ʱ,�������̿�������ӡ����ӡ
*
* ����:	
* @parm void
* @return	0---�ɹ�, -1---ʧ��,����������
*/
typedef int (*punLockPrinter)(void);

/** No.20
* ����:	checkLockState	
* ����:	��ѯ��ӡ������״̬
* ˵��:	�����ӡ������״̬
*
* ����:	
* @parm void
* @return	0---����, -1---δ����, ����������
*/
typedef int (*pcheckLockState)(void);

/** No.21
* ����:	openVideoCapLight	
* ����:	������ͷ������
* ˵��:	������ͷ�����ƴ��ڹر�״̬,����뿪������ͷ�����ƿɵ��ô˽ӿ�
*
* ����:	
* @parm void
* @return	0---�ɹ�,��0---ʧ��,
*/
typedef int (*popenVideoCapLight)(void);

/** No.22
* ����:	closeVideoCapLight	
* ����:	�ر�����ͷ������
* ˵��:	������ͷ�����ƴ��ڿ���״̬�������ر�����ͷ�����ƿɵ��ô˽ӿ�
*
* ����:	
* @parm void
* @return	0---�ɹ�,��0---ʧ��,
*/
typedef int (*pcloseVideoCapLight)(void);

/** No.23
* ����:	geterrMsg	
* ����:	��ȡ������Ϣ
* ˵��:	��ȡ�������Ӧ�Ĵ�����Ϣ
*
* ����:	
* @parm int errNo ������
* @return	���ش������Ӧ�Ĵ�����Ϣ
*/
typedef char* (*pgeterrMsg)(int errNo);

/** No.24
* ����:	connMachine	
* ����:	���豸����
* ˵��:	�����豸�����ӣ��豸ʹ��ʱ������
*
* ����:	
* @parm const char* seriaID �豸���к�
* @return	0---�ɹ�, -1---ʧ��, ����������
*/
typedef  int (*pconnMachine)(const char* seriaID);

/** No.25
* ����:	disconnMachine	
* ����:	�ر��豸����
* ˵��:	�Ͽ����豸������,�豸��һ��ʹ�û����ӡ��ʱ����
*
* ����:	
* @parm void
* @return	0---�ɹ�, -1---ʧ��, ����������
*/
typedef int (*pdisconnMachine)(void);

/** No.26
* ����:	isConnMachine	
* ����:	�豸���Ӽ��
* ˵��:	����豸������״̬
*
* ����:	
* @parm void
* @return	0---�ɹ�, -1---ʧ��, ����������
*/
typedef int (*pisConnMachine)(void);

//===============CAMEAR API===============

/** No.27
* ����:	openVideoCap	
* ����:	������ͷ
* ˵��:	������ͷ
*
* ����:	
* @parm void
* @return	0---����, 1---�ر�, ����������
*/
typedef int (*popenVideoCap)(void);

/** No.28
* ����:	setVedioProperties	
* ����:	��������ͷ���ԨC �Զ����ڹ��� 
* ˵��:	ÿ������ͷ���Զ�����Ĭ��ֵ,������޸�����ͷ�����ȡ��Աȶ�
			ɫ�������Ͷȡ������ȡ���ƽ�⡢�ع�ֵ�����Ե�ֵ�ɵ��ô˽ӿ�
			�����ڱ��ص������ļ�,ÿ�� OCX �������ļ��ж�ȡ
*
* ����:	
* @parm int brightness		����
* @parm int constrast		�Աȶ�
* @parm int hue				ɫ��
* @parm int saturation		���Ͷ�
* @parm int sharpness		������
* @parm int whitebalance��ƽ��
* @parm int gain				�ع�ֵ
* @return	0---�ɹ�,�� 0---ʧ��, 
*/
typedef int (*psetVedioProperties)(int brightness, int constrast, int hue ,int saturation,int sharpness ,int whitebalance, int gain);

/** No.29
* ����:	getImageFormat	
* ����:	��������ͷ���ԨC �Զ����ڹ��� 
* ˵��:	�����ļ������ļ����͡��Ƿ������Ϣ��ָ��ȫ·����������ӡǰ
* ��ӡ��ͼ����ͼ�񲻴�������͵�ͼ���ļ�
* ����ָ��·��������ͼƬ�ļ���, ����ͨ��ͼƬȫ·����ȡͼƬ
* �����ⲿ����ͷ,��ɲ�֧���ⲿ������ͷ����.
* ����˵������ type=0 ʱ,������һ�� bmp ͼƬ��,ͬʱ�Զ�����һ��ͬ��(��׺.jpg)���� jpg ͼƬ.
*
* ����:	
* @parm const char*  filePath	�ļ�����(��Ŀ¼���ļ���,��Ϊ�������)
* @parm int type						�ļ�����0-BMP, 1-JPG ,2-Raw(ԭʼ�ļ�)
* @parm int isEraseBorder		�Ƿ����ͼ����(��ƫ,�ü�,ȥ�ڱ�)0---�� 1---��
* @return	0---�ɹ�,��0---ʧ��, 
*/
typedef int (*pgetImageFormat)(const char* filePath, int type, int isEraseBorder);

/** No.30
* ����:	revolveImg	
* ����:	��תͼ��
* ˵��:	��ԭͼ��˳ʱ����תָ���Ƕ�
*
* ����:	
* @parm const char*  filePath		Դ�ļ�·��
* @parm const char*  targetPath	Ŀ���ļ�·��
* @parm int angle						��ת�Ƕ�(0-360)
* @return	0---�ɹ�,��0---ʧ��, 
*/
typedef int (*prevolveImg)(const char* filePath, const char*  targetPath, int angle);

/** No.31
* ����:	closeVideoCap	
* ����:	�ر�����ͷ
* ˵��:	�ر�����ͷ
*
* ����:	
* @parm void
* @return	0--�ɹ�, �� 0--ʧ��
*/
typedef int (*pcloseVideoCap)(void);

/** No.32
* ����:	checkVideoState	
* ����:	��ѯ����ͷ״̬
* ˵��:	��ȡ����ͷ��״̬(���ڹرջ��ǿ���)
*
* ����:	
* @parm void
* @return	1---��, 2---�ر�, ����---����
*/
typedef int (*pcheckVideoState)(void);

//===============ABNORMAL INFOMATION===============
/** No.33
* ����:	readOpenBackDoorExceptionInfo	
* ����:	��ȡ�쳣������¼
* ˵��:	ÿ����ϢΪһ��������¼
*
* ����:	
* @parm void
* @return	1---��, 2---�ر�, ����---����
*/
typedef char* (*preadOpenBackDoorExceptionInfo)(void);

/** No.34
* ����:	readOpenBackDoorExceptionInfo	
* ����:	ɾ�������쳣������Ϣ
* ˵��:	ɾ�������쳣������Ϣ
*
* ����:	
* @parm void
* @return	0-�ɹ� -1-ʧ�� 2-����
*/
typedef int (*pdelOpenBackDoorExceptionInfo)(void);





class  PsbcStamp
{
public:
	PsbcStamp();
	~PsbcStamp();
public:
	

	int initializationMachine(void);
	char * querySealInfo(const char* machineNum);
	char* querySlotInfo(const char* machineNum);
	int initStamp(const char* machineNum,const char* slotNumAndStampId);
	int setAcrossPageSeal(void);
	int setMachineNum(const char* machineNum);
	int openPaperDoor(void);
	int checkManualPrintPara( int pointX, int pointY, int angle);
	int manualPrintStart(int printNum, int pointX, int pointY, int angle);
	int manualPrintStartByLight(int printNum, int pointX, int pointY, int angle);
	int autoPrintStart(int printNum, int pointX, int pointY, int angle);
	int openMachineBackDoor(void);
	int openMachineBackDoorUnNormal(const char* openInfo);
	char* getMachineNum(void);
	char* getMachineType(void);
	int checkPaperDoorState(void);
	int checkBackDoorState(void);
	int lockPrinter(void);
	int unLockPrinter(void);
	int checkLockState(void);
	int openVideoCapLight(void);
	int closeVideoCapLight(void);
	char* geterrMsg(int errNo);
	int connMachine(const char* seriaID);
	int disconnMachine(void);
	int isConnMachine(void);
	int openVideoCap(void);
	int setVedioProperties(int brightness, int constrast, int hue ,int saturation,int sharpness ,int whitebalance, int gain);
	int getImageFormat(const char* filePath, int type, int isEraseBorder);
	int revolveImg(const char* filePath, const char*  targetPath, int angle);
	int closeVideoCap(void);
	int checkVideoState(void);
	char* readOpenBackDoorExceptionInfo(void);
	int delOpenBackDoorExceptionInfo(void);
private:
	void GetCurrentOcxDir( char * path);
	void LoadLibrarypsbc();
private:
	pinitializationMachine  _pinitializationMachine;
	pquerySealInfo _pquerySealInfo;
	pquerySlotInfo _pquerySlotInfo;
	pinitStamp _pinitStamp;
	psetAcrossPageSeal _psetAcrossPageSeal;
	psetMachineNum _psetMachineNum;
	popenPaperDoor _popenPaperDoor;
	pcheckManualPrintPara _pcheckManualPrintPara;
	pmanualPrintStart _pmanualPrintStart;
	pmanualPrintStartByLight _pmanualPrintStartByLight;
	pautoPrintStart _pautoPrintStart;
	popenMachineBackDoor  _popenMachineBackDoor;
	popenMachineBackDoorUnNormal _popenMachineBackDoorUnNormal;
	pgetMachineNum _pgetMachineNum;
	pgetMachineType _pgetMachineType;
	pcheckPaperDoorState  _pcheckPaperDoorState;
	pcheckBackDoorState  _pcheckBackDoorState;
	plockPrinter  _plockPrinter;
	punLockPrinter  _punLockPrinter;
	pcheckLockState  _pcheckLockState;
	popenVideoCapLight _popenVideoCapLight;
	pcloseVideoCapLight _pcloseVideoCapLight;
	pgeterrMsg _pgeterrMsg;
	pconnMachine _pconnMachine;
	pdisconnMachine _pdisconnMachine;
	pisConnMachine  _pisConnMachine;
	popenVideoCap _popenVideoCap;
	psetVedioProperties _psetVedioProperties;
	pgetImageFormat _pgetImageFormat;
	prevolveImg _prevolveImg;
	pcloseVideoCap  _pcloseVideoCap;
	pcheckVideoState _pcheckVideoState;
	preadOpenBackDoorExceptionInfo _preadOpenBackDoorExceptionInfo;
	pdelOpenBackDoorExceptionInfo _pdelOpenBackDoorExceptionInfo;
	HINSTANCE _dllIns;
};

class PromptInfo
{
public:
	PromptInfo()
	{
		_mapPromptInfo.insert(make_pair(0,"�ɹ�"));
		_mapPromptInfo.insert(make_pair(1,"��ֽ�ſ�"));
		_mapPromptInfo.insert(make_pair(2,"��ֽ�Ź�"));
		_mapPromptInfo.insert(make_pair(3,"��ȫ�ſ�"));
		_mapPromptInfo.insert(make_pair(4,"��ȫ�Ź�"));
		_mapPromptInfo.insert(make_pair(5,"��ӡ������"));
		_mapPromptInfo.insert(make_pair(6,"��ӡ��δ����"));
		_mapPromptInfo.insert(make_pair(7,"�豸���ӳɹ�"));
		_mapPromptInfo.insert(make_pair(8,"�豸δ����"));
		_mapPromptInfo.insert(make_pair(9,"������ͷ�ɹ�"));
		_mapPromptInfo.insert(make_pair(10,"������ͷʧ��"));
		_mapPromptInfo.insert(make_pair(11,"�ر�����ͷ�ɹ�"));
		_mapPromptInfo.insert(make_pair(12,"�ر�����ͷʧ��"));
		_mapPromptInfo.insert(make_pair(-1,"ʧ��"));
		_mapPromptInfo.insert(make_pair(-2,"�������Ϸ�"));

	}

	map<int,string> _mapPromptInfo;
};
#endif