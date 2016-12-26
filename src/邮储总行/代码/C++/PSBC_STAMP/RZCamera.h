// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� RZCAMERA_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// RZCAMERA_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�

#ifndef _RZCAMERA_H
#define _RZCAMERA_H

#ifdef RZCAMERA_EXPORTS
#define RZCAMERA_API extern "C" __declspec(dllexport) int 
#else
#define RZCAMERA_API extern "C" __declspec(dllimport) int 
#endif

enum     CAMPARAM {  
	brightness				= 0,
	contrast				= 1,
	hue						= 2,
	saturation				= 3,
	sharpness				= 4,
	whitebalance			= 6,
	backlightcompensation	= 7,
	zoom					= 10,
	offsetY					= 13,
	offsetX					= 14,
	expouse					= 15,
	gamma					= 16,
	colormode				= 17,
	flipmode				= 18,
	aeing					= 19,
	awbing					= 20
};

enum CAMERAINDEX
{
	PAPERCAMERA,	//ƾ֤����ͷ
	ENVCAMERA,		//��������ͷ
	SIDECAMERA		//��������ͷ
};

enum IMAGEFORMAT
{
	FORMATJPG,		//JPG��ʽ
	FORMATBMP		//BMP��ʽ
	};

#define RET_SUCCESS 0

/*==============================================================
����:OpenCamera	
����:������ͷ

����:	camType		����ͷ���ͣ�0��ƾ֤����ͷ��1����������ͷ��2����������ͷ��

����ֵ     0:�ɹ�  
	    ����:ʧ��		
--------------------------------------------------------------*/
RZCAMERA_API OpenCamera(IN CAMERAINDEX camType);

/*==============================================================
����:CloseCamera	
����:�ر�����ͷ

����:	camType		����ͷ���ͣ�0��ƾ֤����ͷ��1����������ͷ��2����������ͷ��

����ֵ     0:�ɹ�  
	    ����:ʧ��		
--------------------------------------------------------------*/
RZCAMERA_API CloseCamera(IN CAMERAINDEX camType);

/*==============================================================
����:StartPreview	
����:��ʼԤ��

����:	camType		����ͷ���ͣ�0��ƾ֤����ͷ��1����������ͷ��2����������ͷ��
		nWidth		���ڿ��
		nHeight		���ڸ߶�
		hwndParent	�����ھ��

����ֵ     0:�ɹ�  
	    ����:ʧ��		
--------------------------------------------------------------*/
RZCAMERA_API StartPreview(IN CAMERAINDEX camType,IN int nWidth,IN int nHeight, IN HWND hwndParent);

/*==============================================================
����:StopPreview	
����:��ʼԤ��

����:	camType		����ͷ���ͣ�0��ƾ֤����ͷ��1����������ͷ��2����������ͷ��

����ֵ     0:�ɹ�  
	    ����:ʧ��		
--------------------------------------------------------------*/
RZCAMERA_API StopPreview(IN CAMERAINDEX camType);

/*==============================================================
����:SetResolution
����:���÷ֱ���

����:	camType		����ͷ���ͣ�0��ƾ֤����ͷ��1����������ͷ��2����������ͷ��
		nWidth		���
		nHeight		�߶�

����ֵ     0:�ɹ�  
	    ����:ʧ��		
--------------------------------------------------------------*/
RZCAMERA_API SetResolution(IN CAMERAINDEX camType,ULONG nWidth, ULONG nHeight);

/*==============================================================
����:SetDPIValue	
����:����JPGͼƬ��DPIֵ

����:	camType		����ͷ���ͣ�0��ƾ֤����ͷ��1����������ͷ��2����������ͷ��
		nDPIx       Ϊ���DPIֵ
		nDPIy       Ϊ�ߵ�DPIֵ

����ֵ     0:�ɹ�  
	    ����:ʧ��		
--------------------------------------------------------------*/
RZCAMERA_API SetDPIValue(IN CAMERAINDEX camType, IN int nDPIx, IN int nDPIy);

/*==============================================================
����:SetParameter	
����:�����������

����:	camType		����ͷ���ͣ�0��ƾ֤����ͷ��1����������ͷ��2����������ͷ��
		DLParam     ��������
		lvalue      ������ֵ

����ֵ     0:�ɹ�  
	    ����:ʧ��		
--------------------------------------------------------------*/
RZCAMERA_API SetParameter(IN CAMERAINDEX camType, CAMPARAM  CamParam, long lvalue);

/*==============================================================
����:CapturePhoto	
����:����

����:	camType		����ͷ���ͣ�0��ƾ֤����ͷ��1����������ͷ��2����������ͷ��
		imgFormat	����ͼƬ��ʽ(0��JPG��ʽ��1��BMP��ʽ)
		szPath		������չ����ȫ·��

����ֵ     0:�ɹ�  
	    ����:ʧ��		
--------------------------------------------------------------*/
RZCAMERA_API CapturePhoto(IN CAMERAINDEX camType, IN IMAGEFORMAT imgFormat, IN char *szPath);

/*==============================================================
����:StartCaptureVideo	
����:��ʼ¼��

����:	camType		����ͷ���ͣ�0��ƾ֤����ͷ��1����������ͷ��2����������ͷ��
		szPath		������չ����ȫ·��(.avi��ʽ)

����ֵ     0:�ɹ�  
	    ����:ʧ��		
--------------------------------------------------------------*/
RZCAMERA_API StartCaptureVideo(IN CAMERAINDEX camType, IN char *szPath);

/*==============================================================
����:StopCaptureVideo	
����:ֹͣ¼��

����:	camType		����ͷ���ͣ�0��ƾ֤����ͷ��1����������ͷ��2����������ͷ��

����ֵ     0:�ɹ�  
	    ����:ʧ��		
--------------------------------------------------------------*/
RZCAMERA_API StopCaptureVideo(IN CAMERAINDEX camType, IN char *szPath);

RZCAMERA_API RegisterPlugin();


#endif