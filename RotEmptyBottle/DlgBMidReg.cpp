#include "DlgBMidReg.h"

CDlgBMidReg::CDlgBMidReg(QWidget *parent,QVariant *pCheckPara,QVariant *pCheckShape)
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

CDlgBMidReg::~CDlgBMidReg()
{

}
void CDlgBMidReg::initDialog()
{
	s_pBMidReg pBMidReg = pPara->value<s_pBMidReg>();
	//初始化控件	
	QStringList strlOperation1,strlOperation2;
	strlOperation1<<tr("Or")<<tr("And");
	strlOperation2<<tr("Or")<<tr("And");
	ui.comboOperation1->addItems(strlOperation1);
	ui.comboOperation2->addItems(strlOperation2);
	//显示参数
	ui.spinEdge1->setValue(pBMidReg.nEdge1);
	ui.spinArea1->setValue(pBMidReg.nArea1);
	ui.comboOperation1->setCurrentIndex(pBMidReg.nOperation1);
	ui.spinLen1->setValue(pBMidReg.nLen1);
	ui.spinMeanGray1->setValue(pBMidReg.nMeanGray1);
	ui.spinEdge2->setValue(pBMidReg.nEdge2);
	ui.spinArea2->setValue(pBMidReg.nArea2);
	ui.comboOperation2->setCurrentIndex(pBMidReg.nOperation2);
	ui.spinLen2->setValue(pBMidReg.nLen2);
	ui.spinMeanGray2->setValue(pBMidReg.nMeanGray2);
	ui.checkOpen->setChecked(pBMidReg.bOpen);
	ui.spinOpenSize->setValue(pBMidReg.fOpenSize);
	ui.checkArc->setChecked(pBMidReg.bArc);
	ui.spinArcEdge->setValue(pBMidReg.nArcEdge);
	ui.spinArcWidth->setValue(pBMidReg.nArcWidth);
}

void CDlgBMidReg::setHelpTips()
{	
	ui.labelCondition1->setWhatsThis(tr("This is used to check defects with <font color=red> smaller Edge but longger Area/Length</font>"));
	ui.labelCondition2->setWhatsThis(tr("This is used to check defects with <font color=red> bigger Edge but smaller Area/Length</font>"));
	ui.comboOperation1->setWhatsThis(tr("Specity the relationship between <i>Area</i> and <i>Length</i>,'or' means that either one be satisfied "
		"will report an error, 'and' means both of them need to be satisfied"));
	ui.comboOperation2->setWhatsThis(tr("Specity the relationship between <i>Area</i> and <i>Length</i>,'or' means that either one be satisfied "
		"will report an error, 'and' means both of them need to be satisfied"));
	ui.checkArc->setWhatsThis(tr("This is used to filter arc on the bottom, to avoid it be reported as an error"));
}

void CDlgBMidReg::apply()
{
	//((MyLabelItem*)parentWidget())->bParaChanged = true;//通知父窗口模板参数改变
	pLabelItem->bParaChanged = true;
	//传入参数
	s_pBMidReg pBMidReg = pPara->value<s_pBMidReg>();
	pBMidReg.nEdge1 = ui.spinEdge1->value();
	pBMidReg.nArea1 = ui.spinArea1->value();
	pBMidReg.nOperation1 = ui.comboOperation1->currentIndex();
	pBMidReg.nLen1 = ui.spinLen1->value();
	pBMidReg.nMeanGray1 = ui.spinMeanGray1->value();
	pBMidReg.nEdge2 = ui.spinEdge2->value();
	pBMidReg.nArea2 = ui.spinArea2->value();
	pBMidReg.nOperation2 = ui.comboOperation2->currentIndex();
	pBMidReg.nLen2 = ui.spinLen2->value();
	pBMidReg.nMeanGray2 = ui.spinMeanGray2->value();
	pBMidReg.bOpen = ui.checkOpen->isChecked();
	pBMidReg.fOpenSize = ui.spinOpenSize->value();
	pBMidReg.bArc = ui.checkArc->isChecked();
	pBMidReg.nArcEdge = ui.spinArcEdge->value();
	pBMidReg.nArcWidth = ui.spinArcWidth->value();
	pPara->setValue(pBMidReg);
}

void CDlgBMidReg::accept()
{
	apply();
	return QDialog::accept();
}

void CDlgBMidReg::autoAccept()
{
	apply();
}

void CDlgBMidReg::drawInCircle()
{
	s_oBMidReg oBMidReg = pShape->value<s_oBMidReg>();
	pDlgMainWnd->adjustShape(this,oBMidReg.oInCircle,DRAW_CIRCLE);
	pShape->setValue(oBMidReg);
	pDlgMainWnd->displayObject();
	pDlgMainWnd->displayRoiHighLight(ITEM_BMIDDLE_REGION,*pPara,*pShape); 
}
void CDlgBMidReg::drawOutCircle()
{
	s_oBMidReg oBMidReg = pShape->value<s_oBMidReg>();
	pDlgMainWnd->adjustShape(this,oBMidReg.oOutCircle,DRAW_CIRCLE);
	pShape->setValue(oBMidReg);
	pDlgMainWnd->displayObject();
	pDlgMainWnd->displayRoiHighLight(ITEM_BMIDDLE_REGION,*pPara,*pShape);
}