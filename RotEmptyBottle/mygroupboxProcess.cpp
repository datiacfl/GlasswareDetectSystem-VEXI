#include "mygroupboxprocess.h"
#include "DlgMainWindow.h"
#include <QHBoxLayout>
#include <QContextMenuEvent>
#include <QMouseEvent>
#include <QMessageBox>
#include <QInputDialog>
#include "CItemDlg.h"
#include "DlgSidewallLocate.h"
#include "DlgFinishLocate.h"
#include "DlgBaseLocate.h"
#include "DlgHoriSize.h"
#include "DlgVertSize.h"
#include "DlgBentNeck.h"
#include "DlgVertAng.h"
#include "DlgSGenReg.h"
#include "DlgDisturbReg.h"
#include "DlgSSideFReg.h"
#include "DlgSInFReg.h"
#include "DlgSScrewFReg.h"
#include "DlgFRLInReg.h"
#include "DlgFRLMidReg.h"
#include "DlgFRLOutReg.h"
#include "DlgFBLInReg.h"
#include "DlgFBLMidReg.h"
#include "DlgBInReg.h"
#include "DlgBMidReg.h"
#include "DlgBOutReg.h"
#include "DlgSSideReg.h"
#include "DlgFinCont.h"
#include "DlgNeckCont.h"
#include "DlgBodyCont.h"
#include "DlgSBriSpotReg.h"
#include "DlgBAllReg.h"
#include "DlgCircleSize.h"
#include "DlgSBaseReg.h"
#include "DlgSBaseConvexReg.h"
#include "DlgFullHeight.h"
#include "QTextStream"
MyGroupBoxProcess::MyGroupBoxProcess(QWidget *parent)
	: QGroupBox(parent)
{		
	//生成上下文菜单动作
	createActions();
	//改变标识符
	bAllItemsChange = false;
	//检测条目选中标识
	bItemClicked = false;
	nOnMouseItem = -1;
	nRightMouseItem = -1;
	tempID = -1;

	//显示类型0:横向显示 1:纵向显示
#ifdef DAHENGBLPKP_QT
	iShowType = 1;
#else
	iShowType = 0;
#endif
}

MyGroupBoxProcess::~MyGroupBoxProcess()
{
	int i;
	for (i=0;i<vItemLabels.size();++i)
		delete vItemLabels[i];
	vItemLabels.clear();

	//if (tempItemLabel != NULL)
	//{
	//	delete tempItemLabel;
        //tempItemLabel = NULL;
	//}
	
}
void MyGroupBoxProcess::initItems(bool bRefresh /*= true*/)
{
	int i;
	bItemClicked = false;
	nOnMouseItem = -1;
	nRightMouseItem = -1;
	//传递检测指针//注意：MyGroupBoxProcess的父窗口是centralwidget，centralwidget的父窗口才是CDlgMainWindow!
	//关闭对话框
	CItemDlg* pDlg = ((CItemDlg*)((CDlgMainWindow *)(parentWidget()->parentWidget()))->pItemDlg);
	if (NULL != pDlg)
	{
		delete pDlg;
	}
	//清空
	pChecker =((CDlgMainWindow *)(parentWidget()->parentWidget()))->pChecker;
	for (i=0;i<vItemLabels.size();++i)
		delete vItemLabels[i];
	vItemLabels.clear();
	//增加
	QVariant *pPara = NULL;
	MyLabelItem *labelItem = NULL;
	QString strName;
	int nID;
	bool bItemEnabled = true;
	for (i=0;i<pChecker->vItemFlow.size();++i)
	{
		pPara = &pChecker->vModelParas[i];
		nID = pChecker->vItemFlow[i];
		readSaveNames(nID, pPara, strName);
		labelItem = new MyLabelItem(this,nID,strName,pPara,&pChecker->vModelShapes[i]);
		readSaveStatus(nID, pPara, bItemEnabled);
		labelItem->bEnabled = bItemEnabled;
		labelItem->setColStyle();
		vItemLabels.push_back(labelItem);		
	}
	//显示所有检测项
	showItems();	
	//显示形状
	if (bRefresh)
	{
		((CDlgMainWindow *)(parentWidget()->parentWidget()))->displayObject();
	}
}
void MyGroupBoxProcess::createActions()
{
	addAction = new QAction(tr("Add"),this);
	addAction->setIcon(QIcon(":/Resources/images/processContext/addCheckItem.png"));
	addAction->setStatusTip(tr("Add a DetectionItem"));
	connect(addAction,SIGNAL(triggered()),this,SLOT(addItem()));

	insertAction = new QAction(tr("Insert"),this);
	insertAction->setIcon(QIcon(":/Resources/images/processContext/insertCheckItem.png"));
	insertAction->setStatusTip(tr("Insert a DetectionItem"));
	connect(insertAction,SIGNAL(triggered()),this,SLOT(insertItem()));

	renameAction = new QAction(tr("Renamed"),this);
	renameAction->setIcon(QIcon(":/Resources/images/processContext/configCheckItem.png"));
	renameAction->setStatusTip(tr("Change the name of DetectionItem"));
	connect(renameAction,SIGNAL(triggered()),this,SLOT(renameItem()));

	deleteAction = new QAction(tr("Delete"),this);
	deleteAction->setIcon(QIcon(":/Resources/images/processContext/deleteCheckItem.png"));
	deleteAction->setStatusTip(tr("Delete a DetectionItem"));
	connect(deleteAction,SIGNAL(triggered()),this,SLOT(deleteItem()));

	copyitemAction = new QAction(tr("Copy"),this);
	copyitemAction->setIcon(QIcon(":/Resources/images/processContext/copyCheckItem.png"));
	copyitemAction->setStatusTip(tr("Copy a DetectionItem"));
	connect(copyitemAction,SIGNAL(triggered()),this,SLOT(copyItem()));

	pasteitemAction = new QAction(tr("Paste"),this);
	pasteitemAction->setIcon(QIcon(":/Resources/images/processContext/pasteCheckItem.png"));
	pasteitemAction->setStatusTip(tr("Paste a DetectionItem"));
	connect(pasteitemAction,SIGNAL(triggered()),this,SLOT(pasteItem()));
}

void MyGroupBoxProcess::contextMenuEvent(QContextMenuEvent *event)
{
	int i;
	QRect eachRect;
	//增加右键菜单项
	contextMenu = new QMenu;
	contextMenu->addAction(addAction);
	contextMenu->addAction(insertAction);
	contextMenu->addAction(renameAction);
	contextMenu->addAction(deleteAction);
	contextMenu->addAction(copyitemAction);
	contextMenu->addAction(pasteitemAction);

	//根据鼠标位置判断动作是否禁用	
	QPoint ptMouse = mapFromGlobal(QCursor::pos());	
	if (vItemLabels.size()==0)
	{
		addAction->setEnabled(true);
		insertAction->setEnabled(false);
		renameAction->setEnabled(false);
		deleteAction->setEnabled(false);
		copyitemAction->setEnabled(false);
		pasteitemAction->setEnabled(false);
		contextMenu->exec(QCursor::pos());
		return;
	}
	switch(iShowType)
	{
	case 0:
		{
			//1. 增加
			QRect lastItem = QRect(vItemLabels[vItemLabels.size()-1]->pos(),
				vItemLabels[vItemLabels.size()-1]->size());

			if (lastItem.right()<ptMouse.x())
			{
				addAction->setEnabled(true);
			}
			else
			{
				addAction->setEnabled(false);
			}
			//2. 插入
			insertAction->setEnabled(false);
			for (i=0;i<vItemLabels.size();++i)
			{
				eachRect = QRect(vItemLabels[i]->pos(),vItemLabels[i]->size());
				if (eachRect.left()>ptMouse.x())
				{
					insertAction->setEnabled(true);
					nRightMouseItem = i;
					break;
				}
			}
			//3. 粘贴(检测项最后粘贴 && 检测项之间粘贴)
			pasteitemAction->setEnabled(false);
			if (lastItem.right()<ptMouse.x())
			{
				pasteitemAction->setEnabled(true);
			}
			else
			{
				for (i=0;i<vItemLabels.size();++i)
				{
					eachRect = QRect(vItemLabels[i]->pos(),vItemLabels[i]->size());
					if (eachRect.left()>ptMouse.x())
					{
						pasteitemAction->setEnabled(true);
						nRightMouseItem = i;
						break;
					}
				}
			}
			//4. 重命名、删除、复制
			renameAction->setEnabled(false);
			deleteAction->setEnabled(false);
			copyitemAction->setEnabled(false);
			for (i=0;i<vItemLabels.size();++i)
			{
				eachRect = QRect(vItemLabels[i]->pos(),vItemLabels[i]->size());
				if (eachRect.contains(ptMouse))
				{
					renameAction->setEnabled(true);
					deleteAction->setEnabled(true);
					copyitemAction->setEnabled(true);
					insertAction->setEnabled(false);
					pasteitemAction->setEnabled(false);
					nOnMouseItem = i;
					break;
				}
			}
		}
		break;
	case 1:
		{
			//1. 增加
			QRect lastItem = QRect(vItemLabels[vItemLabels.size()-1]->pos(),
				vItemLabels[vItemLabels.size()-1]->size());

			if (lastItem.bottom()<ptMouse.y())
			{
				addAction->setEnabled(true);
			}
			else
			{
				addAction->setEnabled(false);
			}
			//2. 插入
			insertAction->setEnabled(false);
			for (i=0;i<vItemLabels.size();++i)
			{
				eachRect = QRect(vItemLabels[i]->pos(),vItemLabels[i]->size());
				if (eachRect.top()>ptMouse.y())
				{
					insertAction->setEnabled(true);
					nRightMouseItem = i;
					break;
				}
			}
			//3. 粘贴(检测项最后粘贴 && 检测项之间粘贴)
			pasteitemAction->setEnabled(false);
			if (lastItem.bottom()<ptMouse.y())
			{
				pasteitemAction->setEnabled(true);
			}
			else
			{
				for (i=0;i<vItemLabels.size();++i)
				{
					eachRect = QRect(vItemLabels[i]->pos(),vItemLabels[i]->size());
					if (eachRect.top()>ptMouse.y())
					{
						pasteitemAction->setEnabled(true);
						nRightMouseItem = i;
						break;
					}
				}
			}
			//4. 重命名/删除/复制
			renameAction->setEnabled(false);
			deleteAction->setEnabled(false);
			copyitemAction->setEnabled(false);
			for (i=0;i<vItemLabels.size();++i)
			{
				eachRect = QRect(vItemLabels[i]->pos(),vItemLabels[i]->size());
				if (eachRect.contains(ptMouse))
				{
					renameAction->setEnabled(true);
					deleteAction->setEnabled(true);	
					copyitemAction->setEnabled(true);
					insertAction->setEnabled(false);
					pasteitemAction->setEnabled(false);
					nOnMouseItem = i;
					break;
				}
			}

		}
		break;
	default:
		break;
	}
	//执行
	contextMenu->exec(QCursor::pos());
	//右键菜单关闭后，设置回初始的样式表，否则会不变色
	for (i=0;i<vItemLabels.size();++i)
			vItemLabels[i]->setColStyle();
}

void MyGroupBoxProcess::mousePressEvent(QMouseEvent *event)
{
	if (event->button()!=Qt::LeftButton)
		return;	
	//根据鼠标位置判断算法模块是否选中
	int i;
	QRect eachRect;
	bool bItemEnabled = true;
	QPoint ptMouse = mapFromGlobal(QCursor::pos());
	CDlgMainWindow *pMainWnd = NULL;
	pMainWnd = (CDlgMainWindow *)parentWidget()->parentWidget();
	if (NULL == pMainWnd)
	{
		return;
	}

	nOnMouseItem = -1;

	for (i=0;i<vItemLabels.size();++i)
	{
		QPoint pt = vItemLabels[i]->pos();
		QSize sz = vItemLabels[i]->size();
		eachRect = QRect(vItemLabels[i]->pos(),vItemLabels[i]->size());
		if (eachRect.contains(ptMouse))
		{
			nOnMouseItem = i;
			bItemClicked = true;
			vItemLabels[i]->bClicked = true;
			readSaveStatus(vItemLabels[i]->nID, &(pChecker->vModelParas[i]), bItemEnabled);
			vItemLabels[i]->bEnabled = bItemEnabled;
			pMainWnd->m_bEnableItem = !bItemEnabled;
			pMainWnd->pItemLabel = (QWidget *)vItemLabels[i];
			pMainWnd->setBtnStatus();
			updateItemDlg(vItemLabels[i]);

			//2017.11-选中检测项时，设定区域颜色变化
			pMainWnd->displayObject();
			if (bItemEnabled==true && vItemLabels[i]->nID!=1 && vItemLabels[i]->nID!=2 && vItemLabels[i]->nID!=3)
			{							
				pMainWnd->displayRoiHighLight(vItemLabels[i]->nID,pChecker->vModelParas[i],pChecker->vModelShapes[i]);
			}
		}
		else
		{
			vItemLabels[i]->bClicked = false;
		}
		vItemLabels[i]->setColStyle();
	}

	if (nOnMouseItem == -1) //检测项未选中时
	{
		nRightMouseItem = nOnMouseItem;
	}
	else
	{
        nRightMouseItem = nOnMouseItem+1; //2017.2---检测项选中时，在其下方插入或粘贴
	}
	
	if (nOnMouseItem < 0)
	{
		bItemClicked = false;
		pMainWnd->setBtnStatus();
		//关闭对话框
		CItemDlg* pDlg = ((CItemDlg*)((CDlgMainWindow *)(parentWidget()->parentWidget()))->pItemDlg);
		if (NULL != pDlg)
		{
			delete pDlg;
		}
		pMainWnd->pItemLabel = NULL;
		pMainWnd->displayObject();
	}
}

void MyGroupBoxProcess::addItem()
{
	dlgWizard = new CDlgCheckItemWizard(this);
	
	if (QDialog::Accepted==dlgWizard->exec())
	{
		//检查定位检测项是否唯一
		if (dlgWizard->nItemID == ITEM_SIDEWALL_LOCATE ||
			dlgWizard->nItemID==ITEM_FINISH_LOCATE ||
			dlgWizard->nItemID==ITEM_BASE_LOCATE)
		{
			for (int i=0;i<pChecker->vItemFlow.size();++i)
			{
				int nItemID = pChecker->vItemFlow[i];
				if (nItemID== ITEM_SIDEWALL_LOCATE||
					nItemID==ITEM_FINISH_LOCATE ||
					nItemID==ITEM_BASE_LOCATE)
				{
					QMessageBox::critical(this,tr("Error"),tr("Location DetectionItem is already exist！"));
					return;
				}
			}
		}
		//增加
		QSettings noSet("no.ini",QSettings::IniFormat);
		QVariant paraDefault = pChecker->readParabyType(dlgWizard->nItemID,noSet);
		QString strName = "";
		readSaveNames(dlgWizard->nItemID, &paraDefault, strName);
		judgeName(strName);
		readSaveNames(dlgWizard->nItemID, &paraDefault, strName, false);
		pChecker->vItemFlow.push_back(dlgWizard->nItemID);
		pChecker->vModelParas.push_back(paraDefault);
		pChecker->vModelShapes.push_back(pChecker->readShapebyType(dlgWizard->nItemID,noSet));
		initItems();
		bAllItemsChange = true;

		QString	strErr = QString("Cam%1_").arg(pChecker->m_nCamIndex+1)+QString("adding inspection items[%1]:MyGroupBoxProcess::addItem,").arg(strName);//增加检测项
		pChecker->writeAlgOperationRecord(strErr);
	}
	delete dlgWizard;	
}

void MyGroupBoxProcess::insertItem()
{
	if (nRightMouseItem < 0)
	{
		return;
	}
	dlgWizard = new CDlgCheckItemWizard(this);
	if (QDialog::Accepted==dlgWizard->exec())
	{
		//检查定位检测项是否唯一
		if (dlgWizard->nItemID == ITEM_SIDEWALL_LOCATE ||
			dlgWizard->nItemID==ITEM_FINISH_LOCATE ||
			dlgWizard->nItemID==ITEM_BASE_LOCATE)
		{
			for (int i=0;i<pChecker->vItemFlow.size();++i)
			{
				int nItemID = pChecker->vItemFlow[i];
				if (nItemID== ITEM_SIDEWALL_LOCATE||
					nItemID==ITEM_FINISH_LOCATE ||
					nItemID==ITEM_BASE_LOCATE)
				{
					QMessageBox::critical(this,tr("Error"),tr("Location DetectionItem is already exist！"));
					return;
				}
			}
		}
		//插入
		QSettings noSet("no.ini",QSettings::IniFormat);
		QVariant paraDefault = pChecker->readParabyType(dlgWizard->nItemID,noSet);
		QString strName = "";
		readSaveNames(dlgWizard->nItemID, &paraDefault, strName);
		judgeName(strName);
		readSaveNames(dlgWizard->nItemID, &paraDefault, strName, false);
		pChecker->vItemFlow.insert(nRightMouseItem,1,dlgWizard->nItemID);
		pChecker->vModelParas.insert(nRightMouseItem,1,paraDefault);
		pChecker->vModelShapes.insert(nRightMouseItem,1,pChecker->readShapebyType(dlgWizard->nItemID,noSet));
		initItems();
		bAllItemsChange = true;
		QString	strErr = QString("Cam%1_").arg(pChecker->m_nCamIndex+1)+QString("insert inspection item[%1]:MyGroupBoxProcess::insertItem,").arg(strName);//插入检测项
		pChecker->writeAlgOperationRecord(strErr);
	}
	delete dlgWizard;
}

//2017.2---复制检测项
void MyGroupBoxProcess::copyItem()
{
	if (nOnMouseItem < 0)
	{
		return;
	}

	//拷贝(strName、nID、pPara、pShape)
	tempStrName = "";
	tempID = vItemLabels[nOnMouseItem]->nID;
	tempStrName = vItemLabels[nOnMouseItem]->strName;
	paraTemp = *(vItemLabels[nOnMouseItem]->pPara);
	shapeTemp = *(vItemLabels[nOnMouseItem]->pShape);

	QString	strErr = QString("Cam%1_").arg(pChecker->m_nCamIndex+1)+QString("copy inspection items[%1]:MyGroupBoxProcess::copyItem,").arg(tempStrName);//复制检测项
	pChecker->writeAlgOperationRecord(strErr);
}

//2017.2---粘贴检测项
void MyGroupBoxProcess::pasteItem()
{
	//没有拷贝内容
	if (tempID == -1)
	{
		return;
	}

	//检查定位检测项是否唯一
	if (tempID == ITEM_SIDEWALL_LOCATE ||
		tempID==ITEM_FINISH_LOCATE ||
		tempID==ITEM_BASE_LOCATE)
	{
		for (int i=0;i<pChecker->vItemFlow.size();++i)
		{
			int nItemID = pChecker->vItemFlow[i];
			if (nItemID== ITEM_SIDEWALL_LOCATE||
				nItemID==ITEM_FINISH_LOCATE ||
				nItemID==ITEM_BASE_LOCATE)
			{
				QMessageBox::critical(this,tr("Error"),tr("Location DetectionItem is already exist！"));
				return;
			}
		}
	}

	// 粘贴
	QString strToCopy = tempStrName+"_Copy";
	readSaveNames(tempID, &paraTemp, strToCopy, false);
	
	if (nRightMouseItem == -1) //在末尾粘贴
	{
		pChecker->vItemFlow.push_back(tempID);
		pChecker->vModelParas.push_back(paraTemp);
		pChecker->vModelShapes.push_back(shapeTemp);
	}
	else
	{
		pChecker->vItemFlow.insert(nRightMouseItem,1,tempID);
		pChecker->vModelParas.insert(nRightMouseItem,1,paraTemp);
		pChecker->vModelShapes.insert(nRightMouseItem,1,shapeTemp);
	}
	initItems();
	bAllItemsChange = true;	

	QString	strErr = QString::fromLocal8Bit("Cam%1_").arg(pChecker->m_nCamIndex+1)+QString::fromLocal8Bit("paste inspection items[%1]:MyGroupBoxProcess::pasteItem,").arg(strToCopy);//粘贴检测项
	pChecker->writeAlgOperationRecord(strErr);
}

void MyGroupBoxProcess::renameItem()
{
	//发送右击事件
	/*QMouseEvent *event = new QMouseEvent(QEvent::MouseButtonPress,QPoint(1,1),Qt::LeftButton,Qt::NoButton,Qt::NoModifier);
	QCoreApplication::sendEvent(vItemLabels[nOnMouseItem],event);*/
	if (nOnMouseItem < 0)
	{
		return;
	}
	bool isOk;
	QString newName = QInputDialog::getText(this,tr("Renamed"),tr("Please enter a new name (recommended no more than ten chars):"),
		QLineEdit::Normal,vItemLabels[nOnMouseItem]->strName,&isOk); 
	writeLogFile(newName);
	//printf("%s--%s--%s--%s###","newName:", newName,newName.toStdString().data(), QString::fromUtf8(newName));
	if (isOk && newName != vItemLabels[nOnMouseItem]->strName)
	{
		judgeName(newName);
		vItemLabels[nOnMouseItem]->strName=newName;
		//printf("%s--%s--%s--%s###","newName:", newName,newName.toStdString().data(), QString::fromLocal8Bit(newName));
		readSaveNames(vItemLabels[nOnMouseItem]->nID,vItemLabels[nOnMouseItem]->pPara,newName,false);
		vItemLabels[nOnMouseItem]->setText(vItemLabels[nOnMouseItem]->strName);
		bAllItemsChange = true;
		QString	strErr = QString("Cam%1_").arg(pChecker->m_nCamIndex+1)+QString("[rename inspection item%1]:MyGroupBoxProcess::renameItem,").arg(newName);//重命名检测项
		pChecker->writeAlgOperationRecord(strErr);
	}	
}

void MyGroupBoxProcess::deleteItem()
{
	if (nOnMouseItem < 0)
	{
		return;
	}
	QString strItemName = vItemLabels[nOnMouseItem]->strName;
	try
	{
		if (QMessageBox::Yes==QMessageBox::question(this,tr("Delete"),
			tr("Are you sure to delete the DetectionItem named:<font color=red>[%1]</font>？").arg(strItemName),
			QMessageBox::Yes | QMessageBox::No))
		{
			pChecker->vItemFlow.remove(nOnMouseItem);
			pChecker->vModelParas.remove(nOnMouseItem);
			pChecker->vModelShapes.remove(nOnMouseItem);
			initItems();
			bAllItemsChange = true;
			QString	strErr = QString("Cam%1_").arg(pChecker->m_nCamIndex+1)+QString("delete inspection item[%1]:MyGroupBoxProcess::deleteItem,").arg(strItemName);//删除检测项
			pChecker->writeAlgOperationRecord(strErr);
		}
	}
	catch (...)
	{
		QString	strErr = QString("abnormal_delete inspection item[%1]:MyGroupBoxProcess::deleteItem,").arg(strItemName);//删除检测项
		pChecker->writeErrDataRecord(strErr);
	}	
}

void MyGroupBoxProcess::enableItem()
{
	if (nOnMouseItem < 0)
	{
		return;
	}

	CDlgMainWindow *pMainWnd = NULL;
	pMainWnd = (CDlgMainWindow *)parentWidget()->parentWidget();
	if (NULL == pMainWnd)
	{
		return;
	}
	bool bItemEnabled = pMainWnd->m_bEnableItem;
	pMainWnd->m_bEnableItem = !(pMainWnd->m_bEnableItem);
	pMainWnd->setBtnStatus();
	readSaveStatus(vItemLabels[nOnMouseItem]->nID, &(pChecker->vModelParas[nOnMouseItem]), bItemEnabled, false);
	vItemLabels[nOnMouseItem]->bParaChanged = true;
	vItemLabels[nOnMouseItem]->bEnabled = bItemEnabled;
	vItemLabels[nOnMouseItem]->setColStyle();
	pMainWnd->displayObject();
	QString	strErr = QString("Cam%1_").arg(pChecker->m_nCamIndex+1)+QString("enable or unable the inspection item[%1]:MyGroupBoxProcess::enableItem,").arg(vItemLabels[nOnMouseItem]->strName);//禁启用检测项
	pChecker->writeAlgOperationRecord(strErr);
}

void MyGroupBoxProcess::showItems()
{
	int i;
	if (layout()!=0)
		delete layout();

	switch(iShowType)
	{
	case 0:
		{
			QHBoxLayout *hBox = new QHBoxLayout;
			hBox->setContentsMargins(5, 3, 5, 3);
			for (i=0;i<vItemLabels.size();++i)
			{
				hBox->addWidget(vItemLabels[i],Qt::AlignCenter);	
				if (i==vItemLabels.size()-1)
				{
					hBox->addStretch(10);//最后一个向前挤压
				}
				else
					hBox->addStretch(1);
			}
			setLayout(hBox);
		}
		break;
	case 1:
		{
			QVBoxLayout *vBox = new QVBoxLayout;
			vBox->setContentsMargins(5, 3, 5, 3);
			for (i=0;i<vItemLabels.size();++i)
			{
				vBox->addWidget(vItemLabels[i],Qt::AlignCenter);		
				if (i==vItemLabels.size()-1)
				{
					vBox->addStretch(10);//最后一个向前挤压
				}
				else
					vBox->addStretch(1);
			}
			setLayout(vBox);
		}
		break;
	default:
		break;
	}
}

// 根据检测类型显示相应的算法设置对话框
void MyGroupBoxProcess::updateItemDlg(MyLabelItem *pLabelItem)
{
	QVariant *pPara = pLabelItem->pPara;
	QVariant *pShape = pLabelItem->pShape;
	int nID = pLabelItem->nID;
	CDlgMainWindow *pMainWnd = (CDlgMainWindow *)(parentWidget()->parentWidget());
	if (NULL == pMainWnd)
	{
		return;
	}
	//关闭当前正在显示的对话框
	CItemDlg* pDlg = (CItemDlg*)pMainWnd->pItemDlg;
	if (NULL != pDlg)
	{
		delete pDlg;
		pDlg = NULL;
	}
	switch (nID)
	{
	case ITEM_SIDEWALL_LOCATE:
		{
			//CDlgSidewallLocate *dlgSideLoc=new CDlgSidewallLocate(pMainWnd,pPara,pShape);			
			//dlgSideLoc->show();
			pDlg = new CDlgSidewallLocate(pMainWnd,pPara,pShape);	
		}
		break;
	case ITEM_FINISH_LOCATE:
		{
			/*CDlgFinishLocate *dlgFinLoc=new CDlgFinishLocate(pMainWnd,pPara,pShape);
			dlgFinLoc->show();*/
			pDlg = new CDlgFinishLocate(pMainWnd,pPara,pShape);
		}
		break;
	case  ITEM_BASE_LOCATE:
		{
			/*CDlgBaseLocate *dlgBaseLoc=new CDlgBaseLocate(pMainWnd,pPara,pShape);
			dlgBaseLoc->show();*/
			pDlg = new CDlgBaseLocate(pMainWnd,pPara,pShape);
		}
		break;
	case ITEM_HORI_SIZE:
		{
			/*CDlgHoriSize *dlgHoriSize=new CDlgHoriSize(pMainWnd,pPara,pShape);
			dlgHoriSize->show();*/
			pDlg = new CDlgHoriSize(pMainWnd,pPara,pShape);
		}
		break;
	case ITEM_VERT_SIZE:
		{
			/*CDlgVertSize *dlgVertSize=new CDlgVertSize(pMainWnd,pPara,pShape);
			dlgVertSize->show();*/
			pDlg = new CDlgVertSize(pMainWnd,pPara,pShape);
		}
		break;
	case ITEM_FULL_HEIGHT:
		{
			/*CDlgFullHeight *dlgFullHeight=new CDlgFullHeight(pMainWnd,pPara,pShape);
			dlgFullHeight->show();*/
			pDlg = new CDlgFullHeight(pMainWnd,pPara,pShape);
		}
		break;
	case ITEM_BENT_NECK:
		{
			/*CDlgBentNeck *dlgBentNeck=new CDlgBentNeck(pMainWnd,pPara,pShape);
			dlgBentNeck->show();*/
			pDlg = new CDlgBentNeck(pMainWnd,pPara,pShape);
		}
		break;
	case ITEM_VERT_ANG:
		{
			/*CDlgVertAng *dlgVertAng=new CDlgVertAng(pMainWnd,pPara,pShape);
			dlgVertAng->show();*/
			pDlg = new CDlgVertAng(pMainWnd,pPara,pShape);
		}
		break;
	case ITEM_SGENNERAL_REGION:
		{
			//CDlgSGenReg *dlgSGenReg=new CDlgSGenReg(pMainWnd,pPara,pShape);
			pDlg = new CDlgSGenReg(pMainWnd,pPara,pShape);
		}
		break;
	case ITEM_DISTURB_REGION:
		{
			/*CDlgDisturbReg *dlgDistReg=new CDlgDisturbReg(pMainWnd,pPara,pShape);
			dlgDistReg->show();*/
			pDlg = new CDlgDisturbReg(pMainWnd,pPara,pShape);
		}
		break;
	case ITEM_SSIDEFINISH_REGION:
		{
			/*CDlgSSideFReg *dlgSSideFReg=new CDlgSSideFReg(pMainWnd,pPara,pShape);
			dlgSSideFReg->show();*/
			pDlg = new CDlgSSideFReg(pMainWnd,pPara,pShape);
		}
		break;
	case ITEM_SINFINISH_REGION:
		{
			/*CDlgSInFReg *dlgSInFReg=new CDlgSInFReg(pMainWnd,pPara,pShape);
			dlgSInFReg->show();*/
			pDlg = new CDlgSInFReg(pMainWnd,pPara,pShape);
		}
		break;
	case ITEM_SSCREWFINISH_REGION:
		{
			/*CDlgSScrewFReg *dlgSScrewFReg=new CDlgSScrewFReg(pMainWnd,pPara,pShape);
			dlgSScrewFReg->show();*/
			pDlg = new CDlgSScrewFReg(pMainWnd,pPara,pShape);
		}
		break;
	case ITEM_FRLINNER_REGION:
		{
			/*CDlgFRLInReg *dlgFRLInReg=new CDlgFRLInReg(pMainWnd,pPara,pShape);
			dlgFRLInReg->show();*/
			pDlg = new CDlgFRLInReg(pMainWnd,pPara,pShape);
		}
		break;
	case ITEM_FRLMIDDLE_REGION:
		{
			/*CDlgFRLMidReg *dlgFRLMidReg=new CDlgFRLMidReg(pMainWnd,pPara,pShape);
			dlgFRLMidReg->show();*/
			pDlg = new CDlgFRLMidReg(pMainWnd,pPara,pShape);
		}
		break;
	case ITEM_FRLOUTER_REGION:
		{
			/*CDlgFRLOutReg *dlgFRLOutReg=new CDlgFRLOutReg(pMainWnd,pPara,pShape);
			dlgFRLOutReg->show();*/
			pDlg = new CDlgFRLOutReg(pMainWnd,pPara,pShape);
		}
		break;
	case ITEM_FBLINNER_REGION:
		{
			/*CDlgFBLInReg *dlgFBLInReg=new CDlgFBLInReg(pMainWnd,pPara,pShape);
			dlgFBLInReg->show();*/
			pDlg = new CDlgFBLInReg(pMainWnd,pPara,pShape);
		}
		break;
	case ITEM_FBLMIDDLE_REGION:
		{
			/*CDlgFBLMidReg *dlgFBLMidReg=new CDlgFBLMidReg(pMainWnd,pPara,pShape);
			dlgFBLMidReg->show();*/
			pDlg = new CDlgFBLMidReg(pMainWnd,pPara,pShape);
		}
		break;
	case ITEM_BINNER_REGION:
		{
			/*CDlgBInReg *dlgBInReg=new CDlgBInReg(pMainWnd,pPara,pShape);
			dlgBInReg->show();*/
			pDlg = new CDlgBInReg(pMainWnd,pPara,pShape);
		}
		break;
	case ITEM_BMIDDLE_REGION:
		{
			/*CDlgBMidReg *dlgBMidReg=new CDlgBMidReg(pMainWnd,pPara,pShape);
			dlgBMidReg->show();*/
			pDlg = new CDlgBMidReg(pMainWnd,pPara,pShape);
		}
		break;
	case ITEM_BOUTER_REGION:
		{
			/*CDlgBOutReg *dlgBOutReg=new CDlgBOutReg(pMainWnd,pPara,pShape);
			dlgBOutReg->show();*/
			pDlg = new CDlgBOutReg(pMainWnd,pPara,pShape);
		}
		break;
	case ITEM_SSIDEWALL_REGION:
		{
			/*CDlgSSideReg *dlgSSideReg=new CDlgSSideReg(pMainWnd,pPara,pShape);
			dlgSSideReg->show();*/
			pDlg = new CDlgSSideReg(pMainWnd,pPara,pShape);
		}
		break;
	case ITEM_FINISH_CONTOUR:
		{
			/*CDlgFinCont *dlgFinCont=new CDlgFinCont(pMainWnd,pPara,pShape);
			dlgFinCont->show();*/
			pDlg = new CDlgFinCont(pMainWnd,pPara,pShape);
		}
		break;
	case ITEM_NECK_CONTOUR:
		{
			/*CDlgNeckCont *dlgNeckCont=new CDlgNeckCont(pMainWnd,pPara,pShape);
			dlgNeckCont->show();*/
			pDlg = new CDlgNeckCont(pMainWnd,pPara,pShape);
		}
		break;
	case ITEM_BODY_CONTOUR:
		{
			/*CDlgBodyCont *dlgBodyCont=new CDlgBodyCont(pMainWnd,pPara,pShape);
			dlgBodyCont->show();*/
			pDlg = new CDlgBodyCont(pMainWnd,pPara,pShape);
		}
		break;
	case ITEM_SBRISPOT_REGION:
		{
			/*CDlgSBriSpotReg *dlgSBriSpotReg=new CDlgSBriSpotReg(pMainWnd,pPara,pShape);
			dlgSBriSpotReg->show();*/
			pDlg = new CDlgSBriSpotReg(pMainWnd,pPara,pShape);
		}
		break;
	case ITEM_BALL_REGION:
		{
			/*CDlgBAllReg *dlgBAllReg=new CDlgBAllReg(pMainWnd,pPara,pShape);
			dlgBAllReg->show();*/
			pDlg = new CDlgBAllReg(pMainWnd,pPara,pShape);
		}
		break;
	case ITEM_CIRCLE_SIZE:
		{
			/*CDlgCircleSize *dlgCircleSize=new CDlgCircleSize(pMainWnd,pPara,pShape);
			dlgCircleSize->show();*/
			pDlg = new CDlgCircleSize(pMainWnd,pPara,pShape);
		}
		break;
	case ITEM_SBASE_REGION:
		{
			/*CDlgSBaseReg *dlgSBaseReg=new CDlgSBaseReg(pMainWnd,pPara,pShape);
			dlgSBaseReg->show();*/
			pDlg = new CDlgSBaseReg(pMainWnd,pPara,pShape);
		}
		break;
	case ITEM_SBASECONVEX_REGION:
		{
			/*CDlgSBaseConvexReg *dlgSBaseReg=new CDlgSBaseConvexReg(pMainWnd,pPara,pShape);
			dlgSBaseReg->show();*/
			pDlg = new CDlgSBaseConvexReg(pMainWnd,pPara,pShape);
		}
		break;
	default:
		break;
	}
	if (NULL != pDlg)
	{
#ifdef DAHENGBLPKP_QT
		// 设置滚动条可以在需要的时候显示 [8/6/2015 zhaodt]
		((QScrollArea*)(pMainWnd->paramWidget()))->setWidget(pDlg);
#endif
		pDlg->show();
	}
}

// 根据检测类型显示相应的算法设置对话框
void MyGroupBoxProcess::applyItemDlg(MyLabelItem *pLabelItem)
{
	int nID = pLabelItem->nID;
	CDlgMainWindow *pMainWnd = (CDlgMainWindow *)(parentWidget()->parentWidget());
	if (NULL == pMainWnd)
	{
		return;
	}

	switch (nID)
	{
	case ITEM_SIDEWALL_LOCATE:
		{
			CDlgSidewallLocate *dlgSidLoc = (CDlgSidewallLocate *)(pMainWnd->pItemDlg);
			if (dlgSidLoc != NULL)
			{
				dlgSidLoc->autoAccept();
			}
		}
		break;
	case ITEM_FINISH_LOCATE:
		{
			CDlgFinishLocate *dlgFinLoc=(CDlgFinishLocate *)(pMainWnd->pItemDlg);
			if (dlgFinLoc != NULL)
			{
				dlgFinLoc->autoAccept();
			}
		}
		break;
	case  ITEM_BASE_LOCATE:
		{
			CDlgBaseLocate *dlgBaseLoc=(CDlgBaseLocate *)(pMainWnd->pItemDlg);
			if (dlgBaseLoc != NULL)
			{
				dlgBaseLoc->autoAccept();
			}
		}
		break;
	case ITEM_HORI_SIZE:
		{
			CDlgHoriSize *dlgHoriSize = (CDlgHoriSize *)(pMainWnd->pItemDlg);
			if (dlgHoriSize != NULL)
			{
				dlgHoriSize->autoAccept();
			}
		}
		break;
	case ITEM_VERT_SIZE:
		{
			CDlgVertSize *dlgVertSize = (CDlgVertSize *)(pMainWnd->pItemDlg);
			if (dlgVertSize != NULL)
			{
				dlgVertSize->autoAccept();
			}
		}
		break;
	case ITEM_FULL_HEIGHT:
		{
			CDlgFullHeight *dlgFullHeight = (CDlgFullHeight *)(pMainWnd->pItemDlg);
			if (dlgFullHeight != NULL)
			{
				dlgFullHeight->autoAccept();
			}
		}
		break;
	case ITEM_BENT_NECK:
		{
			CDlgBentNeck *dlgBentNeck = (CDlgBentNeck *)(pMainWnd->pItemDlg);
			if (dlgBentNeck != NULL)
			{
				dlgBentNeck->autoAccept();
			}
		}
		break;
	case ITEM_VERT_ANG:
		{
			CDlgVertAng *dlgVertAng = (CDlgVertAng *)(pMainWnd->pItemDlg);
			if (dlgVertAng != NULL)
			{
				dlgVertAng->autoAccept();
			}
		}
		break;
	case ITEM_SGENNERAL_REGION:
		{
			CDlgSGenReg *dlgSGenReg = (CDlgSGenReg *)(pMainWnd->pItemDlg);
			if (dlgSGenReg != NULL)
			{
				dlgSGenReg->autoAccept();
			}
		}
		break;
	case ITEM_DISTURB_REGION:
		{
			CDlgDisturbReg *dlgDistReg = (CDlgDisturbReg *)(pMainWnd->pItemDlg);
			if (dlgDistReg != NULL)
			{
				dlgDistReg->autoAccept();
			}
		}
		break;
	case ITEM_SSIDEFINISH_REGION:
		{
			CDlgSSideFReg *dlgSSideFReg = (CDlgSSideFReg *)(pMainWnd->pItemDlg);
			if (dlgSSideFReg != NULL)
			{
				dlgSSideFReg->autoAccept();
			}
		}
		break;
	case ITEM_SINFINISH_REGION:
		{
			CDlgSInFReg *dlgSInFReg = (CDlgSInFReg *)(pMainWnd->pItemDlg);
			if (dlgSInFReg != NULL)
			{
				dlgSInFReg->autoAccept();
			}
		}
		break;
	case ITEM_SSCREWFINISH_REGION:
		{
			CDlgSScrewFReg *dlgSScrewFReg = (CDlgSScrewFReg *)(pMainWnd->pItemDlg);
			if (dlgSScrewFReg != NULL)
			{
				dlgSScrewFReg->autoAccept();
			}
		}
		break;
	case ITEM_FRLINNER_REGION:
		{
			CDlgFRLInReg *dlgFRLInReg = (CDlgFRLInReg *)(pMainWnd->pItemDlg);
			if (dlgFRLInReg != NULL)
			{
				dlgFRLInReg->autoAccept();
			}
		}
		break;
	case ITEM_FRLMIDDLE_REGION:
		{
			CDlgFRLMidReg *dlgFRLMidReg = (CDlgFRLMidReg *)(pMainWnd->pItemDlg);
			if (dlgFRLMidReg != NULL)
			{
				dlgFRLMidReg->autoAccept();
			}
		}
		break;
	case ITEM_FRLOUTER_REGION:
		{
			CDlgFRLOutReg *dlgFRLOutReg = (CDlgFRLOutReg *)(pMainWnd->pItemDlg);
			if (dlgFRLOutReg != NULL)
			{
				dlgFRLOutReg->autoAccept();
			}
		}
		break;
	case ITEM_FBLINNER_REGION:
		{
			CDlgFBLInReg *dlgFBLInReg = (CDlgFBLInReg *)(pMainWnd->pItemDlg);
			if (dlgFBLInReg != NULL)
			{
				dlgFBLInReg->autoAccept();
			}
		}
		break;
	case ITEM_FBLMIDDLE_REGION:
		{
			CDlgFBLMidReg *dlgFBLMidReg = (CDlgFBLMidReg *)(pMainWnd->pItemDlg);
			if (dlgFBLMidReg != NULL)
			{
				dlgFBLMidReg->autoAccept();
			}
		}
		break;
	case ITEM_BINNER_REGION:
		{
			CDlgBInReg *dlgBInReg = (CDlgBInReg *)(pMainWnd->pItemDlg);
			if (dlgBInReg != NULL)
			{
				dlgBInReg->autoAccept();
			}
		}
		break;
	case ITEM_BMIDDLE_REGION:
		{
			CDlgBMidReg *dlgBMidReg = (CDlgBMidReg *)(pMainWnd->pItemDlg);
			if (dlgBMidReg != NULL)
			{
				dlgBMidReg->autoAccept();
			}
		}
		break;
	case ITEM_BOUTER_REGION:
		{
			CDlgBOutReg *dlgBOutReg = (CDlgBOutReg *)(pMainWnd->pItemDlg);
			if (dlgBOutReg != NULL)
			{
				dlgBOutReg->autoAccept();
			}
		}
		break;
	case ITEM_SSIDEWALL_REGION:
		{
			CDlgSSideReg *dlgSSideReg = (CDlgSSideReg *)(pMainWnd->pItemDlg);
			if (dlgSSideReg != NULL)
			{
				dlgSSideReg->autoAccept();
			}
		}
		break;
	case ITEM_FINISH_CONTOUR:
		{
			CDlgFinCont *dlgFinCont = (CDlgFinCont *)(pMainWnd->pItemDlg);
			if (dlgFinCont != NULL)
			{
				dlgFinCont->autoAccept();
			}
		}
		break;
	case ITEM_NECK_CONTOUR:
		{
			CDlgNeckCont *dlgNeckCont = (CDlgNeckCont *)(pMainWnd->pItemDlg);
			if (dlgNeckCont != NULL)
			{
				dlgNeckCont->autoAccept();
			}
		}
		break;
	case ITEM_BODY_CONTOUR:
		{
			CDlgBodyCont *dlgBodyCont = (CDlgBodyCont *)(pMainWnd->pItemDlg);
			if (dlgBodyCont != NULL)
			{
				dlgBodyCont->autoAccept();
			}
		}
		break;
	case ITEM_SBRISPOT_REGION:
		{
			CDlgSBriSpotReg *dlgSBriSpotReg = (CDlgSBriSpotReg *)(pMainWnd->pItemDlg);
			if (dlgSBriSpotReg != NULL)
			{
				dlgSBriSpotReg->autoAccept();
			}
		}
		break;
	case ITEM_BALL_REGION:
		{
			CDlgBAllReg *dlgBAllReg = (CDlgBAllReg *)(pMainWnd->pItemDlg);
			if (dlgBAllReg != NULL)
			{
				dlgBAllReg->autoAccept();
			}
		}
		break;
	case ITEM_CIRCLE_SIZE:
		{
			CDlgCircleSize *dlgCircleSize = (CDlgCircleSize *)(pMainWnd->pItemDlg);
			if (dlgCircleSize != NULL)
			{
				dlgCircleSize->autoAccept();
			}
		}
		break;
	case ITEM_SBASE_REGION:
		{
			CDlgSBaseReg *dlgSBaseReg = (CDlgSBaseReg *)(pMainWnd->pItemDlg);
			if (dlgSBaseReg != NULL)
			{
				dlgSBaseReg->autoAccept();
			}
		}
		break;
	case ITEM_SBASECONVEX_REGION:
		{
			CDlgSBaseConvexReg *dlgSBaseConReg = (CDlgSBaseConvexReg *)(pMainWnd->pItemDlg);
			if (dlgSBaseConReg != NULL)
			{
				dlgSBaseConReg->autoAccept();
			}
		}
		break;
	default:
		break;
	}
}

void MyGroupBoxProcess::judgeName(QString &strName) 
{
	int i,j;	
	bool flag;
	QVector<int> suffixNum;
	for (i=0;i<vItemLabels.size();++i)
	{	//printf("%s--%s--%s====","judgeName:", vItemLabels[i]->name().left(strName.size()),vItemLabels[i]->name().right(vItemLabels[i]->name().size()-strName.size()));
		if (vItemLabels[i]->name().left(strName.size())==strName)
		{ 
			if (vItemLabels[i]->name().size()==strName.size())
				suffixNum.push_back(1);
			
			QString strRight = vItemLabels[i]->name().right(vItemLabels[i]->name().size()-strName.size());
			bool ok;
			int num = strRight.toInt(&ok,10);
			if (ok)
				suffixNum.push_back(num);
		}
	}

	if (suffixNum.size()>0)
	{
		//从1开始递增，找唯一的后缀
		for (i=1;i<65535;++i)
		{
			flag=false;
			for (j=0;j<suffixNum.size();++j)
			{
				if (i==suffixNum[j])
				{
					flag=true;
					break;
				}
			}
			if (!flag)
			{
				if (i!=1)
					strName+=QString::number(i);//大于1才添加				
				break;
			}
		}
	}	
}
void MyGroupBoxProcess::writeLogFile(QString str)//QString *str
{
	// char tmpLog[256]=".\\lxnt_dlg.txt";
	QFile logFile("logstrn.txt");
	if (!logFile.open(QIODevice::WriteOnly | QIODevice::Append))
	{
		return;
	}
	QString current_date_time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss ddd");   
	QString message = QString("%1 --> %2").arg(current_date_time).
		arg(str);  
	QTextStream textStream(&logFile);  
	textStream << message << "\r\n";  
	logFile.flush();  
	logFile.close();

}
void MyGroupBoxProcess::readSaveNames(int nID, QVariant *pPara, QString &strName, bool bFlag /* = true */)
{
	//flag=true:读 flag=false：写	
	switch(nID)
	{
	case ITEM_SIDEWALL_LOCATE:		
		if (bFlag)
		{
			strName = pPara->value<s_pSideLoc>().strName;
		}
		else
		{
			s_pSideLoc sData = pPara->value<s_pSideLoc>();
			sData.strName=strName;
			pPara->setValue(sData);
		}		
		break;
	case ITEM_FINISH_LOCATE:
		if (bFlag)
		{
			strName = pPara->value<s_pFinLoc>().strName;
		}
		else
		{
			s_pFinLoc sData = pPara->value<s_pFinLoc>();
			sData.strName=strName;
			pPara->setValue(sData);
		}		
		break;
	case ITEM_BASE_LOCATE:
		if (bFlag)
		{
			strName = pPara->value<s_pBaseLoc>().strName;
		}
		else
		{
			s_pBaseLoc sData = pPara->value<s_pBaseLoc>();
			sData.strName=strName;
			pPara->setValue(sData);
		}	
		break;
	case ITEM_HORI_SIZE:
		if (bFlag)
		{
			strName = pPara->value<s_pHoriSize>().strName;
		}
		else
		{
			s_pHoriSize sData = pPara->value<s_pHoriSize>();
			sData.strName=strName;
			pPara->setValue(sData);
		}	
		break;
	case ITEM_VERT_SIZE:
		if (bFlag)
		{
			strName = pPara->value<s_pVertSize>().strName;
		}
		else
		{
			s_pVertSize sData = pPara->value<s_pVertSize>();
			sData.strName=strName;
			pPara->setValue(sData);
		}	
		break;
	case ITEM_FULL_HEIGHT:
		if (bFlag)
		{
			strName = pPara->value<s_pFullHeight>().strName;
		}
		else
		{
			s_pFullHeight sData = pPara->value<s_pFullHeight>();
			sData.strName=strName;
			pPara->setValue(sData);
		}	
		break;
	case ITEM_BENT_NECK:
		if (bFlag)
		{
			strName = pPara->value<s_pBentNeck>().strName;
		}
		else
		{
			s_pBentNeck sData = pPara->value<s_pBentNeck>();
			sData.strName=strName;
			pPara->setValue(sData);
		}	
		break;
	case ITEM_VERT_ANG:
		if (bFlag)
		{
			strName = pPara->value<s_pVertAng>().strName;
		}
		else
		{
			s_pVertAng sData = pPara->value<s_pVertAng>();
			sData.strName=strName;
			pPara->setValue(sData);
		}	
		break;
	case ITEM_SGENNERAL_REGION:
		if (bFlag)
		{
			strName = pPara->value<s_pSGenReg>().strName;
		}
		else
		{
			s_pSGenReg sData = pPara->value<s_pSGenReg>();
			sData.strName=strName;
			pPara->setValue(sData);
		}	
		break;
	case ITEM_SSIDEFINISH_REGION:
		if (bFlag)
		{
			strName = pPara->value<s_pSSideFReg>().strName;
		}
		else
		{
			s_pSSideFReg sData = pPara->value<s_pSSideFReg>();
			sData.strName=strName;
			pPara->setValue(sData);
		}	
		break;
	case ITEM_SINFINISH_REGION:
		if (bFlag)
		{
			strName = pPara->value<s_pSInFReg>().strName;
		}
		else
		{
			s_pSInFReg sData = pPara->value<s_pSInFReg>();
			sData.strName=strName;
			pPara->setValue(sData);
		}	
		break;
	case ITEM_SSCREWFINISH_REGION:
		if (bFlag)
		{
			strName = pPara->value<s_pSScrewFReg>().strName;
		}
		else
		{
			s_pSScrewFReg sData = pPara->value<s_pSScrewFReg>();
			sData.strName=strName;
			pPara->setValue(sData);
		}	
		break;
	case ITEM_FRLINNER_REGION:
		if (bFlag)
		{
			strName = pPara->value<s_pFRLInReg>().strName;
		}
		else
		{
			s_pFRLInReg sData = pPara->value<s_pFRLInReg>();
			sData.strName=strName;
			pPara->setValue(sData);
		}	
		break;
	case ITEM_FRLMIDDLE_REGION:
		if (bFlag)
		{
			strName = pPara->value<s_pFRLMidReg>().strName;
		}
		else
		{
			s_pFRLMidReg sData = pPara->value<s_pFRLMidReg>();
			sData.strName=strName;
			pPara->setValue(sData);
		}	
		break;
	case ITEM_FRLOUTER_REGION:
		if (bFlag)
		{
			strName = pPara->value<s_pFRLOutReg>().strName;
		}
		else
		{
			s_pFRLOutReg sData = pPara->value<s_pFRLOutReg>();
			sData.strName=strName;
			pPara->setValue(sData);
		}	
		break;
	case ITEM_FBLINNER_REGION:
		if (bFlag)
		{
			strName = pPara->value<s_pFBLInReg>().strName;
		}
		else
		{
			s_pFBLInReg sData = pPara->value<s_pFBLInReg>();
			sData.strName=strName;
			pPara->setValue(sData);
		}	
		break;
	case ITEM_FBLMIDDLE_REGION:
		if (bFlag)
		{
			strName = pPara->value<s_pFBLMidReg>().strName;
		}
		else
		{
			s_pFBLMidReg sData = pPara->value<s_pFBLMidReg>();
			sData.strName=strName;
			pPara->setValue(sData);
		}	
		break;
	case ITEM_BINNER_REGION:
		if (bFlag)
		{
			strName = pPara->value<s_pBInReg>().strName;
		}
		else
		{
			s_pBInReg sData = pPara->value<s_pBInReg>();
			sData.strName=strName;
			pPara->setValue(sData);
		}	
		break;
	case ITEM_BMIDDLE_REGION:
		if (bFlag)
		{
			strName = pPara->value<s_pBMidReg>().strName;
		}
		else
		{
			s_pBMidReg sData = pPara->value<s_pBMidReg>();
			sData.strName=strName;
			pPara->setValue(sData);
		}	
		break;
	case ITEM_BOUTER_REGION:
		if (bFlag)
		{
			strName = pPara->value<s_pBOutReg>().strName;
		}
		else
		{
			s_pBOutReg sData = pPara->value<s_pBOutReg>();
			sData.strName=strName;
			pPara->setValue(sData);
		}	
		break;
	case ITEM_SSIDEWALL_REGION:
		if (bFlag)
		{
			strName = pPara->value<s_pSSideReg>().strName;
			//printf("%s--%s--%s--%s###","strName:", pPara->value<s_pSSideReg>().strName,pPara->value<s_pSSideReg>().strName.toStdString().data(), QString::fromLocal8Bit(pPara->value<s_pSSideReg>().strName));
			writeLogFile(strName);
		}
		else
		{
			s_pSSideReg sData = pPara->value<s_pSSideReg>();
			sData.strName=strName;
			pPara->setValue(sData);
		}	
		break;
	case ITEM_DISTURB_REGION:
		if (bFlag)
		{
			strName = pPara->value<s_pDistReg>().strName;
		}
		else
		{
			s_pDistReg sData = pPara->value<s_pDistReg>();
			sData.strName=strName;
			pPara->setValue(sData);
		}	
		break;
	case ITEM_FINISH_CONTOUR:
		if (bFlag)
		{
			strName = pPara->value<s_pFinCont>().strName;
		}
		else
		{
			s_pFinCont sData = pPara->value<s_pFinCont>();
			sData.strName=strName;
			pPara->setValue(sData);
		}	
		break;
	case ITEM_NECK_CONTOUR:
		if (bFlag)
		{
			strName = pPara->value<s_pNeckCont>().strName;
		}
		else
		{
			s_pNeckCont sData = pPara->value<s_pNeckCont>();
			sData.strName=strName;
			pPara->setValue(sData);
		}	
		break;
	case ITEM_BODY_CONTOUR:
		if (bFlag)
		{
			strName = pPara->value<s_pBodyCont>().strName;
		}
		else
		{
			s_pBodyCont sData = pPara->value<s_pBodyCont>();
			sData.strName=strName;
			pPara->setValue(sData);
		}	
		break;
	case ITEM_SBRISPOT_REGION:
		if (bFlag)
		{
			strName = pPara->value<s_pSBriSpotReg>().strName;
		}
		else
		{
			s_pSBriSpotReg sData = pPara->value<s_pSBriSpotReg>();
			sData.strName=strName;
			pPara->setValue(sData);
		}	
		break;
	case ITEM_BALL_REGION:
		if (bFlag)
		{
			strName = pPara->value<s_pBAllReg>().strName;
		}
		else
		{
			s_pBAllReg sData = pPara->value<s_pBAllReg>();
			sData.strName=strName;
			pPara->setValue(sData);
		}	
		break;
	case ITEM_CIRCLE_SIZE:
		if (bFlag)
		{
			strName = pPara->value<s_pCirSize>().strName;
		}
		else
		{
			s_pCirSize sData = pPara->value<s_pCirSize>();
			sData.strName=strName;
			pPara->setValue(sData);
		}	
		break;
	case ITEM_SBASE_REGION:
		if (bFlag)
		{
			strName = pPara->value<s_pSBaseReg>().strName;
		}
		else
		{
			s_pSBaseReg sData = pPara->value<s_pSBaseReg>();
			sData.strName=strName;
			pPara->setValue(sData);
		}	
		break;
	case ITEM_SBASECONVEX_REGION:
		if (bFlag)
		{
			strName = pPara->value<s_pSBaseConvexReg>().strName;
		}
		else
		{
			s_pSBaseConvexReg sData = pPara->value<s_pSBaseConvexReg>();
			sData.strName=strName;
			pPara->setValue(sData);
		}	
		break;
	default:
		break;
	}
}

void MyGroupBoxProcess::readSaveStatus(int nID, QVariant *pPara, bool &bStatus, bool bFlag /* = true */)
{
	//flag=true:读 flag=false：写	
	switch(nID)
	{
	case ITEM_SIDEWALL_LOCATE:		
		if (bFlag)
		{
			bStatus = pPara->value<s_pSideLoc>().bEnabled;
		}
		else
		{
			s_pSideLoc sData = pPara->value<s_pSideLoc>();
			sData.bEnabled=bStatus;
			pPara->setValue(sData);
		}		
		break;
	case ITEM_FINISH_LOCATE:
		if (bFlag)
		{
			bStatus = pPara->value<s_pFinLoc>().bEnabled;
		}
		else
		{
			s_pFinLoc sData = pPara->value<s_pFinLoc>();
			sData.bEnabled=bStatus;
			pPara->setValue(sData);
		}		
		break;
	case ITEM_BASE_LOCATE:
		if (bFlag)
		{
			bStatus = pPara->value<s_pBaseLoc>().bEnabled;
		}
		else
		{
			s_pBaseLoc sData = pPara->value<s_pBaseLoc>();
			sData.bEnabled=bStatus;
			pPara->setValue(sData);
		}	
		break;
	case ITEM_HORI_SIZE:
		if (bFlag)
		{
			bStatus = pPara->value<s_pHoriSize>().bEnabled;
		}
		else
		{
			s_pHoriSize sData = pPara->value<s_pHoriSize>();
			sData.bEnabled=bStatus;
			pPara->setValue(sData);
		}	
		break;
	case ITEM_VERT_SIZE:
		if (bFlag)
		{
			bStatus = pPara->value<s_pVertSize>().bEnabled;
		}
		else
		{
			s_pVertSize sData = pPara->value<s_pVertSize>();
			sData.bEnabled=bStatus;
			pPara->setValue(sData);
		}	
		break;
	case ITEM_FULL_HEIGHT:
		if (bFlag)
		{
			bStatus = pPara->value<s_pFullHeight>().bEnabled;
		}
		else
		{
			s_pFullHeight sData = pPara->value<s_pFullHeight>();
			sData.bEnabled=bStatus;
			pPara->setValue(sData);
		}	
		break;
	case ITEM_BENT_NECK:
		if (bFlag)
		{
			bStatus = pPara->value<s_pBentNeck>().bEnabled;
		}
		else
		{
			s_pBentNeck sData = pPara->value<s_pBentNeck>();
			sData.bEnabled=bStatus;
			pPara->setValue(sData);
		}	
		break;
	case ITEM_VERT_ANG:
		if (bFlag)
		{
			bStatus = pPara->value<s_pVertAng>().bEnabled;
		}
		else
		{
			s_pVertAng sData = pPara->value<s_pVertAng>();
			sData.bEnabled=bStatus;
			pPara->setValue(sData);
		}	
		break;
	case ITEM_SGENNERAL_REGION:
		if (bFlag)
		{
			bStatus = pPara->value<s_pSGenReg>().bEnabled;
		}
		else
		{
			s_pSGenReg sData = pPara->value<s_pSGenReg>();
			sData.bEnabled=bStatus;
			pPara->setValue(sData);
		}	
		break;
	case ITEM_SSIDEFINISH_REGION:
		if (bFlag)
		{
			bStatus = pPara->value<s_pSSideFReg>().bEnabled;
		}
		else
		{
			s_pSSideFReg sData = pPara->value<s_pSSideFReg>();
			sData.bEnabled=bStatus;
			pPara->setValue(sData);
		}	
		break;
	case ITEM_SINFINISH_REGION:
		if (bFlag)
		{
			bStatus = pPara->value<s_pSInFReg>().bEnabled;
		}
		else
		{
			s_pSInFReg sData = pPara->value<s_pSInFReg>();
			sData.bEnabled=bStatus;
			pPara->setValue(sData);
		}	
		break;
	case ITEM_SSCREWFINISH_REGION:
		if (bFlag)
		{
			bStatus = pPara->value<s_pSScrewFReg>().bEnabled;
		}
		else
		{
			s_pSScrewFReg sData = pPara->value<s_pSScrewFReg>();
			sData.bEnabled=bStatus;
			pPara->setValue(sData);
		}	
		break;
	case ITEM_FRLINNER_REGION:
		if (bFlag)
		{
			bStatus = pPara->value<s_pFRLInReg>().bEnabled;
		}
		else
		{
			s_pFRLInReg sData = pPara->value<s_pFRLInReg>();
			sData.bEnabled=bStatus;
			pPara->setValue(sData);
		}	
		break;
	case ITEM_FRLMIDDLE_REGION:
		if (bFlag)
		{
			bStatus = pPara->value<s_pFRLMidReg>().bEnabled;
		}
		else
		{
			s_pFRLMidReg sData = pPara->value<s_pFRLMidReg>();
			sData.bEnabled=bStatus;
			pPara->setValue(sData);
		}	
		break;
	case ITEM_FRLOUTER_REGION:
		if (bFlag)
		{
			bStatus = pPara->value<s_pFRLOutReg>().bEnabled;
		}
		else
		{
			s_pFRLOutReg sData = pPara->value<s_pFRLOutReg>();
			sData.bEnabled=bStatus;
			pPara->setValue(sData);
		}	
		break;
	case ITEM_FBLINNER_REGION:
		if (bFlag)
		{
			bStatus = pPara->value<s_pFBLInReg>().bEnabled;
		}
		else
		{
			s_pFBLInReg sData = pPara->value<s_pFBLInReg>();
			sData.bEnabled=bStatus;
			pPara->setValue(sData);
		}	
		break;
	case ITEM_FBLMIDDLE_REGION:
		if (bFlag)
		{
			bStatus = pPara->value<s_pFBLMidReg>().bEnabled;
		}
		else
		{
			s_pFBLMidReg sData = pPara->value<s_pFBLMidReg>();
			sData.bEnabled=bStatus;
			pPara->setValue(sData);
		}	
		break;
	case ITEM_BINNER_REGION:
		if (bFlag)
		{
			bStatus = pPara->value<s_pBInReg>().bEnabled;
		}
		else
		{
			s_pBInReg sData = pPara->value<s_pBInReg>();
			sData.bEnabled=bStatus;
			pPara->setValue(sData);
		}	
		break;
	case ITEM_BMIDDLE_REGION:
		if (bFlag)
		{
			bStatus = pPara->value<s_pBMidReg>().bEnabled;
		}
		else
		{
			s_pBMidReg sData = pPara->value<s_pBMidReg>();
			sData.bEnabled=bStatus;
			pPara->setValue(sData);
		}	
		break;
	case ITEM_BOUTER_REGION:
		if (bFlag)
		{
			bStatus = pPara->value<s_pBOutReg>().bEnabled;
		}
		else
		{
			s_pBOutReg sData = pPara->value<s_pBOutReg>();
			sData.bEnabled=bStatus;
			pPara->setValue(sData);
		}	
		break;
	case ITEM_SSIDEWALL_REGION:
		if (bFlag)
		{
			bStatus = pPara->value<s_pSSideReg>().bEnabled;
		}
		else
		{
			s_pSSideReg sData = pPara->value<s_pSSideReg>();
			sData.bEnabled=bStatus;
			pPara->setValue(sData);
		}	
		break;
	case ITEM_DISTURB_REGION:
		if (bFlag)
		{
			bStatus = pPara->value<s_pDistReg>().bEnabled;
		}
		else
		{
			s_pDistReg sData = pPara->value<s_pDistReg>();
			sData.bEnabled=bStatus;
			pPara->setValue(sData);
		}	
		break;
	case ITEM_FINISH_CONTOUR:
		if (bFlag)
		{
			bStatus = pPara->value<s_pFinCont>().bEnabled;
		}
		else
		{
			s_pFinCont sData = pPara->value<s_pFinCont>();
			sData.bEnabled=bStatus;
			pPara->setValue(sData);
		}	
		break;
	case ITEM_NECK_CONTOUR:
		if (bFlag)
		{
			bStatus = pPara->value<s_pNeckCont>().bEnabled;
		}
		else
		{
			s_pNeckCont sData = pPara->value<s_pNeckCont>();
			sData.bEnabled=bStatus;
			pPara->setValue(sData);
		}	
		break;
	case ITEM_BODY_CONTOUR:
		if (bFlag)
		{
			bStatus = pPara->value<s_pBodyCont>().bEnabled;
		}
		else
		{
			s_pBodyCont sData = pPara->value<s_pBodyCont>();
			sData.bEnabled=bStatus;
			pPara->setValue(sData);
		}	
		break;
	case ITEM_SBRISPOT_REGION:
		if (bFlag)
		{
			bStatus = pPara->value<s_pSBriSpotReg>().bEnabled;
		}
		else
		{
			s_pSBriSpotReg sData = pPara->value<s_pSBriSpotReg>();
			sData.bEnabled=bStatus;
			pPara->setValue(sData);
		}	
		break;
	case ITEM_BALL_REGION:
		if (bFlag)
		{
			bStatus = pPara->value<s_pBAllReg>().bEnabled;
		}
		else
		{
			s_pBAllReg sData = pPara->value<s_pBAllReg>();
			sData.bEnabled=bStatus;
			pPara->setValue(sData);
		}	
		break;
	case ITEM_CIRCLE_SIZE:
		if (bFlag)
		{
			bStatus = pPara->value<s_pCirSize>().bEnabled;
		}
		else
		{
			s_pCirSize sData = pPara->value<s_pCirSize>();
			sData.bEnabled=bStatus;
			pPara->setValue(sData);
		}	
		break;
	case ITEM_SBASE_REGION:
		if (bFlag)
		{
			bStatus = pPara->value<s_pSBaseReg>().bEnabled;
		}
		else
		{
			s_pSBaseReg sData = pPara->value<s_pSBaseReg>();
			sData.bEnabled=bStatus;
			pPara->setValue(sData);
		}	
		break;
	case ITEM_SBASECONVEX_REGION:
		if (bFlag)
		{
			bStatus = pPara->value<s_pSBaseConvexReg>().bEnabled;
		}
		else
		{
			s_pSBaseConvexReg sData = pPara->value<s_pSBaseConvexReg>();
			sData.bEnabled=bStatus;
			pPara->setValue(sData);
		}	
		break;
	default:
		break;
	}
}