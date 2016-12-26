#ifndef ImageProcess_H_
#define ImageProcess_H_
#ifdef IMAGEPROCESS_EXPORTS
#define MYLIBDLL extern "C" _declspec(dllexport) 
#else
#define MYLIBDLL extern "C" _declspec(dllimport) 
#endif
#include <atltypes.h>
#include <gdiplus.h>

#define __ImageProcessDllVersion301__	1
#define JUDGE_PAPER_A4	2000
typedef int (CALLBACK *MotionDetectRev)(unsigned int uMsg,char* lParam);//�ƶ������Ϣ�ص�

//�������ӿ�˵��
/************************************************************************
 * ����:Ʊ���Զ���ת���и�ڱߣ���A4������ת����
 * ����:
		*srcName Դͼ��ȫ·������ �磺d:\1.jpg
        *dstName �г���Ʊ��·��
 * ���
        ���� 0 �ɹ�
		���� -1 ͼƬ����ʧ��
 ************************************************************************/
MYLIBDLL int STRoateAndExtatBillImage(const char* srcName, const char* dstName);
/**********************************************************************
 * ���Ʊ���Ƿ����ĳ����ʽ,��ȡxml�ļ�����
 * ����:
		*src_file_name:�����ȷ���ļ���
		*ResultData:���ƥ����Ϣ(ģ����_ģ��ID_ƥ����)��eg.����Ʊ��_1_0.801
		*_Angel:���Ʊ�ݽǶ�(��:0,��:180)
		*stamppos:�����ӡλ��(��x:123,y:456,�����:123@456)
 * ���:
		* 0-OK
		*-1-ERROR,Դͼ��·��������
		*-2-ERROR,�����˲�֧�ֵ�ģ������
		*-3-ERROR,��ȡģ�����
		*-8-ERROR,xml�ļ���ȡʧ��
		*-4-ERROR,����ģ��ʶ���ʵ���0.1
 *
 **********************************************************************/
MYLIBDLL int STAutoIdentifyEx2(const char* src_file_name,char *ResultData,char *_Angel,char* stamppos);

/**********************************************************************
 * ��Ʊ��ָ���������ʶ��
 * ����:
		*src_file_name:����Ʊ���ļ���
		*PointString:ʶ���������Ϸ���+��ߣ�eg.100,100,200,200@��
		*OCRresult:����ʶ����

 * ���:
		* 0-OK
		*-1-ERROR,Դͼ��·��������
		*-2-ERROR,�����˲�֧�ֵ�ģ������
		*-3-ERROR,��ȡģ�����
 *
 **********************************************************************/
MYLIBDLL int  STImageAreaOCREx(char* src_file_name,char* PointString,char* OCRresult);
/**********************************************************************
 * ����Ƕ�Ѱ�Ҹ��µ�
 * ����:
		*Imagefile ԭͼƬȫ·�� 
		*chpos ���Ʊ�����ĵ���ͼƬ�е����λ�ã�PS�����ܵ���0(��x:-123,y:456,������:-123@456)
		*chinputangle ͼƬ�бߺ�Ʊ��ʶ���ͼƬ����0 ����180 ����
 * ���:
		*chstamppos (��x:-123,y:456,�����:-123@456)
		*chStamAngel ��������˳ʱ����ת�Ƕ�
		* ����ֵ���ȽϽ�� ret;
		*		  -1������ͼƬ·��Ϊ�� 
		*		  -2��ͼƬ��ȡʧ��

 *
 **********************************************************************/
//MYLIBDLL int STSeachSealPoint(char* Imagefile,int StamX,int StamY,int* StamPointX,int* StamPointY,double *StamAngel,int inputangle);
MYLIBDLL int STSeachSealPoint(char* Imagefile,char* chpos,char* chinputangle,char* chstamppos,char *chStamAngel);
/************************************************************************
// �������ƣ�STMerge_image()
// �������ܣ�����ͼ�ϲ�(���鱣��ΪJPG��ʽ)
// ����˵����char *src_file_name1, ͼƬ1·��
//           char *src_file_name2, ͼƬ2·��
//			 dst_file_name,�ϲ���ͼƬ·��
//			 
// �� �� ֵ��0
// ��    ע��
************************************************************************/
MYLIBDLL int STMerge_image(const char* src_file_name1,const char* src_file_name2,const char* dst_file_name);

/************************************************************************
// �������ƣ�RotateImageAngle()
// �������ܣ��Զ���Ƕ���תͼ��
// ����˵����IplImage *src, ����תͼ��
//           double angle, ��ת�Ƕȣ�-360~360��
//           
// �� �� ֵ��IplImage *dst����ת��ͼ��
// ��    ע��
************************************************************************/
MYLIBDLL int STRotateImageAngle(const char* srcName, const char* dstName, double angle);

/************************************************************************
 * ����:Ʊ���ֶ��б�
 * ����:
		*srcName Դͼ��ȫ·������ �磺d:\1.jpg
		*PointString:ʶ���������Ϸ���+��ߣ�eg.100,100,200,200@��
        *dstName �г���Ʊ��·��
 * ���
        ���� 0 �ɹ�
		���� -1 ͼƬ����ʧ��
 ************************************************************************/
MYLIBDLL int STManualExtatBillImage(const char* srcName,const char* PointString, const char* dstName);

/************************************************************************
 * ת��ͼ��DPI
 * ����:
        *file_name:Դͼ�����·��
		*quality:��Ҫ��ͼ��ߴ�ת���ı���
		*dpi:Ŀ��DPI��ֵ
		*dst_file_name:Ŀ��ͼ�����·��
		*int TypeFlag��ԴͼƬ��ʽ��Ĭ��Ϊ3��JPG��
 * ���:
 * 0-OK
 *-1-ERROR ����Դͼ��ʧ��
 *-2-ERROR дĿ��ͼ��ʧ��
 *
 ��ע�� ֧��ͼƬ��ʽ��
 //		CXIMAGE_FORMAT_BMP = 1,
 // 	CXIMAGE_FORMAT_GIF = 2,
 // 	CXIMAGE_FORMAT_JPG = 3,
 // 	CXIMAGE_FORMAT_PNG = 4,
 // 	CXIMAGE_FORMAT_ICO = 5,
 // 	CXIMAGE_FORMAT_TIF = 6,
 ************************************************************************/
MYLIBDLL int STSetImageDPI(const char* src_file_name,BYTE quality,int dpi,const char* dst_file_name,int TypeFlag=3);

/************************************************************************
// �������ƣ�RotateImageAngle()
// �������ܣ��Զ���Ƕ���תͼ��
// ����˵����IplImage *src, ����תͼ��
//           double angle, ��ת�Ƕȣ�-360~360��
//           int opt,ѡ����ת��ʽ
// �� �� ֵ��IplImage *dst����ת��ͼ��
// ��    ע��
************************************************************************/
MYLIBDLL int RotateImageAngle(const char* srcName, const char* dstName, double angle);

/************************************************************************
// �������ƣ�ImageResizeScale()
// �������ܣ�ͼ�񰴱����任
// ����˵����char *src_file_name, ������ͼ��
//           double scale, ����(scale>0.0)
// �� �� ֵ��0
// ��    ע��
************************************************************************/
MYLIBDLL int ImageResizeScale(const char* src_file_name,double scale);

/************************************************************************
// �������ƣ�ImageResize()
// �������ܣ�ͼ��ָ����߱任
// ����˵����char *src_file_name, ������ͼ��
//           int Newwidth,int Newheight, ���ͼ����
// �� �� ֵ��0
// ��    ע��(Newwidth>0)&&(Newheight>0)
************************************************************************/
MYLIBDLL int ImageResize(const char* src_file_name,int Newwidth,int Newheight);

/************************************************************************
// �������ƣ�Blending_image()
// �������ܣ�����ͼƬ�ں�(���鱣��ΪJPG��ʽ)
// ����˵����char *src_file_name, �������ͼƬ
//           char *src_file_name1, LOGͼƬ
//			 dst_file_name,�ںϺ�ͼ��
//			 double alpha,src_file_nameͼƬ�����,��Χ�ڣ�0.0~1.0��,src_file_name1ͼƬ����ȵ��ڣ�1-alpha��
//			 CPoint beginPoint,LOG�ڱ������ͼƬ�ں���ʼλ�� 
// �� �� ֵ��0
// ��    ע��
************************************************************************/
MYLIBDLL int Blending_image(const char* src_file_name,const char* src_file_name1,const char* dst_file_name,double alpha,CPoint beginPoint);


/************************************************************************
// �������ƣ�Colortoblack_white()
// �������ܣ���ɫͼƬתΪ�ڰ�
// ����˵����char *src_file_name, ������ͼ��
//           char *src_file_name, ���ͼ��
// �� �� ֵ��0
// ��    ע��
************************************************************************/
MYLIBDLL int Colortoblack_white(const char* src_file_name,const char* dst_file_name );

/************************************************************************
 * ת��ͼ��DPI
 * ����:
        *file_name:Դͼ�����·��
		*rate:��Ҫ��ͼ��ߴ�ת���ı���
		*dpi:Ŀ��DPI��ֵ
		*dst_file_name:Ŀ��ͼ�����·��
		*int TypeFlag��ԴͼƬ��ʽ��Ĭ��Ϊ3��JPG��
 * ���:
 * 0-OK
 *-1-ERROR ����Դͼ��ʧ��
 *-2-ERROR дĿ��ͼ��ʧ��
 *
 ��ע�� ֧��ͼƬ��ʽ��
 //		CXIMAGE_FORMAT_BMP = 1,
 // 	CXIMAGE_FORMAT_GIF = 2,
 // 	CXIMAGE_FORMAT_JPG = 3,
 // 	CXIMAGE_FORMAT_PNG = 4,
 // 	CXIMAGE_FORMAT_ICO = 5,
 // 	CXIMAGE_FORMAT_TIF = 6,
 ************************************************************************/
MYLIBDLL int SetImageDPI(const char* src_file_name,double rate,int dpi,const char* dst_file_name,int TypeFlag=3);

/************************************************************************
 * ����:���Ʊ���ĸ����㣬��������͸������г�����Ʊ�ݣ��Զ��бߣ�(�߳��бߣ��첽)
 * ����:
		*srcName Դͼ��ȫ·������ �磺d:\1.jpg
        *dstName �г���Ʊ��·��
        *
 * ���
        ���� 0 �ɹ�
		���� -1 ͼƬ����ʧ��
 ************************************************************************/

MYLIBDLL int RoateAndExtatBillImage(const char* srcName, const char* dstName);


/************************************************************************
 * ����:���Ʊ���ĸ����㣬��������͸������г�����Ʊ�ݣ��Զ��бߣ�
 * ����:
		*srcName Դͼ��ȫ·������ �磺d:\1.jpg
        *dstName �г���Ʊ��·��
        *FlagWebData �ж��Ƿ�ΪHTTPͼƬ��trueΪHTTPͼƬ��falseΪ����ͼƬ��Ĭ��Ϊfalse
 * ���
        ���� 0 �ɹ�
		���� -1 ͼƬ����ʧ��
 ************************************************************************/
MYLIBDLL int RoateAndExtatBillImageEx(const char* srcName, const char* dstName,bool FlagWebData=false);


/************************************************************************
 * ����:Ʊ���Զ���ת���и�ڱ�(�߳��бߣ��첽;��A4������ת����)
 * ����:
		*srcName Դͼ��ȫ·������ �磺d:\1.jpg
        *dstName �г���Ʊ��·��
        *
 * ���
        ���� 0 �ɹ�
		���� -1 ͼƬ����ʧ��
 ************************************************************************/
MYLIBDLL int RoateAndExtatBillImage90(const char* srcName, const char* dstName);

//MYLIBDLL IplImage* rotateImage1(IplImage* img,int degree);
/************************************************************************
 * ����:Ʊ���Զ���ת���и�ڱߣ���A4������ת����
 * ����:
		*srcName Դͼ��ȫ·������ �磺d:\1.jpg
        *dstName �г���Ʊ��·��
 * ���
        ���� 0 �ɹ�
		���� -1 ͼƬ����ʧ��
 ************************************************************************/
MYLIBDLL int NewRoateAndExtatBillImage(const char* srcName, const char* dstName);

MYLIBDLL int STRoateAndExtatBillImageEx(const char* srcName, const char* dstName);
/************************************************************************
 * ����:��ʽƱ���и�
 * ����:
*srcName Դͼ��ȫ·������ �磺d:\1.jpg
        *dstName �г���Ʊ��·��
        *RoatFlag ͼƬ�Ƿ���Ҫ��ת90��
 * ���
        ���� 0 �ɹ�
���� -1 ͼƬ����ʧ��
 ************************************************************************/
MYLIBDLL int NewRoateAndExtatBillImageEx(const char* srcName, const char* dstName,bool FlagCase=false);

/************************************************************************
 * ����:����ν�ͼ
 * ����:
		*src_file_name Դͼ��ȫ·������ �磺d:\1.jpg
        *dst_file_name �г���Ʊ��·��
        *CPoint *SquePoint �������������
		*int MaxNum ָ������ĳ�Ա��
 * ���
        ���� 0 �ɹ�
		���� -1 ͼƬ����ʧ��
 *��ע ���������밴˳��洢
 ************************************************************************/
MYLIBDLL int Arbitrary_cutting(const char* src_file_name,const char* dst_file_name,const CPoint *SquePoint,int MaxNum);


/************************************************************************
 * ����:ͼƬ��ʽת��
 * ����:
		*src_file_name Դͼ��ȫ·������ �磺d:\1.jpg
        *dst_file_name ���ͼƬ·�����磺C:\\ss.bmp

 * ���
        ���� 0 �ɹ�
		���� -1 ͼƬ����ʧ��
 *��ע 
		Ŀǰ֧�ֵ�ͼ���ʽ������
		Windowsλͼ�ļ� - BMP, DIB��
		JPEG�ļ� - JPEG, JPG, JPE��
		��Яʽ����ͼƬ - PNG��
		��Яʽͼ���ʽ - PBM��PGM��PPM��
		Sun rasters - SR��RAS��
		TIFF�ļ� - TIFF��TIF;
		OpenEXR HDR ͼƬ - EXR;
		JPEG 2000 ͼƬ- jp2
 ************************************************************************/
MYLIBDLL int ImageConverter(const char* src_file_name,const char* dst_file_name);

/**********************************************************************
 * ���Ʊ���Ƿ����ĳ����ʽ,��ֻ֧��ת��֧Ʊ��֧��ƾ֤�͵��ƾ֤
 * ����:
		*src_file_name:�����ȷ���ļ���
		*template_type:ģ��������
		*compare_rate:ƥ����,���ֵ����0.8��ֱ�����,�����з�����,
		              һ�����,���ֵ����0.8������Ϊ��ʽ����ȷ.....
		*orient_flag:������,0-ok,1-��Ҫ180����ת
		*template_path:ģ��·��
 * ���:
		* 0-OK
		*-1-ERROR,Դͼ��·��������
		*-2-ERROR,�����˲�֧�ֵ�ģ������
		*-3-ERROR,��ȡģ�����
 *
 **********************************************************************/
MYLIBDLL int AutoIdentify(const char* src_file_name,int *modelID,int *or_flag,char *modelname);

MYLIBDLL int AutoIdentifyEx(const char* src_file_name,int *modelID,int *or_flag,char *modelname,bool FlagWebData=false);


/**********************************************************************
 * ���Ʊ���Ƿ����ĳ����ʽ,��ȡxml�ļ�����
 * ����:
		*src_file_name:�����ȷ���ļ���
		*ResultData:���ƥ����Ϣ(ģ����_ģ��ID_ƥ����)��eg.����Ʊ��_1_0.801
		*FlagWebData:�Ƿ�Ϊ����ͼƬ,Ĭ��false(����ͼƬ)
 * ���:
		* 0-OK
		*-1-ERROR,Դͼ��·��������
		*-2-ERROR,�����˲�֧�ֵ�ģ������
		*-3-ERROR,��ȡģ�����
		*-8-ERROR,xml�ļ���ȡʧ��
		*-4-ERROR,����ģ��ʶ���ʵ���0.1
 *
 **********************************************************************/
MYLIBDLL int NewAutoIdentifyEx(const char* src_file_name,char *ResultData,bool FlagWebData);
MYLIBDLL int NewAutoIdentifyEx2(const char* src_file_name,char *ResultData,bool FlagWebData);
MYLIBDLL int STAutoIdentifyEx(const char* src_file_name,char *ResultData);
MYLIBDLL int STAutoIdentifyAndFlag(const char* src_file_name,char *ResultData,char * iflag);
/**********************************************************************
 * �򵥶�2��Ʊ�ݽ��бȽϣ����������
 * ����:
		*object_file_name:�����ļ���
		*object_file_name1:�����ļ���1
		*CompareEve:ƥ����,���ֵ����0.8�����Ϊ��ͬ

 * ���:
		* 0-OK
		*-1-ERROR,Դͼ��·��������
		*-2-ERROR,�����˲�֧�ֵ�ģ������
		*-3-ERROR,��ȡģ�����
 *
 **********************************************************************/
MYLIBDLL int AutoCompare(const char* object_file_name,const char* object_file_name1,double *CompareEve);

/**********************************************************************
 * ��Ʊ��ָ���������ʶ��
 * ����:
		*src_file_name:����Ʊ���ļ���
		*PointString:ʶ���������Ϸ���+��ߣ�eg.100,100,200,200@��
		*OCRresult:����ʶ����

 * ���:
		* 0-OK
		*-1-ERROR,Դͼ��·��������
		*-2-ERROR,�����˲�֧�ֵ�ģ������
		*-3-ERROR,��ȡģ�����
 *
 **********************************************************************/
MYLIBDLL int DllImageAreaOCR(const char* src_file_name,int SectionID,int PartionID,char* OCRresult,bool FlagWebData=false);

MYLIBDLL int DllImageAreaOCREx(const char* src_file_name,const char* PointString,char* OCRresult,bool FlagWebData=false);

MYLIBDLL int  STImageToPointString(char* src_file_name,char* PointString);

/**********************************************************************
 * ����DLL�����Ϣ
 * ����:
		*ActiveXData:������Ϣ

 * ���:
		* 0-OK
 *
 **********************************************************************/
MYLIBDLL int HaveActiveXData(char *ActiveXData);

/**********************************************************************
 * ��ֽ��ʶ��
 * ����:
		*SrcImagePath:ͼƬ��Ϣ

 * ���:
		* *resultFlag��0����ֽ��1��ֽ
 * ����:
		* -1:ͼƬ��ȡʧ�ܣ�-2:����·������ȷ��0-OK
 **********************************************************************/
MYLIBDLL int PaperReconfig(char *SrcImagePath,int *resultFlag);

/**********************************************************************
 * �ж�Ʊ�ݰڷŷ���
 * ����:
		*ImagePath:ͼƬ��Ϣ

 * ���:
		* *JudgeResult��0 ���ţ�1 ���
 * ����:
		* -1:ͼƬ��ȡʧ�ܣ�-2:����·������ȷ��0-OK
 **********************************************************************/
MYLIBDLL int PaperDirectJudge(char* ImagePath,int* JudgeResult);


MYLIBDLL int TakePicture(char* szImageFile,int nWidth,int nHight,int CamraID);

/**********************************************************************
 * ����ͷ���սӿڣ����֧��3��ͬʱ���գ�
 * ����:
 * ���:
		* 0-OK
		*-1-ERROR ���豸ʧ��
		*-2-ERROR ֡Ϊ��
		*-3-ERROR ����Ƿ�
 *
 **********************************************************************/
MYLIBDLL int OpenCmareaEx(int CamraNums,char *ConfigFile);
MYLIBDLL int OpenCmareaExID(int CamraNums,const char *ConfigFile);
MYLIBDLL int TakePictreEx(int CameraID,const char *ImageName);

//HavePictreEx();�������ñ��ID��Gdiplus::Bitmapָ�룬���Gdiplus::Bitmap��Ϣ
MYLIBDLL int HavePictreEx(int CameraID,Gdiplus::Bitmap* &pCBitmap);
MYLIBDLL int STOpenCmareaEx(byte CameraID);
MYLIBDLL HBITMAP STHavePictreEx(byte CameraID);
MYLIBDLL int STReleaseBitMap(HBITMAP hbittmap);
MYLIBDLL int STCloseCameraId(byte CameraID);
/**********************************************************************
*HavingUcharEncode();�������ñ��ID��char*ָ�룬���JPG�ļ�����Ϣ������С
*UcharEncodeRelease;�ͷ�JPG�ļ���ָ��
*���÷�ʽ��
	open*
	unsigned char *databuf=NULL;
	long length=0;
	HavingUcharEncode(1,&databuf,&length);
	....
	UcharEncodeRelease(&databuf);
	close*
 **********************************************************************/
MYLIBDLL int HavingUcharEncode(int CameraID,unsigned char** EncodeBuf,long *ByeLength);
MYLIBDLL int UcharEncodeRelease(unsigned char** EncodeBuf);
MYLIBDLL int CloseCameraEx();
MYLIBDLL int CloseCameraId(int camearaid);


/*******************ȫ�ֻص�����**************************************
//MyCallBack ��������ֵ��unsigned int uMsg,char* lParam
*****Case1:lParamΪ��,��ʱΪ��Ƶ���ص���Ϣ
			����ֵ��0xO3,����ͷ��ʧ��;0xO4,����ͷ�ֱ��������ò�һ��;
			0xO5,��������MASKδ����ʧ��;0x06,��ⱨ��;0x07,��Ƶ�ڵ�
*****Case2:lParamΪ"CP"����ʱΪ¼��ص���Ϣ
			����ֵ��0xO1,����ͷ��ʧ��;0xO2,��Ƶ�ļ�����ʧ��;
			0x03,¼��������Ϣ����ȷ;0x04,֡��ȡʧ��;0x05,֡д��ʧ��
*****Case2:lParamΪ"MOTCAP"����ʱΪ��Ƶ��Ⲣ¼��ص���Ϣ
			����ֵ��0xO2,��Ƶ�ļ�����ʧ��;0xO3,����ͷ��ʧ��;0xO4,����ͷ�ֱ��������ò�һ��;
			0xO5,��������MASKδ����ʧ��;0x06,��ⱨ��;0x07,��Ƶ�ڵ�		
***********************************************************************/
MYLIBDLL int MotionDe_CallBack( MotionDetectRev MyCallBack );



//�ƶ�������functions
/**********************************************************************
 * ������Ƶ���
 * ����:*DetectConfigPath �����ļ�Ŀ¼(eg.C://PIC)
 * ���:
		* 0-OK
 *
 **********************************************************************/
MYLIBDLL int Begin_Motion_Detect(char *DetectConfigPath);

/**********************************************************************
 * ������Ƶ���
 * ����:
 * ���:
		* 0-OK
 *
 **********************************************************************/
MYLIBDLL int End_Motion_Detect();

/**********************************************************************
 * ������Ƶ�������ͷ�ڵ�ģ��
 * ����:*SrcImage ģ��ԭͼ *ConfigPath ģ�������ļ�Ŀ¼(eg.C://PIC)
 * ���:
		* 0-OK
 *
 **********************************************************************/
MYLIBDLL int ConfigHashImage(char* SrcImage,char* ConfigPath);

/**********************************************************************
 * ����¼���߳�
 * ����:* CamraNums CameraConfig.ini�����е�[CameraNum*]���+1
		* *ConfigFile CameraConfig.ini���þ���·��
		* *CaptureName ¼����Ƶȫ·������ eg.c://pic//out.avi
		* NoCompress ��Ƶ�ļ����Ƿ�ѹ����Ĭ��Ϊѹ��XVID��ps.��Ҫ��װXVID������
 * ���:
		* 0-OK
 *
 **********************************************************************/
MYLIBDLL int CameraCapture(int CamraNums,char *ConfigFile,char* CaptureName,bool NoCompress=false);

/**********************************************************************
 * ֹͣ¼���߳�
 * ����:
 * ���:
		* 0-OK
 *
 **********************************************************************/
MYLIBDLL int End_CameraCapture();


/**********************************************************************
 * �����ƶ���Ⲣ¼���߳�
 * ����:* *DetectConfigPath CameraConfig.ini���þ���·��
		* *CaptureName ¼����Ƶȫ·������ eg.c://pic//out.avi
		* NoCompress ��Ƶ�ļ����Ƿ�ѹ����Ĭ��Ϊѹ��XVID��ps.��Ҫ��װXVID������
 * ���:
		* 0-OK
 *
 **********************************************************************/
MYLIBDLL int Begin_Motion_Capture(char *DetectConfigPath,char* CaptureName,bool NoCompress=false);


/**********************************************************************
 * ֹͣ�ƶ���Ⲣ¼���߳�
 * ����:
 * ���:
		* 0-OK
 *
 **********************************************************************/
MYLIBDLL int End_Motion_Capture();

/**********************************************************************
 * ֹͣ�ƶ���Ⲣ¼���߳�
 * ����:*SrcName1 *SrcName2 ���Ƚϵ�ͼƬ����+·����
 * ���:
		* ����ֵ���ȽϽ�� ret;
		*		  -1��ͼƬ��ȡʧ�� 
		*		  -2��ͼƬ�߶Ȳ�����10
		*		  1-64���������Ƚ�ֵ(�ݶ�: ret<=5 ͼƬ�ǳ����� 5<ret<=10 ͼƬ�󲿷����� ret>=10ͼƬ������)
 *
 **********************************************************************/
MYLIBDLL int CompareImageSimilar(const char* SrcName1,const char* SrcName2);

/**********************************************************************
 * ��������ͷ������Ϣ
 * ����:*int CamraID ����ͷID
		*int brightness  �� ��
		*int constrast  �Աȶ�
		*int hue  ɫ ��
		*int saturation  ���Ͷ�
		*int sharpness  ������
		*int whitebalance  ��ƽ��
		*int gain  �ع�ֵ
 * ���:
		* ����ֵ��0 �ɹ�,-1 ����ͷIDΪ������-2 ����ʧ��;
 * ʹ��˵����
		* �ýӿڴ��������amcap�������:ѡ��->��Ƶ��׽������->��ƵProc Amp�˵��²�������һ�£�
		* ��������������ں󣬽����ò�������
 * ע������:
		* �е�����ͷ����ֵ�ڵ���󣬻��Զ��ָ�Ĭ��ֵ�������������ͷ��ÿ�ε����κ���Ҫ��������һ��
 **********************************************************************/
MYLIBDLL int ImageDll_SetVedioProperties(int CamraID,int brightness/*�� ��*/, int constrast/*�Աȶ�*/,
	int hue/*ɫ ��*/, int saturation/*���Ͷ�*/, int sharpness/*������*/,
	int whitebalance/*��ƽ��*/, int gain/*�ع�ֵ*/);

/**********************************************************************
 * ����Ƕ�Ѱ�Ҹ��µ�
 * ����:
		*Imagefile ԭͼƬȫ·�� 
		*StamX��StamY ���Ʊ�����ĵ���ͼƬ�е����λ�ã�PS�����ܵ���0
		*DirectFlag ͼƬ�бߺ�Ʊ��ʶ���ͼƬ����true ����false ����
 * ���:
		*CPoint* StamPoin ���ظ��µ�
		*double *StamAngel ��������˳ʱ����ת�Ƕ�
		* ����ֵ���ȽϽ�� ret;
		*		  -1������ͼƬ·��Ϊ�� 
		*		  -2��ͼƬ��ȡʧ��

 *
 **********************************************************************/
MYLIBDLL int SeachSealPoint(char* Imagefile,int StamX,int StamY,CPoint* StamPoint,double *StamAngel,bool DirectFlag/*(true ����false ����)*/);
//MYLIBDLL int STSeachSealPoint(char* Imagefile,int StamX,int StamY,int* StamPointX,int* StamPointY,double *StamAngel,int inputangle);
/**********************************************************************
 * ���ɵ���ӡ��ͼƬ Ĭ�ϳߴ磺96dpi Բֱ��Ϊ42mm
 * ����:
		*pathName ����ͼƬȫ·������
		*StampType ����ӡ������:1.Բ�� 2.��Բ 3.����
		*F_str ӡ������(eg."�й����в�������")
		*S_str ӡ�¸�����Ϣ(eg."��̩������")
		*T_str ӡ������(eg."201602")
 * ���:		
		* ����ֵ���ȽϽ�� ret;
		*		  -1������ͼƬ·��Ϊ�� 
		*		   0,OK;

 *
 **********************************************************************/
MYLIBDLL int DrawStamp(char* pathName,int StampType,char* F_str,char* S_str,char* T_str);

/**********************************************************************
 * ����ҵ����ˮ��ͼƬ Ĭ�ϳߴ磺96dpi�£���40mm����10mm
 * ����:
		*pathName ����ͼƬȫ·������
		*StampType ����ӡ������:1.Բ�� 2.��Բ 3.����
		*Rectflag  ͼƬ�Ƿ��б߿�
		*F_str ��ˮ������(eg."AB123456")
 * ���:		
		* ����ֵ���ȽϽ�� ret;
		*		  -1������ͼƬ·��Ϊ�� 
		*		   0,OK;

 *
 **********************************************************************/
MYLIBDLL int DrawRectData(char* pathName,char* F_str,bool Rectflag);

#endif
