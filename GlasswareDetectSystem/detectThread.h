#ifndef DETECTTHREAD_H
#define DETECTTHREAD_H

#include <QThread>
#include "stateTool.h"
#pragma once 

class DetectThread : public QThread
{
	Q_OBJECT

public:
	DetectThread(QObject *parent);
	~DetectThread();
public:
	void run();
	void WaitThreadStop();
public:
	CDetectElement DetectElement;
signals:
	void signals_updateActiveImg(int nCamNo,int nImgNo,double dCostTime,int tmpResult);
	void signals_updateCheckInfo(int IOCardNum,int checkResult,int nGrabImageCount,int type = 0);
	void signals_AddErrorTableView(int nCamSN,int nSignalNo,QString nErrorType);
	void signals_upDateList(int iCam,int iErrorType);
	void signals_upDateCamera(int nCam,int nMode = 0);
	void signals_updateCameraFailureRate();
	void signals_updateImage(QImage*, QString, QString, QString, QString, QString,QList<QRect> ,int );
	void signals_updateMaxImageItem(QImage, QString, QString, QString, QString, QString,QList<QRect>, int, int);
	void signals_ShowDebugLog(QString str,QColor color = Qt::black);
	void signals_showspeed(int);
private:
	void DetectNormal(CGrabElement* pElement);
	void DetectStress(CGrabElement* pElement);
	void rotateImage(CGrabElement* pElement);
	void checkImage(CGrabElement* pElement,int iCheckMode);
	bool getCheckResult(CGrabElement* pElement);
	void GetModelDotData(CGrabElement *pElement);
	void kickOutSample(int nSignalNo, int result);
	void kickOutBad(int nSignalNo);
	void KickOutIOCard0(int nSignalNo,int tmpResult);
	void KickOutIOCard1(int nSignalNo,int tmpResult);
	void CountDefectIOCard0(int nSignalNo,int tmpResult);
	void CountDefectIOCard1(int nSignalNo,int tmpResult);
	void saveImage(CGrabElement* pElement);
	void addErrorImageList(CGrabElement* pElement);
	void upDateState(QImage* myImage, int signalNo,double costTime,int nMouldID,QList<QRect>, int);

// 	bool Rotate90Image(char* m_pImageBuff,int m_lImageWidth,int m_lImageHeight);
	//统计运行时的数据
	void CountRuningData(int cameraNumber,int);
	//踢废函数
	void KickOut(int glasswareNum, int isKickOut, int ioCardNum);
	//重置是否发送踢废信号的标志位:isSendReject
	void ResetSendFlag(int glasswareNum);
public:
	void clearSendFlag();
	void ifSendAret(int i);
private:

	int iStressCamera;
	bool m_bStopThread;					//结束检测

	bool bCheckResult[CAMERA_MAX_COUNT];
	int iErrorType;
	int iMaxErrorType;
	int iMaxErrorArea;

	bool isShowImage[CAMERA_MAX_COUNT];
	bool bIsStress;

	CSpendTime waitLocPos;
	CSpendTime WholeThread;
	CSpendTime checkTimecost;
	CSpendTime showImageDelay[CAMERA_MAX_COUNT];//显示错误图像延时
	
	QDir *dirSaveImagePath;
	//调用算法
	s_AlgCInP sAlgCInp;						//检测输入参数
	s_AlgCheckResult *pAlgCheckResult;		//返回检测结果结构体
	s_Status  sReturnStatus;				// 函数执行状态信息
public:
	int ThreadNumber;					//线程号，对应相机号
	int iCamera;
	int iImageNo;
public:
	static bool isSendReject[256];//基于瓶身是否踢废变量，针对相机0-5，9-20
	int isShowPicture[256];//图片是否显示
	QMutex ShowPicture;
	int grabImageCount;
	int lastSignalNumber;
	bool m_lastResult;
	int m_lastSignal;
};

#endif // DetectThread_H
