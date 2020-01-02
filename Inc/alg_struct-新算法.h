/**************
文件名：alg_struct.h
功能: 提供算法动态库相关结构体的定义，供系统程序调用
日期：2013/3/1
作者：tyx
***************/

#ifndef ALG_STRUCT_H
#define ALG_STRUCT_H

#include "vector"

#include "windows.h"
namespace Alg
{
	//图像结构体
	typedef struct _ImagePara
	{
		int nWidth;   //图像宽
		int nHeight;  //图像高
		int nChannel;
		char *pcData; //图像数据
	}s_ImagePara;

	//函数执行状态信息
	typedef struct _Status
	{
		int nErrorID;					//错误代码ID号
		char chErrorInfo[MAX_PATH];		//错误描述
		char chErrorContext[MAX_PATH];  //错误附加信息，具体某个函数出错	
	}s_Status;

	// 检测初始化参数
	typedef struct _AlgInitParam
	{
		int    nCamIndex;        //相机序号,每个相机对应一个检测实例
		int    nModelType;       //检测类型:0 瓶口 1 瓶脖 2 瓶底 ？
		int    nWidth;           //图像宽度
		int    nHeight;	         //图像高度
		char   chCurrentPath[MAX_PATH]; //run\AlgrithmFiles目录路径
		char   chModelName[MAX_PATH];   //模板名称
	}s_AlgInitParam;

	// 检测输入参数 
	typedef struct _AlgCheckInputParam
	{
		s_ImagePara sInputParam;
		int nParam;//保留 用于图像旋转的角度
		float fParam;//保留
	}s_AlgCInP;

	// 检测输出_错误结构体
	typedef struct _ErrorPara
	{
		RECT rRctError;  //错误区域
		int  nErrorType; //错误类型
		int  nArea;      //错误面积
		int  nLevel;     //错误级别
	}s_ErrorPara;

	// 检测输出_尺寸测量结果结构体
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

	//检测输出结果结构体
	typedef struct _AlgCheckReslut
	{
		std::vector<s_ErrorPara> vErrorPara; //返回错误结构体向量
		int  nSizeError;  //错误总个数

		s_SizeResult sSizeResult;

	}s_AlgCheckResult;

	//模板输入设置结构体
	typedef struct _AlgModelPara
	{	
		s_ImagePara  sImgPara;   //图像数据

	}s_AlgModelPara;

	//用于尺寸综合时复制操作的尺寸结构体
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