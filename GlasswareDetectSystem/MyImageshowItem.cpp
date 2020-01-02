#include "myimageshowitem.h"
#include <QLabel>
#include <QLayout>
#include <QDateTime>
// #include <QFile>
#include <QFileDialog>
#include <QColor>
#include "glasswaredetectsystem.h"
extern GlasswareDetectSystem *pMainFrm;

MyImageShowItem::MyImageShowItem(QWidget *parent)
	: QWidget(parent)
{
	layoutButton = NULL;
	mainLayout = NULL;
	PicButtonLayout = NULL;
	mainBoxLayout = NULL;
	bIsUpdateImage = true;
	bIsMaxShow = false;
	bIsCheck = true;

	colorRect = QColor(0,0,0);
	btnPrevious = new PushButton(this);
	btnFollowing = new PushButton(this);
	btnStartRefresh = new PushButton(this);
	btnPrevious->setVisible(false);
	btnFollowing->setVisible(false);
	btnStartRefresh->setVisible(false);
	singleCameraCount = 0;
	connect(btnPrevious, SIGNAL(clicked()), this, SLOT(slots_showPrevious()));
	connect(btnFollowing, SIGNAL(clicked()), this, SLOT(slots_showFollowing()));
	connect(btnStartRefresh, SIGNAL(clicked()), this, SLOT(slots_showStartRefresh()));

	createActions();

	m_vcolorTable.clear();
	for (int i = 0; i < 256; i++)  
	{  
		m_vcolorTable.append(qRgb(i, i, i)); 
	} 
	timerErrorInfo = new QTimer(this);
	timerErrorInfo->setInterval(1000);
	connect(timerErrorInfo, SIGNAL(timeout()), this, SLOT(slots_clearErrorInfo()));  

	timerWarningInfo = new QTimer(this);
	timerWarningInfo->setInterval(1000);
	connect(timerWarningInfo, SIGNAL(timeout()), this, SLOT(slots_clearWarningInfo()));   
	m_LastNumber=0;
	m_vecSingleCameraPic.clear();
	imgNumber="";
	nMouldID=-1;
}

MyImageShowItem::~MyImageShowItem()
{

	contextMenu->clear(); //清除菜单
	delete contextMenu;
}
void MyImageShowItem::createActions()
{
	contextMenu = new QMenu();
	saveAction = new QAction(tr("Save image"),this);
	connect(saveAction,SIGNAL(triggered()),this,SLOT(slots_saveImage()));
	stopCheck =  new QAction(tr("Stop check"),this);
	connect(stopCheck,SIGNAL(triggered()),this,SLOT(slots_stopCheck()));
	//stopAllStressCheck =  new QAction(tr("Stop All Stress check"),this);
	//connect(stopAllStressCheck,SIGNAL(triggered()),this,SLOT(slots_stopAllStressCheck()));
	startCheck =  new QAction(tr("Start check"),this);
	connect(startCheck,SIGNAL(triggered()),this,SLOT(slots_startCheck()));
	//startAllStressCheck =  new QAction(tr("Start All Stress check"),this);
	//connect(startAllStressCheck,SIGNAL(triggered()),this,SLOT(slots_startAllStressCheck()));
//  	startShow = new QAction(tr("Start show"),this);
//  	connect(startShow,SIGNAL(triggered()),this,SLOT(slots_startShow()));

	startFreshAll = new QAction(tr("Start Refresh All Camera"),this);
	connect(startFreshAll,SIGNAL(triggered()),this,SLOT(slots_startShowAll()));

	showCheck = new QAction(tr("Set algorithm"),this);
	connect(showCheck,SIGNAL(triggered()),this,SLOT(slots_showCheck()));
}

void MyImageShowItem::inital(int nCamNo)
{
	iCameraNo = nCamNo;

	strCamera = "null";
	strImageSN = "null";
	strTime = "null";
	strResult = "null";
	update();


	btnPrevious->setPicName(QString(":/pushButton/previous")) ;
	btnFollowing->setPicName(QString(":/pushButton/following")) ;
	btnStartRefresh->setPicName(QString(":/pushButton/stopShow")) ;
	ShowErrorPicButtonLayout();
	AllPicButtonLayout();

}

void MyImageShowItem::enterEvent(QEvent *)
{
	btnPrevious->setVisible(true);
	btnFollowing->setVisible(true);
	//btnStartRefresh->setVisible(true);
	ShowAllPicButton(bIsMaxShow, true);
}
void MyImageShowItem::leaveEvent(QEvent *)
{
	btnPrevious->setVisible(false);
	btnFollowing->setVisible(false);
	btnStartRefresh->setVisible(false);
	ShowAllPicButton(true, false);
}

void MyImageShowItem::paintEvent(QPaintEvent *event)
{
	//添加边框
	if (!pMainFrm->m_sSystemInfo.m_iImageStretch && !bIsMaxShow)
	{
		QPainterPath path;
		path.setFillRule(Qt::WindingFill);
		path.addRect(1, 1, this->width()-2*1, this->height()-2*1);

		QPainter painterRect(this);
		painterRect.setRenderHint(QPainter::Antialiasing, true);//消除锯齿
		painterRect.fillPath(path, QBrush(Qt::white));

		QColor color(0, 0, 0);
		painterRect.setPen(color);
		painterRect.drawPath(path);
	}

	if (imageForWidget.isNull())
	{
		return;
	}
	int widgetWidth = geometry().width()-4;
	int widgetHeight = geometry().height()-4;
	int iShowWidth = widgetWidth;
	int iShowHeight = widgetHeight;
	int iShowX = 0;
	int iShowY = 0;
	QWidget::paintEvent(event);
	QPainter painter(this);
	painter.setPen(Qt::NoPen);
	painter.setBrush(Qt::red);
// 	painter.drawPixmap(QRect(0, 0, widgetWidth, widgetHeight),pixmapShown);
	if (bIsMaxShow)
	{
		int imgwidth = imageForWidget.width();
		int imgheight = imageForWidget.height();
		if (1.0*widgetWidth/widgetHeight > 1.0*imgwidth/imgheight)
		{
			iShowWidth = 1.0*imageForWidget.width()/imageForWidget.height()*widgetHeight;
			iShowHeight = widgetHeight;
			iShowX = (widgetWidth-iShowWidth)/2;
			iShowY = 0;
			painter.drawImage(QRect(iShowX, iShowY, iShowWidth, iShowHeight),imageForWidget);
		}
		else
		{
			iShowWidth = widgetWidth;
			iShowHeight = 1.0*imageForWidget.height()/imageForWidget.width()*widgetWidth;
			iShowX = 0;
			iShowY = (widgetHeight-iShowHeight)/2;
			painter.drawImage(QRect(iShowX, iShowY, iShowWidth, iShowHeight),imageForWidget);
		}
	}
	else
	{
		if (pMainFrm->m_sSystemInfo.m_iImageStretch)
		{
			iShowWidth = widgetWidth;
			iShowHeight = widgetHeight;
			iShowX = 0;
			iShowY = 0;

			painter.drawImage(QRect(iShowX, iShowY, iShowWidth, iShowHeight),imageForWidget);
		}
		else
		{
			int imgwidth = imageForWidget.width();
			int imgheight = imageForWidget.height();

			if (1.0*widgetWidth/widgetHeight > 1.0*imgwidth/imgheight)
			{
				iShowWidth = 1.0*imageForWidget.width()/imageForWidget.height()*widgetHeight;
				iShowHeight = widgetHeight;
				iShowX = (widgetWidth-iShowWidth)/2 + 2;
				iShowY = 0 + 2;
				painter.drawImage(QRect(iShowX, iShowY, iShowWidth, iShowHeight),imageForWidget);
			}
			else
			{
				iShowWidth = widgetWidth;
				iShowHeight = 1.0*imageForWidget.height()/imageForWidget.width()*widgetWidth;
				iShowX = 0 + 2;
				iShowY = (widgetHeight-iShowHeight)/2 + 2;
				painter.drawImage(QRect(iShowX, iShowY, iShowWidth, iShowHeight),imageForWidget);
			}
		}
	}
	
	QFont font("宋体",9,QFont::DemiBold,false);
	QPen pen(Qt::blue);
	pen.setWidth(2);
	painter.setFont(font);
	painter.setPen(pen);
	painter.setBrush(Qt::NoBrush);
//	painter.drawText(0, 20, tr("Camera:")+QString::number(iCameraNo));
	painter.drawText(0, 20, tr("Camera:")+strCamera);
	painter.drawText(0, 40, tr("ImageSN:")+strImageSN);
	painter.drawText(0, 60, tr("CostTime:")+strTime);
	if (listErrorRect.length()>0)
	{
		pen.setColor(Qt::red);
		painter.setPen(pen);
	}
	painter.drawText(0, 80, tr("Result:")+strResult);
	
	if (nMouldID.toInt() != -1 && nMouldID.toInt() != 0 )
	{
		painter.drawText(0, 100, QString::fromLocal8Bit("模号: ") + QString::number(nMouldID.toInt()));
	}
	

	//淡蓝画笔
	pen.setColor(Qt::magenta);
	pen.setWidth(3);
	painter.setPen(pen);
	painter.setBrush(Qt::NoBrush);

	//输出警报信息
	if (bIsHaveWarning)
	{
		painter.drawText(0,  geometry().height()/2, geometry().width(), geometry().height()/2, Qt::AlignCenter|Qt::TextWordWrap, strWarning);
	}

	//输出状态信息
	if (!bIsCheck)
	{
		painter.drawText(0, 0, geometry().width(), 20, Qt::AlignRight, tr("Check Stoped"));
	}
	if (!bIsUpdateImage)
	{
		painter.drawText(0, 20, geometry().width(), 20, Qt::AlignRight, tr("Refresh Stoped"));
	}
	//红色画笔
	QFont font2("Arial",16,QFont::Bold);
	pen.setColor(Qt::red);
	pen.setWidth(3);
	painter.setFont(font2);
	painter.setPen(pen);
	painter.setBrush(Qt::NoBrush);
	//画矩形框
	double scaleWidth = 1.0*iShowWidth/iImageWidth;
	double scaleHeight = 1.0*iShowHeight/iImageHeight;

	for (int i = 0; i<listErrorRect.length(); i++)
	{
		QRect rect = listErrorRect.at(i);
		painter.drawRect(rect.left() * scaleWidth+iShowX, rect.top() * scaleHeight+iShowY, rect.width() * scaleWidth, rect.height() * scaleHeight);
	}

	//输出错误信息
	if (bIsHaveError)
	{
		painter.drawText(0, 0, geometry().width(), geometry().height(), Qt::AlignCenter|Qt::TextWordWrap, strError);
	}
	//QPen pen(colorRect);
	//pen.setWidth(3);
	//painter.setPen(pen);
	//for (int i = 1; i<=10; i++)
	//{
	//	painter.setPen(QColor(colorRect.red(), colorRect.green(), colorRect.blue(), i*15));
	//	painter.drawRect(-i,-i,widgetWidth+1,widgetWidth+1);
	//}
}
void MyImageShowItem::slots_clearErrorInfo()
{
	bIsHaveError = false;
	timerErrorInfo->stop();
	update();
}
void MyImageShowItem::slots_clearWarningInfo()
{
	bIsHaveWarning = false;
	timerWarningInfo->stop();
	update();
}
void MyImageShowItem::mouseDoubleClickEvent(QMouseEvent *event)
{	
	emit signals_imageItemDoubleClick(iCameraNo);
	emit signals_startShow(iCameraNo);
	if (bIsMaxShow)
	{
		if (ShowAllPicButton(bIsMaxShow, true))
		{
			ConnectThreadAndShowItem();
			return;
		}
		ConnectThreadAndShowItem();
	}
	else
	{
		m_lockData.lock();
		m_PicDataTemp.clear();
		m_lockData.unlock();
		ShowAllPicButton(true, false);
		disconnect(pMainFrm->pdetthread[iCameraNo],
			SIGNAL(signals_updateMaxImageItem(QImage, QString, QString, QString, QString,QString, QList<QRect>, int, int)),
			this,
			SLOT(slots_updateMaxImageItem(QImage, QString, QString, QString, QString, QString,QList<QRect>,int,int)));
		SetButtonInitialStatus();
		pMainFrm->pThis=NULL;
	}
}
void MyImageShowItem::contextMenuEvent(QContextMenuEvent *event)
{
	contextMenu->clear(); //清除原有菜单
	QPoint point = event->pos(); //得到窗口坐标
	contextMenu->addAction(saveAction);
	if (bIsCheck)
	{
		if (pMainFrm->sPermission.iStartStop)
		{
			contextMenu->addAction(stopCheck);
		}
	}
	else
	{
		contextMenu->addAction(startCheck);
	}
	contextMenu->addAction(startFreshAll);
	if (pMainFrm->sPermission.iAlgSet)
	{
		contextMenu->addAction(showCheck);
	}

	//菜单出现的位置为当前鼠标的位置
	contextMenu->exec(QCursor::pos());
	event->accept();
}
void MyImageShowItem::updateImage(QImage* imageShown,QString camera, QString imageSN,QString time, QString result, QString nMouldTemp, QList<QRect> listRect)
{
	try
	{
		imageForWidget = (imageShown)->mirrored();
	}
	catch (...)
	{
		CLogFile::write(tr("----取出显示图像异常----"),AbnormityLog);
		return;
	}

	strCamera = camera;
	strImageSN = imageSN;
	strTime = time;
	strResult = result;
	nMouldID= nMouldTemp;

	listErrorRect = listRect;
	//qDebug()<<nMouldTemp;
	iImageWidth = imageForWidget.width();
	iImageHeight = imageForWidget.height();

	// 	update();
	repaint();

}
void MyImageShowItem::slots_updateImage(QImage* imageShown,QString camera, QString imageSN,QString time, QString result, QString nMouldID, QList<QRect> listRect,int QueenID)
{
	if(QString::number(iCameraNo+1) != camera)
	{
		return;
	}
	if (imageShown == NULL)
	{
		return;
	}
	if (pMainFrm->m_queue[iCameraNo].InitID!= QueenID)
	{
		return;
	}
	updateImage(imageShown,camera, imageSN,time, result, nMouldID,listRect);
}
void MyImageShowItem::slots_update()
{
	update();
}

void MyImageShowItem::slots_showErrorInfo(QString error, int time, bool bError)
{
	strError = error;
	bIsHaveError = bError;
	update();
	if (0 != time)
	{
		timerErrorInfo->setInterval(time*1000);
		timerErrorInfo->start();
	}
}
void MyImageShowItem::slots_showWarningInfo(QString error, int time, bool bError)
{
	strWarning = error;
	bIsHaveWarning = bError;
	update();
	if (0 != time)
	{
		timerWarningInfo->setInterval(time*1000);
		timerWarningInfo->start();
	}
}

void MyImageShowItem::slots_saveImage()
{
	QTime time = QTime::currentTime();
	QDate date = QDate::currentDate();
	QString strImgPath = tr("SaveImage/");
	strImgPath = strImgPath+tr("Camera%1/").arg(iCameraNo+1);
	//QString strFilePath = pMainFrm->m_sConfigInfo.m_strAppPath + strImgPath;
	
	QString fileName = QFileDialog::getSaveFileName(this, tr("Save Image"),\
		".\\SaveImage\\" + QString("%1-%2-%3-%4%5%6.bmp").arg(date.year()).arg(date.month()).arg(date.day()).arg(time.hour()).arg(time.minute()).arg(time.second()),\
		tr("Images (*.bmp *.png *.jpg)"));
//	QString fileName = ".\\SaveImage\\" + QString("%1-%2-%3-%4%5%6.bmp").arg(date.year()).arg(date.month()).arg(date.day()).arg(time.hour()).arg(time.minute()).arg(time.second());
	QDir *dir = new QDir;
	//QT 5.12.6 update
	/*QString strFilePath = fileName.left(fileName.findRev("\\")+1);*/
	QString strFilePath = fileName.left(fileName.lastIndexOf("\\") + 1);
	if(!dir->exists(strFilePath))
	{
		bool ok = dir->mkpath(strFilePath);
	}
	dir=NULL;
	//delete dir;
	if (!fileName.isEmpty())
	{
/*		QImage *imgSave = new QImage(pDlg->pBmpItem[nItemID]->pixmap().toImage().convertToFormat(QImage::Format_Indexed8));
		imgSave->setColorTable(pMainFrm->m_vcolorTable);
		imgSave->save(fileName);*/
//		pixmapShown.toImage().convertToFormat(QImage::Format_Indexed8, m_vcolorTable).save(fileName);
		imageForWidget.save(fileName);
	}

}
void MyImageShowItem::slots_showCheck()
{
	emit signals_showCheck(iCameraNo);
}
void MyImageShowItem::slots_stopCheck()
{
	bIsCheck = false;
	emit signals_stopCheck(iCameraNo );
	update();
}
void MyImageShowItem::slots_stopAllStressCheck()
{
//	bIsCheck = false;
	emit signals_stopAllStressCheck();
	update();
}
void MyImageShowItem::slots_startAllStressCheck()
{
//	bIsCheck = false;
	emit signals_stopAllStressCheck();
	update();
}
void MyImageShowItem::slots_startCheck()
{
	bIsCheck = true;
	emit signals_startCheck(iCameraNo );
	update();

}
void MyImageShowItem::slots_startShow()
{
	
	update();
	btnStartRefresh->setPicName(QString(":/pushButton/stopShow")) ;
	m_lockData.lock();
	bIsUpdateImage = true;
	m_PicDataTemp.clear();
	m_LastAllCameraPic.clear();
	m_vecSingleCameraPic.clear();
	m_lockData.unlock();
}
void MyImageShowItem::slots_stopShow()
{
	bIsUpdateImage = false;
	//emit signals_stopShow(iCameraNo );
	update();
	btnStartRefresh->setPicName(QString(":/pushButton/startShow")) ;
}
void MyImageShowItem::updataLastPic()
{
	std::list<std::vector<SingleCameraPic>>:: iterator iter = m_LastAllCameraPic.begin();
	int i=0;
	for(; iter != m_LastAllCameraPic.end(); iter++)
	{
		if(i==m_LastNumber)
		{
			m_PicDataTemp.clear();
			std::vector<SingleCameraPic>::iterator iters = (*iter).begin();
			int in=0;
			for(; iters != (*iter).end(); iters++)
			{
				m_PicDataTemp.push_back(*iters);
				if (iters->listRect.size() > 0)
				{
					m_vecCameraAllPic[in]->setStyleSheet("background-color: rgb(255, 0, 0);");
				}
				else
				{
					m_vecCameraAllPic[in]->setStyleSheet("background-color: rgb(0,200, 0);");
				}
				in++;
			}
		}
		i++;
	}
}
void MyImageShowItem::slots_showPrevious()
{
	emit signals_stopShow(iCameraNo);
	disconnect(pMainFrm->pdetthread[iCameraNo],SIGNAL(signals_updateImage(QImage*, QString , QString ,QString , QString, QString,QList<QRect>,int )),this,SLOT(slots_updateImage(QImage*, QString , QString ,QString , QString,QString, QList<QRect>,int )));
	disconnect(pMainFrm->pdetthread[iCameraNo],SIGNAL(signals_updateMaxImageItem(QImage, QString, QString, QString, QString, QString,QList<QRect>, int, int)),this,SLOT(slots_updateMaxImageItem(QImage, QString, QString, QString, QString,QString, QList<QRect>,int,int)));
	pMainFrm->widget_carveSetting->image_widget->bIsShow[iCameraNo] = false;

	m_lockData.lock();
	bIsUpdateImage=false;
	m_LastNumber++;
	if(m_LastNumber>=m_LastAllCameraPic.size())
	{
		if(m_LastNumber==1&&m_LastAllCameraPic.size()==1)
		{
			m_LastNumber=0;
			QString strError = QString("后面没有数据了!");
			slots_showWarningInfo(strError);
		}else{
			m_LastNumber=m_LastAllCameraPic.size()-1;
			m_lockData.unlock();
			QString strError = QString("后面没有数据了!");
			slots_showWarningInfo(strError);
			return;
		}
	}
	updataLastPic();
	pMainFrm->pThis=&m_PicDataTemp[0].imageShown;
	updateImage(&m_PicDataTemp[0].imageShown,m_PicDataTemp[0].GetCamera(),m_PicDataTemp[0].GetImageSN(),m_PicDataTemp[0].GetTime(),
		m_PicDataTemp[0].GetResult(),m_PicDataTemp[0].Mould,m_PicDataTemp[0].GetListRect());
	
	m_lockData.unlock();

}
void MyImageShowItem::slots_showFollowing()
{
	emit signals_stopShow(iCameraNo);
	disconnect(pMainFrm->pdetthread[iCameraNo],SIGNAL(signals_updateImage(QImage*, QString , QString ,QString , QString, QString,QList<QRect>,int )),this,SLOT(slots_updateImage(QImage*, QString , QString ,QString , QString,QString, QList<QRect>,int )));
	disconnect(pMainFrm->pdetthread[iCameraNo],SIGNAL(signals_updateMaxImageItem(QImage, QString, QString, QString, QString,QString, QList<QRect>, int, int)),this,SLOT(slots_updateMaxImageItem(QImage, QString, QString, QString, QString,QString, QList<QRect>,int,int)));
	pMainFrm->widget_carveSetting->image_widget->bIsShow[iCameraNo] = false;
	m_lockData.lock();
	bIsUpdateImage=false;
	m_LastNumber--;
	if(m_LastNumber<0)
	{
		m_LastNumber=0;
		m_lockData.unlock();
		QString strError = QString("前面没有数据了!");
		slots_showWarningInfo(strError);
		return;
	}
	updataLastPic();

	pMainFrm->pThis=&m_PicDataTemp[0].imageShown;
	updateImage(&m_PicDataTemp[0].imageShown,m_PicDataTemp[0].GetCamera(),m_PicDataTemp[0].GetImageSN(),m_PicDataTemp[0].GetTime(),
		m_PicDataTemp[0].GetResult(),m_PicDataTemp[0].Mould,m_PicDataTemp[0].GetListRect());

	m_lockData.unlock();
}
void MyImageShowItem::slots_showStartRefresh()
{
	if (bIsUpdateImage == false)
	{
		pMainFrm->widget_carveSetting->image_widget->slots_startShow(iCameraNo);
		slots_startShow();	
		emit signals_showStartRefresh(iCameraNo);
		ConnectThreadAndShowItem();
	}
	else
	{
		pMainFrm->widget_carveSetting->image_widget->slots_stopShow(iCameraNo);
		slots_stopShow();
		disconnect(pMainFrm->pdetthread[iCameraNo],SIGNAL(signals_updateMaxImageItem(QImage, QString, QString, QString, QString, QList<QRect>, int, int)),this,SLOT(slots_updateMaxImageItem(QImage, QString, QString, QString, QString, QList<QRect>,int,int)));
	}
}
void MyImageShowItem::slots_startShowAll()
{
	emit signals_startShowAll();
	if (bIsMaxShow)
	{
		ConnectThreadAndShowItem();
	}
	singleCameraCount = 0;
	for (int i=0;i<CAMERA_MAX_COUNT;i++)
	{
		pMainFrm->m_SavePicture[i].pThat=NULL;
	}
}
void MyImageShowItem::setMaxShow(bool bSatus)
{
	bIsMaxShow = bSatus;
}

void MyImageShowItem::ShowErrorPicButtonLayout()
{
	layoutButton = new QHBoxLayout;
	layoutButton->addWidget(btnPrevious,0,Qt::AlignBottom);
	layoutButton->addWidget(btnFollowing,0,Qt::AlignBottom);
	layoutButton->addWidget(btnStartRefresh,0,Qt::AlignBottom);
	mainLayout = new QVBoxLayout(this);
	mainLayout->addStretch();
	mainLayout->addLayout(layoutButton);
	setLayout(mainLayout);
}

bool MyImageShowItem::ShowAllPicButton(bool isMaxShow, bool isShow)
{
	if (isMaxShow)
	{
		if (m_vecCameraAllPic.size() > 0)
		{
			std::vector<QPushButton*>::iterator iter = m_vecCameraAllPic.begin();
			for(; iter != m_vecCameraAllPic.end(); iter++)
			{

				if (*iter)
				{
					(*iter)->setVisible(isShow);
				}
			}
			return true;
		}
	}
	return false;
}

void MyImageShowItem::AllPicButtonLayout()
{
	PicButtonLayout = new QGridLayout;
	PicButtonLayout->addWidget(btnPrevious,0,0);
	PicButtonLayout->addWidget(btnFollowing,0,1);
	PicButtonLayout->addWidget(btnStartRefresh,0,2);
	if (pMainFrm->m_sRealCamInfo[iCameraNo].m_iImageTargetNo < 20)
	{
		//添加空白按钮区域，使界面布局显示对齐
		/*for (int i = 3; i < pMainFrm->m_sRealCamInfo[iCameraNo].m_iImageTargetNo; i++)
		{
			PicButtonLayout->addWidget(btnStartRefresh,0,i);
		}*/
		for (int i = 0; i < pMainFrm->m_sRealCamInfo[iCameraNo].m_iImageTargetNo; i++)
		{
			m_vecCameraAllPic.push_back(new QPushButton(QString::number(i+1),this));
			m_vecCameraAllPic[i]->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
			PicButtonLayout->addWidget(m_vecCameraAllPic[i],1,i);
			m_vecCameraAllPic[i]->setVisible(false);
			connect(m_vecCameraAllPic[i], SIGNAL(clicked()), this, SLOT(slots_showButtonToPic()));
		}
	}
	else
	{
		int maxPushbutton=0;
		for (int i = 0; i <= pMainFrm->m_sRealCamInfo[iCameraNo].m_iImageTargetNo/20; i++)
		{
			for (int j = 0; j < 20; j++)
			{
				if(maxPushbutton==pMainFrm->m_sRealCamInfo[iCameraNo].m_iImageTargetNo)
				{
					break;
				}
				m_vecCameraAllPic.push_back(new QPushButton(QString::number(i * 20 + j+1),this));
				PicButtonLayout->addWidget(m_vecCameraAllPic[i * 20 + j], i + 1, j);
				maxPushbutton++;
				m_vecCameraAllPic[i * 20 + j]->setVisible(false);
				connect(m_vecCameraAllPic[i * 20 + j], SIGNAL(clicked()), this, SLOT(slots_showButtonToPic()));
			}
		}
	}
	PicButtonLayout->setSpacing(0);
	mainLayout->addLayout(layoutButton);
	mainLayout->addLayout(PicButtonLayout);
	setLayout(mainLayout);
}

void MyImageShowItem::slots_updateMaxImageItem(QImage imageShown,QString camera, QString imageSN,QString time,
											   QString result, QString nMouldID, QList<QRect> listRect,int QueenID, int grabImageCount)
{	
	m_lockData.lock();
	SingleCameraPic cameraPic(imageShown, camera, imageSN, time, result,nMouldID, listRect, QueenID, grabImageCount);

	if (imgNumber == imageSN)
	{
		m_vecSingleCameraPic.push_back(cameraPic);
		if(m_vecSingleCameraPic.size() == pMainFrm->m_sRealCamInfo[iCameraNo].m_iImageTargetNo)
		{
			updatapic();//获取本次所有数据
			m_vecSingleCameraPic.clear();
			if(pMainFrm->number_camera!=-1)
			{
				SetButtonInitialStatus();
				singleCameraCount = 0;
			}
		}
	}else{
		m_vecSingleCameraPic.clear();
		imgNumber = imageSN;
		m_vecSingleCameraPic.push_back(cameraPic);
		singleCameraCount = 0;
		SetButtonInitialStatus();
	}
	m_tempImage=imageShown;
	pMainFrm->pThis=&m_tempImage;
	if (m_vecCameraAllPic.size() > singleCameraCount)
	{
		if (listRect.length() > 0)
		{
			/*if(iCameraNo==0)
			{
			QString temps=QString("D:\\temp\\")+imageSN+"_"+QString::number(grabImageCount)+".bmp";
			imageShown->save(temps);
			}*/
			m_vecCameraAllPic[singleCameraCount]->setStyleSheet("background-color: rgb(255, 0, 0);");
		}
		else
		{
			
			m_vecCameraAllPic[singleCameraCount]->setStyleSheet("background-color: rgb(0,200, 0);");
		}
	}
	singleCameraCount++;

	m_lockData.unlock();
}

void MyImageShowItem::ConnectThreadAndShowItem()
{
	SetButtonInitialStatus();
	m_lockData.lock();
	m_vecSingleCameraPic.clear();
	m_lockData.unlock();
	connect(pMainFrm->pdetthread[iCameraNo],
		SIGNAL(signals_updateMaxImageItem(QImage, QString, QString, QString, QString,QString, QList<QRect>, int, int)),
		this,
		SLOT(slots_updateMaxImageItem(QImage, QString, QString, QString, QString,QString, QList<QRect>,int,int)),Qt::UniqueConnection);
}

void MyImageShowItem::SetButtonInitialStatus()
{
	if (m_vecCameraAllPic.size() > 0)
	{
		std::vector<QPushButton*>::iterator iter = m_vecCameraAllPic.begin();
		for(; iter != m_vecCameraAllPic.end(); iter++)
		{

			if (*iter)
			{
				(*iter)->setStyleSheet("background-color: rgb(0xf0f0, 0xf0f0, 0xf0f0);");
			}
		}
	}
}

void MyImageShowItem::slots_showButtonToPic()
{
	emit signals_stopShow(iCameraNo);
	disconnect(pMainFrm->pdetthread[iCameraNo],SIGNAL(signals_updateImage(QImage*, QString , QString ,QString , QString, QString,QList<QRect>,int )),this,SLOT(slots_updateImage(QImage*, QString , QString ,QString , QString, QString,QList<QRect>,int )));
	disconnect(pMainFrm->pdetthread[iCameraNo],SIGNAL(signals_updateMaxImageItem(QImage, QString, QString, QString, QString,QString, QList<QRect>, int, int)),this,SLOT(slots_updateMaxImageItem(QImage, QString, QString, QString, QString,QString, QList<QRect>,int,int)));
	pMainFrm->widget_carveSetting->image_widget->bIsShow[iCameraNo] = false;
	QPushButton* sendButton = (QPushButton*)sender(); 
	int index = sendButton->text().toInt()-1;
	bIsUpdateImage=false;

	if (m_PicDataTemp.size() > index)
	{
		pMainFrm->pThis=&m_PicDataTemp[index].imageShown;
		pMainFrm->pThat=NULL;
		updateImage(&m_PicDataTemp[index].imageShown,m_PicDataTemp[index].GetCamera(),m_PicDataTemp[index].GetImageSN(),m_PicDataTemp[index].GetTime(),
		m_PicDataTemp[index].GetResult(),m_PicDataTemp[index].GetMould(),m_PicDataTemp[index].GetListRect());
	}else{
		pMainFrm->pThis=NULL;
	}
	std::vector<SingleCameraPic>::iterator iter = m_PicDataTemp.begin();
	int i=0;
	for(; iter != m_PicDataTemp.end(); iter++)
	{
		if (iter->listRect.size() > 0)
		{
			m_vecCameraAllPic[i]->setStyleSheet("background-color: rgb(255, 0, 0);");
		}
		else
		{
			m_vecCameraAllPic[i]->setStyleSheet("background-color: rgb(0,200, 0);");
		}
		i++;
	}
}

void MyImageShowItem::updatapic()
{
	if(bIsMaxShow&&bIsUpdateImage)
	{
		if(m_vecSingleCameraPic.size()!=pMainFrm->m_sRealCamInfo[iCameraNo].m_iImageTargetNo)
		{
			return;
		}
		bool ifsave=false;
		m_PicDataTemp.clear();
		std::vector<SingleCameraPic>::iterator iter = m_vecSingleCameraPic.begin();
		int i=0;
		for(; iter != m_vecSingleCameraPic.end(); iter++)
		{
			m_PicDataTemp.push_back(*iter);

			if (iter->listRect.size() > 0)
			{
				ifsave=true;
				m_vecCameraAllPic[i]->setStyleSheet("background-color: rgb(255, 0, 0);");
			}
			else
			{
				m_vecCameraAllPic[i]->setStyleSheet("background-color: rgb(0,200, 0);");
			}
			i++;
		}
		if(m_LastAllCameraPic.size()>pMainFrm->m_savecameranumber)
		{
			m_LastAllCameraPic.pop_back();
		}
		if(pMainFrm->number_camera!=-1)//调试模式
		{
			m_LastAllCameraPic.push_front(m_PicDataTemp);
		}else{ //开始检测模式
			if(ifsave)
			{
				m_LastAllCameraPic.push_front(m_PicDataTemp);
			}
		}
		/*if(m_LastAllCameraPic.size()>10)
		{
		m_LastAllCameraPic.pop_back();
		}
		m_LastAllCameraPic.push_front(m_PicDataTemp);*/
	}
}