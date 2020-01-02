#include "DlgBInReg.h"

CDlgBInReg::CDlgBInReg(QWidget *parent,QVariant *pCheckPara,QVariant *pCheckShape)
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
	connect(ui.comboMethod,SIGNAL(currentIndexChanged(int)),this,SLOT(methodChanged(int)));
	connect(ui.btnResetBase,SIGNAL(clicked()),this,SLOT(ResetBaseShape()));
	connect(ui.btnInCircle,SIGNAL(clicked()),this,SLOT(drawInCircle()));	
	connect(ui.btnOutCircle,SIGNAL(clicked()),this,SLOT(drawOutCircle()));
	connect(ui.btnSetShape,SIGNAL(clicked()),this,SLOT(drawPolyShape()));
	connect(ui.btnAutoDraw,SIGNAL(clicked()),this,SLOT(autodraw()));
	connect(ui.btnMark,SIGNAL(clicked()),this,SLOT(drawMark()));
	connect(ui.btnChar,SIGNAL(clicked()),this,SLOT(drawChar()));
	connect(ui.checkChar,SIGNAL(clicked()),this,SLOT(enableMark()));
	connect(ui.btnBinRegExp_Def,SIGNAL(clicked()),this,SLOT(fbtnBinRegExp_Def()));	
	//初始化对话框
	initDialog();
	//设置“这是什么”文本
	setHelpTips();

}

CDlgBInReg::~CDlgBInReg()
{

}

void CDlgBInReg::initDialog()
{
    ui.groupBox->setVisible(false);
	s_pBInReg pBInReg = pPara->value<s_pBInReg>();
	//初始化控件
	QStringList strlMethods;
	strlMethods<<tr("Circle")<<tr("Ring")<<tr("Rectangle")<<tr("TriBase");
	ui.comboMethod->addItems(strlMethods);
	QStringList strlOperation1,strlOperation2;
	strlOperation1<<tr("Or")<<tr("And");
	strlOperation2<<tr("Or")<<tr("And");
	ui.comboOperation1->addItems(strlOperation1);
	ui.comboOperation2->addItems(strlOperation2);
	//显示参数
	ui.comboMethod->setCurrentIndex(pBInReg.nMethodIdx);
	ui.spinEdge1->setValue(pBInReg.nEdge1);
	ui.spinArea1->setValue(pBInReg.nArea1);
	ui.comboOperation1->setCurrentIndex(pBInReg.nOperation1);
	ui.spinLen1->setValue(pBInReg.nLen1);
	ui.spinMeanGray1->setValue(pBInReg.nMeanGray1);
	ui.spinEdge2->setValue(pBInReg.nEdge2);
	ui.spinArea2->setValue(pBInReg.nArea2);
	ui.comboOperation2->setCurrentIndex(pBInReg.nOperation2);
	ui.spinLen2->setValue(pBInReg.nLen2);
	ui.spinMeanGray2->setValue(pBInReg.nMeanGray2);
	ui.checkOpen->setChecked(pBInReg.bOpen);
	ui.spinOpenSize->setValue(pBInReg.fOpenSize);
	ui.checkBottomDL->setChecked(pBInReg.bBottomDL);
	ui.spinDarkGray->setValue(pBInReg.nDarkB);
	ui.spinLightGray->setValue(pBInReg.nLightB);
	ui.checkArc->setChecked(pBInReg.bArc);
	ui.spinArcEdge->setValue(pBInReg.nArcEdge);
	ui.spinArcWidth->setValue(pBInReg.nArcWidth);
	ui.checkChar->setChecked(pBInReg.bChar);
	ui.spinCharNum->setValue(pBInReg.nCharNum);
	ui.checkDoubleScale->setChecked(pBInReg.bDoubleScale);
	ui.spinEdgeMin->setValue(pBInReg.nEdgeMin);
	ui.spinEdgeMax->setValue(pBInReg.nEdgeMax);
	ui.spinAreaMin->setValue(pBInReg.nAreaMin);
	ui.spinScaleRatio->setValue(pBInReg.fScaleRatio);
	ui.checkSpot->setChecked(pBInReg.bSpot);
	ui.spinAreaSpot->setValue(pBInReg.nAreaSpot);
	ui.spinRoundness->setValue(pBInReg.fSpotRound);
	ui.spinSpotNum->setValue(pBInReg.nSpotNum);

	ui.checkStripe->setChecked(pBInReg.bStrip);
	ui.spinStripeEdge->setValue(pBInReg.nStripEdge);
	ui.spinStripeArea->setValue(pBInReg.nStripArea);
	ui.spinStripeHeight->setValue(pBInReg.nStripHeight);
	ui.spinStripeWidthL->setValue(pBInReg.nStripWidthL);
	ui.spinStripeWidthH->setValue(pBInReg.nStripWidthH);
	ui.spinStripeAnisometry->setValue(pBInReg.fStripRab);
	ui.spinStripeAngleL->setValue(pBInReg.nStripAngleL);
	ui.spinStripeAngleH->setValue(pBInReg.nStripAngleH);

	ui.btnMark->setEnabled(pBInReg.bChar);
	ui.btnChar->setEnabled(pBInReg.bChar);
}

void CDlgBInReg::setHelpTips()
{	
	ui.labelCondition1->setWhatsThis(tr("This is used to check defects with <font color=red> smaller Edge but longger Area/Length<.font>"));
	ui.labelCondition2->setWhatsThis(tr("This is used to check defects with <font color=red> bigger Edge but smaller Area/Length<.font>"));
	ui.comboOperation1->setWhatsThis(tr("Specity the relationship between <i>Area</i> and <i>Length</i>,“or” means that either one be "
		"satisfied will report an error,“and” means both of them need to be satisfied"));
	ui.comboOperation2->setWhatsThis(tr("Specity the relationship between <i>Area</i> and <i>Length</i>,“or” means that either one be "
		"satisfied will report an error,“and” means both of them need to be satisfied"));
	ui.checkBottomDL->setWhatsThis(tr("This is used to check defects as: finish is blocked by impurities and the image is all black, "
		"or bottom is broken and the image is all white"));
}
void CDlgBInReg::apply()
{
	//((MyLabelItem*)parentWidget())->bParaChanged = true;//通知父窗口模板参数改变
	pLabelItem->bParaChanged = true;
	//传入参数
	s_pBInReg pBInReg = pPara->value<s_pBInReg>();
	pBInReg.nMethodIdx = ui.comboMethod->currentIndex();
	pBInReg.nEdge1 = ui.spinEdge1->value();
	pBInReg.nArea1 = ui.spinArea1->value();
	pBInReg.nOperation1 = ui.comboOperation1->currentIndex();
	pBInReg.nLen1 = ui.spinLen1->value();
	pBInReg.nMeanGray1 = ui.spinMeanGray1->value();
	pBInReg.nEdge2 = ui.spinEdge2->value();
	pBInReg.nArea2 = ui.spinArea2->value();
	pBInReg.nOperation2 = ui.comboOperation2->currentIndex();
	pBInReg.nLen2 = ui.spinLen2->value();
	pBInReg.nMeanGray2 = ui.spinMeanGray2->value();
	pBInReg.bOpen = ui.checkOpen->isChecked();
	pBInReg.fOpenSize = ui.spinOpenSize->value();
	pBInReg.bBottomDL = ui.checkBottomDL->isChecked();
	pBInReg.nDarkB = ui.spinDarkGray->value();
	pBInReg.nLightB = ui.spinLightGray->value();
	pBInReg.bArc = ui.checkArc->isChecked();
	pBInReg.nArcEdge = ui.spinArcEdge->value();
	pBInReg.nArcWidth = ui.spinArcWidth->value();
	pBInReg.bChar = ui.checkChar->isChecked();
	pBInReg.nCharNum = ui.spinCharNum->value();
	pBInReg.bDoubleScale = ui.checkDoubleScale->isChecked();
	pBInReg.nEdgeMin = ui.spinEdgeMin->value();
	pBInReg.nEdgeMax = ui.spinEdgeMax->value();
	pBInReg.nAreaMin = ui.spinAreaMin->value();
	pBInReg.fScaleRatio = ui.spinScaleRatio->value();
	pBInReg.bSpot = ui.checkSpot->isChecked();
	pBInReg.nAreaSpot = ui.spinAreaSpot->value();
	pBInReg.fSpotRound = ui.spinRoundness->value();
	pBInReg.nSpotNum = ui.spinSpotNum->value();

	pBInReg.bStrip = ui.checkStripe->isChecked();
	pBInReg.nStripEdge = ui.spinStripeEdge->value();
	pBInReg.nStripArea = ui.spinStripeArea->value();
	pBInReg.nStripHeight = ui.spinStripeHeight->value();
	pBInReg.nStripWidthL = ui.spinStripeWidthL->value();
	pBInReg.nStripWidthH = ui.spinStripeWidthH->value();
	pBInReg.fStripRab = ui.spinStripeAnisometry->value();
	pBInReg.nStripAngleL = ui.spinStripeAngleL->value();
	pBInReg.nStripAngleH = ui.spinStripeAngleH->value();
	pPara->setValue(pBInReg); 
}

void CDlgBInReg::accept()
{
	apply();
	return QDialog::accept();
}

void CDlgBInReg::autoAccept()
{
	apply();
}

void CDlgBInReg::methodChanged(int index)//方形瓶底和异形瓶底诉求一致
{
	//改变时直接赋值，方便显示正确区域-未点确定也保存，可能有误解
	s_pBInReg pBInReg = pPara->value<s_pBInReg>();
	pBInReg.nMethodIdx = index;
	pPara->setValue(pBInReg);
	ui.btnInCircle->setVisible(index==1);
	ui.btnOutCircle->setVisible(index==1 || index==0);
	ui.btnSetShape->setVisible(index==3 || index == 2);
	ui.btnResetBase->setVisible(index==3 || index == 2);
	
	ui.horizontalLayout_2->setEnabled(index==0 || index==1 || index==3 || index == 2);
	ui.horizontalLayout_3->setEnabled(index==0 || index==1 || index==3 || index == 2); 
	ui.horizontalLayout->setEnabled(index==0 || index==1 || index==3 || index == 2);
	ui.horizontalLayout_17->setEnabled(index==0 || index==1 || index==3 || index == 2);
	ui.groupBox_3->setVisible(index==0 || index==1 || index==3 || index == 2);
	ui.groupBox_2->setVisible(index==0 || index==1 || index==3 || index == 2);
	//ui.groupBox_3->setVisible(index==0 || index==1 || index==3);
	//ui.btnInCircle->setVisible(index==1);
}
void CDlgBInReg::ResetBaseShape()
{
	if (QMessageBox::No==QMessageBox::question(this,tr("Reset"),
		tr("The region will revert to the default shape,Do you want to continue?"),QMessageBox::Yes | QMessageBox::No))
		return;
	try
	{
		//s_oSGenReg oSGenReg = pShape->value<s_oSGenReg>();
		s_oBInReg oBInReg = pShape->value<s_oBInReg>();
		if (ui.comboMethod->currentIndex() == 3)
		{
				gen_contour_polygon_xld(&oBInReg.oTriBase,HTuple(0).Concat(202).Concat(488).Concat(478).Concat(378).Concat(246).Concat(150).Concat(0),HTuple(186).Concat(0).Concat(180).Concat(334).Concat(452).Concat(498).Concat(502).Concat(186));
		}
		else if (ui.comboMethod->currentIndex() == 2)
		{
		        gen_rectangle2_contour_xld(&oBInReg.oRectBase,55,55,0,45,45); 
		}
	
		//检测项形状改变标识符为真
		((MyLabelItem *)pDlgMainWnd->pItemLabel)->bShapeChanged = true;
		//模板原点更新为当前的原点！
		//pDlgMainWnd->pChecker->modelOri = pDlgMainWnd->pChecker->currentOri;

		pShape->setValue(oBInReg);
		pDlgMainWnd->displayObject();
		pDlgMainWnd->displayRoiHighLight(ITEM_BINNER_REGION,*pPara,*pShape); //ITEM_SGENNERAL_REGION2017.11-为与其他身普区区分，该区域高亮显示
	}
	catch(HException &e)
	{
		//Halcon异常		
		QString tempStr,strErr;
		tempStr=e.message;
		tempStr.remove(0,20);
		strErr = QString("abnormal:ResetBaseShape,")+ tempStr;
		pDlgMainWnd->pChecker->writeErrDataRecord(strErr);
	}
	catch (...)
	{
		pDlgMainWnd->pChecker->writeErrDataRecord(QString("abnormal:ResetBaseShape"));		
	}
}
void CDlgBInReg::drawPolyShape()
{
    s_oBInReg oBInReg = pShape->value<s_oBInReg>();
	if(ui.comboMethod->currentIndex() == 3)
	{
		pDlgMainWnd->adjustShape(this,oBInReg.oTriBase,DRAW_TRIBASEXLD);
	}
	else if(ui.comboMethod->currentIndex() == 2)
	{
	    pDlgMainWnd->adjustShape(this,oBInReg.oRectBase,DRAW_RECTANGLE);
	}
	pShape->setValue(oBInReg);
	pDlgMainWnd->displayObject();
	pDlgMainWnd->displayRoiHighLight(ITEM_BINNER_REGION,*pPara,*pShape); 
}
void CDlgBInReg::drawInCircle()
{
	s_oBInReg oBInReg = pShape->value<s_oBInReg>();
	pDlgMainWnd->adjustShape(this,oBInReg.oInCircle,DRAW_CIRCLE);
	pShape->setValue(oBInReg);
	pDlgMainWnd->displayObject();
	pDlgMainWnd->displayRoiHighLight(ITEM_BINNER_REGION,*pPara,*pShape); 
}

void CDlgBInReg::drawOutCircle()
{
	s_oBInReg oBInReg = pShape->value<s_oBInReg>();
	pDlgMainWnd->adjustShape(this,oBInReg.oOutCircle,DRAW_CIRCLE);
	pShape->setValue(oBInReg);
	pDlgMainWnd->displayObject();
	pDlgMainWnd->displayRoiHighLight(ITEM_BINNER_REGION,*pPara,*pShape);
}

void CDlgBInReg::autodraw()
{
	//是否有瓶口定位
	bool bLocate = false;
	int i;
	for (i=0;i<pDlgMainWnd->pChecker->vItemFlow.size();++i)
	{
		switch(pDlgMainWnd->pChecker->vItemFlow[i])
		{
		case ITEM_BASE_LOCATE:
			{
				s_pBaseLoc pBaseLoc = pDlgMainWnd->pChecker->vModelParas[i].value<s_pBaseLoc>();
				bLocate = true;
				break;
			}
		}
	}
	//无定位模块不自动重绘返回
	if (!bLocate)
	{
		return;
	}
	//定位
	Hobject tempobj;
	pDlgMainWnd->pChecker->rtnInfo = pDlgMainWnd->pChecker->fnFindCurrentPos(tempobj);
	if (0 != pDlgMainWnd->pChecker->rtnInfo.nType)
	{
		pDlgMainWnd->displayObject();
		pDlgMainWnd->displayRoiHighLight(ITEM_BINNER_REGION,*pPara,*pShape);
		return;
	}	
	//更新区域
	s_oBInReg oBInReg = pShape->value<s_oBInReg>();
	gen_circle(&oBInReg.oOutCircle,pDlgMainWnd->pChecker->currentOri.Row,pDlgMainWnd->pChecker->currentOri.Col,max(pDlgMainWnd->pChecker->currentOri.Radius-70,30));
	gen_circle(&oBInReg.oInCircle,pDlgMainWnd->pChecker->currentOri.Row,pDlgMainWnd->pChecker->currentOri.Col,max(pDlgMainWnd->pChecker->currentOri.Radius/3,10));
	pShape->setValue(oBInReg);
	pDlgMainWnd->displayObject();
	pDlgMainWnd->displayRoiHighLight(ITEM_BINNER_REGION,*pPara,*pShape);
}

void CDlgBInReg::drawMark()
{
	s_oBInReg oBInReg = pShape->value<s_oBInReg>();
	s_pBInReg pBInReg = pPara->value<s_pBInReg>();
	pDlgMainWnd->adjustShape(this,oBInReg.oCurMarkReg,DRAW_CIRCLE);
	oBInReg.oMarkReg=oBInReg.oCurMarkReg;
	Hobject regMark;
	Hlong nNum;
	//gen_region_contour_xld(oBInReg.oMarkReg,&regMark,"filled");
	regMark = oBInReg.oMarkReg;
	select_shape(regMark,&regMark,"area","and",100,99999999);
	count_obj(regMark,&nNum);
	if (nNum==0)
	{
		QMessageBox::critical(this,tr("Error"),tr("Fail to create shape model because the Mark is too small!"));
		return;
	}
	Hobject imgReduced;
	reduce_domain(pDlgMainWnd->imgShow,regMark,&imgReduced);
	try
	{
		create_shape_model(imgReduced,"auto",-PI,PI,"auto","auto","use_polarity","auto","auto",&oBInReg.ModelID);
	}
	catch(HException &e)
	{
		//Halcon异常		
		QString tempStr;
		tempStr=e.message;  
		tempStr.remove(0,20);
		int nErr;
		nErr = e.err;
		if (nErr == 8510)
		{
			QMessageBox::critical(this,tr("Error"),tr("Number of shape model points too small!"));
		}
		else
		{
			QMessageBox::critical(this,tr("Error"),tempStr);
		}		
		return;
	}
	double dRow1, dCol1, dCenRow, dCenCol, dPhi;
	dCenRow = pDlgMainWnd->pChecker->currentOri.Row;
	dCenCol = pDlgMainWnd->pChecker->currentOri.Col;
	smallest_circle(regMark, &dRow1, &dCol1, NULL);
	line_orientation(dRow1, dCol1, dCenRow, dCenCol, &dPhi);
	if (dCol1 < dCenCol && dRow1 > dCenRow)
	{
		dPhi -= PI;
	}
	else if (dCol1 < dCenCol && dRow1 <= dCenRow)
	{
		dPhi += PI;
	}
	pBInReg.dModelPhi = dPhi;

	pShape->setValue(oBInReg);
	pPara->setValue(pBInReg);
	pDlgMainWnd->pChecker->m_nBaseCharModelID = oBInReg.ModelID;
	pDlgMainWnd->displayObject();
	pDlgMainWnd->displayRoiHighLight(ITEM_BINNER_REGION,*pPara,*pShape);
}

void CDlgBInReg::drawChar()
{
	s_oBInReg oBInReg = pShape->value<s_oBInReg>();
	pDlgMainWnd->adjustShape(this,oBInReg.oCurCharReg,DRAW_POLYGON);
	oBInReg.oCharReg = oBInReg.oCurCharReg;
	pShape->setValue(oBInReg);
	pDlgMainWnd->displayObject();
	pDlgMainWnd->displayRoiHighLight(ITEM_BINNER_REGION,*pPara,*pShape);
}

void CDlgBInReg::enableMark()
{
	if (ui.checkChar->isChecked())
	{
		ui.btnMark->setEnabled(true);
		ui.btnChar->setEnabled(true);
	}
	else
	{
		ui.btnMark->setEnabled(false);
		ui.btnChar->setEnabled(false);
	}
}
//liuxu 2018-3 瓶底花纹及字符排除是否可以改为上面的"+"隐藏开关
void CDlgBInReg::fbtnBinRegExp_Def()
{
	QString strName = ui.btnBinRegExp_Def->text();
	if (strName=="+")
	{
		ui.btnBinRegExp_Def->setText("-");
		ui.groupBox->setVisible(true);
	}
	else if (strName=="-")
	{
		ui.btnBinRegExp_Def->setText("+");
		ui.groupBox->setVisible(false);
	}		
}