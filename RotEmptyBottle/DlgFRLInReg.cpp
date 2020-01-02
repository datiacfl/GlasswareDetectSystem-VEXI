#include "DlgFRLInReg.h"

CDlgFRLInReg::CDlgFRLInReg(QWidget *parent,QVariant *pCheckPara,QVariant *pCheckShape)
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

CDlgFRLInReg::~CDlgFRLInReg()
{

}
void CDlgFRLInReg::initDialog()
{
	s_pFRLInReg pFRLInReg = pPara->value<s_pFRLInReg>();
	//初始化控件	
	//显示参数
	ui.spinEdge->setValue(pFRLInReg.nEdge);
	ui.spinGray->setValue(pFRLInReg.nGray);
	ui.spinArea->setValue(pFRLInReg.nArea);
	ui.spinRadius->setValue(pFRLInReg.nInnerRadius);
	ui.spinOpenSize->setValue(pFRLInReg.fOpenSize);
	ui.checkOverPress->setChecked(pFRLInReg.bOverPress);
	ui.spinPressEdge->setValue(pFRLInReg.nPressEdge);
	ui.spinPressNum->setValue(pFRLInReg.nPressNum);
	ui.checkInBroken->setChecked(pFRLInReg.bInBroken);
	ui.spinBrokenEdge->setValue(pFRLInReg.nBrokenEdge);
	ui.spinBrokenArea->setValue(pFRLInReg.nBrokenArea);
	ui.spinBrokenMeanGray->setValue(pFRLInReg.nBrokenGrayMean);
}

void CDlgFRLInReg::setHelpTips()
{	
	ui.spinGray->setWhatsThis(tr("Gray value should be in between the setting value and 255，and set<font color=red>the smaller,the more sensitive</font>"));
}

void CDlgFRLInReg::apply()
{
	//((MyLabelItem*)parentWidget())->bParaChanged = true;//通知父窗口模板参数改变
	pLabelItem->bParaChanged = true;
	//传入参数
	s_pFRLInReg pFRLInReg = pPara->value<s_pFRLInReg>();
	pFRLInReg.nEdge = ui.spinEdge->value();
	pFRLInReg.nGray = ui.spinGray->value();
	pFRLInReg.nArea = ui.spinArea->value();
	pFRLInReg.nInnerRadius = ui.spinRadius->value();
	pFRLInReg.fOpenSize = ui.spinOpenSize->value();
	pFRLInReg.bOverPress = ui.checkOverPress->isChecked();
	pFRLInReg.nPressEdge = ui.spinPressEdge->value();
	pFRLInReg.nPressNum = ui.spinPressNum->value();
	pFRLInReg.bInBroken = ui.checkInBroken->isChecked();
	pFRLInReg.nBrokenEdge = ui.spinBrokenEdge->value();
	pFRLInReg.nBrokenArea = ui.spinBrokenArea->value();
	pFRLInReg.nBrokenGrayMean = ui.spinBrokenMeanGray->value();
	pPara->setValue(pFRLInReg);
}

void CDlgFRLInReg::accept()
{
	apply();
	return QDialog::accept();
}

void CDlgFRLInReg::autoAccept()
{
	apply();
}

void CDlgFRLInReg::drawInCircle()
{
	s_oFRLInReg oFRLInReg = pShape->value<s_oFRLInReg>();
	pDlgMainWnd->adjustShape(this,oFRLInReg.oInCircle,DRAW_CIRCLE);
	pShape->setValue(oFRLInReg);
	pDlgMainWnd->displayObject();
	pDlgMainWnd->displayRoiHighLight(ITEM_FRLINNER_REGION,*pPara,*pShape); 
}

void CDlgFRLInReg::drawOutCircle()
{
	s_oFRLInReg oFRLInReg = pShape->value<s_oFRLInReg>();
	pDlgMainWnd->adjustShape(this,oFRLInReg.oOutCircle,DRAW_CIRCLE);
	pShape->setValue(oFRLInReg);
	pDlgMainWnd->displayObject();
	pDlgMainWnd->displayRoiHighLight(ITEM_FRLINNER_REGION,*pPara,*pShape); 
}

void CDlgFRLInReg::autodraw()
{
	//是否有瓶口定位
	bool bLocate = false;
	double fInRadius;
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
					smallest_circle(oFinLoc.oInCircle,NULL,NULL,&fInRadius);
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
		pDlgMainWnd->displayRoiHighLight(ITEM_FRLINNER_REGION,*pPara,*pShape); 
		return;
	}	
	//更新区域
	s_oFRLInReg oFRLInReg = pShape->value<s_oFRLInReg>();
	gen_circle(&oFRLInReg.oOutCircle,pDlgMainWnd->pChecker->currentOri.Row,pDlgMainWnd->pChecker->currentOri.Col,fInRadius+25);
	gen_circle(&oFRLInReg.oInCircle	,pDlgMainWnd->pChecker->currentOri.Row,pDlgMainWnd->pChecker->currentOri.Col,fInRadius-25);
	pShape->setValue(oFRLInReg);
	pDlgMainWnd->displayObject();
	pDlgMainWnd->displayRoiHighLight(ITEM_FRLINNER_REGION,*pPara,*pShape); 
}
