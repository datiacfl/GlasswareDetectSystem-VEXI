#include "DlgFRLMidReg.h"

CDlgFRLMidReg::CDlgFRLMidReg(QWidget *parent,QVariant *pCheckPara,QVariant *pCheckShape)
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
	connect(ui.radioButtonOldway,SIGNAL(clicked()),this,SLOT(displayParas()));
	connect(ui.radioButtonNeway,SIGNAL(clicked()),this,SLOT(displayParas()));
	//初始化对话框
	initDialog();
	//设置“这是什么”文本
	setHelpTips();
}

CDlgFRLMidReg::~CDlgFRLMidReg()
{

}
void CDlgFRLMidReg::initDialog()
{
	s_pFRLMidReg pFRLMidReg = pPara->value<s_pFRLMidReg>();
	//初始化控件	
	//显示参数
	ui.spinEdge->setValue(pFRLMidReg.nEdge);
	ui.spinGray->setValue(pFRLMidReg.nGray);
	ui.spinArea->setValue(pFRLMidReg.nArea);
	ui.spinLength->setValue(pFRLMidReg.nLen);
	ui.spinEdge_2->setValue(pFRLMidReg.nEdge_2);
	ui.spinGray_2->setValue(pFRLMidReg.nGray_2);
	ui.spinArea_2->setValue(pFRLMidReg.nArea_2);
	ui.spinLength_2->setValue(pFRLMidReg.nLen_2);
	ui.checkOpen->setChecked(pFRLMidReg.bOpen);
	ui.spinOpenSize->setValue(pFRLMidReg.fOpenSize);
	ui.checkPitting->setChecked(pFRLMidReg.bPitting);
	ui.spinPitEdge->setValue(pFRLMidReg.nPitEdge);
	ui.spinPitArea->setValue(pFRLMidReg.nPitArea);
	ui.spinPitNum->setValue(pFRLMidReg.nPitNum);
	ui.checkLOF->setChecked(pFRLMidReg.bLOF);
	ui.spinLOFEdge->setValue(pFRLMidReg.nLOFEdge);
	ui.spinLOFRab->setValue(pFRLMidReg.fLOFRab);
	ui.spinLOFLen->setValue(pFRLMidReg.nLOFLen);
	ui.spinLOFRab_In->setValue(pFRLMidReg.fLOFRab_In);
	ui.spinLOFLen_In->setValue(pFRLMidReg.nLOFLen_In);
	ui.spinLOFRab_Out->setValue(pFRLMidReg.fLOFRab_Out);
	ui.spinLOFLen_Out->setValue(pFRLMidReg.nLOFLen_Out);
	ui.spinLOFInDiaL->setValue(pFRLMidReg.nLOFDiaMin);
	ui.spinLOFInDiaH->setValue(pFRLMidReg.nLOFDiaMax);
	ui.spinLOFAngleOffset->setValue(pFRLMidReg.nLOFAngleOffset);
	ui.checkDeform->setChecked(pFRLMidReg.bDeform);
	ui.spinDeformGary->setValue(pFRLMidReg.nDeformGary);
	ui.spinDeformHei->setValue(pFRLMidReg.nDeformHei);
	ui.spinDeformCirWid->setValue(pFRLMidReg.nDeformCirWid);

    ui.radioButtonOldway->setChecked(pFRLMidReg.bLOFOldWay);
	ui.radioButtonNeway->setChecked(pFRLMidReg.bLOFNewWay);
	ui.spinLOFEdge_new->setValue(pFRLMidReg.nLOFEdge_new);
	ui.spinLOFWidth_new->setValue(pFRLMidReg.nLOFWidth_new);
	ui.spinLOFLen_new->setValue(pFRLMidReg.nLOFLen_new);
	ui.groupBox_oldway->setVisible(pFRLMidReg.bLOFOldWay);
	ui.groupBox_neway->setVisible(pFRLMidReg.bLOFNewWay);
}

void CDlgFRLMidReg::setHelpTips()
{	
	ui.spinArea->setWhatsThis(tr("Region is determined as a defect when its area is bigger than the setting value,and set <font color=red>"
		"the smaller,the more sensitive</font>,the relationship of <i>area</i> and <i>length</i> is 'or',that either one be satisfied will report an error"));
	ui.labelLOFBorder->setWhatsThis(tr("suitable for middle broken scissors,usually such scissors have shorter length, and with the contact edge"));
	ui.spinLOFLen->setWhatsThis(tr("Set length of scissors defect that it represent distance between inner and outter ring,set <font color=red>"
		"the smaller,the more sensitive</font>,the relationship of <i>anisometry</i> and <i>length</i> is 'and',that both of them need to be satisfied"));
}

void CDlgFRLMidReg::apply()
{
	//((MyLabelItem*)parentWidget())->bParaChanged = true;//通知父窗口模板参数改变
	pLabelItem->bParaChanged = true;
	//传入参数
	s_pFRLMidReg pFRLMidReg = pPara->value<s_pFRLMidReg>();
	pFRLMidReg.nEdge = ui.spinEdge->value();
	pFRLMidReg.nGray = ui.spinGray->value();
	pFRLMidReg.nArea = ui.spinArea->value();
	pFRLMidReg.nLen = ui.spinLength->value();
	pFRLMidReg.nEdge_2 = ui.spinEdge_2->value();
	pFRLMidReg.nGray_2 = ui.spinGray_2->value();
	pFRLMidReg.nArea_2 = ui.spinArea_2->value();
	pFRLMidReg.nLen_2 = ui.spinLength_2->value();
	pFRLMidReg.bOpen = ui.checkOpen->isChecked();
	pFRLMidReg.fOpenSize = ui.spinOpenSize->value();
	pFRLMidReg.bPitting = ui.checkPitting->isChecked();
	pFRLMidReg.nPitEdge = ui.spinPitEdge->value();
	pFRLMidReg.nPitArea = ui.spinPitArea->value();
	pFRLMidReg.nPitNum = ui.spinPitNum->value();
	pFRLMidReg.bLOF = ui.checkLOF->isChecked();
	pFRLMidReg.nLOFEdge = ui.spinLOFEdge->value();
	pFRLMidReg.fLOFRab = ui.spinLOFRab->value();
	pFRLMidReg.nLOFLen = ui.spinLOFLen->value();
	pFRLMidReg.fLOFRab_In = ui.spinLOFRab_In->value();
	pFRLMidReg.nLOFLen_In = ui.spinLOFLen_In->value();
	pFRLMidReg.fLOFRab_Out = ui.spinLOFRab_Out->value();
	pFRLMidReg.nLOFLen_Out = ui.spinLOFLen_Out->value();
	pFRLMidReg.nLOFDiaMin = ui.spinLOFInDiaL->value();
	pFRLMidReg.nLOFDiaMax = ui.spinLOFInDiaH->value();
	pFRLMidReg.nLOFAngleOffset = ui.spinLOFAngleOffset->value();
	pFRLMidReg.bDeform = ui.checkDeform->isChecked();
	pFRLMidReg.nDeformGary = ui.spinDeformGary->value();
	pFRLMidReg.nDeformHei = ui.spinDeformHei->value();
	pFRLMidReg.nDeformCirWid = ui.spinDeformCirWid->value();
	pFRLMidReg.bLOFOldWay = ui.radioButtonOldway->isChecked();
	pFRLMidReg.bLOFNewWay = ui.radioButtonNeway->isChecked();
	pFRLMidReg.nLOFEdge_new = ui.spinLOFEdge_new->value();
	pFRLMidReg.nLOFWidth_new = ui.spinLOFWidth_new->value();
	pFRLMidReg.nLOFLen_new = ui.spinLOFLen_new->value();
	pPara->setValue(pFRLMidReg);
}

void CDlgFRLMidReg::accept()
{
	apply();
	return QDialog::accept();
}

void CDlgFRLMidReg::autoAccept()
{
	apply();
}

void CDlgFRLMidReg::drawInCircle()
{
	s_oFRLMidReg oFRLMidReg = pShape->value<s_oFRLMidReg>();
	pDlgMainWnd->adjustShape(this,oFRLMidReg.oInCircle,DRAW_CIRCLE);
	pShape->setValue(oFRLMidReg);
	pDlgMainWnd->displayObject();
	pDlgMainWnd->displayRoiHighLight(ITEM_FRLMIDDLE_REGION,*pPara,*pShape); 
}

void CDlgFRLMidReg::drawOutCircle()
{
	s_oFRLMidReg oFRLMidReg = pShape->value<s_oFRLMidReg>();
	pDlgMainWnd->adjustShape(this,oFRLMidReg.oOutCircle,DRAW_CIRCLE);
	pShape->setValue(oFRLMidReg);
	pDlgMainWnd->displayObject();
	pDlgMainWnd->displayRoiHighLight(ITEM_FRLMIDDLE_REGION,*pPara,*pShape); 
}

void CDlgFRLMidReg::displayParas()
{
	if (ui.radioButtonOldway->isChecked())
	{
		ui.groupBox_oldway->setVisible(true);
		ui.groupBox_neway->setVisible(false);
	}
	if (ui.radioButtonNeway->isChecked())
	{
		ui.groupBox_oldway->setVisible(false);
		ui.groupBox_neway->setVisible(true);
	}
}

void CDlgFRLMidReg::autodraw()
{
	//是否有瓶口定位
	bool bLocate = false;
	double fInRadius,fOutRadius;
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
		pDlgMainWnd->displayRoiHighLight(ITEM_FRLMIDDLE_REGION,*pPara,*pShape); 
		return;
	}	
	//更新区域
	s_oFRLMidReg oFRLMidReg = pShape->value<s_oFRLMidReg>();
	gen_circle(&oFRLMidReg.oOutCircle,pDlgMainWnd->pChecker->currentOri.Row,pDlgMainWnd->pChecker->currentOri.Col,fOutRadius-25);
	gen_circle(&oFRLMidReg.oInCircle,pDlgMainWnd->pChecker->currentOri.Row,pDlgMainWnd->pChecker->currentOri.Col,fInRadius+20);
	pShape->setValue(oFRLMidReg);
	pDlgMainWnd->displayObject();
	pDlgMainWnd->displayRoiHighLight(ITEM_FRLMIDDLE_REGION,*pPara,*pShape); 
}
