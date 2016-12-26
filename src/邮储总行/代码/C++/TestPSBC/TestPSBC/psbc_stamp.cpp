#include "stdafx.h"
#include "psbc_stamp.h"
#include <string>
using namespace std;
PsbcStamp::PsbcStamp():
    _pinitializationMachine(0),
	_pquerySealInfo(0),
	_pquerySlotInfo(0),
	_pinitStamp(0),
	_psetAcrossPageSeal(0),
	_psetMachineNum(0),
	_popenPaperDoor(0),
	_pcheckManualPrintPara(0),
	_pmanualPrintStart(0),
	_pmanualPrintStartByLight(0),
	_pautoPrintStart(0),
	_popenMachineBackDoor(0),
	_popenMachineBackDoorUnNormal(0),
	_pgetMachineNum(0),
	_pgetMachineType(0),
	_pcheckPaperDoorState(0),
	_pcheckBackDoorState(0),
	_plockPrinter(0),
	_punLockPrinter(0),
	_pcheckLockState(0),
	_popenVideoCapLight(0),
	_pcloseVideoCapLight(0),
	_pgeterrMsg(0),
	_pconnMachine(0),
	_pdisconnMachine(0),
	_pisConnMachine(0),
	_popenVideoCap(0),
	_psetVedioProperties(0),
	_pgetImageFormat(0),
	_prevolveImg(0),
	_pcloseVideoCap(0),
	_pcheckVideoState(0),
	_preadOpenBackDoorExceptionInfo(0),
	_pdelOpenBackDoorExceptionInfo(0)
{
	LoadLibrarypsbc();
}
	PsbcStamp::~PsbcStamp()
	{
		//�ͷŶ�̬��
	}
	int PsbcStamp::initializationMachine(void)
	{
		return  _pinitializationMachine?_pinitializationMachine():-1;
	}

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
  char * PsbcStamp::querySealInfo(const char* machineNum)
  {
	  return  _pquerySealInfo?_pquerySealInfo(machineNum):0;
 }

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
 char* PsbcStamp::querySlotInfo(const char* machineNum)
 {
	 return  _pquerySlotInfo?_pquerySlotInfo(machineNum):0;
 }

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
 int PsbcStamp::initStamp(const char* machineNum,const char* slotNumAndStampId)
 {
	  return  _pinitStamp?_pinitStamp(machineNum,slotNumAndStampId):-1;
 }

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
 int PsbcStamp::setAcrossPageSeal(void)
 {
	  return  _psetAcrossPageSeal?_psetAcrossPageSeal():-1;
 }

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
 int PsbcStamp::setMachineNum(const char* machineNum)
 {
	 return  _psetMachineNum?_psetMachineNum(machineNum):-1;
 }

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
 int PsbcStamp::openPaperDoor(void)
 {
	  return  _popenPaperDoor?_popenPaperDoor():-1;
 }

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
 int PsbcStamp::checkManualPrintPara( int pointX, int pointY, int angle)
 {
	   return  _pcheckManualPrintPara?_pcheckManualPrintPara(pointX,pointY,angle):-1;
 }

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
 int PsbcStamp::manualPrintStart(int printNum, int pointX, int pointY, int angle)
 {
	   return  _pmanualPrintStart?_pmanualPrintStart(printNum,pointX,pointY,angle):-1;
 }

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
 int PsbcStamp::manualPrintStartByLight(int printNum, int pointX, int pointY, int angle)
 {
	  return  _pmanualPrintStartByLight?_pmanualPrintStartByLight(printNum,pointX,pointY,angle):-1;
 }

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
 int PsbcStamp::autoPrintStart(int printNum, int pointX, int pointY, int angle)
 {
	   return  _pautoPrintStart?_pautoPrintStart(printNum,pointX,pointY,angle):-1;
 }

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
 int PsbcStamp::openMachineBackDoor(void)
 {
	    return  _popenMachineBackDoor?_popenMachineBackDoor():-1;
 }

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
 int PsbcStamp::openMachineBackDoorUnNormal(const char* openInfo)
 {
	  return  _popenMachineBackDoorUnNormal?_popenMachineBackDoorUnNormal(openInfo):-1;
 }

/** No.14
* ����:	getMachineNum	
* ����:	��ѯ�豸���
* ˵��:	��ȡ�豸���, ����ֵΪ 20 λ���ڵ��ַ���
*
* ����:	
* @parm void
* @return	�ɹ�: �ɹ����ر��,ʧ�ܷ��ظ�ֵ
*/
 char* PsbcStamp::getMachineNum(void)
 {
	  return  _pgetMachineNum?_pgetMachineNum():0;
 }

/** No.15
* ����:	getMachineType	
* ����:	��ȡ�豸�ͺ�
* ˵��:	��ȡ�豸�ͺ�,���ͺ�����ӡ�������ͺ�һ��
*
* ����:	
* @parm void
* @return	�ɹ�: �ɹ������ͺ�,ʧ�ܷ���"-@#"+������
*/
 char* PsbcStamp::getMachineType(void)
 {
	 return  _pgetMachineType?_pgetMachineType():0;
 }

/** No.16
* ����:	checkPaperDoorState	
* ����:	��ѯֽ���Ƿ�ر�
* ˵��:	��ӡǰ���ֽ���Ƿ�ر�
*
* ����:	
* @parm void
* @return	1---δ�ر�, 2---�ر�,����---����
*/
 int PsbcStamp::checkPaperDoorState(void)
 {
	 return  _pcheckPaperDoorState?_pcheckPaperDoorState():0;
 }
/** No.17
* ����:	checkBackDoorState	
* ����:	��ѯ������ ״̬
* ˵��:	��ȡ��������״̬(���ڹرջ��ǿ���)
*
* ����:	
* @parm void
* @return	1---δ�ر�, 2---�ر�, ����---����
*/
 int PsbcStamp::checkBackDoorState(void)
 {
	  return  _pcheckBackDoorState?_pcheckBackDoorState():0;
 }

/** No.18
* ����:	lockPrinter	
* ����:	��ӡ������
* ˵��:	��ӡ������ʱ��������������ʹ����ӡ����ӡ
*
* ����:	
* @parm void
* @return	0---�ɹ�, -1---ʧ��
*/
 int PsbcStamp::lockPrinter(void)
 {
	  return  _plockPrinter?_plockPrinter():0;
 }

/** No.19
* ����:	unLockPrinter	
* ����:	��ӡ���������
* ˵��:	��ӡ���������ʱ,�������̿�������ӡ����ӡ
*
* ����:	
* @parm void
* @return	0---�ɹ�, -1---ʧ��,����������
*/
 int PsbcStamp::unLockPrinter(void)
 {
	  return  _punLockPrinter?_punLockPrinter():0;
 }

/** No.20
* ����:	checkLockState	
* ����:	��ѯ��ӡ������״̬
* ˵��:	�����ӡ������״̬
*
* ����:	
* @parm void
* @return	0---����, -1---δ����, ����������
*/
 int PsbcStamp::checkLockState(void)
 {
	  return  _pcheckLockState?_pcheckLockState():0;
 }

/** No.21
* ����:	openVideoCapLight	
* ����:	������ͷ������
* ˵��:	������ͷ�����ƴ��ڹر�״̬,����뿪������ͷ�����ƿɵ��ô˽ӿ�
*
* ����:	
* @parm void
* @return	0---�ɹ�,��0---ʧ��,
*/
 int PsbcStamp::openVideoCapLight(void)
 {
	  return  _popenVideoCapLight?_popenVideoCapLight():0;
 }

/** No.22
* ����:	closeVideoCapLight	
* ����:	�ر�����ͷ������
* ˵��:	������ͷ�����ƴ��ڿ���״̬�������ر�����ͷ�����ƿɵ��ô˽ӿ�
*
* ����:	
* @parm void
* @return	0---�ɹ�,��0---ʧ��,
*/
 int PsbcStamp::closeVideoCapLight(void)
 {
	  return  _pcloseVideoCapLight?_pcloseVideoCapLight():0;
 }

/** No.23
* ����:	geterrMsg	
* ����:	��ȡ������Ϣ
* ˵��:	��ȡ�������Ӧ�Ĵ�����Ϣ
*
* ����:	
* @parm int errNo ������
* @return	���ش������Ӧ�Ĵ�����Ϣ
*/
 char* PsbcStamp::geterrMsg(int errNo)
 {
	   return  _pgeterrMsg?_pgeterrMsg(errNo):0;
 }
/** No.24
* ����:	connMachine	
* ����:	���豸����
* ˵��:	�����豸�����ӣ��豸ʹ��ʱ������
*
* ����:	
* @parm const char* seriaID �豸���к�
* @return	0---�ɹ�, -1---ʧ��, ����������
*/
 int PsbcStamp::connMachine(const char* seriaID)
 {
	  return  _pconnMachine?_pconnMachine(seriaID):0;
 }

/** No.25
* ����:	disconnMachine	
* ����:	�ر��豸����
* ˵��:	�Ͽ����豸������,�豸��һ��ʹ�û����ӡ��ʱ����
*
* ����:	
* @parm void
* @return	0---�ɹ�, -1---ʧ��, ����������
*/
 int PsbcStamp::disconnMachine(void)
 {
	  return  _pdisconnMachine?_pdisconnMachine():-1;
 }

/** No.26
* ����:	isConnMachine	
* ����:	�豸���Ӽ��
* ˵��:	����豸������״̬
*
* ����:	
* @parm void
* @return	0---�ɹ�, -1---ʧ��, ����������
*/
 int PsbcStamp::isConnMachine(void)
 {
	   return  _pisConnMachine?_pisConnMachine():-1;
 }

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
 int PsbcStamp::openVideoCap(void)
 {
	  return  _popenVideoCap?_popenVideoCap():-1;
 }

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
 int PsbcStamp::setVedioProperties(int brightness, int constrast, int hue ,int saturation,int   ,int whitebalance, int gain)
 {
	 return  _psetVedioProperties?_psetVedioProperties(brightness, constrast,  hue,  saturation,   saturation ,  whitebalance ,  gain):-1;
 }

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
 int PsbcStamp::getImageFormat(const char* filePath, int type, int isEraseBorder)
 {
	  return  _pgetImageFormat?_pgetImageFormat(filePath,type,isEraseBorder):-1;
 }
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
 int PsbcStamp::revolveImg(const char* filePath, const char*  targetPath, int angle)
{
	 return  _prevolveImg?_prevolveImg(filePath,targetPath,angle):-1;
 }

/** No.31
* ����:	closeVideoCap	
* ����:	�ر�����ͷ
* ˵��:	�ر�����ͷ
*
* ����:	
* @parm void
* @return	0--�ɹ�, �� 0--ʧ��
*/
 int PsbcStamp::closeVideoCap(void)
 {
	  return  _pcloseVideoCap?_pcloseVideoCap():-1;
 }

/** No.32
* ����:	checkVideoState	
* ����:	��ѯ����ͷ״̬
* ˵��:	��ȡ����ͷ��״̬(���ڹرջ��ǿ���)
*
* ����:	
* @parm void
* @return	1---��, 2---�ر�, ����---����
*/
 int PsbcStamp::checkVideoState(void)
 {
	  return  _pcheckVideoState?_pcheckVideoState():-1;
 }

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
 char* PsbcStamp::readOpenBackDoorExceptionInfo(void)
{
	  return  _preadOpenBackDoorExceptionInfo?_preadOpenBackDoorExceptionInfo():0;
 
 }

/** No.34
* ����:	readOpenBackDoorExceptionInfo	
* ����:	ɾ�������쳣������Ϣ
* ˵��:	ɾ�������쳣������Ϣ
*
* ����:	
* @parm void
* @return	0-�ɹ� -1-ʧ�� 2-����
*/
 int PsbcStamp::delOpenBackDoorExceptionInfo(void)
 {
	   return  _pdelOpenBackDoorExceptionInfo?_pdelOpenBackDoorExceptionInfo():0;
 }

 void PsbcStamp::GetCurrentOcxDir( char * path)
 {
	 if(path == NULL)
	{
		return ;
	}
	char v_path[MAX_PATH]; //���·���ı���
	memset(v_path,0,MAX_PATH);
	::GetModuleFileName(AfxGetInstanceHandle(),v_path,MAX_PATH);
	std::string  str_Path;
	str_Path = v_path;
	str_Path.erase(str_Path.find_last_of('\\'),str_Path.length());
	memcpy(path,str_Path.c_str(),str_Path.length());
	return ;
 }

 // �˴��޸Ķ�̬���붯̬�������
 void PsbcStamp::LoadLibrarypsbc()
 {
	char szDir[256]={0};
	char szFullPath[256]={0};
	GetCurrentOcxDir(szDir);
	std::string strFullPath(szDir);
#ifdef _DEBUG
	strFullPath.append("\\STDLL.dll");
#else
	strFullPath.append("\\STDLL.dll");
#endif
	
	memcpy(szFullPath,strFullPath.c_str(),strFullPath.length());
	_dllIns =::LoadLibrary(szFullPath);
	DWORD _lasteRROR =0;
	_lasteRROR=GetLastError();
	if(_dllIns)
	{
		_pinitializationMachine = (pinitializationMachine)GetProcAddress(_dllIns, "initializationMachine");
	    _pquerySealInfo = (pquerySealInfo)GetProcAddress(_dllIns,"querySealInfo");
		_pquerySlotInfo = (pquerySlotInfo)GetProcAddress(_dllIns,"querySloatInfo");
		_pinitStamp = (pinitStamp)GetProcAddress(_dllIns,"initStamp");
		_psetAcrossPageSeal = (psetAcrossPageSeal)GetProcAddress(_dllIns,"setAcrossPageSeal");
		_psetMachineNum = (psetMachineNum)GetProcAddress(_dllIns,"setMachineNum");
		_popenPaperDoor= (popenPaperDoor)GetProcAddress(_dllIns,"openPaperDoor");
		_pcheckManualPrintPara = (pcheckManualPrintPara)GetProcAddress(_dllIns,"checkManualPrintPara");
		_pmanualPrintStart = (pmanualPrintStart)GetProcAddress(_dllIns,"manualPrintStart");
		_pmanualPrintStartByLight= (pmanualPrintStartByLight)GetProcAddress(_dllIns,"manualPrintStartByLight");
		_pautoPrintStart = (pautoPrintStart)GetProcAddress(_dllIns,"autoPrintStart");
		_popenMachineBackDoor= (popenMachineBackDoor)GetProcAddress(_dllIns,"openMachineBackDoor");
		_popenMachineBackDoorUnNormal= (popenMachineBackDoorUnNormal)GetProcAddress(_dllIns,"openMachineBackDoorUnNormal");
		_pgetMachineNum= (pgetMachineNum)GetProcAddress(_dllIns,"getMachineNum");
		_pgetMachineType = (pgetMachineType)GetProcAddress(_dllIns,"getMachineType");
		_pcheckPaperDoorState= (pcheckPaperDoorState)GetProcAddress(_dllIns,"checkPaperDoorState");
		_pcheckBackDoorState = (pcheckBackDoorState)GetProcAddress(_dllIns,"checkBackDoorState");
		_plockPrinter = (plockPrinter)GetProcAddress(_dllIns,"lockPrinter");
		_punLockPrinter= (punLockPrinter)GetProcAddress(_dllIns,"unLockPrinter");
		_pcheckLockState = (pcheckLockState)GetProcAddress(_dllIns,"checkLockState");
		_popenVideoCapLight = (popenVideoCapLight)GetProcAddress(_dllIns,"openVideoCapLight");
		_pcloseVideoCapLight= (pcloseVideoCapLight)GetProcAddress(_dllIns,"closeVideoCapLight");
		_pgeterrMsg = (pgeterrMsg)GetProcAddress(_dllIns,"geterrMsg");
		_pconnMachine= (pconnMachine)GetProcAddress(_dllIns,"connMachine");
		_pdisconnMachine= (pdisconnMachine)GetProcAddress(_dllIns,"disconnMachine");
		_pisConnMachine= (pisConnMachine)GetProcAddress(_dllIns,"isConnMachine");
		_popenVideoCap= (popenVideoCap)GetProcAddress(_dllIns,"openVideoCap");
		_psetVedioProperties = (psetVedioProperties)GetProcAddress(_dllIns,"setVedioProperties");
		_pgetImageFormat= (pgetImageFormat)GetProcAddress(_dllIns,"getImageFormat");
		_prevolveImg= (prevolveImg)GetProcAddress(_dllIns,"revolveImg");
		_pcloseVideoCap= (pcloseVideoCap)GetProcAddress(_dllIns,"closeVideoCap");
		_pcheckVideoState = (pcheckVideoState)GetProcAddress(_dllIns,"checkVideoState");
		_preadOpenBackDoorExceptionInfo = (preadOpenBackDoorExceptionInfo)GetProcAddress(_dllIns,"readOpenBackDoorExceptionInfo");
		_pdelOpenBackDoorExceptionInfo= (pdelOpenBackDoorExceptionInfo)GetProcAddress(_dllIns,"delOpenBackDoorExceptionInfo");
	}
 }
