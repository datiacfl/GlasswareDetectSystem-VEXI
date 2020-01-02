#include "DlgSSideFReg.h"

CDlgSSideFReg::CDlgSSideFReg(QWidget *parent,QVariant *pCheckPara,QVariant *pCheckShape)
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
	connect(ui.btnExpand,SIGNAL(clicked()),this,SLOT(expandDlg()));	
	connect(ui.btnResetReg,SIGNAL(clicked()),this,SLOT(ResetReg()));
	connect(ui.comboShapeType,SIGNAL(currentIndexChanged(int)),this,SLOT(typeChanged(int)));
	//��ʼ���Ի���
	initDialog();
	//���á�����ʲô���ı�
	setHelpTips();
}

CDlgSSideFReg::~CDlgSSideFReg()
{

}
void CDlgSSideFReg::initDialog()
{
	s_pSSideFReg pSSideFReg = pPara->value<s_pSSideFReg>();
	//��ʼ���ؼ�
	ui.groupAdvPara->setVisible(false);
	QStringList strlTypes;
	strlTypes<<tr("Polygon")<<tr("Rect");
	ui.comboShapeType->addItems(strlTypes);
	//��ʾ����
	ui.comboShapeType->setCurrentIndex(pSSideFReg.nShapeType);
	ui.spinEdge->setValue(pSSideFReg.nEdge);
	ui.spinArea->setValue(pSSideFReg.nArea);
	ui.spinWidth->setValue(pSSideFReg.nWidth);

	ui.checkGenRoi->setChecked(pSSideFReg.bGenRoi);
	ui.spinRoiRatio->setValue(pSSideFReg.fRoiRatio);
	ui.spinClosingWH->setValue(pSSideFReg.nClosingWH);
	ui.spinGapWH->setValue(pSSideFReg.nGapWH);
	ui.spinMaskSize->setValue(pSSideFReg.nMaskSize);
	ui.spinClosingSize->setValue(pSSideFReg.fClosingSize);
}
void CDlgSSideFReg::expandDlg()
{
	QString strName = ui.btnExpand->text();
	if (strName=="+")
	{
		ui.btnExpand->setText("-");
		ui.groupAdvPara->setVisible(true);
	}
	else if (strName=="-")
	{
		ui.btnExpand->setText("+");
		ui.groupAdvPara->setVisible(false);
	}		
}
void CDlgSSideFReg::setHelpTips()
{		
	ui.checkGenRoi->setWhatsThis(tr("Pretreatment the region and generate a ROI, which filter the shadows on "
		"edge from the valid check region"));
	ui.spinRoiRatio->setWhatsThis(tr("Set the pretreatment ratio coefficient, the value between [0,1],"
		"<font color=red>set smaller make the valid check region bigger</font>"));
	ui.spinClosingWH->setWhatsThis(tr("Set the closing width and height on the edge of ROI, this is used to "
		"<font color=red>avoid defects as crack are filterd by ROI</font>"));
	ui.spinGapWH->setWhatsThis(tr("If the difference between ROI and original region are bigger (either width "
		"or height) than setted value, an error will report, as there may has an cirtical defects on the edge"));
	ui.spinMaskSize->setWhatsThis(tr("Set the width of the mask,this value influence the effect of <i>Edge</i>."
		"As a rule of thumb,masksize should be twice of the maximum checkable defect's diameter,if the masksize "
		"is setted bigger, time consume will increased"));
	ui.spinClosingSize->setWhatsThis(tr("If the distance between two defects are smaller than setted value,"
		"they will merge as one defect. This is uesd to avoid some bubble defects escape because of incomplete extracion"));	
}

void CDlgSSideFReg::apply()
{
	//((MyLabelItem*)parentWidget())->bParaChanged = true;//֪ͨ������ģ������ı�
	pLabelItem->bParaChanged = true;
	//�������
	s_pSSideFReg pSSideFReg = pPara->value<s_pSSideFReg>();
	pSSideFReg.nShapeType = ui.comboShapeType->currentIndex();
	pSSideFReg.nEdge = ui.spinEdge->value();
	pSSideFReg.nArea = ui.spinArea->value();
	pSSideFReg.nWidth = ui.spinWidth->value();	

	pSSideFReg.bGenRoi = ui.checkGenRoi->isChecked();
	pSSideFReg.fRoiRatio = ui.spinRoiRatio->value();
	pSSideFReg.nClosingWH = ui.spinClosingWH->value();
	pSSideFReg.nGapWH = ui.spinGapWH->value();
	pSSideFReg.nMaskSize = ui.spinMaskSize->value();
	pSSideFReg.fClosingSize = ui.spinClosingSize->value();
	pPara->setValue(pSSideFReg);
}

void CDlgSSideFReg::accept()
{
	apply();
	return QDialog::accept();
}

void CDlgSSideFReg::autoAccept()
{
	apply();
}

void CDlgSSideFReg::drawReg()
{
	s_oSSideFReg oSSideFReg = pShape->value<s_oSSideFReg>();
	if (ui.comboShapeType->currentIndex() == 0)
	{
		pDlgMainWnd->adjustShape(this,oSSideFReg.oCheckRegion,DRAW_POLYGON);  //Ĭ�϶����
	}
	else
	{
		pDlgMainWnd->adjustShape(this,oSSideFReg.oCheckRegion_Rect,DRAW_RECTANGLE); //��������
	}
	pShape->setValue(oSSideFReg);
	pDlgMainWnd->displayObject();
	pDlgMainWnd->displayRoiHighLight(ITEM_SSIDEFINISH_REGION,*pPara,*pShape); 
}

//2017.7-�ָ�Ĭ������
void CDlgSSideFReg::ResetReg()
{
	if (QMessageBox::No==QMessageBox::question(this,tr("Reset"),
		tr("The region will revert to the default shape,Do you want to continue?"),QMessageBox::Yes | QMessageBox::No))
		return;
	try
	{
		s_oSSideFReg oSSideFReg = pShape->value<s_oSSideFReg>();
		if (ui.comboShapeType->currentIndex() == 0)
		{
			gen_contour_polygon_xld(&oSSideFReg.oCheckRegion,
				HTuple(100).Concat(57).Concat(57).Concat(100).Concat(143).Concat(143).Concat(100),
				HTuple(50).Concat(75).Concat(125).Concat(150).Concat(125).Concat(75).Concat(50)); //Ĭ�϶����
		}
		else
		{
			gen_rectangle2_contour_xld(&oSSideFReg.oCheckRegion_Rect,55,55,0,45,45);
		}
		//�������״�ı��ʶ��Ϊ��
		((MyLabelItem *)pDlgMainWnd->pItemLabel)->bShapeChanged = true;
		//ģ��ԭ�����Ϊ��ǰ��ԭ�㣡
		pDlgMainWnd->pChecker->modelOri = pDlgMainWnd->pChecker->currentOri;

		pShape->setValue(oSSideFReg);
		pDlgMainWnd->displayObject();
		pDlgMainWnd->displayRoiHighLight(ITEM_SSIDEFINISH_REGION,*pPara,*pShape); 
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

void CDlgSSideFReg::typeChanged(int index)
{	
	//�������
	s_pSSideFReg pSSideFReg = pPara->value<s_pSSideFReg>();
	pSSideFReg.nShapeType = index;
	pPara->setValue(pSSideFReg);

}