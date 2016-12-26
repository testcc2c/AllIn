
/************************************************* 
Copyright:yuanyi 
Author: 
Date:2016-05-24 
Description: �����ݼ�����صĹ��� 
**************************************************/  

#ifndef  _ALGORITHE_H
#define  _ALGORITHE_H
#include <string>
using namespace std; 
typedef unsigned int Uint;
typedef unsigned short UInt16;
typedef unsigned char byte;
typedef unsigned long UInt32;//

struct svector
{
	double _x;
	double _y;
};

namespace algorithm
{
	namespace  convert
	{
		//0-Fת��Ϊ0-16������
		int Char16ToInt(char c)  ;
		//16�����ַ���ת��Ϊ�������
		int StrToNumber16(const char *str);
		//0-Fת��Ϊ����
		char ConvertHexChar(char ch);
		//�ַ���ת��Ϊ16����
		int  str2hex(char *str1, unsigned char *p);
		//16����ת��Ϊ�ַ����
		void hex2str(char *ptr, unsigned char *buf, int len);
		//ת��ΪС��ģʽ���ַ���
		UInt16 LeBufToU16( byte Buf[] , int offset);
		//ת��32bit����Ϊ�޷���long
		UInt32 LeBufToU32(byte Buf[] , int offset);
		//unsigned longת��Ϊ32bit����
		void U32ToLeBuf(UInt32 val ,byte Buf[] , int offset);
		//unsigned shortת��Ϊ16bit����
		void U16ToLeBuf(UInt16 val, byte Buf[] , int offset);
		//��������
		double round(double val);
	}

	namespace math
	{
		//��������֮��ľ���
		double  TwoPointsDistance(double firstX,double firstY , double secondX ,double secondY);
		//��������֮��ļн�
		double  CalculateVectorAngle(svector a,svector b);
		//����λ��
		double  CalculatePosition(svector a ,svector b,double length ,double angle ,double angle2,svector& sPos);
		//��ת
		double  rotate(double rPointx,double rPointy,double orgX,double orgY,double raAngle,double & outX,double & outY);
	}

	namespace project
	{
        int  ZeroArrayJudge(char *arry ,int len);
	}

	//  =(x1x2+y1y2)/[��(x1?+y1?)*��(x2?+y2?)] 
}
#endif