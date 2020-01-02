#ifndef COMMON_H
#define COMMON_H
#pragma once

//解除_WIN32_WINNT 未定义的编译警告
#ifndef _WIN32_WINNT 
#define _WIN32_WINNT 0x0502
#endif

#define SHADOW_WIDTH            0
#define IMAGE_SPACE             10
#define TITEL_HEIGHT            110
#define SPPEDHIGHEST            400
#define SPPEDNORMAL             300

#define DEFAULT_SKIN            ":/skin/1b"
#include <qimage.h>
#include <QWaitCondition>
#include <QMutex>
#include "qt_windows.h"

#pragma comment(lib, "version.lib")

#pragma warning(disable:4005) //不显示宏重定义警告

//最大相机个数
#define CAMERA_MAX_COUNT 30
//#define ERROR_MAX_COUNT 43
//最多错误类型个数
#define ERRORTYPE_MAX_COUNT 50
#define IOCard_MAX_COUNT 2
//错误图像个数
#define ERROR_IMAGE_COUNT 30

//#define PASSWORD1 ""
//#define PASSWORD2 "daheng"
#define PASSWORD3 "kongping"

typedef enum{
	UI_EN,
	UI_ZH
}LANGUAGE;
typedef enum{
	SQL_NEW,
	SQL_MODEFY,
	SQL_DELETE,
	SQL_RESERVE
}SQLSTATE;

//typedef enum{
//	NORMAL,
//	ENTER,
//	PRESS,
//	NOSTATUS
//}ButtonStatus;


// 系统类型
enum e_SystemType	
{
	Body = 0,
	FinishButtom,
	Combi14,
	Combi10,
	Body2Cell,
	CombiInYaoBo,
	Combi21,
	VexiFinishButtom,
	VexiButtom
};

// 主界面类型
enum e_CurrentMainPage	
{
	ImagePage = 0,
	InfoPage,
	CarveSettingPage,
	ManagementSettingPage,
	TestPage,
	CountPage,
	AlgPage,
	PLCPage,
	DeBugPage
};

enum e_ToolButton	
{
	ImageButton = 0,
	InfoButton,
	CarveSettingButton,
	ManagementSettingButton,
	TestButton,
	CountButton,
	AlgButton
};

//保存日志类型
enum e_SaveLogType	    
{
	OperationLog = 0,			//操作日志
	DebugLog,					//调试日志(缺图 || 误触发 || 缓存区为空 等日志信息)
	AbnormityLog,               //异常日志(异常捕获 || 理论上不应出现的判断错误)

	CheckLog,		            //检测日志
	MendParamLog,			    //修改参数日志
	StatInfo,					//检测统计信息日志
	AlgorithmDLL				//算法库日志
};
// 采集图像类型
enum e_GrabImageType	
{
	BodyImage = 0,	    // 瓶身
	BottomImage		// 瓶底
};
//保存图像类型
enum e_SaveImageType
{
	NotSave = 0,
	AllImage,
	FailureImage,
	AllImageInCount,
	FailureImageInCount,
};

// 相机序号
enum e_CameraType	
{
	Camera1 = 0,	 
	Camera2,
	Camera3,
	Camera4		
};

//当前绘制状态
enum e_DrawStatus	
{
	DRAW_Status_NULL = 0,			//无操作
	DRAW_Status_MOVE,				//移动
	DRAW_Status_ZOOM,				//缩放
	DRAW_Status_MODIFY,				//修改
};


//当前鼠标位置所在点
enum e_DrawSelect	
{
	DRAW_Select_NULL = 0,			//无操作点
	DRAW_Select_MOVE,				//移动点
	DRAW_Select_ZOOM,				//缩放点
	DRAW_Select_MODIFY,				//修改点
};
//权限
typedef struct _Permission
{
	int iClear;
	int iExit;
	int iStartStop;
	int iImageCarve;
	int iVarietyManege;
	int iSystemSet;
	int iPLCSet;
	int iAlgSet;
	_Permission()
	{
		iClear = 0;
		iExit = 0;
		iStartStop = 0;
		iImageCarve = 0;
		iVarietyManege = 0;
		iSystemSet = 0;
		iPLCSet = 0;
		iAlgSet = 0;
	}
	void clear()
	{
		iClear = 0;
		iExit = 0;
		iStartStop = 0;
		iImageCarve = 0;
		iVarietyManege = 0;
		iSystemSet = 0;
		iPLCSet = 0;
		iAlgSet = 0;
	}
}s_Permission;
//选取点
typedef struct _SelectPoint
{
	int iX;
	int iY;
	int iOffset;
	_SelectPoint()
	{
		iX = 0;
		iY = 0;
		iOffset = 5;
	}
}s_SelectPoint;

//矩形结构体
typedef struct _RectangleShape
{
	int ileftupX;
	int ileftupY;
	int iWidth;
	int iHeight;
	_RectangleShape()
	{
		ileftupX = 0;
		ileftupY = 0;
		iWidth = 1;
		iHeight = 1;
	}
	_RectangleShape(QRect rt)
	{
		ileftupX = rt.x();
		ileftupY = rt.y();
		iWidth = rt.width();
		iHeight = rt.height();
	}
}s_RectangleShape;

typedef struct _IOSignal 
{
	short iGrabCount;				//图像号
	short iGrabDelay;				//采集延时
	_IOSignal()
	{
		iGrabCount = 0;
		iGrabDelay = 0;
	}
}s_IOSignal;

typedef struct _ResultInfo
{
public:
	int nIOCardNum;
	int nCamNo;
	int nImgNo;
	double dCostTime;
	int tmpResult;

	_ResultInfo()
	{
		nIOCardNum  = 0;
		nCamNo = 0;
		nImgNo = 0;
		dCostTime = 0;
		tmpResult = 0;
	}
}s_ResultInfo;

typedef struct _VEXIIOCardInfo{
	int nCamera1Interval;
	int nCamera2Interval;
	int nCamera3Interval;
	int nCamera4Interval;
	int nCamera5Interval;
	int nCamera6Interval;

	int nCamera1TrggerTimes;
	int nCamera2TrggerTimes;
	int nCamera3TrggerTimes;
	int nCamera4TrggerTimes;
	int nCamera5TrggerTimes;
	int nCamera6TrggerTimes;

	int nCamera1TrggerDelay;
	int nCamera2TrggerDelay;
	int nCamera3TrggerDelay;
	int nCamera4TrggerDelay;
	int nCamera5TrggerDelay;
	int nCamera6TrggerDelay;

	int nCamera1Frame;
	int nCamera2Frame;
	int nCamera3Frame;
	int nCamera4Frame;
	int nCamera5Frame;
	int nCamera6Frame;

	int nRejectDelay;
	int nRejectWidth;
	int bDoubleReject;
	int nDoubleRejectDelay;
	int nDoubleRejectWidth;

	int bCleanLightSource;
	int nCleanLightSourceInterval;
	int nCleanLightSourceWidth;

	_VEXIIOCardInfo()
	{
		nCamera1Interval = 0;
		nCamera2Interval = 0;
		nCamera3Interval = 0;
		nCamera4Interval = 0;
		nCamera5Interval = 0;
		nCamera6Interval = 0;

		nCamera1TrggerTimes = 0;
		nCamera2TrggerTimes = 0;
		nCamera3TrggerTimes = 0;
		nCamera4TrggerTimes = 0;
		nCamera5TrggerTimes = 0;
		nCamera6TrggerTimes = 0;

		nCamera1TrggerDelay = 0;
		nCamera2TrggerDelay = 0;
		nCamera3TrggerDelay = 0;
		nCamera4TrggerDelay = 0;
		nCamera5TrggerDelay = 0;
		nCamera6TrggerDelay = 0;

		nCamera1Frame = 0;
		nCamera2Frame = 0;
		nCamera3Frame = 0;
		nCamera4Frame = 0;
		nCamera5Frame = 0;
		nCamera6Frame = 0;

		nRejectDelay = 0;
		nRejectWidth = 0;
		bDoubleReject = 0;
		nDoubleRejectDelay = 0;
		nDoubleRejectWidth = 0;

		bCleanLightSource = 0;
		nCleanLightSourceInterval = 0;
		nCleanLightSourceWidth = 0;
	}
	void operator = (const _VEXIIOCardInfo s)
	{
		nCamera1Interval = s.nCamera1Interval;
		nCamera2Interval = s.nCamera2Interval;
		nCamera3Interval = s.nCamera3Interval;
		nCamera4Interval = s.nCamera4Interval;
		nCamera5Interval = s.nCamera6Interval;
		nCamera5Interval = s.nCamera6Interval;

		nCamera1TrggerTimes = s.nCamera1TrggerTimes;
		nCamera2TrggerTimes = s.nCamera2TrggerTimes;
		nCamera3TrggerTimes = s.nCamera3TrggerTimes;
		nCamera4TrggerTimes = s.nCamera4TrggerTimes;
		nCamera5TrggerTimes = s.nCamera5TrggerTimes;
		nCamera6TrggerTimes = s.nCamera6TrggerTimes;

		nCamera1TrggerDelay = s.nCamera1TrggerDelay;
		nCamera2TrggerDelay = s.nCamera2TrggerDelay;
		nCamera3TrggerDelay = s.nCamera3TrggerDelay;
		nCamera4TrggerDelay = s.nCamera4TrggerDelay;
		nCamera5TrggerDelay = s.nCamera5TrggerDelay;
		nCamera6TrggerDelay = s.nCamera6TrggerDelay;

		nCamera1Frame = s.nCamera1Frame;
		nCamera2Frame = s.nCamera2Frame;
		nCamera3Frame = s.nCamera3Frame;
		nCamera4Frame = s.nCamera4Frame;
		nCamera5Frame = s.nCamera5Frame;
		nCamera6Frame = s.nCamera6Frame;

		nRejectDelay = s.nRejectDelay;
		nRejectWidth = s.nRejectWidth;
		bDoubleReject = s.bDoubleReject;
		nDoubleRejectDelay = s.nDoubleRejectDelay;
		nDoubleRejectWidth = s.nDoubleRejectWidth;

		bCleanLightSource = s.bCleanLightSource;
		nCleanLightSourceInterval = s.nCleanLightSourceInterval;
		nCleanLightSourceWidth = s.nCleanLightSourceWidth;
	}
}s_VEXIIOCardInfo;

#endif // COMMON_H