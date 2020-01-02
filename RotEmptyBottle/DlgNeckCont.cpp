#include "DlgNeckCont.h"

CDlgNeckCont::CDlgNeckCont(QWidget *parent,QVariant *pCheckPara,QVariant *pCheckShape)
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
	connect(ui.btnDrawReg,SIGNAL(clicked()),this,SLOT(drawReg()));	
	//��ʼ���Ի���
	initDialog();
	//���á�����ʲô���ı�
	setHelpTips();
}

CDlgNeckCont::~CDlgNeckCont()
{

}
void CDlgNeckCont::initDialog()
{
	s_pNeckCont pNeckCont = pPara->value<s_pNeckCont>();
	//��ʼ���ؼ�
	//��ʾ����
	ui.spinThresh->setValue(pNeckCont.nThresh);
	ui.spinNeckHeiL->setValue(pNeckCont.nNeckHeiL);
	ui.spinNeckHeiH->setValue(pNeckCont.nNeckHeiH);
	ui.spinArea->setValue(pNeckCont.nArea);
}
void CDlgNeckCont::setHelpTips()
{	
	ui.spinThresh->setWhatsThis(tr("Set the sensitivity when searching edge points,<font color=red>smaller make more sensitive</font>"
		"but may easily influnced by light oil spots"));		
}

void CDlgNeckCont::apply()
{
	//((MyLabelItem*)parentWidget())->bParaChanged = true;//֪ͨ������ģ������ı�
	pLabelItem->bParaChanged = true;
	//�������
	s_pNeckCont pNeckCont = pPara->value<s_pNeckCont>();
	pNeckCont.nThresh = ui.spinThresh->value();
	pNeckCont.nNeckHeiL = ui.spinNeckHeiL->value();
	pNeckCont.nNeckHeiH = ui.spinNeckHeiH->value();
	pNeckCont.nArea = ui.spinArea->value();
	pPara->setValue(pNeckCont);
}

void CDlgNeckCont::accept()
{
	apply();
	return QDialog::accept();
}

void CDlgNeckCont::autoAccept()
{
	apply();
}

void CDlgNeckCont::drawReg()
{
	s_oNeckCont oNeckCont = pShape->value<s_oNeckCont>();
	pDlgMainWnd->adjustShape(this,oNeckCont.oCheckRegion,DRAW_RECTANGLE);
	pShape->setValue(oNeckCont);
	pDlgMainWnd->displayObject();
	pDlgMainWnd->displayRoiHighLight(ITEM_NECK_CONTOUR,*pPara,*pShape); 
}