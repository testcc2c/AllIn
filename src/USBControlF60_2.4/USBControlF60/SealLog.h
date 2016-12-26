/*
**	@file	SealLog.h
**	������־���
**	@version 1.0 
**	@date  
**	@author 
**
**
*/
#ifndef _SEAL_LOG_H
#define _SEAL_LOG_H

#ifdef __cplusplus
extern "C" 
{
#endif

#ifdef  USBSEALLOG_EXPORTS
#define USBSEALLOG_API __declspec(dllexport)
#else
#define USBSEALLOG_API __declspec(dllimport)
#endif

/**
* ����:WriteSealLog	
* ����:д��־�ļ�
* 
* ����:	
* @parm int level ��־����(0��д 1��ʾ 2���� 3���� 4����)
* @parm onst char* szLog ��־����
* ����ֵ   �� 		
*/
USBSEALLOG_API  void WriteSealLog(int level, const char* szLog);
/**
* ����:SetLogRoot
* ����:������־�ĸ�Ŀ¼

* ����
* @param const char* szLogPath ��־�ļ��ĸ�Ŀ¼
* @return ��
*/
USBSEALLOG_API  void SetLogRoot(const char* szLogPath);
/**
* ����:SetLogLevel
* ����:������־����

* ����
* @param int level(0��д 1��ʾ 2���� 3���� 4����)
* @return ��
*/
USBSEALLOG_API  void SetLogLevel(int level);
#ifdef __cplusplus
}
#endif
#endif