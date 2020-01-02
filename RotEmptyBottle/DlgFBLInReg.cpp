#include "DlgFBLInReg.h"

CDlgFBLInReg::CDlgFBLInReg(QWidget *parent,QVariant *pCheckPara,QVariant *pCheckShape)
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
	connect(ui.btnPolygon,SIGNAL(clicked()),this,SLOT(drawPolygon()));
	//��ʼ���Ի���
	initDialog();
	//���á�����ʲô���ı�
	setHelpTips();
}

CDlgFBLInReg::~CDlgFBLInReg()
{

}
void CDlgFBLInReg::initDialog()
{
	s_pFBLInReg pFBLInReg = pPara->value<s_pFBLInReg>();
	//��ʼ���ؼ�
	ui.btnInCircle->setVisible(false);
	ui.btnOutCircle->setVisible(false);
	ui.spinEdge->setVisible(false);
	ui.spinArea->setVisible(false);
	ui.spinOpenSize->setVisible(false);
	ui.label_7->setVisible(false);
	ui.label_8->setVisible(false);
	ui.label_9->setVisible(false);
	//��ʾ����
	//ui.spinEdge->setValue(pFBLInReg.nEdge);
	//ui.spinArea->setValue(pFBLInReg.nArea);
	//ui.spinOpenSize->setValue(pFBLInReg.fOpenSize);
	ui.spinLOFEdge->setValue(pFBLInReg.nLOFEdge);
	ui.spinLOFEdgeH->setValue(pFBLInReg.nLOFEdgeH);
	ui.spinLOFArea->setValue(pFBLInReg.nLOFArea);
	ui.spinLOFHeight->setValue(pFBLInReg.nLOFHeight);
	ui.spinLOFOpenSize->setValue(pFBLInReg.fLOFOpenSize);
	ui.spinLOFPhiL->setValue(pFBLInReg.nLOFPhiL);
	ui.spinLOFPhiH->setValue(pFBLInReg.nLOFPhiH);
	ui.spinLOFMeanGray->setValue(pFBLInReg.nLOFMeanGray);

}

void CDlgFBLInReg::setHelpTips()
{	
}

void CDlgFBLInReg::apply()
{
	//((MyLabelItem*)parentWidget())->bParaChanged = true;//֪ͨ������ģ������ı�
	pLabelItem->bParaChanged = true;
	//�������
	s_pFBLInReg pFBLInReg = pPara->value<s_pFBLInReg>();
	//pFBLInReg.nEdge = ui.spinEdge->value();
	//pFBLInReg.nArea = ui.spinArea->value();
	//pFBLInReg.fOpenSize = ui.spinOpenSize->value();	
	pFBLInReg.nLOFEdge = ui.spinLOFEdge->value();
	pFBLInReg.nLOFEdgeH = ui.spinLOFEdgeH->value();
	pFBLInReg.nLOFArea = ui.spinLOFArea->value();
	pFBLInReg.nLOFHeight = ui.spinLOFHeight->value();
	pFBLInReg.fLOFOpenSize = ui.spinLOFOpenSize->value();	
	pFBLInReg.nLOFPhiL = ui.spinLOFPhiL->value();
	pFBLInReg.nLOFPhiH = ui.spinLOFPhiH->value();
	pFBLInReg.nLOFMeanGray = ui.spinLOFMeanGray->value();
	pPara->setValue(pFBLInReg);
}

void CDlgFBLInReg::accept()
{
	apply();
	return QDialog::accept();
}

void CDlgFBLInReg::autoAccept()
{
	apply();
}

void CDlgFBLInReg::drawInCircle()
{
	s_oFBLInReg oFBLInReg = pShape->value<s_oFBLInReg>();
	pDlgMainWnd->adjustShape(this,oFBLInReg.oInCircle,DRAW_CIRCLE);
	pShape->setValue(oFBLInReg);
	pDlgMainWnd->displayObject();
}

void CDlgFBLInReg::drawOutCircle()
{
	s_oFBLInReg oFBLInReg = pShape->value<s_oFBLInReg>();
	pDlgMainWnd->adjustShape(this,oFBLInReg.oOutCircle,DRAW_CIRCLE);
	pShape->setValue(oFBLInReg);
	pDlgMainWnd->displayObject();
}

void CDlgFBLInReg::drawPolygon()
{
	s_oFBLInReg oFBLInReg = pShape->value<s_oFBLInReg>();
	pDlgMainWnd->adjustShape(this,oFBLInReg.oPolygon,DRAW_POLYGON);
	pShape->setValue(oFBLInReg);
	pDlgMainWnd->displayObject();
}
