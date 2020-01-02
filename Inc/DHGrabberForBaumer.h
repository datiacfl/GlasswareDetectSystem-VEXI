/************************************************************************/
/* Copyright (c) 2012, 北京大恒图像视觉有限公司视觉系统部  
/* All rights reserved.													
/*																		
/* 文件名称： DHGrabberForBaumer.h	
/* 摘要： 导出采集卡类(Baumer千兆网相机)
/* 这个动态库是针对Baumer千兆网相机，
/* 目前已经测试相机型号：
/* DXG04h
/*调用过程：(具体调用过程参看例程)
/*
/* 当前版本： 3.0.0.1 beta1
/* 修改者： 孙国强
/* 修改内容摘要：完善头文件注释
/* 完成日期： 2012年6月11日
/************************************************************************/

#if !defined(DHGrabber_h_)
#define DHGrabber_h_

const int GBMaxFileNameLen = 255;
const int GBMaxTextLen = 255;

//回调信息结构
typedef struct _GBSignalInfoStruct
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

//采集卡初始化结构
typedef struct _GBInitStruct
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

//错误信息结构
typedef struct _GBErrorInfoStruct
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



#if !defined(DHGrabberBAUMER_h_)
#define DHGrabberBAUMER_h_

//////////////////////////////////////////////////////////////////////////
//Baumer专用参数
enum BaumerParamID	
{
	BaumerFramesPerSecondsContinuous = 0,
	BaumerExposure,
	BaumerExposureMin,
	BaumerExposureMax,
	BaumerGain,
	BaumerGainMin,
	BaumerGainMax,
	BaumerTriggerDelay
};

//Baumer专用参数值
enum BaumerParamVal
{
	BaumerTriggerOff = 0,
	BaumerTriggerOn
};

//错误代码定义
enum ErrorStruct
{
	NormalState = 0,    // 正常状态
	ErrorNoFindCam,	    // 没有找到相机
	ErrorValOverFlow,	// 数据溢出
	ErrorGrabberSN,		// 相机序号超出能够找到的相机数  错误处理存在 
	ErrorGetCamInfo,	// 得到相机信息失败              错误处理存在 
	ErrorOpenCam,		// 打开相机失败                  错误处理存在
	ErrorInit,			// 初始化失败                    错误处理存在
	ErrorStartGrab,		// 开始采集失败                  错误处理存在
	ErrorStopGrab,		// 停止采集失败                  错误处理存在
	ErrorClose,			// 关闭失败                      错误处理存在
	ErrorSendBufAdd,	// 传出图像内存地址失败          错误处理存在
	ErrorGetParam,		// 非法获取参数                  错误处理存在
	ErrorSetParam,		// 非法设置参数                  错误处理存在
	ErrorParamDlg,	    // 调用参数设置对话框失败        错误处理存在
	ErrorReadIniFile,	// 读取配置文件失败              错误处理存在
	ErrorLostFrame,     // 采集到TrashBuffer丢帧         错误处理存在
	ErrorSysLostFrame,  // 系统内部报出的丢帧
	ErrorTriggerIgnored,// 通常因为外触发频率过快
	ErrorSaveInitFile	//保存初始化文件失败
};

//////////////////////////////////////////////////////////////////////////
//采集类
#define	_EXPORTING

#ifdef _EXPORTING
#define CLASS_DECLSPEC    __declspec(dllexport)  //程序编译时使用
#else
#define CLASS_DECLSPEC    __declspec(dllimport)	 //动态库应用时使用
#endif

class CLASS_DECLSPEC CDHGrabberBaumer : public CGrabber
{
//操作
public:
	CDHGrabberBaumer();
	virtual ~CDHGrabberBaumer();
	
	//初始化
	BOOL Init(const s_GBINITSTRUCT* pInitParam);

	//关闭
	BOOL Close();

	//开始采集
	BOOL StartGrab();

	//停止采集
	BOOL StopGrab();

	//单贞采集
	BOOL Snapshot();
	
	//设置参数
	BOOL SetParamInt(GBParamID Param, int nInputVal);
	
	//得到参数
	BOOL GetParamInt(GBParamID Param, int &nOutputVal);

	//调用参数对话框
	void CallParamDialog();

	//得到出错信息
	void GetLastErrorInfo(s_GBERRORINFO *pErrorInfo);

	//////////////////////////////////////////////////////////////////////////
	// Baumer专有接口
	
	/************************************************************************/
	/*  功能：设置采集卡参数
	/*  输入：目前只支持 DSLineCropHeight项 和 DSLineMaxCropHeight项
	/*	输出：无
	/*	返回：正确:TRUE   错误:FALSE
	/************************************************************************/
	BOOL BaumerSetParamPro(BaumerParamID Param, int nInputVal);	


	/************************************************************************/
	/*  功能：获取采集卡参数(目前没加任何功能)
	/*  输入：无
	/*	输出：无
	/*	返回：正确:TRUE   错误:FALSE
	/************************************************************************/
	BOOL BaumerGetParamPro(BaumerParamID Param, int &nOutputVal);


	/************************************************************************/
	/*  功能：设置采集卡参数
	/*  输入：目前只支持 DSLineExternalTriggerOnOff 项
	/*        具体配置：
	/*        帧信号使能 DSLineExternalTriggerOnOff + DSLineTriggerOn
	/*        帧信号失效 DSLineExternalTriggerOnOff + DSLineTriggerOff
	/*	输出：无
	/*	返回：正确:TRUE   错误:FALSE
	/************************************************************************/
	BOOL BaumerSetParamPro(BaumerParamID Param, BaumerParamVal nInputVal);	


	/************************************************************************/
	/*  功能：获取采集卡参数
	/*  输入：目前只支持 DSLineExternalTriggerOnOff 项
	/*	输出：帧信号使能则返回 DSLineTriggerOn    帧信号失效则返回DSLineTriggerOff
	/*	返回：正确:TRUE   错误:FALSE
	/************************************************************************/
	BOOL BaumerGetParamPro(BaumerParamID Param, BaumerParamVal& nOutputVal);


	/************************************************************************/
	/*  功能：设置触发状态
	/*  输入：BaumerParamVal
	/*	输出：无
	/*	返回：正确:TRUE   错误:FALSE
	/************************************************************************/
	BOOL BaumerSetTriggerParam(BaumerParamVal ParamValInput);
	/************************************************************************/
	/*  功能：获取触发状态
	/*  输入：无
	/*	输出：BaumerParamVal
	/*	返回：正确:TRUE   错误:FALSE
	/************************************************************************/
	BOOL BaumerGetTriggerParam(BaumerParamVal &ParamValInput);

	BOOL BaumerSetParamPro(BaumerParamID Param, float nInputVal);	

	BOOL BaumerGetParamPro(BaumerParamID Param, float& nOutputVal);



	/************************************************************************/
	/*  功能：设置采集窗口区域(待删除函数)
	/*  输入：无
	/*	输出：无
	/*	返回：正确:TRUE   错误:FALSE
	/************************************************************************/
	BOOL BaumerGetAOI(RECT &rtAOI);


	/************************************************************************/
	/*  功能：设置采集窗口区域(待删除函数)
	/*  输入：无
	/*	输出：无
	/*	返回：正确:TRUE   错误:FALSE
	/************************************************************************/
	BOOL BaumerSetAOI(RECT rtAOI);


//属性
protected:
	CGrabber *m_pGrabber;
};

#endif// !defined(DHGrabberBAUMER_h_)


//////////////////////////////////////////////////////////////////////////
//使用说明
/*

//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
//修改记录
/*

*/
//////////////////////////////////////////////////////////////////////////

