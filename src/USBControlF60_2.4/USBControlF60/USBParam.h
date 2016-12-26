#pragma once
#include "USBProtocol.h"
#include "WLock.h"

//�˲���Ҫ����λ������Ļ�������һ���ֽڲ��У���Ϊ��һ���ֽ��������������
#define WRITEBUF_LEN		  65

#define READBINFILEBUF  59
#define READBUFLEN		256
#define UsbDevWaitTime	7000

class CUSBParam
{
public:
	CUSBParam(void);
	~CUSBParam(void);

	//�ϳɷ�������
	void ComposeSendPackage(SendPackage &sendPackage);
	//��������
	ReceivePackage* AnalyzeRecvPackage(void);

	//���ͱ���Ļ�����	
	UCHAR WriteBuffer[WRITEBUF_LEN];
	unsigned int writebuflen;
	//���ձ���Ļ�����
	UCHAR ReadBuffer[READBUFLEN];
	UCHAR *pRead;
	//ʵ�ʽ��յĳ���
	DWORD readbuflen ;

	SendPackage m_sendcmd;	//��������
	ReceivePackage m_answercmd;	//��Ӧ����

	Mutex g_Lock;
};

