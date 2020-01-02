#include "DlgBaseLocate.h"

CDlgBaseLocate::CDlgBaseLocate(QWidget *parent,QVariant *pCheckPara,QVariant *pCheckShape)
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
	connect(ui.checkRectShape,SIGNAL(clicked(bool)), this,SLOT(isRectShape(bool)));//add liuxu20180802this
	connect(ui.btnCentReg,SIGNAL(clicked()),this,SLOT(drawCentReg()));
	connect(ui.btnModeNOEdge,SIGNAL(clicked()),this,SLOT(drawModeNOEdge()));	
	connect(ui.btnBeltDia,SIGNAL(clicked()),this,SLOT(drawBeltDia()));
	connect(ui.btnAutoCalib,SIGNAL(clicked()),this,SLOT(loctionCalibrate()));
	connect(ui.btnHandCalib,SIGNAL(clicked()),this,SLOT(handCalibrate()));	
	//初始化对话框
	initDialog();
	//设置“这是什么”文本
	setHelpTips();	
}

CDlgBaseLocate::~CDlgBaseLocate()
{

}

void CDlgBaseLocate::initDialog()
{
	s_pBaseLoc pBaseLoc = pPara->value<s_pBaseLoc>();
	//初始化控件
	QStringList strlMethods;
	strlMethods<<tr("SegmentLocate(Recommend)")<<tr("EdgeLocate")<<tr("SlipbeltLocate")<<
		tr("InnerLocate(RedWine)")<<tr("SlipbitLocate")<<tr("EdgeLocate(ModeNO)")<<tr("InnerRingLocate(RedWine)")<<
		tr("CompositeLocation(Stress)")<<tr("GrayLocate")<<tr("LocateShape")/**/;
	ui.comboMethod->addItems(strlMethods);
	//显示参数
	ui.comboMethod->setCurrentIndex(pBaseLoc.nMethodIdx);
	ui.checkIgnore->setChecked(pBaseLoc.bIgnore);
	ui.spinSegRatio->setValue(pBaseLoc.fSegRatio);
	ui.spinGray->setValue(pBaseLoc.nGray);
	ui.spinEdge->setValue(pBaseLoc.nEdge);
	ui.spinRadiusOffset->setValue(pBaseLoc.nRadiusOffset);
	ui.spinBeltSpace->setValue(pBaseLoc.nBeltSpace);
	ui.spinBeltWidth->setValue(pBaseLoc.nBeltWidth);
	ui.spinBeltHeight->setValue(pBaseLoc.nBeltHeight);
	ui.spinBeltEdge->setValue(pBaseLoc.nBeltEdge);
	ui.spinMoveOffset->setValue(pBaseLoc.nMoveOffset);
	ui.spinMoveStep->setValue(pBaseLoc.nMoveStep);
	ui.checkRectShape->setChecked(pBaseLoc.bRectShape);
	//i_shape = 4;
}
void CDlgBaseLocate::isRectShape(bool bRectSp)
{
	ui.groupBelt->setVisible(bRectSp);//new add
	ui.groupBelt_4->setVisible(bRectSp); //new adding
	//if(ui.comboMethod->currentIndex() == 9)
	//{
	//	ui.groupBelt->setVisible(true);//new add
	//	ui.groupBelt_4->setVisible(true); //new adding
	//}
	if(bRectSp)
	{
		ui.comboMethod->setCurrentIndex(9);
		//set other false
		ui.groupSeg->setVisible(false);//want to like methodChanged,but need input index
		ui.groupScale->setVisible(false);	
		ui.groupInner->setVisible(false);	
		ui.groupBelt_2->setVisible(false);
		ui.groupEdgeModeNO->setVisible(false);
		ui.groupStress->setVisible(false);
		ui.groupGrayLocate->setVisible(false);
		ui.label_9->setVisible(false);
	}
	//else
	//{
	//	ui.comboMethod->setCurrentIndex(4);
	//}
}
void CDlgBaseLocate::methodChanged(int index)
{	
   // if(!ui.checkRectShape->isChecked())	
	//{
	if(index<=8)
	{
		ui.checkRectShape->setChecked(false);
	}
	if (index==9)
	{
		ui.checkRectShape->setChecked(true);
		//ui.label_BeltHeight->setVisible(false);
	}
	ui.groupSeg->setVisible(index==0 || index==2 || index==3 || index==4|| index==6);
	ui.groupScale->setVisible(index==0 || index==2 || index==4 || index==6);	
	ui.groupInner->setVisible(index==3);	
	ui.groupBelt->setVisible(index==2 || index==4 || index==8 || index==9);//new add
	ui.groupBelt_2->setVisible(index==2);
	ui.groupBelt_4->setVisible(index==4|| index==9); //new adding
	ui.groupEdgeModeNO->setVisible(index == 5);
	ui.groupStress->setVisible(index == 7);
	ui.groupGrayLocate->setVisible(index == 8);
	ui.label_9->setVisible(index == 8);
	
}

void CDlgBaseLocate::setHelpTips()
{	
	ui.comboMethod->setWhatsThis(tr("Depending on different images and types of bottle,5 methods are available:<br>"
		"<b>SegmentLocate:</b>most commonly used method,using the features that bottom is brighter than the surrounding bottle,locate by binary segmentation;<br>"
		"<b>EdgeLocate:</b>suitable for images that the light of the bottom is similar with the surrounding bottle,but its edge is clear;<br>"
		"<b>SlipbeltLocate：</b>it's supplement of SegmentLocate.When bottom is brighter than the surrounding bottle,but the position of "
		"the bright region is far away the center of bottom,correct origin by slip belt;<br>"
		"<b>InnerLocate</b>：suitable for red wine bottle that bottom is uneven,origin can be sure by the black ring in the center of bottom;<br>"
		"<b>SlipbitLocate</b>：it's supplement of SegmentLocate.Correct origin by slip bit;<br>"
		"<b>SlipbitLocateRect</b>:It's supplement of SegmentLocate.Correct origin by rectangle bit shape alginment;<br>"
		"<b>GrayLocate</b>：In this method, the average gray value in the ring is calculated by the moving ring, and the final location is obtained"));
	ui.btnCentReg->setWhatsThis(tr("For <i>SegmentLocate</i>,<i>SlipbeltLocate</i> and <i>SlipbitLocate</i>,set inner ring in the center of bottom,"
		"the radius of inner ring should be set 1/3 radius of bottom.For <i>InnerLocate</i>,inner ring should be set in the black ring of the bottom"));
	ui.spinSegRatio->setWhatsThis(tr("For <i>SegmentLocate</i>,<i>SlipbeltLocate</i> and <i>SlipbitLocate</i>,defalt value is <font color = red>0.75</font>,"
		"means the segment scale. For <i>InnerLocate</i>,defalt value is <font color = red>0.5</font>,means the extracting gray value"));
	ui.btnBeltDia->setWhatsThis(tr("Setting the radius of the slip belt,use to correct origin"));
	ui.spinBeltSpace->setWhatsThis(tr("Set the distance between the adjacent two belt bit by <b>measuring</b>,units are in pixels"));	
	ui.spinBeltWidth->setWhatsThis(tr("Set the width of the belt bit by <b>measuring</b>,units are in pixels"));	
	ui.spinBeltHeight->setWhatsThis(tr("Set the height of the belt bit by <b>measuring</b>,units are in pixels"));
	ui.spinBeltEdge->setWhatsThis(tr("Set the contrast of the belt,units are in pixels"));
	ui.spinMoveOffset->setWhatsThis(tr("Set the moving scope of the ring,units are in pixels"));
	ui.spinMoveStep->setWhatsThis(tr("Set the moving step of the ring,units are in pixels"));
}

void CDlgBaseLocate::apply()
{
	//((MyLabelItem*)parentWidget())->bParaChanged = true;//通知父窗口模板参数改变
	pLabelItem->bParaChanged = true;
	//传入参数
	s_pBaseLoc pBaseLoc = pPara->value<s_pBaseLoc>();
	pBaseLoc.nMethodIdx = ui.comboMethod->currentIndex();
	pBaseLoc.fSegRatio = ui.spinSegRatio->value();
	pBaseLoc.nGray = ui.spinGray->value();
	pBaseLoc.nEdge = ui.spinEdge->value();
	pBaseLoc.nRadiusOffset = ui.spinRadiusOffset->value();
	pBaseLoc.nBeltSpace = ui.spinBeltSpace->value();
	pBaseLoc.nBeltWidth = ui.spinBeltWidth->value();
	pBaseLoc.nBeltHeight = ui.spinBeltHeight->value();
	pBaseLoc.bIgnore = ui.checkIgnore->isChecked();
	pBaseLoc.nBeltEdge = ui.spinBeltEdge->value();
	pBaseLoc.nMoveOffset = ui.spinMoveOffset->value();
	pBaseLoc.nMoveStep = ui.spinMoveStep->value();
	pBaseLoc.bRectShape = ui.checkRectShape->isChecked();
	/*if(pBaseLoc.bRectShape)
	i_shape = 2;
	else
	i_shape = 4;*/
	pPara->setValue(pBaseLoc);
}

void CDlgBaseLocate::accept()
{
	apply();
	return QDialog::accept();
}

void CDlgBaseLocate::autoAccept()
{
	apply();
}

void CDlgBaseLocate::drawCentReg()
{
	s_oBaseLoc oBaseLoc = pShape->value<s_oBaseLoc>();
	//pDlgMainWnd->adjustShape(this,oBaseLoc.oCentReg,DRAW_CIRCLE);//DRAW_CIRCLE
	if (ui.checkRectShape->isChecked())
	{
		pDlgMainWnd->adjustShape(this,oBaseLoc.oCentReg_Rect,DRAW_RECTANGLE); //新增矩形
	}
	else
	{
		pDlgMainWnd->adjustShape(this,oBaseLoc.oCentReg,DRAW_CIRCLE);  //default circle
	}
	pShape->setValue(oBaseLoc);
	pDlgMainWnd->displayObject(ui.comboMethod->currentIndex());
}

void CDlgBaseLocate::drawModeNOEdge()
{
	s_oBaseLoc oBaseLoc = pShape->value<s_oBaseLoc>();
	//pDlgMainWnd->adjustShape(this,oBaseLoc.oModeNOEdge,i_shape);//DRAW_CIRCLE
	if (ui.checkRectShape->isChecked())
	{
		pDlgMainWnd->adjustShape(this,oBaseLoc.oModeNOEdge_Rect,DRAW_RECTANGLE); //新增矩形
	}
	else
	{
		pDlgMainWnd->adjustShape(this,oBaseLoc.oModeNOEdge,DRAW_CIRCLE);  //default circle
	}
	pShape->setValue(oBaseLoc);
	pDlgMainWnd->displayObject(ui.comboMethod->currentIndex());
}

void CDlgBaseLocate::drawBeltDia()
{
	s_oBaseLoc oBaseLoc = pShape->value<s_oBaseLoc>();
	//pDlgMainWnd->adjustShape(this,oBaseLoc.oBeltDia,i_shape);//DRAW_CIRCLE
	if (ui.checkRectShape->isChecked())
	{
		pDlgMainWnd->adjustShape(this,oBaseLoc.oBeltDia_Rect,DRAW_RECTANGLE); //新增矩形
	}
	else
	{
		pDlgMainWnd->adjustShape(this,oBaseLoc.oBeltDia,DRAW_CIRCLE);  //default circle
	}
	pShape->setValue(oBaseLoc);
	if(true == oBaseLoc.ifGenSp) oBaseLoc.ifGenSp = false;
	pDlgMainWnd->displayObject(ui.comboMethod->currentIndex());
	
}
void CDlgBaseLocate::loctionCalibrate()
{
	//仅应力可用
	int nIdx = ui.comboMethod->currentIndex();
	if (nIdx != 7)
	{
		QMessageBox::information(this,tr("Note"),tr("This calibration is used only for the stress image！"));	
		return;
	}
	s_oBaseLoc oBaseLoc = pShape->value<s_oBaseLoc>();	
	//仅读取参数，用于定位正常图像，确定当前原点
	s_pBaseLoc pBaseLoc = pPara->value<s_pBaseLoc>();
	pBaseLoc.nMethodIdx = ui.comboMethod->currentIndex();
	pBaseLoc.fSegRatio = ui.spinSegRatio->value();
	pBaseLoc.nRadiusOffset = ui.spinRadiusOffset->value();
	pBaseLoc.nBeltSpace = ui.spinBeltSpace->value();
	pBaseLoc.nBeltWidth = ui.spinBeltWidth->value();
	pBaseLoc.nBeltHeight = ui.spinBeltHeight->value();
	pBaseLoc.bIgnore = ui.checkIgnore->isChecked();
	pBaseLoc.nBeltEdge = ui.spinBeltEdge->value();
	pBaseLoc.nMoveOffset = ui.spinMoveOffset->value();
	pBaseLoc.nMoveStep = ui.spinMoveStep->value();
	//定位
	RtnInfo rtnInfo;
	switch(pBaseLoc.nMethodIdx)
	{
	case 0:
		rtnInfo = pDlgMainWnd->pChecker->findPosBaseSeg(pDlgMainWnd->pChecker->m_ImageSrc,oBaseLoc,pBaseLoc);
		break;
	case 1:
		rtnInfo = pDlgMainWnd->pChecker->findPosBaseEdge(pDlgMainWnd->pChecker->m_ImageSrc,oBaseLoc,pBaseLoc);
		break;
	case 2:
		rtnInfo = pDlgMainWnd->pChecker->findPosBaseBelt(pDlgMainWnd->pChecker->m_ImageSrc,oBaseLoc,pBaseLoc);
		break;
	case 3:
		rtnInfo = pDlgMainWnd->pChecker->findPosBaseCircle(pDlgMainWnd->pChecker->m_ImageSrc,oBaseLoc,pBaseLoc);
		break;
	case 4:
		rtnInfo = pDlgMainWnd->pChecker->findPosBaseBeltEx(pDlgMainWnd->pChecker->m_ImageSrc,oBaseLoc,pBaseLoc);
		break;
	case 5:
		rtnInfo = pDlgMainWnd->pChecker->findPosBaseEdgeMode(pDlgMainWnd->pChecker->m_ImageSrc,oBaseLoc,pBaseLoc);
		break;
	case 6:
		rtnInfo = pDlgMainWnd->pChecker->findPosBaseRing(pDlgMainWnd->pChecker->m_ImageSrc,oBaseLoc,pBaseLoc);
		break;	
	case 8: 
		rtnInfo = pDlgMainWnd->pChecker->findPosBaseGray(pDlgMainWnd->pChecker->m_ImageSrc,oBaseLoc,pBaseLoc);
		break;	
	default:
		break;
	}
	//原点
	if (rtnInfo.nType>0)
	{
		QMessageBox::information(this,tr("Note"),tr("Calibration failure！Can't find the origin of the current image!"));	
		return;
	}
	else
	{
		//原点更新标志
		pLabelItem->bShapeChanged = true;
		oBaseLoc.drow1 = pDlgMainWnd->pChecker->normalOri.Row;
		oBaseLoc.dcol1 = pDlgMainWnd->pChecker->normalOri.Col;
		oBaseLoc.dradius1 = pDlgMainWnd->pChecker->normalOri.Radius;
		oBaseLoc.drow2 = oBaseLoc.Row;
		oBaseLoc.dcol2 = oBaseLoc.Col;
		oBaseLoc.dradius2 = oBaseLoc.Radius;
		float fscale;//正常与应力图像缩放比例 
		if (0 == oBaseLoc.dradius1 || 0 == oBaseLoc.dradius2)
		{
			fscale = 1;
		}
		else
		{
			fscale = oBaseLoc.dradius2/oBaseLoc.dradius1;
		}
		oBaseLoc.Row = oBaseLoc.drow2 + (pDlgMainWnd->pChecker->normalOri.Row-oBaseLoc.drow1)*fscale;
		oBaseLoc.Col = oBaseLoc.dcol2 + (pDlgMainWnd->pChecker->normalOri.Col-oBaseLoc.dcol1)*fscale;
		oBaseLoc.Radius = pDlgMainWnd->pChecker->normalOri.Radius*fscale;
	}
	pShape->setValue(oBaseLoc);
	pDlgMainWnd->displayObject(ui.comboMethod->currentIndex());
}

void CDlgBaseLocate::handCalibrate()
{
	//仅应力可用
	int nIdx = ui.comboMethod->currentIndex();
	if (nIdx != 7)
	{
		QMessageBox::information(this,tr("Note"),tr("This calibration is used only for the stress image！"));	
		return;
	}
	s_oBaseLoc oBaseLoc = pShape->value<s_oBaseLoc>();	
	Hobject regOriCir;
	gen_circle(&regOriCir,oBaseLoc.Row,oBaseLoc.Col,oBaseLoc.Radius);
	pDlgMainWnd->adjustShape(this,regOriCir,DRAW_CIRCLE);

	//原点更新标志
	oBaseLoc.drow1 = pDlgMainWnd->pChecker->normalOri.Row;
	oBaseLoc.dcol1 = pDlgMainWnd->pChecker->normalOri.Col;
	oBaseLoc.dradius1 = pDlgMainWnd->pChecker->normalOri.Radius;
	smallest_circle(regOriCir,&oBaseLoc.drow2,&oBaseLoc.dcol2,&oBaseLoc.dradius2);
	oBaseLoc.Row = oBaseLoc.drow2;
	oBaseLoc.Col = oBaseLoc.dcol2;
	oBaseLoc.Radius = oBaseLoc.dradius2;
	pShape->setValue(oBaseLoc);
	pDlgMainWnd->displayObject(ui.comboMethod->currentIndex());
}
