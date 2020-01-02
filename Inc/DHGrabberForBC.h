/************************************************************************/
/* Copyright (c) 2010, 中国大恒集团北京图像视觉技术分公司研发二部     
/* All rights reserved.													
/*																		
/* 文件名称： DHGrabberForBC.h	
/* 摘要： 导出采集卡类（Basler 1394相机）

/* 当前版本： 3.0.0.1 beta1
/* 修改者： 孙国强
/* 修改内容摘要：修改接口文件
/* 完成日期： 2010年11月2日
/*
/* 当前版本： 1.0
/* 作者： 江卓佳,尹方宏
/* 完成日期： 2006年08月15日
/*
/* 当前版本： 1.0.1
/* 作者： 孙国强
/* 修改日期： 2010年11月2日
/************************************************************************/


/*
采集卡类型编号定义如下
0:模拟采集卡
1:DALSA X64采集卡
2:AVT相机
3:千兆网相机
4:公司CG300模拟采集卡
5:公司1394相机
6:EURESYS 采集卡
7.公司USB相机
10.Basler 1394相机*/

#if !defined(DHGrabber_h_)
#define DHGrabber_h_

const int GBMaxFileNameLen = 255;
const int GBMaxTextLen = 255;

typedef struct _GBSignalInfoStruct//回调信息结构
{
	PVOID Context;								//存放拥有回调函数的对象的this指针
	int iGrabberTypeSN;							// 采集卡类型编号
	int nGrabberSN;								//采集卡序号
	int nErrorCode;								//错误代码（0：正常）
	int nFrameCount;							//已采集的帧记数
	char strDescription[GBMaxTextLen];			//描述信息

	int iReserve1;								// 备用字段1
	int iReserve2;								// 备用字段2
	
}s_GBSIGNALINFO;//回调信息结构

//回调函数指针声明
typedef void (WINAPI *PGBCALLBACK)(const s_GBSIGNALINFO* SignalInfo);

typedef struct _GBInitStruct//采集卡初始化结构
{
	int iGrabberTypeSN;						// 采集卡类型编号
	int nGrabberSN;							//采集卡序号
    char strDeviceName[GBMaxTextLen];		//设备名称
	char strDeviceMark[GBMaxTextLen];		// 设备标识
	char strGrabberFile[GBMaxFileNameLen];	//用于初始化的文件
	PGBCALLBACK CallBackFunc;				//回调函数指针
	PVOID Context;							//存放拥有回调函数的对象的this指针
	
	int iReserve1;							// 备用字段1
	int iReserve2;							// 备用字段2

}s_GBINITSTRUCT;//采集卡初始化结构

typedef struct _GBErrorInfoStruct//错误信息结构
{
   	int nErrorCode;							//错误代码（0：正常）
	char strErrorDescription[GBMaxTextLen];	//错误描述
	char strErrorRemark[GBMaxTextLen];		//附加信息

}s_GBERRORINFO;//错误信息结构

//公共参数
enum GBParamID
{
	GBImageWidth = 0,		//图像宽度 (单位:字节)
	GBImageHeight,			//图像高度 (单位:字节)
	GBImagePixelSize,		//图像象素大小 (单位:字节)
	GBImageBufferSize,		//图像缓冲区大小 (单位:字节)
	GBImageBufferAddr,		//图像缓冲区地址
	GBGrabberTypeSN			//采集卡类型编号
};

//错误代码定义
const int GBOK = 0;

class CGrabber
{
//操作
public:
	CGrabber()
	{
	}
	virtual ~CGrabber()
	{
	}
	
	//初始化
	virtual BOOL Init(const s_GBINITSTRUCT* pInitParam) = 0;

	//关闭
	virtual BOOL Close() = 0;

	//开始采集
	virtual BOOL StartGrab() = 0;

	//停止采集
	virtual BOOL StopGrab() = 0;
	
	//单帧采集
	virtual BOOL Snapshot() = 0;

	//设置参数
	virtual BOOL SetParamInt(GBParamID Param, int nInputVal) = 0;
	
	//得到参数
	virtual BOOL GetParamInt(GBParamID Param, int &nOutputVal) = 0;
	
	//调用参数对话框
	virtual void CallParamDialog() = 0;
	
	//得到出错信息
	virtual void GetLastErrorInfo(s_GBERRORINFO *pErrorInfo) = 0;
};

#endif// !defined(DHGrabber_h_)



//////////////////////////////////////////////////////////////////////////
//采集类
#if !defined(DHGrabberBC_h_)
#define DHGrabberBC_h_

//////////////////////////////////////////////////////////////////////////
//Basler相机专有参数
enum BCParamID	
{
	BCColorCode = 0,		//颜色编码，即图像格式(Mono8, YUV422等等)
	BCTriggerOnOff,			//相机是否处于外触发模式 1：是 0：否
	BCTriggerMode,			//触发模式
	BCTriggerPolarity,		//触发极性
	BCBrightness,			//相机亮度大小
	BCShutter,				//相机快门值
	BCBytes,				//相机传输字节数
	BCGain,					//相机增益大小
	BCU,					//相机U值
 	BCV						//相机V值
};

enum BCParamVal	
{
	BCColor_Mono8 = 0,			//Mono8格式
	BCColor_YUV8_411,			//YUV8_411
	BCColor_YUV8_422,			//YUV8_422
	BCColor_YUV8_444,			//YUV8_444
	BCColor_Raw8,				//Raw8(Bayer转换前数据)
	BCColor_Mono16U,			//Mono16(unsigned)
	BCColor_Mono16S,			//Mono16(signed)
	BCColor_RGB8,				//RGB8
	BCColor_RGB16U,				//RGB16(unsigned)
	BCColor_RGB16S,				//RGB16(signed)
	BCColor_Raw16,				//Raw16
	BCColor_Unknown,			//其他未知的颜色编码
	BCTriggerOn,				//外触发开启
	BCTriggerOff,				//外触发关闭
	BCTriggerMode0,				//外触发模式0，在BCTriggerOn下生效
	BCTriggerMode1,				//外触发模式1，在BCTriggerOn下生效
	BCTriggerPolarityLowActive, //外触发低电极，在BCTriggerOn下生效
	BCTriggerPolarityHighActive //外触发高电极，在BCTriggerOn下生效
};

//////////////////////////////////////////////////////////////////////////
//采集类
class _declspec(dllexport) CDHGrabberBC : public CGrabber
{
//操作
public:

	CDHGrabberBC();
	virtual ~CDHGrabberBC();
	
	//初始化
	BOOL Init(const s_GBINITSTRUCT* pInitParam);

	//关闭
	BOOL Close();

	//开始采集
	BOOL StartGrab();

	//停止采集
	BOOL StopGrab();

	//设置参数
	BOOL SetParamInt(GBParamID Param, int nInputVal);
	
	//得到参数
	BOOL GetParamInt(GBParamID Param, int &nOutputVal);

	//调用参数对话框
	void CallParamDialog();

	//得到出错信息
	void GetLastErrorInfo(s_GBERRORINFO *pErrorInfo);

	//////////////////////////////////////Basler相机扩展接口函数
	
	//SnapShot单帧采集
	BOOL Snapshot();

	//设置采集窗口区域
	BOOL BCSetAOI(RECT rtAOI);

	//获取采集窗口区域
	BOOL BCGetAOI(RECT &rtAOI);
	
	//设置相机参数
	BOOL BCSetParamPro(BCParamID Param, int nInputVal);
	BOOL BCSetParamPro(BCParamID Param, BCParamVal ParamValInput);

	//获取相机参数
	BOOL BCGetParamPro(BCParamID Param, int &nOutputVal);
	BOOL BCGetParamPro(BCParamID Param, BCParamVal &ParamValOutput);

	//得到相机序列号
 	BOOL GetCameraSN(CString& strRetCameraSN);
	//  [7/10/2006]
 
	//! Converts a 422YUV8 to a R,G,B three channel  (works on raw pointers)  //  [8/15/2006]
    void BCConvertYUV422ToRGB(BYTE* pDestR, BYTE* pDestG, BYTE* pDestB, const BYTE* pSource,  const CSize& Size, unsigned int lineoffset = 0);

	//! Converts a 422YUV8 to a RGB8 image (works on raw pointers)  //  [8/15/2006]
    void BCConvertYUV422ToRGB(BYTE* pDest, const BYTE* pSource,  const CSize& Size, unsigned int lineoffset = 0);

//属性
protected:
	CGrabber *m_pGrabber;
};

#endif// !defined(GrabberExport_h_)
