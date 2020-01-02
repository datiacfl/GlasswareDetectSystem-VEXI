#include "DlgCircleSize.h"

CDlgCircleSize::CDlgCircleSize(QWidget *parent,QVariant *pCheckPara,QVariant *pCheckShape)
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
	connect(ui.btnCircle,SIGNAL(clicked()),this,SLOT(drawCircle()));	
	connect(ui.btnCalib,SIGNAL(clicked()),this,SLOT(calibRuler()));
	//初始化对话框
	initDialog();
	//设置“这是什么”文本
	setHelpTips();
}

CDlgCircleSize::~CDlgCircleSize()
{

}

void CDlgCircleSize::initDialog()
{
	s_pCirSize pCircleSize = pPara->value<s_pCirSize>();	
	//初始化控件	
	//显示参数
	ui.spinEdge->setValue(pCircleSize.nEdge);
	ui.checkDiameter->setChecked(pCircleSize.bDia);
	ui.spinDiaLower->setValue(pCircleSize.fDiaLower);
	ui.spinDiaUpper->setValue(pCircleSize.fDiaUpper);
	ui.spinDiaReal->setValue(pCircleSize.fDiaReal);
	ui.spinDiaModify->setValue(pCircleSize.fDiaModify);
	if (pCircleSize.fDiaRuler==1)
	{
		ui.labelRuler->setText(tr("<font color=red>Uncalibrated！</font>"));
	} else
	{
		ui.labelRuler->setText(QString("1px=%1mm").arg(QString::number(pCircleSize.fDiaRuler,'f',5)));
	}
	ui.checkOvality->setChecked(pCircleSize.bOvality);
	ui.spinOvality->setValue(pCircleSize.fOvality);
}
void CDlgCircleSize::setHelpTips()
{		
	ui.spinEdge->setWhatsThis(tr("Set the sensitivity when searching the ring,<font color=red>smaller make more sensitive</font>"));
}

void CDlgCircleSize::apply()
{
	pLabelItem->bParaChanged = true;
	//传入参数
	s_pCirSize pCircleSize = pPara->value<s_pCirSize>();
	pCircleSize.nEdge = ui.spinEdge->value();
	pCircleSize.bDia = ui.checkDiameter->isChecked();
	pCircleSize.fDiaLower = ui.spinDiaLower->value();
	pCircleSize.fDiaUpper = ui.spinDiaUpper->value();
	pCircleSize.fDiaReal = ui.spinDiaReal->value();
	pCircleSize.fDiaModify = ui.spinDiaModify->value();
	pCircleSize.bOvality = ui.checkOvality->isChecked();
	pCircleSize.fOvality = ui.spinOvality->value();
	pPara->setValue(pCircleSize);
}

void CDlgCircleSize::accept()
{
	apply();
	return QDialog::accept();
}

void CDlgCircleSize::autoAccept()
{
	apply();
}

void CDlgCircleSize::calibRuler()
{
	if (QMessageBox::No==QMessageBox::question(this,tr("Calibrated"),
		tr("Whether to recalculate the scale？"),QMessageBox::Yes | QMessageBox::No))
		return;
	//s_pVertSize pVertSize = pPara->value<s_pVertSize>();
	//pVertSize.fReal = ui.spinReal->value();
	//pVertSize.nEdge = ui.spinEdge->value();
	//HTuple rowPt,colPt;
	//Hobject oLineSeg;
	//Hlong row1,col1,row2,col2;
	//smallest_rectangle1(pShape->value<s_oVertSize>().oSizeRect,&row1,&col1,&row2,&col2);
	//gen_region_line(&oLineSeg,row1,(col1+col2)/2,row2,(col1+col2)/2);
	//int nRtn = pDlgMainWnd->pChecker->findEdgePointDouble(pDlgMainWnd->imgShow,oLineSeg,&rowPt,&colPt,pVertSize.nEdge,T2B);
	//if (nRtn<2)
	//{
	//	ui.labelRuler->setText(tr("<font color=red>Calibration failure！</font>"));
	//	return;
	//}
	//pVertSize.fRuler = pVertSize.fReal/(rowPt[1].D()-rowPt[0].D());
	//ui.labelRuler->setText(QString("1px=%1mm").arg(QString::number(pVertSize.fRuler,'f',5)));
	//pPara->setValue(pVertSize);
	Hobject imgMean;
	Hobject regOutCir,regInCir,regCheck,regDyn,regCon,regTemp,regCircle;
	double Row,Column,dRadius,dRad1,dRad2;
	Hlong lNum;
	s_pCirSize pCirSize = pPara->value<s_pCirSize>();
	pCirSize.fDiaReal = ui.spinDiaReal->value();
	pCirSize.nEdge = ui.spinEdge->value();

	smallest_circle(pShape->value<s_oCirSize>().oCircle,&Row,&Column,&dRadius);
	mean_image(pDlgMainWnd->imgShow,&imgMean,31,31);
	dyn_threshold(pDlgMainWnd->imgShow,imgMean,&regDyn,pCirSize.nEdge,"light");
	closing_circle(regDyn,&regDyn,3.5);
	connection(regDyn,&regCon);
	gen_circle(&regOutCir,Row,Column,dRadius+35);
	gen_circle(&regInCir,Row,Column,dRadius-35);
	difference(regOutCir,regInCir,&regCheck);
	intersection(regCon,regCheck,&regTemp);
	count_obj(regTemp,&lNum);
	if (lNum==0)	
	{
		ui.labelRuler->setText(tr("<font color=red>Calibration failure！</font>"));
		return;
	}
	select_shape_std(regTemp,&regTemp,"max_area",70);
	shape_trans(regTemp,&regTemp,"convex");
	fill_up(regTemp,&regTemp);
	gen_contour_region_xld(regTemp,&regCircle,"center");
	select_shape_xld(regCircle,&regCircle,HTuple("contlength").Concat("circularity"),
		"and", HTuple(6.28*dRadius*0.8).Concat(0.8), HTuple(99999).Concat(1));
	count_obj(regCircle,&lNum);
	if (lNum==0)
	{
		ui.labelRuler->setText(tr("<font color=red>Calibration failure！</font>"));
		return;
	}
	fit_ellipse_contour_xld(regCircle,"fitzgibbon",-1,0,0,200,3,2,NULL,NULL,NULL,&dRad1,&dRad2,NULL,NULL,NULL);
	pCirSize.fDiaRuler = pCirSize.fDiaReal/(dRad1+dRad2);
	ui.labelRuler->setText(QString("1px=%1mm").arg(QString::number(pCirSize.fDiaRuler,'f',5)));
	pPara->setValue(pCirSize);
}
void CDlgCircleSize::drawCircle()
{
	s_oCirSize oCircleSize = pShape->value<s_oCirSize>();
	pDlgMainWnd->adjustShape(this,oCircleSize.oCircle,DRAW_CIRCLE);
	pShape->setValue(oCircleSize);
	pDlgMainWnd->displayObject();
	pDlgMainWnd->displayRoiHighLight(ITEM_CIRCLE_SIZE,*pPara,*pShape); 
}
