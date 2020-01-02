#include "DlgFinCont.h"

CDlgFinCont::CDlgFinCont(QWidget *parent,QVariant *pCheckPara,QVariant *pCheckShape)
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
	//初始化对话框
	initDialog();
	//设置“这是什么”文本
	setHelpTips();
}

CDlgFinCont::~CDlgFinCont()
{

}
void CDlgFinCont::initDialog()
{
	s_pFinCont pFinCont = pPara->value<s_pFinCont>();
	//初始化控件	
	//显示参数
	ui.spinSubThresh->setValue(pFinCont.nSubThresh);
	ui.spinRegWidth->setValue(pFinCont.nRegWidth);
	ui.spinRegHeight->setValue(pFinCont.nRegHeight);
	ui.spinGapWidth->setValue(pFinCont.nGapWidth);
	ui.spinGapHeight->setValue(pFinCont.nGapHeight);
	ui.spinNotchHeight->setValue(pFinCont.nNotchHeight);
	ui.spinArea->setValue(pFinCont.nArea);
	ui.checkOverPress->setChecked(pFinCont.bCheckOverPress);
}

void CDlgFinCont::setHelpTips()
{
	ui.spinGapWidth->setWhatsThis(tr("Gap region isn't reported as a defect when size of the region is smaller than <i>width of gap</i>*<i>height of gap</i>"));
	ui.spinGapHeight->setWhatsThis(tr("Gap region isn't reported as a defect when size of the region is smaller than <i>width of gap</i>*<i>height of gap</i>"));
	ui.spinNotchHeight->setWhatsThis(tr("Detect defect by symmetry when the gap is located just off the center of the bottle,"
		"and notch is reported as a defect when <i>height of notch</i> is bigger than the setting value"));
}

void CDlgFinCont::apply()
{
	//((MyLabelItem*)parentWidget())->bParaChanged = true;//通知父窗口模板参数改变
	pLabelItem->bParaChanged = true;
	//传入参数
	s_pFinCont pFinCont = pPara->value<s_pFinCont>();
	pFinCont.nSubThresh = ui.spinSubThresh->value();
	pFinCont.nRegWidth = ui.spinRegWidth->value();
	pFinCont.nRegHeight = ui.spinRegHeight->value();
	pFinCont.nGapWidth = ui.spinGapWidth->value();
	pFinCont.nGapHeight = ui.spinGapHeight->value();
	pFinCont.nNotchHeight = ui.spinNotchHeight->value();
	pFinCont.nArea = ui.spinArea->value();
	pFinCont.bCheckOverPress = ui.checkOverPress->isChecked();
	pPara->setValue(pFinCont);
}

void CDlgFinCont::accept()
{
	apply();
	return QDialog::accept();
}

void CDlgFinCont::autoAccept()
{
	apply();
}