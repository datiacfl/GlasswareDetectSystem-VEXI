#include "DlgSBriSpotReg.h"

CDlgSBriSpotReg::CDlgSBriSpotReg(QWidget *parent,QVariant *pCheckPara,QVariant *pCheckShape)
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
	connect(ui.btnResetReg,SIGNAL(clicked()),this,SLOT(ResetReg()));
	connect(ui.comboShapeType,SIGNAL(currentIndexChanged(int)),this,SLOT(typeChanged(int)));
	//初始化对话框
	initDialog();
	//设置“这是什么”文本
	setHelpTips();
}

CDlgSBriSpotReg::~CDlgSBriSpotReg()
{

}

void CDlgSBriSpotReg::initDialog()
{
	s_pSBriSpotReg pSBriSpotReg = pPara->value<s_pSBriSpotReg>();
	//初始化控件
	QStringList strlTypes;
	strlTypes<<tr("Polygon")<<tr("Rect");
	ui.comboShapeType->addItems(strlTypes);
	//显示参数
	ui.comboShapeType->setCurrentIndex(pSBriSpotReg.nShapeType);
	ui.spinGray->setValue(pSBriSpotReg.nGray);
	ui.doubleSpinOpenRadius->setValue(pSBriSpotReg.fOpenRadius);
	ui.spinArea->setValue(pSBriSpotReg.nArea);
}

void CDlgSBriSpotReg::setHelpTips()
{
	ui.spinGray->setWhatsThis(tr("Adding the region that the gray value is bigger than the setting value of the gray to the defect region,"
		"in order to compensate that the big defect region isn't completely extracted by the contrast"));
	ui.spinArea->setWhatsThis(tr("Region is determined as a defect when its area is bigger than the setting value，"
		"and set<font color=red>the smaller,the more sensitive</font>"));
}

void CDlgSBriSpotReg::apply()
{
	//((MyLabelItem*)parentWidget())->bParaChanged = true;//通知父窗口模板参数改变
	pLabelItem->bParaChanged = true;
	//传入参数
	s_pSBriSpotReg pSBriSpotReg = pPara->value<s_pSBriSpotReg>();
	pSBriSpotReg.nShapeType = ui.comboShapeType->currentIndex();
	pSBriSpotReg.nGray = ui.spinGray->value();
	pSBriSpotReg.fOpenRadius = ui.doubleSpinOpenRadius->value();
	pSBriSpotReg.nArea = ui.spinArea->value();
	pPara->setValue(pSBriSpotReg);
}


void CDlgSBriSpotReg::accept()
{
	apply();
	return QDialog::accept();
}

void CDlgSBriSpotReg::autoAccept()
{
	apply();
}

void CDlgSBriSpotReg::drawReg()
{
	s_oSBriSpotReg oSBriSpotReg = pShape->value<s_oSBriSpotReg>();
	if (ui.comboShapeType->currentIndex() == 0)
	{
		pDlgMainWnd->adjustShape(this,oSBriSpotReg.oCheckRegion,DRAW_POLYGON);  //默认多边形
	}
	else
	{
		pDlgMainWnd->adjustShape(this,oSBriSpotReg.oCheckRegion_Rect,DRAW_RECTANGLE); //新增矩形
	}
	pShape->setValue(oSBriSpotReg);
	pDlgMainWnd->displayObject();
	pDlgMainWnd->displayRoiHighLight(ITEM_SBRISPOT_REGION,*pPara,*pShape); 
}

//2017.7-恢复默认区域
void CDlgSBriSpotReg::ResetReg()
{
	if (QMessageBox::No==QMessageBox::question(this,tr("Reset"),
		tr("The region will revert to the default shape,Do you want to continue?"),QMessageBox::Yes | QMessageBox::No))
		return;
	try
	{
		s_oSBriSpotReg oSBriSpotReg = pShape->value<s_oSBriSpotReg>();
		if (ui.comboShapeType->currentIndex() == 0)
		{
			gen_contour_polygon_xld(&oSBriSpotReg.oCheckRegion,
				HTuple(100).Concat(57).Concat(57).Concat(100).Concat(143).Concat(143).Concat(100),
				HTuple(50).Concat(75).Concat(125).Concat(150).Concat(125).Concat(75).Concat(50)); //默认多边形
		}
		else
		{
			gen_rectangle2_contour_xld(&oSBriSpotReg.oCheckRegion_Rect,55,55,0,45,45);
		}
		//检测项形状改变标识符为真
		((MyLabelItem *)pDlgMainWnd->pItemLabel)->bShapeChanged = true;
		//模板原点更新为当前的原点！
		pDlgMainWnd->pChecker->modelOri = pDlgMainWnd->pChecker->currentOri;

		pShape->setValue(oSBriSpotReg);
		pDlgMainWnd->displayObject();
		pDlgMainWnd->displayRoiHighLight(ITEM_SBRISPOT_REGION,*pPara,*pShape);
	}
	catch(HException &e)
	{
		//Halcon异常		
		QString tempStr,strErr;
		tempStr=e.message;
		tempStr.remove(0,20);
		strErr = QString("abnormal:ResetReg,")+ tempStr;
		pDlgMainWnd->pChecker->writeErrDataRecord(strErr);
	}
	catch (...)
	{
		pDlgMainWnd->pChecker->writeErrDataRecord(QString("abnormal:ResetReg"));		
	}
}

void CDlgSBriSpotReg::typeChanged(int index)
{	
	//传入参数
	s_pSBriSpotReg pSBriSpotReg = pPara->value<s_pSBriSpotReg>();
	pSBriSpotReg.nShapeType = index;
	pPara->setValue(pSBriSpotReg);

}