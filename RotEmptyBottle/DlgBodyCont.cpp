#include "DlgBodyCont.h"

CDlgBodyCont::CDlgBodyCont(QWidget *parent,QVariant *pCheckPara,QVariant *pCheckShape)
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

CDlgBodyCont::~CDlgBodyCont()
{

}
void CDlgBodyCont::initDialog()
{
	s_pBodyCont pBodyCont = pPara->value<s_pBodyCont>();
	//��ʼ���ؼ�
	//��ʾ����
	ui.spinThresh->setValue(pBodyCont.nThresh);
	ui.spinWidth->setValue(pBodyCont.nWidth);
	ui.spinArea->setValue(pBodyCont.nArea);
}
void CDlgBodyCont::setHelpTips()
{	
	ui.spinThresh->setWhatsThis(tr("Set the sensitivity when searching edge points,<font color=red>smaller make more sensitive</font>"
		"but may easily influnced by light oil spots"));	
}

void CDlgBodyCont::apply()
{
	//((MyLabelItem*)parentWidget())->bParaChanged = true;//֪ͨ������ģ������ı�
	pLabelItem->bParaChanged = true;
	//�������
	s_pBodyCont pBodyCont = pPara->value<s_pBodyCont>();
	pBodyCont.nThresh = ui.spinThresh->value();
	pBodyCont.nWidth = ui.spinWidth->value();
	pBodyCont.nArea = ui.spinArea->value();
	pPara->setValue(pBodyCont);
}

void CDlgBodyCont::accept()
{
	apply();
	return QDialog::accept();
}

void CDlgBodyCont::autoAccept()
{
	apply();
}

void CDlgBodyCont::drawReg()
{
	s_oBodyCont oBodyCont = pShape->value<s_oBodyCont>();
	pDlgMainWnd->adjustShape(this,oBodyCont.oCheckRegion,DRAW_RECTANGLE);
	pShape->setValue(oBodyCont);
	pDlgMainWnd->displayObject();
	pDlgMainWnd->displayRoiHighLight(ITEM_BODY_CONTOUR,*pPara,*pShape); 
}