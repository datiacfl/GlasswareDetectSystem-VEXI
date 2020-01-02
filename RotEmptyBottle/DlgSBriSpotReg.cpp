#include "DlgSBriSpotReg.h"

CDlgSBriSpotReg::CDlgSBriSpotReg(QWidget *parent,QVariant *pCheckPara,QVariant *pCheckShape)
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

CDlgSBriSpotReg::~CDlgSBriSpotReg()
{

}

void CDlgSBriSpotReg::initDialog()
{
	s_pSBriSpotReg pSBriSpotReg = pPara->value<s_pSBriSpotReg>();
	//��ʼ���ؼ�
	QStringList strlTypes;
	strlTypes<<tr("Polygon")<<tr("Rect");
	ui.comboShapeType->addItems(strlTypes);
	//��ʾ����
	ui.comboShapeType->setCurrentIndex(pSBriSpotReg.nShapeType);
	ui.spinGray->setValue(pSBriSpotReg.nGray);
	ui.doubleSpinOpenRadius->setValue(pSBriSpotReg.fOpenRadius);
	ui.spinArea->setValue(pSBriSpotReg.nArea);
}

void CDlgSBriSpotReg::setHelpTips()
{
	ui.spinGray->setWhatsThis(tr("Adding the region that the gray value is bigger than the setting value of the gray to the defect region,"
		"in order to compensate that the big defect region isn't completely extracted by the contrast"));
	ui.spinArea->setWhatsThis(tr("Region is determined as a defect when its area is bigger than the setting value��"
		"and set<font color=red>the smaller,the more sensitive</font>"));
}

void CDlgSBriSpotReg::apply()
{
	//((MyLabelItem*)parentWidget())->bParaChanged = true;//֪ͨ������ģ������ı�
	pLabelItem->bParaChanged = true;
	//�������
	s_pSBriSpotReg pSBriSpotReg = pPara->value<s_pSBriSpotReg>();
	pSBriSpotReg.nShapeType = ui.comboShapeType->currentIndex();
	pSBriSpotReg.nGray = ui.spinGray->value();
	pSBriSpotReg.fOpenRadius = ui.doubleSpinOpenRadius->value();
	pSBriSpotReg.nArea = ui.spinArea->value();
	pPara->setValue(pSBriSpotReg);
}


void CDlgSBriSpotReg::accept()
{
	apply();
	return QDialog::accept();
}

void CDlgSBriSpotReg::autoAccept()
{
	apply();
}

void CDlgSBriSpotReg::drawReg()
{
	s_oSBriSpotReg oSBriSpotReg = pShape->value<s_oSBriSpotReg>();
	if (ui.comboShapeType->currentIndex() == 0)
	{
		pDlgMainWnd->adjustShape(this,oSBriSpotReg.oCheckRegion,DRAW_POLYGON);  //Ĭ�϶����
	}
	else
	{
		pDlgMainWnd->adjustShape(this,oSBriSpotReg.oCheckRegion_Rect,DRAW_RECTANGLE); //��������
	}
	pShape->setValue(oSBriSpotReg);
	pDlgMainWnd->displayObject();
	pDlgMainWnd->displayRoiHighLight(ITEM_SBRISPOT_REGION,*pPara,*pShape); 
}

//2017.7-�ָ�Ĭ������
void CDlgSBriSpotReg::ResetReg()
{
	if (QMessageBox::No==QMessageBox::question(this,tr("Reset"),
		tr("The region will revert to the default shape,Do you want to continue?"),QMessageBox::Yes | QMessageBox::No))
		return;
	try
	{
		s_oSBriSpotReg oSBriSpotReg = pShape->value<s_oSBriSpotReg>();
		if (ui.comboShapeType->currentIndex() == 0)
		{
			gen_contour_polygon_xld(&oSBriSpotReg.oCheckRegion,
				HTuple(100).Concat(57).Concat(57).Concat(100).Concat(143).Concat(143).Concat(100),
				HTuple(50).Concat(75).Concat(125).Concat(150).Concat(125).Concat(75).Concat(50)); //Ĭ�϶����
		}
		else
		{
			gen_rectangle2_contour_xld(&oSBriSpotReg.oCheckRegion_Rect,55,55,0,45,45);
		}
		//�������״�ı��ʶ��Ϊ��
		((MyLabelItem *)pDlgMainWnd->pItemLabel)->bShapeChanged = true;
		//ģ��ԭ�����Ϊ��ǰ��ԭ�㣡
		pDlgMainWnd->pChecker->modelOri = pDlgMainWnd->pChecker->currentOri;

		pShape->setValue(oSBriSpotReg);
		pDlgMainWnd->displayObject();
		pDlgMainWnd->displayRoiHighLight(ITEM_SBRISPOT_REGION,*pPara,*pShape);
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

void CDlgSBriSpotReg::typeChanged(int index)
{	
	//�������
	s_pSBriSpotReg pSBriSpotReg = pPara->value<s_pSBriSpotReg>();
	pSBriSpotReg.nShapeType = index;
	pPara->setValue(pSBriSpotReg);

}