#include "DlgCheckItemWizard.h"
#include "InnerData.h"

CDlgCheckItemWizard::CDlgCheckItemWizard(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	//layout()->setSizeConstraint(QLayout::SetFixedSize);//禁止缩放
	initItemTree();
	ui.okButton->setEnabled(false);
}

CDlgCheckItemWizard::~CDlgCheckItemWizard()
{

}

void CDlgCheckItemWizard::initItemTree()
{	
	ui.itemTree->setStyleSheet("QTreeWidget::item{height:24px}");
	ui.itemTree->setStyleSheet("font-size:16px");
	ui.itemTree->setColumnCount(1);
	ui.itemTree->setHeaderLabel(tr("DetectionItem Tree"));
	QList<QTreeWidgetItem *> rootList; 

	//常用检测项
	rootFrequentItem = new QTreeWidgetItem(ui.itemTree,QStringList(tr("FrequentItem")),ITEM_ROOT_FREQUENT_ITEM);
	sidewallLocateF = new QTreeWidgetItem(rootFrequentItem,QStringList(tr("BodyLocationF")),ITEM_SIDEWALL_LOCATE);
	sGeneralRegionF = new QTreeWidgetItem(rootFrequentItem,QStringList(tr("GeneralRegionF")),ITEM_SGENNERAL_REGION);
	bInnerRegionF = new QTreeWidgetItem(rootFrequentItem,QStringList(tr("InnerRegionF")),ITEM_BINNER_REGION);
	sSidewallRegionF = new QTreeWidgetItem(rootFrequentItem,QStringList(tr("BodyStressRegionF")),ITEM_SSIDEWALL_REGION);
	finishContourF = new QTreeWidgetItem(rootFrequentItem,QStringList(tr("MouthContourF")),ITEM_FINISH_CONTOUR);
	rootFrequentItem->addChild(sidewallLocateF);
	rootFrequentItem->addChild(sGeneralRegionF);
	rootFrequentItem->addChild(bInnerRegionF);
	rootFrequentItem->addChild(sSidewallRegionF);
	rootFrequentItem->addChild(finishContourF);

	//定位
	rootLocate = new QTreeWidgetItem(ui.itemTree,QStringList(tr("Location")),ITEM_ROOT_LOCATE);
	sidewallLocate = new QTreeWidgetItem(rootLocate,QStringList(tr("BodyLocation")),ITEM_SIDEWALL_LOCATE);
	finishLocate = new QTreeWidgetItem(rootLocate,QStringList(tr("MouthLoction")),ITEM_FINISH_LOCATE);
	baseLocate = new QTreeWidgetItem(rootLocate,QStringList(tr("BottomLoction")),ITEM_BASE_LOCATE);
	rootLocate->addChild(sidewallLocate);
	rootLocate->addChild(finishLocate);
	rootLocate->addChild(baseLocate);
	
	//尺寸
	rootSize = new QTreeWidgetItem(ui.itemTree,QStringList(tr("Size")),ITEM_ROOT_SIZE);
	horiSize = new QTreeWidgetItem(rootSize,QStringList(tr("HorizontalSize")),ITEM_HORI_SIZE);
	vertSize = new QTreeWidgetItem(rootSize,QStringList(tr("VerticalSize")),ITEM_VERT_SIZE);
	fullHeight = new QTreeWidgetItem(rootSize,QStringList(tr("fullHeight")),ITEM_FULL_HEIGHT);
	bentNeck = new QTreeWidgetItem(rootSize,QStringList(tr("BentNeck")),ITEM_BENT_NECK);
	vertAng = new QTreeWidgetItem(rootSize,QStringList(tr("VerticalAngle")),ITEM_VERT_ANG);
	circleSize = new QTreeWidgetItem(rootSize,QStringList(tr("CircleSize")),ITEM_CIRCLE_SIZE);	
	rootSize->addChild(horiSize);
	rootSize->addChild(vertSize);
	rootSize->addChild(fullHeight);
	rootSize->addChild(bentNeck);
	rootSize->addChild(vertAng);
	rootSize->addChild(circleSize);
	
	//区域
	rootRegion = new QTreeWidgetItem(ui.itemTree,QStringList(tr("Region")),ITEM_ROOT_REGION);
	sidewallRegion = new QTreeWidgetItem(rootRegion,QStringList(tr("BodyRegion")),ITEM_SIDEWALL_REGION);
	finishRegion = new QTreeWidgetItem(rootRegion,QStringList(tr("MouthRegion")),ITEM_FINISH_REGION);
	baseRegion = new QTreeWidgetItem(rootRegion,QStringList(tr("BottomRegion")),ITEM_BASE_REGION);
	stressRegion = new QTreeWidgetItem(rootRegion,QStringList(tr("StressRegion")),ITEM_STRESS_REGION);
	rootRegion->addChild(sidewallRegion);
	rootRegion->addChild(finishRegion);
	rootRegion->addChild(baseRegion);
	rootRegion->addChild(stressRegion);
		//-瓶身区域
	sGeneralRegion = new QTreeWidgetItem(sidewallRegion,QStringList(tr("GeneralRegion")),ITEM_SGENNERAL_REGION);
	sSideFinishRegion = new QTreeWidgetItem(sidewallRegion,QStringList(tr("MouthRegion")),ITEM_SSIDEFINISH_REGION);
	sInFinishRegion = new QTreeWidgetItem(sidewallRegion,QStringList(tr("InnerMouth")),ITEM_SINFINISH_REGION);
	sScrewFinishRegion = new QTreeWidgetItem(sidewallRegion,QStringList(tr("ScrewRegion")),ITEM_SSCREWFINISH_REGION);
	sBrightSpotRegion = new QTreeWidgetItem(sidewallRegion,QStringList(tr("BrightSpotRegion")),ITEM_SBRISPOT_REGION);
	sBaseConvexRegion = new QTreeWidgetItem(sidewallRegion,QStringList(tr("BaseConvexRegion")),ITEM_SBASECONVEX_REGION);
	sidewallRegion->addChild(sGeneralRegion);
	sidewallRegion->addChild(sSideFinishRegion);
	sidewallRegion->addChild(sInFinishRegion);
	sidewallRegion->addChild(sScrewFinishRegion);
	sidewallRegion->addChild(sBrightSpotRegion);
	sidewallRegion->addChild(sBaseConvexRegion);
		//-瓶口区域			
	fRingLightRegion = new QTreeWidgetItem(finishRegion,QStringList(tr("Ringlight")),ITEM_FRINGLIGHT_REGION);
	fBackLightRegion = new QTreeWidgetItem(finishRegion,QStringList(tr("Backlight")),ITEM_FBACKLIGHT_REGION);
	finishRegion->addChild(fRingLightRegion);
	finishRegion->addChild(fBackLightRegion);
			//--环形光
	fRLInnerRegion = new QTreeWidgetItem(fRingLightRegion,QStringList(tr("InnerRegion")),ITEM_FRLINNER_REGION);
	fRLMiddleRegion = new QTreeWidgetItem(fRingLightRegion,QStringList(tr("MiddleRegion")),ITEM_FRLMIDDLE_REGION);
	fRLOuterRegion = new QTreeWidgetItem(fRingLightRegion,QStringList(tr("OutterRegion")),ITEM_FRLOUTER_REGION);
	fRingLightRegion->addChild(fRLInnerRegion);
	fRingLightRegion->addChild(fRLMiddleRegion);
	fRingLightRegion->addChild(fRLOuterRegion);
		//--背光
	fBLInnerRegion = new QTreeWidgetItem(fBackLightRegion,QStringList(tr("InnerRegion")),ITEM_FBLINNER_REGION);
	fBLMiddleRegion = new QTreeWidgetItem(fBackLightRegion,QStringList(tr("MiddleRegion")),ITEM_FBLMIDDLE_REGION);
	fBackLightRegion->addChild(fBLInnerRegion);
	fBackLightRegion->addChild(fBLMiddleRegion);
	//-瓶底区域 2014.10.28 合并瓶底内环和中环区域，统一为内环区域
	bInnerRegion = new QTreeWidgetItem(baseRegion,QStringList(tr("InnerRegion")),ITEM_BINNER_REGION);
	//bMiddleRegion = new QTreeWidgetItem(baseRegion,QStringList(tr("MiddleRegion")),ITEM_BMIDDLE_REGION);
	bOuterRegion = new QTreeWidgetItem(baseRegion,QStringList(tr("OutterRegion")),ITEM_BOUTER_REGION);
	//通过瓶底条纹进行检测&&不加专门的电话线检测
	bAllRegion = new QTreeWidgetItem(baseRegion,QStringList(tr("AllRegion")),ITEM_BALL_REGION);
	baseRegion->addChild(bInnerRegion);
	//baseRegion->addChild(bMiddleRegion);
	baseRegion->addChild(bOuterRegion);
	baseRegion->addChild(bAllRegion);
	//-应力区域
	sSidewallRegion = new QTreeWidgetItem(stressRegion,QStringList(tr("BodyStressRegion")),ITEM_SSIDEWALL_REGION);
	sBaseRegion = new QTreeWidgetItem(stressRegion,QStringList(tr("BaseStressRegion")),ITEM_SBASE_REGION);
	stressRegion->addChild(sSidewallRegion);
	stressRegion->addChild(sBaseRegion);	
	//-干扰区域
	disturbRegion = new QTreeWidgetItem(rootRegion,QStringList(tr("DisturbleRegion")),ITEM_DISTURB_REGION)	;
	disturbRegion->addChild(rootRegion);
	//轮廓
	rootContour = new QTreeWidgetItem(ui.itemTree,QStringList(tr("Contour")),ITEM_ROOT_CONTOUR);	
	finishContour = new QTreeWidgetItem(rootContour,QStringList(tr("MouthContour")),ITEM_FINISH_CONTOUR);
	neckContour = new QTreeWidgetItem(rootContour,QStringList(tr("ShoulderContour")),ITEM_NECK_CONTOUR);
	bodyContour = new QTreeWidgetItem(rootContour,QStringList(tr("BodyContour")),ITEM_BODY_CONTOUR);
	rootContour->addChild(finishContour);
	rootContour->addChild(neckContour);
	rootContour->addChild(bodyContour);
	
	rootList<<rootLocate<<rootSize<<rootRegion<<rootContour;
	ui.itemTree->insertTopLevelItems(0,rootList);
	
	//信号槽
	connect(ui.itemTree,SIGNAL(itemClicked(QTreeWidgetItem*,int)),this,SLOT(showItemTips(QTreeWidgetItem*)));
	//全部展开
	ui.itemTree->expandAll();
}

void CDlgCheckItemWizard::showItemTips(QTreeWidgetItem* item)
{
	QFont font;
	font.setPointSize(14);
	ui.labelPreview->setFont(font);
	ui.labelDetail->setFont(font);
	nItemID = item->type();
	switch (nItemID)
	{
	case ITEM_ROOT_FREQUENT_ITEM:	
		ui.labelPreview->setText(tr("Null"));
		ui.labelDetail->setText(tr("Some of the most commonly used items are shown here."));
		ui.okButton->setEnabled(false);
		break;
	case ITEM_ROOT_LOCATE:	
		ui.labelPreview->setText(tr("Null"));
		ui.labelDetail->setText(tr("We can get the position of the bottle by calculating the offset of the coordinates origin ,"
			"in order to detect normally(eg. Size,Region ,Contour and so on) .No need to locate if the image of the bottle is stable."));
		ui.okButton->setEnabled(false);
		break;
	case ITEM_SIDEWALL_LOCATE:
		ui.labelPreview->setPixmap(QPixmap(":/checkItemWizard/Resources/images/checkItemWizard/sidewallLocate.png"));///
		ui.labelDetail->setText(tr("There are four methods to locate ,calculating the bottle horizontal, vertical offset, "
			"and rotation angle by the position of three lines ."));
		ui.okButton->setEnabled(true);
		break;
	case  ITEM_FINISH_LOCATE:
		ui.labelPreview->setPixmap(QPixmap(":/checkItemWizard/Resources/images/checkItemWizard/finishLocate.png"));//fstopShow.png
		//ui.labelPreview->setIcon(QPixmap(":/Resources/images/checkItemWizard/stopS.png"));
		ui.labelDetail->setText(tr("Calculates the center of the bottle mouth depending on the lighting program(eg. Ring light and Back light) ."));
		ui.okButton->setEnabled(true);
		break;
	case  ITEM_BASE_LOCATE:
		ui.labelPreview->setPixmap(QPixmap(":/checkItemWizard/Resources/images/checkItemWizard/baseLocate.png"));
		//ui.labelPreview->setIcon(QPixmap(":/Resources/images/imgTool/stopShow.png"));
		ui.labelDetail->setText(tr("There are three methods to locate depending on the effects of the bottle bottom image."));
		ui.okButton->setEnabled(true);
		break;
	/**/case ITEM_ROOT_SIZE:
		ui.labelPreview->setText(tr("Null"));
		ui.labelDetail->setText(tr("Detect size of the bottle(eg. diameter,height,bent neck,vertical angle of the bottle and so on)."
			"<font color=red>Note:the angle of grabing image is too less to cause error.</font>"));
		ui.okButton->setEnabled(false);
		break;
	case ITEM_HORI_SIZE:
		ui.labelPreview->setPixmap(tr(":/checkItemWizard/Resources/images/checkItemWizard/horiSize.png"));
		ui.labelDetail->setText(tr("Detect the distance between two horizontal points of the bottle."));
		ui.okButton->setEnabled(true);
		break;
	case ITEM_VERT_SIZE:
		ui.labelPreview->setPixmap(tr(":/checkItemWizard/Resources/images/checkItemWizard/vertSize.png"));
		ui.labelDetail->setText(tr("Detect the distance between two vertical points of the bottle."));
		ui.okButton->setEnabled(true);
		break;
	case ITEM_FULL_HEIGHT:
		ui.labelPreview->setPixmap(tr(":/checkItemWizard/Resources/images/checkItemWizard/fullHeight.png"));
		ui.labelDetail->setText(tr("Detect the height of the bottle."));
		ui.okButton->setEnabled(true);
		break;
	case ITEM_BENT_NECK:
		ui.labelPreview->setPixmap(tr(":/checkItemWizard/Resources/images/checkItemWizard/bentNeck.png"));
		ui.labelDetail->setText(tr("Detect bent neck by calculating the center of the bottle and the bottle "
			"body center ,iff the Location method is <font color=red>TranslationRotation</font>."));
		ui.okButton->setEnabled(true);
		break;
	case ITEM_VERT_ANG:
		ui.labelPreview->setPixmap(tr(":/checkItemWizard/Resources/images/checkItemWizard/vertAng.png"));
		ui.labelDetail->setText(tr("Detect the defect(eg. bottom partial,body tilt and so on)by calculating the vertical angle,"
			"iff the Location method is <font color=red>TranslationRotation</font>."));
		ui.okButton->setEnabled(true);
		break;
	case ITEM_CIRCLE_SIZE:
		ui.labelPreview->setPixmap(tr(":/checkItemWizard/Resources/images/checkItemWizard/circleSize.png"));
		ui.labelDetail->setText(tr("Detect the diameter and ovality of the ring."));
		ui.okButton->setEnabled(true);
		break;
	case ITEM_ROOT_REGION:	
		ui.labelPreview->setText(tr("Null"));
		ui.labelDetail->setText(tr("Detect the defect(eg. stone,bubble,crack and so on)by analyzing the connected "
			"region's shape, orientation,quantity,etc ."));
		ui.okButton->setEnabled(false);
		break;
	case ITEM_SIDEWALL_REGION:
		ui.labelPreview->setText(tr("Null"));
		ui.labelDetail->setText(tr("Detect the defect of the bottle body."));
		ui.okButton->setEnabled(false);
		break;
	case ITEM_SGENNERAL_REGION:
		ui.labelPreview->setPixmap(tr(":/checkItemWizard/Resources/images/checkItemWizard/genneralRegion.png"));
		ui.labelDetail->setText(tr("Detect the defect of the bottle body,applying in most region"));
		ui.okButton->setEnabled(true);
		break;
	case ITEM_SSIDEFINISH_REGION:
		ui.labelPreview->setPixmap(tr(":/checkItemWizard/Resources/images/checkItemWizard/sideFinishRegion.png"));
		ui.labelDetail->setText(tr("Detect the defect dedicating to the bottle mouth region,"
			"considering the horizontal shadow interference"));
		ui.okButton->setEnabled(true);
		break;
	case ITEM_SINFINISH_REGION:
		ui.labelPreview->setPixmap(tr(":/checkItemWizard/Resources/images/checkItemWizard/inFinishRegion.png"));
		ui.labelDetail->setText(tr("Detect the double mouth defect dedicating to the bottle inner mouth region."));
		ui.okButton->setEnabled(true);
		break;
	case ITEM_SSCREWFINISH_REGION:
		ui.labelPreview->setPixmap(tr(":/checkItemWizard/Resources/images/checkItemWizard/screwFinishRegion.png"));
		ui.labelDetail->setText(tr("Detect the defect(eg. crack,stone and so on)dedicating to the bottle screw region"));
		ui.okButton->setEnabled(true);
		break;
	case ITEM_FINISH_REGION:
		ui.labelPreview->setText(tr("Null"));
		ui.labelDetail->setText(tr("Detect the bottle mouth surface defect depending on"
			"the lighting program(eg. Ring light and Back light)."));
		ui.okButton->setEnabled(false);
		break;
	case ITEM_FRINGLIGHT_REGION:
		ui.labelPreview->setText(tr("Null"));
		ui.labelDetail->setText(tr("Detect the bottle mouth region in the ring light program,"
			"and its feature is white defects under the black background."));		
		ui.okButton->setEnabled(false);
		break;
	case ITEM_FRLINNER_REGION:
		ui.labelPreview->setPixmap(tr(":/checkItemWizard/Resources/images/checkItemWizard/fRLInnerRegion.png"));
		ui.labelDetail->setText(tr("Detect the defect(eg. deform,double mouth and so on) in the mouth inner ring."));
		ui.okButton->setEnabled(true);
		break;
	case ITEM_FRLMIDDLE_REGION:
		ui.labelPreview->setPixmap(tr(":/checkItemWizard/Resources/images/checkItemWizard/fRLMiddleRegion.png"));
		ui.labelDetail->setText(tr("Detect the defect(eg. bubble,crack,stone,scissors and so on) in the mouth middle ring."));
		ui.okButton->setEnabled(true);
		break;
	case ITEM_FRLOUTER_REGION:
		ui.labelPreview->setPixmap(tr(":/checkItemWizard/Resources/images/checkItemWizard/fRLOuterRegion.png"));
		ui.labelDetail->setText(tr("Detect the defect(eg. breach,etc.) in the mouth outter ring."));
		ui.okButton->setEnabled(true);
		break;
	case ITEM_FBACKLIGHT_REGION:
		ui.labelPreview->setText(tr("Null"));
		ui.labelDetail->setText(tr("Detect the bottle mouth region in the back light program,"
			"and its feature is black defects under the white background."));	
		ui.okButton->setEnabled(false);
		break;
	case ITEM_FBLINNER_REGION:
		ui.labelPreview->setPixmap(tr(":/checkItemWizard/Resources/images/checkItemWizard/fBLInnerRegion.png"));
		ui.labelDetail->setText(tr("Detect the defect(eg. deform,double mouth and so on) in the mouth inner ring."));
		ui.okButton->setEnabled(true);
		break;
	case ITEM_FBLMIDDLE_REGION:
		ui.labelPreview->setPixmap(tr(":/checkItemWizard/Resources/images/checkItemWizard/fBLMiddleRegion.png"));
		ui.labelDetail->setText(tr("Detect the defect(eg. crack,stone,scissors and so on) in the mouth middle ring."));
		ui.okButton->setEnabled(true);
		break;
	case ITEM_BASE_REGION:
		ui.labelPreview->setText(tr("Null"));
		ui.labelDetail->setText(tr("Detect the bottle bottom surface defect."));	
		ui.okButton->setEnabled(false);
		break;
	case ITEM_BINNER_REGION:
		ui.labelPreview->setPixmap(tr(":/checkItemWizard/Resources/images/checkItemWizard/bInnerRegion.png"));
		ui.labelDetail->setText(tr("Detect the defect(eg. light or dark bottom,bubble,crack,stone and so on) in the bottom inner ring."));	
		ui.okButton->setEnabled(true);
		break;
	case ITEM_BMIDDLE_REGION:
		ui.labelPreview->setPixmap(tr(":/checkItemWizard/Resources/images/checkItemWizard/bMiddleRegion.png"));
		ui.labelDetail->setText(tr("Detect the defect in the bottom middle ring such as inner ring,"
			"considering the special stripes interference."));	
		ui.okButton->setEnabled(true);
		break;
	case ITEM_BOUTER_REGION:
		ui.labelPreview->setPixmap(tr(":/checkItemWizard/Resources/images/checkItemWizard/bOuterRegion.png"));
		ui.labelDetail->setText(tr("Detect the defect in the slip belt region of the bottom outter ring."));	
		ui.okButton->setEnabled(true);
		break;
	case ITEM_BALL_REGION:
		ui.labelPreview->setPixmap(tr(":/checkItemWizard/Resources/images/checkItemWizard/bAllRegion.png"));
		ui.labelDetail->setText(tr("Detect the defect(eg.bottom wire) in all the bottom."));	
		ui.okButton->setEnabled(true);
		break;
	case ITEM_STRESS_REGION:
		ui.labelPreview->setText(tr("Null"));
		ui.labelDetail->setText(tr("Detect the stress defect."));
		ui.okButton->setEnabled(false);
		break;
	case ITEM_SSIDEWALL_REGION:
		ui.labelPreview->setPixmap(tr(":/checkItemWizard/Resources/images/checkItemWizard/sSidewallRegion.png"));
		ui.labelDetail->setText(tr("Detect the defect(eg. inner stress,stone stress and so on) in the bottle body stress image."));
		ui.okButton->setEnabled(true);
		break;
	case ITEM_SBASE_REGION:
		ui.labelPreview->setPixmap(tr(":/checkItemWizard/Resources/images/checkItemWizard/sBaseRegion.png"));
		ui.labelDetail->setText(tr("Detect the defect(eg. inner stress,stone stress and so on) in the bottle base stress image."));
		ui.okButton->setEnabled(true);
		break;
	case ITEM_DISTURB_REGION:
		ui.labelPreview->setPixmap(tr(":/checkItemWizard/Resources/images/checkItemWizard/disturbRegion.png"));
		ui.labelDetail->setText(tr("Use to exclude the interference(eg. stripes, pattern, characters, lines, and so on)."));
		ui.okButton->setEnabled(true);
		break;
	case ITEM_ROOT_CONTOUR:
		ui.labelPreview->setText(tr("Null"));
		ui.labelDetail->setText(tr("Detect the bottle contour defect by the edge of the bottle."));
		ui.okButton->setEnabled(false);
		break;
	case ITEM_FINISH_CONTOUR:
		ui.labelPreview->setPixmap(tr(":/checkItemWizard/Resources/images/checkItemWizard/finishContour.png"));
		ui.labelDetail->setText(tr("Detect the contour defect(eg. breach, deform,double mouth"
			"and so on) int the mouth region."));
		ui.okButton->setEnabled(true);
		break;
	case ITEM_NECK_CONTOUR:
		ui.labelPreview->setPixmap(tr(":/checkItemWizard/Resources/images/checkItemWizard/neckContour.png"));
		ui.labelDetail->setText(tr("Detect the contour defect(eg. shoulder collapse, sticky material,"
			"shoulder asymmetry and so on) int the shoulder region."));
		ui.okButton->setEnabled(true);
		break;
	case ITEM_BODY_CONTOUR:
		ui.labelPreview->setPixmap(tr(":/checkItemWizard/Resources/images/checkItemWizard/bodyContour.png"));
		ui.labelDetail->setText(tr("Detect the contour defect(eg. wings,bottle subsidence and so on) int the body region."));
		ui.okButton->setEnabled(true);
		break;
	case ITEM_SBRISPOT_REGION:
		ui.labelPreview->setPixmap(tr(":/checkItemWizard/Resources/images/checkItemWizard/brightSpotsRegion.png"));
		ui.labelDetail->setText(tr("Detect the bright spots defect."));
		ui.okButton->setEnabled(true);
		break;
	case ITEM_SBASECONVEX_REGION:
		ui.labelPreview->setPixmap(tr(":/checkItemWizard/Resources/images/checkItemWizard/baseConvexRegion.png"));
		ui.labelDetail->setText(tr("Detect the defect dedicating to the convex region of the red wine bottle base."));
		ui.okButton->setEnabled(true);
		break;
	default:
		break;
	}	
}
