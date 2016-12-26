#pragma once
extern "C" {
#include "hidsdi.h"
#include "setupapi.h"
}
#include "WLock.h"
#include <list>
#include <map>
#include <vector>
#include <Dbt.h>
#include <string>
using std::string;
using std::list;
using std::map;
using std::pair;


class CCtrlUSB
{
public:
	static CCtrlUSB* sharedCCtrlUSB(void);	
	~CCtrlUSB(void);
private:
	CCtrlUSB(void);
	static CCtrlUSB* m_pInstance;	

	class CGarbo   //����Ψһ��������������������ɾ��CSingleton��ʵ��  
	{  
	public:  
		~CGarbo();		
	};  
	static CGarbo Garbo;
public:
	
	//������Ϣ�Ĵ��ھ��
	HWND m_hWnd;

	//����ע���豸֪ͨ�¼��õĹ㲥�ӿڡ�
	//Ҫʹ�øýṹ�壬��Ҫ��StdAfx.h�н��������#define WINVER 0x0500
	DEV_BROADCAST_DEVICEINTERFACE DevBroadcastDeviceInterface;

	//PVOID m_CallBack;
	std::vector<PVOID> vecCallback;

    Mutex path_mutex_;
	string strdevpath;
public:
	void Init(HWND hWnd);

	//�豸��ν�����Ϣ
	LRESULT OnDeviceChange(WPARAM wParam, LPARAM lParam);

	//��ȡ�����豸·��
	void FindDevPath();

	//�ж��Ƿ���ӡ�ػ��豸
	bool IsST_USBDevPath(const char* path);

	//��ȡ�豸·��map<string, bool>
	//string �豸·��
	//bool true �Ѿ���ʹ�ã�false,δ��ʹ��
	map<string, bool>* CCtrlUSB::GetDevPathMap();
	//ע��ص�����
	void RegisterDevCallBack(PVOID func);
	
	string GetDevPath();
};

