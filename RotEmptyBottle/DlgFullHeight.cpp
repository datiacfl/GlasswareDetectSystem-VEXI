#include "DlgFullHeight.h"

extern bool g_bSizeComplex;

CDlgFullHeight::CDlgFullHeight(QWidget *parent,QVariant *pCheckPara,QVariant *pCheckShape)
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
	connect(ui.btnSizeRect,SIGNAL(clicked()),this,SLOT(drawSizeRect()));
	connect(ui.btnCalib,SIGNAL(clicked()),this,SLOT(calibRuler()));
	connect(ui.spinSizeGroup,SIGNAL(valueChanged(int)),this,SLOT(changeGroupName(int)));
	//初始化对话框
	initDialog();
	//设置“这是什么”文本
	setHelpTips();
}

CDlgFullHeight::~CDlgFullHeight()
{

}
void CDlgFullHeight::initDialog()
{
	s_pFullHeight pFullHeight = pPara->value<s_pFullHeight>();	
	//初始化控件	
	ui.groupBoxComplex->setVisible(g_bSizeComplex);
	//if (pFullHeight.bComplex)
	{
		ui.spinSizeGroup->setEnabled(false);
	}
	//ui.spinSizeGroup->setValue(pFullHeight.nSizeGroup);
	//changeGroupName(pFullHeight.nSizeGroup);
	//显示参数
	ui.spinEdge->setValue(pFullHeight.nEdge);
	ui.spinLower->setValue(pFullHeight.fLower);
	ui.spinUpper->setValue(pFullHeight.fUpper);
	ui.spinReal->setValue(pFullHeight.fReal);
	ui.spinModify->setValue(pFullHeight.fModify);
	if (pFullHeight.fRuler==1)
	{
		ui.labelRuler->setText(tr("<font color=red>Uncalibrated！</font>"));
	} else
	{
		ui.labelRuler->setText(QString("1px=%1mm").arg(QString::number(pFullHeight.fRuler,'f',5)));
	}
}
void CDlgFullHeight::setHelpTips()
{		
	ui.spinEdge->setWhatsThis(tr("Set the sensitivity when searching edge points,<font color=red>smaller make more sensitive</font>"));
	ui.spinReal->setWhatsThis(tr("Real height of the bottle"));	
}

void CDlgFullHeight::apply()
{
	//((MyLabelItem*)parentWidget())->bParaChanged = true;//通知父窗口模板参数改变
	pLabelItem->bParaChanged = true;
	//传入参数
	s_pFullHeight pFullHeight = pPara->value<s_pFullHeight>();
	//pFullHeight.nSizeGroup = ui.spinSizeGroup->value();
	pFullHeight.nEdge = ui.spinEdge->value();
	pFullHeight.fLower = ui.spinLower->value();
	pFullHeight.fUpper = ui.spinUpper->value();
	pFullHeight.fModify = ui.spinModify->value();
	pPara->setValue(pFullHeight);
}

void CDlgFullHeight::accept()
{
	apply();
	return QDialog::accept();
}

void CDlgFullHeight::autoAccept()
{
	apply();
}

void CDlgFullHeight::calibRuler()
{
	if (QMessageBox::No==QMessageBox::question(this,tr("Calibrated"),
		tr("Whether to recalculate the scale？"),QMessageBox::Yes | QMessageBox::No))
		return;
	s_pFullHeight pFullHeight = pPara->value<s_pFullHeight>();
	pFullHeight.fReal = ui.spinReal->value();
	pFullHeight.nEdge = ui.spinEdge->value();
	HTuple rowPt,colPt;
	Hobject oLineSeg;
	double row1,col1,row2,col2;
	smallest_rectangle1_xld(pShape->value<s_oFullHeight>().oSizeRect,&row1,&col1,&row2,&col2);
	gen_region_line(&oLineSeg,row1,(col1+col2)/2,row2,(col1+col2)/2);
	int nRtn = pDlgMainWnd->pChecker->findEdgePointSingle(pDlgMainWnd->imgShow,oLineSeg,&rowPt,&colPt,pFullHeight.nEdge,T2B);
	if (nRtn<1)
	{
		ui.labelRuler->setText(tr("<font color=red>Calibration failure！</font>"));
		return;
	}
	pFullHeight.fRuler = pFullHeight.fReal/(row2-rowPt[0].D());
	ui.labelRuler->setText(QString("1px=%1mm").arg(QString::number(pFullHeight.fRuler,'f',5)));
	pPara->setValue(pFullHeight);
}
void CDlgFullHeight::drawSizeRect()
{
	s_oFullHeight oFullHeight = pShape->value<s_oFullHeight>();
	pDlgMainWnd->adjustShape(this,oFullHeight.oSizeRect,DRAW_RECTANGLE);
	pShape->setValue(oFullHeight);
	pDlgMainWnd->displayObject();
	pDlgMainWnd->displayRoiHighLight(ITEM_FULL_HEIGHT,*pPara,*pShape); 
}

void CDlgFullHeight::changeGroupName(int index)
{
	ui.labelGroupName->setText(tr("<font color=blue>%1</font>").arg(index));
}
