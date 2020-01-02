#ifndef CONFIGINFO_H
#define CONFIGINFO_H

#pragma once
//#include <QList>
#include <QTime>

#include "common.h"
#include "stateTool.h"

//IO����Ϣ
typedef struct _ConfigIOCardInfo
{
	short	iCardID;						//�豸ID
	QString	strCardName;					//�豸����
	QString	strCardInitFile;				//�豸��ʼ���ļ�

	_ConfigIOCardInfo()
	{
		iCardID = 0;
		strCardName = "PIO24B";
		strCardInitFile = "PIO24B_reg_init.txt";
	}
}s_ConfigIOCardInfo;
//�߷���Ϣ
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
	int	m_iSampleTypeCount;					//�������͸���
	BOOL m_bSampleType[ERRORTYPE_MAX_COUNT]; //ͼ�����ͣ�true: ��ʾ���棬false: ��ʾ������

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
	BOOL m_bSaveStatInfo;					//�Ƿ񱣴������Ϣ
	int	m_iErrorTypeCount;					//�������͸��� �������ļ��ж��� [11/26/2010 GZ]
	cErrorTypeInfo m_cErrorReject;			//������Ϣ��׼ �������ļ��ж��� [11/26/2010 GZ]
	BOOL m_bErrorType[ERRORTYPE_MAX_COUNT]; //ͼ�����ͣ�true: ��ʾ���棬false: ��ʾ������
	int m_bErrorCountByType[ERRORTYPE_MAX_COUNT]; //ͼ�����ͣ�true: ��ʾ���棬false: ��ʾ������
	QVector<QString> m_vstrErrorType;		//��������
	int i_countErrorType[CAMERA_MAX_COUNT][ERRORTYPE_MAX_COUNT];

}s_ErrorInfo;

//ͼ����в��� ���� �˴����壬��Ϊ������һ��������и��N��ͼ��
//һ���ṹ���Ӧһ����������ṹ����ÿ��������Ӧ���и���ͼ������
typedef struct _CorveToCamera {
	int i_ImageCount;				//���ͼ���и��Сͼ��ĸ���
	int i_GrabSN[CAMERA_MAX_COUNT]; //ͼ���Ӧ��������
	int i_ImageX[CAMERA_MAX_COUNT];
	int i_ImageY[CAMERA_MAX_COUNT];
	int i_ImageWidth[CAMERA_MAX_COUNT];
	int i_ImageHeight[CAMERA_MAX_COUNT];
} sCorveToCamera;

typedef struct _realCamInfo
{
	BOOL m_bSmuGrabber;			//�Ƿ���ģ��ɼ�
	BOOL m_bCameraInitSuccess;	//�����ʼ���Ƿ�ɹ�
	int m_iGrabType;			//������� 0:ģ����� 1:AVT
	int m_iImageType;			//�ɼ�ͼ������0��ƿ����1��ƿ��ƿ�ס�ͼ���ۺ���
	int m_iIOCardSN;			//��Ӧ�߷Ͻӿڿ�
	int m_iImageTargetNo;		//ͬһͼ��ŵ�Ŀ�����ո���
	int m_iImageGrabbedNo;		//ͬһͼ��ŵ����ո���
//	int m_iGrabYUVtoRGB;		//�Ƿ���Ҫͼ���ʽת��
	int m_iGrabPosition;		//����ɼ���λ
	int m_iImageAngle;			//ͼ����ת�Ƕ� : �и��е�С�Ƕ���ת
	int m_iImageRoAngle;		//ͼ����ת�Ƕ� : 90,270-�����ļ���������ת
	HANDLE m_hSendLocInfo;	
	HANDLE m_hReceiveLocInfo;

	int m_iShuter;
	int	m_iTrigger;

	int m_iImageWidth;
	int m_iImageHeight;
	int m_iImageSize;
	int m_iImageBitCount;

	sCorveToCamera m_sCorves;

	CGrabber* m_pGrabber;		//�ɼ�������ָ��
	PBYTE m_pGrabYUVtoRGB;		//��ʽת��ʱ����ʱ����[4/26/2011 lly]

//	QList<int> m_listCarvedCamera;

	QImage *m_pRealImage;		//ʵ����ʾͼ���и�ǰ��ͼ��
	
	BOOL m_bGrabIsTrigger;			//�Ƿ����ⲿ����ģʽ
	BOOL m_bGrabIsStart;			//����Ƿ�ʼ
	int m_iGrabImageCount;			//�����������[3/14/2011 lly]::njc���������������󴥷�
	int m_iGrabTriggerSignalCount;	//��������źŸ���[3/22/2011 lly]::njc���������������������󴥷�
	int m_iLastTriggerSignalCount;	//�����һ�δ���ʱ���źŵĸ���[3/22/2011 lly]
	int m_iImageIdxLast;			// ͼ��ţ������ж��󴥷� [12/19/2010 zhaodt]
	
	DWORD m_iGrabCallBackCount;		//�ɼ��ص�����

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
		m_iImageTargetNo = 8;		//ͬһͼ��ŵ�Ŀ�����ո���
		m_iImageGrabbedNo = 0;		//ͬһͼ��ŵ����ո���

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
//	s_AlgImageLocInfo m_AlgImageLocInfos[256];//��λ��Ϣ
typedef struct _ImageLocInfo
{
	s_AlgImageLocInfo m_AlgImageLocInfos;	//��λ��Ϣ
	int m_iHaveInfo;

}s_ImageLocInfo;

typedef struct _carvedCamInfo
{
	int m_iToRealCamera;		//��Ӧ��ʵ������
	int m_iResImageWidth;
	int m_iResImageHeight;
	int m_iImageType;			//�ɼ�ͼ������0��ƿ����1��ƿ��ƿ�ס�ͼ���ۺ���
	int m_iIOCardSN;			//��Ӧ�߷Ͻӿڿ�
	int m_iErrorCount;
	int m_iGrabPosition;
	
	int m_iStress;				//�Ƿ���Ӧ��ͼ��0����Ҫ������λ��Ϣ������ͼ�� 1������Ҫ������λ��Ϣ������ͼ�� 2��Ӧ��ͼ��
	int m_iToStressCamera;
	int m_iToNormalCamera;
	QList<CGrabElement *> listWaiteLoc;
	s_ImageLocInfo sImageLocInfo[256];		//��λ��Ϣ

	int m_iImageAngle;			//ͼ����ת�Ƕ� : �и��е�С�Ƕ���ת
	int m_iImageRoAngle;		//ͼ����ת�Ƕ� : 90,270-�����ļ���������ת

	int i_ImageX;
	int i_ImageY;
	int m_iImageWidth;
	int m_iImageHeight;
	int m_iImageSize;
	int m_iImageBitCount;

	PBYTE m_pGrabTemp;			//ͼ�����ʱ����ʱ����
	QImage *m_pActiveImage;		//ʵ����ʾͼ���и���ͼ��

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
	e_SystemType m_iSystemType;			//ϵͳ���� 0:ƿ��ϵͳ, :ƿ��ƿ��ϵͳ, 2:һ���ϵͳ(14���), 3:һ���ϵͳ(10���), 4:ƿ��2���, 5:ҩ��һ���, 6:ƿ������Ӧ��һ���, 8:���ϼ������
	int m_ButtomImageNo;
	short iRealCamCount;		//��ʵ�������
	short iCamCount;			//�и���������
	BOOL m_bIsUsePLC;
	BOOL m_bIsIOCardOK;			//�Ƿ���ýӿڿ�
	BOOL m_bIsStopNeedPermission;	//ֹͣ����Ƿ���ҪȨ��
	BOOL m_bIsCarve;			//�Ƿ��и�
	BOOL m_bIsTest;				//�Ƿ����ģʽ ��δʹ�ã�
//	BOOL m_bUseHighClock;		//�Ƿ�ʹ�ø߾���ʱ��
	int iIOCardCount;			//�ӿڿ�����
	int iIsButtomStress;		//�Ƿ���ƿ��Ӧ��
	int iIsSample;				//�Ƿ���ȡ������
	int iIsSaveCountInfoByTime;	//�Ƿ񱣴�ָ��ʱ����ڵ�ͳ����Ϣ
	int iIsCameraCount;			//�Ƿ񱣴���������ͳ����Ϣ
	QString LastModelName;		//�ϴ�ʹ��ģ��
	QString m_strModelName;		//ģ����
	int m_iSaveNormalErrorImageByTime;
	int m_iSaveStressErrorImageByTime;
	bool m_bSaveCamera[CAMERA_MAX_COUNT];
	bool m_bSaveErrorType[ERRORTYPE_MAX_COUNT];

	bool m_iStopOnConveyorStoped;	//���ʹ�ֹͣ�Ƿ�ֹͣ���

	int nLoginHoldTime;	//0:��ͳ�ƣ�1����ʱ��ͳ�ƣ�2��������ͳ��	
	int m_iIsTrackStatistics;	//0:��ͳ�ƣ�1����ʱ��ͳ�ƣ�2��������ͳ��	
	int m_iTrackTime;
	int m_iTrackNumber;
	int m_iTrackAlertRateMax[ERRORTYPE_MAX_COUNT];//0Ϊ�ܣ�������Ӧȱ������
	int m_iTrackAlertRateMin[ERRORTYPE_MAX_COUNT];//0Ϊ�ܣ�������Ӧȱ������
//	int m_iIsTrackErrorType;	
 	int m_iIsTrackErrorType[ERRORTYPE_MAX_COUNT];	
	int m_NoKickIfNoFind;
	int m_NoKickIfROIFail;

	int m_iTwoImagePage;		//�Ƿ���ҳ��ʾͼ��
	int m_iImageStyle;			//ͼ������Ų����������Ų�0:���£�1������
	int m_iImageStretch;		//�Ƿ�����ͼ��
	int m_iNoRejectIfNoOrigin[CAMERA_MAX_COUNT];			//�Ҳ���ԭ���Ƿ��߷�	
	int m_iNoRejectIfROIfail[CAMERA_MAX_COUNT];			//�Ҳ���ԭ���Ƿ��߷�	
	int m_iNoStaticIfNoOrigin[CAMERA_MAX_COUNT];			//�Ҳ���ԭ���Ƿ�ͳ��

	int m_iGrabCountInQueen;	//ͬʱ�����������  δʹ��	
	BOOL m_bMissType;			//©���Ƿ��߳�  δʹ��	
	QString m_strWindowTitle;	//������  δʹ��

	int IOCardiCamCount[2];
	QString m_strTitle;
	//�����ͬ�ߴ�ʱ�����ֵ�����ڳ�ʼ���㷨
	int m_iMaxCameraImageWidth;
	int m_iMaxCameraImageHeight;
	int m_iMaxCameraImageSize;
	int m_iMaxCameraImagePixelSize;
	s_ConfigIOCardInfo m_sConfigIOCardInfo[IOCard_MAX_COUNT];

	BOOL m_bLoadModel;// �Ƿ���ģ��ɹ� [8/4/2010 GZ]

	bool bSaveRecord;
	int iSaveRecordInterval;
	int iIsSampleAndAlamConflict;
	int m_iIs3Sensor;
	//
	bool bAutoSetZero;
	QTime shift1;
	QTime shift2;
	QTime shift3;

	double fPressScale;			//ƿ��Ӧ����ǿϵ��
	double fBasePressScale;		//ƿ��Ӧ����ǿϵ��

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

		m_bLoadModel=FALSE;// �Ƿ���ģ��ɹ� [8/4/2010 GZ]

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
	int m_iPermission;//Ȩ��
	int m_checkedNum;
	int m_passNum;
	int m_failureNum;
	int m_checkedNum2;
	int m_passNum2;
	int m_failureNum2;
	int m_failureNumFromIOcard;
	int m_kickoutNumber;

	int m_iKickMode;//�߷�ģʽ0:������ 1:��ƿ��	2:������ 3��������
	int m_iKickMode2;//�߷�ģʽ0:������ 1:��ƿ��	2:������ 3��������
	bool m_bCheck;//�Ƿ����ڼ�⣬0ֹͣ��⣬1�����ڼ�⡣
	bool m_bIsCheck[CAMERA_MAX_COUNT];//������Ƿ����ڼ��
	int nModelReadFailureNumber;//nMouldID = -1������δ����Ϊ0
	int nModelChenkedNumber[99];//nMouldIDΪ0-99������ͳ��
	int nModelCheckedCount;	// nMouldID����

	QString strSpeed;

	//����ͳ��
	int m_iErrorCamCount[CAMERA_MAX_COUNT];// ÿ������Ĵ������
	double m_iErrorCamRate[CAMERA_MAX_COUNT];// ÿ������Ĵ�����
	int m_iErrorTypeCount[ERRORTYPE_MAX_COUNT];//ÿ���������͵Ĵ������
	cErrorTypeInfo m_cErrorTypeInfo[CAMERA_MAX_COUNT];//ͳ�ƴ�����Ϣ
	//�����ϴ�ҳ����Ϣ
	//e_CurrentMainPage m_eLastMainPage;
//	e_CurrentSettingPage m_eLastSettingPage;


	e_SaveImageType m_eSaveImageType;
	int m_iSaveImgCount[CAMERA_MAX_COUNT];
   
	int iStatisticsInfoSaveMode;  //0��ʱ�䣬1������
//	QList<s_StatisticsInfo> listStatisticsInfo; 
	int m_iCamLostImgNo[CAMERA_MAX_COUNT];// ������߼��� 
	int m_iLastTriggerSignalCount;
	int m_iCamContinueReject[CAMERA_MAX_COUNT];// ������޼���


	_RunningInfo()
	{
		m_iLastIOCard1IN0=0;
		m_iPermission = 0;
		m_bCheck = false;
		m_checkedNum = 0;
		m_passNum = 0;
		m_failureNum = 0;
		m_iKickMode = 3;//�߷�ģʽ��Ϊ3(������)

		m_checkedNum2 = 0;
		m_passNum2 = 0;
		m_failureNum2 = 0;
		m_iKickMode2 = 3;//�߷�ģʽ��Ϊ3(������)
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
	QString m_sAlgFilePath;// �㷨·�� [10/26/2010 GZ]
///	QString m_strModelName;

	_ConfigInfo()
	{
//		sSystemInfo = s_SystemInfo();
	}

}s_ConfigInfo;
#endif // COMMON_H