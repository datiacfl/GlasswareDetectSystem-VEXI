#include "widget_debug.h"
#include "glasswaredetectsystem.h"
extern GlasswareDetectSystem *pMainFrm;


Widget_Debug::Widget_Debug(QWidget *parent)
	: QWidget(parent)
{
	scrollAreaWidgetContents = new QWidget();
	scrollArea = new QScrollArea(this);
	scrollArea->setWidgetResizable(true);
	widget_systemInfo = new DHBaseWidget(scrollAreaWidgetContents); 
	widget_runningInfo = new DHBaseWidget(scrollAreaWidgetContents); 
	widget_errorInfo = new DHBaseWidget(scrollAreaWidgetContents); 
	widget_cameraInfo = new DHBaseWidget(scrollAreaWidgetContents); 
	widget_realCameraInfo = new DHBaseWidget(scrollAreaWidgetContents); 
	widget_queueInfo1 = new DHBaseWidget(scrollAreaWidgetContents); 
	widget_queueInfo2 = new DHBaseWidget(scrollAreaWidgetContents); 

	DebugLogText = new CMyLogText(this);
	DebugLogText->setFixedWidth(500);
	DebugLogText->setMaximumBlockCount(1000);//保留200段日志记录

	label_systemInfo = new QLabel("systemInfo：");
	label_runningInfo = new QLabel("runningInfo：");
	label_errorInfo = new QLabel("errorInfo：");
	label_cameraInfo = new QLabel("cameraInfo:");
	label_realCameraInfo = new QLabel("realCameraInfo:");
	label_queueInfo1 = new QLabel("queueInfo1:");
	label_queueInfo2 = new QLabel("queueInfo2:");

	timerUpdateDebugInfo = new QTimer(this);

	initial();
 	for (int i = 0;i<pMainFrm->m_sSystemInfo.iCamCount;i++)
	{
		connect(pMainFrm->pdetthread[i],SIGNAL(signals_ShowDebugLog(QString,QColor)),this,SLOT(slots_ShowDebugLog(QString,QColor))) ;
	}
}

Widget_Debug::~Widget_Debug()
{
}
void Widget_Debug::slots_intoWidget()
{
	timerUpdateDebugInfo->setInterval(100);
	connect(timerUpdateDebugInfo, SIGNAL(timeout()), this, SLOT(slots_updateDebugInfo()),Qt::QueuedConnection);   
	timerUpdateDebugInfo->start();

}

bool Widget_Debug::leaveWidget()
{
	disconnect(timerUpdateDebugInfo, SIGNAL(timeout()), this, SLOT(slots_updateDebugInfo()));   
	timerUpdateDebugInfo->stop();
	return true;
}

void Widget_Debug::initial()
{
	widget_systemInfo->setWidgetName(tr("system info"));
	QVBoxLayout *layoutSystemInfo = new QVBoxLayout(widget_systemInfo);
	layoutSystemInfo->addWidget(widget_systemInfo->widgetName);
	layoutSystemInfo->addWidget(label_systemInfo);
	layoutSystemInfo->setContentsMargins(5,0,5,5);

	widget_runningInfo->setWidgetName(tr("running info"));
	QVBoxLayout *layoutRunningInfo = new QVBoxLayout(widget_runningInfo);
	layoutRunningInfo->addWidget(widget_runningInfo->widgetName);
	layoutRunningInfo->addWidget(label_runningInfo);
	layoutRunningInfo->setContentsMargins(5,0,5,5);

	widget_cameraInfo->setWidgetName(tr("camera info"));
	QVBoxLayout *layoutCameraInfo = new QVBoxLayout(widget_cameraInfo);
	layoutCameraInfo->addWidget(widget_cameraInfo->widgetName);
	layoutCameraInfo->addWidget(label_cameraInfo);
	layoutCameraInfo->setContentsMargins(5,0,5,5);

	widget_realCameraInfo->setWidgetName(tr("real camera info"));
	QVBoxLayout *layoutRealCameraInfo = new QVBoxLayout(widget_realCameraInfo);
	layoutRealCameraInfo->addWidget(widget_realCameraInfo->widgetName);
	layoutRealCameraInfo->addWidget(label_realCameraInfo);
	layoutRealCameraInfo->setContentsMargins(5,0,5,5);

	widget_queueInfo1->setWidgetName(tr("queue info1"));
	QVBoxLayout *layoutQueueInfo1 = new QVBoxLayout(widget_queueInfo1);
	layoutQueueInfo1->addWidget(widget_queueInfo1->widgetName);
	layoutQueueInfo1->addWidget(label_queueInfo1);
	layoutQueueInfo1->setContentsMargins(5,0,5,5);

	widget_queueInfo2->setWidgetName(tr("queue info2"));
	QVBoxLayout *layoutQueueInfo2 = new QVBoxLayout(widget_queueInfo2);
	layoutQueueInfo2->addWidget(widget_queueInfo2->widgetName);
	layoutQueueInfo2->addWidget(label_queueInfo2);
	layoutQueueInfo2->setContentsMargins(5,0,5,5);

	widget_errorInfo->setWidgetName(tr("error info"));
	QVBoxLayout *layoutErrorInfo = new QVBoxLayout(widget_errorInfo);
	layoutErrorInfo->addWidget(widget_errorInfo->widgetName);
	layoutErrorInfo->addWidget(label_errorInfo);
	layoutErrorInfo->setContentsMargins(5,0,5,5);

	QWidget *widgetDebufinfo = new QWidget();
	QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
// 	sizePolicy.setHorizontalStretch(0);
// 	sizePolicy.setVerticalStretch(0);
	sizePolicy.setHeightForWidth(widgetDebufinfo->sizePolicy().hasHeightForWidth());
	widgetDebufinfo->setSizePolicy(sizePolicy);


	QGridLayout *layoutScrollArea = new QGridLayout(widgetDebufinfo);
	layoutScrollArea->addWidget(widget_systemInfo,0,0,1,1);
	layoutScrollArea->addWidget(widget_runningInfo,0,1,1,1);
	layoutScrollArea->addWidget(widget_cameraInfo,1,0,1,1);
	layoutScrollArea->addWidget(widget_realCameraInfo,1,1,1,1);
	layoutScrollArea->addWidget(widget_errorInfo,2,0,1,2);
	layoutScrollArea->addWidget(widget_queueInfo1,3,0,1,1);
	layoutScrollArea->addWidget(widget_queueInfo2,3,1,1,1);

	QHBoxLayout *mainLayoutWidget = new QHBoxLayout(scrollAreaWidgetContents);
	mainLayoutWidget->addWidget(widgetDebufinfo);
//	mainLayoutWidget->addWidget(DebugLogText);
	mainLayoutWidget->setMargin(6);
	mainLayoutWidget->setContentsMargins(5,5,5,5);

	scrollArea->setWidget(scrollAreaWidgetContents);

	QHBoxLayout *mainLayout = new QHBoxLayout(this);
	mainLayout->addWidget(scrollArea);
	mainLayout->addWidget(DebugLogText);
}

void Widget_Debug::slots_updateDebugInfo()
{
	getSystemInfo();
	getRunningInfo();
	getCameraInfo();
	getRealCameraInfo();
	getqueueInfo1Info();
	getqueueInfo2Info();
	geterrorInfoInfo();
	//for (int i = 0;i<1000000000;i++)
	//{
	//	int j;
	//	j=j+1;
	//}
 	//timerUpdateDebugInfo->stop();
}
void Widget_Debug::getSystemInfo()
{
	QString strConfigIOCardInfo;
	for(int i = 0;i<pMainFrm->m_sSystemInfo.iIOCardCount;i++)
	{
		strConfigIOCardInfo += "m_sConfigIOCardInfo:" + QString::number(pMainFrm->m_sSystemInfo.m_sConfigIOCardInfo[i].iCardID) +" "+ pMainFrm->m_sSystemInfo.m_sConfigIOCardInfo[i].strCardInitFile +" "+ pMainFrm->m_sSystemInfo.m_sConfigIOCardInfo[i].strCardName +"\n";
	}


	label_systemInfo->setText("systemType:"+QString::number(pMainFrm->m_sSystemInfo.m_iSystemType)+"\n" + \
		"iRealCamCount:" + QString::number(pMainFrm->m_sSystemInfo.iRealCamCount)+"\n" + \
		"iCamCount:" + QString::number(pMainFrm->m_sSystemInfo.iCamCount)+"\n" + \
		"IsCameraCount:" + QString::number(pMainFrm->m_sSystemInfo.iIsCameraCount)+"\n" + \

		"m_iMaxCameraImageWidth:" + QString::number(pMainFrm->m_sSystemInfo.m_iMaxCameraImageWidth)+"\n" + \
		"m_iMaxCameraImageHeight:" + QString::number(pMainFrm->m_sSystemInfo.m_iMaxCameraImageHeight)+"\n" + \
		"m_iMaxCameraImageSize:" + QString::number(pMainFrm->m_sSystemInfo.m_iMaxCameraImageSize)+"\n" + \
		strConfigIOCardInfo

		);
}
void Widget_Debug::getRunningInfo()
{
	label_runningInfo->setText("m_iPermission:" + QString::number(pMainFrm->m_sRunningInfo.m_iPermission)+"\n" + 
		"checkedNum:" + QString::number(pMainFrm->m_sRunningInfo.m_checkedNum)+"\n" + 
		"passNum:" + QString::number(pMainFrm->m_sRunningInfo.m_passNum)+"\n" + 
		"failureNum:" + QString::number(pMainFrm->m_sRunningInfo.m_failureNum)+"\n" + 
		"checkedNum2:" + QString::number(pMainFrm->m_sRunningInfo.m_checkedNum2)+"\n" + 
		"passNum2:" + QString::number(pMainFrm->m_sRunningInfo.m_passNum2)+"\n" + 
		"failureNum2:" + QString::number(pMainFrm->m_sRunningInfo.m_failureNum2)+"\n" 
		);
}
void Widget_Debug::getCameraInfo()
{
	QString strToRealCamera;
	QString strResImageWidth;
	QString strResImageHeight;
	QString strIOCardSN;			//对应踢废接口卡
	QString strImageType;			//图像类型
	QString strGrabPosition;
	QString strStress;				//是否是应力图像0：普通图像 1：正常需要传出定位信息2：应力图像
	QString strToNormalCamera;
	QString strImgGrabCounter;

	for(int i = 0;i<pMainFrm->m_sSystemInfo.iCamCount;i++)
	{
		strToRealCamera += QString::number(pMainFrm->m_sCarvedCamInfo[i].m_iToRealCamera) + " ";
		strResImageWidth += QString::number(pMainFrm->m_sCarvedCamInfo[i].m_iResImageWidth) + " ";
		strResImageHeight += QString::number(pMainFrm->m_sCarvedCamInfo[i].m_iResImageHeight) + " ";
		strIOCardSN += QString::number(pMainFrm->m_sCarvedCamInfo[i].m_iIOCardSN) + " ";
		strImageType += QString::number(pMainFrm->m_sCarvedCamInfo[i].m_iImageType) + " ";
		strGrabPosition += QString::number(pMainFrm->m_sCarvedCamInfo[i].m_iGrabPosition) + " ";
		strStress += QString::number(pMainFrm->m_sCarvedCamInfo[i].m_iStress) + " ";
		strToNormalCamera += QString::number(pMainFrm->m_sCarvedCamInfo[i].m_iToNormalCamera) + " ";
		strImgGrabCounter += QString::number(pMainFrm->m_iImgGrabCounter[i]) + " ";

	}

	label_cameraInfo->setText("ToRealCamera:" + strToRealCamera + "\n"
		"IOCardSN:" + strIOCardSN +"\n"
		"ImageType:" + strImageType +"\n"
		"GrabPosition:" + strGrabPosition +"\n"
		"Stress:" + strStress +"\n"
		"ToNormalCamera:" + strToNormalCamera +"\n"
		"ImgGrabCounter:" + strImgGrabCounter +"\n"

//		"ResImageWidth:" + strResImageWidth +"\n"
//		"ResImageHeight:" + strResImageHeight +"\n"
		);
}
void Widget_Debug::getRealCameraInfo()
{
	QString strCameraInitSuccess;	//相机初始化是否成功
	QString strIOCardSN;			//对应踢废接口卡
	QString strImageType;			//图像类型
	QString strGrabPosition;		//相机采集工位
	QString strGrabIsStart;			//相机是否开始
	QString strGrabImageCount;			//相机拍照张数[3/14/2011 lly]::njc拍照总数，包括误触发
	QString strImageIdxLast;			// 图像号，用于判断误触发 [12/19/2010 zhaodt]
	QString strGrabCounter;

	for(int i = 0;i<pMainFrm->m_sSystemInfo.iRealCamCount;i++)
	{
		strCameraInitSuccess += QString::number(pMainFrm->m_sRealCamInfo[i].m_bCameraInitSuccess) + " ";
		strIOCardSN += QString::number(pMainFrm->m_sRealCamInfo[i].m_iIOCardSN) + " ";
		strImageType += QString::number(pMainFrm->m_sRealCamInfo[i].m_iImageType) + " ";
		strGrabPosition += QString::number(pMainFrm->m_sRealCamInfo[i].m_iGrabPosition) + " ";
		strGrabIsStart += QString::number(pMainFrm->m_sRealCamInfo[i].m_bGrabIsStart) + " ";
		strGrabImageCount += QString::number(pMainFrm->m_sRealCamInfo[i].m_iGrabImageCount) + " ";
		strImageIdxLast += QString::number(pMainFrm->m_sRealCamInfo[i].m_iImageIdxLast) + " ";
		strGrabCounter += QString::number(pMainFrm->m_iGrabCounter[i]) + " ";
	}
	label_realCameraInfo->setText("CameraInitSuccess:" + strCameraInitSuccess + "\n"
		"IOCardSN:" + strIOCardSN + "\n"
		"ImageType:" + strImageType + "\n"
		"GrabPosition:" + strGrabPosition + "\n"
		"GrabIsStart:" + strGrabIsStart + "\n"
		"GrabImageCount:" + strGrabImageCount + "\n"
		"ImageIdxLast:" + strImageIdxLast + "\n"
		"GrabCounter:" + strGrabCounter + "\n"
		);
}
void Widget_Debug::getqueueInfo1Info()
{
	QString strCameraCount =  QString::number(pMainFrm->m_cCombine.i_CameraCount);
	QString strLatestImageNo =  QString::number(pMainFrm->m_cCombine.m_iLatestImageNo);
	QString strCombinCamera;
	QString strStopCheckCamera;
	QString strRlts;

	for(int i = 0;i<pMainFrm->m_sSystemInfo.iCamCount;i++)
	{
		strCombinCamera +=  QString::number(pMainFrm->m_cCombine.b_CombinCamera[i]) + " ";
		strStopCheckCamera +=  QString::number(pMainFrm->m_cCombine.i_StopCheckCamera[i]) + " ";
	}
 	for(int i = 0;i<256;i++)
 	{
 		for(int j = 0;j<pMainFrm->m_sSystemInfo.iCamCount;j++)
 		{
 			strRlts +=  QString::number(pMainFrm->m_cCombine.m_Rlts[i].b_Checked[j]) + " ";
 		}
 		strRlts += "\n";
 	}
	//for(int i = 0;i<256;i++)
	//{
	//	strRlts +=  QString::number(pMainFrm->m_cCombine.sErrorPara[i].nErrorType) + " ";
	//	strRlts +=  QString::number(pMainFrm->m_cCombine.iErrorCamera[i]) + " ";
	//	strRlts += "\n";
	//}
	if (pMainFrm->m_sRunningInfo.m_iPermission<8)
	{
		label_queueInfo1->setText("CameraCount: "+ strCameraCount +"\n" + 
			"LatestImageNo: "+ strLatestImageNo + "\n" + 
			"CombinCamera: "+ strCombinCamera + "\n" + 
			"StopCheckCamera: "+ strStopCheckCamera + "\n"
// 			"Rlts: "+ strRlts
			);
	}
	else
	{
		label_queueInfo1->setText("CameraCount: "+ strCameraCount +"\n" + 
			"LatestImageNo: "+ strLatestImageNo + "\n" + 
			"CombinCamera: "+ strCombinCamera + "\n" + 
			"StopCheckCamera: "+ strStopCheckCamera + "\n" + 
			"Rlts: "+ strRlts
			);
	}
}
void Widget_Debug::getqueueInfo2Info()
{
	QString strCameraCount =  QString::number(pMainFrm->m_cCombine1.i_CameraCount);
	QString strLatestImageNo =  QString::number(pMainFrm->m_cCombine1.m_iLatestImageNo);
	QString strCombinCamera;
	QString strStopCheckCamera;
	QString strRlts;

	for(int i = 0;i<pMainFrm->m_sSystemInfo.iCamCount;i++)
	{
		strCombinCamera +=  QString::number(pMainFrm->m_cCombine1.b_CombinCamera[i]) + " ";
		strStopCheckCamera +=  QString::number(pMainFrm->m_cCombine1.i_StopCheckCamera[i]) + " ";
	}
 	for(int i = 0;i<256;i++)
 	{
 		for(int j = 0;j<pMainFrm->m_sSystemInfo.iCamCount;j++)
 		{
 			strRlts +=  QString::number(pMainFrm->m_cCombine1.m_Rlts[i].b_Checked[j]) + " ";
 		}
 		strRlts += "\n";
 	}
	//for(int i = 0;i<256;i++)
	//{
	//	strRlts +=  QString::number(pMainFrm->m_cCombine1.sErrorPara[i].nErrorType) + " ";
	//	strRlts +=  QString::number(pMainFrm->m_cCombine1.iErrorCamera[i]) + " ";
	//	strRlts += "\n";
	//}
	if (pMainFrm->m_sRunningInfo.m_iPermission<8)
	{

		label_queueInfo2->setText("CameraCount: "+ strCameraCount +"\n" + 
			"LatestImageNo: "+ strLatestImageNo + "\n" + 
			"CombinCamera: "+ strCombinCamera + "\n" + 
			"StopCheckCamera: "+ strStopCheckCamera + "\n"
// 			"Rlts: "+ strRlts
			);
	}else
	{
		label_queueInfo2->setText("CameraCount: "+ strCameraCount +"\n" + 
			"LatestImageNo: "+ strLatestImageNo + "\n" + 
			"CombinCamera: "+ strCombinCamera + "\n" + 
			"StopCheckCamera: "+ strStopCheckCamera + "\n" + 
			"Rlts: "+ strRlts
			);

	}
}
void Widget_Debug::geterrorInfoInfo()
{
	QString GrabListLength;
	QString DetectListLength;
	QString toNormal;
	QString toStress;

	for(int i = 0;i<pMainFrm->m_sSystemInfo.iCamCount;i++)
	{
		GrabListLength += QString::number(i)+ ":" + QString::number(pMainFrm->m_queue[i].listGrab.count()) + " ";
		DetectListLength += QString::number(i)+ ":" + QString::number(pMainFrm->m_queue[i].listDetect.length()) + " ";
 		toNormal +=  QString::number(i)+ ":" + QString::number(pMainFrm->m_sCarvedCamInfo[i].m_iToNormalCamera) + " ";
 		toStress += QString::number(i)+ ":" + QString::number(pMainFrm->m_sCarvedCamInfo[i].m_iToStressCamera) + " ";
	}

	label_errorInfo->setText("GrabListLength: " + GrabListLength + "\n" + 
		"DetectListLength: " + DetectListLength + "\n" + 
		"toNormal: " + toNormal + "\n" + 
		"toStress: " + toStress);

}

void Widget_Debug::slots_ShowDebugLog(QString str,QColor color)
{
	DebugLogText->writeLog(str,color);
}
