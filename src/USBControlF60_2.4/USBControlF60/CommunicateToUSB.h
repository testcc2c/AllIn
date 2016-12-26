#pragma once

#include <iostream>
#include <queue>
#include "USBParam.h"

//class CUSBParam;
class CCommunicateToUSB
{
public:
	CCommunicateToUSB(void);
	~CCommunicateToUSB(void);

	int InitUSB(void);
	
	void RegisterDevCallBack(PVOID func);
	int OpenDev(const char *file);
	int CloseDev(void);
	int send(SendPackage *sendPackage);
	int receive(ReceivePackage *recvPackage);
	int GetStamperStauts();
	void SetStamperStauts(int status);

    static void signal();

public:
	//�ص�����ָ��
	PVOID m_USBMsgCallBack;
	
	//���ͱ����õ�OVERLAPPED��
	OVERLAPPED WriteOverlapped;
	//���ձ����õ�OVERLAPPED��
	OVERLAPPED ReadOverlapped;


	//������������ݵ��豸���
	HANDLE hReadHandle;
	//��������д���ݵ��豸���
	HANDLE hWriteHandle;
	//���ݽ����߳�	
	HANDLE hReadThread;
	//���ݷ����߳�
	HANDLE hWriteThread;

	//���������¼�
	HANDLE recvevent;

	//��д�߳��˳��¼�
	HANDLE exitevent;

	//���ڷ������ݵı�־, TRUE ���ڷ�����
	BOOL DataInSending;
	//�豸�Ƿ��Ѿ���
	BOOL isfound;

	BOOL DataInReading;

	//��������
	CUSBParam m_param;

    struct NotifyParam {
        unsigned int uMsg;
        unsigned int wParam;
        long lParam;
        unsigned char* data;
        unsigned char len;
    };

    static HANDLE notify_ev_;
    static Mutex notify_lock_;
    static NotifyParam notify_;

protected:
	static UINT __stdcall WriteData2UsbThread(LPVOID pParam);
	static UINT __stdcall ReadDataFromUsbThread(LPVOID pParam);
    static UINT __stdcall AsyncNotifyThread(LPVOID pParam);
    static UINT __stdcall WriteLogThread(LPVOID pParam);

private:
	//��������
	int sendData2Usb(void);		
	std::string strDevPathName;	//�豸·��
	ReceivePackage* usbpackage;

    static unsigned char send_cmd_;
	static int  stamperStatus ;
    static HANDLE reset_ev;
    static Mutex log_list_lock;
    static std::queue<std::string> logs_;
};

