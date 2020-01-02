#include "mylabelitem.h"
#include "InnerData.h"
#include <QMessageBox>
#include <QMouseEvent>

extern int g_nAlgType;

MyLabelItem::MyLabelItem(QWidget *parent,int ID,QString sName,QVariant *pModelPara,QVariant *pModelShape)
	: QLabel(parent)
{
	nID = ID;
	bParaChanged = false;
	bShapeChanged = false;
	bEnabled = true;
	bClicked = false;
	pPara = pModelPara;
	pShape = pModelShape;
	initLabelItem(g_nAlgType);
	//设置最小大小
	//setMinimumSize(20,40);
	//设置大小策略
	setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Maximum);
	//设置边框
	setFrameShape(QFrame::Box);
	//设置文字方向
	setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
	//设置自动换行
	setWordWrap(true);
	//生成样式表,设置颜色样式和状态栏信息
	genStyleSheet();
	setColStyle();
	//设置名字
	strName = sName;
	setText(strName);
}

MyLabelItem::~MyLabelItem()
{

}

void MyLabelItem::initLabelItem(int nAlgType/* = 0*/)
{
	switch(nAlgType)
	{
	case 1:
		//设置最小大小
		setMinimumSize(20,40);
		break;
	case 2:
		//设置最小大小
		setMinimumSize(80,40);
		break;
	default:
		//设置最小大小
		setMinimumSize(20,40);
		break;
	}
}

void MyLabelItem::genStyleSheet()
{
	//定义不同类型检测项的背景色
	QString colorLocBack = QString("rgb(%1,%2,%3)").arg(202).arg(215).arg(37);	
	QString colorSizeBack = QString("rgb(%1,%2,%3)").arg(102).arg(231).arg(84);	
	QString colorRegBack = QString("rgb(%1,%2,%3)").arg(0).arg(206).arg(209);  //2017.2-原70,66,230
	QString colorRegDtbBack = QString("rgb(%1,%2,%3)").arg(210).arg(196).arg(46);
	QString colorConBack = QString("rgb(%1,%2,%3)").arg(61).arg(171).arg(180);
	//定义相同的字体色、边框、鼠标停留色、按下颜色
	QString lsHead = "background-color:";
	QString lsTail = "; color: rgb(96,36,88);\
					 border-radius: 5px;border: 2px groove gray;";
	labelStyle_Loc		= lsHead+colorLocBack+lsTail;
	labelStyle_Size		= lsHead+colorSizeBack+lsTail;
	labelStyle_Reg		= lsHead+colorRegBack+lsTail;
	labelStyle_Reg_Dtb	= lsHead+colorRegDtbBack+lsTail;
	labelStyle_Con		= lsHead+colorConBack+lsTail;
	//labelPressStyle = "MyLabelItem{background-color:rgb(75,107,116); color:rgb(60,204,106) ;\
					  border-radius: 5px;  border: 2px groove gray;\
					  border-style: inset;}";
	labelPressStyle = "border-width:3px; border-style:solid; border-color:rgb(255,170,0);";
	labelErrorStyle = "MyLabelItem{background-color:rgb(255,0,0); color:rgb(96,36,88) ;\
					  border-radius: 5px;  border: 2px groove gray;}";
	labelDisableStyle = "background-color:rgb(150,150,150); color:rgb(96,96,96) ;\
					  border-radius: 5px;  border: 2px groove gray;";
}

void MyLabelItem::setColStyle()
{
	QString labelStyle;
	switch(nID)
	{
	case ITEM_SIDEWALL_LOCATE:		
		setStatusTip(tr("DetectionItem：Location--BodyLocation"));
		if (!bEnabled)
		{
			labelStyle = labelDisableStyle;
		}
		else
		{
			labelStyle = labelStyle_Loc;
		}
		if (bClicked)
		{
			labelStyle += labelPressStyle;			
		}
		break;
	case ITEM_FINISH_LOCATE:		
		setStatusTip(tr("DetectionItem：Location--MouthLocation"));		
		if (!bEnabled)
		{
			labelStyle = labelDisableStyle;
		}
		else
		{
			labelStyle = labelStyle_Loc;
		}
		if (bClicked)
		{
			labelStyle += labelPressStyle;			
		}
		break;
	case ITEM_BASE_LOCATE:		
		setStatusTip(tr("DetectionItem：Location--BottomLocation"));		
		if (!bEnabled)
		{
			labelStyle = labelDisableStyle;
		}
		else
		{
			labelStyle = labelStyle_Loc;
		}
		if (bClicked)
		{
			labelStyle += labelPressStyle;			
		}
		break;
	case ITEM_HORI_SIZE:		
		setStatusTip(tr("DetectionItem：Size--HorizontalSize"));		
		if (!bEnabled)
		{
			labelStyle = labelDisableStyle;
		}
		else
		{
			labelStyle = labelStyle_Size;
		}
		if (bClicked)
		{
			labelStyle += labelPressStyle;			
		}
		break;
	case ITEM_VERT_SIZE:		
		setStatusTip(tr("DetectionItem：Size--VerticalSize"));	
		if (!bEnabled)
		{
			labelStyle = labelDisableStyle;
		}
		else
		{
			labelStyle = labelStyle_Size;
		}
		if (bClicked)
		{
			labelStyle += labelPressStyle;			
		}
		break;
	case ITEM_FULL_HEIGHT:		
		setStatusTip(tr("DetectionItem：Size--FullHeight"));	
		if (!bEnabled)
		{
			labelStyle = labelDisableStyle;
		}
		else
		{
			labelStyle = labelStyle_Size;
		}
		if (bClicked)
		{
			labelStyle += labelPressStyle;			
		}
		break;
	case ITEM_BENT_NECK:
		setStatusTip(tr("DetectionItem：Size--BentNeck"));		
		if (!bEnabled)
		{
			labelStyle = labelDisableStyle;
		}
		else
		{
			labelStyle = labelStyle_Size;
		}
		if (bClicked)
		{
			labelStyle += labelPressStyle;			
		}
		break;
	case ITEM_VERT_ANG:
		setStatusTip(tr("DetectionItem：Size--VerticalAngle"));		
		if (!bEnabled)
		{
			labelStyle = labelDisableStyle;
		}
		else
		{
			labelStyle = labelStyle_Size;
		}
		if (bClicked)
		{
			labelStyle += labelPressStyle;			
		}
		break;
	case ITEM_SGENNERAL_REGION:
		setStatusTip(tr("DetectionItem：Region--BodyRegion--GeneralRegion"));
		if (!bEnabled)
		{
			labelStyle = labelDisableStyle;
		}
		else
		{
			labelStyle = labelStyle_Reg;
		}
		if (bClicked)
		{
			labelStyle += labelPressStyle;			
		}
		break;
	case ITEM_SSIDEFINISH_REGION:
		setStatusTip(tr("DetectionItem：Region--BodyRegion--MouthRegion"));
		if (!bEnabled)
		{
			labelStyle = labelDisableStyle;
		}
		else
		{
			labelStyle = labelStyle_Reg;
		}
		if (bClicked)
		{
			labelStyle += labelPressStyle;			
		}
		break;
	case ITEM_SINFINISH_REGION:
		setStatusTip(tr("DetectionItem：Region--BodyRegion--InnerMouth"));
		if (!bEnabled)
		{
			labelStyle = labelDisableStyle;
		}
		else
		{
			labelStyle = labelStyle_Reg;
		}
		if (bClicked)
		{
			labelStyle += labelPressStyle;			
		}
		break;
	case ITEM_SSCREWFINISH_REGION:
		setStatusTip(tr("DetectionItem：Region--BodyRegion--ScrewRegion"));
		if (!bEnabled)
		{
			labelStyle = labelDisableStyle;
		}
		else
		{
			labelStyle = labelStyle_Reg;
		}
		if (bClicked)
		{
			labelStyle += labelPressStyle;			
		}
		break;
	case ITEM_FRLINNER_REGION:
		setStatusTip(tr("DetectionItem：Region--MouthRegion--Ringlight--InnerRegion"));
		if (!bEnabled)
		{
			labelStyle = labelDisableStyle;
		}
		else
		{
			labelStyle = labelStyle_Reg;
		}
		if (bClicked)
		{
			labelStyle += labelPressStyle;			
		}
		break;
	case ITEM_FRLMIDDLE_REGION:
		setStatusTip(tr("DetectionItem：Region--MouthRegion--Ringlight--MiddleRegion"));
		if (!bEnabled)
		{
			labelStyle = labelDisableStyle;
		}
		else
		{
			labelStyle = labelStyle_Reg;
		}
		if (bClicked)
		{
			labelStyle += labelPressStyle;			
		}
		break;
	case ITEM_FRLOUTER_REGION:
		setStatusTip(tr("DetectionItem：Region--MouthRegion--Ringlight--OutterRegion"));
		if (!bEnabled)
		{
			labelStyle = labelDisableStyle;
		}
		else
		{
			labelStyle = labelStyle_Reg;
		}
		if (bClicked)
		{
			labelStyle += labelPressStyle;			
		}
		break;
	case ITEM_FBLINNER_REGION:
		setStatusTip(tr("DetectionItem：Region--MouthRegion--Backlight--InnerRegion"));
		if (!bEnabled)
		{
			labelStyle = labelDisableStyle;
		}
		else
		{
			labelStyle = labelStyle_Reg;
		}
		if (bClicked)
		{
			labelStyle += labelPressStyle;			
		}
		break;
	case ITEM_FBLMIDDLE_REGION:
		setStatusTip(tr("DetectionItem：Region--MouthRegion--Backlight--MiddleRegion"));
		if (!bEnabled)
		{
			labelStyle = labelDisableStyle;
		}
		else
		{
			labelStyle = labelStyle_Reg;
		}
		if (bClicked)
		{
			labelStyle += labelPressStyle;			
		}
		break;
	case ITEM_BINNER_REGION:
		setStatusTip(tr("DetectionItem：Region--BottomRegion--InnerRegion"));
		if (!bEnabled)
		{
			labelStyle = labelDisableStyle;
		}
		else
		{
			labelStyle = labelStyle_Reg;
		}
		if (bClicked)
		{
			labelStyle += labelPressStyle;			
		}
		break;
	case ITEM_BMIDDLE_REGION:
		setStatusTip(tr("DetectionItem：Region--BottomRegion--MiddleRegion"));
		if (!bEnabled)
		{
			labelStyle = labelDisableStyle;
		}
		else
		{
			labelStyle = labelStyle_Reg;
		}
		if (bClicked)
		{
			labelStyle += labelPressStyle;			
		}
		break;
	case ITEM_BOUTER_REGION:
		setStatusTip(tr("DetectionItem：Region--BottomRegion--OutterRegion"));
		if (!bEnabled)
		{
			labelStyle = labelDisableStyle;
		}
		else
		{
			labelStyle = labelStyle_Reg;
		}
		if (bClicked)
		{
			labelStyle += labelPressStyle;			
		}
		break;
	case ITEM_BALL_REGION:
		setStatusTip(tr("DetectionItem：Region--BottomRegion--AllRegion"));
		if (!bEnabled)
		{
			labelStyle = labelDisableStyle;
		}
		else
		{
			labelStyle = labelStyle_Reg;
		}
		if (bClicked)
		{
			labelStyle += labelPressStyle;			
		}
		break;
	case ITEM_SSIDEWALL_REGION:
		setStatusTip(tr("DetectionItem：Region--StressRegion--BodyStressRegion"));
		if (!bEnabled)
		{
			labelStyle = labelDisableStyle;
		}
		else
		{
			labelStyle = labelStyle_Reg;
		}
		if (bClicked)
		{
			labelStyle += labelPressStyle;			
		}
		break;
	case ITEM_SBASE_REGION:
		setStatusTip(tr("DetectionItem：Region--StressRegion--BaseStressRegion"));
		if (!bEnabled)
		{
			labelStyle = labelDisableStyle;
		}
		else
		{
			labelStyle = labelStyle_Reg;
		}
		if (bClicked)
		{
			labelStyle += labelPressStyle;			
		}
		break;
	case ITEM_DISTURB_REGION:
		setStatusTip(tr("DetectionItem：Region--DisturbleRegion"));
		if (!bEnabled)
		{
			labelStyle = labelDisableStyle;
		}
		else
		{
			labelStyle = labelStyle_Reg_Dtb;
		}
		if (bClicked)
		{
			labelStyle += labelPressStyle;			
		}
		break;
	case ITEM_FINISH_CONTOUR:
		setStatusTip(tr("DetectionItem：Contour--MouthContour"));
		if (!bEnabled)
		{
			labelStyle = labelDisableStyle;
		}
		else
		{
			labelStyle = labelStyle_Con;
		}
		if (bClicked)
		{
			labelStyle += labelPressStyle;			
		}
		break;
	case ITEM_NECK_CONTOUR:
		setStatusTip(tr("DetectionItem：Contour--ShoulderContour"));
		if (!bEnabled)
		{
			labelStyle = labelDisableStyle;
		}
		else
		{
			labelStyle = labelStyle_Con;
		}
		if (bClicked)
		{
			labelStyle += labelPressStyle;			
		}
		break;
	case ITEM_BODY_CONTOUR:
		setStatusTip(tr("DetectionItem：Contour--BodyContour"));
		if (!bEnabled)
		{
			labelStyle = labelDisableStyle;
		}
		else
		{
			labelStyle = labelStyle_Con;
		}
		if (bClicked)
		{
			labelStyle += labelPressStyle;			
		}
		break;
	case ITEM_SBRISPOT_REGION:
		setStatusTip(tr("DetectionItem：Region--BodyRegion--BrightSpotRegion"));
		if (!bEnabled)
		{
			labelStyle = labelDisableStyle;
		}
		else
		{
			labelStyle = labelStyle_Con;
		}
		if (bClicked)
		{
			labelStyle += labelPressStyle;			
		}
		break;
	case ITEM_CIRCLE_SIZE:		
		setStatusTip(tr("DetectionItem：Size--CircleSize"));	
		if (!bEnabled)
		{
			labelStyle = labelDisableStyle;
		}
		else
		{
			labelStyle = labelStyle_Size;
		}
		if (bClicked)
		{
			labelStyle += labelPressStyle;			
		}
		break;
	case ITEM_SBASECONVEX_REGION:
		setStatusTip(tr("DetectionItem：Region--BodyRegion--BaseConvexRegion"));
		if (!bEnabled)
		{
			labelStyle = labelDisableStyle;
		}
		else
		{
			labelStyle = labelStyle_Reg;
		}
		if (bClicked)
		{
			labelStyle += labelPressStyle;			
		}
		break;
	default:
		break;
	}
	setStyleSheet(labelStyle);
}
