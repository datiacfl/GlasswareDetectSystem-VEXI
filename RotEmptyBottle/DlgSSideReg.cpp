#include "DlgSSideReg.h"

CDlgSSideReg::CDlgSSideReg(QWidget *parent,QVariant *pCheckPara,QVariant *pCheckShape)
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
	connect(ui.btnResetReg,SIGNAL(clicked()),this,SLOT(ResetReg()));
	connect(ui.Stone,SIGNAL(clicked()),this,SLOT(beStone()));
	connect(ui.Crack,SIGNAL(clicked()),this,SLOT(beCrack()));
	connect(ui.comboShapeType,SIGNAL(currentIndexChanged(int)),this,SLOT(typeChanged(int)));
	//初始化对话框
	initDialog();
	//设置“这是什么”文本
	setHelpTips();
}

CDlgSSideReg::~CDlgSSideReg()
{

}
void CDlgSSideReg::initDialog()
{
	s_pSSideReg pSSidgeReg = pPara->value<s_pSSideReg>();
	//初始化控件
	QStringList strlTypes;
	strlTypes<<tr("Polygon")<<tr("Rect");
	ui.comboShapeType->addItems(strlTypes);
	//显示参数
	ui.comboShapeType->setCurrentIndex(pSSidgeReg.nShapeType);
	ui.spinEdge->setValue(pSSidgeReg.nEdge);
	ui.spinGray->setValue(pSSidgeReg.nGray);
	ui.spinArea->setValue(pSSidgeReg.nArea);
	ui.spinRab->setValue(pSSidgeReg.fRab);	
	ui.spinSideDistance->setValue(pSSidgeReg.nSideDistance);
	//ui.Stone->
	if (pSSidgeReg.bInspItem==1)
	{
		ui.Crack->setChecked(true);
		ui.groupBox_SpeDefects->setVisible(true);
		ui.checkDisturbCondition1->setChecked(pSSidgeReg.bDistCon1);
		ui.spinDisConVerPhi->setValue(pSSidgeReg.nDistVerPhi);
		ui.spinDisConAniL1->setValue(pSSidgeReg.nDistAniL1);
		ui.spinDisConAniH1->setValue(pSSidgeReg.nDistAniH1);
		ui.spinDisConInRadiusL1->setValue(pSSidgeReg.nDistInRadiusL1);
		ui.spinDisConInRadiusH1->setValue(pSSidgeReg.nDistInRadiusH1);
		ui.checkDisturbCondition2->setChecked(pSSidgeReg.bDistCon2);

		ui.spinDisConHorPhi->setValue(pSSidgeReg.nDistHorPhi);
		ui.spinDisConAniL2->setValue(pSSidgeReg.nDistAniL2);
		ui.spinDisConAniH2->setValue(pSSidgeReg.nDistAniH2);
		ui.spinDisConInRadiusL2->setValue(pSSidgeReg.nDistInRadiusL2);
		ui.spinDisConInRadiusH2->setValue(pSSidgeReg.nDistInRadiusH2);
	}
	if (pSSidgeReg.bInspItem==0)
	{
		ui.Stone->setChecked(true);
		ui.groupBox_SpeDefects->setVisible(false);
	}

}
void CDlgSSideReg::setHelpTips()
{	
	ui.spinEdge->setWhatsThis(tr("The edge between defect region and background should be longer than the setting value,"
		"set <font color=red>the smaller,the more sensitive</font>"));
	ui.spinGray->setWhatsThis(tr("Adding the region that the gray value is bigger than the setting value of the gray to the defect region,"
		"in order to compensate that the big defect region isn't completely extracted by the contrast"));
	ui.spinArea->setWhatsThis(tr("Region is determined as a defect when its area is bigger than the setting value，"
		"and set<font color=red>the smaller,the more sensitive</font>"));
	ui.spinRab->setWhatsThis(tr("Region is determined as a defect when its anisometry is smaller than the setting value，"
		"the relationship of <i>area</i> and <i>length</i> is 'and'，both of them need to be satisfied，"
		"This is uesd to<font color = red>avoid stripes region that caused by reflective be reported as an error</font>"));
}

void CDlgSSideReg::apply()
{
	//((MyLabelItem*)parentWidget())->bParaChanged = true;//通知父窗口模板参数改变
	pLabelItem->bParaChanged = true;
	//传入参数
	s_pSSideReg pSSideReg = pPara->value<s_pSSideReg>();
	pSSideReg.nShapeType = ui.comboShapeType->currentIndex();
	pSSideReg.nEdge = ui.spinEdge->value();
	pSSideReg.nGray = ui.spinGray->value();
	pSSideReg.nArea = ui.spinArea->value();
	pSSideReg.fRab = ui.spinRab->value();
	pSSideReg.nSideDistance = ui.spinSideDistance->value();
	pSSideReg.bInspItem = ui.Stone->isChecked()?0:1;    //->is->isChecked()?1:(ui.radioRight->isChecked()?2:3);

	pSSideReg.bDistCon1 = ui.checkDisturbCondition1->isChecked() && pSSideReg.bInspItem;
	pSSideReg.nDistVerPhi = ui.spinDisConVerPhi->value();
	pSSideReg.nDistAniL1 = ui.spinDisConAniL1->value();
	pSSideReg.nDistAniH1 = ui.spinDisConAniH1->value();
	pSSideReg.nDistInRadiusL1 = ui.spinDisConInRadiusL1->value();
	pSSideReg.nDistInRadiusH1 = ui.spinDisConInRadiusH1->value();
	pSSideReg.bDistCon2 = ui.checkDisturbCondition2->isChecked() && pSSideReg.bInspItem; //保证Stone是为false
	pSSideReg.nDistHorPhi = ui.spinDisConHorPhi->value();
	pSSideReg.nDistAniL2 = ui.spinDisConAniL2->value();
	pSSideReg.nDistAniH2 = ui.spinDisConAniH2->value();
	pSSideReg.nDistInRadiusL2 = ui.spinDisConInRadiusL2->value();
	pSSideReg.nDistInRadiusH2 = ui.spinDisConInRadiusH2->value();
	pPara->setValue(pSSideReg);
}

void CDlgSSideReg::accept()
{
	apply();
	return QDialog::accept();
}

void CDlgSSideReg::autoAccept()
{
	apply();
}

void CDlgSSideReg::drawReg()
{
	s_oSSideReg oSSideReg = pShape->value<s_oSSideReg>();
	if (ui.comboShapeType->currentIndex() == 0)
	{
		pDlgMainWnd->adjustShape(this,oSSideReg.oCheckRegion,DRAW_POLYGON);  //默认多边形
	}
	else
	{
		pDlgMainWnd->adjustShape(this,oSSideReg.oCheckRegion_Rect,DRAW_RECTANGLE); //新增矩形
	}
	pShape->setValue(oSSideReg);
	pDlgMainWnd->displayObject();
	pDlgMainWnd->displayRoiHighLight(ITEM_SSIDEWALL_REGION,*pPara,*pShape); 
}

//2017.7-恢复默认区域
void CDlgSSideReg::ResetReg()
{
	if (QMessageBox::No==QMessageBox::question(this,tr("Reset"),
		tr("The region will revert to the default shape,Do you want to continue?"),QMessageBox::Yes | QMessageBox::No))
		return;
	try
	{
		s_oSSideReg oSSideReg = pShape->value<s_oSSideReg>();
		if (ui.comboShapeType->currentIndex() == 0)
		{
			gen_contour_polygon_xld(&oSSideReg.oCheckRegion,
				HTuple(100).Concat(57).Concat(57).Concat(100).Concat(143).Concat(143).Concat(100),
				HTuple(50).Concat(75).Concat(125).Concat(150).Concat(125).Concat(75).Concat(50)); //默认多边形
		}
		else
		{
			gen_rectangle2_contour_xld(&oSSideReg.oCheckRegion_Rect,55,55,0,45,45);
		}
		//检测项形状改变标识符为真
		((MyLabelItem *)pDlgMainWnd->pItemLabel)->bShapeChanged = true;
		//模板原点更新为当前的原点！
		pDlgMainWnd->pChecker->modelOri = pDlgMainWnd->pChecker->currentOri;

		pShape->setValue(oSSideReg);
		pDlgMainWnd->displayObject();
		pDlgMainWnd->displayRoiHighLight(ITEM_SSIDEWALL_REGION,*pPara,*pShape); 
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

void CDlgSSideReg::typeChanged(int index)
{	
	//传入参数
	s_pSSideReg pSSideReg = pPara->value<s_pSSideReg>();
	pSSideReg.nShapeType = index;
	pPara->setValue(pSSideReg);

}

void CDlgSSideReg::beStone( )
{
	s_pSSideReg pSSideReg = pPara->value<s_pSSideReg>();
	ui.groupBox_SpeDefects->setVisible(false);
	pSSideReg.bDistCon1 = false;
	pSSideReg.bDistCon2 = false;
	pPara->setValue(pSSideReg);
}

void CDlgSSideReg::beCrack( )
{
	ui.groupBox_SpeDefects->setVisible(true);//bDistCon1 和bDistCon2 不一定全为true
}