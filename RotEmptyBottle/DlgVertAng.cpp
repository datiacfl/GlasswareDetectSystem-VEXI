#include "DlgVertAng.h"

CDlgVertAng::CDlgVertAng(QWidget *parent,QVariant *pCheckPara,QVariant *pCheckShape)
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
	connect(ui.btnCalib,SIGNAL(clicked()),this,SLOT(calibRuler()));	
	//初始化对话框
	initDialog();
	//设置“这是什么”文本
	setHelpTips();
}

CDlgVertAng::~CDlgVertAng()
{

}
void CDlgVertAng::initDialog()
{
	s_pVertAng pVertAng = pPara->value<s_pVertAng>();	
	//初始化控件	
	//显示参数
	ui.spinVertAng->setValue(pVertAng.fVertAng);
}
void CDlgVertAng::setHelpTips()
{	
	ui.btnCalib->setWhatsThis(tr("If the camrera is inclined, you can take the current image's angle as a vertical angle by calibration"));
}

void CDlgVertAng::apply()
{
	//((MyLabelItem*)parentWidget())->bParaChanged = true;//通知父窗口模板参数改变
	pLabelItem->bParaChanged = true;
	//传入参数
	s_pVertAng pVertAng = pPara->value<s_pVertAng>();
	pVertAng.fVertAng = ui.spinVertAng->value();
	pPara->setValue(pVertAng);
}

void CDlgVertAng::accept()
{
	apply();
	return QDialog::accept();
}

void CDlgVertAng::autoAccept()
{
	apply();
}

void CDlgVertAng::calibRuler()
{
	if (QMessageBox::No==QMessageBox::question(this,tr("Calibrated"),
		tr("Calibration basing at the current image？"),QMessageBox::Yes | QMessageBox::No))
		return;
	s_pVertAng pVertAng = pPara->value<s_pVertAng>();
	double dCurAng = pDlgMainWnd->pChecker->currentOri.Angle;
	tuple_deg(dCurAng,&dCurAng);
	if (dCurAng<0)
	{
		dCurAng+=180;
	}
	pVertAng.fRuler = dCurAng;
	pPara->setValue(pVertAng);
}