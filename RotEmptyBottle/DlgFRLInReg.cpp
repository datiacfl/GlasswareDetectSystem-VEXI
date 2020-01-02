#include "DlgFRLInReg.h"

CDlgFRLInReg::CDlgFRLInReg(QWidget *parent,QVariant *pCheckPara,QVariant *pCheckShape)
	: CItemDlg(parent,pCheckPara,pCheckShape)
{
	ui.setupUi(this);
	//���ȷ��ȡ����Ӧ�ð�ť
	addCtrLayout();
	//���ô��ڴ�С
	setDlgSize();
	////�������ţ��ɲ��ֵ�����С
	//layout()->setSizeConstraint(QLayout::SetFixedSize);
	//������Ͽ��źŲ�	
	connect(ui.btnInCircle,SIGNAL(clicked()),this,SLOT(drawInCircle()));
	connect(ui.btnOutCircle,SIGNAL(clicked()),this,SLOT(drawOutCircle()));
	connect(ui.btnAutoDraw,SIGNAL(clicked()),this,SLOT(autodraw()));
	//��ʼ���Ի���
	initDialog();
	//���á�����ʲô���ı�
	setHelpTips();
}

CDlgFRLInReg::~CDlgFRLInReg()
{

}
void CDlgFRLInReg::initDialog()
{
	s_pFRLInReg pFRLInReg = pPara->value<s_pFRLInReg>();
	//��ʼ���ؼ�	
	//��ʾ����
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
	ui.spinGray->setWhatsThis(tr("Gray value should be in between the setting value and 255��and set<font color=red>the smaller,the more sensitive</font>"));
}

void CDlgFRLInReg::apply()
{
	//((MyLabelItem*)parentWidget())->bParaChanged = true;//֪ͨ������ģ������ı�
	pLabelItem->bParaChanged = true;
	//�������
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
	//�Ƿ���ƿ�ڶ�λ
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
				if (0 ==pFinLoc.nMethodIdx)//�ݻ��ιⶨλ��Ч
				{
					bLocate = true;
					s_oFinLoc oFinLoc = pDlgMainWnd->pChecker->vModelShapes[i].value<s_oFinLoc>();
					smallest_circle(oFinLoc.oInCircle,NULL,NULL,&fInRadius);
				}				
				break;
			}
		}
	}
	//�޶�λģ�鲻�Զ��ػ淵��
	if (!bLocate)
	{
		return;
	}
	//��λ
	Hobject tempobj;
	pDlgMainWnd->pChecker->rtnInfo = pDlgMainWnd->pChecker->fnFindCurrentPos(tempobj);
	if (0 != pDlgMainWnd->pChecker->rtnInfo.nType)
	{
		pDlgMainWnd->displayObject();
		pDlgMainWnd->displayRoiHighLight(ITEM_FRLINNER_REGION,*pPara,*pShape); 
		return;
	}	
	//��������
	s_oFRLInReg oFRLInReg = pShape->value<s_oFRLInReg>();
	gen_circle(&oFRLInReg.oOutCircle,pDlgMainWnd->pChecker->currentOri.Row,pDlgMainWnd->pChecker->currentOri.Col,fInRadius+25);
	gen_circle(&oFRLInReg.oInCircle	,pDlgMainWnd->pChecker->currentOri.Row,pDlgMainWnd->pChecker->currentOri.Col,fInRadius-25);
	pShape->setValue(oFRLInReg);
	pDlgMainWnd->displayObject();
	pDlgMainWnd->displayRoiHighLight(ITEM_FRLINNER_REGION,*pPara,*pShape); 
}
