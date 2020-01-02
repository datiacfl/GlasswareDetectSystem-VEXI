#include "DlgFBLMidReg.h"

CDlgFBLMidReg::CDlgFBLMidReg(QWidget *parent,QVariant *pCheckPara,QVariant *pCheckShape)
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
	//��ʼ���Ի���
	initDialog();
	//���á�����ʲô���ı�
	setHelpTips();
}

CDlgFBLMidReg::~CDlgFBLMidReg()
{

}
void CDlgFBLMidReg::initDialog()
{
	s_pFBLMidReg pFBLMidReg = pPara->value<s_pFBLMidReg>();
	//��ʼ���ؼ�	
	//��ʾ����
	ui.spinEdge->setValue(pFBLMidReg.nEdge);
	ui.spinArea->setValue(pFBLMidReg.nArea);
	ui.checkShadow->setChecked(pFBLMidReg.bShadow);
	ui.spinShadowAng->setValue(pFBLMidReg.nShadowAng);	
}

void CDlgFBLMidReg::setHelpTips()
{	
}

void CDlgFBLMidReg::apply()
{
	//((MyLabelItem*)parentWidget())->bParaChanged = true;//֪ͨ������ģ������ı�
	pLabelItem->bParaChanged = true;
	//�������
	s_pFBLMidReg pFBLMidReg = pPara->value<s_pFBLMidReg>();
	pFBLMidReg.nEdge = ui.spinEdge->value();
	pFBLMidReg.nArea = ui.spinArea->value();
	pFBLMidReg.bShadow = ui.checkShadow->isChecked();
	pFBLMidReg.nShadowAng = ui.spinShadowAng->value();
	pPara->setValue(pFBLMidReg);
}

void CDlgFBLMidReg::accept()
{
	apply();
	return QDialog::accept();
}

void CDlgFBLMidReg::autoAccept()
{
	apply();
}

void CDlgFBLMidReg::drawInCircle()
{
	s_oFBLMidReg oFBLMidReg = pShape->value<s_oFBLMidReg>();
	pDlgMainWnd->adjustShape(this,oFBLMidReg.oInCircle,DRAW_CIRCLE);
	pShape->setValue(oFBLMidReg);
	pDlgMainWnd->displayObject();
}

void CDlgFBLMidReg::drawOutCircle()
{
	s_oFBLMidReg oFBLMidReg = pShape->value<s_oFBLMidReg>();
	pDlgMainWnd->adjustShape(this,oFBLMidReg.oOutCircle,DRAW_CIRCLE);
	pShape->setValue(oFBLMidReg);
	pDlgMainWnd->displayObject();
}
