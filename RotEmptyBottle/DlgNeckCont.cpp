#include "DlgNeckCont.h"

CDlgNeckCont::CDlgNeckCont(QWidget *parent,QVariant *pCheckPara,QVariant *pCheckShape)
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
	//初始化对话框
	initDialog();
	//设置“这是什么”文本
	setHelpTips();
}

CDlgNeckCont::~CDlgNeckCont()
{

}
void CDlgNeckCont::initDialog()
{
	s_pNeckCont pNeckCont = pPara->value<s_pNeckCont>();
	//初始化控件
	//显示参数
	ui.spinThresh->setValue(pNeckCont.nThresh);
	ui.spinNeckHeiL->setValue(pNeckCont.nNeckHeiL);
	ui.spinNeckHeiH->setValue(pNeckCont.nNeckHeiH);
	ui.spinArea->setValue(pNeckCont.nArea);
}
void CDlgNeckCont::setHelpTips()
{	
	ui.spinThresh->setWhatsThis(tr("Set the sensitivity when searching edge points,<font color=red>smaller make more sensitive</font>"
		"but may easily influnced by light oil spots"));		
}

void CDlgNeckCont::apply()
{
	//((MyLabelItem*)parentWidget())->bParaChanged = true;//通知父窗口模板参数改变
	pLabelItem->bParaChanged = true;
	//传入参数
	s_pNeckCont pNeckCont = pPara->value<s_pNeckCont>();
	pNeckCont.nThresh = ui.spinThresh->value();
	pNeckCont.nNeckHeiL = ui.spinNeckHeiL->value();
	pNeckCont.nNeckHeiH = ui.spinNeckHeiH->value();
	pNeckCont.nArea = ui.spinArea->value();
	pPara->setValue(pNeckCont);
}

void CDlgNeckCont::accept()
{
	apply();
	return QDialog::accept();
}

void CDlgNeckCont::autoAccept()
{
	apply();
}

void CDlgNeckCont::drawReg()
{
	s_oNeckCont oNeckCont = pShape->value<s_oNeckCont>();
	pDlgMainWnd->adjustShape(this,oNeckCont.oCheckRegion,DRAW_RECTANGLE);
	pShape->setValue(oNeckCont);
	pDlgMainWnd->displayObject();
	pDlgMainWnd->displayRoiHighLight(ITEM_NECK_CONTOUR,*pPara,*pShape); 
}