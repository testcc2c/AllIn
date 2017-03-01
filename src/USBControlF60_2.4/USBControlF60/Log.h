#pragma once
#include <direct.h>
#include <time.h>
#include <assert.h>
#include <io.h>

// class Lock  
// {  
// private:         
// 	CriticalSection m_cs;  
// public:  
// 	Lock(CriticalSection  cs) : m_cs(cs)  
// 	{  
// 		m_cs.Lock();  		
// 	}  
// 	~Lock()  
// 	{  
// 		m_cs.Unlock();  
// 	}  
// }; 

class CLog
{
private:
	CLog(void){
		m_bLog = false;
		m_strDirPath.clear();
	}
	
	class CGarbo   //����Ψһ��������������������ɾ��CSingleton��ʵ��  
	{  
	public:  
		~CGarbo()  
		{  
			if(CLog::m_pInstance)  
				delete CLog::m_pInstance;  
		}  
	};  
	static CGarbo Garbo;
private:
	bool m_bLog;
	string m_strDirPath;
	static CLog* m_pInstance;	
public:	
	static CLog* sharedLog(void);	

	string GetCurrentModulePath();
	bool CreateMultiLevelDirectory(const char *strFilePathName);
	void DeleteHistoryLog(const char* filepath);

	//��־��¼
	void WriteLog(const char* szLogFileName, const char* szLog);

    void WriteLog(int level, const char* szLog);

	// ��־���Լ�¼
	void WriteDebugLog(const char *fmt, ...);

	// ��¼һ����־
	void WriteNormalLog(const char *fmt, ...);

	//��¼USB������Ϣ
	void CLog::WriteUSBDebugLog(unsigned char *pData, int length);

	void WriteUSBdata(const char *szMsg, unsigned char *pData, int length );

	// ��¼�ϲ������־
	void WriteAppLog(const char* szLogFileName, const char* szLog);
};

