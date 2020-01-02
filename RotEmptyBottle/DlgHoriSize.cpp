#include "DlgHoriSize.h"

extern bool g_bSizeComplex;

CDlgHoriSize::CDlgHoriSize(QWidget *parent,QVariant *pCheckPara,QVariant *pCheckShape)
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
	connect(ui.btnSizeRect,SIGNAL(clicked()),this,SLOT(drawSizeRect()));
	connect(ui.btnCalib,SIGNAL(clicked()),this,SLOT(calibRuler()));
	connect(ui.spinSizeGroup,SIGNAL(valueChanged(int)),this,SLOT(changeGroupName(int)));
	//��ʼ���Ի���
	initDialog();
	//���á�����ʲô���ı�
	setHelpTips();
}

CDlgHoriSize::~CDlgHoriSize()
{

}

void CDlgHoriSize::initDialog()
{
	s_pHoriSize pHoriSize = pPara->value<s_pHoriSize>();	
	//��ʼ���ؼ�
	ui.groupBoxComplex->setVisible(g_bSizeComplex);
	if (pHoriSize.bComplex)
	{
		ui.spinSizeGroup->setEnabled(false);
	}
	ui.spinSizeGroup->setValue(pHoriSize.nSizeGroup);
	changeGroupName(pHoriSize.nSizeGroup);
	//��ʾ����
	ui.spinEdge->setValue(pHoriSize.nEdge);
	ui.spinLower->setValue(pHoriSize.fLower);
	ui.spinUpper->setValue(pHoriSize.fUpper);
	ui.spinModify->setValue(pHoriSize.fModify);
	ui.spinReal->setValue(pHoriSize.fReal);
	if (pHoriSize.fRuler==1)
	{
		ui.labelRuler->setText(tr("<font color=red>Uncalibrated��</font>"));
	} else
	{
		ui.labelRuler->setText(QString("1px=%1mm").arg(QString::number(pHoriSize.fRuler,'f',5)));
	}
}
void CDlgHoriSize::setHelpTips()
{	
	ui.spinEdge->setWhatsThis(tr("Set the sensitivity when searching edge points,<font color=red>smaller make more sensitive</font>"));
	ui.spinReal->setWhatsThis(tr("Real distance between the two endpoints of the bottle"));
}

void CDlgHoriSize::apply()
{
	//((MyLabelItem*)parentWidget())->bParaChanged = true;//֪ͨ������ģ������ı�
	pLabelItem->bParaChanged = true;
	//�������
	s_pHoriSize pHoriSize = pPara->value<s_pHoriSize>();
	pHoriSize.nSizeGroup = ui.spinSizeGroup->value();
	pHoriSize.nEdge = ui.spinEdge->value();
	pHoriSize.fLower = ui.spinLower->value();
	pHoriSize.fUpper = ui.spinUpper->value();
	pHoriSize.fModify = ui.spinModify->value();
	pPara->setValue(pHoriSize);
}

void CDlgHoriSize::accept()
{
	apply();
	return QDialog::accept();
}

void CDlgHoriSize::autoAccept()
{
	apply();
}

void CDlgHoriSize::calibRuler()
{
	if (QMessageBox::No==QMessageBox::question(this,tr("Calibrated"),
		tr("Whether to recalculate the scale��"),QMessageBox::Yes | QMessageBox::No))
		return;
	s_pHoriSize pHoriSize = pPara->value<s_pHoriSize>();
	pHoriSize.fReal = ui.spinReal->value();
	pHoriSize.nEdge = ui.spinEdge->value();
	HTuple rowPt,colPt;
	Hobject oLineSeg;
	double row1,col1,row2,col2;
	smallest_rectangle1_xld(pShape->value<s_oHoriSize>().oSizeRect,&row1,&col1,&row2,&col2);
	gen_region_line(&oLineSeg,(row1+row2)/2,col1,(row1+row2)/2,col2);
	int nRtn = pDlgMainWnd->pChecker->findEdgePointDouble(pDlgMainWnd->imgShow,oLineSeg,&rowPt,&colPt,pHoriSize.nEdge);
	if (nRtn<2)
	{
		ui.labelRuler->setText(tr("<font color=red>Calibration failure��</font>"));
		return;
	}
	pHoriSize.fRuler = pHoriSize.fReal/(colPt[1].D()-colPt[0].D());
	ui.labelRuler->setText(QString("1px=%1mm").arg(QString::number(pHoriSize.fRuler,'f',5)));
	pPara->setValue(pHoriSize);
}
void CDlgHoriSize::drawSizeRect()
{
	s_oHoriSize oHoriSize = pShape->value<s_oHoriSize>();	
	pDlgMainWnd->adjustShape(this,oHoriSize.oSizeRect,DRAW_RECTANGLE);
	pShape->setValue(oHoriSize);
	pDlgMainWnd->displayObject();
	pDlgMainWnd->displayRoiHighLight(ITEM_HORI_SIZE,*pPara,*pShape); 
}
void CDlgHoriSize::changeGroupName(int index)
{
	ui.labelGroupName->setText(tr("<font color=blue>%1</font>").arg(index));
}
