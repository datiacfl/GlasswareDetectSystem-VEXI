/**************
�ļ�����alg_struct.h
����: �ṩ�㷨��̬����ؽṹ��Ķ��壬��ϵͳ�������
���ڣ�2013/3/1
���ߣ�tyx
***************/

#ifndef ALG_STRUCT_H
#define ALG_STRUCT_H

#include "vector"

#include "windows.h"
namespace Alg
{
	//ͼ��ṹ��
	typedef struct _ImagePara
	{
		int nWidth;   //ͼ���
		int nHeight;  //ͼ���
		int nChannel;
		char *pcData; //ͼ������
	}s_ImagePara;

	//����ִ��״̬��Ϣ
	typedef struct _Status
	{
		int nErrorID;					//�������ID��
		char chErrorInfo[MAX_PATH];		//��������
		char chErrorContext[MAX_PATH];  //���󸽼���Ϣ������ĳ����������	
	}s_Status;

	// ����ʼ������
	typedef struct _AlgInitParam
	{
		int    nCamIndex;        //������,ÿ�������Ӧһ�����ʵ��
		int    nModelType;       //�������:0 ƿ�� 1 ƿ�� 2 ƿ�� ��
		int    nWidth;           //ͼ����
		int    nHeight;	         //ͼ��߶�
		char   chCurrentPath[MAX_PATH]; //run\AlgrithmFilesĿ¼·��
		char   chModelName[MAX_PATH];   //ģ������
	}s_AlgInitParam;

	// ���������� 
	typedef struct _AlgCheckInputParam
	{
		s_ImagePara sInputParam;
		int nParam;//���� ����ͼ����ת�ĽǶ�
		float fParam;//����
	}s_AlgCInP;

	// ������_����ṹ��
	typedef struct _ErrorPara
	{
		RECT rRctError;  //��������
		int  nErrorType; //��������
		int  nArea;      //�������
		int  nLevel;     //���󼶱�
	}s_ErrorPara;

	// ������_�ߴ��������ṹ��
	typedef struct _SizeResult
	{
		float fBodyDia;			// ���⾶
		float fNeckDia;			// ���⾶
		float fMouthDia;		// ���⾶
		float fInnerDia;		// ƿ���ھ� // ��ھ���fSealDia��
		float fTotalHeight;		// ƿȫ��
		float fMouthHeight;		// �ڱߺ�	

		_SizeResult()
		{		
			fBodyDia= -1;
			fNeckDia= -1;
			fMouthDia=-1;
			fInnerDia=-1;
			fTotalHeight=-1;
			fMouthHeight=-1;	
		}
	}s_SizeResult;

	//����������ṹ��
	typedef struct _AlgCheckReslut
	{
		std::vector<s_ErrorPara> vErrorPara; //���ش���ṹ������
		int  nSizeError;  //�����ܸ���

		s_SizeResult sSizeResult;

	}s_AlgCheckResult;

	//ģ���������ýṹ��
	typedef struct _AlgModelPara
	{	
		s_ImagePara  sImgPara;   //ͼ������

	}s_AlgModelPara;

	//���ڳߴ��ۺ�ʱ���Ʋ����ĳߴ�ṹ��
	typedef struct _SizePara4Copy
	{
		int sizeFlag;
		float fBodyDiaS, fBodyDiaL, fBodyDiaH, fBodyDiaM;
		float fNeckDiaS, fNeckDiaL, fNeckDiaH, fNeckDiaM;
		float fMouthDiaS, fMouthDiaL, fMouthDiaH, fMouthDiaM;
		float fTotalHeightS, fTotalHeightL, fTotalHeightH, fTotalHeightM;
		float fMouthHeightS, fMouthHeightL, fMouthHeightH, fMouthHeightM;
		float fSealDiaS, fSealDiaL, fSealDiaH, fSealDiaM;

		BOOL bBodyDia,bNeckDia,bMouthDia,bTotalHeight,bMouthHeight,bSealDia;
		_SizePara4Copy()
		{
			sizeFlag=0;
			fBodyDiaS=fNeckDiaS=fMouthDiaS=fTotalHeightS=fMouthHeightS=fSealDiaS=20.0;
			fBodyDiaL=fNeckDiaL=fMouthDiaL=fTotalHeightL=fMouthHeightL=fSealDiaL=0.0;
			fBodyDiaH=fNeckDiaH=fMouthDiaH=fTotalHeightH=fMouthHeightH=fSealDiaH=1000.0;
			fBodyDiaM=fNeckDiaM=fMouthDiaM=fTotalHeightM=fMouthHeightM=fSealDiaM=0.0;
			bBodyDia=bNeckDia=bMouthDia=bTotalHeight=bMouthHeight=bSealDia=FALSE;	
		}
	}s_SizePara4Copy;
}
#endif