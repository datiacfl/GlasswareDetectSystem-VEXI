#include "DlgFinCont.h"

CDlgFinCont::CDlgFinCont(QWidget *parent,QVariant *pCheckPara,QVariant *pCheckShape)
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
	//��ʼ���Ի���
	initDialog();
	//���á�����ʲô���ı�
	setHelpTips();
}

CDlgFinCont::~CDlgFinCont()
{

}
void CDlgFinCont::initDialog()
{
	s_pFinCont pFinCont = pPara->value<s_pFinCont>();
	//��ʼ���ؼ�	
	//��ʾ����
	ui.spinSubThresh->setValue(pFinCont.nSubThresh);
	ui.spinRegWidth->setValue(pFinCont.nRegWidth);
	ui.spinRegHeight->setValue(pFinCont.nRegHeight);
	ui.spinGapWidth->setValue(pFinCont.nGapWidth);
	ui.spinGapHeight->setValue(pFinCont.nGapHeight);
	ui.spinNotchHeight->setValue(pFinCont.nNotchHeight);
	ui.spinArea->setValue(pFinCont.nArea);
	ui.checkOverPress->setChecked(pFinCont.bCheckOverPress);
}

void CDlgFinCont::setHelpTips()
{
	ui.spinGapWidth->setWhatsThis(tr("Gap region isn't reported as a defect when size of the region is smaller than <i>width of gap</i>*<i>height of gap</i>"));
	ui.spinGapHeight->setWhatsThis(tr("Gap region isn't reported as a defect when size of the region is smaller than <i>width of gap</i>*<i>height of gap</i>"));
	ui.spinNotchHeight->setWhatsThis(tr("Detect defect by symmetry when the gap is located just off the center of the bottle,"
		"and notch is reported as a defect when <i>height of notch</i> is bigger than the setting value"));
}

void CDlgFinCont::apply()
{
	//((MyLabelItem*)parentWidget())->bParaChanged = true;//֪ͨ������ģ������ı�
	pLabelItem->bParaChanged = true;
	//�������
	s_pFinCont pFinCont = pPara->value<s_pFinCont>();
	pFinCont.nSubThresh = ui.spinSubThresh->value();
	pFinCont.nRegWidth = ui.spinRegWidth->value();
	pFinCont.nRegHeight = ui.spinRegHeight->value();
	pFinCont.nGapWidth = ui.spinGapWidth->value();
	pFinCont.nGapHeight = ui.spinGapHeight->value();
	pFinCont.nNotchHeight = ui.spinNotchHeight->value();
	pFinCont.nArea = ui.spinArea->value();
	pFinCont.bCheckOverPress = ui.checkOverPress->isChecked();
	pPara->setValue(pFinCont);
}

void CDlgFinCont::accept()
{
	apply();
	return QDialog::accept();
}

void CDlgFinCont::autoAccept()
{
	apply();
}