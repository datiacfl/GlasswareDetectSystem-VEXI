#ifndef CONFIGINFO_H
#define CONFIGINFO_H

#pragma once
//#include <QList>
#include <QTime>

#include "common.h"
#include "stateTool.h"

//IO卡信息
typedef struct _ConfigIOCardInfo
{
	short	iCardID;						//设备ID
	QString	strCardName;					//设备名称
	QString	strCardInitFile;				//设备初始化文件

	_ConfigIOCardInfo()
	{
		iCardID = 0;
		strCardName = "PIO24B";
		strCardInitFile = "PIO24B_reg_init.txt";
	}
}s_ConfigIOCardInfo;
//踢废信息
typedef struct _StatisticsInfo
{
	int totalNum;				
	int	passNum;				
	int failureNum;				

	_StatisticsInfo()
	{
		totalNum = 0;						
		passNum = 0;					
		failureNum = 0;		
	}
}s_StatisticsInfo;

typedef struct _SampleInfo
{
	int m_iSampleCount;
	int	m_iSampleTypeCount;					//错误类型个数
	BOOL m_bSampleType[ERRORTYPE_MAX_COUNT]; //图像类型，true: 表示保存，false: 表示不保存

 //	QMutex m_mutexSample;

	_SampleInfo()
	{
		m_iSampleCount = 0;
		m_iSampleTypeCount = 0;
		for (int i=0;i<ERRORTYPE_MAX_COUNT;i++)
		{
			m_bSampleType[i] = false;
		}
	}
}s_SampleInfo;

typedef struct _ErrorInfo
{
	BOOL m_bSaveStatInfo;					//是否保存错误信息
	int	m_iErrorTypeCount;					//错误类型个数 从配置文件中读出 [11/26/2010 GZ]
	cErrorTypeInfo m_cErrorReject;			//错误信息标准 从配置文件中读出 [11/26/2010 GZ]
	BOOL m_bErrorType[ERRORTYPE_MAX_COUNT]; //图像类型，true: 表示保存，false: 表示不保存
	int m_bErrorCountByType[ERRORTYPE_MAX_COUNT]; //图像类型，true: 表示保存，false: 表示不保存
	QVector<QString> m_vstrErrorType;		//错误类型
	int i_countErrorType[CAMERA_MAX_COUNT][ERRORTYPE_MAX_COUNT];

}s_ErrorInfo;

//图像剪切参数 ：： 此处定义，因为可能是一个相机被切割成N张图；
//一个结构体对应一个相机，而结构体中每个参数对应被切割后的图像序列
typedef struct _CorveToCamera {
	int i_ImageCount;				//相机图像被切割成小图像的个数
	int i_GrabSN[CAMERA_MAX_COUNT]; //图像对应的相机编号
	int i_ImageX[CAMERA_MAX_COUNT];
	int i_ImageY[CAMERA_MAX_COUNT];
	int i_ImageWidth[CAMERA_MAX_COUNT];
	int i_ImageHeight[CAMERA_MAX_COUNT];
} sCorveToCamera;

typedef struct _realCamInfo
{
	BOOL m_bSmuGrabber;			//是否是模拟采集
	BOOL m_bCameraInitSuccess;	//相机初始化是否成功
	int m_iGrabType;			//相机类型 0:模拟相机 1:AVT
	int m_iImageType;			//采集图像类型0：瓶身。1：瓶口瓶底。图像综合用
	int m_iIOCardSN;			//对应踢废接口卡
	int m_iImageTargetNo;		//同一图像号的目标拍照个数
	int m_iImageGrabbedNo;		//同一图像号的拍照个数
//	int m_iGrabYUVtoRGB;		//是否需要图像格式转换
	int m_iGrabPosition;		//相机采集工位
	int m_iImageAngle;			//图像旋转角度 : 切割中的小角度旋转
	int m_iImageRoAngle;		//图像旋转角度 : 90,270-配置文件，方向旋转
	HANDLE m_hSendLocInfo;	
	HANDLE m_hReceiveLocInfo;

	int m_iShuter;
	int	m_iTrigger;

	int m_iImageWidth;
	int m_iImageHeight;
	int m_iImageSize;
	int m_iImageBitCount;

	sCorveToCamera m_sCorves;

	CGrabber* m_pGrabber;		//采集卡基类指针
	PBYTE m_pGrabYUVtoRGB;		//格式转化时的临时缓存[4/26/2011 lly]

//	QList<int> m_listCarvedCamera;

	QImage *m_pRealImage;		//实际显示图像（切割前的图像）
	
	BOOL m_bGrabIsTrigger;			//是否开启外部触发模式
	BOOL m_bGrabIsStart;			//相机是否开始
	int m_iGrabImageCount;			//相机拍照张数[3/14/2011 lly]::njc拍照总数，包括误触发
	int m_iGrabTriggerSignalCount;	//相机触发信号个数[3/22/2011 lly]::njc触发拍照总数，不包括误触发
	int m_iLastTriggerSignalCount;	//相机上一次触发时，信号的个数[3/22/2011 lly]
	int m_iImageIdxLast;			// 图像号，用于判断误触发 [12/19/2010 zhaodt]
	
	DWORD m_iGrabCallBackCount;		//采集回调次数

	QMutex m_mutexmShownImage;					
	QMutex m_mutexmRealImage;					

	QString m_strErrorInfo;

	_realCamInfo()
	{
		m_bSmuGrabber = false;
		m_bCameraInitSuccess = false;
		m_iGrabType = 0;
		m_iImageType = 0;
		m_iIOCardSN = 0;
		m_iGrabPosition = 0;
		m_iImageRoAngle = 0;
		m_iImageTargetNo = 8;		//同一图像号的目标拍照个数
		m_iImageGrabbedNo = 0;		//同一图像号的拍照个数

//		m_BStress = 0;
		m_iImageWidth = 500;
		m_iImageHeight = 500;
		m_iImageSize = 250000;
		m_iImageBitCount = 8;

		m_iGrabImageCount = 0;
		m_iGrabTriggerSignalCount = 0;
		m_iLastTriggerSignalCount = 0;
		m_iImageIdxLast = -1;

		m_bGrabIsTrigger = TRUE;
		m_bGrabIsStart = FALSE;

		m_pGrabYUVtoRGB = NULL;
		m_pGrabber = NULL;
		m_pRealImage = NULL;
	}
}s_RealCamInfo;
//	s_AlgImageLocInfo m_AlgImageLocInfos[256];//定位信息
typedef struct _ImageLocInfo
{
	s_AlgImageLocInfo m_AlgImageLocInfos;	//定位信息
	int m_iHaveInfo;

}s_ImageLocInfo;

typedef struct _carvedCamInfo
{
	int m_iToRealCamera;		//对应真实相机编号
	int m_iResImageWidth;
	int m_iResImageHeight;
	int m_iImageType;			//采集图像类型0：瓶身。1：瓶口瓶底。图像综合用
	int m_iIOCardSN;			//对应踢废接口卡
	int m_iErrorCount;
	int m_iGrabPosition;
	
	int m_iStress;				//是否是应力图像0：需要传出定位信息的正常图像 1：不需要传出定位信息的正常图像 2：应力图像
	int m_iToStressCamera;
	int m_iToNormalCamera;
	QList<CGrabElement *> listWaiteLoc;
	s_ImageLocInfo sImageLocInfo[256];		//定位信息

	int m_iImageAngle;			//图像旋转角度 : 切割中的小角度旋转
	int m_iImageRoAngle;		//图像旋转角度 : 90,270-配置文件，方向旋转

	int i_ImageX;
	int i_ImageY;
	int m_iImageWidth;
	int m_iImageHeight;
	int m_iImageSize;
	int m_iImageBitCount;

	PBYTE m_pGrabTemp;			//图像剪切时的临时缓存
	QImage *m_pActiveImage;		//实际显示图像（切割后的图像）

	int m_iShuter;
	int	m_iTrigger;

	QMutex m_mutexmShownImage;					//

	_carvedCamInfo()
	{
		m_iToRealCamera = -1;

		m_iResImageWidth = 500;
		m_iResImageHeight = 500;
		m_iImageType = 0;
		m_iIOCardSN = 0;
		m_iErrorCount = 0;
		m_iGrabPosition = 0;

		m_iStress = 0;
		m_iToStressCamera = -1;
		m_iToNormalCamera = -1;
		qDeleteAll(listWaiteLoc);
		listWaiteLoc.clear();

		m_iImageAngle = 0;
		m_iImageRoAngle = 0;

		m_iImageWidth = 500;
		m_iImageHeight = 500;
		m_iImageSize = 250000;
		m_iImageBitCount = 8;

		m_pGrabTemp = NULL;
		m_pActiveImage = NULL;
	}
}s_CarvedCamInfo;

typedef struct _SystemInfo
{
	QMutex m_mutexSystemInfo;
	int m_iSimulate;
	bool m_bDebugMode;	
	e_SystemType m_iSystemType;			//系统类型 0:瓶身系统, :瓶口瓶底系统, 2:一体机系统(14相机), 3:一体机系统(10相机), 4:瓶身2光电, 5:药玻一体机, 6:瓶身单独应力一体机, 8:联合检验机。
	int m_ButtomImageNo;
	short iRealCamCount;		//真实相机个数
	short iCamCount;			//切割后相机个数
	BOOL m_bIsUsePLC;
	BOOL m_bIsIOCardOK;			//是否可用接口卡
	BOOL m_bIsStopNeedPermission;	//停止检测是否需要权限
	BOOL m_bIsCarve;			//是否切割
	BOOL m_bIsTest;				//是否测试模式 （未使用）
//	BOOL m_bUseHighClock;		//是否使用高精度时间
	int iIOCardCount;			//接口卡个数
	int iIsButtomStress;		//是否有瓶底应力
	int iIsSample;				//是否有取样功能
	int iIsSaveCountInfoByTime;	//是否保存指定时间段内的统计信息
	int iIsCameraCount;			//是否保存各个相机的统计信息
	QString LastModelName;		//上次使用模板
	QString m_strModelName;		//模板名
	int m_iSaveNormalErrorImageByTime;
	int m_iSaveStressErrorImageByTime;
	bool m_bSaveCamera[CAMERA_MAX_COUNT];
	bool m_bSaveErrorType[ERRORTYPE_MAX_COUNT];

	bool m_iStopOnConveyorStoped;	//输送带停止是否停止检测

	int nLoginHoldTime;	//0:不统计，1：按时间统计，2：按个数统计	
	int m_iIsTrackStatistics;	//0:不统计，1：按时间统计，2：按个数统计	
	int m_iTrackTime;
	int m_iTrackNumber;
	int m_iTrackAlertRateMax[ERRORTYPE_MAX_COUNT];//0为总，其他对应缺陷类型
	int m_iTrackAlertRateMin[ERRORTYPE_MAX_COUNT];//0为总，其他对应缺陷类型
//	int m_iIsTrackErrorType;	
 	int m_iIsTrackErrorType[ERRORTYPE_MAX_COUNT];	
	int m_NoKickIfNoFind;
	int m_NoKickIfROIFail;

	int m_iTwoImagePage;		//是否两页显示图像
	int m_iImageStyle;			//图像横向排布还是上下排布0:上下，1：横向
	int m_iImageStretch;		//是否缩放图像
	int m_iNoRejectIfNoOrigin[CAMERA_MAX_COUNT];			//找不到原点是否踢废	
	int m_iNoRejectIfROIfail[CAMERA_MAX_COUNT];			//找不到原点是否踢废	
	int m_iNoStaticIfNoOrigin[CAMERA_MAX_COUNT];			//找不到原点是否统计

	int m_iGrabCountInQueen;	//同时触发相机个数  未使用	
	BOOL m_bMissType;			//漏检是否踢出  未使用	
	QString m_strWindowTitle;	//软件名  未使用

	int IOCardiCamCount[2];
	QString m_strTitle;
	//相机不同尺寸时的最大值，用于初始化算法
	int m_iMaxCameraImageWidth;
	int m_iMaxCameraImageHeight;
	int m_iMaxCameraImageSize;
	int m_iMaxCameraImagePixelSize;
	s_ConfigIOCardInfo m_sConfigIOCardInfo[IOCard_MAX_COUNT];

	BOOL m_bLoadModel;// 是否导入模板成功 [8/4/2010 GZ]

	bool bSaveRecord;
	int iSaveRecordInterval;
	int iIsSampleAndAlamConflict;
	int m_iIs3Sensor;
	//
	bool bAutoSetZero;
	QTime shift1;
	QTime shift2;
	QTime shift3;

	double fPressScale;			//瓶身应力增强系数
	double fBasePressScale;		//瓶底应力增强系数

// 	bool bCameraOffLineSurveillance;
// 	bool bCameraContinueRejectSurveillance;
// 
// 	int iCamOfflineNo;
// 	int iCamContinueRejectNumber;

	bool bVEXIDoubleReject;
	bool bVEXICleanLightSource;
	int nVEXICleanLightSourceInterval;
	int nVEXICleanLightSourceWidth;

	_SystemInfo()
	{
		m_iSimulate =0;
		m_iSystemType = Combi14;
		m_ButtomImageNo = 6;
		iRealCamCount = 1;
		iCamCount = 1;
		m_bIsIOCardOK = FALSE;
		m_bIsCarve = FALSE;
// 		m_bMissType = FALSE;
		m_iGrabCountInQueen = 1;
		m_bIsTest = FALSE;
//		m_bUseHighClock = TRUE;
		iIOCardCount = 1;
//		m_bIfNoFind = FALSE;
		IOCardiCamCount[0] = 0;
		IOCardiCamCount[1] = 0;
		m_NoKickIfNoFind = 0;
		m_NoKickIfROIFail = 0;
		m_iStopOnConveyorStoped = false;

		m_iTwoImagePage=0;
		m_iImageStyle=0;
		m_iImageStretch = 1;

		m_bLoadModel=FALSE;// 是否导入模板成功 [8/4/2010 GZ]

		bSaveRecord = true;
		iSaveRecordInterval = 60;

		bAutoSetZero = true;
		shift1.setHMS(0,0,0);
		shift2.setHMS(0,0,0);
		shift3.setHMS(16,0,0);

		fPressScale = 1;
		fBasePressScale = 1;

// 		bCameraOffLineSurveillance = false;
// 		bCameraContinueRejectSurveillance = false;
// 
// 		iCamOfflineNo = 1;
// 		iCamContinueRejectNumber = 15;

		bVEXIDoubleReject = false;
		bVEXICleanLightSource = false;
		nVEXICleanLightSourceInterval = 1000;
		nVEXICleanLightSourceWidth = 100;

		for (int i=0; i<CAMERA_MAX_COUNT;i++)
		{
			m_iNoRejectIfNoOrigin[i] = 0;
			m_iNoRejectIfROIfail[i] = 0;
			m_iNoStaticIfNoOrigin[i] = 0;
		}
	}
}s_SystemInfo;

typedef struct _RunningInfo
{
	QMutex m_mutexRunningInfo;
	QMutex m_mutexTestInfo;
	int m_iLastIOCard1IN0;
	int m_iPermission;//权限
	int m_checkedNum;
	int m_passNum;
	int m_failureNum;
	int m_checkedNum2;
	int m_passNum2;
	int m_failureNum2;
	int m_failureNumFromIOcard;
	int m_kickoutNumber;

	int m_iKickMode;//踢废模式0:连续踢 1:隔瓶踢	2:持续好 3：正常踢
	int m_iKickMode2;//踢废模式0:连续踢 1:隔瓶踢	2:持续好 3：正常踢
	bool m_bCheck;//是否正在检测，0停止检测，1：正在检测。
	bool m_bIsCheck[CAMERA_MAX_COUNT];//此相机是否正在检测
	int nModelReadFailureNumber;//nMouldID = -1数量，未设置为0
	int nModelChenkedNumber[99];//nMouldID为0-99的数量统计
	int nModelCheckedCount;	// nMouldID总数

	QString strSpeed;

	//计数统计
	int m_iErrorCamCount[CAMERA_MAX_COUNT];// 每个相机的错误计数
	double m_iErrorCamRate[CAMERA_MAX_COUNT];// 每个相机的错误率
	int m_iErrorTypeCount[ERRORTYPE_MAX_COUNT];//每个错误类型的错误计数
	cErrorTypeInfo m_cErrorTypeInfo[CAMERA_MAX_COUNT];//统计错误信息
	//保存上次页面信息
	//e_CurrentMainPage m_eLastMainPage;
//	e_CurrentSettingPage m_eLastSettingPage;


	e_SaveImageType m_eSaveImageType;
	int m_iSaveImgCount[CAMERA_MAX_COUNT];
   
	int iStatisticsInfoSaveMode;  //0按时间，1按数量
//	QList<s_StatisticsInfo> listStatisticsInfo; 
	int m_iCamLostImgNo[CAMERA_MAX_COUNT];// 相机掉线监视 
	int m_iLastTriggerSignalCount;
	int m_iCamContinueReject[CAMERA_MAX_COUNT];// 相机连剔监视


	_RunningInfo()
	{
		m_iLastIOCard1IN0=0;
		m_iPermission = 0;
		m_bCheck = false;
		m_checkedNum = 0;
		m_passNum = 0;
		m_failureNum = 0;
		m_iKickMode = 3;//踢废模式设为3(正常踢)

		m_checkedNum2 = 0;
		m_passNum2 = 0;
		m_failureNum2 = 0;
		m_iKickMode2 = 3;//踢废模式设为3(正常踢)
		m_failureNumFromIOcard = 0;
		m_kickoutNumber = 0;

		for (int i=0;i<CAMERA_MAX_COUNT;i++)
		{
			m_iErrorCamCount[i] = 0;
			m_bIsCheck[i] = true;
			m_iSaveImgCount[i] = 0;

		}
		for (int i=0;i<ERRORTYPE_MAX_COUNT;i++)
		{
			m_iErrorTypeCount[i] = 0;
		}

//		m_eLastMainPage = InfoPage;
//		m_eLastSettingPage = CarveSettingPage;
		m_eSaveImageType = NotSave;
	}

}s_RunningInfo;

typedef struct _ConfigInfo
{
	//s_SystemInfo sSystemInfo;
	//s_CamInfo sCamInfo;
	//s_ErrorInfo sErrorInfo;
	QString m_strAppPath;
	QString m_strConfigPath;
	QString m_strDataPath;
	QString m_strGrabInfoPath;
	QString m_strErrorTypePath;
	QString m_strModelInfoPath;
	QString m_strPLCStatusTypePath;
	QString m_sAlgFilePath;// 算法路径 [10/26/2010 GZ]
///	QString m_strModelName;

	_ConfigInfo()
	{
//		sSystemInfo = s_SystemInfo();
	}

}s_ConfigInfo;
#endif // COMMON_H