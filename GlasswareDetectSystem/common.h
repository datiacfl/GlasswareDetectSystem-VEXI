#ifndef COMMON_H
#define COMMON_H
#pragma once

//���_WIN32_WINNT δ����ı��뾯��
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

#pragma warning(disable:4005) //����ʾ���ض��徯��

//����������
#define CAMERA_MAX_COUNT 30
//#define ERROR_MAX_COUNT 43
//���������͸���
#define ERRORTYPE_MAX_COUNT 50
#define IOCard_MAX_COUNT 2
//����ͼ�����
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


// ϵͳ����
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

// ����������
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

//������־����
enum e_SaveLogType	    
{
	OperationLog = 0,			//������־
	DebugLog,					//������־(ȱͼ || �󴥷� || ������Ϊ�� ����־��Ϣ)
	AbnormityLog,               //�쳣��־(�쳣���� || �����ϲ�Ӧ���ֵ��жϴ���)

	CheckLog,		            //�����־
	MendParamLog,			    //�޸Ĳ�����־
	StatInfo,					//���ͳ����Ϣ��־
	AlgorithmDLL				//�㷨����־
};
// �ɼ�ͼ������
enum e_GrabImageType	
{
	BodyImage = 0,	    // ƿ��
	BottomImage		// ƿ��
};
//����ͼ������
enum e_SaveImageType
{
	NotSave = 0,
	AllImage,
	FailureImage,
	AllImageInCount,
	FailureImageInCount,
};

// ������
enum e_CameraType	
{
	Camera1 = 0,	 
	Camera2,
	Camera3,
	Camera4		
};

//��ǰ����״̬
enum e_DrawStatus	
{
	DRAW_Status_NULL = 0,			//�޲���
	DRAW_Status_MOVE,				//�ƶ�
	DRAW_Status_ZOOM,				//����
	DRAW_Status_MODIFY,				//�޸�
};


//��ǰ���λ�����ڵ�
enum e_DrawSelect	
{
	DRAW_Select_NULL = 0,			//�޲�����
	DRAW_Select_MOVE,				//�ƶ���
	DRAW_Select_ZOOM,				//���ŵ�
	DRAW_Select_MODIFY,				//�޸ĵ�
};
//Ȩ��
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
//ѡȡ��
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

//���νṹ��
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
	short iGrabCount;				//ͼ���
	short iGrabDelay;				//�ɼ���ʱ
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