#include "DlgBOutReg.h"

CDlgBOutReg::CDlgBOutReg(QWidget *parent,QVariant *pCheckPara,QVariant *pCheckShape)
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

CDlgBOutReg::~CDlgBOutReg()
{

}
void CDlgBOutReg::initDialog()
{
	s_pBOutReg pBOutReg = pPara->value<s_pBOutReg>();
	//��ʼ���ؼ�			
	QStringList strlOperation;
	strlOperation<<tr("Or")<<tr("And");
	ui.comboOperation->addItems(strlOperation);
	//��ʾ����
	ui.spinEdge->setValue(pBOutReg.nEdge);
	ui.spinGray->setValue(pBOutReg.nGray);
	ui.spinArea->setValue(pBOutReg.nArea);
	ui.comboOperation->setCurrentIndex(pBOutReg.nOperation);
	ui.spinLen->setValue(pBOutReg.nLen);
	ui.spinLenMax->setValue(pBOutReg.nLenMax);
	ui.spinOpenSize->setValue(pBOutReg.fOpenSize);
	//���װ��ƿ���⻷����
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
	//((MyLabelItem*)parentWidget())->bParaChanged = true;//֪ͨ������ģ������ı�
	pLabelItem->bParaChanged = true;
	//�������
	s_pBOutReg pBOutReg = pPara->value<s_pBOutReg>();
	pBOutReg.nEdge = ui.spinEdge->value();
	pBOutReg.nGray = ui.spinGray->value();
	pBOutReg.nArea = ui.spinArea->value();
	pBOutReg.nOperation = ui.comboOperation->currentIndex();
	pBOutReg.nLen = ui.spinLen->value();
	pBOutReg.nLenMax = ui.spinLenMax->value();
	pBOutReg.fOpenSize = ui.spinOpenSize->value();
	//���װ��ƿ���⻷����
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
	//�Ƿ���ƿ�ڶ�λ
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
		pDlgMainWnd->displayRoiHighLight(ITEM_BOUTER_REGION,*pPara,*pShape); 
		return;
	}	
	//��������
	s_oBOutReg oBOutReg = pShape->value<s_oBOutReg>();
	gen_circle(&oBOutReg.oOutCircle,pDlgMainWnd->pChecker->currentOri.Row,pDlgMainWnd->pChecker->currentOri.Col,max(pDlgMainWnd->pChecker->currentOri.Radius+10,30));
	gen_circle(&oBOutReg.oInCircle,pDlgMainWnd->pChecker->currentOri.Row,pDlgMainWnd->pChecker->currentOri.Col,max(pDlgMainWnd->pChecker->currentOri.Radius-100,10));
	pShape->setValue(oBOutReg);
	pDlgMainWnd->displayObject();
	pDlgMainWnd->displayRoiHighLight(ITEM_BOUTER_REGION,*pPara,*pShape); 
}