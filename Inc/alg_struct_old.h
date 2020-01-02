#if !defined(AFX_CHECK_H__3D35A3B4_D261_4116_8EBD_714891F3AEF3__INCLUDED_)
#define AFX_CHECK_H__3D35A3B4_D261_4116_8EBD_714891F3AEF3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "vector"


namespace Alg{

//图像结构体
typedef struct _ImagePara
{
	int nWidth;   //图像宽
	int nHeight;  //图像高
	int nChannel;
	char *pcData; //图像数据
}s_ImagePara;

// 函数执行状态信息
typedef struct _Status
{
	int  nErrorID;	    	       // 错误代码ID号
	char chErrorInfo[MAX_PATH];	   // 错误描述
	char chErrorContext[MAX_PATH]; //错误附加信息，具体某个函数出错	
}s_Status;

// 算法初始化参数
typedef struct _AlgInitParam
{
	int    nCamIndex;        //相机序号,每个相机对应一个检测实例
	int    nModelType;       //检测类型:0 瓶口 1 瓶脖 2 瓶底
	int    nWidth;           //图像宽度
	int    nHeight;	         //图像高度
	char   chCurrentPath[MAX_PATH]; //run\AlgrithmFiles目录路径
	char   chModelName[MAX_PATH];   //模板名称
}s_AlgInitParam;

// 检测输入参数 algorithm check input parameter
typedef struct _AlgCheckInputParam
{
	s_ImagePara sInputParam;
	int nParam;
	float fParam;
}s_AlgCInP;

// 检测输出参数 algorithm check output parameter
// 输出错误结构体
typedef struct _ErrorPara
{
	RECT rRctError;  //错误区域
	int  nErrorType; //错误类型
	int  nArea;      //错误面积
	int  nLevel;     //错误级别
}s_ErrorPara;

// 输出尺寸测量结果结构体
typedef struct _SizeResult
{
	float fBodyDia;			// 身外径
	float fNeckDia;			// 脖外径
	float fMouthDia;		// 口外径
	float fInnerDia;		// 瓶口内径 // 封口径（fSealDia）
	float fTotalHeight;		// 瓶全高
	float fMouthHeight;		// 口边厚	

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

typedef struct _AlgCheckReslut
{
   std::vector<s_ErrorPara> vErrorPara; //返回错误结构体向量
   int  nSizeError;  //错误总个数
   
   s_SizeResult sSizeResult;
	
}s_AlgCheckResult;

// 检测输出参数 algorithm model parameter
// SetAlgParam函数使用
typedef struct _AlgModelPara
{	
	s_ImagePara  sImgPara;   //图像数据
	
}s_AlgModelPara;
// 检测输出参数 algorithm model parameter
// SetAlgParam函数使用
typedef struct _AlgCheckPara
{
 	s_ImagePara  sImgPara;  //图像数据

}s_AlgCheckPara;

// 模板设置初始化信息
typedef struct _AlgModelInit
{

}s_AlgModelInit;

//检测参数设置初始化信息
typedef struct _AlgChecklInit
{
	
}s_AlgCheckInit;

// 算法信息结构体
typedef struct _AlgInfo
{
   
	
	
}s_AlgInfo;

}

#endif // !defined(AFX_CHECK_H__3D35A3B4_D261_4116_8EBD_714891F3AEF3__INCLUDED_)