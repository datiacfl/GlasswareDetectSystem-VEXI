#include "DlgFRLOutReg.h"

CDlgFRLOutReg::CDlgFRLOutReg(QWidget *parent,QVariant *pCheckPara,QVariant *pCheckShape)
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

CDlgFRLOutReg::~CDlgFRLOutReg()
{

}
void CDlgFRLOutReg::initDialog()
{
	s_pFRLOutReg pFRLOutReg = pPara->value<s_pFRLOutReg>();
	//初始化控件	
	//显示参数
	ui.spinEdge->setValue(pFRLOutReg.nEdge);
	ui.spinGray->setValue(pFRLOutReg.nGray);
	ui.spinArea->setValue(pFRLOutReg.nArea);
	ui.spinOpenSize->setValue(pFRLOutReg.fOpenSize);
	ui.checkBreach->setChecked(pFRLOutReg.bBreach);
	ui.spinBreachEdge->setValue(pFRLOutReg.nBreachEdge);
	ui.spinBreachWidth->setValue(pFRLOutReg.nBreachWidth);
	ui.spinBreachLen->setValue(pFRLOutReg.nBreachLen);
	ui.checkBrokenRing->setChecked(pFRLOutReg.bBrokenRing);
	ui.spinBrokenRingEdge->setValue(pFRLOutReg.nBrokenRingEdge);
	ui.spinBrokenRingGray->setValue(pFRLOutReg.nBrokenRingGray);
	ui.spinBrokenRingLen->setValue(pFRLOutReg.nBrokenRingLen);
	ui.spinBrokenOpenSize->setValue(pFRLOutReg.fBrokenOpenSize);

	//隐藏控件
	//ui.label_16->setVisible(false);
	//ui.spinBrokenOpenSize->setVisible(false);	
}

void CDlgFRLOutReg::setHelpTips()
{	
}

void CDlgFRLOutReg::apply()
{
	//((MyLabelItem*)parentWidget())->bParaChanged = true;//通知父窗口模板参数改变
	pLabelItem->bParaChanged = true;
	//传入参数
	s_pFRLOutReg pFRLOutReg = pPara->value<s_pFRLOutReg>();
	pFRLOutReg.nEdge = ui.spinEdge->value();
	pFRLOutReg.nGray = ui.spinGray->value();
	pFRLOutReg.nArea = ui.spinArea->value();
	pFRLOutReg.fOpenSize = ui.spinOpenSize->value();
	pFRLOutReg.bBreach = ui.checkBreach->isChecked();
	pFRLOutReg.nBreachEdge = ui.spinBreachEdge->value();
	pFRLOutReg.nBreachWidth = ui.spinBreachWidth->value();
	pFRLOutReg.nBreachLen = ui.spinBreachLen->value();
	pFRLOutReg.bBrokenRing = ui.checkBrokenRing->isChecked();
	pFRLOutReg.nBrokenRingEdge = ui.spinBrokenRingEdge->value();
	pFRLOutReg.nBrokenRingGray = ui.spinBrokenRingGray->value();
	pFRLOutReg.nBrokenRingLen = ui.spinBrokenRingLen->value();
	pFRLOutReg.fBrokenOpenSize = ui.spinBrokenOpenSize->value();
	pPara->setValue(pFRLOutReg);
}

void CDlgFRLOutReg::accept()
{
	apply();
	return QDialog::accept();
}

void CDlgFRLOutReg::autoAccept()
{
	apply();
}

void CDlgFRLOutReg::drawInCircle()
{
	s_oFRLOutReg oFRLOutReg = pShape->value<s_oFRLOutReg>();
	pDlgMainWnd->adjustShape(this,oFRLOutReg.oInCircle,DRAW_CIRCLE);
	pShape->setValue(oFRLOutReg);
	pDlgMainWnd->displayObject();
	pDlgMainWnd->displayRoiHighLight(ITEM_FRLOUTER_REGION,*pPara,*pShape); 
}

void CDlgFRLOutReg::drawOutCircle()
{
	s_oFRLOutReg oFRLOutReg = pShape->value<s_oFRLOutReg>();
	pDlgMainWnd->adjustShape(this,oFRLOutReg.oOutCircle,DRAW_CIRCLE);
	pShape->setValue(oFRLOutReg);
	pDlgMainWnd->displayObject();
	pDlgMainWnd->displayRoiHighLight(ITEM_FRLOUTER_REGION,*pPara,*pShape);
}

void CDlgFRLOutReg::autodraw()
{
	//是否有瓶口定位
	bool bLocate = false;
	double fOutRadius;
	int i;
	for (i=0;i<pDlgMainWnd->pChecker->vItemFlow.size();++i)
	{
		switch(pDlgMainWnd->pChecker->vItemFlow[i])
		{
		case ITEM_FINISH_LOCATE:
			{
				s_pFinLoc pFinLoc = pDlgMainWnd->pChecker->vModelParas[i].value<s_pFinLoc>();
				if (0 ==pFinLoc.nMethodIdx)//暂环形光定位有效
				{				
					bLocate = true;
					s_oFinLoc oFinLoc = pDlgMainWnd->pChecker->vModelShapes[i].value<s_oFinLoc>();
					smallest_circle(oFinLoc.oOutCircle,NULL,NULL,&fOutRadius);
				}
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
		pDlgMainWnd->displayRoiHighLight(ITEM_FRLOUTER_REGION,*pPara,*pShape);
		return;
	}	
	//更新区域
	s_oFRLOutReg oFRLOutReg = pShape->value<s_oFRLOutReg>();
	gen_circle(&oFRLOutReg.oOutCircle,pDlgMainWnd->pChecker->currentOri.Row,pDlgMainWnd->pChecker->currentOri.Col,fOutRadius+30);
	gen_circle(&oFRLOutReg.oInCircle,pDlgMainWnd->pChecker->currentOri.Row,pDlgMainWnd->pChecker->currentOri.Col,fOutRadius-30);
	pShape->setValue(oFRLOutReg);
	pDlgMainWnd->displayObject();
	pDlgMainWnd->displayRoiHighLight(ITEM_FRLOUTER_REGION,*pPara,*pShape);
}
