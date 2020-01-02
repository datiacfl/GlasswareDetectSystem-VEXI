#include "DlgBodyCont.h"

CDlgBodyCont::CDlgBodyCont(QWidget *parent,QVariant *pCheckPara,QVariant *pCheckShape)
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

CDlgBodyCont::~CDlgBodyCont()
{

}
void CDlgBodyCont::initDialog()
{
	s_pBodyCont pBodyCont = pPara->value<s_pBodyCont>();
	//初始化控件
	//显示参数
	ui.spinThresh->setValue(pBodyCont.nThresh);
	ui.spinWidth->setValue(pBodyCont.nWidth);
	ui.spinArea->setValue(pBodyCont.nArea);
}
void CDlgBodyCont::setHelpTips()
{	
	ui.spinThresh->setWhatsThis(tr("Set the sensitivity when searching edge points,<font color=red>smaller make more sensitive</font>"
		"but may easily influnced by light oil spots"));	
}

void CDlgBodyCont::apply()
{
	//((MyLabelItem*)parentWidget())->bParaChanged = true;//通知父窗口模板参数改变
	pLabelItem->bParaChanged = true;
	//传入参数
	s_pBodyCont pBodyCont = pPara->value<s_pBodyCont>();
	pBodyCont.nThresh = ui.spinThresh->value();
	pBodyCont.nWidth = ui.spinWidth->value();
	pBodyCont.nArea = ui.spinArea->value();
	pPara->setValue(pBodyCont);
}

void CDlgBodyCont::accept()
{
	apply();
	return QDialog::accept();
}

void CDlgBodyCont::autoAccept()
{
	apply();
}

void CDlgBodyCont::drawReg()
{
	s_oBodyCont oBodyCont = pShape->value<s_oBodyCont>();
	pDlgMainWnd->adjustShape(this,oBodyCont.oCheckRegion,DRAW_RECTANGLE);
	pShape->setValue(oBodyCont);
	pDlgMainWnd->displayObject();
	pDlgMainWnd->displayRoiHighLight(ITEM_BODY_CONTOUR,*pPara,*pShape); 
}