#include "DlgBAllReg.h"

CDlgBAllReg::CDlgBAllReg(QWidget *parent,QVariant *pCheckPara,QVariant *pCheckShape)
	: CItemDlg(parent,pCheckPara,pCheckShape)
{
	ui.setupUi(this);

	//2017.8-���ģ���޳���
	QGridLayout *gridLayout = new QGridLayout();
	gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
	gridLayout->setSpacing(0);
	gridLayout->setMargin(0);
	int number;
	QString strObjectName;
	for (int i=0;i<=8;i++) //9��10��
	{
		for (int j=0;j<=9;j++)
		{
			number = i*10+j+1;
			buttonReject[number-1] = new QPushButton();
			strObjectName = "pushButton_"+ QString("%1").arg(number);
			buttonReject[number-1]->setObjectName(QString::fromUtf8(strObjectName)); 
			buttonReject[number-1]->setText(QString("%1").arg(number));

			buttonReject[number-1]->setFixedWidth(30);
			buttonReject[number-1]->setFixedHeight(30);
			buttonReject[number-1]->setStyleSheet("QPushButton{background-color:rgb(112,128,144);\
                        color:white;border-radius:8px;border:2px groove gray;\
	                    border-style:outset;}"
	                    "QPushButton:checked{background-color:rgb(85,170,255);\
                        border-style: inset; }");
			buttonReject[number-1]->setCheckable(true);
			gridLayout->addWidget(buttonReject[number-1],i,j,1,1);
		}
	}
	ui.verticalLayout_5->addLayout(gridLayout);
		
	//���ȷ��ȡ����Ӧ�ð�ť
	addCtrLayout();
	//���ô��ڴ�С
	setDlgSize();
	////�������ţ��ɲ��ֵ�����С
	//layout()->setSizeConstraint(QLayout::SetFixedSize);
	//������Ͽ��źŲ�	
	connect(ui.btnInCircle,SIGNAL(clicked()),this,SLOT(drawInCircle()));
	connect(ui.btnOutCircle,SIGNAL(clicked()),this,SLOT(drawOutCircle()));
	connect(ui.btnExpand,SIGNAL(clicked()),this,SLOT(expandDlg()));	
	//��ʼ���Ի���
	initDialog();
	//���á�����ʲô���ı�
	setHelpTips();
}

CDlgBAllReg::~CDlgBAllReg()
{

}

void CDlgBAllReg::initDialog()
{
	// 2017.7-��ģ��ԭ����ơ��ƿ�ײ����ģ��ʶ��
	s_pBAllReg pBAllReg = pPara->value<s_pBAllReg>();

	//��ʼ���ؼ�
	ui.groupModeNO->setVisible(false);
	ui.groupAdvPara->setVisible(false);
	ui.groupModePoint->setVisible(false);
	ui.btnInCircle->setVisible(false);
	ui.btnExpand->setVisible(false);
	ui.groupModeRejectSet->setVisible(false);

	//��ʾ����
	ui.spinMouldEdge->setValue(pBAllReg.nMouldEdge);	
	ui.spinMouldDia->setValue(pBAllReg.nMouldDia);
	ui.spinMouldSpace->setValue(pBAllReg.nMouldSpace);
	ui.checkAntiClockwise->setChecked(pBAllReg.bCheckAntiClockwise);
	ui.spinMouldInnerRadiusL->setValue(pBAllReg.nMouldInnerDiaL);
	ui.spinMouldInnerRadiusH->setValue(pBAllReg.nMouldInnerDiaH);
	ui.checkIfReportError->setChecked(pBAllReg.bCheckIfReportError);
	ui.spinModeReject_1->setValue(pBAllReg.nModeReject_1);
	ui.spinModeReject_2->setValue(pBAllReg.nModeReject_2);
	ui.spinModeReject_3->setValue(pBAllReg.nModeReject_3);
	ui.bDelStripe->setChecked(pBAllReg.bDelStripe);
	ui.nStrLengthth->setValue(pBAllReg.nStrLengthth);
	ui.nStrWidth->setValue(pBAllReg.nStrWidth);/**/
	ui.checkthirtmp->setChecked(pBAllReg.bFlagThirtMp);

	//����ģ�ű�״̬������Ϊ�޳���
	for (int i=0;i<90;i++)
	{		
		if (pBAllReg.strModeReject.isEmpty())
		{
			buttonReject[i]->setChecked(false);
		}
		else
		{
			QString tempStr,strSection;
			tempStr = pBAllReg.strModeReject;
			strSection = tempStr.section(',', i, i).trimmed();
			buttonReject[i]->setChecked(strSection.toInt());
		}
	}
	
	////��ʼ���ؼ�
	//ui.groupAdvPara->setVisible(false);
	////��ʾ����
	//ui.checkModeNO->setChecked(pBAllReg.bModeNO);
	//ui.spinModeNOEdge->setValue(pBAllReg.nModePointEdge);	
	//ui.spinModeNOWidth->setValue(pBAllReg.nModeNOWidth);
	//ui.spinModeNOHeight->setValue(pBAllReg.nModeNOHeight);
	//ui.spinModePointCount->setValue(pBAllReg.nModePointNum);
	//ui.spinModePointRadius->setValue(pBAllReg.fModePointRadius);
	//ui.spinMaxPointSpace->setValue(pBAllReg.nMaxModePointSpace);
	//ui.spinMaskWidth->setValue(pBAllReg.nMaskWidth);
	//ui.spinMaskHeight->setValue(pBAllReg.nMaskHeight);
	//ui.spinFontCloseScale->setValue(pBAllReg.nFontCloseScale);
	//ui.spinModePointGradient->setValue(pBAllReg.nModePointSobel);
	//ui.spinMinModePointHeight->setValue(pBAllReg.nMinModePointHeight);
	//ui.spinSobelOpeningScale->setValue(pBAllReg.fSobelOpeningScale);	

	//ui.checkModeNOExt->setChecked(pBAllReg.bModeNOExt);
	//ui.spinMixModePointCountExt->setValue(pBAllReg.nMinModePointNumExt);	
	//ui.spinMixModePointDisExt->setValue(pBAllReg.nSigPointDisExt);

}

void CDlgBAllReg::expandDlg()
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

void CDlgBAllReg::setHelpTips()
{	
}
	
void CDlgBAllReg::apply()
{
	//((MyLabelItem*)parentWidget())->bParaChanged = true;//֪ͨ������ģ������ı�
	pLabelItem->bParaChanged = true;
	//�������
	s_pBAllReg pBAllReg = pPara->value<s_pBAllReg>();
	pBAllReg.nMouldEdge = ui.spinMouldEdge->value();
	pBAllReg.nMouldDia = ui.spinMouldDia->value();
	pBAllReg.nMouldSpace = ui.spinMouldSpace->value();
	pBAllReg.bCheckAntiClockwise = ui.checkAntiClockwise->isChecked();
	pBAllReg.nMouldInnerDiaL = ui.spinMouldInnerRadiusL->value();
	pBAllReg.nMouldInnerDiaH = ui.spinMouldInnerRadiusH->value();
	pBAllReg.bCheckIfReportError = ui.checkIfReportError->isChecked();
	pBAllReg.nModeReject_1 = ui.spinModeReject_1->value();
	pBAllReg.nModeReject_2 = ui.spinModeReject_2->value();
	pBAllReg.nModeReject_3 = ui.spinModeReject_3->value();
	pBAllReg.bDelStripe = ui.bDelStripe->isChecked();
	pBAllReg.nStrLengthth = ui.nStrLengthth->value();
	pBAllReg.nStrWidth = ui.nStrWidth->value();
	pBAllReg.bFlagThirtMp = ui.checkthirtmp->isChecked();
	//����ģ�ű�״̬
	pBAllReg.strModeReject.clear();
	for (int i=0;i<9;i++) //9��10��
	{
		for (int j=0;j<10;j++)
		{
			int ind = i*10+j;
			int bChecked = buttonReject[ind]->isChecked(); 
			pBAllReg.strModeReject += QString("%1").arg(bChecked);			
			if (ind != 89)
			{
				pBAllReg.strModeReject += ",";
			}
		}		
	}

	pPara->setValue(pBAllReg);
}

void CDlgBAllReg::accept()
{
	apply();
	return QDialog::accept();
}

void CDlgBAllReg::autoAccept()
{
	apply();
}

void CDlgBAllReg::drawInCircle()
{
	s_oBAllReg oBAllReg = pShape->value<s_oBAllReg>();
	pDlgMainWnd->adjustShape(this,oBAllReg.oInCircle,DRAW_CIRCLE);
	pShape->setValue(oBAllReg);
	pDlgMainWnd->displayObject();
	pDlgMainWnd->displayRoiHighLight(ITEM_BALL_REGION,*pPara,*pShape);
}

void CDlgBAllReg::drawOutCircle()
{
	s_oBAllReg oBAllReg = pShape->value<s_oBAllReg>();
	pDlgMainWnd->adjustShape(this,oBAllReg.oOutCircle,DRAW_CIRCLE);
	pShape->setValue(oBAllReg);
	pDlgMainWnd->displayObject();
	pDlgMainWnd->displayRoiHighLight(ITEM_BALL_REGION,*pPara,*pShape);
}

//void CDlgBAllReg::ButtonToggled()
//{
//	QPushButton* btn = dynamic_cast<QPushButton*>(sender());
//	QString buttonName;
//	int num;
//	buttonName = btn->name();
//	num = buttonName.toInt();
//	if (num>=1 && num<=90)
//	{
//		bButtonPressed[num-1] = btn->isChecked();
//	}	
//}
