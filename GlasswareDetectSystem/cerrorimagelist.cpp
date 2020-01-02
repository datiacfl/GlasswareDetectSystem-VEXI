#include "cerrorimagelist.h"

#include <QHeaderView>
#include <QLayout>

#include "glasswaredetectsystem.h"
extern GlasswareDetectSystem *pMainFrm;
CErrorImageList::CErrorImageList(QWidget *parent)
	: DHBaseWidget(parent)
{
// 	pView = new QGraphicsView(this);
// 	setMaximumWidth(300);
// 	setMinimumWidth(300);
	imageError = NULL;
	setWidgetName(tr("Error list"));
	m_ListErrorWidget = new myTableView(this);
	m_ListErrorWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);	//禁止编辑
	m_ListErrorWidget->setSelectionBehavior(QAbstractItemView::SelectRows); //整行选中
	m_ListErrorWidget->setSelectionMode(QAbstractItemView::SingleSelection); //单个选中目标
	m_ListErrorWidget->verticalHeader()->setVisible(false);					//隐藏行头
	m_ListErrorWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	btnClear = new QPushButton(this);
	btnClear->setText(tr("Clear"));

	buttonCarve = new QPushButton;
	buttonCarve->setVisible(false);
	QPixmap iconCarve(":/sysButton/carve");
	buttonCarve->setIcon(iconCarve);
	buttonCarve->setFixedSize(iconCarve.size());

	labelTotal = new QLabel(this);
	labelFailur = new QLabel(this);
	labelFailurRate = new QLabel(this);
	labelTotal->setAlignment(Qt::AlignCenter);
	labelFailur->setAlignment(Qt::AlignCenter);
	labelFailurRate->setAlignment(Qt::AlignCenter);
	QFont fontLable("宋体",9,QFont::DemiBold,false);
	//fontLable.setPixelSize(15);
	labelTotal->setFont(fontLable);
	labelFailur->setFont(fontLable);
	labelFailurRate->setFont(fontLable);

	QHBoxLayout *hLayoutName = new QHBoxLayout;
	hLayoutName->addWidget(widgetName);
	hLayoutName->addStretch();
	hLayoutName->addWidget(buttonCarve);

	QHBoxLayout *hLayoutCount = new QHBoxLayout();
	QFrame *frame = new QFrame(this);
	frame->setFrameShape(QFrame::VLine);
	QFrame *frame2 = new QFrame(this);
	frame2->setFrameShape(QFrame::VLine);
	hLayoutCount->addWidget(labelTotal);
	hLayoutCount->addWidget(frame);
	hLayoutCount->addWidget(labelFailur);
	hLayoutCount->addWidget(frame2);
	hLayoutCount->addWidget(labelFailurRate);


	QVBoxLayout *vLayoutListError = new QVBoxLayout(this);
	vLayoutListError->addLayout(hLayoutName);
	vLayoutListError->addLayout(hLayoutCount);
	vLayoutListError->addWidget(m_ListErrorWidget);
	vLayoutListError->addWidget(btnClear);
	vLayoutListError->setSpacing(6);
	vLayoutListError->setContentsMargins(5, 0, 5, 5);

	connect(m_ListErrorWidget, SIGNAL(clicked(QModelIndex)), this, SLOT(slots_ShowSelectImage(QModelIndex)));
//	connect(m_ListErrorWidget, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(slots_ShowCheckModle(QModelIndex)));
	connect(btnClear, SIGNAL(clicked()), this, SLOT(slots_clearTable()));


 	for (int i = 0;i<pMainFrm->m_sSystemInfo.iCamCount;i++)
	{
		connect(pMainFrm->pdetthread[i], SIGNAL(signals_AddErrorTableView(int,int,QString)), this, SLOT(slots_appendFirstRow(int,int,QString)));
	}
	timer_updateInfo = new QTimer(this);
	timer_updateInfo->setInterval(1000);
	connect(timer_updateInfo, SIGNAL(timeout()), this, SLOT(slots_updateInfo()));   
	timer_updateInfo->start();  

	initail();
}

CErrorImageList::~CErrorImageList()
{
	for (int i = 0; i<m_modelError->rowCount();i++)
	{
		QList<QStandardItem*>  item = m_modelError->takeRow(i);
		if (!item.isEmpty())
		{
			qDeleteAll(item);
			item.clear();
		}
	}	
	if (NULL != m_modelError)
	{
		delete m_modelError;
		m_modelError = NULL;
	}
	if (CherkerAry.pCheckerlist != NULL)
	{
		delete[] CherkerAry.pCheckerlist;
	}

}

void CErrorImageList::initail()
{
	//绑定数据model
	m_modelError = new QStandardItemModel();
	//插入列表头
	QStringList headerList;  
	headerList << QObject::tr("Time") << QObject::tr("CameraNo") << QObject::tr("ErrorType") << QObject::tr("ImageCount");  
	m_modelError->setHorizontalHeaderLabels(headerList);
	//利用setModel()方法将数据模型与QTableView绑定--为避免不在该界面时的刷新，取消开始的绑定
	m_ListErrorWidget->setModel(m_modelError);
	//设置列宽
	m_ListErrorWidget->setColumnWidth(0, 60); 
	m_ListErrorWidget->setColumnWidth(1, 100); 
	m_ListErrorWidget->setColumnWidth(2, 150); 
	m_ListErrorWidget->setColumnWidth(3, 80); 

	CherkerAry.iValidNum = pMainFrm->m_sSystemInfo.iCamCount;
	CherkerAry.pCheckerlist = new s_CheckerList[CherkerAry.iValidNum];

}

bool CErrorImageList::IntoWidget()
{
	connect(this,SIGNAL(signals_showErrorImage(QImage*, int, int, double, QString, int,QList<QRect>, int )), \
		pMainFrm->widget_carveSetting->image_widget, SLOT(slots_showErrorImage(QImage*, int, int, double, QString,int, QList<QRect>, int)));

	//进入后再关联model,离开后取消绑定，防止界面刷新,占用主线程资源
	m_ListErrorWidget->setModel(m_modelError);
	//设置列宽
	m_ListErrorWidget->setColumnWidth(0, 50); 
	m_ListErrorWidget->setColumnWidth(1, 80); 
	m_ListErrorWidget->setColumnWidth(2, 100); 
	m_ListErrorWidget->setColumnWidth(3, 80); 
	return true;
}
bool CErrorImageList::leaveWidget()
{
	disconnect(this,SIGNAL(signals_showErrorImage(QImage*, int, int, double, QString, int,QList<QRect>, int)), \
		pMainFrm->widget_carveSetting->image_widget, SLOT(slots_showErrorImage(QImage*, int, int, double, QString,int, QList<QRect>, int)));

	//进入后再关联model,离开后取消绑定，防止界面刷新,占用主线程资源
 	m_ListErrorWidget->setModel(NULL);
 	return true;
}

void CErrorImageList::slots_clearTable()
{
	//m_ListErrorWidget->setModel(NULL);
	////m_modelError->clear ();
	//m_modelError->removeRow(0);//,m_modelError->rowCount());
	//m_ListErrorWidget->setModel(m_modelError);

	while(m_modelError->rowCount()>0 )
	{
		QList<QStandardItem*> listItem = m_modelError->takeRow(0);
		qDeleteAll(listItem);
		listItem.clear();
		//delete listItem;
	}
}
void CErrorImageList::slots_appendFirstRow(int iCamNo,int iImageCount,QString iErrorType)
{
	QTime time = QTime::currentTime();
	QStandardItem *item1 = new QStandardItem(QObject::tr("%1:%2:%3").arg(time.hour()).arg(time.minute()).arg(time.second()));
	QStandardItem *item2 = new QStandardItem(QObject::tr("%1").arg(iCamNo+1));
	QStandardItem *item3 = new QStandardItem(iErrorType);
	QStandardItem *item4 = new QStandardItem(QObject::tr("%1").arg(iImageCount));
	//	QStandardItem *item4 = new QStandardItem(QObject::tr("%1").arg(iErrorType));

	QList<QStandardItem*> item;
	item<<item1<<item2<<item3<<item4;
	m_modelError->insertRow(0,item);

	if (ERROR_IMAGE_COUNT < m_modelError->rowCount())
	{
		slots_RemoveLastRow();
	}
//	m_ListErrorWidget->selectRow(-1);
	m_ListErrorWidget->showRow(0);

}
void CErrorImageList::slots_RemoveLastRow()
{
	//	QStandardItem  *item = m_modelError->data()
	if (true)
	{
		m_ListErrorWidget->clearSelection();
	}
	QList<QStandardItem*>  item = m_modelError->takeRow(m_modelError->rowCount()-1);
	if (!item.isEmpty())
	{
		qDeleteAll(item);
		item.clear();
	}

}

void CErrorImageList::slots_ShowSelectImage(QModelIndex modelIndex)
{
	int iListNo = modelIndex.row();
	CGrabElement *pElement;
	pMainFrm->m_ErrorList.m_mutexmErrorList.lock();
	if (pMainFrm->m_ErrorList.listError.count()>iListNo)
	{
		pElement = pMainFrm->m_ErrorList.listError.at(iListNo);
		//pMainFrm->m_ErrorList.listError
	}
	else
	{
		pMainFrm->m_ErrorList.m_mutexmErrorList.unlock();
		return;
	}
 	if (imageError != NULL)
 	{
 		delete imageError;
 		imageError = NULL;
 	}
 	imageError = new QImage(*pElement->myImage); 


	int nCamNo = pElement->nCamSN; 
	pMainFrm->m_SavePicture[nCamNo].pThat=imageError;
	pMainFrm->m_SavePicture[nCamNo].m_Picture =imageError->copy();
	
	pMainFrm->widget_carveSetting->image_widget->sAlgImageLocInfo[nCamNo].sLocOri = pElement->sImgLocInfo.sLocOri;
	pMainFrm->widget_carveSetting->image_widget->sAlgImageLocInfo[nCamNo].sXldPoint.nCount = pElement->sImgLocInfo.sXldPoint.nCount;
	memcpy(pMainFrm->widget_carveSetting->image_widget->sAlgImageLocInfo[nCamNo].sXldPoint.nColsAry,pElement->sImgLocInfo.sXldPoint.nColsAry,4*BOTTLEXLD_POINTNUM);
	memcpy(pMainFrm->widget_carveSetting->image_widget->sAlgImageLocInfo[nCamNo].sXldPoint.nRowsAry,pElement->sImgLocInfo.sXldPoint.nRowsAry,4*BOTTLEXLD_POINTNUM);

	QString result;
	QStandardItem* aItem;
	for (int i=0;i<m_modelError->rowCount();i++)
	{
		if(i==iListNo)
		{
			aItem=m_modelError->item(i,2);
			result=aItem->text();
			break;
		}
	}
	emit signals_showErrorImage(imageError, nCamNo, pElement->nSignalNo, pElement->dCostTime,result,pElement->nMouldID, pElement->cErrorRectList, iListNo);
	pMainFrm->m_ErrorList.m_mutexmErrorList.unlock();
	disconnect(pMainFrm->pdetthread[nCamNo],
		SIGNAL(signals_updateMaxImageItem(QImage, QString, QString, QString, QString, QList<QRect>, int, int)),
		pMainFrm->widget_carveSetting->image_widget->listImageShowItem.at(nCamNo),
		SLOT(slots_updateMaxImageItem(QImage, QString, QString, QString, QString, QList<QRect>,int,int)));
}

void CErrorImageList::slots_updateInfo()
{
	double total = pMainFrm->m_sRunningInfo.m_checkedNum;
	double failur = pMainFrm->m_sRunningInfo.m_failureNumFromIOcard;
	double failurRate;
	if (0 == total)
	{
		failurRate = 0;
	}
	else
	{
		failurRate = (failur/total)*100;
	}
	labelTotal->setText(tr("Product Number:")+"\n"+QString::number(total));
	labelFailur->setText(tr("Reject Number:")+"\n"+QString::number(failur));
	labelFailurRate->setText(tr("Reject Rate:")+"\n"+QString::number(failurRate,'f',2)+"%");
}
