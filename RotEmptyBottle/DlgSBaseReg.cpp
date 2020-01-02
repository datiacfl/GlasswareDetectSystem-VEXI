#include "DlgSBaseReg.h"

CDlgSBaseReg::CDlgSBaseReg(QWidget *parent,QVariant *pCheckPara,QVariant *pCheckShape)
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
	connect(ui.btnInCircle,SIGNAL(clicked()),this,SLOT(drawInCircle()));	
	connect(ui.btnOutCircle,SIGNAL(clicked()),this,SLOT(drawOutCircle()));	
	//初始化对话框
	initDialog();
	//设置“这是什么”文本
	setHelpTips();
}

CDlgSBaseReg::~CDlgSBaseReg()
{

}
void CDlgSBaseReg::initDialog()
{
	s_pSBaseReg pSBaseReg = pPara->value<s_pSBaseReg>();
	//初始化控件
	QStringList strlMethods;
	strlMethods<<tr("Circle")<<tr("Ring");
	ui.comboMethod->addItems(strlMethods);
	//显示参数
	ui.comboMethod->setCurrentIndex(pSBaseReg.nMethodIdx);
	ui.spinEdge->setValue(pSBaseReg.nEdge);
	ui.spinGray->setValue(pSBaseReg.nGray);
	ui.spinArea->setValue(pSBaseReg.nArea);
	ui.spinRab->setValue(pSBaseReg.fRab);	
	ui.spinSideDistance->setValue(pSBaseReg.nSideDistance);
}
void CDlgSBaseReg::methodChanged(int index)
{		
	//改变时直接赋值，方便显示正确区域-未点确定也保存，可能有误解
	s_pSBaseReg pSBaseReg = pPara->value<s_pSBaseReg>();
	pSBaseReg.nMethodIdx = index;
	pPara->setValue(pSBaseReg);
	ui.btnInCircle->setVisible(index==1);
}

void CDlgSBaseReg::setHelpTips()
{	
	ui.spinEdge->setWhatsThis(tr("The edge between defect region and background should be longer than the setting value,"
		"set <font color=red>the smaller,the more sensitive</font>"));
	ui.spinGray->setWhatsThis(tr("Adding the region that the gray value is bigger than the setting value of the gray to the defect region,"
		"in order to compensate that the big defect region isn't completely extracted by the contrast"));
	ui.spinArea->setWhatsThis(tr("Region is determined as a defect when its area is bigger than the setting value，"
		"and set<font color=red>the smaller,the more sensitive</font>"));
	ui.spinRab->setWhatsThis(tr("Region is determined as a defect when its anisometry is smaller than the setting value，"
		"the relationship of <i>area</i> and <i>length</i> is 'and'，both of them need to be satisfied，"
		"This is uesd to<font color = red>avoid stripes region that caused by reflective be reported as an error</font>"));
}

void CDlgSBaseReg::apply()
{
	//((MyLabelItem*)parentWidget())->bParaChanged = true;//通知父窗口模板参数改变
	pLabelItem->bParaChanged = true;
	//传入参数
	s_pSBaseReg pSBaseReg = pPara->value<s_pSBaseReg>();
	pSBaseReg.nMethodIdx = ui.comboMethod->currentIndex();
	pSBaseReg.nEdge = ui.spinEdge->value();
	pSBaseReg.nGray = ui.spinGray->value();
	pSBaseReg.nArea = ui.spinArea->value();
	pSBaseReg.fRab = ui.spinRab->value();
	pSBaseReg.nSideDistance = ui.spinSideDistance->value();
	pPara->setValue(pSBaseReg);
}

void CDlgSBaseReg::accept()
{
	apply();
	return QDialog::accept();
}

void CDlgSBaseReg::autoAccept()
{
	apply();
}

void CDlgSBaseReg::drawInCircle()
{
	s_oSBaseReg oSBaseReg = pShape->value<s_oSBaseReg>();
	pDlgMainWnd->adjustShape(this,oSBaseReg.oInCircle,DRAW_CIRCLE);
	pShape->setValue(oSBaseReg);
	pDlgMainWnd->displayObject(/*ui.comboMethod->currentIndex()*/);
	pDlgMainWnd->displayRoiHighLight(ITEM_SBASE_REGION,*pPara,*pShape); 
}

void CDlgSBaseReg::drawOutCircle()
{
	s_oSBaseReg oSBaseReg = pShape->value<s_oSBaseReg>();
	pDlgMainWnd->adjustShape(this,oSBaseReg.oOutCircle,DRAW_CIRCLE);
	pShape->setValue(oSBaseReg);
	pDlgMainWnd->displayObject(/*ui.comboMethod->currentIndex()*/);
	pDlgMainWnd->displayRoiHighLight(ITEM_SBASE_REGION,*pPara,*pShape); 
}
