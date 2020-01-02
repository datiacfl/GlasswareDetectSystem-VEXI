#include "DlgVertSize.h"

extern bool g_bSizeComplex;

CDlgVertSize::CDlgVertSize(QWidget *parent,QVariant *pCheckPara,QVariant *pCheckShape)
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

CDlgVertSize::~CDlgVertSize()
{

}

void CDlgVertSize::initDialog()
{
	s_pVertSize pVertSize = pPara->value<s_pVertSize>();	
	//��ʼ���ؼ�	
	ui.groupBoxComplex->setVisible(g_bSizeComplex);
	if (pVertSize.bComplex)
	{
		ui.spinSizeGroup->setEnabled(false);
	}
	ui.spinSizeGroup->setValue(pVertSize.nSizeGroup);
	changeGroupName(pVertSize.nSizeGroup);
	//��ʾ����
	ui.spinEdge->setValue(pVertSize.nEdge);
	ui.spinLower->setValue(pVertSize.fLower);
	ui.spinUpper->setValue(pVertSize.fUpper);
	ui.spinReal->setValue(pVertSize.fReal);
	ui.spinModify->setValue(pVertSize.fModify);
	if (pVertSize.fRuler==1)
	{
		ui.labelRuler->setText(tr("<font color=red>Uncalibrated��</font>"));
	} else
	{
		ui.labelRuler->setText(QString("1px=%1mm").arg(QString::number(pVertSize.fRuler,'f',5)));
	}
}
void CDlgVertSize::setHelpTips()
{		
	ui.spinEdge->setWhatsThis(tr("Set the sensitivity when searching edge points,<font color=red>smaller make more sensitive</font>"));
	ui.spinReal->setWhatsThis(tr("Real distance between the two endpoints of the bottle"));	
}

void CDlgVertSize::apply()
{
	//((MyLabelItem*)parentWidget())->bParaChanged = true;//֪ͨ������ģ������ı�
	pLabelItem->bParaChanged = true;
	//�������
	s_pVertSize pVertSize = pPara->value<s_pVertSize>();
	pVertSize.nSizeGroup = ui.spinSizeGroup->value();
	pVertSize.nEdge = ui.spinEdge->value();
	pVertSize.fLower = ui.spinLower->value();
	pVertSize.fUpper = ui.spinUpper->value();
	pVertSize.fModify = ui.spinModify->value();
	pPara->setValue(pVertSize);
}

void CDlgVertSize::accept()
{
	apply();
	return QDialog::accept();
}

void CDlgVertSize::autoAccept()
{
	apply();
}

void CDlgVertSize::calibRuler()
{
	if (QMessageBox::No==QMessageBox::question(this,tr("Calibrated"),
		tr("Whether to recalculate the scale��"),QMessageBox::Yes | QMessageBox::No))
		return;
	s_pVertSize pVertSize = pPara->value<s_pVertSize>();
	pVertSize.fReal = ui.spinReal->value();
	pVertSize.nEdge = ui.spinEdge->value();
	HTuple rowPt,colPt;
	Hobject oLineSeg;
	double row1,col1,row2,col2;
	smallest_rectangle1_xld(pShape->value<s_oVertSize>().oSizeRect,&row1,&col1,&row2,&col2);
	gen_region_line(&oLineSeg,row1,(col1+col2)/2,row2,(col1+col2)/2);
	int nRtn = pDlgMainWnd->pChecker->findEdgePointDouble(pDlgMainWnd->imgShow,oLineSeg,&rowPt,&colPt,pVertSize.nEdge,T2B);
	if (nRtn<2)
	{
		ui.labelRuler->setText(tr("<font color=red>Calibration failure��</font>"));
		return;
	}
	pVertSize.fRuler = pVertSize.fReal/(rowPt[1].D()-rowPt[0].D());
	ui.labelRuler->setText(QString("1px=%1mm").arg(QString::number(pVertSize.fRuler,'f',5)));
	pPara->setValue(pVertSize);
}
void CDlgVertSize::drawSizeRect()
{
	s_oVertSize oVertSize = pShape->value<s_oVertSize>();
	pDlgMainWnd->adjustShape(this,oVertSize.oSizeRect,DRAW_RECTANGLE);
	pShape->setValue(oVertSize);
	pDlgMainWnd->displayObject();
	pDlgMainWnd->displayRoiHighLight(ITEM_VERT_SIZE,*pPara,*pShape); 
}

void CDlgVertSize::changeGroupName(int index)
{
	ui.labelGroupName->setText(tr("<font color=blue>%1</font>").arg(index));
}
