// dllmain.cpp : ���� DLL Ӧ�ó������ڵ㡣
#include "stdafx.h"
#include "Log.h"
#include "CtrlUSB.h"
//#include <vld.h>



//���̻��߳̾��
HINSTANCE hinst = NULL; 
//���ھ��
HWND hwndDLG = NULL; 

//������Ϣ������
LRESULT CALLBACK WinProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam ) ;  
//����������Ϣ�����߳�
DWORD WINAPI CreateWindowThreadPro(LPVOID lpParameter);


BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{	
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		{//�õ�����ʵ��
			hinst = static_cast<HINSTANCE>(hModule);
			//���������߳�
			HANDLE hThread = CreateThread(NULL,NULL,(LPTHREAD_START_ROUTINE)CreateWindowThreadPro,NULL,NULL,NULL);
			bool bRet = (hThread != NULL);
			CloseHandle(hThread);
		}
		break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

//������Ϣ����
LRESULT CALLBACK WinProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	CCtrlUSB* pCCtrlUSB = CCtrlUSB::sharedCCtrlUSB();
	switch( message )
	{
	case WM_CREATE:		
		if (pCCtrlUSB)
		{
			pCCtrlUSB->Init(hWnd);
			pCCtrlUSB->FindDevPath();
            if (!pCCtrlUSB->GetDevPath().empty())
                CLog::sharedLog()->WriteNormalLog("WinProc->�ɹ�ȷ���豸·��");
            else
                CLog::sharedLog()->WriteNormalLog("WinProc->δ��ȷ���豸·��");
		}		
		break;
	case WM_DEVICECHANGE:
		if (pCCtrlUSB)
		{
			pCCtrlUSB->OnDeviceChange(wParam, lParam);
		}		
		return (TRUE);
	case WM_DESTROY:		
		::PostQuitMessage(0);
		break;
	default:
		break;
	}

	return ::DefWindowProc(hWnd, message, wParam, lParam);
}

//���ڴ�����������Ϣ�߳�
DWORD WINAPI CreateWindowThreadPro(LPVOID lpParameter)
{
	WNDCLASS wc;  
	MSG msg;

	wc.style = CS_VREDRAW | CS_HREDRAW;
	wc.lpfnWndProc = (WNDPROC)WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hinst;
	wc.hIcon = NULL;
	wc.hCursor = NULL;
	wc.hbrBackground = NULL;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = _T("USBControlledStamperDev");

	RegisterClass(&wc);

	hwndDLG = ::CreateWindow(
		_T("USBControlledStamperDev"), //����������
		_T(""), //���ڱ���
		WS_OVERLAPPEDWINDOW, //���ڷ�񣬶���Ϊ��ͨ��
		0, //����λ�õ�x����
		0, //����λ�õ�y����
		1, //���ڵĿ��
		1, //���ڵĸ߶�
		NULL, //�����ھ��
		NULL, //�˵����
		hinst, //Ӧ�ó���ʵ�����
		NULL ); //���ڴ�������ָ��

	if(!hwndDLG) return 1;
	//���ش���
	::ShowWindow(hwndDLG, SW_HIDE);
	//���ڿͻ��������
	::UpdateWindow(hwndDLG);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}
