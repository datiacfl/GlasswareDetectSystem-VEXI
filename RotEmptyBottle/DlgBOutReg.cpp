#include "DlgBOutReg.h"

CDlgBOutReg::CDlgBOutReg(QWidget *parent,QVariant *pCheckPara,QVariant *pCheckShape)
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
	connect(ui.btnAutoDraw,SIGNAL(clicked()),this,SLOT(autodraw()));
	//初始化对话框
	initDialog();
	//设置“这是什么”文本
	setHelpTips();
}

CDlgBOutReg::~CDlgBOutReg()
{

}
void CDlgBOutReg::initDialog()
{
	s_pBOutReg pBOutReg = pPara->value<s_pBOutReg>();
	//初始化控件			
	QStringList strlOperation;
	strlOperation<<tr("Or")<<tr("And");
	ui.comboOperation->addItems(strlOperation);
	//显示参数
	ui.spinEdge->setValue(pBOutReg.nEdge);
	ui.spinGray->setValue(pBOutReg.nGray);
	ui.spinArea->setValue(pBOutReg.nArea);
	ui.comboOperation->setCurrentIndex(pBOutReg.nOperation);
	ui.spinLen->setValue(pBOutReg.nLen);
	ui.spinLenMax->setValue(pBOutReg.nLenMax);
	ui.spinOpenSize->setValue(pBOutReg.fOpenSize);
	//检灌装线瓶底外环条纹
	ui.checkStripe->setChecked(pBOutReg.bStrip);
	ui.spinStripeEdge->setValue(pBOutReg.nStripEdge);
	ui.spinStripeArea->setValue(pBOutReg.nStripArea);
	ui.spinStripeHeight->setValue(pBOutReg.nStripHeight);
	ui.spinStripeWidthL->setValue(pBOutReg.nStripWidthL);
	ui.spinStripeWidthH->setValue(pBOutReg.nStripWidthH);
	ui.spinStripeAnisometry->setValue(pBOutReg.fStripRab);
	ui.spinStripeAngleL->setValue(pBOutReg.nStripAngleL);
	ui.spinStripeAngleH->setValue(pBOutReg.nStripAngleH);
}

void CDlgBOutReg::setHelpTips()
{	
	
}

void CDlgBOutReg::apply()
{
	//((MyLabelItem*)parentWidget())->bParaChanged = true;//通知父窗口模板参数改变
	pLabelItem->bParaChanged = true;
	//传入参数
	s_pBOutReg pBOutReg = pPara->value<s_pBOutReg>();
	pBOutReg.nEdge = ui.spinEdge->value();
	pBOutReg.nGray = ui.spinGray->value();
	pBOutReg.nArea = ui.spinArea->value();
	pBOutReg.nOperation = ui.comboOperation->currentIndex();
	pBOutReg.nLen = ui.spinLen->value();
	pBOutReg.nLenMax = ui.spinLenMax->value();
	pBOutReg.fOpenSize = ui.spinOpenSize->value();
	//检灌装线瓶底外环条纹
	pBOutReg.bStrip = ui.checkStripe->isChecked();
	pBOutReg.nStripEdge = ui.spinStripeEdge->value();
	pBOutReg.nStripArea = ui.spinStripeArea->value();
	pBOutReg.nStripHeight = ui.spinStripeHeight->value();
	pBOutReg.nStripWidthL = ui.spinStripeWidthL->value();
	pBOutReg.nStripWidthH = ui.spinStripeWidthH->value();
	pBOutReg.fStripRab = ui.spinStripeAnisometry->value();
	pBOutReg.nStripAngleL = ui.spinStripeAngleL->value();
	pBOutReg.nStripAngleH = ui.spinStripeAngleH->value();

	pPara->setValue(pBOutReg);
}

void CDlgBOutReg::accept()
{
	apply();
	return QDialog::accept();
}

void CDlgBOutReg::autoAccept()
{
	apply();
}

void CDlgBOutReg::drawInCircle()
{
	s_oBOutReg oBOutReg = pShape->value<s_oBOutReg>();
	pDlgMainWnd->adjustShape(this,oBOutReg.oInCircle,DRAW_CIRCLE);
	pShape->setValue(oBOutReg);
	pDlgMainWnd->displayObject();
	pDlgMainWnd->displayRoiHighLight(ITEM_BOUTER_REGION,*pPara,*pShape); 
}
void CDlgBOutReg::drawOutCircle()
{
	s_oBOutReg oBOutReg = pShape->value<s_oBOutReg>();
	pDlgMainWnd->adjustShape(this,oBOutReg.oOutCircle,DRAW_CIRCLE);
	pShape->setValue(oBOutReg);
	pDlgMainWnd->displayObject();
	pDlgMainWnd->displayRoiHighLight(ITEM_BOUTER_REGION,*pPara,*pShape); 
}

void CDlgBOutReg::autodraw()
{
	//是否有瓶口定位
	bool bLocate = false;
	int i;
	for (i=0;i<pDlgMainWnd->pChecker->vItemFlow.size();++i)
	{
		switch(pDlgMainWnd->pChecker->vItemFlow[i])
		{
		case ITEM_BASE_LOCATE:
			{
				s_pBaseLoc pBaseLoc = pDlgMainWnd->pChecker->vModelParas[i].value<s_pBaseLoc>();
				bLocate = true;
				break;
			}
		}
	}
	//无定位模块不自动重绘返回
	if (!bLocate)
	{
		return;
	}
	//定位
	Hobject tempobj;
	pDlgMainWnd->pChecker->rtnInfo = pDlgMainWnd->pChecker->fnFindCurrentPos(tempobj);
	if (0 != pDlgMainWnd->pChecker->rtnInfo.nType)
	{
		pDlgMainWnd->displayObject();
		pDlgMainWnd->displayRoiHighLight(ITEM_BOUTER_REGION,*pPara,*pShape); 
		return;
	}	
	//更新区域
	s_oBOutReg oBOutReg = pShape->value<s_oBOutReg>();
	gen_circle(&oBOutReg.oOutCircle,pDlgMainWnd->pChecker->currentOri.Row,pDlgMainWnd->pChecker->currentOri.Col,max(pDlgMainWnd->pChecker->currentOri.Radius+10,30));
	gen_circle(&oBOutReg.oInCircle,pDlgMainWnd->pChecker->currentOri.Row,pDlgMainWnd->pChecker->currentOri.Col,max(pDlgMainWnd->pChecker->currentOri.Radius-100,10));
	pShape->setValue(oBOutReg);
	pDlgMainWnd->displayObject();
	pDlgMainWnd->displayRoiHighLight(ITEM_BOUTER_REGION,*pPara,*pShape); 
}