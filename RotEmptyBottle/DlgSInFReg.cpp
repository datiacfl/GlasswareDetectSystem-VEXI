#include "DlgSInFReg.h"

CDlgSInFReg::CDlgSInFReg(QWidget *parent,QVariant *pCheckPara,QVariant *pCheckShape)
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
	//初始化对话框
	initDialog();
	//设置“这是什么”文本
	setHelpTips();
}

CDlgSInFReg::~CDlgSInFReg()
{

}
void CDlgSInFReg::initDialog()
{
	s_pSInFReg pSInFReg = pPara->value<s_pSInFReg>();
	//初始化控件
	
	//显示参数
	ui.spinGray->setValue(pSInFReg.nGray);
	ui.spinArea->setValue(pSInFReg.nArea);
	ui.spinOpenSize->setValue(pSInFReg.fOpeningSize);
	if (pSInFReg.nPos==0)
	{
		ui.radioLeft->setChecked(true);
	}
	else if (pSInFReg.nPos==1)
	{
		ui.radioRight->setChecked(true);
	}	
}
void CDlgSInFReg::setHelpTips()
{		
}

void CDlgSInFReg::apply()
{
	//((MyLabelItem*)parentWidget())->bParaChanged = true;//通知父窗口模板参数改变
	pLabelItem->bParaChanged = true;
	//传入参数
	s_pSInFReg pSInFReg = pPara->value<s_pSInFReg>();
	pSInFReg.nGray = ui.spinGray->value();
	pSInFReg.nArea = ui.spinArea->value();
	pSInFReg.fOpeningSize = ui.spinOpenSize->value();
	if (ui.radioLeft->isChecked())
	{
		pSInFReg.nPos=0;
	}
	else if (ui.radioRight->isChecked())
	{
		pSInFReg.nPos=1;
	}	
	pPara->setValue(pSInFReg);
}

void CDlgSInFReg::accept()
{
	apply();
	return QDialog::accept();
}

void CDlgSInFReg::autoAccept()
{
	apply();
}

void CDlgSInFReg::drawReg()
{
	s_oSInFReg oSInFReg = pShape->value<s_oSInFReg>();
	pDlgMainWnd->adjustShape(this,oSInFReg.oCheckRegion,DRAW_POLYGON);
	pShape->setValue(oSInFReg);
	pDlgMainWnd->displayObject();
	pDlgMainWnd->displayRoiHighLight(ITEM_SINFINISH_REGION,*pPara,*pShape); 
}

//2017.7-恢复默认区域
void CDlgSInFReg::ResetReg()
{
	if (QMessageBox::No==QMessageBox::question(this,tr("Reset"),
		tr("The region will revert to the default shape,Do you want to continue?"),QMessageBox::Yes | QMessageBox::No))
		return;
	try
	{
		s_oSInFReg oSInFReg = pShape->value<s_oSInFReg>();
		gen_contour_polygon_xld(&oSInFReg.oCheckRegion,
			HTuple(100).Concat(57).Concat(57).Concat(100).Concat(143).Concat(143).Concat(100),
			HTuple(50).Concat(75).Concat(125).Concat(150).Concat(125).Concat(75).Concat(50)); 
		//检测项形状改变标识符为真
		((MyLabelItem *)pDlgMainWnd->pItemLabel)->bShapeChanged = true;
		//模板原点更新为当前的原点！
		pDlgMainWnd->pChecker->modelOri = pDlgMainWnd->pChecker->currentOri;

		pShape->setValue(oSInFReg);
		pDlgMainWnd->displayObject();
		pDlgMainWnd->displayRoiHighLight(ITEM_SINFINISH_REGION,*pPara,*pShape); 
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
