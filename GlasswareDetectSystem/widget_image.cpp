#include "widget_image.h"
#include "glasswaredetectsystem.h"

extern GlasswareDetectSystem *pMainFrm;

ImageWidget::ImageWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	iSpacing = 10;
	iShownMode = -1;
	iImagePage = 0;
	bIsCarveWidgetShow = false;
	bIsStopAllStessCheck = false;
	for (int i = 0; i < CAMERA_MAX_COUNT; i++)
	{
		bIsShow[i] = true;
		bIsShowErrorImage[i] = false;
		nImageWidth[i] = 0;
		nImageHeight[i] = 0;
		nSignalNumber[i] = 0;
		iImagePosition[i] = -1;
		ImageError[i] = NULL;
		sAlgImageLocInfo[i].sXldPoint.nColsAry = new int[4*BOTTLEXLD_POINTNUM];
		sAlgImageLocInfo[i].sXldPoint.nRowsAry = new int[4*BOTTLEXLD_POINTNUM];

	}
	initDialog();
	checkCamera();

	
//	ui.scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
}
ImageWidget::~ImageWidget()
{
	for (int i = 0; i < CAMERA_MAX_COUNT; i++)
	{
		delete[] sAlgImageLocInfo[i].sXldPoint.nColsAry;
		delete[] sAlgImageLocInfo[i].sXldPoint.nRowsAry;
		if (ImageError[i] != NULL)
		{
			delete ImageError[i];
			ImageError[i] = NULL;
		}
	}	
//	delete gridLayoutLeft;
//	delete gridLayoutMiddle;
//	delete gridLayoutRight;
}
void ImageWidget::resizeEvent(QResizeEvent *event)
{
	widgetWidth = ui.scrollArea->geometry().width();
	widgetHeight = ui.scrollArea->geometry().height();

	int minItemHeight = (widgetHeight - 3*iSpacing)/2,minItemWidth;

	if (0 == pMainFrm->m_sSystemInfo.m_iTwoImagePage)
	{
		for (int i = 0; i < pMainFrm->m_sSystemInfo.iCamCount; i++)
		{
			minItemHeight = (widgetHeight - 3*iSpacing)/2;
			minItemWidth = minItemHeight/2;
			MyImageShowItem *imageShowItem = listImageShowItem.at(i);
			imageShowItem->setMinimumSize(minItemWidth,minItemHeight);
		}
	}
}

void ImageWidget::initDialog()
{
	buttonTurnImage = new QPushButton;
 	//设置图片
 	QPixmap iconTurnImage(":/sysButton/turnImage");
 	buttonTurnImage->setIcon(iconTurnImage);
	buttonTurnImage->setFixedSize(iconTurnImage.size());
	bool bTwoPage = false;
	int iTempNo = 0;
	int iStressNo[CAMERA_MAX_COUNT] = {0};
	int iNormalCameraNo = 0;
	for (int i=0; i<pMainFrm->m_sSystemInfo.iCamCount;i++)
	{
		if (0 == pMainFrm->m_sCarvedCamInfo[i].m_iImageType && 2 == pMainFrm->m_sCarvedCamInfo[i].m_iStress)
		{
			bTwoPage = true;
			iStressNo[i] = iTempNo++;
		}
		else
		{
			iNormalCameraNo++;
		}
	}
	if (!bTwoPage)
	{
		buttonTurnImage->setVisible(false);
	}
	connect(buttonTurnImage, SIGNAL(clicked()), this, SLOT(slots_turnImage()));
	if (0 == pMainFrm->m_sSystemInfo.m_iTwoImagePage)
	{
		buttonTurnImage->setVisible(false);
	}

	buttonShowCarve = new QPushButton;
 	QPixmap iconShowCarve(":/sysButton/arrowright");
 	buttonShowCarve->setIcon(iconShowCarve);
 	buttonShowCarve->setFixedSize(iconTurnImage.size());
	connect(buttonShowCarve, SIGNAL(clicked()), this, SLOT(slots_showCarve()));

	ui.widget->setWidgetName(tr("Image"));
	ui.LayoutName->addWidget(buttonShowCarve);
	ui.LayoutName->addWidget(ui.widget->widgetName);
	ui.LayoutName->addStretch();
	ui.LayoutName->addWidget(buttonTurnImage);

	QWidget *WidgetScrollArea = new QWidget();
	widgetContent = new QWidget(WidgetScrollArea);
	widgetContentStess = new QWidget(WidgetScrollArea);
	QHBoxLayout *Contentlayout = new QHBoxLayout(WidgetScrollArea);
	Contentlayout->addWidget(widgetContent);
	Contentlayout->addWidget(widgetContentStess);
	Contentlayout->setSpacing(0);
	Contentlayout->setContentsMargins(0,0,0,0);

// 	WidgetScrollArea->setLayout(scrollArea);
	ui.scrollArea->setWidget(WidgetScrollArea);
	gridLayoutImage = new QGridLayout(widgetContent);
	gridLayoutStressImage = new QGridLayout(widgetContentStess);

	if ((1 == pMainFrm->m_sSystemInfo.iIsButtomStress) || (13 == pMainFrm->m_sSystemInfo.iRealCamCount))
	{
		gridLayoutLeft = new QGridLayout(this);
		gridLayoutMiddle = new QGridLayout(this);
		gridLayoutRight = new QGridLayout(this);
	}

	for (int i = 0; i < pMainFrm->m_sSystemInfo.iCamCount; i++)
	{
		MyImageShowItem *imageShowItem = new MyImageShowItem(widgetContent);
		imageShowItem->inital(i);
		listImageShowItem.append(imageShowItem);
		if (VexiFinishButtom == pMainFrm->m_sSystemInfo.m_iSystemType)
		{
			gridLayoutImage->addWidget(imageShowItem,i%2,i/2,1,1);
		}
	}
	widgetContentStess->setVisible(false);
	gridLayoutImage->setSpacing(iSpacing);
	gridLayoutImage->setContentsMargins(iSpacing,iSpacing,iSpacing,iSpacing);
	gridLayoutStressImage->setSpacing(iSpacing);
	gridLayoutStressImage->setContentsMargins(iSpacing,iSpacing,iSpacing,iSpacing);
//	widgetContentStess->setVisible(false);


	for (int i = 0;i<pMainFrm->m_sSystemInfo.iCamCount;i++)
	{
		MyImageShowItem *imageShowItem = listImageShowItem.at(i);

		connect(imageShowItem,SIGNAL(signals_imageItemDoubleClick(int ) ),this,SLOT(slots_imageItemDoubleClick(int )));

		connect(imageShowItem,SIGNAL(signals_showStartRefresh(int)),this,SLOT(slots_showStartRefresh(int)));
		connect(imageShowItem,SIGNAL(signals_showPrevious(int)),this,SLOT(slots_showPrevious(int)));
		connect(imageShowItem,SIGNAL(signals_showFollowing(int)),this,SLOT(slots_showFollowing(int)));

		connect(imageShowItem,SIGNAL(signals_showCheck(int)),this,SLOT(slots_showCheck(int)));
		connect(imageShowItem,SIGNAL(signals_stopCheck(int)),this,SLOT(slots_stopCheck(int)));
		connect(imageShowItem,SIGNAL(signals_startCheck(int)),this,SLOT(slots_startCheck(int)));
		connect(imageShowItem,SIGNAL(signals_startShow(int)),this,SLOT(slots_startShow(int)));
		connect(imageShowItem,SIGNAL(signals_stopShow(int)),this,SLOT(slots_stopShow(int)));
		connect(imageShowItem,SIGNAL(signals_startShowAll()),this,SLOT(slots_startShowAll()));

// 		connect(pMainFrm->pdetthread[i],SIGNAL(signals_updateActiveImg(int,int,double,int)),this,SLOT(slots_updateActiveImg(int,int,double,int)));

	}
	for (int i = 0;i<pMainFrm->m_sSystemInfo.iCamCount;i++)
	{
		connect(pMainFrm->pdetthread[i], SIGNAL(signals_AddErrorTableView(int,int,QString)), this, SLOT(slots_addError(int,int,QString)));
	}
}
void ImageWidget::slots_intoWidget()
{
	for (int i = 0; i < pMainFrm->m_sSystemInfo.iCamCount; i++)
	{	
		if (bIsShow[i])
		{
			MyImageShowItem *imageShowItem = listImageShowItem.at(i);
			connect(pMainFrm->pdetthread[i],SIGNAL(signals_updateImage(QImage*, QString , QString ,QString , QString, QString,QList<QRect>,int )),imageShowItem,SLOT(slots_updateImage(QImage*, QString , QString ,QString , QString, QString,QList<QRect>,int )));
		}
	}
}
bool ImageWidget::leaveWidget()
{
	for (int i = 0; i < pMainFrm->m_sSystemInfo.iCamCount; i++)
	{
		MyImageShowItem *imageShowItem = listImageShowItem.at(i);
		disconnect(pMainFrm->pdetthread[i],SIGNAL(signals_updateImage(QImage*, QString , QString ,QString , QString,QString, QList<QRect>,int )),imageShowItem,SLOT(slots_updateImage(QImage*, QString , QString ,QString , QString,QString, QList<QRect>,int )));
	}

	return true;
}
//检查对应相机是否正确初始化
bool ImageWidget::checkCamera()
{
	bool bRet = true;
	for (int i = 0; i < pMainFrm->m_sSystemInfo.iCamCount; i++)
	{
		int iRealCameraSN = pMainFrm->m_sCarvedCamInfo[i].m_iToRealCamera;
		MyImageShowItem *imageShowItem = listImageShowItem.at(i);
		if (!pMainFrm->m_sRealCamInfo[iRealCameraSN].m_bCameraInitSuccess)
		{
			imageShowItem->slots_showErrorInfo(pMainFrm->m_sRealCamInfo[iRealCameraSN].m_strErrorInfo);
			bRet = false;
		}
		else
		{
			imageShowItem->slots_clearErrorInfo();
			emit signals_SetCameraStatus(i,1);
		}
	}
	return true;
}
void ImageWidget::slots_turnImage()
{
	if (iShownMode != -1) //显示全部图像
	{
		slots_imageItemDoubleClick(iShownMode);
	}
	if (iImagePage == 0)
	{
		widgetContent->setVisible(false);
		widgetContentStess->setVisible(true);
		iImagePage = 1;
	}
	else
	{
		widgetContentStess->setVisible(false);
		widgetContent->setVisible(true);

		iImagePage = 0;
	}
}
void ImageWidget::slots_showCarve()
{
	if (!bIsCarveWidgetShow)
	{
		QPixmap iconShowCarve(":/sysButton/arrowLeft");
		buttonShowCarve->setIcon(iconShowCarve);
		emit signals_showCarve();
		bIsCarveWidgetShow = true;
	}
	else
	{
		QPixmap iconHideCarve(":/sysButton/arrowright");
		buttonShowCarve->setIcon(iconHideCarve);
		emit signals_hideCarve();
		bIsCarveWidgetShow = false;
	}
}

void ImageWidget::slots_imageItemDoubleClick(int iCameraNo)
{	
	if (iShownMode != -1) //显示全部图像
	{
		widgetContent->setMinimumWidth(iSpacing);
		for (int i = 0; i < pMainFrm->m_sSystemInfo.iCamCount; i++)
		{
			listImageShowItem.at(i)->setVisible(true);
			listImageShowItem.at(i)->setMaxShow(false);
		}
		iShownMode = -1;
	}else //只显示双击图像
	{
		widgetContent->setMinimumWidth(iSpacing);
		for (int i = 0; i < pMainFrm->m_sSystemInfo.iCamCount; i++)
		{
			if (iCameraNo == i)
			{
				listImageShowItem.at(i)->setVisible(true); 
				listImageShowItem.at(i)->setMaxShow(true);
			}
			else
			{
				if (iCameraNo != -1)
				{
					listImageShowItem.at(i)->setVisible(false);
				}
			}
		}
		iShownMode = iCameraNo;
	}
}
void ImageWidget::slots_showPrevious(int nItemID)
{
	bool bFound = false;
	CGrabElement* pElement;

	pMainFrm->m_ErrorList.m_mutexmErrorList.lock();

	for (int i = iImagePosition[nItemID]+1; i < pMainFrm->m_ErrorList.listError.length(); i++)
	{
		pElement = pMainFrm->m_ErrorList.listError.at(i);
		if (pElement->nCamSN == nItemID)
		{
			iImagePosition[nItemID] = i;
			bFound = true;
			break;
		}
	}
	pMainFrm->m_ErrorList.m_mutexmErrorList.unlock();

	if (bFound)
	{
		slots_stopShow(nItemID);

		QString camera = QString::number(pElement->nCamSN+1);
		QString imageSN = QString::number(pElement->nSignalNo);
		QString time = QString::number(pElement->dCostTime,'f',2);
		QString result = pMainFrm->m_sErrorInfo.m_vstrErrorType.at(pElement->nCheckRet);
		QString Mould = QString::number(pElement->nMouldID);
		Q_ASSERT(pElement->myImage->byteCount() == pElement->myImage->height() * pElement->myImage->width());

		listImageShowItem.at(nItemID)->updateImage(pElement->myImage, camera, imageSN, time, result,Mould, pElement->cErrorRectList);
		sAlgImageLocInfo[nItemID].sLocOri = pElement->sImgLocInfo.sLocOri;
		sAlgImageLocInfo[nItemID].sXldPoint.nCount = pElement->sImgLocInfo.sXldPoint.nCount;
		memcpy(sAlgImageLocInfo[nItemID].sXldPoint.nColsAry,pElement->sImgLocInfo.sXldPoint.nColsAry,4*BOTTLEXLD_POINTNUM);
		memcpy(sAlgImageLocInfo[nItemID].sXldPoint.nRowsAry,pElement->sImgLocInfo.sXldPoint.nRowsAry,4*BOTTLEXLD_POINTNUM);
		//new一个设置算法用的QImage
		if (ImageError[nItemID] != NULL)
		{
			delete ImageError[nItemID];
			ImageError[nItemID] = NULL;
		}
		ImageError[nItemID] = new QImage(*pElement->myImage);

	}
	else if (iImagePosition[nItemID] == -1)
	{
		QString strError = QString(tr("No error Image! "));
		listImageShowItem.at(nItemID)->slots_showWarningInfo(strError);
		return;
	}
	else
	{
		QString strError = QString(tr("Alreay the final Image! "));
		listImageShowItem.at(nItemID)->slots_showWarningInfo(strError);
		return;
	}
}
void ImageWidget::slots_showFollowing(int nItemID)
{
	bool bFound = false;
	CGrabElement* pElement;
	if (iImagePosition[nItemID] == -1)
	{
		iImagePosition[nItemID] = ERROR_IMAGE_COUNT;
	}
	for (int i = iImagePosition[nItemID]-1; i >=0; i--)
	{
		if (i < 0)
		{
			continue;
		}
		pElement = pMainFrm->m_ErrorList.listError.at(i);
		if (pElement->nCamSN == nItemID)
		{
			iImagePosition[nItemID] = i;
			bFound = true;
			break;
		}
	}
	if (bFound)
	{
		slots_stopShow(nItemID);

		QString camera = QString::number(pElement->nCamSN+1);
		QString imageSN = QString::number(pElement->nSignalNo);
		QString time = QString::number(pElement->dCostTime,'f',2);
		QString result = pMainFrm->m_sErrorInfo.m_vstrErrorType.at(pElement->nCheckRet);
		QString Mould = QString::number(pElement->nMouldID);
		Q_ASSERT(pElement->myImage->byteCount() == pElement->myImage->height() * pElement->myImage->width());

		listImageShowItem.at(nItemID)->updateImage(pElement->myImage, camera, imageSN, time, result,Mould, pElement->cErrorRectList);
		sAlgImageLocInfo[nItemID].sLocOri = pElement->sImgLocInfo.sLocOri;
		sAlgImageLocInfo[nItemID].sXldPoint.nCount = pElement->sImgLocInfo.sXldPoint.nCount;
		memcpy(sAlgImageLocInfo[nItemID].sXldPoint.nColsAry,pElement->sImgLocInfo.sXldPoint.nColsAry,4*BOTTLEXLD_POINTNUM);
		memcpy(sAlgImageLocInfo[nItemID].sXldPoint.nRowsAry,pElement->sImgLocInfo.sXldPoint.nRowsAry,4*BOTTLEXLD_POINTNUM);
		//new一个设置算法用的QImage
		if (ImageError[nItemID] != NULL)
		{
			delete ImageError[nItemID];
			ImageError[nItemID] = NULL;
		}
		ImageError[nItemID] = new QImage(*pElement->myImage);


	}else if (iImagePosition[nItemID] == ERROR_IMAGE_COUNT)
	{
		QString strError = QString(tr("No error Image! "));
		listImageShowItem.at(nItemID)->slots_showWarningInfo(strError);
		iImagePosition[nItemID] = -1;
		return;
	}
	else
	{
		QString strError = QString(tr("Alreay the first Image! "));
		listImageShowItem.at(nItemID)->slots_showWarningInfo(strError);
		return;
	}
}
void ImageWidget::slots_showStartRefresh(int nItemID)
{
	bIsShow[nItemID] = true;
	iImagePosition[nItemID] = -1;
	MyImageShowItem *imageShowItem = listImageShowItem.at(nItemID);
	connect(pMainFrm->pdetthread[nItemID],SIGNAL(signals_updateImage(QImage*, QString , QString ,QString ,QString, QString,QList<QRect>,int)),imageShowItem,SLOT(slots_updateImage(QImage*, QString , QString ,QString , QString,QString, QList<QRect>,int )));
	bIsShowErrorImage[nItemID] = false;
}
void ImageWidget::slots_showErrorImage(QImage* ImageShown, int iCamera, int iSignalNo,double iCostTime, QString iErrorType,int nMouldID, QList<QRect> listRect, int listNo)
{
	slots_stopShow(iCamera);
	QString camera = QString::number(iCamera+1);
	QString imageSN = QString::number(iSignalNo);
	QString time = QString::number(iCostTime,'f',2);
	QString mouldID = QString::number(nMouldID);
	iImagePosition[iCamera] = listNo;
	listImageShowItem.at(iCamera)->updateImage(ImageShown, camera, imageSN, time, iErrorType,mouldID, listRect);
	//new一个设置算法用的QImage
	if (ImageError[iCamera] != NULL)
	{
		delete ImageError[iCamera];
		ImageError[iCamera] = NULL;
	}
	ImageError[iCamera] = new QImage(*ImageShown);

}
void ImageWidget::slots_showCheck(int nItemID)
{
	if (!pMainFrm->sPermission.iAlgSet)
	{
		return;
	}
	pMainFrm->slots_turnPage(6, nItemID);
	//if (!bIsShowErrorImage[nItemID])
	//{
	//	//pMainFrm->ShowCheckSet(nItemID);
	//	pMainFrm->slots_turnPage(6, nItemID);
	//}
	//else
	//{
	//	showErrorCheck(nItemID);
	//}
}

void ImageWidget::showErrorCheck(int nItemID)
{
	if (nItemID >= pMainFrm->m_sSystemInfo.iCamCount)
	{
		return;
	}

	try
	{
		s_Status  sReturnStatus;
		QImage* tempIamge;
		if(pMainFrm->m_SavePicture[nItemID].pThat==NULL)
		{
			return;
		}
		tempIamge=pMainFrm->m_SavePicture[nItemID].pThat;
		sReturnStatus = pMainFrm->m_cBottleModel.CloseModelDlg();
		if (sReturnStatus.nErrorID != RETURN_OK)
		{
			CLogFile::write(tr("Abnormal in close model "),AbnormityLog);
			return;
		}

		s_AlgModelPara  sAlgModelPara;	
 		sAlgModelPara.sImgPara.nChannel = 1;
		
// 		pMainFrm->m_mutexmCheckSet.lock();
 		sAlgModelPara.sImgPara.nHeight = tempIamge->height();
 		sAlgModelPara.sImgPara.nWidth = tempIamge->width();
 		sAlgModelPara.sImgPara.pcData = (char*)tempIamge->bits();
 		sAlgModelPara.sImgLocInfo = sAlgImageLocInfo[nItemID];
// 		pMainFrm->Logfile.write(tr("---- Show defect Image in AlgPage.Camera:%1----").arg(nItemID),AbnormityLog);
// 		pMainFrm->m_mutexmCheckSet.unlock
		if (sAlgModelPara.sImgPara.nHeight != pMainFrm->m_sCarvedCamInfo[nItemID].m_iImageHeight)
		{
			return;
		}
		if (sAlgModelPara.sImgPara.nWidth != pMainFrm->m_sCarvedCamInfo[nItemID].m_iImageWidth)
		{
			return;
		}		
		for (int i=0;i<pMainFrm->m_sSystemInfo.iCamCount;i++)
		{
			pMainFrm->CherkerAry.pCheckerlist[i].nID = i;
			pMainFrm->CherkerAry.pCheckerlist[i].pChecker = &pMainFrm->m_cBottleCheck[i];
		}	
		int widthd = pMainFrm->widget_alg->geometry().width();
		int heightd	= pMainFrm->widget_alg->geometry().height();
		if (widthd < 150 || heightd < 150)
		{
			return;
		}	
		sReturnStatus = pMainFrm->m_cBottleModel.SetModelDlg(sAlgModelPara,
			&pMainFrm->m_cBottleCheck[nItemID],pMainFrm->CherkerAry,pMainFrm->widget_alg);
		if (sReturnStatus.nErrorID != RETURN_OK)
		{
			CLogFile::write(tr("Abnormal in set Model"),AbnormityLog);
			return;
		}
		pMainFrm->statked_widget->setCurrentWidget(pMainFrm->widget_alg);
		pMainFrm->m_eCurrentMainPage = AlgPage;
		pMainFrm->m_eLastMainPage = AlgPage;
		pMainFrm->iLastPage = 6;

	}
	catch (...)
	{
	}
}
void ImageWidget::slots_stopCheck(int nItemID)
{
	CLogFile::write(tr("Stop camera%1 Check").arg(nItemID+1),OperationLog);
	pMainFrm->m_sRunningInfo.m_bIsCheck[nItemID] = 0;
	CameraStatusLabel *cameraStatus = pMainFrm->cameraStatus_list.at(nItemID);
	if (0 == pMainFrm->m_sCarvedCamInfo[nItemID].m_iIOCardSN)
	{
		pMainFrm->m_cCombine.SetCombineCamera(nItemID,false);
		pMainFrm->m_cCombine.i_StopCheckCamera[nItemID] = 1;

		cameraStatus->SetCameraStatus(2);
	}
	else if (1 == pMainFrm->m_sCarvedCamInfo[nItemID].m_iIOCardSN)
	{
		pMainFrm->m_cCombine1.SetCombineCamera(nItemID,false);
		cameraStatus->SetCameraStatus(0);
		pMainFrm->m_cCombine1.i_StopCheckCamera[nItemID] = 1;
	}
	pMainFrm->m_sRealCamInfo[nItemID].m_pGrabber->StopGrab();
	//emit signals_SetCameraStatus(nItemID,2);
}
void ImageWidget::slots_startCheck(int nItemID)
{
	CLogFile::write(tr("Start camera%1 Check").arg(nItemID+1),OperationLog);
	pMainFrm->m_sRunningInfo.m_bIsCheck[nItemID] = 1;
	if (0 == pMainFrm->m_sCarvedCamInfo[nItemID].m_iIOCardSN)
	{
		pMainFrm->m_cCombine.SetCombineCamera(nItemID,true);
		pMainFrm->m_cCombine.i_StopCheckCamera[nItemID] = 0;
	}
	else if (1 == pMainFrm->m_sCarvedCamInfo[nItemID].m_iIOCardSN)
	{
		pMainFrm->m_cCombine1.SetCombineCamera(nItemID,true);
		pMainFrm->m_cCombine1.i_StopCheckCamera[nItemID] = 0;

	}
	pMainFrm->m_sRealCamInfo[nItemID].m_pGrabber->StartGrab();
	emit signals_SetCameraStatus(nItemID,0);
}

void ImageWidget::slots_startShowAll()
{
	for (int i = 0; i < pMainFrm->m_sSystemInfo.iCamCount;i++)
	{
		slots_startShow(i);
	}
}

void ImageWidget::slots_startShow(int nItemID)
{
	bIsShow[nItemID] = true;
	bIsShowErrorImage[nItemID] = false;

	listImageShowItem.at(nItemID)->slots_startShow();
 	MyImageShowItem *imageShowItem = listImageShowItem.at(nItemID);
 	connect(pMainFrm->pdetthread[nItemID],SIGNAL(signals_updateImage(QImage*, QString , QString ,QString ,QString, QString,QList<QRect>,int)),imageShowItem,SLOT(slots_updateImage(QImage*, QString , QString ,QString ,QString, QString, QList<QRect>,int )),Qt::UniqueConnection);
}
void ImageWidget::slots_stopShow(int nItemID)
{
	bIsShowErrorImage[nItemID] = true;
	bIsShow[nItemID] = false;
	listImageShowItem.at(nItemID)->slots_stopShow();
 	MyImageShowItem *imageShowItem = listImageShowItem.at(nItemID);
 	disconnect(pMainFrm->pdetthread[nItemID],SIGNAL(signals_updateImage(QImage*, QString , QString ,QString , QString,QString, QList<QRect>,int )),imageShowItem,SLOT(slots_updateImage(QImage*, QString , QString ,QString , QString,QString, QList<QRect>,int )));
}
//加入新错误图像时，当前错误图像位置加1。
void ImageWidget::slots_addError(int nItemID,int nSignalNo,QString nErrorType)
{
	for (int i=0; i < pMainFrm->m_sSystemInfo.iCamCount; i++)
	{
		if (iImagePosition[i] != -1)
		{
			if (iImagePosition[i] < ERROR_IMAGE_COUNT - 1)
			{
				iImagePosition[i]++;
			}
		}
	}
}