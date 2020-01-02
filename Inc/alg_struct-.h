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

#define	OUTPUT_MAXERRNUM 20
#define	BOTTLEXLD_POINTNUM 50  //2013.9.22 nanjc ��ȡ�����Ǽܵ�������
#define CAMERA_MAX_COUNT 26


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
		int    nCamIndex;						//������,ÿ�������Ӧһ�����ʵ��
		int	   nSameCamCount;					//��Ӧͬһ����ʵ�����ʵ������
		int	   nSameCamIndex[CAMERA_MAX_COUNT];	//��Ӧͬһ����ʵ������������
		int    nModelType;						//�������:0 ƿ�� 1 ƿ�� 2 ƿ�� ...����
		int    nWidth;							//ͼ����
		int    nHeight;							//ͼ��߶�
		char   chCurrentPath[MAX_PATH];			//run\AlgrithmFilesĿ¼·��
		char   chModelName[MAX_PATH];			//ģ������
	}s_AlgInitParam;

	//2013.9.22 nanjc ��������ͼ��λӦ��ͼ��
	typedef struct _Loc_Ori
	{
		float modelRow;
		float modelCol;
		float modelAngle;
		_Loc_Ori()
		{
			modelRow = 0;
			modelCol = 0;
			modelAngle = 0;	
		}
	}s_Loc_Ori;
	
	typedef struct _Ori_Redress
	{
		bool  bOriRedress;
		float RedressRow;
		float RedressCol;
		float RedressAngle;
		_Ori_Redress()
		{
			bOriRedress = false;
			RedressRow = 0;
			RedressCol = 0;
			RedressAngle = 0;	
		}
	}s_Ori_Redress;//ԭ�����

	typedef struct _Xld_Point
	{
		int nCount;
		int * nRowsAry;
		int * nColsAry;
		_Xld_Point()
		{
			nCount = 0;
			nRowsAry = NULL;
			nColsAry = NULL;	
		}
	}s_Xld_Point;//ƿ������������Ӧ��ԭ��궨
	//ͼ��λ��Ϣ
	typedef struct _AlgImageLocInfo
	{
		s_Loc_Ori		sLocOri;		//ԭ����Ϣ
		s_Ori_Redress	sOriRedress;	//ԭ�������Ϣ
		s_Xld_Point		sXldPoint;		//������Ϣ
	}s_AlgImageLocInfo;

	// ���������� 
	typedef struct _AlgCheckInputParam
	{
		s_ImagePara sInputParam;
		s_AlgImageLocInfo sImgLocInfo; //2013.9.22 nanjc ��������ͼ��λӦ��ͼ��
		int nParam;//���� ����ͼ����ת�ĽǶ�
		float fParam;//����
	}s_AlgCInP;

	//2013.9.12 nanjc ��ʼ��
	// ������_����ṹ��
	typedef struct _ErrorPara
	{
		RECT rRctError;  //��������
		int  nErrorType; //��������
		int  nArea;      //�������
		int  nLevel;     //���󼶱�
		int	 nxoffset;	 //xλ��
		int	 nyoffset;	 //xλ��

		_ErrorPara()
		{
			rRctError.bottom = 0;
			rRctError.left = 0;
			rRctError.right = 0;
			rRctError.top = 0;
			nErrorType = 0;
			nArea = 0;
			nLevel = 0;
			nxoffset = 0;
			nyoffset = 0;
		}
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


	//2013.9.12 nanjc ��߽紫��stl�쳣����������ָ�봫��
	//����������ṹ��
	typedef struct _AlgCheckReslut
	{
		int  nSizeError;//�����ܸ���//�㷨��ϵͳ�Ե�ַ��ʽ���ݼ���������ܴ���BUG���罫
		//�����ܸ�����ṹ����������˳�򣬽������ܸ���������ֵ��ϵͳ������

		s_ErrorPara *vErrorParaAry;//���ش���ṹ������

		s_SizeResult sSizeResult;

		s_AlgImageLocInfo sImgLocInfo; //2013.9.22 nanjc ��������ͼ��λӦ��ͼ��

		int nArea; //����Ӧ���ۺ�
	}s_AlgCheckResult;



	//ģ���������ýṹ��
	typedef struct _AlgModelPara
	{	
		s_ImagePara  sImgPara;   //ͼ������
		
		s_AlgImageLocInfo sImgLocInfo; //2013.9.22 nanjc ��������ͼ��λӦ��ͼ��
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