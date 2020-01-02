#include "DlgVertAng.h"

CDlgVertAng::CDlgVertAng(QWidget *parent,QVariant *pCheckPara,QVariant *pCheckShape)
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
	connect(ui.btnCalib,SIGNAL(clicked()),this,SLOT(calibRuler()));	
	//��ʼ���Ի���
	initDialog();
	//���á�����ʲô���ı�
	setHelpTips();
}

CDlgVertAng::~CDlgVertAng()
{

}
void CDlgVertAng::initDialog()
{
	s_pVertAng pVertAng = pPara->value<s_pVertAng>();	
	//��ʼ���ؼ�	
	//��ʾ����
	ui.spinVertAng->setValue(pVertAng.fVertAng);
}
void CDlgVertAng::setHelpTips()
{	
	ui.btnCalib->setWhatsThis(tr("If the camrera is inclined, you can take the current image's angle as a vertical angle by calibration"));
}

void CDlgVertAng::apply()
{
	//((MyLabelItem*)parentWidget())->bParaChanged = true;//֪ͨ������ģ������ı�
	pLabelItem->bParaChanged = true;
	//�������
	s_pVertAng pVertAng = pPara->value<s_pVertAng>();
	pVertAng.fVertAng = ui.spinVertAng->value();
	pPara->setValue(pVertAng);
}

void CDlgVertAng::accept()
{
	apply();
	return QDialog::accept();
}

void CDlgVertAng::autoAccept()
{
	apply();
}

void CDlgVertAng::calibRuler()
{
	if (QMessageBox::No==QMessageBox::question(this,tr("Calibrated"),
		tr("Calibration basing at the current image��"),QMessageBox::Yes | QMessageBox::No))
		return;
	s_pVertAng pVertAng = pPara->value<s_pVertAng>();
	double dCurAng = pDlgMainWnd->pChecker->currentOri.Angle;
	tuple_deg(dCurAng,&dCurAng);
	if (dCurAng<0)
	{
		dCurAng+=180;
	}
	pVertAng.fRuler = dCurAng;
	pPara->setValue(pVertAng);
}