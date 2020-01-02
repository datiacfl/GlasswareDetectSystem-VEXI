#include "DlgBentNeck.h"

CDlgBentNeck::CDlgBentNeck(QWidget *parent,QVariant *pCheckPara,QVariant *pCheckShape)
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
	connect(ui.btnFinRect,SIGNAL(clicked()),this,SLOT(drawFinRect()));	
	//初始化对话框
	initDialog();
	//设置“这是什么”文本
	setHelpTips();
}

CDlgBentNeck::~CDlgBentNeck()
{

}

void CDlgBentNeck::initDialog()
{
	s_pBentNeck pBentNeck = pPara->value<s_pBentNeck>();
	//初始化控件	
	//显示参数
	ui.spinBentNeck->setValue(pBentNeck.nBentNeck);
}
void CDlgBentNeck::setHelpTips()
{	

}

void CDlgBentNeck::apply()
{
	//((MyLabelItem*)parentWidget())->bParaChanged = true;//通知父窗口模板参数改变
	pLabelItem->bParaChanged = true;
	//传入参数
	s_pBentNeck pBentNeck = pPara->value<s_pBentNeck>();
	pBentNeck.nBentNeck = ui.spinBentNeck->value();
	pPara->setValue(pBentNeck);
}

void CDlgBentNeck::accept()
{
	apply();
	return QDialog::accept();
}

void CDlgBentNeck::autoAccept()
{
	apply();
}

void CDlgBentNeck::drawFinRect()
{
	s_oBentNeck oBentNeck = pShape->value<s_oBentNeck>();
	pDlgMainWnd->adjustShape(this,oBentNeck.oFinRect,DRAW_RECTANGLE);
	pShape->setValue(oBentNeck);
	pDlgMainWnd->displayObject();
	pDlgMainWnd->displayRoiHighLight(ITEM_BENT_NECK,*pPara,*pShape); 
}