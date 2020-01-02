#include "DlgSGenReg.h"

CDlgSGenReg::CDlgSGenReg(QWidget *parent,QVariant *pCheckPara,QVariant *pCheckShape)
	: CItemDlg(parent,pCheckPara,pCheckShape)
{
	ui.setupUi(this);
	//添加确定取消、应用按钮
	addCtrLayout();
	//设置窗口大小
	setDlgSize();
	////禁用缩放，由布局调整大小
	//layout()->setSizeConstraint(QLayout::SetFixedSize);
	//连接组合框信号槽
	connect(ui.btnDrawReg,SIGNAL(clicked()),this,SLOT(drawReg()));
	connect(ui.btnExpand,SIGNAL(clicked()),this,SLOT(expandDlg()));	
	connect(ui.comboShapeType,SIGNAL(currentIndexChanged(int)),this,SLOT(typeChanged(int)));
	connect(ui.btnStone,SIGNAL(clicked()),this,SLOT(setStoneDisplay()));
	connect(ui.btnDarkDot,SIGNAL(clicked()),this,SLOT(setDarkDotDisplay()));
	connect(ui.btnTinyCrack,SIGNAL(clicked()),this,SLOT(setTinyCrackDisplay()));
	connect(ui.btnLightStripe,SIGNAL(clicked()),this,SLOT(setLightStripeDisplay()));
	connect(ui.btnBubbles,SIGNAL(clicked()),this,SLOT(setBubblesDisplay()));
	connect(ui.checkStone,SIGNAL(clicked()),this,SLOT(setBtnsStyle()));
	connect(ui.checkDarkdot,SIGNAL(clicked()),this,SLOT(setBtnsStyle()));
	connect(ui.checkTinyCrack,SIGNAL(clicked()),this,SLOT(setBtnsStyle()));
	connect(ui.checkLightStripes,SIGNAL(clicked()),this,SLOT(setBtnsStyle()));
	connect(ui.checkBubbles,SIGNAL(clicked()),this,SLOT(setBtnsStyle()));
	connect(ui.btnResetReg,SIGNAL(clicked()),this,SLOT(ResetReg()));
	connect(ui.btnExpand_SpeDefects,SIGNAL(clicked()),this,SLOT(expandDlgSpeDefects()));	

	//初始化对话框
	initDialog();
	//设置“这是什么”文本
	setHelpTips();

	//初始化
	nButtonClicked = 0;
}

CDlgSGenReg::~CDlgSGenReg()
{

}
void CDlgSGenReg::initDialog()
{
	s_pSGenReg pSGenReg = pPara->value<s_pSGenReg>(); 

	//初始化控件
	ui.groupAdvPara->setVisible(false);
	ui.groupBox_SpeDefects->setVisible(false);
	ui.groupBox_Bubbles_2->setVisible(false);
	//ui.groupBox_Stone->setVisible(false);
	//ui.groupBox_DarkDot->setVisible(false);
	//ui.groupBox_TinyCrack->setVisible(false);
	//ui.groupBox_LightStripe->setVisible(false);
	//ui.groupBox_Bubbles->setVisible(false);

	QStringList strlTypes;
	strlTypes<<tr("Polygon")<<tr("Rect");
	ui.comboShapeType->addItems(strlTypes);

	//显示参数
	ui.comboShapeType->setCurrentIndex(pSGenReg.nShapeType);
	ui.spinEdge->setValue(pSGenReg.nEdge);
	ui.spinGray->setValue(pSGenReg.nGray);
	ui.spinArea->setValue(pSGenReg.nArea);
	ui.spinLength->setValue(pSGenReg.nLength);

	ui.checkStone->setChecked(pSGenReg.bStone);
	ui.spinStoneEdge->setValue(pSGenReg.nStoneEdge);
	ui.spinStoneArea->setValue(pSGenReg.nStoneArea);
	ui.spinStoneNum->setValue(pSGenReg.nStoneNum);
	ui.checkDarkdot->setChecked(pSGenReg.bDarkdot);
	ui.spinDarkdotEdge->setValue(pSGenReg.nDarkdotEdge);
	ui.spinDarkdotArea->setValue(pSGenReg.nDarkdotArea);
	ui.spinDarkdotCir->setValue(pSGenReg.fDarkdotCir);
	ui.spinDrakdotNum->setValue(pSGenReg.nDarkdotNum);
	ui.checkTinyCrack->setChecked(pSGenReg.bTinyCrack);
	ui.spinTinyCrackEdge->setValue(pSGenReg.nTinyCrackEdge);
	ui.spinTinyCrackAnis->setValue(pSGenReg.nTinyCrackAnsi);
	ui.spinTinyCrackLength->setValue(pSGenReg.nTinyCrackLength);
	ui.spinTinyCrackInRadius->setValue(pSGenReg.nTinyCrackInRadius);
	ui.spinTinyCrackPhiL->setValue(pSGenReg.nTinyCrackPhiL);
	ui.spinTinyCrackPhiH->setValue(pSGenReg.nTinyCrackPhiH);
	ui.checkLightStripes->setChecked(pSGenReg.bLightStripe);
	ui.spinLightStripesEdge->setValue(pSGenReg.nLightStripeEdge);
	ui.spinLightStripesLength->setValue(pSGenReg.nLightStripeLength);
	ui.spinLightStripesInRadius->setValue(pSGenReg.nLightStripeInRadius);
	ui.spinLightStripesPhiL->setValue(pSGenReg.nLightStripePhiL);
	ui.spinLightStripesPhiH->setValue(pSGenReg.nLightStripePhiH);
	ui.checkBubbles->setChecked(pSGenReg.bBubbles);
	ui.spinBubblesLowThres->setValue(pSGenReg.nBubblesLowThres);
	ui.spinBubblesHighThres->setValue(pSGenReg.nBubblesHighThres);
	ui.spinBubblesCir->setValue(pSGenReg.fBubblesCir);
	ui.spinBubblesLength->setValue(pSGenReg.nBubblesLength);
	//ui.spinBubblesArea->setValue(pSGenReg.nBubblesArea);
	//ui.spinBubblesGrayOffset->setValue(pSGenReg.nBubblesGrayOffset);
	ui.checkOpen->setChecked(pSGenReg.bOpening);
	ui.spinOpeningSize->setValue(pSGenReg.fOpeningSize);

	ui.checkDisturbEdge->setChecked(pSGenReg.bDistEdge);
	ui.spinDistEdge->setValue(pSGenReg.nDistEdge);
	ui.checkDisturbCondition1->setChecked(pSGenReg.bDistCon1);
	//ui.spinDisConPhiL1->setValue(pSGenReg.nDistPhiL1);
	//ui.spinDisConPhiH1->setValue(pSGenReg.nDistPhiH1);
	ui.spinDisConVerPhi->setValue(pSGenReg.nDistVerPhi);
	ui.spinDisConAniL1->setValue(pSGenReg.nDistAniL1);
	ui.spinDisConAniH1->setValue(pSGenReg.nDistAniH1);
	ui.spinDisConInRadiusL1->setValue(pSGenReg.nDistInRadiusL1);
	ui.spinDisConInRadiusH1->setValue(pSGenReg.nDistInRadiusH1);
	ui.checkDisturbCondition2->setChecked(pSGenReg.bDistCon2);
	//ui.spinDisConPhiL2->setValue(pSGenReg.nDistPhiL2);
	//ui.spinDisConPhiH2->setValue(pSGenReg.nDistPhiH2);
	ui.spinDisConHorPhi->setValue(pSGenReg.nDistHorPhi);
	ui.spinDisConAniL2->setValue(pSGenReg.nDistAniL2);
	ui.spinDisConAniH2->setValue(pSGenReg.nDistAniH2);
	ui.spinDisConInRadiusL2->setValue(pSGenReg.nDistInRadiusL2);
	ui.spinDisConInRadiusH2->setValue(pSGenReg.nDistInRadiusH2);

	ui.checkGenRoi->setChecked(pSGenReg.bGenRoi);
	ui.spinRoiRatio->setValue(pSGenReg.fRoiRatio);
	ui.spinClosingWH->setValue(pSGenReg.nClosingWH);
	ui.spinGapWH->setValue(pSGenReg.nGapWH);
	ui.spinMaskSize->setValue(pSGenReg.nMaskSize);
	ui.spinMeanGray->setValue(pSGenReg.nMeanGray);
	ui.label_closeSize->setVisible(false);
	ui.spinClosingSize->setValue(pSGenReg.fClosingSize);
	//瓶身普通区域不显示闭运算，只有在瓶口区域中有效
	ui.spinClosingSize->setVisible(false);

	setBtnsStyle();
}
void CDlgSGenReg::expandDlg()
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
void CDlgSGenReg::expandDlgSpeDefects()
{
	QString strName = ui.btnExpand_SpeDefects->text();
	if (strName=="+")
	{
		ui.btnExpand_SpeDefects->setText("-");
		ui.groupBox_SpeDefects->setVisible(true);
		switch (nButtonClicked) //显示单个特殊缺陷的参数
		{
			case 0:
				setStoneDisplay();
				break;
			case 1:
				setDarkDotDisplay();
				break;	
			case 2:
				setTinyCrackDisplay();
				break;
			case 3:
				setLightStripeDisplay();
				break;
			case 4:
				setBubblesDisplay();
				break;
			default:
				setStoneDisplay();
				break;
		}		
	}
	else if (strName=="-")
	{
		ui.btnExpand_SpeDefects->setText("+");
		ui.groupBox_SpeDefects->setVisible(false);
	}		
}
void CDlgSGenReg::setHelpTips()
{	
	ui.spinEdge->setWhatsThis(tr("The edge between defect region and background should be longer than the setting value,"
		"set <font color=red>the smaller,the more sensitive</font>"));
	ui.spinGray->setWhatsThis(tr("Adding the region that the gray value is smaller than the setting value of the gray to the defect region,"
		"in order to compensate that the big defect region isn't completely extracted by the contrast"));
	ui.spinArea->setWhatsThis(tr("Region is determined as a defect when its area is bigger than the setting value，"
		"and set<font color=red>the smaller,the more sensitive</font>"));
	ui.spinLength->setWhatsThis(tr("Region is determined as a defect when its length is bigger than the setting value，"
		"and set<font color=red>the smaller,the more sensitive</font>，the relationship of <i>area</i> and"
		"<i>length</i> is 'or',that either one be satisfied will report an error"));
	ui.checkStone->setWhatsThis(tr("Stones generally have a higher contrast,a smaller area and more number than the general defects"));
	ui.checkDarkdot->setWhatsThis(tr("Black dots generally have a higher contrast and a smaller area than the stones"));
	ui.checkGenRoi->setWhatsThis(tr("Pretreatment the region and generate a ROI, which filter the shadows on edge from the valid check region"));
	ui.spinRoiRatio->setWhatsThis(tr("Set the pretreatment ratio coefficient, the value between [0,1],<font color=red>set smaller make the valid check region bigger</font>"));
	ui.spinClosingWH->setWhatsThis(tr("Set the closing width and height on the edge of ROI, this is used to <font color=red>avoid defects as crack are filterd by ROI</font>"));
	ui.spinGapWH->setWhatsThis(tr("If the difference between ROI and original region are bigger (either width or height) than setted value, an error will report, as there may has an cirtical defects on the edge"));
	ui.spinMaskSize->setWhatsThis(tr("Set the width of the mask,this value influence the effect of <i>Edge</i>. As a rule of thumb,masksize should be twice of the maximum checkable defect's diameter,if the masksize is setted bigger, time consume will increased"));
	ui.spinClosingSize->setWhatsThis(tr("If the distance between two defects are smaller than setted value, they will merge as one defect. This is uesd to avoid some bubble defects escape because of incomplete extracion"));
}

void CDlgSGenReg::apply()
{
	//((MyLabelItem*)parentWidget())->bParaChanged = true;//通知父窗口模板参数改变
	pLabelItem->bParaChanged = true;
	//传入参数
	s_pSGenReg pSGenReg = pPara->value<s_pSGenReg>();
	pSGenReg.nShapeType = ui.comboShapeType->currentIndex();
	pSGenReg.nEdge = ui.spinEdge->value();
	pSGenReg.nGray = ui.spinGray->value();
	pSGenReg.nArea = ui.spinArea->value();
	pSGenReg.nLength = ui.spinLength->value();

	pSGenReg.bStone = ui.checkStone->isChecked();
	pSGenReg.nStoneEdge = ui.spinStoneEdge->value();
	pSGenReg.nStoneArea = ui.spinStoneArea->value();
	pSGenReg.nStoneNum = ui.spinStoneNum->value();
	pSGenReg.bDarkdot = ui.checkDarkdot->isChecked();
	pSGenReg.nDarkdotEdge = ui.spinDarkdotEdge->value();
	pSGenReg.nDarkdotArea = ui.spinDarkdotArea->value();
	pSGenReg.fDarkdotCir = ui.spinDarkdotCir->value();
	pSGenReg.nDarkdotNum = ui.spinDrakdotNum->value();
	pSGenReg.bTinyCrack = ui.checkTinyCrack->isChecked();
	pSGenReg.nTinyCrackEdge = ui.spinTinyCrackEdge->value();
	pSGenReg.nTinyCrackAnsi = ui.spinTinyCrackAnis->value();
	pSGenReg.nTinyCrackLength = ui.spinTinyCrackLength->value();
	pSGenReg.nTinyCrackInRadius = ui.spinTinyCrackInRadius->value();
	pSGenReg.nTinyCrackPhiL = ui.spinTinyCrackPhiL->value();
	pSGenReg.nTinyCrackPhiH = ui.spinTinyCrackPhiH->value();
	pSGenReg.bLightStripe = ui.checkLightStripes->isChecked();
	pSGenReg.nLightStripeEdge = ui.spinLightStripesEdge->value();
	pSGenReg.nLightStripeLength = ui.spinLightStripesLength->value();
	pSGenReg.nLightStripeInRadius = ui.spinLightStripesInRadius->value();
	pSGenReg.nLightStripePhiL = ui.spinLightStripesPhiL->value();
	pSGenReg.nLightStripePhiH = ui.spinLightStripesPhiH->value();
	pSGenReg.bBubbles = ui.checkBubbles->isChecked();
	pSGenReg.nBubblesLowThres = ui.spinBubblesLowThres->value();
	pSGenReg.nBubblesHighThres = ui.spinBubblesHighThres->value();
	pSGenReg.fBubblesCir = ui.spinBubblesCir->value();
	pSGenReg.nBubblesLength = ui.spinBubblesLength->value();
	//pSGenReg.nBubblesArea = ui.spinBubblesArea->value();
	//pSGenReg.nBubblesGrayOffset = ui.spinBubblesGrayOffset->value();

	pSGenReg.bDistEdge = ui.checkDisturbEdge->isChecked();
	pSGenReg.nDistEdge = ui.spinDistEdge->value();
	pSGenReg.bDistCon1 = ui.checkDisturbCondition1->isChecked();
	//pSGenReg.nDistPhiL1 = ui.spinDisConPhiL1->value();
	//pSGenReg.nDistPhiH1 = ui.spinDisConPhiH1->value();
	pSGenReg.nDistVerPhi = ui.spinDisConVerPhi->value();
	pSGenReg.nDistAniL1 = ui.spinDisConAniL1->value();
	pSGenReg.nDistAniH1 = ui.spinDisConAniH1->value();
	pSGenReg.nDistInRadiusL1 = ui.spinDisConInRadiusL1->value();
	pSGenReg.nDistInRadiusH1 = ui.spinDisConInRadiusH1->value();
	pSGenReg.bDistCon2 = ui.checkDisturbCondition2->isChecked();
	//pSGenReg.nDistPhiL2 = ui.spinDisConPhiL2->value();
	//pSGenReg.nDistPhiH2 = ui.spinDisConPhiH2->value();
	pSGenReg.nDistHorPhi = ui.spinDisConHorPhi->value();
	pSGenReg.nDistAniL2 = ui.spinDisConAniL2->value();
	pSGenReg.nDistAniH2 = ui.spinDisConAniH2->value();
	pSGenReg.nDistInRadiusL2 = ui.spinDisConInRadiusL2->value();
	pSGenReg.nDistInRadiusH2 = ui.spinDisConInRadiusH2->value();

	pSGenReg.bOpening = ui.checkOpen->isChecked();
	pSGenReg.fOpeningSize = ui.spinOpeningSize->value();
	pSGenReg.bGenRoi = ui.checkGenRoi->isChecked();
	pSGenReg.fRoiRatio = ui.spinRoiRatio->value();
	pSGenReg.nClosingWH = ui.spinClosingWH->value();
	pSGenReg.nGapWH = ui.spinGapWH->value();
	pSGenReg.nMaskSize = ui.spinMaskSize->value();
	pSGenReg.nMeanGray = ui.spinMeanGray->value();
	pSGenReg.fClosingSize = ui.spinClosingSize->value();
	pPara->setValue(pSGenReg);
}

void CDlgSGenReg::accept()
{
	apply();
	return QDialog::accept();
}

void CDlgSGenReg::autoAccept()
{
	apply();
}

void CDlgSGenReg::drawReg()
{
	s_oSGenReg oSGenReg = pShape->value<s_oSGenReg>();
	if (ui.comboShapeType->currentIndex() == 0)
	{
		pDlgMainWnd->adjustShape(this,oSGenReg.oCheckRegion,DRAW_POLYGON);  //默认多边形
	}
	else
	{
		pDlgMainWnd->adjustShape(this,oSGenReg.oCheckRegion_Rect,DRAW_RECTANGLE); //新增矩形
	}
	
	pShape->setValue(oSGenReg);
	pDlgMainWnd->displayObject();
	pDlgMainWnd->displayRoiHighLight(ITEM_SGENNERAL_REGION,*pPara,*pShape); //2017.11-为与其他身普区区分，该区域高亮显示
}

//2017.7-恢复默认区域
void CDlgSGenReg::ResetReg()
{
	if (QMessageBox::No==QMessageBox::question(this,tr("Reset"),
		tr("The region will revert to the default shape,Do you want to continue?"),QMessageBox::Yes | QMessageBox::No))
		return;
	try
	{
		s_oSGenReg oSGenReg = pShape->value<s_oSGenReg>();
		if (ui.comboShapeType->currentIndex() == 0)
		{
			gen_contour_polygon_xld(&oSGenReg.oCheckRegion,
				HTuple(100).Concat(57).Concat(57).Concat(100).Concat(143).Concat(143).Concat(100),
				HTuple(50).Concat(75).Concat(125).Concat(150).Concat(125).Concat(75).Concat(50)); //默认多边形
		}
		else
		{
			gen_rectangle2_contour_xld(&oSGenReg.oCheckRegion_Rect,55,55,0,45,45);
		}
		//检测项形状改变标识符为真
		((MyLabelItem *)pDlgMainWnd->pItemLabel)->bShapeChanged = true;
		//模板原点更新为当前的原点！
		pDlgMainWnd->pChecker->modelOri = pDlgMainWnd->pChecker->currentOri;

		pShape->setValue(oSGenReg);
		pDlgMainWnd->displayObject();
		pDlgMainWnd->displayRoiHighLight(ITEM_SGENNERAL_REGION,*pPara,*pShape); //2017.11-为与其他身普区区分，该区域高亮显示
	}
	catch(HException &e)
	{
		//Halcon异常		
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

void CDlgSGenReg::typeChanged(int index)
{	
	//传入参数
	s_pSGenReg pSGenReg = pPara->value<s_pSGenReg>();
	pSGenReg.nShapeType = index;
	pPara->setValue(pSGenReg);

	// 2017.2---注释以下两行（bug：点击缺陷区域不显示提示信息&&点击身普区未修改参数退出提示需保存模板对话框）
	//pLabelItem->bParaChanged = true;
	//pDlgMainWnd->displayObject();
}

void CDlgSGenReg::setStoneDisplay()
{
	nButtonClicked = 0;
	ui.groupBox_Stone->setVisible(true);
	ui.groupBox_DarkDot->setVisible(false);
	ui.groupBox_TinyCrack->setVisible(false);
	ui.groupBox_LightStripe->setVisible(false);
	ui.groupBox_Bubbles->setVisible(false);
}

void CDlgSGenReg::setDarkDotDisplay()
{
	nButtonClicked = 1;
	ui.groupBox_Stone->setVisible(false);
	ui.groupBox_DarkDot->setVisible(true);
	ui.groupBox_TinyCrack->setVisible(false);
	ui.groupBox_LightStripe->setVisible(false);
	ui.groupBox_Bubbles->setVisible(false);
}

void CDlgSGenReg::setTinyCrackDisplay()
{
	nButtonClicked = 2;
	ui.groupBox_Stone->setVisible(false);
	ui.groupBox_DarkDot->setVisible(false);
	ui.groupBox_TinyCrack->setVisible(true);
	ui.groupBox_LightStripe->setVisible(false);
	ui.groupBox_Bubbles->setVisible(false);
}

void CDlgSGenReg::setLightStripeDisplay()
{
	nButtonClicked = 3;
	ui.groupBox_Stone->setVisible(false);
	ui.groupBox_DarkDot->setVisible(false);
	ui.groupBox_TinyCrack->setVisible(false);
	ui.groupBox_LightStripe->setVisible(true);
	ui.groupBox_Bubbles->setVisible(false);
}

void CDlgSGenReg::setBubblesDisplay()
{
	nButtonClicked = 4;
	ui.groupBox_Stone->setVisible(false);
	ui.groupBox_DarkDot->setVisible(false);
	ui.groupBox_TinyCrack->setVisible(false);
	ui.groupBox_LightStripe->setVisible(false);
	ui.groupBox_Bubbles->setVisible(true);
}

//2017.5---特殊缺陷复选框选中时，改变按钮样式
void CDlgSGenReg::setBtnsStyle()
{
	if (ui.checkStone->isChecked())
	{
		ui.btnStone->setStyleSheet("background-color: rgb(0,206,209)"); 
	}
	else
	{
		ui.btnStone->setStyleSheet("background:lightgray"); 
	}

	if (ui.checkDarkdot->isChecked())
	{
		ui.btnDarkDot->setStyleSheet("background-color: rgb(0,206,209)"); 
	}
	else
	{
		ui.btnDarkDot->setStyleSheet("background:lightgray");
	}

	if (ui.checkTinyCrack->isChecked())
	{
		ui.btnTinyCrack->setStyleSheet("background-color: rgb(0,206,209)"); 
	}
	else
	{
		ui.btnTinyCrack->setStyleSheet("background:lightgray");
	}

	if (ui.checkLightStripes->isChecked())
	{
		ui.btnLightStripe->setStyleSheet("background-color: rgb(0,206,209)"); 
	}
	else
	{
		ui.btnLightStripe->setStyleSheet("background:lightgray");
	}

	if (ui.checkBubbles->isChecked())
	{
		ui.btnBubbles->setStyleSheet("background-color: rgb(0,206,209)"); 
	}
	else
	{
		ui.btnBubbles->setStyleSheet("background:lightgray");
	}
}