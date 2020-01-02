#include "DlgSBaseConvexReg.h"

CDlgSBaseConvexReg::CDlgSBaseConvexReg(QWidget *parent,QVariant *pCheckPara,QVariant *pCheckShape)
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
	connect(ui.btnDrawReg,SIGNAL(clicked()),this,SLOT(drawReg()));
	connect(ui.btnExpand,SIGNAL(clicked()),this,SLOT(expandDlg()));	
	connect(ui.btnResetReg,SIGNAL(clicked()),this,SLOT(ResetReg()));
	//初始化对话框
	initDialog();
	//设置“这是什么”文本
	setHelpTips();
}

CDlgSBaseConvexReg::~CDlgSBaseConvexReg()
{

}
void CDlgSBaseConvexReg::initDialog()
{
	s_pSBaseConvexReg pSBaseConvexReg = pPara->value<s_pSBaseConvexReg>();
	//初始化控件
	ui.groupAdvPara->setVisible(false);
	//显示参数
	ui.checkGenDefects->setChecked(pSBaseConvexReg.bGenDefects);
	ui.spinEdge->setValue(pSBaseConvexReg.nEdge);
	ui.spinGray->setValue(pSBaseConvexReg.nGray);
	ui.spinArea->setValue(pSBaseConvexReg.nArea);
	ui.spinLength->setValue(pSBaseConvexReg.nLength);
	ui.checkContDefects->setChecked(pSBaseConvexReg.bContDefects);
	//ui.spinContGray->setValue(pSBaseConvexReg.nContGray);
	ui.spinContArea->setValue(pSBaseConvexReg.nContArea);
	ui.spinContLength->setValue(pSBaseConvexReg.nContLength);
	ui.spinOpeningSize->setValue(pSBaseConvexReg.fOpeningSize);

	ui.checkGenRoi->setChecked(pSBaseConvexReg.bGenRoi);
	ui.spinRoiRatio->setValue(pSBaseConvexReg.fRoiRatio);
	ui.spinClosingWH->setValue(pSBaseConvexReg.nClosingWH);
	ui.spinGapWH->setValue(pSBaseConvexReg.nGapWH);
	ui.spinMaskSize->setValue(pSBaseConvexReg.nMaskSize);
	ui.label_closeSize->setVisible(false);
	ui.spinClosingSize->setValue(pSBaseConvexReg.fClosingSize);
	//瓶身普通区域不显示闭运算，只有在瓶口区域中有效
	ui.spinClosingSize->setVisible(false);
}
void CDlgSBaseConvexReg::expandDlg()
{
	QString strName = ui.btnExpand->text();
	if (strName=="+")
	{
		ui.btnExpand->setText("-");
		ui.groupAdvPara->setVisible(true);
	}
	else if (strName=="-")
	{
		ui.btnExpand->setText("+");
		ui.groupAdvPara->setVisible(false);
	}		
}
void CDlgSBaseConvexReg::setHelpTips()
{	
	ui.spinEdge->setWhatsThis(tr("The edge between defect region and background should be longer than the setting value,"
		"set <font color=red>the smaller,the more sensitive</font>"));
	ui.spinGray->setWhatsThis(tr("Adding the region that the gray value is smaller than the setting value of the gray to the defect region,"
		"in order to compensate that the big defect region isn't completely extracted by the contrast"));
	ui.spinArea->setWhatsThis(tr("Region is determined as a defect when its area is bigger than the setting value，"
		"and set<font color=red>the smaller,the more sensitive</font>"));
	ui.spinLength->setWhatsThis(tr("Region is determined as a defect when its length is bigger than the setting value，"
		"and set<font color=red>the smaller,the more sensitive</font>，the relationship of <i>area</i> and"
		"<i>length</i> is 'or',that either one be satisfied will report an error"));
	ui.checkGenRoi->setWhatsThis(tr("Pretreatment the region and generate a ROI, which filter the shadows on edge from the valid check region"));
	ui.spinRoiRatio->setWhatsThis(tr("Set the pretreatment ratio coefficient, the value between [0,1],<font color=red>set smaller make the valid check region bigger</font>"));
	ui.spinClosingWH->setWhatsThis(tr("Set the closing width and height on the edge of ROI, this is used to <font color=red>avoid defects as crack are filterd by ROI</font>"));
	ui.spinGapWH->setWhatsThis(tr("If the difference between ROI and original region are bigger (either width or height) than setted value, an error will report, as there may has an cirtical defects on the edge"));
	ui.spinMaskSize->setWhatsThis(tr("Set the width of the mask,this value influence the effect of <i>Edge</i>. As a rule of thumb,masksize should be twice of the maximum checkable defect's diameter,if the masksize is setted bigger, time consume will increased"));
	ui.spinClosingSize->setWhatsThis(tr("If the distance between two defects are smaller than setted value, they will merge as one defect. This is uesd to avoid some bubble defects escape because of incomplete extracion"));
}

void CDlgSBaseConvexReg::apply()
{
	pLabelItem->bParaChanged = true;
	//传入参数
	s_pSBaseConvexReg pSBaseConvexReg = pPara->value<s_pSBaseConvexReg>();
	pSBaseConvexReg.bGenDefects = ui.checkGenDefects->isChecked();
	pSBaseConvexReg.nEdge = ui.spinEdge->value();
	pSBaseConvexReg.nGray = ui.spinGray->value();
	pSBaseConvexReg.nArea = ui.spinArea->value();
	pSBaseConvexReg.nLength = ui.spinLength->value();

	pSBaseConvexReg.bContDefects = ui.checkContDefects->isChecked();
	//pSBaseConvexReg.nContGray = ui.spinContGray->value();
	pSBaseConvexReg.nContArea = ui.spinContArea->value();
	pSBaseConvexReg.nContLength = ui.spinContLength->value();
	pSBaseConvexReg.fOpeningSize = ui.spinOpeningSize->value();

	pSBaseConvexReg.bGenRoi = ui.checkGenRoi->isChecked();
	pSBaseConvexReg.fRoiRatio = ui.spinRoiRatio->value();
	pSBaseConvexReg.nClosingWH = ui.spinClosingWH->value();
	pSBaseConvexReg.nGapWH = ui.spinGapWH->value();
	pSBaseConvexReg.nMaskSize = ui.spinMaskSize->value();
	pSBaseConvexReg.fClosingSize = ui.spinClosingSize->value();
	pPara->setValue(pSBaseConvexReg);
}

void CDlgSBaseConvexReg::accept()
{
	apply();
	return QDialog::accept();
}

void CDlgSBaseConvexReg::autoAccept()
{
	apply();
}

void CDlgSBaseConvexReg::drawReg()
{
	s_oSBaseConvexReg oSBaseConvexReg = pShape->value<s_oSBaseConvexReg>();
	pDlgMainWnd->adjustShape(this,oSBaseConvexReg.oCheckRegion,DRAW_POLYGON);
	pShape->setValue(oSBaseConvexReg);
	pDlgMainWnd->displayObject();
	pDlgMainWnd->displayRoiHighLight(ITEM_SBASECONVEX_REGION,*pPara,*pShape); 
}

//2017.7-恢复默认区域
void CDlgSBaseConvexReg::ResetReg()
{
	if (QMessageBox::No==QMessageBox::question(this,tr("Reset"),
		tr("The region will revert to the default shape,Do you want to continue?"),QMessageBox::Yes | QMessageBox::No))
		return;
	try
	{
		s_oSBaseConvexReg oSBaseConvexReg = pShape->value<s_oSBaseConvexReg>();
		gen_contour_polygon_xld(&oSBaseConvexReg.oCheckRegion,
			HTuple(100).Concat(57).Concat(57).Concat(100).Concat(143).Concat(143).Concat(100),
			HTuple(50).Concat(75).Concat(125).Concat(150).Concat(125).Concat(75).Concat(50)); 
		//检测项形状改变标识符为真
		((MyLabelItem *)pDlgMainWnd->pItemLabel)->bShapeChanged = true;
		//模板原点更新为当前的原点！
		pDlgMainWnd->pChecker->modelOri = pDlgMainWnd->pChecker->currentOri;

		pShape->setValue(oSBaseConvexReg);
		pDlgMainWnd->displayObject();
		pDlgMainWnd->displayRoiHighLight(ITEM_SBASECONVEX_REGION,*pPara,*pShape); 
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