#include "DlgFBLInReg.h"

CDlgFBLInReg::CDlgFBLInReg(QWidget *parent,QVariant *pCheckPara,QVariant *pCheckShape)
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
	connect(ui.btnInCircle,SIGNAL(clicked()),this,SLOT(drawInCircle()));
	connect(ui.btnOutCircle,SIGNAL(clicked()),this,SLOT(drawOutCircle()));
	connect(ui.btnPolygon,SIGNAL(clicked()),this,SLOT(drawPolygon()));
	//初始化对话框
	initDialog();
	//设置“这是什么”文本
	setHelpTips();
}

CDlgFBLInReg::~CDlgFBLInReg()
{

}
void CDlgFBLInReg::initDialog()
{
	s_pFBLInReg pFBLInReg = pPara->value<s_pFBLInReg>();
	//初始化控件
	ui.btnInCircle->setVisible(false);
	ui.btnOutCircle->setVisible(false);
	ui.spinEdge->setVisible(false);
	ui.spinArea->setVisible(false);
	ui.spinOpenSize->setVisible(false);
	ui.label_7->setVisible(false);
	ui.label_8->setVisible(false);
	ui.label_9->setVisible(false);
	//显示参数
	//ui.spinEdge->setValue(pFBLInReg.nEdge);
	//ui.spinArea->setValue(pFBLInReg.nArea);
	//ui.spinOpenSize->setValue(pFBLInReg.fOpenSize);
	ui.spinLOFEdge->setValue(pFBLInReg.nLOFEdge);
	ui.spinLOFEdgeH->setValue(pFBLInReg.nLOFEdgeH);
	ui.spinLOFArea->setValue(pFBLInReg.nLOFArea);
	ui.spinLOFHeight->setValue(pFBLInReg.nLOFHeight);
	ui.spinLOFOpenSize->setValue(pFBLInReg.fLOFOpenSize);
	ui.spinLOFPhiL->setValue(pFBLInReg.nLOFPhiL);
	ui.spinLOFPhiH->setValue(pFBLInReg.nLOFPhiH);
	ui.spinLOFMeanGray->setValue(pFBLInReg.nLOFMeanGray);

}

void CDlgFBLInReg::setHelpTips()
{	
}

void CDlgFBLInReg::apply()
{
	//((MyLabelItem*)parentWidget())->bParaChanged = true;//通知父窗口模板参数改变
	pLabelItem->bParaChanged = true;
	//传入参数
	s_pFBLInReg pFBLInReg = pPara->value<s_pFBLInReg>();
	//pFBLInReg.nEdge = ui.spinEdge->value();
	//pFBLInReg.nArea = ui.spinArea->value();
	//pFBLInReg.fOpenSize = ui.spinOpenSize->value();	
	pFBLInReg.nLOFEdge = ui.spinLOFEdge->value();
	pFBLInReg.nLOFEdgeH = ui.spinLOFEdgeH->value();
	pFBLInReg.nLOFArea = ui.spinLOFArea->value();
	pFBLInReg.nLOFHeight = ui.spinLOFHeight->value();
	pFBLInReg.fLOFOpenSize = ui.spinLOFOpenSize->value();	
	pFBLInReg.nLOFPhiL = ui.spinLOFPhiL->value();
	pFBLInReg.nLOFPhiH = ui.spinLOFPhiH->value();
	pFBLInReg.nLOFMeanGray = ui.spinLOFMeanGray->value();
	pPara->setValue(pFBLInReg);
}

void CDlgFBLInReg::accept()
{
	apply();
	return QDialog::accept();
}

void CDlgFBLInReg::autoAccept()
{
	apply();
}

void CDlgFBLInReg::drawInCircle()
{
	s_oFBLInReg oFBLInReg = pShape->value<s_oFBLInReg>();
	pDlgMainWnd->adjustShape(this,oFBLInReg.oInCircle,DRAW_CIRCLE);
	pShape->setValue(oFBLInReg);
	pDlgMainWnd->displayObject();
}

void CDlgFBLInReg::drawOutCircle()
{
	s_oFBLInReg oFBLInReg = pShape->value<s_oFBLInReg>();
	pDlgMainWnd->adjustShape(this,oFBLInReg.oOutCircle,DRAW_CIRCLE);
	pShape->setValue(oFBLInReg);
	pDlgMainWnd->displayObject();
}

void CDlgFBLInReg::drawPolygon()
{
	s_oFBLInReg oFBLInReg = pShape->value<s_oFBLInReg>();
	pDlgMainWnd->adjustShape(this,oFBLInReg.oPolygon,DRAW_POLYGON);
	pShape->setValue(oFBLInReg);
	pDlgMainWnd->displayObject();
}
