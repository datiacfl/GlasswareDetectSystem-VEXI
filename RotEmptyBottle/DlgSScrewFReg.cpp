#include "DlgSScrewFReg.h"

CDlgSScrewFReg::CDlgSScrewFReg(QWidget *parent,QVariant *pCheckPara,QVariant *pCheckShape)
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
	connect(ui.btnResetReg,SIGNAL(clicked()),this,SLOT(ResetReg()));
	connect(ui.comboShapeType,SIGNAL(currentIndexChanged(int)),this,SLOT(typeChanged(int)));
	//��ʼ���Ի���
	initDialog();
	//���á�����ʲô���ı�
	setHelpTips();
}

CDlgSScrewFReg::~CDlgSScrewFReg()
{

}
void CDlgSScrewFReg::initDialog()
{
	s_pSScrewFReg pSScrewFReg = pPara->value<s_pSScrewFReg>();
	//��ʼ���ؼ�
	QStringList strlTypes;
	strlTypes<<tr("Polygon")<<tr("Rect");
	ui.comboShapeType->addItems(strlTypes);
	//��ʾ����
	ui.comboShapeType->setCurrentIndex(pSScrewFReg.nShapeType);
	ui.spinEdge->setValue(pSScrewFReg.nEdge);
	ui.spinArea->setValue(pSScrewFReg.nArea);
	ui.spinLength->setValue(pSScrewFReg.nLength);
	ui.spinInnerDia->setValue(pSScrewFReg.nDia);
	ui.spinRab->setValue(pSScrewFReg.nRab);
}
void CDlgSScrewFReg::setHelpTips()
{		
	ui.spinArea->setWhatsThis(tr("Region is determined as a defective when the <i>area</i>, <i>length</i> "
		"and <i>width</i> are satisfied simultaneously"));	
}

void CDlgSScrewFReg::apply()
{
	//((MyLabelItem*)parentWidget())->bParaChanged = true;//֪ͨ������ģ������ı�
	pLabelItem->bParaChanged = true;
	//�������
	s_pSScrewFReg pSScrewFReg = pPara->value<s_pSScrewFReg>();
	pSScrewFReg.nShapeType = ui.comboShapeType->currentIndex();
	pSScrewFReg.nEdge = ui.spinEdge->value();
	pSScrewFReg.nArea = ui.spinArea->value();
	pSScrewFReg.nLength = ui.spinLength->value();
	pSScrewFReg.nDia = ui.spinInnerDia->value();
	pSScrewFReg.nRab = ui.spinRab->value();
	pPara->setValue(pSScrewFReg);
}

void CDlgSScrewFReg::accept()
{
	apply();
	return QDialog::accept();
}

void CDlgSScrewFReg::autoAccept()
{
	apply();
}

void CDlgSScrewFReg::drawReg()
{
	s_oSScrewFReg oSScrewFReg = pShape->value<s_oSScrewFReg>();
	if (ui.comboShapeType->currentIndex() == 0)
	{
		pDlgMainWnd->adjustShape(this,oSScrewFReg.oCheckRegion,DRAW_POLYGON);  //Ĭ�϶����
	}
	else
	{
		pDlgMainWnd->adjustShape(this,oSScrewFReg.oCheckRegion_Rect,DRAW_RECTANGLE); //��������
	}
	pShape->setValue(oSScrewFReg);
	pDlgMainWnd->displayObject();
	pDlgMainWnd->displayRoiHighLight(ITEM_SSCREWFINISH_REGION,*pPara,*pShape); 
}

//2017.7-�ָ�Ĭ������
void CDlgSScrewFReg::ResetReg()
{
	if (QMessageBox::No==QMessageBox::question(this,tr("Reset"),
		tr("The region will revert to the default shape,Do you want to continue?"),QMessageBox::Yes | QMessageBox::No))
		return;
	try
	{
		s_oSScrewFReg oSScrewFReg = pShape->value<s_oSScrewFReg>(); 
		if (ui.comboShapeType->currentIndex() == 0)
		{
			gen_contour_polygon_xld(&oSScrewFReg.oCheckRegion,
				HTuple(100).Concat(57).Concat(57).Concat(100).Concat(143).Concat(143).Concat(100),
				HTuple(50).Concat(75).Concat(125).Concat(150).Concat(125).Concat(75).Concat(50)); //Ĭ�϶����
		}
		else
		{
			gen_rectangle2_contour_xld(&oSScrewFReg.oCheckRegion_Rect,55,55,0,45,45);
		}
		//�������״�ı��ʶ��Ϊ��
		((MyLabelItem *)pDlgMainWnd->pItemLabel)->bShapeChanged = true;
		//ģ��ԭ�����Ϊ��ǰ��ԭ�㣡
		pDlgMainWnd->pChecker->modelOri = pDlgMainWnd->pChecker->currentOri;

		pShape->setValue(oSScrewFReg);
		pDlgMainWnd->displayObject();
		pDlgMainWnd->displayRoiHighLight(ITEM_SSCREWFINISH_REGION,*pPara,*pShape);
	}
	catch(HException &e)
	{
		//Halcon�쳣		
		QString tempStr,strErr;
		tempStr=e.message;
		tempStr.remove(0,20);
		strErr = QString("abnormal:ResetReg,")+ tempStr;
		pDlgMainWnd->pChecker->writeErrDataRecord(strErr);
	}
	catch (...)
	{
		pDlgMainWnd->pChecker->writeErrDataRecord(QString("abnormal:ResetReg"));		
	}
}

void CDlgSScrewFReg::typeChanged(int index)
{	
	//�������
	s_pSScrewFReg pSScrewFReg = pPara->value<s_pSScrewFReg>();
	pSScrewFReg.nShapeType = index;
	pPara->setValue(pSScrewFReg);

}