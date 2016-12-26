/********************************************************************
	created:	2016/09/08
	created:	8:9:2016   19:13
	filename: 	F:\workspace\ӡ�ػ�\ӡ���豸��Ʒ��\��Ʒ\����\����ӡ��ϵͳ\�ʴ�������ʾ�汾\
                SealStampApp\PSBC.STDZ.Device.STAMP.Device\PSBC.STDZ.Device.STAMP.Device.h
	file path:	F:\workspace\ӡ�ػ�\ӡ���豸��Ʒ��\��Ʒ\����\����ӡ��ϵͳ\�ʴ�������ʾ�汾\
                SealStampApp\PSBC.STDZ.Device.STAMP.Device
	file base:	PSBC.STDZ.Device.STAMP.Device
	file ext:	h
	author:		ZDD
	version:	1.0
	purpose:	����ʴ�������ӡ�ӿ�
	change:		2016/09/08 by zdd init version
*********************************************************************/

#ifndef _PSBC_STDZ_DEVICE_STAMP_DEVICE_H_
#define _PSBC_STDZ_DEVICE_STAMP_DEVICE_H_

#include <string>

#ifdef __cplusplus
extern "C" 
{
#endif

#ifdef  STMAP_DEVICE_EXPORTS
	#define STMAP_DEVICE_PSBC_API  __declspec(dllexport)
#else
	#define STMAP_DEVICE_PSBC_API  __declspec(dllimport)
#endif

#define MAX_INPUT_LENGTH		128	//�������Ĳ�������
#define MAX_INPUT_PARM			10	//�������Ĳ�������

//�������������Ĳ���
typedef struct _tag_Parm
{
	char parm1[MAX_INPUT_LENGTH];
	char parm2[MAX_INPUT_LENGTH];
	char parm3[MAX_INPUT_LENGTH];
	char parm4[MAX_INPUT_LENGTH];
	char parm5[MAX_INPUT_LENGTH];
	char parm6[MAX_INPUT_LENGTH];
	char parm7[MAX_INPUT_LENGTH];
	char parm8[MAX_INPUT_LENGTH];
	char parm9[MAX_INPUT_LENGTH];
	char parm10[MAX_INPUT_LENGTH];
	_tag_Parm()
	{
		memset(parm1,0, MAX_INPUT_LENGTH);
		memset(parm2,0, MAX_INPUT_LENGTH);
		memset(parm3,0, MAX_INPUT_LENGTH);
		memset(parm4,0, MAX_INPUT_LENGTH);
		memset(parm5,0, MAX_INPUT_LENGTH);
		memset(parm6,0, MAX_INPUT_LENGTH);
		memset(parm7,0, MAX_INPUT_LENGTH);
		memset(parm8,0, MAX_INPUT_LENGTH);
		memset(parm9,0, MAX_INPUT_LENGTH);
		memset(parm10,0, MAX_INPUT_LENGTH);
	}
}StampParm;

// �����б�
typedef struct _tag_Parm_In
{
	StampParm   arrayParm[MAX_INPUT_PARM];
	int         nParmCount;
}Parm_In, Parm_Out;

/**
* ����:Execute	
* ����:ִ���ʴ����нӿڹ���
* 
* ����:	
* @parm const char* typeId
* @parm const char* transcode
* @parm const char* clientconfig
* @parm const char* deviceconfig
* @parm const char* instrut
* @parm const char* input1
* @parm const char* input2
* @parm void* output1
* @parm void* output2
* @parm char* errormessage
* @return 0-�ɹ� ������ʾ�������,������Ϣ��errormessage���
*/
STMAP_DEVICE_PSBC_API int Execute(\
	const char* typeId,\
	const char* transcode,\
	const char* clientconfig,\
	const char* deviceconfig,\
	const char* instrut,\
	const void* input1,\
	const void* input2,\
	void* output1,\
	void* output2,\
	char* errormessage\
	);

/** No.1
* ����:	initializationMachine	
* ����:	��ӡ���Լ�
* ˵��:	������״̬�Ƿ����������磺���ӡ��
*			�豸��һ��ʹ�û����ӡ��ʱ����
* ����:	��
* @return 0---�ɹ�, -1---ʧ��, ����������
*/
STMAP_DEVICE_PSBC_API int initializationMachine(void);

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
STMAP_DEVICE_PSBC_API char* querySealInfo(const char* machineNum);

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
STMAP_DEVICE_PSBC_API char* querySloatInfo(const char* machineNum);

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
STMAP_DEVICE_PSBC_API int initStamp(const char* machineNum,const char* slotNumAndStampId);

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
STMAP_DEVICE_PSBC_API int setAcrossPageSeal(void);

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
STMAP_DEVICE_PSBC_API int setMachineNum(const char* machineNum);

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
STMAP_DEVICE_PSBC_API int openPaperDoor(void);

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
STMAP_DEVICE_PSBC_API int checkManualPrintPara( int pointX, int pointY, int angle);

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
STMAP_DEVICE_PSBC_API int manualPrintStart(int printNum, int pointX, int pointY, int angle);

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
STMAP_DEVICE_PSBC_API int manualPrintStartByLight(int printNum, int pointX, int pointY, int angle);

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
STMAP_DEVICE_PSBC_API int autoPrintStart(int printNum, int pointX, int pointY, int angle);

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
STMAP_DEVICE_PSBC_API int openMachineBackDoor(void);

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
STMAP_DEVICE_PSBC_API int openMachineBackDoorUnNormal(const char* openInfo);

/** No.14
* ����:	getMachineNum	
* ����:	��ѯ�豸���
* ˵��:	��ȡ�豸���, ����ֵΪ 20 λ���ڵ��ַ���
*
* ����:	
* @parm void
* @return	�ɹ�: �ɹ����ر��,ʧ�ܷ��ظ�ֵ
*/
STMAP_DEVICE_PSBC_API char* getMachineNum(void);

/** No.15
* ����:	getMachineType	
* ����:	��ȡ�豸�ͺ�
* ˵��:	��ȡ�豸�ͺ�,���ͺ�����ӡ�������ͺ�һ��
*
* ����:	
* @parm void
* @return	�ɹ�: �ɹ������ͺ�,ʧ�ܷ���"-@#"+������
*/
STMAP_DEVICE_PSBC_API char* getMachineType(void);

/** No.16
* ����:	checkPaperDoorState	
* ����:	��ѯֽ���Ƿ�ر�
* ˵��:	��ӡǰ���ֽ���Ƿ�ر�
*
* ����:	
* @parm void
* @return	1---δ�ر�, 2---�ر�,����---����
*/
STMAP_DEVICE_PSBC_API int checkPaperDoorState(void);

/** No.17
* ����:	checkBackDoorState	
* ����:	��ѯ������ ״̬
* ˵��:	��ȡ��������״̬(���ڹرջ��ǿ���)
*
* ����:	
* @parm void
* @return	1---δ�ر�, 2---�ر�, ����---����
*/
STMAP_DEVICE_PSBC_API int checkBackDoorState(void);

/** No.18
* ����:	lockPrinter	
* ����:	��ӡ������
* ˵��:	��ӡ������ʱ��������������ʹ����ӡ����ӡ
*
* ����:	
* @parm void
* @return	0---�ɹ�, -1---ʧ��
*/
STMAP_DEVICE_PSBC_API int lockPrinter(void);

/** No.19
* ����:	unLockPrinter	
* ����:	��ӡ���������
* ˵��:	��ӡ���������ʱ,�������̿�������ӡ����ӡ
*
* ����:	
* @parm void
* @return	0---�ɹ�, -1---ʧ��,����������
*/
STMAP_DEVICE_PSBC_API int unLockPrinter(void);

/** No.20
* ����:	checkLockState	
* ����:	��ѯ��ӡ������״̬
* ˵��:	�����ӡ������״̬
*
* ����:	
* @parm void
* @return	0---����, -1---δ����, ����������
*/
STMAP_DEVICE_PSBC_API int checkLockState(void);

/** No.21
* ����:	openVideoCapLight	
* ����:	������ͷ������
* ˵��:	������ͷ�����ƴ��ڹر�״̬,����뿪������ͷ�����ƿɵ��ô˽ӿ�
*
* ����:	
* @parm void
* @return	0---�ɹ�,��0---ʧ��,
*/
STMAP_DEVICE_PSBC_API int openVideoCapLight(void);

/** No.22
* ����:	closeVideoCapLight	
* ����:	�ر�����ͷ������
* ˵��:	������ͷ�����ƴ��ڿ���״̬�������ر�����ͷ�����ƿɵ��ô˽ӿ�
*
* ����:	
* @parm void
* @return	0---�ɹ�,��0---ʧ��,
*/
STMAP_DEVICE_PSBC_API int closeVideoCapLight(void);

/** No.23
* ����:	geterrMsg	
* ����:	��ȡ������Ϣ
* ˵��:	��ȡ�������Ӧ�Ĵ�����Ϣ
*
* ����:	
* @parm int errNo ������
* @return	���ش������Ӧ�Ĵ�����Ϣ
*/
STMAP_DEVICE_PSBC_API char* geterrMsg(int errNo);

/** No.24
* ����:	connMachine	
* ����:	���豸����
* ˵��:	�����豸�����ӣ��豸ʹ��ʱ������
*
* ����:	
* @parm const char* seriaID �豸���к�
* @return	0---�ɹ�, -1---ʧ��, ����������
*/
STMAP_DEVICE_PSBC_API int connMachine(const char* seriaID);

/** No.25
* ����:	disconnMachine	
* ����:	�ر��豸����
* ˵��:	�Ͽ����豸������,�豸��һ��ʹ�û����ӡ��ʱ����
*
* ����:	
* @parm void
* @return	0---�ɹ�, -1---ʧ��, ����������
*/
STMAP_DEVICE_PSBC_API int disconnMachine(void);

/** No.26
* ����:	isConnMachine	
* ����:	�豸���Ӽ��
* ˵��:	����豸������״̬
*
* ����:	
* @parm void
* @return	0---�ɹ�, -1---ʧ��, ����������
*/
STMAP_DEVICE_PSBC_API int isConnMachine(void);

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
STMAP_DEVICE_PSBC_API int openVideoCap(void);

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
STMAP_DEVICE_PSBC_API int setVedioProperties(
    int brightness, 
    int constrast, 
    int hue,
    int saturation,
    int sharpness,
    int whitebalance, 
    int gain);

/** No.29
* ����:	getImageFormat	
* ����:	��ȡͼ��
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
STMAP_DEVICE_PSBC_API int getImageFormat(const char* filePath, int type, int isEraseBorder);

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
STMAP_DEVICE_PSBC_API int revolveImg(const char* filePath, const char*  targetPath, int angle);

/** No.31
* ����:	closeVideoCap	
* ����:	�ر�����ͷ
* ˵��:	�ر�����ͷ
*
* ����:	
* @parm void
* @return	0--�ɹ�, �� 0--ʧ��
*/
STMAP_DEVICE_PSBC_API int closeVideoCap(void);

/** No.32
* ����:	checkVideoState	
* ����:	��ѯ����ͷ״̬
* ˵��:	��ȡ����ͷ��״̬(���ڹرջ��ǿ���)
*
* ����:	
* @parm void
* @return	1---��, 2---�ر�, ����---����
*/
STMAP_DEVICE_PSBC_API int checkVideoState(void);

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
STMAP_DEVICE_PSBC_API char* readOpenBackDoorExceptionInfo(void);

/** No.34
* ����:	readOpenBackDoorExceptionInfo	
* ����:	ɾ�������쳣������Ϣ
* ˵��:	ɾ�������쳣������Ϣ
*
* ����:	
* @parm void
* @return	0-�ɹ� -1-ʧ�� 2-����
*/
STMAP_DEVICE_PSBC_API int delOpenBackDoorExceptionInfo(void);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // _PSBC_STDZ_DEVICE_STAMP_DEVICE_H_
