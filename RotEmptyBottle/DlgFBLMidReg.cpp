#include "DlgFBLMidReg.h"

CDlgFBLMidReg::CDlgFBLMidReg(QWidget *parent,QVariant *pCheckPara,QVariant *pCheckShape)
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
	//初始化对话框
	initDialog();
	//设置“这是什么”文本
	setHelpTips();
}

CDlgFBLMidReg::~CDlgFBLMidReg()
{

}
void CDlgFBLMidReg::initDialog()
{
	s_pFBLMidReg pFBLMidReg = pPara->value<s_pFBLMidReg>();
	//初始化控件	
	//显示参数
	ui.spinEdge->setValue(pFBLMidReg.nEdge);
	ui.spinArea->setValue(pFBLMidReg.nArea);
	ui.checkShadow->setChecked(pFBLMidReg.bShadow);
	ui.spinShadowAng->setValue(pFBLMidReg.nShadowAng);	
}

void CDlgFBLMidReg::setHelpTips()
{	
}

void CDlgFBLMidReg::apply()
{
	//((MyLabelItem*)parentWidget())->bParaChanged = true;//通知父窗口模板参数改变
	pLabelItem->bParaChanged = true;
	//传入参数
	s_pFBLMidReg pFBLMidReg = pPara->value<s_pFBLMidReg>();
	pFBLMidReg.nEdge = ui.spinEdge->value();
	pFBLMidReg.nArea = ui.spinArea->value();
	pFBLMidReg.bShadow = ui.checkShadow->isChecked();
	pFBLMidReg.nShadowAng = ui.spinShadowAng->value();
	pPara->setValue(pFBLMidReg);
}

void CDlgFBLMidReg::accept()
{
	apply();
	return QDialog::accept();
}

void CDlgFBLMidReg::autoAccept()
{
	apply();
}

void CDlgFBLMidReg::drawInCircle()
{
	s_oFBLMidReg oFBLMidReg = pShape->value<s_oFBLMidReg>();
	pDlgMainWnd->adjustShape(this,oFBLMidReg.oInCircle,DRAW_CIRCLE);
	pShape->setValue(oFBLMidReg);
	pDlgMainWnd->displayObject();
}

void CDlgFBLMidReg::drawOutCircle()
{
	s_oFBLMidReg oFBLMidReg = pShape->value<s_oFBLMidReg>();
	pDlgMainWnd->adjustShape(this,oFBLMidReg.oOutCircle,DRAW_CIRCLE);
	pShape->setValue(oFBLMidReg);
	pDlgMainWnd->displayObject();
}
