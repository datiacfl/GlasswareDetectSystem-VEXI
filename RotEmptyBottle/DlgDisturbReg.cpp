#include "DlgDisturbReg.h"

CDlgDisturbReg::CDlgDisturbReg(QWidget *parent,QVariant *pCheckPara,QVariant *pCheckShape)
	: CItemDlg(parent,pCheckPara,pCheckShape)
{
	ui.setupUi(this);
	//添加确定取消、应用按钮
	addCtrLayout();
	//设置窗口大小
	setDlgSize();
	////禁用缩放，由布局调整大小
	//layout()->setSizeConstraint(QLayout::SetFixedSize);
	//连接组合框信号槽
	connect(ui.btnDrawReg,SIGNAL(clicked()),this,SLOT(drawDistReg()));
	connect(ui.btnPickUp,SIGNAL(clicked()),this,SLOT(PickUpReg()));
	connect(ui.comboRegType,SIGNAL(currentIndexChanged(int)),this,SLOT(typeChanged(int)));
	connect(ui.btnResetReg,SIGNAL(clicked()),this,SLOT(ResetReg()));
	connect(ui.comboShapeType,SIGNAL(currentIndexChanged(int)),this,SLOT(typeShapeChanged(int)));
	//初始化对话框
	initDialog();
	//设置“这是什么”文本
	setHelpTips();
}

CDlgDisturbReg::~CDlgDisturbReg()
{

}
void CDlgDisturbReg::initDialog()
{
	s_pDistReg pDistReg = pPara->value<s_pDistReg>();
	//初始化控件
	QStringList strlTypes;
	strlTypes<<tr("NotDetection")<<tr("TypicalDefects")<<tr("ExcludeStripes")<<tr("ExcludeBubbles");
	ui.comboRegType->addItems(strlTypes);
	QStringList strlShapeTypes;
	strlShapeTypes<<tr("Polygon")<<tr("Rect");
	ui.comboShapeType->addItems(strlShapeTypes);
	//显示参数
	ui.comboRegType->setCurrentIndex(pDistReg.nRegType);
	ui.comboShapeType->setCurrentIndex(pDistReg.nShapeType);
	ui.checkStripeSelf->setChecked(pDistReg.bStripeSelf);
	ui.spinOpenSize->setValue(pDistReg.fOpenSize);
	ui.checkMove->setChecked(pDistReg.bIsMove);
	ui.spinStripeMaskSize->setValue(pDistReg.nStripeMaskSize);
	ui.spinStripeMaskSize->setEnabled(pDistReg.bStripeSelf);
	ui.spinStripeEdge->setValue(pDistReg.nStripeEdge);
	ui.spinStripeEdge->setEnabled(pDistReg.bStripeSelf);
	ui.btnPickUp->setEnabled(pDistReg.bStripeSelf);
	ui.checkVertStripe->setChecked(pDistReg.bVertStripe);
	ui.spinVertAng->setValue(pDistReg.nVertAng);
	ui.spinVertWidthL->setValue(pDistReg.nVertWidthL);
	ui.spinVertWidthH->setValue(pDistReg.nVertWidthH);
	ui.spinVertRabL->setValue(pDistReg.fVertRabL);
	ui.spinVertRabH->setValue(pDistReg.fVertRabH);
	ui.spinVertInRadiusL->setValue(pDistReg.fVertInRadiusL);
	ui.spinVertInRadiusH->setValue(pDistReg.fVertInRadiusH);
	ui.checkHoriStripe->setChecked(pDistReg.bHoriStripe);
	ui.spinHoriAng->setValue(pDistReg.nHoriAng);
	ui.spinHoriWidthL->setValue(pDistReg.nHoriWidthL);
	ui.spinHoriWidthH->setValue(pDistReg.nHoriWidthH);
	ui.spinHoriRabL->setValue(pDistReg.fHoriRabL);
	ui.spinHoriRabH->setValue(pDistReg.fHoriRabH);
	ui.spinHoriInRadiusL->setValue(pDistReg.fHoriInRadiusL);
	ui.spinHoriInRadiusH->setValue(pDistReg.fHoriInRadiusH);
	ui.spinBubbleCir->setValue(pDistReg.fBubbleCir);
	ui.spinBubbleArea->setValue(pDistReg.nBubbleArea);
	ui.spinBubbleLowThre->setValue(pDistReg.nBubbleLowThre);
	ui.spinBubbleHighThre->setValue(pDistReg.nBubbleHighThre);
}
void CDlgDisturbReg::typeChanged(int index)
{	
	ui.groupNotdet->setVisible(index==0);
	ui.groupTypical->setVisible(index==1);
	ui.groupStripe->setVisible(index==2);
	ui.groupBubble->setVisible(index==3);
}
void CDlgDisturbReg::setHelpTips()
{		
}

void CDlgDisturbReg::apply()
{
	//((MyLabelItem*)parentWidget())->bParaChanged = true;//通知父窗口模板参数改变
	pLabelItem->bParaChanged = true;
	//传入参数
	s_pDistReg pDistReg = pPara->value<s_pDistReg>();
	pDistReg.bStripeSelf = ui.checkStripeSelf->isChecked();
	pDistReg.nRegType = ui.comboRegType->currentIndex();
	pDistReg.nShapeType = ui.comboShapeType->currentIndex();
	pDistReg.fOpenSize = ui.spinOpenSize->value();
	pDistReg.bIsMove = ui.checkMove->isChecked();
	pDistReg.nStripeEdge = ui.spinStripeEdge->value();
	pDistReg.nStripeMaskSize = ui.spinStripeMaskSize->value();
	pDistReg.bVertStripe = ui.checkVertStripe->isChecked();
	pDistReg.nVertAng = ui.spinVertAng->value();
	pDistReg.nVertWidthL = ui.spinVertWidthL->value();
	pDistReg.nVertWidthH = ui.spinVertWidthH->value();
	pDistReg.fVertRabL = ui.spinVertRabL->value();
	pDistReg.fVertRabH = ui.spinVertRabH->value();
	pDistReg.fVertInRadiusL = ui.spinVertInRadiusL->value();
	pDistReg.fVertInRadiusH = ui.spinVertInRadiusH->value();
	pDistReg.bHoriStripe = ui.checkHoriStripe->isChecked();
	pDistReg.nHoriAng = ui.spinHoriAng->value();
	pDistReg.nHoriWidthL = ui.spinHoriWidthL->value();
	pDistReg.nHoriWidthH = ui.spinHoriWidthH->value();
	pDistReg.fHoriRabL = ui.spinHoriRabL->value();
	pDistReg.fHoriRabH = ui.spinHoriRabH->value();
	pDistReg.fHoriInRadiusL = ui.spinHoriInRadiusL->value();
	pDistReg.fHoriInRadiusH = ui.spinHoriInRadiusH->value();
	pDistReg.fBubbleCir = ui.spinBubbleCir->value();
	pDistReg.nBubbleArea = ui.spinBubbleArea->value();
	pDistReg.nBubbleLowThre = ui.spinBubbleLowThre->value();
	pDistReg.nBubbleHighThre = ui.spinBubbleHighThre->value();
	pPara->setValue(pDistReg);
}

void CDlgDisturbReg::accept()
{
	apply();
	return QDialog::accept();
}

void CDlgDisturbReg::autoAccept()
{
	apply();
}

void CDlgDisturbReg::drawDistReg()
{
	s_oDistReg oDistReg = pShape->value<s_oDistReg>();
	if (ui.comboShapeType->currentIndex() == 0)
	{
		pDlgMainWnd->adjustShape(this,oDistReg.oDisturbReg,DRAW_POLYGON);  //默认多边形
	}
	else
	{
		pDlgMainWnd->adjustShape(this,oDistReg.oDisturbReg_Rect,DRAW_RECTANGLE); //新增矩形
	}
	pShape->setValue(oDistReg);
	pDlgMainWnd->displayObject();
	pDlgMainWnd->displayRoiHighLight(ITEM_DISTURB_REGION,*pPara,*pShape); 
}
void CDlgDisturbReg::PickUpReg()
{
	s_oDistReg oDistReg = pShape->value<s_oDistReg>();
	s_pDistReg pDistReg = pPara->value<s_pDistReg>();
	Hobject xldVal;
	if(pDistReg.nShapeType == 0)
	{
		copy_obj(oDistReg.oDisturbReg, &xldVal, 1, -1);
	}
	else
	{
		copy_obj(oDistReg.oDisturbReg_Rect, &xldVal, 1, -1);
	}
	select_shape_xld(xldVal, &xldVal, "area", "and", 1, 99999999);
	pDlgMainWnd->displayPickupDisReg(xldVal,ui.spinStripeMaskSize->value(),ui.spinStripeEdge->value(),pDistReg.strName,
		ui.checkHoriStripe->isChecked(),ui.spinHoriAng->value(),ui.spinHoriWidthL->value(),ui.spinHoriWidthH->value(),ui.spinHoriRabL->value(),ui.spinHoriRabH->value(),ui.spinHoriInRadiusL->value(),ui.spinHoriInRadiusH->value(),
		ui.checkVertStripe->isChecked(),ui.spinVertAng->value(),ui.spinVertWidthL->value(),ui.spinVertWidthH->value(),ui.spinVertRabL->value(),ui.spinVertRabH->value(),ui.spinVertInRadiusL->value(),ui.spinVertInRadiusH->value());
}

//2017.7-恢复默认区域
void CDlgDisturbReg::ResetReg()
{
	if (QMessageBox::No==QMessageBox::question(this,tr("Reset"),
		tr("The region will revert to the default shape,Do you want to continue?"),QMessageBox::Yes | QMessageBox::No))
		return;
	try
	{
		s_oDistReg oDistReg = pShape->value<s_oDistReg>();
		if (ui.comboShapeType->currentIndex() == 0)
		{
			gen_contour_polygon_xld(&oDistReg.oDisturbReg,
				HTuple(100).Concat(57).Concat(57).Concat(100).Concat(143).Concat(143).Concat(100),
				HTuple(50).Concat(75).Concat(125).Concat(150).Concat(125).Concat(75).Concat(50));  //默认多边形
		}
		else
		{
			gen_rectangle2_contour_xld(&oDistReg.oDisturbReg_Rect,55,55,0,45,45);
		} 
		//检测项形状改变标识符为真
		((MyLabelItem *)pDlgMainWnd->pItemLabel)->bShapeChanged = true;
		//模板原点更新为当前的原点！
		pDlgMainWnd->pChecker->modelOri = pDlgMainWnd->pChecker->currentOri;

		pShape->setValue(oDistReg);
		pDlgMainWnd->displayObject();
		pDlgMainWnd->displayRoiHighLight(ITEM_DISTURB_REGION,*pPara,*pShape);
	}
	catch(HException &e)
	{
		//Halcon异常		
		QString tempStr,strErr;
		tempStr=e.message;
		tempStr.remove(0,20);
		strErr = QString("abnormal:ResetReg,")+ tempStr;
		pDlgMainWnd->pChecker->writeErrDataRecord(strErr);
	}
	catch (...)
	{
		pDlgMainWnd->pChecker->writeErrDataRecord(QString("abnormal:ResetReg"));		
	}
}

void CDlgDisturbReg::typeShapeChanged(int index)
{	
	//传入参数
	s_pDistReg pDistReg = pPara->value<s_pDistReg>();
	pDistReg.nShapeType = index;
	pPara->setValue(pDistReg);
}