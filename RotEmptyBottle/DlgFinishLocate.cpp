#include "DlgFinishLocate.h"

CDlgFinishLocate::CDlgFinishLocate(QWidget *parent,QVariant *pCheckPara,QVariant *pCheckShape)
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
	connect(ui.comboMethod,SIGNAL(currentIndexChanged(int)),this,SLOT(methodChanged(int)));
	connect(ui.btnOutRing,SIGNAL(clicked()),this,SLOT(drawOutRing()));
	connect(ui.btnInRing,SIGNAL(clicked()),this,SLOT(drawInRing()));
	//初始化对话框
	initDialog();
	//设置“这是什么”文本
	setHelpTips();
}

CDlgFinishLocate::~CDlgFinishLocate()
{
	
}

void CDlgFinishLocate::initDialog()
{
	s_pFinLoc pFinLoc = pPara->value<s_pFinLoc>();
	//初始化控件
	QStringList strlMethods;
	strlMethods<<tr("RingLocation")<<tr("BackLocation")<<tr("OtherLocationZhangYu");
	ui.comboMethod->addItems(strlMethods);	
	//显示参数
	ui.comboMethod->setCurrentIndex(pFinLoc.nMethodIdx);
	ui.spinEdge->setValue(pFinLoc.nEdge);
	ui.spinOpenSize->setValue(pFinLoc.fOpenSize);
	ui.spinLowThres->setValue(pFinLoc.nLowThres);
	ui.spinHighThres->setValue(pFinLoc.nHighThres);
	ui.spinCenOffset->setValue(pFinLoc.nCenOffset);
	ui.spinFloatRange->setValue(pFinLoc.nFloatRange);	
}

void CDlgFinishLocate::methodChanged(int index)
{	
	ui.groupRing->setVisible(index==0);
	ui.groupBack->setVisible(index==1);
	ui.groupOther->setVisible(index==2);
	ui.btnOutRing->setVisible(index==0 || index==2);
}

void CDlgFinishLocate::setHelpTips()
{
	ui.spinEdge->setWhatsThis(tr("Set the edge when extracting inner and outter ring,set<font color=red>smaller make more sensitive</font>,"
		"but may easily influnced by curved reflective of outter ring,Set bigger make more strict,but may cause location failed"));
	ui.spinOpenSize->setWhatsThis(tr("Set the open computing scales to reduce the impact,when location is influnced by curved reflective of outter ring"));
	ui.spinFloatRange->setWhatsThis(tr("locate failed when width and hight of the inner mouth are bigger than the setting value,"
		"then need to adjust to mechanism"));
}

void CDlgFinishLocate::apply()
{
	//((MyLabelItem*)parentWidget())->bParaChanged = true;//通知父窗口模板参数改变
	pLabelItem->bParaChanged = true;
	//传入参数
	s_pFinLoc pFinLoc = pPara->value<s_pFinLoc>();
	pFinLoc.nMethodIdx = ui.comboMethod->currentIndex();
	pFinLoc.nEdge = ui.spinEdge->value();
	pFinLoc.fOpenSize = ui.spinOpenSize->value();
	pFinLoc.nLowThres = ui.spinLowThres->value();
	pFinLoc.nHighThres = ui.spinHighThres->value();
	pFinLoc.nCenOffset = ui.spinCenOffset->value();
	pFinLoc.nFloatRange = ui.spinFloatRange->value();
	pPara->setValue(pFinLoc);
}

void CDlgFinishLocate::accept()
{
	apply();
	return QDialog::accept();
}

void CDlgFinishLocate::autoAccept()
{
	apply();
}

void CDlgFinishLocate::drawOutRing()
{
	s_oFinLoc oFinLoc = pShape->value<s_oFinLoc>();
	pDlgMainWnd->adjustShape(this,oFinLoc.oOutCircle,DRAW_CIRCLE);
	pShape->setValue(oFinLoc);
	pDlgMainWnd->displayObject(ui.comboMethod->currentIndex());
}

void CDlgFinishLocate::drawInRing()
{
	s_oFinLoc oFinLoc = pShape->value<s_oFinLoc>();
	pDlgMainWnd->adjustShape(this,oFinLoc.oInCircle,DRAW_CIRCLE);
	pShape->setValue(oFinLoc);
	pDlgMainWnd->displayObject(ui.comboMethod->currentIndex());
}
