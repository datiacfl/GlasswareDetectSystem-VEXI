#include "DlgSidewallLocate.h"

CDlgSidewallLocate::CDlgSidewallLocate(QWidget *parent,QVariant *pCheckPara,QVariant *pCheckShape)
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
	connect(ui.comboMethod,SIGNAL(currentIndexChanged(int)),this,SLOT(methodChanged(int)));
	connect(ui.btnCalibrate,SIGNAL(clicked()),this,SLOT(loctionCalibrate()));
	connect(ui.btnFirstLine,SIGNAL(clicked()),this,SLOT(drawFirstLine()));
	connect(ui.btnSecondLine,SIGNAL(clicked()),this,SLOT(drawSecondLine()));
	connect(ui.btnThirdLine,SIGNAL(clicked()),this,SLOT(drawThirdLine()));
	connect(ui.btnNewModel,SIGNAL(clicked()),this,SLOT(setNewModel()));
	connect(ui.pbtnAuto,SIGNAL(clicked()),this,SLOT(autoDrawLine()));
	//connect(ui.btnResetReg,SIGNAL(clicked()),this,SLOT(ResetReg()));
	
	//��ʼ���Ի���
	initDialog();
	//���á�����ʲô���ı�
	setHelpTips();
}

CDlgSidewallLocate::~CDlgSidewallLocate()
{

}
void CDlgSidewallLocate::initDialog()
{
	s_pSideLoc pSideLoc = pPara->value<s_pSideLoc>();	
	s_oSideLoc oSideLoc = pShape->value<s_oSideLoc>();	
	//��ʼ���ؼ�
	QStringList strlMethods,strlDirect;
	strlMethods<<tr("TranslationRotation")<<tr("HorizontalTranslation")<<tr("UnilateralTranslationRotation")<<tr("CompositeLocation(Stress)")
		<<tr("HorVerTranslation")<<tr("CenterHorTranslation")<<tr("TranslationRotation(Stress)"); //2018.1---ƿ��Ӧ������Լ���λ
	ui.comboMethod->addItems(strlMethods);
	strlDirect<<tr("LightToDark")<<tr("DarkToLight");
	ui.comboDirect->addItems(strlDirect);
	//��ʾ����
	ui.comboMethod->setCurrentIndex(pSideLoc.nMethodIdx);
	ui.checkStress->setChecked(pSideLoc.bStress);
	ui.spinFloatRange->setValue(pSideLoc.nFloatRange);
	if (oSideLoc.nLeftRight==1)
	{
		ui.radioLeft->setChecked(true);
	}
	if (oSideLoc.nLeftRight==2)
	{
		ui.radioRight->setChecked(true);
	}
	if (oSideLoc.nLeftRight==3)
	{
		ui.radioMiddle->setChecked(true);
	}
	ui.comboDirect->setCurrentIndex(pSideLoc.nDirect);
	ui.spinEdge->setValue(pSideLoc.nEdge);	
	ui.checkPointSubPix->setChecked(pSideLoc.bFindPointSubPix);
}

void CDlgSidewallLocate::methodChanged(int index)
{	
	ui.groupLoc->setVisible(index==0 || index==1 || index==2 || index==4 || index==5 || index==6);
	ui.groupPos->setVisible(index==1 || index==2 || index==5);
	ui.radioMiddle->setEnabled(index==5);
	ui.groupReLoc->setVisible(index==0 || index==4 || index==5);
	ui.btnSecondLine->setEnabled(index==0 || index==1 || index==2 || index==5 || index==6);	
	ui.btnThirdLine->setEnabled(index==0 || index==2 || index==4 || index==6);	

	// 2017.5---��ֱ�����������ز��ұ߽��
	ui.groupThirdLineLoc->setVisible(index==0 || index==4);
	ui.checkPointSubPix->setVisible(index==0 || index==4);

	ui.groupPress->setVisible(index==3);
	ui.checkStress->setEnabled(index!=3 || index!=6);
	ui.checkStress->setChecked(index==3 || index==6);
}

void CDlgSidewallLocate::setHelpTips()
{
	ui.comboMethod->setWhatsThis(tr("Depending on different images,6 methods are available:<br>"
		"<b>TranslationRotation:</b>most commonly used method,suitable for images contain both finish and body, "
		"and offer auto correction when there are spots on light-surce or more than 1 bottle in the image;<br>"
		"<b>HorizontalTranslation:</b>suitable for iamges only contain bottle body,vertical translate cannot located."
		"Need to specify the origin is on Left or Right;<br>"
		"<b>UnilateralTranslationRotation:</b>suitable for images that only one side is clear,the other side cannot used "
		"for locate.Need to specify Left or Right side;<br>"
		"<b>CompositeLocation(Stress):</b>suitable for the stress images,locate by the position of the normal image;<br>"
		"<b>HorVerTranslation:</b>suitable for images contain both finish and body,only translation,not rotation;<br>"
		"<b>CenterHorTranslation:</b>suitable for iamges only contain bottle body,offer auto correction when there are "
		"spots on light-surce or more than 1 bottle in the image,but vertical translate cannot located.;<br>"));
	ui.btnCalibrate->setWhatsThis(tr("move the bottle contour to the correct position, in order to get the correct displacement "
		"between normal image and stress image"));
	ui.btnNewModel->setWhatsThis(tr("Make sure current image has been located correctly, and has no disturb on image"));
	ui.spinFloatRange->setWhatsThis(tr("When the distance between the sides of the bottle exceed the permit range(this "
		"may caused by disturb on image),there will be an auto correction on locate origin,<font color=red>set 0 will "
		"disable the function</font>"));
	ui.comboDirect->setWhatsThis(tr("For all regular images and most stress images,bottle is darker than background,in "
		"this case the direction should be<i>light to dark</i>,but for some special bottles(as infusion bottles), on the "
		"stress image the bottle may lighter than background. In this case, the direction should be <i>dark to light</i>"));
	ui.spinEdge->setWhatsThis(tr("Set the sensitivity when searching edge points on locate lines, set<font color=red>smaller "
		"make more sensitive</font>,but may easily influnced by light oil spots. Set bigger make the search more strict, but "
		"may cause no edge points found"));
}

void CDlgSidewallLocate::apply()
{
	//֪ͨ������ģ������ı�
	//((MyLabelItem*)parentWidget())->bParaChanged = true;
	pLabelItem->bParaChanged = true;
	//�������
	s_pSideLoc pSideLoc=pPara->value<s_pSideLoc>();
	s_oSideLoc oSideLoc=pShape->value<s_oSideLoc>();
	//2014.1.14 �����ı�ʱ,����ģ�������ԭ�㣬ͨ����״�ı�������ȥ����ģ��
	if (pSideLoc.nMethodIdx != ui.comboMethod->currentIndex() || oSideLoc.nLeftRight != (ui.radioLeft->isChecked()?1:(ui.radioRight->isChecked()?2:3)))
	{
		//((MyLabelItem *)(this->parentWidget()))->bShapeChanged = true;
		pLabelItem->bShapeChanged = true;
	}
	pSideLoc.nMethodIdx = ui.comboMethod->currentIndex();
	pSideLoc.bStress = ui.checkStress->isChecked();
	pSideLoc.nFloatRange = ui.spinFloatRange->value();
	pSideLoc.nDirect = ui.comboDirect->currentIndex();
	pSideLoc.nEdge = ui.spinEdge->value();
	pSideLoc.bFindPointSubPix = ui.checkPointSubPix->isChecked();
	pPara->setValue(pSideLoc);
	oSideLoc.nLeftRight = ui.radioLeft->isChecked()?1:(ui.radioRight->isChecked()?2:3);
	pShape->setValue(oSideLoc);
}

void CDlgSidewallLocate::accept()
{
	apply();
	return QDialog::accept();
}

void CDlgSidewallLocate::autoAccept()
{
	apply();
}

void CDlgSidewallLocate::loctionCalibrate()
{
	s_oSideLoc oSideLoc = pShape->value<s_oSideLoc>();	
	if (!ui.checkStress->isChecked())
	{
		QMessageBox::information(this,tr("Note"),tr("This calibration is used only for the stress image��"));	
		return;
	}
	Hlong nNum;
	count_obj(pDlgMainWnd->pChecker->m_normalbotXld,&nNum);
	if (nNum!=1)
	{
		QMessageBox::information(this,tr("Note"),tr("Correct bottle contour  was not found��"));	
		return;
	}
	count_obj(pDlgMainWnd->pChecker->m_pressbotXld,&nNum);
	if (nNum!=1)
	{
		//�任ΪӦ����ƿ������
		HTuple homMat2DIdentity;
		hom_mat2d_identity(&homMat2DIdentity);
		vector_angle_to_rigid (oSideLoc.drow1, oSideLoc.dcol1, oSideLoc.dphi1,
			oSideLoc.drow2, oSideLoc.dcol2, oSideLoc.dphi2, &homMat2DIdentity);
		affine_trans_contour_xld(pDlgMainWnd->pChecker->m_normalbotXld,&pDlgMainWnd->pChecker->m_pressbotXld,homMat2DIdentity);
	}

	pDlgMainWnd->adjustShape(this,pDlgMainWnd->pChecker->m_pressbotXld,DRAW_BOTTLEXLD);
	//λ������ת�Ƕ�
	area_center_xld (pDlgMainWnd->pChecker->m_normalbotXld, NULL, &oSideLoc.drow1, &oSideLoc.dcol1, NULL);
	orientation_xld (pDlgMainWnd->pChecker->m_normalbotXld, &oSideLoc.dphi1);
	area_center_xld (pDlgMainWnd->pChecker->m_pressbotXld, NULL, &oSideLoc.drow2, &oSideLoc.dcol2, NULL);
	orientation_xld (pDlgMainWnd->pChecker->m_pressbotXld, &oSideLoc.dphi2);
	//ԭ��
	oSideLoc.ori.Row = pDlgMainWnd->pChecker->normalOri.Row + oSideLoc.drow2 - oSideLoc.drow1;
	oSideLoc.ori.Col = pDlgMainWnd->pChecker->normalOri.Col + oSideLoc.dcol2 - oSideLoc.dcol1;
	oSideLoc.ori.Angle = pDlgMainWnd->pChecker->normalOri.Angle + oSideLoc.dphi2 - oSideLoc.dphi1;
	pDlgMainWnd->displayObject(ui.comboMethod->currentIndex());
	pShape->setValue(oSideLoc);
}

void CDlgSidewallLocate::drawFirstLine()
{	
	s_oSideLoc oSideLoc = pShape->value<s_oSideLoc>();	
	pDlgMainWnd->adjustShape(this,oSideLoc.oFirstLine,DRAW_LINE);
	pShape->setValue(oSideLoc);
	pDlgMainWnd->displayObject(ui.comboMethod->currentIndex());
}

void CDlgSidewallLocate::drawSecondLine()
{
	s_oSideLoc oSideLoc = pShape->value<s_oSideLoc>();
	pDlgMainWnd->adjustShape(this,oSideLoc.oSecondLine,DRAW_LINE);
	pShape->setValue(oSideLoc);
	pDlgMainWnd->displayObject(ui.comboMethod->currentIndex());
}

void CDlgSidewallLocate::drawThirdLine()
{
	s_oSideLoc oSideLoc = pShape->value<s_oSideLoc>();
	pDlgMainWnd->adjustShape(this,oSideLoc.oThirdLine,DRAW_LINE);
	pShape->setValue(oSideLoc);
	pDlgMainWnd->displayObject(ui.comboMethod->currentIndex());
}

//���ܣ�Ϊԭ���Զ������趨�µ�У׼ģ��
void CDlgSidewallLocate::setNewModel()
{
	int i;
	if (QMessageBox::No==QMessageBox::question(this,tr("Sure"),tr("Calibration basing at the current image��"),
		QMessageBox::Yes | QMessageBox::No))
		return;
	s_oSideLoc oSideLoc = pShape->value<s_oSideLoc>();
	float fDist1 = oSideLoc.ori.nCol12-oSideLoc.ori.nCol11;
	float fDist2 = oSideLoc.ori.nCol22-oSideLoc.ori.nCol21;
	//���浽�����
	oSideLoc.ori.fDist1 = fDist1;
	oSideLoc.ori.fDist2 = fDist2;
	pShape->setValue(oSideLoc);
	pDlgMainWnd->pCheckerReal->oldSideOri.fDist1=fDist1;
	pDlgMainWnd->pCheckerReal->oldSideOri.fDist2=fDist2;
	pDlgMainWnd->pChecker->oldSideOri.fDist1=fDist1;
	pDlgMainWnd->pChecker->oldSideOri.fDist2=fDist2;
	//���浽ģ����
	QString strShapePath = pDlgMainWnd->pChecker->strModelPath+"\\ModelShape.ini";
	QSettings shapeSet(strShapePath,QSettings::IniFormat);
	for (i=0;i<pDlgMainWnd->pChecker->vItemFlow.size();++i)
	{
		if (pDlgMainWnd->pChecker->vItemFlow[i]==ITEM_SIDEWALL_LOCATE)
		{
			shapeSet.beginGroup("Item_"+QString::number(i+1));
			shapeSet.beginGroup("origin");
			shapeSet.setValue("fDist1",QString::number(fDist1));
			shapeSet.setValue("fDist2",QString::number(fDist2));
			shapeSet.endGroup();
			shapeSet.endGroup();
		}
	}	
}

void CDlgSidewallLocate::autoDrawLine()
{
	s_oSideLoc oSideLoc = pShape->value<s_oSideLoc>();
	Hobject imgMean, regThres, regSel, regLn1, regLn2;
	Hlong nImgWid, nImgHei, nNum, nMaskWid;
	Hlong nRow1, nCol1, nRow2, nCol2;
	Hlong nLnR1, nLnC1, nLnR2, nLnC2;
	nMaskWid = 31;
	get_image_pointer1(pDlgMainWnd->imgShow, NULL, NULL, &nImgWid, &nImgHei);
	mean_image(pDlgMainWnd->imgShow, &imgMean, nMaskWid, nMaskWid);
	dyn_threshold(pDlgMainWnd->imgShow, imgMean, &regThres, 10, "dark");
	closing_circle(regThres, &regThres, 7.5);
	gen_region_line(&regLn1, 0, 0, 0, nImgWid-1);
	gen_region_line(&regLn2, nImgHei-1, 0, nImgHei-1, nImgWid-1);
	union2(regThres, regLn1, &regThres);
	union2(regThres, regLn2, &regThres);
	fill_up(regThres, &regThres);
	connection(regThres, &regThres);
	count_obj(regThres, &nNum);
	if (nNum == 0)
	{
		QMessageBox::information(this, tr("Note"), tr("Can't find the bottle area!"));
		return;
	}
	select_shape_std(regThres, &regSel, "max_area", 70);
	opening_rectangle1(regSel, &regSel, 1, nMaskWid);
	connection(regSel, &regSel);
	count_obj(regSel, &nNum);
	if (nNum == 0)
	{
		QMessageBox::information(this, tr("Note"), tr("Can't find the bottle area!"));
		return;
	}
	select_shape_std(regSel, &regSel, "max_area", 70);
	smallest_rectangle1(regSel, &nRow1, &nCol1, &nRow2, &nCol2);

	int nIdx = ui.comboMethod->currentIndex();
	switch(nIdx)
	{
	case 0:
	case 2:
		//generate the first line
		nLnR1 = nRow2-(nRow2-nRow1)/3;
		nLnC1 = nCol1-(nCol2-nCol1)/2;
		nLnC1 = max(0, nLnC1);
		nLnR2 = nLnR1;
		nLnC2 = nCol2+(nCol2-nCol1)/2;
		nLnC2 = min(nLnC2, nImgWid-1);
		gen_region_line(&oSideLoc.oFirstLine, nLnR1, nLnC1, nLnR2, nLnC2);

		//generate the second line
		nLnR1 = nRow2-(nRow2-nRow1)/5;
		nLnC1 = nCol1-(nCol2-nCol1)/2;
		nLnC1 = max(0, nLnC1);
		nLnR2 = nLnR1;
		nLnC2 = nCol2+(nCol2-nCol1)/2;
		nLnC2 = min(nLnC2, nImgWid-1);
		gen_region_line(&oSideLoc.oSecondLine, nLnR1, nLnC1, nLnR2, nLnC2);

		//generate the third line
		nLnR1 = nRow1-100;
		nLnR1 = max(0, nLnR1);
		nLnC1 = (nCol1+nCol2)/2;
		nLnR2 = nRow1+100;
		nLnR2 = min(nLnR2,nImgHei-1);
		nLnC2 = nLnC1;
		gen_region_line(&oSideLoc.oThirdLine, nLnR1, nLnC1, nLnR2, nLnC2);
		break;
	case 1:
	case 5:
		//generate the first line
		nLnR1 = nRow2-2*(nRow2-nRow1)/3;
		nLnC1 = nCol1-(nCol2-nCol1)/2;
		nLnC1 = max(0, nLnC1);
		nLnR2 = nLnR1;
		nLnC2 = nCol2+(nCol2-nCol1)/2;
		nLnC2 = min(nLnC2, nImgWid-1);
		gen_region_line(&oSideLoc.oFirstLine, nLnR1, nLnC1, nLnR2, nLnC2);

		//generate the second line
		nLnR1 = nRow2-(nRow2-nRow1)/3;
		nLnC1 = nCol1-(nCol2-nCol1)/2;
		nLnC1 = max(0, nLnC1);
		nLnR2 = nLnR1;
		nLnC2 = nCol2+(nCol2-nCol1)/2;
		nLnC2 = min(nLnC2, nImgWid-1);
		gen_region_line(&oSideLoc.oSecondLine, nLnR1, nLnC1, nLnR2, nLnC2);
		break;
	case 4:
		//generate the first line
		nLnR1 = nRow2-(nRow2-nRow1)/3;
		nLnC1 = nCol1-(nCol2-nCol1)/2;
		nLnC1 = max(0, nLnC1);
		nLnR2 = nLnR1;
		nLnC2 = nCol2+(nCol2-nCol1)/2;
		nLnC2 = min(nLnC2, nImgWid-1);
		gen_region_line(&oSideLoc.oFirstLine, nLnR1, nLnC1, nLnR2, nLnC2);
		
		//generate the third line
		nLnR1 = nRow1-100;
		nLnR1 = max(0, nLnR1);
		nLnC1 = (nCol1+nCol2)/2;
		nLnR2 = nRow1+100;
		nLnR2 = min(nLnR2,nImgHei-1);
		nLnC2 = nLnC1;
		gen_region_line(&oSideLoc.oThirdLine, nLnR1, nLnC1, nLnR2, nLnC2);
		break;
	default:
		break;
	}

	// �����ڲ�ģ���������ʾ
	pShape->setValue(oSideLoc);
	pDlgMainWnd->displayObject(ui.comboMethod->currentIndex());	
}

////2017.8-�ۺ϶�λ��Ӧ����-�ָ�Ĭ��λ��
//void CDlgSidewallLocate::ResetReg()
//{
//	if (QMessageBox::No==QMessageBox::question(this,tr("Reset"),
//		tr("The region will revert to the default shape,Do you want to continue?"),QMessageBox::Yes | QMessageBox::No))
//		return;
//	try
//	{		
//		long nNum;
//		count_obj(pDlgMainWnd->pChecker->m_normalbotXld,&nNum);
//		if (nNum!=1)
//		{
//			QMessageBox::information(this,tr("Note"),tr("Correct bottle contour  was not found��"));	
//			return;
//		}
//		copy_obj(pDlgMainWnd->pChecker->m_normalbotXld,&pDlgMainWnd->pChecker->m_pressbotXld,1,-1);
//
//		//ԭ��
//		s_oSideLoc oSideLoc = pShape->value<s_oSideLoc>();
//		oSideLoc.ori.Row = pDlgMainWnd->pChecker->normalOri.Row;
//		oSideLoc.ori.Col = pDlgMainWnd->pChecker->normalOri.Col;
//		oSideLoc.ori.Angle = pDlgMainWnd->pChecker->normalOri.Angle;
//		pShape->setValue(oSideLoc);
//		pDlgMainWnd->displayObject(ui.comboMethod->currentIndex());
//	}
//	catch(HException &e)
//	{
//		//Halcon�쳣		
//		QString tempStr,strErr;
//		tempStr=e.message;
//		tempStr.remove(0,20);
//		strErr = QString("�쳣:ResetReg,")+ tempStr;
//		pDlgMainWnd->pChecker->writeErrDataRecord(strErr);
//	}
//	catch (...)
//	{
//		pDlgMainWnd->pChecker->writeErrDataRecord(QString("�쳣:ResetReg"));		
//	}
//}