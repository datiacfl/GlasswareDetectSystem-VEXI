#include "DlgSScrewFReg.h"

CDlgSScrewFReg::CDlgSScrewFReg(QWidget *parent,QVariant *pCheckPara,QVariant *pCheckShape)
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

CDlgSScrewFReg::~CDlgSScrewFReg()
{

}
void CDlgSScrewFReg::initDialog()
{
	s_pSScrewFReg pSScrewFReg = pPara->value<s_pSScrewFReg>();
	//初始化控件
	QStringList strlTypes;
	strlTypes<<tr("Polygon")<<tr("Rect");
	ui.comboShapeType->addItems(strlTypes);
	//显示参数
	ui.comboShapeType->setCurrentIndex(pSScrewFReg.nShapeType);
	ui.spinEdge->setValue(pSScrewFReg.nEdge);
	ui.spinArea->setValue(pSScrewFReg.nArea);
	ui.spinLength->setValue(pSScrewFReg.nLength);
	ui.spinInnerDia->setValue(pSScrewFReg.nDia);
	ui.spinRab->setValue(pSScrewFReg.nRab);
}
void CDlgSScrewFReg::setHelpTips()
{		
	ui.spinArea->setWhatsThis(tr("Region is determined as a defective when the <i>area</i>, <i>length</i> "
		"and <i>width</i> are satisfied simultaneously"));	
}

void CDlgSScrewFReg::apply()
{
	//((MyLabelItem*)parentWidget())->bParaChanged = true;//通知父窗口模板参数改变
	pLabelItem->bParaChanged = true;
	//传入参数
	s_pSScrewFReg pSScrewFReg = pPara->value<s_pSScrewFReg>();
	pSScrewFReg.nShapeType = ui.comboShapeType->currentIndex();
	pSScrewFReg.nEdge = ui.spinEdge->value();
	pSScrewFReg.nArea = ui.spinArea->value();
	pSScrewFReg.nLength = ui.spinLength->value();
	pSScrewFReg.nDia = ui.spinInnerDia->value();
	pSScrewFReg.nRab = ui.spinRab->value();
	pPara->setValue(pSScrewFReg);
}

void CDlgSScrewFReg::accept()
{
	apply();
	return QDialog::accept();
}

void CDlgSScrewFReg::autoAccept()
{
	apply();
}

void CDlgSScrewFReg::drawReg()
{
	s_oSScrewFReg oSScrewFReg = pShape->value<s_oSScrewFReg>();
	if (ui.comboShapeType->currentIndex() == 0)
	{
		pDlgMainWnd->adjustShape(this,oSScrewFReg.oCheckRegion,DRAW_POLYGON);  //默认多边形
	}
	else
	{
		pDlgMainWnd->adjustShape(this,oSScrewFReg.oCheckRegion_Rect,DRAW_RECTANGLE); //新增矩形
	}
	pShape->setValue(oSScrewFReg);
	pDlgMainWnd->displayObject();
	pDlgMainWnd->displayRoiHighLight(ITEM_SSCREWFINISH_REGION,*pPara,*pShape); 
}

//2017.7-恢复默认区域
void CDlgSScrewFReg::ResetReg()
{
	if (QMessageBox::No==QMessageBox::question(this,tr("Reset"),
		tr("The region will revert to the default shape,Do you want to continue?"),QMessageBox::Yes | QMessageBox::No))
		return;
	try
	{
		s_oSScrewFReg oSScrewFReg = pShape->value<s_oSScrewFReg>(); 
		if (ui.comboShapeType->currentIndex() == 0)
		{
			gen_contour_polygon_xld(&oSScrewFReg.oCheckRegion,
				HTuple(100).Concat(57).Concat(57).Concat(100).Concat(143).Concat(143).Concat(100),
				HTuple(50).Concat(75).Concat(125).Concat(150).Concat(125).Concat(75).Concat(50)); //默认多边形
		}
		else
		{
			gen_rectangle2_contour_xld(&oSScrewFReg.oCheckRegion_Rect,55,55,0,45,45);
		}
		//检测项形状改变标识符为真
		((MyLabelItem *)pDlgMainWnd->pItemLabel)->bShapeChanged = true;
		//模板原点更新为当前的原点！
		pDlgMainWnd->pChecker->modelOri = pDlgMainWnd->pChecker->currentOri;

		pShape->setValue(oSScrewFReg);
		pDlgMainWnd->displayObject();
		pDlgMainWnd->displayRoiHighLight(ITEM_SSCREWFINISH_REGION,*pPara,*pShape);
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

void CDlgSScrewFReg::typeChanged(int index)
{	
	//传入参数
	s_pSScrewFReg pSScrewFReg = pPara->value<s_pSScrewFReg>();
	pSScrewFReg.nShapeType = index;
	pPara->setValue(pSScrewFReg);

}