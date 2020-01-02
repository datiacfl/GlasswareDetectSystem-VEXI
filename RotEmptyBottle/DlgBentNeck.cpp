#include "DlgBentNeck.h"

CDlgBentNeck::CDlgBentNeck(QWidget *parent,QVariant *pCheckPara,QVariant *pCheckShape)
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
	connect(ui.btnFinRect,SIGNAL(clicked()),this,SLOT(drawFinRect()));	
	//��ʼ���Ի���
	initDialog();
	//���á�����ʲô���ı�
	setHelpTips();
}

CDlgBentNeck::~CDlgBentNeck()
{

}

void CDlgBentNeck::initDialog()
{
	s_pBentNeck pBentNeck = pPara->value<s_pBentNeck>();
	//��ʼ���ؼ�	
	//��ʾ����
	ui.spinBentNeck->setValue(pBentNeck.nBentNeck);
}
void CDlgBentNeck::setHelpTips()
{	

}

void CDlgBentNeck::apply()
{
	//((MyLabelItem*)parentWidget())->bParaChanged = true;//֪ͨ������ģ������ı�
	pLabelItem->bParaChanged = true;
	//�������
	s_pBentNeck pBentNeck = pPara->value<s_pBentNeck>();
	pBentNeck.nBentNeck = ui.spinBentNeck->value();
	pPara->setValue(pBentNeck);
}

void CDlgBentNeck::accept()
{
	apply();
	return QDialog::accept();
}

void CDlgBentNeck::autoAccept()
{
	apply();
}

void CDlgBentNeck::drawFinRect()
{
	s_oBentNeck oBentNeck = pShape->value<s_oBentNeck>();
	pDlgMainWnd->adjustShape(this,oBentNeck.oFinRect,DRAW_RECTANGLE);
	pShape->setValue(oBentNeck);
	pDlgMainWnd->displayObject();
	pDlgMainWnd->displayRoiHighLight(ITEM_BENT_NECK,*pPara,*pShape); 
}