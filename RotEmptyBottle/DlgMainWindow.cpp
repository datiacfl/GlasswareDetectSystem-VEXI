#include "DlgMainWindow.h"
#include "check.h"
#include "InfoZip.h"
#include "DlgCopyModel.h"
#include <QDesktopWidget>
#include "CItemDlg.h"
//#define NDEBUG
#include <QFile> 
#include <assert.h>
extern int nMaxCamareWidth;

CDlgMainWindow::CDlgMainWindow(s_AlgModelPara &imgData)
{
	if(NULL == imgData.sImgPara.pcData) //s_Xld_Point not check yet
		MessageBoxA(NULL,"image pointer is  null dlgmainwindow_line15", "risk", MB_OK);
	//assert(NULL == s_AlgModelPara.sImgPara.pcData);
	
	//װ�ؽ���
	ui.setupUi(this);
	//����
	nImgWidth = imgData.sImgPara.nWidth;
	nImgHeight = imgData.sImgPara.nHeight;
	nImgChannel = imgData.sImgPara.nChannel;
	cImgData = imgData.sImgPara.pcData;

	sAlgCInp.sImgLocInfo.sXldPoint.nCount = 0;
	sAlgCInp.sImgLocInfo.sXldPoint.nRowsAry = new int[BOTTLEXLD_POINTNUM]();
	sAlgCInp.sImgLocInfo.sXldPoint.nColsAry = new int[BOTTLEXLD_POINTNUM]();


	//���ü�����еĵ㼯ת����,�ֳ���ʵ�ֹ��ܣ��Ժ����Ż�
	CCheck tempcheck;

	strCloseWindow = "";
	translator = NULL;
	fWndScale = 0.5;	
	nParentWndWidth = 1200;
	nParentWndHeight = 960;
	nTittleHeight = 0;
	m_bDrawing = false;	
	bShowShape = true;	
	bMeasure = false;
	bDistDone = false;
	m_bEnableItem = false;
	pItemDlg = NULL;
	pItemLabel = NULL;
	bResetFlag = false;
	bReadNewModel = false;
	labelWndScale = new QLabel("WndSize");	
	labelCamIndex = new QLabel("CamIdx");
	labelLanguage = new QLabel("Language");
	comboWndScale = new QComboBox;
	comboCamIndex = new QComboBox;
	comboLanguage = new QComboBox;
}
QWidget* CDlgMainWindow::paramWidget()
{
	
}

bool CDlgMainWindow::init(QWidget *parent/* = NULL*/)
{
	try
	{
		//��ʼ�����ڿ��
		QSettings algSet("daheng","GlasswareAlg"); //дע���
		//	nWndScale = algSet.value("nWndScale",4).toInt();//2013.9.9 nanjc Ĭ��ֵ����Ӧ���ڴ�С�����������ļ���ȡ
		nLangIndex = algSet.value("nLangIndex",0).toInt();
		//����ͼ��

		//��������Ӧ���ڴ�С
		QWidget *desktop;
		int ititleHeight;//�и�����ʱ�ޱ�����
		if (NULL != parent)
		{
			desktop = parent;
			ititleHeight = 0;
		}
		else
		{
			//desktop=QApplication::desktop();
			ititleHeight = 30; 
		}
		nParentWndWidth = desktop->width();
		nParentWndHeight = desktop->height();

		// 2017.11-��ʼ�������С&����		
		setStyleSheet("font-size:15px;background-color: lightgray;");

		// ���ذ�ťͼƬ [7/24/2015 zhaodt]
		QPixmap tempPixmap;
		tempPixmap = QPixmap(":/Resources/images/imgTool/openImg.png");
		//ui.pbtnImgOpen->setStyleSheet(tr("border-image:url(:/Resources/images/imgTool/openImg.png);"));
		ui.pbtnImgOpen->setIcon(tempPixmap);
		ui.pbtnImgOpen->setFixedSize(tempPixmap.width()+5,tempPixmap.height()+5);
		tempPixmap = QPixmap(":/Resources/images/imgTool/saveImg.png");
		ui.pbtnImgSave->setIcon(tempPixmap);
		ui.pbtnImgSave->setFixedSize(tempPixmap.width()+5,tempPixmap.height()+5);
		tempPixmap = QPixmap(":/Resources/images/imgTool/previousImg.png");
		ui.pbtnImgPre->setIcon(tempPixmap);
		ui.pbtnImgPre->setFixedSize(tempPixmap.width()+5,tempPixmap.height()+5);
		tempPixmap = QPixmap(":/Resources/images/imgTool/nextImg.png");
		ui.pbtnImgNext->setIcon(tempPixmap);
		ui.pbtnImgNext->setFixedSize(tempPixmap.width()+5,tempPixmap.height()+5);
		tempPixmap = QPixmap(":/Resources/images/imgTool/originalImg.png");
		ui.pbtnImgOriginal->setIcon(tempPixmap);
		ui.pbtnImgOriginal->setFixedSize(tempPixmap.width()+5,tempPixmap.height()+5);
		tempPixmap = QPixmap(":/Resources/images/imgTool/paintedImg.png");
		ui.pbtnImgPainted->setIcon(tempPixmap);
		ui.pbtnImgPainted->setFixedSize(tempPixmap.width()+5,tempPixmap.height()+5);
		tempPixmap = QPixmap(":/Resources/images/imgTool/resetShape.png");
		ui.pbtnRegReset->setIcon(tempPixmap);
		ui.pbtnRegReset->setFixedSize(tempPixmap.width()+5,tempPixmap.height()+5);
		tempPixmap = QPixmap(":/Resources/images/imgTool/measureImg.png");
		ui.pbtnImgMeasure->setIcon(tempPixmap);
		ui.pbtnImgMeasure->setFixedSize(tempPixmap.width()+5,tempPixmap.height()+5);
		tempPixmap = QPixmap(":/Resources/images/imgTool/continueShow.png");
		ui.pbtnShowContinue->setIcon(tempPixmap);
		ui.pbtnShowContinue->setFixedSize(tempPixmap.width()+5,tempPixmap.height()+5);
		tempPixmap = QPixmap(":/Resources/images/imgTool/stopAtErrorShow.png");
		ui.pbtnShowStop->setIcon(tempPixmap);
		ui.pbtnShowStop->setFixedSize(tempPixmap.width()+5,tempPixmap.height()+5);
		tempPixmap = QPixmap(":/Resources/images/imgTool/addItem.png");
		ui.pbtnAddItem->setIcon(tempPixmap);
		ui.pbtnAddItem->setFixedSize(tempPixmap.width()+5,tempPixmap.height()+5);
		tempPixmap = QPixmap(":/Resources/images/imgTool/insertItem.png");
		ui.pbtnInsertItem->setIcon(tempPixmap);
		ui.pbtnInsertItem->setFixedSize(tempPixmap.width()+5,tempPixmap.height()+5);
		tempPixmap = QPixmap(":/Resources/images/imgTool/deleteItem.png");
		ui.pbtnDeleteItem->setIcon(tempPixmap);
		ui.pbtnDeleteItem->setFixedSize(tempPixmap.width()+5,tempPixmap.height()+5);
		tempPixmap = QPixmap(":/Resources/images/imgTool/renameItem.png");
		ui.pbtnRenameItem->setIcon(tempPixmap);
		ui.pbtnRenameItem->setFixedSize(tempPixmap.width()+5,tempPixmap.height()+5);
		tempPixmap = QPixmap(":/Resources/images/imgTool/disableItem.png");
		ui.pbtnEnableItem->setIcon(tempPixmap);
		ui.pbtnEnableItem->setFixedSize(tempPixmap.width()+5,tempPixmap.height()+5);
		// 2017.2---����&ճ��
		tempPixmap = QPixmap(":/Resources/images/imgTool/copyItem.png");
		ui.pbtnCopyItem->setIcon(tempPixmap);
		ui.pbtnCopyItem->setFixedSize(tempPixmap.width()+5,tempPixmap.height()+5);
		tempPixmap = QPixmap(":/Resources/images/imgTool/pasteItem.png");
		ui.pbtnPasteItem->setIcon(tempPixmap);
		ui.pbtnPasteItem->setFixedSize(tempPixmap.width()+5,tempPixmap.height()+5);
		// ��������л���Ͽ�
		QFont tempFont;
		tempFont.setPointSize(15);
		for (int i=0;i<pChecker->checkerAry.iValidNum;++i)
		{
			ui.combCamIdx->setFont(tempFont);
			ui.combCamIdx->addItem(tr("Cam:")+QString::number(i+1));
		}
		ui.combCamIdx->setCurrentIndex(pChecker->m_nCamIndex);
		ui.combCamIdx->setFixedSize(100,tempPixmap.width()+5);
		// ���������л���Ͽ�
		ui.combLangIdx->setFont(tempFont);
		ui.combLangIdx->addItem(QIcon(":/flags/Resources/images/Flags/England.png"),"EN");	
		ui.combLangIdx->addItem(QIcon(":/flags/Resources/images/Flags/China.png"),"CN");
		ui.combLangIdx->setCurrentIndex(nLangIndex);
		ui.combLangIdx->setFixedSize(80,tempPixmap.width()+5);
		// �趨������̱�ʶ����
		ui.labelProcess->setFont(tempFont);

		//�����㷨���ڳ������� [7/23/2015 zhaodt]
		setMaximumWidth(nParentWndWidth);
		setMaximumHeight(nParentWndHeight);
		setMinimumWidth(nParentWndWidth);
		setMinimumHeight(nParentWndHeight);
		//�������ڴ�С
		//float fWndScaleH = 1.0*(nParentWndHeight-140-nTittleHeight)/nImgHeight;//30(������)+30����������+30��״̬����+50����ť��+10+10+10�������=170
		//float fWndScaleW = 1.0*(nParentWndWidth-656)/nImgWidth;//500(������)+100����������+56�������=625
		//fWndScale = max(min(fWndScaleW,fWndScaleH),0.1);
		int nWndH = nParentWndHeight-90-nTittleHeight;//30(������)+30��״̬����+10+10+10�������=90
		int nWndW = nParentWndWidth/2;
		ui.imgWidget->setFixedSize(nWndW,nWndH);
		setWndScale(false);
		float fWndScaleH = 1.0*ui.imgFrame->height()/nImgHeight;
		float fWndScaleW = 1.0*ui.imgFrame->width()/nImgWidth;
		fWndScale = max(min(fWndScaleW,fWndScaleH),0.1);
		//���ش�������
		labelWndScale->setVisible(false);
		comboWndScale->setVisible(false);
		//��ʼ���������
		ui.processBox->initItems(false); //2013.9.5 nanjc ����false,�����ظ�������ʾ����
		//���ü��������ʽ
		ui.processBox->setStyleSheet("MyGroupBoxProcess{border-radius: 10px;border:3px darkGray;border-style:inset;}");
		//��ʼ��״̬��
		initStatusBar();		
		//��ʼ����ťѡ��״̬;
		enableButtons(true);
		//���ÿؼ�״̬����ʾ��Ϣ
		changeLanguage(nLangIndex);
		//���ͼ��,���ڳ�ʼ��pChecker����
		displayObject();
		//ģ�尴ť�źŲ�
		connect(ui.btnSaveModel,SIGNAL(clicked()),this,SLOT(saveModel()));	
		connect(ui.btnTest,SIGNAL(clicked()),this,SLOT(checkTest()));
		connect(ui.btnExportModel,SIGNAL(clicked()),this,SLOT(exportModel()));
		connect(ui.btnImportModel,SIGNAL(clicked()),this,SLOT(importModel()));
		connect(ui.btnCopyModel,SIGNAL(clicked()),this,SLOT(copyModel()));
		//2013.9.12  nanjc ����ֹͣ�źŲ�
		connect(pCheckerReal,SIGNAL(signals_stopContinue()),this,SLOT(checkStopStatus()));
	}
	return true;
}
void CDlgMainWindow::initToolBar()
{
}
void CDlgMainWindow::initStatusBar()
{
	//��ʾ����汾��Ϣ
	labelVision = new QLabel;
	labelVisionName = new QLabel("Version:");
	labelVision->setMinimumSize(labelVision->sizeHint());
	labelVision->setAlignment(Qt::AlignHCenter);
	labelVision->setFrameShape(QFrame::StyledPanel);
	labelVision->setFrameShadow(QFrame::Sunken);
	labelVision->setText(pChecker->strVision);
	//labelVisionName->setText("Version:");
	//labelVisionName->setText(tr("Version:"));
	statusBar()->addPermanentWidget(labelVisionName);
	statusBar()->addPermanentWidget(labelVision);	
	//����״̬��������߿�Ϊ0	
	statusBar()->setStyleSheet(QString("QStatusBar::item{border: 0px}"));
	//�������½Ǵ�С���ڿ��Ƶ�
	statusBar()->setSizeGripEnabled(false);	
}
//���ܣ��������
void CDlgMainWindow::translateUi()
{
	ui.retranslateUi(this);	
	//�汾
	labelVisionName->setText(tr("Version:"));
	//������
	labelWndScale->setText(tr("WndSize"));
	//���ڷ���-�һ�groupbox�����˵�
	ui.processBox->createActions();

	//��������³�ʼ�������
	for (int i=0;i<ui.processBox->vItemLabels.size();++i)
		ui.processBox->vItemLabels[i]->setColStyle();

	//���ÿؼ���״̬����ʾ��Ϣ
	setCtrlTips();

	statusBar()->showMessage(tr("Ready"),2000);
}
//���ܣ����ÿؼ���״̬����ʾ��Ϣ
void CDlgMainWindow::setCtrlTips()
{
#ifdef DAHENGBLPKP_QT
	//���ض���״̬����ʾ
	ui.pbtnImgOpen->setStatusTip(ui.openImgAction->toolTip());
	ui.pbtnImgSave->setStatusTip(ui.saveImgAction->toolTip());
	ui.pbtnImgPre->setStatusTip(ui.prevImgAction->toolTip());
	ui.pbtnImgNext->setStatusTip(ui.nextImgAction->toolTip());
	ui.pbtnImgOriginal->setStatusTip(ui.oriImgAction->toolTip());
	ui.pbtnImgPainted->setStatusTip(ui.drawImgAction->toolTip());
	ui.pbtnRegReset->setStatusTip(ui.resetShapeAction->toolTip());
	ui.pbtnImgMeasure->setStatusTip(ui.measureImgAction->toolTip());
	ui.pbtnShowContinue->setStatusTip(ui.continueShowAction->toolTip());
	ui.pbtnShowStop->setStatusTip(ui.stopAtErrorShowAction->toolTip());

	ui.pbtnAddItem->setStatusTip(tr("Add a DetectionItem"));
	ui.pbtnDeleteItem->setStatusTip(tr("Delete a DetectionItem"));
	ui.pbtnInsertItem->setStatusTip(tr("Insert a DetectionItem"));
	ui.pbtnRenameItem->setStatusTip(tr("Change the name of DetectionItem"));
	ui.pbtnEnableItem->setStatusTip(tr("Disable or enable the Selected DetectionItem"));
	ui.pbtnCopyItem->setStatusTip(tr("Copy the DetectionItem"));
	ui.pbtnPasteItem->setStatusTip(tr("Paste the DetectionItem"));
#endif

	ui.btnSaveModel->setStatusTip(tr("Save the current model to the configuration file, and applied to an external detection(Ctrl+S)"));
	ui.btnExportModel->setStatusTip(tr("Exporting the current model to a '*. zip' file(Ctrl+E)"));
	ui.btnImportModel->setStatusTip(tr("Import a '*. zip' file to the current debug window(Ctrl+I)"));
	ui.btnCopyModel->setStatusTip(tr("Copy current model to the other cameras(Ctrl+C)"));	//������Ϣ
	ui.btnTest->setStatusTip(tr("Inspect current image with current setting"));
}
//���ܣ���̬�л�����
void CDlgMainWindow::changeLanguage(int index)
{
	//if (index == 0 && nLangIndex == 0)
	//{		
	//	return;
	//}
	QSettings algSet("daheng","GlasswareAlg");
	//static QTranslator *translator = NULL;

	if (index == 0)//Ӣ��
	{
		if (translator!=NULL)
		{
			qApp->removeTranslator(translator);
			delete translator;
			translator = NULL;
		}
		translateUi();
		//��������			
		nLangIndex = index;
		algSet.setValue("nLangIndex",nLangIndex);
	}
	if (index == 1)//����
	{
		translator = new QTranslator;
		if (translator->load("AlgLang_CH.qm"))
		{
			qApp->installTranslator(translator);
			translateUi();
			//��������
			nLangIndex = index;			
			algSet.setValue("nLangIndex",nLangIndex);
		}
		else			
		{
			QMessageBox::information(this,tr("Note"),tr("Failed to load Chinese language pack,please check that whether the file named 'AlgLang_CH.qm' is lost!"));	
			//��������
			nLangIndex = 0;
			algSet.setValue("nLangIndex",nLangIndex);
#ifdef DAHENGBLPKP_QT
			ui.combLangIdx->setCurrentIndex(0);
#else
			comboLanguage->setCurrentIndex(0);
#endif
		}
	}

	// ˢ�¼������������� [9/1/2015 zhaodt]
	int nItemClicked = ui.processBox->nOnMouseItem;
	if (nItemClicked >= 0)
	{
		ui.processBox->updateItemDlg(ui.processBox->vItemLabels[nItemClicked]);
	}
}

//*���ܣ����ڱ�������
void CDlgMainWindow::changeWndScale(int index,bool bRefresh/* = true*/)
{
	//2013.9.9 nanjc Ĭ��ֵ����Ӧ���ڴ�С�����������ļ��洢
	//�ȴ洢��ע���
	//QSettings algSet("daheng","GlasswareAlg");
	//algSet.setValue("nWndScale",index);
	nWndScale = index;
	fWndScale = (index+1)/10.f;
	setWndScale(bRefresh,fWndScale);
}
//*���ܣ��趨���ڱ���
void CDlgMainWindow::setWndScale(bool bRefresh /* = true */,float fScale /* = 1.0 */)
{
	//�������ڱ���
	int nFrameWidth,nFrameHeight;
#ifdef DAHENGBLPKP_QT
	int nWndW,nWndH;
	fScale = 1.0*nImgHeight/nImgWidth;
	nWndW = ui.imgWidget->width();
	nWndH = ui.imgWidget->height();
	if (nWndW*fScale > nWndH)
	{
		nFrameHeight = nWndH;
		nFrameWidth = nFrameHeight/fScale;
	}
	else
	{
		nFrameWidth = nWndW;
		nFrameHeight = nFrameWidth*fScale;
	}
#else
	nFrameWidth = nImgWidth*fScale>1500?1500:nImgWidth*fScale;
	nFrameHeight = nImgHeight*fScale<100?100:nImgHeight*fScale;//��������Ⱥ���С�߶�
#endif

	ui.imgFrame->setFixedSize(nFrameWidth,nFrameHeight);

	//��halcon����	
	if (m_lWindID==0)
	{
		Hlong lWindID = (Hlong)(ui.imgFrame->winId());
		set_window_attr("border_width", 0);
		set_check("~father");
		open_window(0,0,nFrameWidth, nFrameHeight, lWindID, "visible", "", &m_lWindID);
	}
	else
	{
		set_window_extents(m_lWindID,0,0,nFrameWidth,nFrameHeight);
	}

	//��ʾ����
	set_check("father");
	set_draw(m_lWindID, "margin");
	set_part(m_lWindID, 0, 0, nImgHeight-1, nImgWidth-1);
	set_font(m_lWindID,"-Meiryp UI-15-*-*-*-*-1-ANSI_CHARSET-");//-FontName-Height-Width-Italic-Underlined-Strikeout-Bold-CharSet-
	set_part_style(m_lWindID, 0);//0:�ٶ���� 1��ͼ�����������еȣ���ʱ�е� 2������������ʱ��
	if (bRefresh)
	{
		displayObject();
	}
}

//*���ܣ��������л�
void CDlgMainWindow::changeCamIndex(int index)
{		
	int i;
	Hlong lWid,lHei;
	CCheck *tempChecker;

	if (index == pChecker->m_nCamIndex)
	{
		return;
	}

	if (!tryClose())
	{
#ifdef DAHENGBLPKP_QT
		ui.combCamIdx->setCurrentIndex(pChecker->m_nCamIndex);
#else
		comboCamIndex->setCurrentIndex(pChecker->m_nCamIndex);
#endif
		return;
	}
	//�õ�Ŀ������ļ��ָ��
	for (i=0;i<pChecker->checkerAry.iValidNum;++i)
	{
		if (pChecker->checkerAry.pCheckerlist[i].nID == index)
		{
			tempChecker = (CCheck*)(pChecker->checkerAry.pCheckerlist[i].pChecker->m_pAlg);
			break;
		}
	}
	//�ж��Ƿ��Ѿ���ͼ
	Hlong tempArea;
	area_center(tempChecker->m_ImageSrc,&tempArea,NULL,NULL);
	if (tempArea == 0)
	{
		QMessageBox::information(this,tr("Note"),tr("Detection image isn't exist��please be sure whether to be detecting!"));
#ifdef DAHENGBLPKP_QT
		ui.combCamIdx->setCurrentIndex(pChecker->m_nCamIndex);
#else
		comboCamIndex->setCurrentIndex(pChecker->m_nCamIndex);
#endif
		return;
	}
	copy_obj(tempChecker->m_ImageSrc,&imgShow,1,-1);
	get_image_pointer1(imgShow,NULL,NULL,&lWid,&lHei);
	bottleOri = tempChecker->normalOri;
	copy_obj(tempChecker->m_normalbotXld,&bottleContour,1,-1);

	nImgWidth = lWid;
	nImgHeight = lHei;
	//�����л�
	disconnect(pCheckerReal,SIGNAL(signals_stopContinue()),this,SLOT(checkStopStatus()));
	pCheckerReal = tempChecker;//�ⲿָ��
	*pChecker = *pCheckerReal;//����ָ��
	pCheckerReal->m_pMainWnd = this;
	pChecker->m_pMainWnd = this;
	pChecker->m_bExtExcludeDefect = true;

	connect(pCheckerReal,SIGNAL(signals_stopContinue()),this,SLOT(checkStopStatus()));

	//2014.6.21 �л����ʱ���¼������
#ifdef DAHENGBLPKP_QT
	setWndScale(false);
	float fWndScaleH = 1.0*ui.imgFrame->height()/nImgHeight;//30(������)+30����������+30��״̬����+50����ť��+10+10+10�������=170
	float fWndScaleW = 1.0*ui.imgFrame->width()/nImgWidth;//500(������)+100����������+56�������=625
	fWndScale = max(min(fWndScaleW,fWndScaleH),0.1);
	//�ƶ�����
	int nFrameWidth = (nImgWidth*fWndScale+656)>1500?1500:(nImgWidth*fWndScale+656);
	//	move((nParentWndWidth - nFrameWidth)/2,0);
#else
	float deskwidth = nParentWndWidth-100;
	float deskheight = nParentWndHeight-180;
	nWndScale = min(deskwidth/nImgWidth,deskheight/nImgHeight)*10-1;
	nWndScale = max(0,min(9,nWndScale));
	comboWndScale->setCurrentIndex(nWndScale);
	changeWndScale(nWndScale,false); //2013.9.5 nanjc ����false,�����ظ�������ʾ����
	////�ƶ�����
	//move((nParentWndWidth - this->width())/2-100,
	//	(nParentWndHeight - this->height())/2-10);
#endif
	ui.processBox->initItems(false);	
	check(imgShow,bottleOri,bottleContour);
	displayObject();
}
void CDlgMainWindow::writeAlgLog1(char *acLoginfo)//QString *str
{
   // char tmpLog[256]=".\\lxnt_dlg.txt";

	/*QFile file(".\\lxnt_dlg.txt");
	if (!file.open(QFile::WriteOnly | QFile::Text))
	{
	QMessageBox::information(this, "Error Message", "Please Select a Text File!");
	return;
	}
	QTextStream out(&file);
	out << str +"\n"; */
	
	/*FILE *fp=fopen(tmpLog,"a+");
	fprintf(fp,acLoginfo);
	fprintf(fp,"\n");
	fclose(fp);*/
}
//*���ܣ���ʾͼ��
void CDlgMainWindow::displayObject(int iMethodIdx/* = -1*/)
{	
	try
	{
		QString strDis;
		disp_image(imgShow,m_lWindID);
		//2013.9.5 nanjc �رմ�����Ϣ�Ի���
		if (m_lRegInfoID !=0)
		{
			close_window(m_lRegInfoID);
			m_lRegInfoID = 0;
		}
		if (!bShowShape)
			return;
		//��ʾ��״
		int i;
		for (i=0;i<pChecker->vItemFlow.size();++i)
		{
			set_line_width(m_lWindID, 1);
			switch(pChecker->vItemFlow[i])
			{
			case ITEM_SIDEWALL_LOCATE:
				{
					s_oSideLoc &oSideLoc = pChecker->vModelShapes[i].value<s_oSideLoc>();
					s_pSideLoc &pSideLoc = pChecker->vModelParas[i].value<s_pSideLoc>();
					if (!pSideLoc.bEnabled)
					{
						break;
					}
					set_line_width(m_lWindID, 2);
					set_color(m_lWindID,"green");
					disp_circle(m_lWindID,oSideLoc.ori.Row,oSideLoc.ori.Col,8);
					disp_circle(m_lWindID,oSideLoc.ori.nRow11,oSideLoc.ori.nCol11,5);
					disp_circle(m_lWindID,oSideLoc.ori.nRow12,oSideLoc.ori.nCol12,5);
					disp_circle(m_lWindID,oSideLoc.ori.nRow21,oSideLoc.ori.nCol21,5);
					disp_circle(m_lWindID,oSideLoc.ori.nRow22,oSideLoc.ori.nCol22,5);
					set_color(m_lWindID,"yellow");	
					//nanjc 2013.9.6 ������ʾ����ͬ������ʾ��ͬ����
					int iMethod;
					if (iMethodIdx<0)
					{
						iMethod = pChecker->vModelParas[i].value<s_pSideLoc>().nMethodIdx;
					}
					else
					{
						iMethod = iMethodIdx;
					}
					if (iMethod == 0 || iMethod == 1 || iMethod == 2 || iMethod == 4 || iMethod == 5 || iMethod==6)
					{
						disp_obj(oSideLoc.oFirstLine,m_lWindID);
					}
					if (iMethod == 0 || iMethod == 1 || iMethod == 2 || iMethod == 5 || iMethod==6)
					{
						disp_obj(oSideLoc.oSecondLine,m_lWindID);
					}				
					if (iMethod == 0 || iMethod == 2 || iMethod == 4 || iMethod==6)
					{
						disp_obj(oSideLoc.oThirdLine,m_lWindID);
					}	
					//2013.9.22 nanjc ����ͼ��λӦ��ͼ��
					if (iMethod == 3)
					{				
						disp_obj(pChecker->m_pressbotXld,m_lWindID);
					}
				}
				break;
			case ITEM_FINISH_LOCATE:
				{
					s_oFinLoc &oFinLoc = pChecker->vModelShapes[i].value<s_oFinLoc>();
					s_pFinLoc &pFinLoc = pChecker->vModelParas[i].value<s_pFinLoc>();
					if (!pFinLoc.bEnabled)
					{
						break;
					}
					set_line_width(m_lWindID, 2);
					set_color(m_lWindID,"green");
					disp_circle(m_lWindID,oFinLoc.Row,oFinLoc.Col,oFinLoc.Radius);  //��λresult display
					set_color(m_lWindID,"yellow");
					//nanjc 2013.9.6 ������ʾ����ͬ������ʾ��ͬ����
					int iMethod;
					if (iMethodIdx<0)
					{
						break;//��&�׼��ʱ����ʾ����ֹ�������			
						iMethod = pChecker->vModelParas[i].value<s_pFinLoc>().nMethodIdx;
					}
					else
					{
						iMethod = iMethodIdx;
					}
					disp_obj(oFinLoc.oInCircle,m_lWindID);
					if (iMethod!=1)
					{
						disp_obj(oFinLoc.oOutCircle,m_lWindID);
					}
				}
				break;
			case ITEM_BASE_LOCATE:
				{
					s_oBaseLoc &oBaseLoc = pChecker->vModelShapes[i].value<s_oBaseLoc>();
					s_pBaseLoc &pBaseLoc = pChecker->vModelParas[i].value<s_pBaseLoc>();
					set_line_width(m_lWindID, 2);
					set_color(m_lWindID,"green");
					//must adding no loc not display circle
					if(pChecker->vModelParas[i].value<s_pBaseLoc>().nMethodIdx < 9)
					 {
						disp_circle(m_lWindID,oBaseLoc.Row,oBaseLoc.Col,oBaseLoc.Radius);
					 }
					 else if(pBaseLoc.bRectShape && pChecker->vModelParas[i].value<s_pBaseLoc>().nMethodIdx == 9)
                     {
						disp_obj(oBaseLoc.FoundModel,m_lWindID);
					 }
					set_color(m_lWindID,"yellow");			
					//nanjc 2013.9.6 ������ʾ����ͬ������ʾ��ͬ���� 
					int iMethod;
					if (iMethodIdx<0)
					{
						break;//��&�׼��ʱ����ʾ����ֹ�������
						iMethod = pChecker->vModelParas[i].value<s_pBaseLoc>().nMethodIdx;
					}
					else
					{
						iMethod = iMethodIdx;
					}
					if (iMethod == 0 || iMethod == 2 || iMethod == 3)
					{
						disp_obj(oBaseLoc.oCentReg,m_lWindID);
					}
					if ((iMethod == 2) || ((iMethod == 9) && (!pBaseLoc.bRectShape)))//20180802 add liuxu   
					{
						disp_obj(oBaseLoc.oBeltDia,m_lWindID);
					}
					if(iMethod == 9 && pBaseLoc.bRectShape)
					{
					    disp_obj(oBaseLoc.oBeltDia_Rect,m_lWindID);//&& pBaseLoc.bRectShape
					}
					if (iMethod == 5 )//20180802 add liuxu
					{
						disp_obj(oBaseLoc.oModeNOEdge,m_lWindID);
					}
					
				}
				break;
			case ITEM_HORI_SIZE:
				{
					s_oHoriSize &oHoriSize = pChecker->vModelShapes[i].value<s_oHoriSize>();
					s_pHoriSize &pHoriSize = pChecker->vModelParas[i].value<s_pHoriSize>();
					if (!pHoriSize.bEnabled)
					{
						break;
					}
					Hlong rowCent,colCent;
					rowCent = (oHoriSize.ptLeft.y()+oHoriSize.ptRight.y())/2;
					colCent = (oHoriSize.ptLeft.x()+oHoriSize.ptRight.x())/2;
					set_color(m_lWindID,"green");
					disp_obj(oHoriSize.oSizeRect,m_lWindID);
					set_color(m_lWindID,"yellow");
					disp_arrow(m_lWindID,rowCent,colCent,oHoriSize.ptLeft.y(),oHoriSize.ptLeft.x(),3);
					disp_arrow(m_lWindID,rowCent,colCent,oHoriSize.ptRight.y(),oHoriSize.ptRight.x(),3);				
					//��ʾ�ߴ�����
					double row1,col1;
					smallest_rectangle1_xld(oHoriSize.oSizeRect,&row1,&col1,NULL,NULL);
					set_color(m_lWindID,"navy");
					QString strCurDist = QString("%1 mm").arg(QString::number(pChecker->vModelParas[i].value<s_pHoriSize>().fCurValue,'f',2));
					set_tposition(m_lWindID,row1,col1);
					write_string(m_lWindID,strCurDist.toLocal8Bit().constData());
				}
				break;
			case ITEM_VERT_SIZE:
				{
					s_oVertSize &oVertSize = pChecker->vModelShapes[i].value<s_oVertSize>();
					s_pVertSize &pVertSize = pChecker->vModelParas[i].value<s_pVertSize>();
					if (!pVertSize.bEnabled)
					{
						break;
					}
					Hlong rowCent,colCent;
					rowCent = (oVertSize.ptLeft.y()+oVertSize.ptRight.y())/2;
					colCent = (oVertSize.ptLeft.x()+oVertSize.ptRight.x())/2; 
					set_color(m_lWindID,"green");
					disp_obj(oVertSize.oSizeRect,m_lWindID);
					set_color(m_lWindID,"yellow");
					disp_arrow(m_lWindID,rowCent,colCent,oVertSize.ptLeft.y(),oVertSize.ptLeft.x(),2);
					disp_arrow(m_lWindID,rowCent,colCent,oVertSize.ptRight.y(),oVertSize.ptRight.x(),2);
					//��ʾ�ߴ�����
					double row1,col1;
					smallest_rectangle1_xld(oVertSize.oSizeRect,&row1,&col1,NULL,NULL);
					set_color(m_lWindID,"navy");
					QString strCurDist = QString("%1 mm").arg(QString::number(pChecker->vModelParas[i].value<s_pVertSize>().fCurValue,'f',2));
					set_tposition(m_lWindID,row1,col1);
					write_string(m_lWindID,strCurDist.toLocal8Bit().constData());
				}
				break;
			case ITEM_FULL_HEIGHT:
				{
					s_oFullHeight &oFullHeight = pChecker->vModelShapes[i].value<s_oFullHeight>();
					s_pFullHeight &pFullHeight = pChecker->vModelParas[i].value<s_pFullHeight>();
					if (!pFullHeight.bEnabled)
					{
						break;
					}
					Hlong rowCent,colCent;
					rowCent = (oFullHeight.ptLeft.y()+oFullHeight.ptRight.y())/2;
					colCent = (oFullHeight.ptLeft.x()+oFullHeight.ptRight.x())/2; 
					set_color(m_lWindID,"green");
					disp_obj(oFullHeight.oSizeRect,m_lWindID);
					set_color(m_lWindID,"yellow");
					disp_arrow(m_lWindID,rowCent,colCent,oFullHeight.ptLeft.y(),oFullHeight.ptLeft.x(),2);
					disp_arrow(m_lWindID,rowCent,colCent,oFullHeight.ptRight.y(),oFullHeight.ptRight.x(),2);
					//��ʾ�ߴ�����
					double row1,col1;
					smallest_rectangle1_xld(oFullHeight.oSizeRect,&row1,&col1,NULL,NULL);
					set_color(m_lWindID,"navy");
					QString strCurDist = QString("%1 mm").arg(QString::number(pChecker->vModelParas[i].value<s_pFullHeight>().fCurValue,'f',2));
					set_tposition(m_lWindID,row1,col1);
					write_string(m_lWindID,strCurDist.toLocal8Bit().constData());
				}
				break;
			case ITEM_BENT_NECK:
				{
					s_oBentNeck &oBentNeck = pChecker->vModelShapes[i].value<s_oBentNeck>();
					s_pBentNeck &pBentNeck = pChecker->vModelParas[i].value<s_pBentNeck>();
					if (!pBentNeck.bEnabled)
					{
						break;
					}
					//��ʾ�ߴ�����			
					set_color(m_lWindID,"navy");
					QString strCurDist = tr("BentValue:%1 px").arg(QString::number(pChecker->vModelParas[i].value<s_pBentNeck>().nCurValue));
					set_tposition(m_lWindID,110,20);
					write_string(m_lWindID,strCurDist.toLocal8Bit().constData());
				}
				break;
			case ITEM_VERT_ANG:
				{
					s_pVertAng &pVertAng = pChecker->vModelParas[i].value<s_pVertAng>();
					if (!pVertAng.bEnabled)
					{
						break;
					}
					//��ʾ�ߴ�����			
					set_color(m_lWindID,"navy");
					QString strCurAng = tr("VerticalAngle:%1 ��").arg(QString::number(pChecker->vModelParas[i].value<s_pVertAng>().fCurValue,'f',2));
					set_tposition(m_lWindID,140,20);
					write_string(m_lWindID,strCurAng.toLocal8Bit().constData());
				}
				break;
			case ITEM_SGENNERAL_REGION:
				{										
					s_oSGenReg oSGenReg = pChecker->vModelShapes[i].value<s_oSGenReg>();
					s_pSGenReg pSGenReg = pChecker->vModelParas[i].value<s_pSGenReg>();
					if (!pSGenReg.bEnabled)
					{
						break;
					}
					set_color(m_lWindID,"green");
					if (pSGenReg.nShapeType == 0)
					{
						disp_obj(oSGenReg.oCheckRegion,m_lWindID);
					}
					else
					{
						disp_obj(oSGenReg.oCheckRegion_Rect,m_lWindID);
					}
					
					set_color(m_lWindID,"blue");
					disp_obj(oSGenReg.oValidRegion,m_lWindID);
				}
				break;
			case ITEM_DISTURB_REGION:
				{										
					s_oDistReg oDistReg = pChecker->vModelShapes[i].value<s_oDistReg>();
					s_pDistReg pDistReg = pChecker->vModelParas[i].value<s_pDistReg>();
					if (!pDistReg.bEnabled)
					{
						break;
					}
					set_color(m_lWindID,"gold");
					if (pDistReg.nShapeType == 0)
					{
						disp_obj(oDistReg.oDisturbReg,m_lWindID);
					}
					else
					{
						disp_obj(oDistReg.oDisturbReg_Rect,m_lWindID);
					}
				}
				break;
			case ITEM_SSIDEFINISH_REGION:
				{										
					s_oSSideFReg oSSideFReg = pChecker->vModelShapes[i].value<s_oSSideFReg>();
					s_pSSideFReg pSSideFReg = pChecker->vModelParas[i].value<s_pSSideFReg>();
					if (!pSSideFReg.bEnabled)
					{
						break;
					}
					set_color(m_lWindID,"green");
					if (pSSideFReg.nShapeType == 0)
					{
						disp_obj(oSSideFReg.oCheckRegion,m_lWindID);
					}
					else
					{
						disp_obj(oSSideFReg.oCheckRegion_Rect,m_lWindID);
					}
					set_color(m_lWindID,"blue");
					disp_obj(oSSideFReg.oValidRegion,m_lWindID);
				}
				break;
			case ITEM_SINFINISH_REGION:
				{										
					s_oSInFReg oSInFReg = pChecker->vModelShapes[i].value<s_oSInFReg>();
					s_pSInFReg pSInFReg = pChecker->vModelParas[i].value<s_pSInFReg>();
					if (!pSInFReg.bEnabled)
					{
						break;
					}
					set_color(m_lWindID,"green");
					disp_obj(oSInFReg.oCheckRegion,m_lWindID);				
				}
				break;
			case ITEM_SSCREWFINISH_REGION:
				{										
					s_oSScrewFReg oSScrewFReg = pChecker->vModelShapes[i].value<s_oSScrewFReg>();
					s_pSScrewFReg pSScrewFReg = pChecker->vModelParas[i].value<s_pSScrewFReg>();
					if (!pSScrewFReg.bEnabled)
					{
						break;
					}
					set_color(m_lWindID,"green");
					if (pSScrewFReg.nShapeType == 0)
					{
						disp_obj(oSScrewFReg.oCheckRegion,m_lWindID);
					}
					else
					{
						disp_obj(oSScrewFReg.oCheckRegion_Rect,m_lWindID);
					}
				}
				break;
			case ITEM_FRLINNER_REGION:
				{										
					s_oFRLInReg oFRLInReg = pChecker->vModelShapes[i].value<s_oFRLInReg>();
					s_pFRLInReg pFRLInReg = pChecker->vModelParas[i].value<s_pFRLInReg>();
					if (!pFRLInReg.bEnabled)
					{
						break;
					}
					set_color(m_lWindID,"plum");
					disp_obj(oFRLInReg.oInCircle,m_lWindID);		
					disp_obj(oFRLInReg.oOutCircle,m_lWindID);
				}
				break;
			case ITEM_FRLMIDDLE_REGION:
				{										
					s_oFRLMidReg oFRLMidReg = pChecker->vModelShapes[i].value<s_oFRLMidReg>();
					s_pFRLMidReg pFRLMidReg = pChecker->vModelParas[i].value<s_pFRLMidReg>();
					if (!pFRLMidReg.bEnabled)
					{
						break;
					}
					set_color(m_lWindID,"magenta");
					disp_obj(oFRLMidReg.oInCircle,m_lWindID);		
					disp_obj(oFRLMidReg.oOutCircle,m_lWindID);
				}
				break;
			case ITEM_FRLOUTER_REGION:
				{										
					s_oFRLOutReg oFRLOutReg = pChecker->vModelShapes[i].value<s_oFRLOutReg>();
					s_pFRLOutReg pFRLOutReg = pChecker->vModelParas[i].value<s_pFRLOutReg>();
					if (!pFRLOutReg.bEnabled)
					{
						break;
					}
					set_color(m_lWindID,"dark orchid");
					disp_obj(oFRLOutReg.oInCircle,m_lWindID);		
					disp_obj(oFRLOutReg.oOutCircle,m_lWindID);
				}
				break;
			case ITEM_FBLINNER_REGION:
				{										
					s_oFBLInReg oFBLInReg = pChecker->vModelShapes[i].value<s_oFBLInReg>();
					s_pFBLInReg pFBLInReg = pChecker->vModelParas[i].value<s_pFBLInReg>();
					if (!pFBLInReg.bEnabled)
					{
						break;
					}
					set_color(m_lWindID,"plum");
					disp_obj(oFBLInReg.oPolygon,m_lWindID);	
					//disp_obj(oFBLInReg.oInCircle,m_lWindID);		
					//disp_obj(oFBLInReg.oOutCircle,m_lWindID);
				}
				break;
			case ITEM_FBLMIDDLE_REGION:
				{										
					s_oFBLMidReg oFBLMidReg = pChecker->vModelShapes[i].value<s_oFBLMidReg>();
					s_pFBLMidReg pFBLMidReg = pChecker->vModelParas[i].value<s_pFBLMidReg>();
					if (!pFBLMidReg.bEnabled)
					{
						break;
					}
					set_color(m_lWindID,"magenta");
					disp_obj(oFBLMidReg.oInCircle,m_lWindID);		
					disp_obj(oFBLMidReg.oOutCircle,m_lWindID);
				}
				break;
			case ITEM_BINNER_REGION:
				{										
					s_oBInReg oBInReg = pChecker->vModelShapes[i].value<s_oBInReg>();
					s_pBInReg pBInReg = pChecker->vModelParas[i].value<s_pBInReg>();
					if (!pBInReg.bEnabled)
					{
						break;
					}
					set_color(m_lWindID,"plum");
					//disp_obj(oBInReg.oOutCircle,m_lWindID);		
					if (1 == pChecker->vModelParas[i].value<s_pBInReg>().nMethodIdx)
					{
						disp_obj(oBInReg.oInCircle,m_lWindID);		
					}
					if (0 == pChecker->vModelParas[i].value<s_pBInReg>().nMethodIdx || 1 == pChecker->vModelParas[i].value<s_pBInReg>().nMethodIdx)
					{
						disp_obj(oBInReg.oOutCircle,m_lWindID);		
					}
					if (3 == pChecker->vModelParas[i].value<s_pBInReg>().nMethodIdx)
					{
						disp_obj(oBInReg.oTriBase,m_lWindID);		
					}
					if (2 == pChecker->vModelParas[i].value<s_pBInReg>().nMethodIdx)
					{
						disp_obj(oBInReg.oRectBase,m_lWindID);		
					}

					if (pBInReg.bChar)
					{
						disp_obj(oBInReg.oCurCharReg,m_lWindID);
						disp_obj(oBInReg.oCurMarkReg,m_lWindID);
					}
				}
				break;
			case ITEM_BMIDDLE_REGION:
				{										
					s_oBMidReg oBMidReg = pChecker->vModelShapes[i].value<s_oBMidReg>();
					s_pBMidReg pBMidReg = pChecker->vModelParas[i].value<s_pBMidReg>();
					if (!pBMidReg.bEnabled)
					{
						break;
					}
					set_color(m_lWindID,"magenta");
					disp_obj(oBMidReg.oOutCircle,m_lWindID);		
					disp_obj(oBMidReg.oInCircle,m_lWindID);		
				}
				break;
			case ITEM_BOUTER_REGION:
				{										
					s_oBOutReg oBOutReg = pChecker->vModelShapes[i].value<s_oBOutReg>();
					s_pBOutReg pBOutReg = pChecker->vModelParas[i].value<s_pBOutReg>();
					if (!pBOutReg.bEnabled)
					{
						break;
					}
					set_color(m_lWindID,"dark orchid");
					disp_obj(oBOutReg.oInCircle,m_lWindID);		
					disp_obj(oBOutReg.oOutCircle,m_lWindID);		
				}
				break;
			case ITEM_SSIDEWALL_REGION:
				{										
					s_oSSideReg oSSideReg = pChecker->vModelShapes[i].value<s_oSSideReg>();
					s_pSSideReg pSSideReg = pChecker->vModelParas[i].value<s_pSSideReg>();
					if (!pSSideReg.bEnabled)
					{
						break;
					}
					set_color(m_lWindID,"green");
					if (pSSideReg.nShapeType == 0)
					{
						disp_obj(oSSideReg.oCheckRegion,m_lWindID);
					}
					else
					{
						disp_obj(oSSideReg.oCheckRegion_Rect,m_lWindID);
					}

				}
				break;
			case ITEM_FINISH_CONTOUR:
				{										
					s_oFinCont oFinCont = pChecker->vModelShapes[i].value<s_oFinCont>();
					s_pFinCont pFinCont = pChecker->vModelParas[i].value<s_pFinCont>();
					if (!pFinCont.bEnabled)
					{
						break;
					}
					set_color(m_lWindID,"cyan");
					disp_obj(oFinCont.oCheckRegion,m_lWindID);			
					set_color(m_lWindID,"magenta");
					disp_obj(oFinCont.oFinishCont,m_lWindID);	
				}
				break;
			case ITEM_NECK_CONTOUR:
				{
					s_oNeckCont &oNeckCont = pChecker->vModelShapes[i].value<s_oNeckCont>();
					s_pNeckCont &pNeckCont = pChecker->vModelParas[i].value<s_pNeckCont>();
					if (!pNeckCont.bEnabled)
					{
						break;
					}
					set_color(m_lWindID,"cyan");
					disp_obj(oNeckCont.oCheckRegion,m_lWindID);
					set_color(m_lWindID,"magenta");
					disp_obj(oNeckCont.oNeckCont,m_lWindID);
					disp_obj(oNeckCont.oNeckLine,m_lWindID);
					//��ʾ��������
					double row1,col1;
					smallest_rectangle1_xld(oNeckCont.oCheckRegion,&row1,&col1,NULL,NULL);
					set_color(m_lWindID,"navy");
					QString strCurHei = tr("NeckHeight:%1 px").arg(oNeckCont.nNeckHei);
					set_tposition(m_lWindID,row1,col1);
					write_string(m_lWindID,strCurHei.toLocal8Bit().constData());
					//���
					gen_empty_obj(&oNeckCont.oNeckCont);
					gen_empty_obj(&oNeckCont.oNeckLine);
					oNeckCont.nNeckHei = 0;
					pChecker->vModelShapes[i].setValue(oNeckCont);
				}
				break;
			case ITEM_BODY_CONTOUR:
				{
					s_oBodyCont &oBodyCont = pChecker->vModelShapes[i].value<s_oBodyCont>();
					s_pBodyCont &pBodyCont = pChecker->vModelParas[i].value<s_pBodyCont>();
					if (!pBodyCont.bEnabled)
					{
						break;
					}
					set_color(m_lWindID,"cyan");
					disp_obj(oBodyCont.oCheckRegion,m_lWindID);
					set_color(m_lWindID,"magenta");
					disp_obj(oBodyCont.oBodyCont,m_lWindID);				
					//��ʾƿ��������
					double row1,col1;
					smallest_rectangle1_xld(oBodyCont.oCheckRegion,&row1,&col1,NULL,NULL);
					set_color(m_lWindID,"navy");
					QString strCurHei = tr("Width:%1 px").arg(oBodyCont.nBodyWidth);
					set_tposition(m_lWindID,row1,col1);
					write_string(m_lWindID,strCurHei.toLocal8Bit().constData());
					//���
					gen_empty_obj(&oBodyCont.oBodyCont);
					oBodyCont.nBodyWidth = 0;
					pChecker->vModelShapes[i].setValue(oBodyCont);
				}
				break;
			case ITEM_SBRISPOT_REGION:
				{
					s_oSBriSpotReg &oSBriSpotReg = pChecker->vModelShapes[i].value<s_oSBriSpotReg>();
					s_pSBriSpotReg &pSBriSpotReg = pChecker->vModelParas[i].value<s_pSBriSpotReg>();
					if (!pSBriSpotReg.bEnabled)
					{
						break;
					}
					set_color(m_lWindID,"green");
					if (pSBriSpotReg.nShapeType == 0)
					{
						disp_obj(oSBriSpotReg.oCheckRegion,m_lWindID);
					}
					else
					{
						disp_obj(oSBriSpotReg.oCheckRegion_Rect,m_lWindID);
					}
				}
				break;
			case ITEM_BALL_REGION:
				{										
					s_oBAllReg oBAllReg = pChecker->vModelShapes[i].value<s_oBAllReg>();
					s_pBAllReg pBAllReg = pChecker->vModelParas[i].value<s_pBAllReg>();
					if (!pBAllReg.bEnabled)
					{
						break;
					}
					set_color(m_lWindID,"cyan");
					//disp_obj(oBAllReg.oInCircle,m_lWindID); //2017.7���ݰ�ƿ�ײ���ģ��ʶ�������ע��		
					disp_obj(oBAllReg.oOutCircle,m_lWindID);	
					set_color(m_lWindID,"blue");
					//disp_obj(oBAllReg.oRegModeNum,m_lWindID);
					disp_obj(oBAllReg.oRegMould,m_lWindID);
					set_color(m_lWindID,"white");
					QString strMouldNo = tr("MouldNumber:%1").arg(oBAllReg.nMouldNO);
					set_tposition(m_lWindID,90,20);
					write_string(m_lWindID,strMouldNo.toLocal8Bit().constData());
					//��ʾģ��������Ϣ
					if (!(oBAllReg.strMouldInfo.isEmpty()))
					{
						HTuple oldFont;
						get_font(m_lWindID,&oldFont);
						set_font(m_lWindID,"-����-10-*-*-*-*-*-ANSI_CHARSET-");
						set_color(m_lWindID,"firebrick");
						QString strMouldInfo = tr("MouldOrder:")+oBAllReg.strMouldInfo;
						set_tposition(m_lWindID,120,20);
						write_string(m_lWindID,strMouldInfo.toLocal8Bit().constData());
						set_font(m_lWindID,oldFont);
					}
				}
				break;
			case ITEM_CIRCLE_SIZE:
				{										
					s_pCirSize pCirSize = pChecker->vModelParas[i].value<s_pCirSize>();		
					s_oCirSize oCirSize = pChecker->vModelShapes[i].value<s_oCirSize>();
					if (!pCirSize.bEnabled)
					{
						break;
					}
					set_color(m_lWindID,"spring green");
					disp_obj(oCirSize.oCircle,m_lWindID);		
					double fRow,fCol,fRadiu;
					smallest_circle(oCirSize.oCircle,&fRow,&fCol,&fRadiu);
					if (pCirSize.bDia || pCirSize.bOvality)
					{
						QString strCurSize = "";
						Hlong lfontwidth = 0;
						//��ʾ�ߴ�����
						set_color(m_lWindID,"navy");
						if (pCirSize.bDia)
						{
							strCurSize = tr("Diameter:%1 ").arg(QString::number(pCirSize.fDiaCurValue,'f',2));
						}
						if (pCirSize.bOvality)
						{
							strCurSize += tr("Ovality:%1").arg(QString::number(pCirSize.fOvalCurValue,'f',2));
						}
						get_string_extents(m_lWindID,strCurSize.toLocal8Bit().constData(),NULL,NULL,&lfontwidth,NULL);
						set_tposition(m_lWindID,fRow-fRadiu,fCol-lfontwidth/2);
						write_string(m_lWindID,strCurSize.toLocal8Bit().constData());
					}
				}
				break;
			case ITEM_SBASE_REGION:
				{										
					s_oSBaseReg oSBaseReg = pChecker->vModelShapes[i].value<s_oSBaseReg>();
					s_pSBaseReg pSBaseReg = pChecker->vModelParas[i].value<s_pSBaseReg>();
					if (!pSBaseReg.bEnabled)
					{
						break;
					}
					//��ֹ�붨λ��Ϣ��iMethodIdx������ȫ��ʾ����Ȧ
					set_color(m_lWindID,"green");
					disp_obj(oSBaseReg.oOutCircle,m_lWindID);					
					if (1 == pChecker->vModelParas[i].value<s_pSBaseReg>().nMethodIdx)
					{
						disp_obj(oSBaseReg.oInCircle,m_lWindID);					
					}
					//int iMethod;
					//if (iMethodIdx<0)
					//{
					//	iMethod = pChecker->vModelParas[i].value<s_pSBaseReg>().nMethodIdx;
					//}
					//else
					//{
					//	iMethod = iMethodIdx;
					//}
					//if (iMethod == 1)
					//{
					//	disp_obj(oSBaseReg.oInCircle,m_lWindID);					
					//}
				}
				break;
			case ITEM_SBASECONVEX_REGION:
				{										
					s_oSBaseConvexReg oSBaseConvexReg = pChecker->vModelShapes[i].value<s_oSBaseConvexReg>();
					s_pSBaseConvexReg pSBaseConvexReg = pChecker->vModelParas[i].value<s_pSBaseConvexReg>();
					if (!pSBaseConvexReg.bEnabled)
					{
						break;
					}
					set_color(m_lWindID,"green");
					disp_obj(oSBaseConvexReg.oCheckRegion,m_lWindID);
					set_color(m_lWindID,"blue");
					disp_obj(oSBaseConvexReg.oValidRegion,m_lWindID);
					set_color(m_lWindID,"magenta");
					disp_obj(oSBaseConvexReg.oBaseConvexRegion,m_lWindID);
				}
				break;
			default:
				break;
			}
		}
		//��ʾȱ��
		set_line_width(m_lWindID, 2);
		set_color(m_lWindID,"red");
		disp_obj(pChecker->rtnInfo.regError,m_lWindID);
		set_color(m_lWindID,"orange");
		set_line_width(m_lWindID, 1);
		if (pChecker->m_bExtExcludeDefect)
		{
			for (i = 0;i<pChecker->m_vExcludeInfo.count();++i)
			{	
				disp_obj(pChecker->m_vExcludeInfo.at(i).regExclude,m_lWindID);
			}
		}
		//��ʾ��������
		int nErrorType = pChecker->rtnInfo.nType;
		switch(nErrorType)
		{
		case GOOD_BOTTLE:
			strDis=tr("OK");
			break;
		case ERROR_LOCATEFAIL:
			strDis=tr("ERROR_LOCATE");
			break;
		case ERROR_INVALID_ROI:
			strDis=tr("ERROR_INVALID_ROI");
			break;
		case ERROR_HORISIZE:
			strDis=tr("ERROR_HORI_SIZE");
			break;
		case ERROR_VERTSIZE:
			strDis=tr("ERROR_VERT_SIZE");
			break;
		case ERROR_BENTNECK:
			strDis=tr("ERROR_BENTNECK_SIZE");
			break;
		case ERROR_VERTANG:
			strDis=tr("ERROR_VERTANG_SIZE");
			break;
		case ERROR_SPOT:
			strDis=tr("ERROR_SPOT");
			break;
		case ERROR_CRACK://tr("ERROR_CRACK");QString::fromLocal8Bit(
			strDis=pChecker->rtnInfo.strErrorNm ;
			break;
		case ERROR_BUBBLE:
			strDis=tr("ERROR_BUBBLE");
			break;
		case ERROR_STONE:
			strDis=tr("ERROR_STONE");
			break;
		case ERROR_DARKDOT:
			strDis=tr("ERROR_DARKDOT");
			break;
		case ERROR_SSIDEFIN:
			strDis=tr("ERROR_MOUTHROI_BODY");
			break;
		case ERROR_OVERPRESS:
			strDis=tr("ERROR_DOUBLE_MOUTH");
			break;
		case ERROR_SSCREWF:
			strDis=tr("ERROR_SCREWCRACK_BODY");
			break;
		case ERROR_FINISHIN:
			strDis=tr("ERROR_IN_MOUTH");
			break;
		case ERROR_FINISHMID:
			strDis=tr("ERROR_MID_MOUTH");
			break;
		case ERROR_PITTING:
			strDis=tr("ERROR_PITTING");
			break;
		case ERROR_LOF:
			strDis=tr("ERROR_SCISSORS_MID_MOUTH");
			break;
		case ERROR_FINISHOUT:
			strDis=tr("ERROR_OUT_MOUTH");
			break;
		case ERROR_BREACH:
			strDis=tr("ERROR_BREACH_OUT_MOUTH");
			break;
		case ERROR_BOTTOM_DL:
			strDis=tr("ERROR_LD_BOTTOM");
			break;
		case ERROR_INNER_STRESS:
			strDis=tr("ERROR_INNER_STRESS");
			break;
		case ERROR_STONE_STRESS:
			strDis=tr("ERROR_STONE_STRESS");
			break;
		case ERROR_FIN_CONT:
			strDis=tr("ERROR_MOUTH_CONTOUR");
			break;
		case ERROR_NECK_CONT:
			strDis=tr("ERROR_NECK_CONTOUR");
			break;
		case ERROR_BODY_CONT:
			strDis=tr("ERROR_BODY_CONTOUR");
			break;
		case ERROR_MOUTHDEFORM:
			strDis=tr("ERROR_DEFORM_MOUTH");
			break;
		case ERROR_BROKENRING:
			strDis=tr("ERROR_BROKENRING_OUT_MOUTH");
			break;	
		case ERROR_BOTTOM_STRIPE:
			strDis=tr("ERROR_BOTTOM_STRIPE");
			break;
		case ERROR_BRI_SPOT:
			strDis=tr("ERROR_BRIGHT_SPOTS");
			break;
		case ERROR_CIRCLE_DIA:
			strDis=tr("ERROR_CIRCLE_DIA");
			break;
		case ERROR_CIRCLE_OVALITY:
			strDis=tr("ERROR_CIRCLE_OVALITY");
			break;
		case ERROR_BASECONVEX_CONT:
			strDis=tr("ERROR_BASECONVEX_CONT");
			break;
		case ERROR_TINYCRACK:
			strDis=tr("ERROR_TINYCRACK");
			break;
		case ERROR_LOF_BL:
			strDis=tr("ERROR_SCISSORS_MID_MOUTH");
			break;
		case ERROR_THIN_BUBBLE:
			strDis=tr("ERROR_THIN_BUBBLE");
			break;
		case ERROR_MOULD_POINT:
			strDis=tr("ERROR_MOULD_POINT");
			break;
		case ERROR_MOULD_REJECT:
			strDis=tr("ERROR_MOULD_REJECT");
			break;
		default:
			break;		
		}
		if (pChecker->rtnInfo.nType>0)
		{
			HTuple tpArea;
			double maxArea;
			area_center(pChecker->rtnInfo.regError,&tpArea,NULL,NULL);
			tuple_max(tpArea,&maxArea);
			strDis+=QString("  %1").arg(QString::number(maxArea,'f',0));
		}
		Hlong textRow=20,textCol=20;
		set_tposition(m_lWindID,textRow,textCol);
		if (nErrorType>0)
		{
			set_color(m_lWindID,"red");
		}
		else
			set_color(m_lWindID,"green");
		//printf("strDis:%s--,%s--,%s",strDis,strDis.toLocal8Bit(),strDis.toLocal8Bit().constData());
		write_string(m_lWindID,HTuple(strDis.toLocal8Bit().constData()));//strDis.toLocal8Bit().constData()
		//��ʾ��������
		if (!(pChecker->rtnInfo.strEx.isEmpty()))
		{
			HTuple oldFont;
			get_font(m_lWindID,&oldFont);
			set_font(m_lWindID,"-����-10-*-*-*-*-*-ANSI_CHARSET-");
			set_color(m_lWindID,"firebrick");
			textRow+=35;
			set_tposition(m_lWindID,textRow,textCol);
			write_string(m_lWindID,HTuple(pChecker->rtnInfo.strEx.toLocal8Bit().constData()));
			set_font(m_lWindID,oldFont);
		}
		//��ʾ����ʱ��
		strDis = QString("time = %1ms").arg(QString::number(pChecker->m_dTimeProcess,'f',1));
		set_color(m_lWindID,"blue");
		textRow+=25;
		set_tposition(m_lWindID,textRow,textCol);
		write_string(m_lWindID,HTuple(strDis.toLocal8Bit().constData()));
	}
	catch(HException &e)
	{
		//Halcon�쳣		
		QString tempStr,strErr;
		tempStr=e.message;
		tempStr.remove(0,20);
		strErr = QString("abnormal:displayObject,Image display")+ tempStr;//ͼ����ʾ
		pChecker->writeErrDataRecord(strErr);
	}
	catch (...)
	{
		pChecker->writeErrDataRecord(QString("abnormal:displayObject,Image display"));//ͼ����ʾ		
	}
}

//*���ܣ�������ʾѡ�м�����Ӧ�������
void CDlgMainWindow::displayRoiHighLight(int nId,QVariant &vModelPara,QVariant &vModelShape)
{	
	try
	{
		set_line_width(m_lWindID, 5); //liuxu
		set_color(m_lWindID,"magenta");

		switch(nId)
		{			
			case ITEM_HORI_SIZE:
				{
					s_oHoriSize &oHoriSize = vModelShape.value<s_oHoriSize>();
					disp_obj(oHoriSize.oSizeRect,m_lWindID);
				}
				break;
			case ITEM_VERT_SIZE:
				{
					s_oVertSize &oVertSize = vModelShape.value<s_oVertSize>();
					disp_obj(oVertSize.oSizeRect,m_lWindID);
				}
				break;
			case ITEM_FULL_HEIGHT:
				{
					s_oFullHeight &oFullHeight = vModelShape.value<s_oFullHeight>();
					disp_obj(oFullHeight.oSizeRect,m_lWindID);
				}
				break;
			case ITEM_SGENNERAL_REGION:
				{										
					s_oSGenReg oSGenReg = vModelShape.value<s_oSGenReg>();
					s_pSGenReg pSGenReg = vModelPara.value<s_pSGenReg>();
					if (pSGenReg.nShapeType == 0)
					{
						disp_obj(oSGenReg.oCheckRegion,m_lWindID);
					}
					else
					{
						disp_obj(oSGenReg.oCheckRegion_Rect,m_lWindID);
					}
				}
				break;
			case ITEM_DISTURB_REGION:
				{										
					s_oDistReg oDistReg = vModelShape.value<s_oDistReg>();
					s_pDistReg pDistReg = vModelPara.value<s_pDistReg>();
					if (pDistReg.nShapeType == 0)
					{
						disp_obj(oDistReg.oDisturbReg,m_lWindID);
					}
					else
					{
						disp_obj(oDistReg.oDisturbReg_Rect,m_lWindID);
					}
				}
				break;
			case ITEM_SSIDEFINISH_REGION:
				{										
					s_oSSideFReg oSSideFReg = vModelShape.value<s_oSSideFReg>();
					s_pSSideFReg pSSideFReg = vModelPara.value<s_pSSideFReg>();
					if (pSSideFReg.nShapeType == 0)
					{
						disp_obj(oSSideFReg.oCheckRegion,m_lWindID);
					}
					else
					{
						disp_obj(oSSideFReg.oCheckRegion_Rect,m_lWindID);
					}
				}
				break;
			case ITEM_SINFINISH_REGION:
				{										
					s_oSInFReg oSInFReg = vModelShape.value<s_oSInFReg>();
					disp_obj(oSInFReg.oCheckRegion,m_lWindID);				
				}
				break;
			case ITEM_SSCREWFINISH_REGION:
				{										
					s_oSScrewFReg oSScrewFReg = vModelShape.value<s_oSScrewFReg>();
					s_pSScrewFReg pSScrewFReg = vModelPara.value<s_pSScrewFReg>();
					if (pSScrewFReg.nShapeType == 0)
					{
						disp_obj(oSScrewFReg.oCheckRegion,m_lWindID);
					}
					else
					{
						disp_obj(oSScrewFReg.oCheckRegion_Rect,m_lWindID);
					}				
				}
				break;
			case ITEM_FRLINNER_REGION:
				{										
					s_oFRLInReg oFRLInReg = vModelShape.value<s_oFRLInReg>();
					disp_obj(oFRLInReg.oInCircle,m_lWindID);		
					disp_obj(oFRLInReg.oOutCircle,m_lWindID);
				}
				break;
			case ITEM_FRLMIDDLE_REGION:
				{										
					s_oFRLMidReg oFRLMidReg = vModelShape.value<s_oFRLMidReg>();
					disp_obj(oFRLMidReg.oInCircle,m_lWindID);		
					disp_obj(oFRLMidReg.oOutCircle,m_lWindID);
				}
				break;
			case ITEM_FRLOUTER_REGION:
				{										
					s_oFRLOutReg oFRLOutReg = vModelShape.value<s_oFRLOutReg>();
					disp_obj(oFRLOutReg.oInCircle,m_lWindID);		
					disp_obj(oFRLOutReg.oOutCircle,m_lWindID);
				}
				break;
			case ITEM_FBLINNER_REGION:
				{										
					s_oFBLInReg oFBLInReg = vModelShape.value<s_oFBLInReg>();
					disp_obj(oFBLInReg.oPolygon,m_lWindID);	
				}
				break;
			case ITEM_FBLMIDDLE_REGION:
				{										
					s_oFBLMidReg oFBLMidReg = vModelShape.value<s_oFBLMidReg>();
					disp_obj(oFBLMidReg.oInCircle,m_lWindID);		
					disp_obj(oFBLMidReg.oOutCircle,m_lWindID);
				}
				break;
			case ITEM_BINNER_REGION:
				{										
					s_oBInReg oBInReg = vModelShape.value<s_oBInReg>();
					s_pBInReg pBInReg = vModelPara.value<s_pBInReg>();
					//disp_obj(oBInReg.oOutCircle,m_lWindID);		
					if (1 == pBInReg.nMethodIdx)
					{
						disp_obj(oBInReg.oInCircle,m_lWindID);	
						disp_obj(oBInReg.oOutCircle,m_lWindID);	
					}
					if (0 == pBInReg.nMethodIdx)
					{
						disp_obj(oBInReg.oOutCircle,m_lWindID);		
					}
					if (3 == pBInReg.nMethodIdx)
					{
						disp_obj(oBInReg.oTriBase,m_lWindID);		
					}
					if (2 == pBInReg.nMethodIdx)
					{
						disp_obj(oBInReg.oRectBase,m_lWindID);		
					}
					if (pBInReg.bChar)
					{
						disp_obj(oBInReg.oCurCharReg,m_lWindID);
						disp_obj(oBInReg.oCurMarkReg,m_lWindID);
					}
				}
				break;
			case ITEM_BMIDDLE_REGION:
				{										
					s_oBMidReg oBMidReg = vModelShape.value<s_oBMidReg>();
					disp_obj(oBMidReg.oOutCircle,m_lWindID);		
					disp_obj(oBMidReg.oInCircle,m_lWindID);		
				}
				break;
			case ITEM_BOUTER_REGION:
				{										
					s_oBOutReg oBOutReg = vModelShape.value<s_oBOutReg>();
					disp_obj(oBOutReg.oInCircle,m_lWindID);		
					disp_obj(oBOutReg.oOutCircle,m_lWindID);		
				}
				break;
			case ITEM_SSIDEWALL_REGION:
				{										
					s_oSSideReg oSSideReg = vModelShape.value<s_oSSideReg>();
					s_pSSideReg pSSideReg = vModelPara.value<s_pSSideReg>();	
					if (pSSideReg.nShapeType == 0)
					{
						disp_obj(oSSideReg.oCheckRegion,m_lWindID);
					}
					else
					{
						disp_obj(oSSideReg.oCheckRegion_Rect,m_lWindID);
					}	
				}
				break;
			case ITEM_FINISH_CONTOUR:
				{										
					s_oFinCont oFinCont = vModelShape.value<s_oFinCont>();
					disp_obj(oFinCont.oCheckRegion,m_lWindID);				
				}
				break;
			case ITEM_NECK_CONTOUR:
				{
					s_oNeckCont &oNeckCont = vModelShape.value<s_oNeckCont>();
					disp_obj(oNeckCont.oCheckRegion,m_lWindID);
				}
				break;
			case ITEM_BODY_CONTOUR:
				{
					s_oBodyCont &oBodyCont = vModelShape.value<s_oBodyCont>();
					disp_obj(oBodyCont.oCheckRegion,m_lWindID);
				}
				break;
			case ITEM_SBRISPOT_REGION:
				{
					s_oSBriSpotReg &oSBriSpotReg = vModelShape.value<s_oSBriSpotReg>();
					s_pSBriSpotReg &pSBriSpotReg = vModelPara.value<s_pSBriSpotReg>();	
					if (pSBriSpotReg.nShapeType == 0)
					{
						disp_obj(oSBriSpotReg.oCheckRegion,m_lWindID);
					}
					else
					{
						disp_obj(oSBriSpotReg.oCheckRegion_Rect,m_lWindID);
					}			
				}
				break;
			case ITEM_BALL_REGION:
				{										
					s_oBAllReg oBAllReg = vModelShape.value<s_oBAllReg>();	
					disp_obj(oBAllReg.oOutCircle,m_lWindID);	
				}
				break;
			case ITEM_CIRCLE_SIZE:
				{											
					s_oCirSize oCirSize = vModelShape.value<s_oCirSize>();
					disp_obj(oCirSize.oCircle,m_lWindID);		
				}
				break;
			case ITEM_SBASE_REGION:
				{										
					s_oSBaseReg oSBaseReg = vModelShape.value<s_oSBaseReg>();
					s_pSBaseReg pSBaseReg = vModelPara.value<s_pSBaseReg>();
					disp_obj(oSBaseReg.oOutCircle,m_lWindID);					
					if (1 == pSBaseReg.nMethodIdx)
					{
						disp_obj(oSBaseReg.oInCircle,m_lWindID);					
					}					
				}
				break;
			case ITEM_SBASECONVEX_REGION:
				{										
					s_oSBaseConvexReg oSBaseConvexReg = vModelShape.value<s_oSBaseConvexReg>();
					disp_obj(oSBaseConvexReg.oCheckRegion,m_lWindID);
				}
				break;
			default:
				break;
			}	
			set_line_width(m_lWindID, 2); //liuxu	
	}
	catch(HException &e)
	{
		//Halcon�쳣		
		QString tempStr,strErr;
		tempStr=e.message;
		tempStr.remove(0,20);
		strErr = QString("abnormal:displayRoiHighLight,Highlight the display region")+ tempStr;//������ʾ����
		pChecker->writeErrDataRecord(strErr);
	}
	catch (...)
	{
		pChecker->writeErrDataRecord(QString("abnormal:displayRoiHighLight,Highlight the display region"));//������ʾ����		
	}
}

//*���ܣ��ж�ĳ�������Ƿ�ѡ��
void CDlgMainWindow::judgeObjStatus(int nPressRow, int nPressCol)
{
	try
	{
		// ��ȡ��״����
		int i;
		int nItemClicked = -1;
		Hlong isInside;
		Hobject regPro,xldPro;
		double fDis,fTemp;
		fDis = 9999;
		ui.processBox->nOnMouseItem = -1;
		ui.processBox->bItemClicked = false;
		for (i=0;i<pChecker->vItemFlow.size();++i)
		{
			ui.processBox->vItemLabels[i]->bClicked = false;
			ui.processBox->vItemLabels[i]->setColStyle();
			switch(pChecker->vItemFlow[i])
			{
			case ITEM_SIDEWALL_LOCATE:
				{
					s_oSideLoc &oSideLoc = pChecker->vModelShapes[i].value<s_oSideLoc>();
					s_pSideLoc &pSideLoc = pChecker->vModelParas[i].value<s_pSideLoc>();
					if (!pSideLoc.bEnabled)
					{
						break;
					}
				}
				break;
			case ITEM_FINISH_LOCATE:
				{
					s_oFinLoc &oFinLoc = pChecker->vModelShapes[i].value<s_oFinLoc>();
					s_pFinLoc &pFinLoc = pChecker->vModelParas[i].value<s_pFinLoc>();
					if (!pFinLoc.bEnabled)
					{
						break;
					}
				}
				break;
			case ITEM_BASE_LOCATE:
				{
					s_oBaseLoc &oBaseLoc = pChecker->vModelShapes[i].value<s_oBaseLoc>();
					s_pBaseLoc &pBaseLoc = pChecker->vModelParas[i].value<s_pBaseLoc>();
					if (!pBaseLoc.bEnabled)
					{
						break;
					}
				}
				break;
			case ITEM_HORI_SIZE:
				{
					s_oHoriSize &oHoriSize = pChecker->vModelShapes[i].value<s_oHoriSize>();
					s_pHoriSize &pHoriSize = pChecker->vModelParas[i].value<s_pHoriSize>();
					if (!pHoriSize.bEnabled)
					{
						break;
					}
					gen_region_contour_xld(oHoriSize.oSizeRect,&regPro,"filled");
					test_region_point(regPro,nPressRow,nPressCol,&isInside);
					if (isInside)
					{						
						distance_pc(oHoriSize.oSizeRect, nPressRow, nPressCol, &fTemp, NULL);
						if (fTemp < fDis)
						{
							nItemClicked = i;
							fDis = fTemp;
						}
					}	
				}
				break;
			case ITEM_VERT_SIZE:
				{
					s_oVertSize &oVertSize = pChecker->vModelShapes[i].value<s_oVertSize>();
					s_pVertSize &pVertSize = pChecker->vModelParas[i].value<s_pVertSize>();
					if (!pVertSize.bEnabled)
					{
						break;
					}
					gen_region_contour_xld(oVertSize.oSizeRect,&regPro,"filled");
					test_region_point(regPro,nPressRow,nPressCol,&isInside);
					if (isInside)
					{
						distance_pc(oVertSize.oSizeRect, nPressRow, nPressCol, &fTemp, NULL);
						if (fTemp < fDis)
						{
							nItemClicked = i;
							fDis = fTemp;
						}
					}
				}
				break;
			case ITEM_FULL_HEIGHT:
				{
					s_oFullHeight &oFullHeight = pChecker->vModelShapes[i].value<s_oFullHeight>();
					s_pFullHeight &pFullHeight = pChecker->vModelParas[i].value<s_pFullHeight>();
					if (!pFullHeight.bEnabled)
					{
						break;
					}
					gen_region_contour_xld(oFullHeight.oSizeRect,&regPro,"filled");
					test_region_point(regPro,nPressRow,nPressCol,&isInside);
					if (isInside)
					{
						distance_pc(oFullHeight.oSizeRect, nPressRow, nPressCol, &fTemp, NULL);
						if (fTemp < fDis)
						{
							nItemClicked = i;
							fDis = fTemp;
						}						
					}
				}
				break;
			case ITEM_BENT_NECK:
				{
					s_oBentNeck &oBentNeck = pChecker->vModelShapes[i].value<s_oBentNeck>();
					s_pBentNeck &pBentNeck = pChecker->vModelParas[i].value<s_pBentNeck>();
					if (!pBentNeck.bEnabled)
					{
						break;
					}					
				}
				break;
			case ITEM_VERT_ANG:
				{
					s_pVertAng &pVertAng = pChecker->vModelParas[i].value<s_pVertAng>();
					if (!pVertAng.bEnabled)
					{
						break;
					}
				}
				break;
			case ITEM_SGENNERAL_REGION:
				{										
					s_oSGenReg oSGenReg = pChecker->vModelShapes[i].value<s_oSGenReg>();
					s_pSGenReg pSGenReg = pChecker->vModelParas[i].value<s_pSGenReg>();
					if (!pSGenReg.bEnabled)
					{
						break;
					}

					Hobject TempCont;
					if (pSGenReg.nShapeType == 0)
					{
						copy_obj(oSGenReg.oCheckRegion,&TempCont,1,-1);
					}
					else
					{
						copy_obj(oSGenReg.oCheckRegion_Rect,&TempCont,1,-1);
					}
					gen_region_contour_xld(TempCont,&regPro,"filled");
					
					test_region_point(regPro,nPressRow,nPressCol,&isInside);
					if (isInside)
					{
						distance_pc(TempCont, nPressRow, nPressCol, &fTemp, NULL);
						if (fTemp < fDis)
						{
							nItemClicked = i;
							fDis = fTemp;
						}					
					}
				}
				break;
			case ITEM_DISTURB_REGION:
				{										
					s_oDistReg oDistReg = pChecker->vModelShapes[i].value<s_oDistReg>();
					s_pDistReg pDistReg = pChecker->vModelParas[i].value<s_pDistReg>();
					if (!pDistReg.bEnabled)
					{
						break;
					}
					Hobject TempCont;
					if (pDistReg.nShapeType == 0)
					{
						copy_obj(oDistReg.oDisturbReg,&TempCont,1,-1);
					}
					else
					{
						copy_obj(oDistReg.oDisturbReg_Rect,&TempCont,1,-1);
					}
					gen_region_contour_xld(TempCont,&regPro,"filled");
					test_region_point(regPro,nPressRow,nPressCol,&isInside);
					if (isInside)
					{
						distance_pc(TempCont, nPressRow, nPressCol, &fTemp, NULL);
						if (fTemp < fDis)
						{
							nItemClicked = i;
							fDis = fTemp;
						}						
					}
				}
				break;
			case ITEM_SSIDEFINISH_REGION:
				{										
					s_oSSideFReg oSSideFReg = pChecker->vModelShapes[i].value<s_oSSideFReg>();
					s_pSSideFReg pSSideFReg = pChecker->vModelParas[i].value<s_pSSideFReg>();
					if (!pSSideFReg.bEnabled)
					{
						break;
					}
					Hobject TempCont;
					if (pSSideFReg.nShapeType == 0)
					{
						copy_obj(oSSideFReg.oCheckRegion,&TempCont,1,-1);
					}
					else
					{
						copy_obj(oSSideFReg.oCheckRegion_Rect,&TempCont,1,-1);
					}
					gen_region_contour_xld(TempCont,&regPro,"filled");
					test_region_point(regPro,nPressRow,nPressCol,&isInside);
					if (isInside)
					{
						distance_pc(TempCont, nPressRow, nPressCol, &fTemp, NULL);
						if (fTemp < fDis)
						{
							nItemClicked = i;
							fDis = fTemp;
						}					
					}
				}
				break;
			case ITEM_SINFINISH_REGION:
				{										
					s_oSInFReg oSInFReg = pChecker->vModelShapes[i].value<s_oSInFReg>();
					s_pSInFReg pSInFReg = pChecker->vModelParas[i].value<s_pSInFReg>();
					if (!pSInFReg.bEnabled)
					{
						break;
					}
					gen_region_contour_xld(oSInFReg.oCheckRegion,&regPro,"filled");
					test_region_point(regPro,nPressRow,nPressCol,&isInside);
					if (isInside)
					{
						distance_pc(oSInFReg.oCheckRegion, nPressRow, nPressCol, &fTemp, NULL);
						if (fTemp < fDis)
						{
							nItemClicked = i;
							fDis = fTemp;
						}					
					}
				}
				break;
			case ITEM_SSCREWFINISH_REGION:
				{										
					s_oSScrewFReg oSScrewFReg = pChecker->vModelShapes[i].value<s_oSScrewFReg>();
					s_pSScrewFReg pSScrewFReg = pChecker->vModelParas[i].value<s_pSScrewFReg>();
					if (!pSScrewFReg.bEnabled)
					{
						break;
					}
					Hobject TempCont;
					if (pSScrewFReg.nShapeType == 0)
					{
						copy_obj(oSScrewFReg.oCheckRegion,&TempCont,1,-1);
					}
					else
					{
						copy_obj(oSScrewFReg.oCheckRegion_Rect,&TempCont,1,-1);
					}
					gen_region_contour_xld(TempCont,&regPro,"filled");
					test_region_point(regPro,nPressRow,nPressCol,&isInside);
					if (isInside)
					{
						distance_pc(TempCont, nPressRow, nPressCol, &fTemp, NULL);
						if (fTemp < fDis)
						{
							nItemClicked = i;
							fDis = fTemp;
						}					
					}			
				}
				break;
			case ITEM_FRLINNER_REGION:
				{										
					s_oFRLInReg oFRLInReg = pChecker->vModelShapes[i].value<s_oFRLInReg>();
					s_pFRLInReg pFRLInReg = pChecker->vModelParas[i].value<s_pFRLInReg>();
					if (!pFRLInReg.bEnabled)
					{
						break;
					}
					
					difference(oFRLInReg.oOutCircle,oFRLInReg.oInCircle,&regPro);
					test_region_point(regPro,nPressRow,nPressCol,&isInside);
					if (isInside)
					{
						gen_contour_region_xld(regPro, &xldPro, "border_holes");
						distance_pc(xldPro, nPressRow, nPressCol, &fTemp, NULL);
						if (fTemp < fDis)
						{
							nItemClicked = i;
							fDis = fTemp;
						}				
					}
				}
				break;
			case ITEM_FRLMIDDLE_REGION:
				{										
					s_oFRLMidReg oFRLMidReg = pChecker->vModelShapes[i].value<s_oFRLMidReg>();
					s_pFRLMidReg pFRLMidReg = pChecker->vModelParas[i].value<s_pFRLMidReg>();
					if (!pFRLMidReg.bEnabled)
					{
						break;
					}
					
					difference(oFRLMidReg.oOutCircle,oFRLMidReg.oInCircle,&regPro);
					test_region_point(regPro,nPressRow,nPressCol,&isInside);
					if (isInside)
					{
						gen_contour_region_xld(regPro, &xldPro, "border_holes");
						distance_pc(xldPro, nPressRow, nPressCol, &fTemp, NULL);
						if (fTemp < fDis)
						{
							nItemClicked = i;
							fDis = fTemp;
						}				
					}
				}
				break;
			case ITEM_FRLOUTER_REGION:
				{										
					s_oFRLOutReg oFRLOutReg = pChecker->vModelShapes[i].value<s_oFRLOutReg>();
					s_pFRLOutReg pFRLOutReg = pChecker->vModelParas[i].value<s_pFRLOutReg>();
					if (!pFRLOutReg.bEnabled)
					{
						break;
					}
					
					difference(oFRLOutReg.oOutCircle,oFRLOutReg.oInCircle,&regPro);
					test_region_point(regPro,nPressRow,nPressCol,&isInside);
					if (isInside)
					{
						gen_contour_region_xld(regPro, &xldPro, "border_holes");
						distance_pc(xldPro, nPressRow, nPressCol, &fTemp, NULL);
						if (fTemp < fDis)
						{
							nItemClicked = i;
							fDis = fTemp;
						}
					}
				}
				break;
			case ITEM_FBLINNER_REGION:
				{										
					s_oFBLInReg oFBLInReg = pChecker->vModelShapes[i].value<s_oFBLInReg>();
					s_pFBLInReg pFBLInReg = pChecker->vModelParas[i].value<s_pFBLInReg>();
					if (!pFBLInReg.bEnabled)
					{
						break;
					}
					
					// ���޸�---2017.3��ƿ�ڱ�����ʱ��Ϊ������ӡ
					//difference(oFBLInReg.oOutCircle,oFBLInReg.oInCircle,&regPro);
					gen_region_contour_xld(oFBLInReg.oPolygon,&regPro,"filled");
					test_region_point(regPro,nPressRow,nPressCol,&isInside);
					if (isInside)
					{
						gen_contour_region_xld(regPro, &xldPro, "border_holes");
						distance_pc(xldPro, nPressRow, nPressCol, &fTemp, NULL);
						if (fTemp < fDis)
						{
							nItemClicked = i;
							fDis = fTemp;
						}
					}
				}
				break;
			case ITEM_FBLMIDDLE_REGION:
				{										
					s_oFBLMidReg oFBLMidReg = pChecker->vModelShapes[i].value<s_oFBLMidReg>();
					s_pFBLMidReg pFBLMidReg = pChecker->vModelParas[i].value<s_pFBLMidReg>();
					if (!pFBLMidReg.bEnabled)
					{
						break;
					}
					
					difference(oFBLMidReg.oOutCircle,oFBLMidReg.oInCircle,&regPro);
					test_region_point(regPro,nPressRow,nPressCol,&isInside);
					if (isInside)
					{
						gen_contour_region_xld(regPro, &xldPro, "border_holes");
						distance_pc(xldPro, nPressRow, nPressCol, &fTemp, NULL);
						if (fTemp < fDis)
						{
							nItemClicked = i;
							fDis = fTemp;
						}
					}
				}
				break;
			case ITEM_BINNER_REGION:
				{										
					s_oBInReg oBInReg = pChecker->vModelShapes[i].value<s_oBInReg>();
					s_pBInReg pBInReg = pChecker->vModelParas[i].value<s_pBInReg>();
					if (!pBInReg.bEnabled)
					{
						break;
					}
					if (1 == pChecker->vModelParas[i].value<s_pBInReg>().nMethodIdx)
					{
						difference(oBInReg.oOutCircle,oBInReg.oInCircle,&regPro);
					}
					else if(0 == pChecker->vModelParas[i].value<s_pBInReg>().nMethodIdx)
					{
						regPro = oBInReg.oOutCircle;
					}
					else if(3 == pChecker->vModelParas[i].value<s_pBInReg>().nMethodIdx)
					{
						regPro = oBInReg.oTriBase;
					}
					else if(2 == pChecker->vModelParas[i].value<s_pBInReg>().nMethodIdx)
					{
						regPro = oBInReg.oRectBase;
					}
					test_region_point(regPro,nPressRow,nPressCol,&isInside);
					if (isInside)
					{
						gen_contour_region_xld(regPro, &xldPro, "border_holes");
						distance_pc(xldPro, nPressRow, nPressCol, &fTemp, NULL);
						if (fTemp < fDis)
						{
							nItemClicked = i;
							fDis = fTemp;
						}
					}
				}
				break;
			case ITEM_BMIDDLE_REGION:
				{										
					s_oBMidReg oBMidReg = pChecker->vModelShapes[i].value<s_oBMidReg>();
					s_pBMidReg pBMidReg = pChecker->vModelParas[i].value<s_pBMidReg>();
					if (!pBMidReg.bEnabled)
					{
						break;
					}
					
					difference(oBMidReg.oOutCircle,oBMidReg.oInCircle,&regPro);
					test_region_point(regPro,nPressRow,nPressCol,&isInside);
					if (isInside)
					{
						gen_contour_region_xld(regPro, &xldPro, "border_holes");
						distance_pc(xldPro, nPressRow, nPressCol, &fTemp, NULL);
						if (fTemp < fDis)
						{
							nItemClicked = i;
							fDis = fTemp;
						}
					}
				}
				break;
			case ITEM_BOUTER_REGION:
				{										
					s_oBOutReg oBOutReg = pChecker->vModelShapes[i].value<s_oBOutReg>();
					s_pBOutReg pBOutReg = pChecker->vModelParas[i].value<s_pBOutReg>();
					if (!pBOutReg.bEnabled)
					{
						break;
					}
					
					difference(oBOutReg.oOutCircle,oBOutReg.oInCircle,&regPro);
					test_region_point(regPro,nPressRow,nPressCol,&isInside);
					if (isInside)
					{
						gen_contour_region_xld(regPro, &xldPro, "border_holes");
						distance_pc(xldPro, nPressRow, nPressCol, &fTemp, NULL);
						if (fTemp < fDis)
						{
							nItemClicked = i;
							fDis = fTemp;
						}
					}
				}
				break;
			case ITEM_SSIDEWALL_REGION:
				{										
					s_oSSideReg oSSideReg = pChecker->vModelShapes[i].value<s_oSSideReg>();
					s_pSSideReg pSSideReg = pChecker->vModelParas[i].value<s_pSSideReg>();
					if (!pSSideReg.bEnabled)
					{
						break;
					}
					Hobject TempCont;
					if (pSSideReg.nShapeType == 0)
					{
						copy_obj(oSSideReg.oCheckRegion,&TempCont,1,-1);
					}
					else
					{
						copy_obj(oSSideReg.oCheckRegion_Rect,&TempCont,1,-1);
					}
					gen_region_contour_xld(TempCont,&regPro,"filled");
					test_region_point(regPro,nPressRow,nPressCol,&isInside);
					if (isInside)
					{
						distance_pc(TempCont, nPressRow, nPressCol, &fTemp, NULL);
						if (fTemp < fDis)
						{
							nItemClicked = i;
							fDis = fTemp;
						}
					}
				}
				break;
			case ITEM_FINISH_CONTOUR:
				{										
					s_oFinCont oFinCont = pChecker->vModelShapes[i].value<s_oFinCont>();
					s_pFinCont pFinCont = pChecker->vModelParas[i].value<s_pFinCont>();
					if (!pFinCont.bEnabled)
					{
						break;
					}
				}
				break;
			case ITEM_NECK_CONTOUR:
				{
					s_oNeckCont &oNeckCont = pChecker->vModelShapes[i].value<s_oNeckCont>();
					s_pNeckCont &pNeckCont = pChecker->vModelParas[i].value<s_pNeckCont>();
					if (!pNeckCont.bEnabled)
					{
						break;
					}
					gen_region_contour_xld(oNeckCont.oCheckRegion,&regPro,"filled");
					test_region_point(regPro,nPressRow,nPressCol,&isInside);
					if (isInside)
					{
						distance_pc(oNeckCont.oCheckRegion, nPressRow, nPressCol, &fTemp, NULL);
						if (fTemp < fDis)
						{
							nItemClicked = i;
							fDis = fTemp;
						}
					}
				}
				break;
			case ITEM_BODY_CONTOUR:
				{
					s_oBodyCont &oBodyCont = pChecker->vModelShapes[i].value<s_oBodyCont>();
					s_pBodyCont &pBodyCont = pChecker->vModelParas[i].value<s_pBodyCont>();
					if (!pBodyCont.bEnabled)
					{
						break;
					}
					gen_region_contour_xld(oBodyCont.oCheckRegion,&regPro,"filled");
					test_region_point(regPro,nPressRow,nPressCol,&isInside);
					if (isInside)
					{
						distance_pc(oBodyCont.oCheckRegion, nPressRow, nPressCol, &fTemp, NULL);
						if (fTemp < fDis)
						{
							nItemClicked = i;
							fDis = fTemp;
						}
					}
				}
				break;
			case ITEM_SBRISPOT_REGION:
				{
					s_oSBriSpotReg &oSBriSpotReg = pChecker->vModelShapes[i].value<s_oSBriSpotReg>();
					s_pSBriSpotReg &pSBriSpotReg = pChecker->vModelParas[i].value<s_pSBriSpotReg>();
					if (!pSBriSpotReg.bEnabled)
					{
						break;
					}
					Hobject TempCont;
					if (pSBriSpotReg.nShapeType == 0)
					{
						copy_obj(oSBriSpotReg.oCheckRegion,&TempCont,1,-1);
					}
					else
					{
						copy_obj(oSBriSpotReg.oCheckRegion_Rect,&TempCont,1,-1);
					}
					gen_region_contour_xld(TempCont,&regPro,"filled");
					test_region_point(regPro,nPressRow,nPressCol,&isInside);
					if (isInside)
					{
						distance_pc(TempCont, nPressRow, nPressCol, &fTemp, NULL);
						if (fTemp < fDis)
						{
							nItemClicked = i;
							fDis = fTemp;
						}
					}
				}
				break;
			case ITEM_BALL_REGION:
				{										
					s_oBAllReg oBAllReg = pChecker->vModelShapes[i].value<s_oBAllReg>();
					s_pBAllReg pBAllReg = pChecker->vModelParas[i].value<s_pBAllReg>();
					if (!pBAllReg.bEnabled)
					{
						break;
					}
					
					//difference(oBAllReg.oOutCircle,oBAllReg.oInCircle,&regPro);
					copy_obj (oBAllReg.oOutCircle,&regPro,1,-1);
					test_region_point(regPro,nPressRow,nPressCol,&isInside);
					if (isInside)
					{
						gen_contour_region_xld(regPro, &xldPro, "border_holes");
						distance_pc(xldPro, nPressRow, nPressCol, &fTemp, NULL);
						if (fTemp < fDis)
						{
							nItemClicked = i;
							fDis = fTemp;
						}
					}
				}
				break;
			case ITEM_CIRCLE_SIZE:
				{										
					s_pCirSize pCirSize = pChecker->vModelParas[i].value<s_pCirSize>();		
					s_oCirSize oCirSize = pChecker->vModelShapes[i].value<s_oCirSize>();
					if (!pCirSize.bEnabled)
					{
						break;
					}
					test_region_point(oCirSize.oCircle,nPressRow,nPressCol,&isInside);
					if (isInside)
					{
						gen_contour_region_xld(oCirSize.oCircle, &xldPro, "border_holes");
						distance_pc(xldPro, nPressRow, nPressCol, &fTemp, NULL);
						if (fTemp < fDis)
						{
							nItemClicked = i;
							fDis = fTemp;
						}
					}					
				}
				break;
			case ITEM_SBASE_REGION:
				{										
					s_oSBaseReg oSBaseReg = pChecker->vModelShapes[i].value<s_oSBaseReg>();
					s_pSBaseReg pSBaseReg = pChecker->vModelParas[i].value<s_pSBaseReg>();
					if (!pSBaseReg.bEnabled)
					{
						break;
					}
									
					if (1 == pChecker->vModelParas[i].value<s_pSBaseReg>().nMethodIdx)
					{
						difference(oSBaseReg.oOutCircle,oSBaseReg.oInCircle,&regPro);
					}
					else
					{
						regPro = oSBaseReg.oOutCircle;
					}
					
					test_region_point(regPro,nPressRow,nPressCol,&isInside);
					if (isInside)
					{
						gen_contour_region_xld(regPro, &xldPro, "border_holes");
						distance_pc(xldPro, nPressRow, nPressCol, &fTemp, NULL);
						if (fTemp < fDis)
						{
							nItemClicked = i;
							fDis = fTemp;
						}
					}
				}
				break;
			case ITEM_SBASECONVEX_REGION:
				{										
					s_oSBaseConvexReg oSBaseConvexReg = pChecker->vModelShapes[i].value<s_oSBaseConvexReg>();
					s_pSBaseConvexReg pSBaseConvexReg = pChecker->vModelParas[i].value<s_pSBaseConvexReg>();
					if (!pSBaseConvexReg.bEnabled)
					{
						break;
					}
					gen_region_contour_xld(oSBaseConvexReg.oCheckRegion,&regPro,"filled");
					test_region_point(regPro,nPressRow,nPressCol,&isInside);
					if (isInside)
					{
						distance_pc(oSBaseConvexReg.oCheckRegion, nPressRow, nPressCol, &fTemp, NULL);
						if (fTemp < fDis)
						{
							nItemClicked = i;
							fDis = fTemp;
						}
					}	
				}
				break;
			default:
				break;
			}
		}
		if (nItemClicked > -1)
		{
			ui.processBox->nOnMouseItem = nItemClicked;
			ui.processBox->bItemClicked = true;
			ui.processBox->vItemLabels[nItemClicked]->bClicked = true;

			pItemLabel = (QWidget *)ui.processBox->vItemLabels[nItemClicked];
			setBtnStatus();
				
			ui.processBox->vItemLabels[nItemClicked]->setColStyle();
			ui.processBox->updateItemDlg(ui.processBox->vItemLabels[nItemClicked]);
		}
		else
		{
			ui.processBox->bItemClicked = false;
			setBtnStatus();
			// �رնԻ���
			CItemDlg* pDlg = (CItemDlg*)pItemDlg;
			if (NULL != pDlg)
			{
				delete pDlg;
			}
			pItemDlg = NULL;
			pItemLabel = NULL;
		}
	}
	catch(HException &e)
	{
		//Halcon�쳣		
		QString tempStr,strErr;
		tempStr=e.message;
		tempStr.remove(0,20);
		strErr = QString("abnormal:judgeObjStatus")+ tempStr;
		pChecker->writeErrDataRecord(strErr);
	}
	catch (...)
	{
		pChecker->writeErrDataRecord(QString("abnormal:judgeObjStatus"));		
	}
}
//*���ܣ���ʾ�ų�ȱ����Ϣ��
bool CDlgMainWindow::displayExcludeInfo(CCheck *pShowChecker,Hlong lpRow,Hlong lpCol)
{
	try
	{
		if (pShowChecker->m_bExtExcludeDefect)
		{
			int i,j;
			Hlong nNum,isInside,nArea,nMaxArea = 0;
			Hobject objSel,regInside;
			int nindexi = -1;	//�����ų�������
			int nindexj = -1;	//�����ų�������
			ShowExcludeInfo showExcludeInfo;//�����ų�������Ϣ
			gen_empty_obj(&regInside);
			for (i=0;i<pShowChecker->m_vExcludeInfo.count();++i)
			{
				count_obj(pShowChecker->m_vExcludeInfo.at(i).regExclude,&nNum);			
				for (j=0;j<nNum;++j)
				{
					//�ж��Ƿ���ȱ���ϰ���
					select_obj(pShowChecker->m_vExcludeInfo.at(i).regExclude,&objSel,j+1);
					test_region_point(objSel,lPressRow,lPressCol,&isInside);
					if (isInside)
					{
						area_center(objSel,&nArea,NULL,NULL);
						if (nArea>nMaxArea)
						{
							nindexi = i;
							nindexj = j;
							nMaxArea = nArea;
							copy_obj(objSel,&regInside,1,-1);
						}
						break;
					}
				}
			}
			if (nindexi<0 || nindexj<0)
			{
				return false;
			}
			showExcludeInfo.strIndex += QString("%1-%2").arg(nindexi+1).arg(nindexj+1);
			showExcludeInfo.strDetName += pShowChecker->m_vExcludeInfo.at(nindexi).strDetName;
			//����ȱ����Ϣ
			double dRa,dRb,dRab,dPhi,dMeanGray,dInnerDia,dArea;
			//������仯ȱ�ݣ�����ӡ���ڱ��Ρ��⻷ȱ�ڣ���������
			Hobject objLOF,xldInside,regSkeleton;
			double oriRow = pShowChecker->currentOri.Row;
			double oriCol = pShowChecker->currentOri.Col;
			Hlong row1,col1,row2,col2;
			intensity(regInside,imgShow,&dMeanGray,NULL);
			inner_circle(regInside, NULL, NULL, &dInnerDia);
			//�����ų�ȱ�����ͣ����������ͼ���ȱ�ݲ���
			switch(pShowChecker->m_vExcludeInfo.at(nindexi).nDefectType)
			{
			case EXCLUDE_TYPE_GENERALDEFEXTS://һ��ȱ��
				showExcludeInfo.strType += tr("GENERALDEFEXTS");
				elliptic_axis(regInside,&dRa,&dRb,&dPhi);
				dRa*=2;
				dRb = dRb==0?1:dRb*2;
				dRab = dRa/dRb;
				tuple_deg(dPhi,&dPhi);
				break;
			case EXCLUDE_TYPE_STONE://��ʯ
				showExcludeInfo.strType += tr("STONE");
				elliptic_axis(regInside,&dRa,&dRb,&dPhi);
				dRa*=2;
				dRb = dRb==0?1:dRb*2;
				dRab = dRa/dRb;
				tuple_deg(dPhi,&dPhi);
				break;
			case EXCLUDE_TYPE_DARKDOT://С�ڵ�
				showExcludeInfo.strType += tr("DARKDOT");
				elliptic_axis(regInside,&dRa,&dRb,&dPhi);
				dRa*=2;
				dRb = dRb==0?1:dRb*2;
				dRab = dRa/dRb;
				tuple_deg(dPhi,&dPhi);
				break;
			case EXCLUDE_TYPE_DISTURB://����
				showExcludeInfo.strType += tr("DISTURB");
				elliptic_axis(regInside,&dRa,&dRb,&dPhi);
				dRa*=2;
				dRb = dRb==0?1:dRb*2;
				dRab = dRa/dRb;
				tuple_deg(dPhi,&dPhi);
				break;
			case EXCLUDE_TYPE_BACKMOUTHMID://�����ƽ��
				showExcludeInfo.strType += tr("BACKMOUTHMID");
				polar_trans_region(regInside,&objLOF,oriRow,oriCol,2*PI,0,0,pShowChecker->m_nHeight,
					pShowChecker->m_nWidth,pShowChecker->m_nHeight,"nearest_neighbor");		
				smallest_rectangle1(objLOF,&row1,&col1,&row2,&col2);
				dRa = row2-row1;
				dRb = col2-col1;
				dRb = dRb==0?1:dRb;
				dRab = dRa/(dRb);
				dPhi = 0;
				break;
			case EXCLUDE_TYPE_PITTING://���
				showExcludeInfo.strType += tr("PITTING");
				elliptic_axis(regInside,&dRa,&dRb,&dPhi);
				dRa*=2;
				dRb = dRb==0?1:dRb*2;
				dRab = dRa/dRb;
				tuple_deg(dPhi,&dPhi);
				break;
			case EXCLUDE_TYPE_LOF://����ӡ
				showExcludeInfo.strType += tr("LOF");
				polar_trans_region(regInside,&objLOF,oriRow,oriCol,2*PI,0,0,pShowChecker->m_nHeight,
					pShowChecker->m_nWidth,pShowChecker->m_nHeight,"nearest_neighbor");		
				smallest_rectangle1(objLOF,&row1,&col1,&row2,&col2);
				dRa = row2-row1;
				dRb = col2-col1;
				dRb = dRb==0?1:dRb;
				dRab = dRa/(dRb);
				dPhi = 0;
				break;
			case EXCLUDE_TYPE_LOF_BL://2017.3-����ӡ������Դ��
				showExcludeInfo.strType += tr("LOF");
				elliptic_axis(regInside,&dRa,&dRb,&dPhi);
				dRa*=2;
				dRb = dRb==0?1:dRb*2;
				dRab = dRa/dRb;
				tuple_deg(dPhi,&dPhi);
				break;
			case EXCLUDE_TYPE_DEFORM://�ڱ���
				showExcludeInfo.strType += tr("DEFORM");
				polar_trans_region(regInside,&objLOF,oriRow,oriCol,2*PI,0,0,pShowChecker->m_nHeight,
					pShowChecker->m_nWidth,pShowChecker->m_nHeight,"nearest_neighbor");		
				smallest_rectangle1(objLOF,&row1,&col1,&row2,&col2);
				dRa = row2-row1;
				dRb = col2-col1;
				dRb = dRb==0?1:dRb;
				dRab = dRa/(dRb);
				dPhi = 0;
				break;
			case EXCLUDE_TYPE_BROKENRING://�⻷�ϻ�
				showExcludeInfo.strType += tr("BROKENRING");
				contlength(regInside,&dRa);
				smallest_rectangle1(regInside,&row1,&col1,&row2,&col2);
				dRa /= 2;
				dRb = col2-col1;
				dRb = dRb==0?1:dRb;
				dRab = dRa/(dRb);
				dPhi = 0;
				break;
			case EXCLUDE_TYPE_BREACH://�⻷ȱ��
				showExcludeInfo.strType += tr("BREACH");
				polar_trans_region(regInside,&objLOF,oriRow,oriCol,2*PI,0,0,pShowChecker->m_nHeight,
					pShowChecker->m_nWidth,pShowChecker->m_nHeight,"nearest_neighbor");		
				smallest_rectangle1(objLOF,&row1,&col1,&row2,&col2);
				dRa = row2-row1;
				dRb = col2-col1;
				dRb = dRb==0?1:dRb;
				dRab = dRa/(dRb);
				dPhi = 0;
				break;
			case EXCLUDE_TYPE_LIGHTSTRIPE://������
				showExcludeInfo.strType += tr("LIGHTSTRIPE");
				elliptic_axis(regInside,&dRa,&dRb,&dPhi);
				dRa*=2;
				dRb = dRb==0?1:dRb*2;
				dRab = dRa/dRb;
				tuple_deg(dPhi,&dPhi);
				break;
			case EXCLUDE_TYPE_TINYCRACK://΢����
				showExcludeInfo.strType += tr("TINYCRACK");
				elliptic_axis(regInside,&dRa,&dRb,&dPhi);
				dRa*=2;
				dRb = dRb==0?1:dRb*2;
				dRab = dRa/dRb;
				tuple_deg(dPhi,&dPhi);
				break;		
			case EXCLUDE_TYPE_BOTSTRIPE://������
				showExcludeInfo.strType += tr("BOTTOMSTRIPE");
				polar_trans_region(regInside,&objLOF,oriRow,oriCol,2*PI,0,0,pChecker->m_nHeight,
					pChecker->m_nWidth,pChecker->m_nHeight,"nearest_neighbor");		
				smallest_rectangle1(objLOF,&row1,&col1,&row2,&col2);
				dRa = row2-row1;
				dRb = col2-col1;
				dRb = dRb==0?1:dRb;
				eccentricity(objLOF,&dRab,NULL,NULL);
				elliptic_axis(objLOF,NULL,NULL,&dPhi);
				tuple_deg(dPhi,&dPhi);
				//dPhi=dPhi<0?dPhi+180.f:dPhi;
				dPhi = fabs(dPhi);
				break;
			case EXCLUDE_TYPE_DISTCON1://��������1
				showExcludeInfo.strType += tr("DISTCON1");
				elliptic_axis(regInside,&dRa,&dRb,&dPhi);
				dRa*=2;
				dRb = dRb==0?1:dRb*2;
				dRab = dRa/dRb;
				tuple_deg(dPhi,&dPhi);
				break;
			case EXCLUDE_TYPE_DISTCON2://��������2
				showExcludeInfo.strType += tr("DISTCON2");
				elliptic_axis(regInside,&dRa,&dRb,&dPhi);
				dRa*=2;
				dRb = dRb==0?1:dRb*2;
				dRab = dRa/dRb;
				tuple_deg(dPhi,&dPhi);
				break;	
			case EXCLUDE_TYPE_THIN_BUBBLE://��Ƥ����---2018.2,region->xld
				showExcludeInfo.strType += tr("THINBUBBLES");
				skeleton(regInside, &regSkeleton);
				gen_contours_skeleton_xld(regSkeleton, &xldInside, 1, "filter");
				area_center_xld(xldInside,&dArea,NULL,NULL,NULL);
				nArea = Hlong(dArea);
				length_xld(xldInside,&dRa);				
				eccentricity_xld(xldInside,&dRab,NULL,NULL);
				smallest_rectangle2_xld(xldInside,NULL,NULL,&dPhi,NULL,NULL);
				tuple_deg(dPhi,&dPhi);
				dRb=0;
				dMeanGray=0;
				dInnerDia=0;
				//elliptic_axis(regInside,&dRa,&dRb,&dPhi);
				//dRa*=2;
				//dRb = dRb==0?1:dRb*2;
				//dRab = dRa/dRb;
				//tuple_deg(dPhi,&dPhi);
				break;
			case EXCLUDE_TYPE_MOULD_POINT://ģ��ʶ��
				showExcludeInfo.strType += tr("MOULDPOINT");
				smallest_rectangle1(regInside, &row1, &col1, &row2, &col2);
				elliptic_axis(regInside,NULL,NULL,&dPhi);
				dRa = row2-row1+1;
				dRb = col2-col1+1;
				dRb = dRb==0?1:dRb;
				dRab = dRa/(dRb);
				tuple_deg(dPhi,&dPhi);
				break;
			default://����
				showExcludeInfo.strType += tr("OTHER");
				elliptic_axis(regInside,&dRa,&dRb,&dPhi);			
				dRa*=2;
				dRb = dRb==0?1:dRb*2;
				dRab = dRa/dRb;
				tuple_deg(dPhi,&dPhi);
				break;
			}
			showExcludeInfo.strArea += tr("%1").arg(nMaxArea);				
			showExcludeInfo.strLength += tr("%1").arg(QString::number(dRa,'f',1));				
			showExcludeInfo.strWidth += tr("%1").arg(QString::number(dRb,'f',1));
			showExcludeInfo.strInnerDia += tr("%1").arg(QString::number(dInnerDia*2,'f',1));
			showExcludeInfo.strAnisometry += tr("%1").arg(QString::number(dRab,'f',1));				
			showExcludeInfo.strAngle += tr("%1").arg(QString::number(dPhi,'f',1));				
			showExcludeInfo.strMean += tr("%1").arg(QString::number(dMeanGray,'f',1));				

			//��������
			Hlong lWid=150;
			Hlong lHei=180;	
			//��ֹ���ڳ���ͼ��󴰿�
			Hlong maxRow = (pChecker->m_nHeight)*fWndScale/*(nWndScale/10.f)*/-lHei-10;
			Hlong maxCol = (pChecker->m_nWidth)*fWndScale/*(nWndScale/10.f)*/-lWid-10;
			lpRow = lpRow>maxRow?maxRow:lpRow;
			lpCol = lpCol>maxCol?maxCol:lpCol;	
			set_window_attr("border_width",1);
			set_window_attr("background_color","tan");
			open_window(lpRow,lpCol,lWid, lHei, m_lWindID, "visible", "", &m_lRegInfoID);	
			//��ʾ��Ϣ
			int nPosRow = 0;
			int nGapWid = (nMaxCamareWidth*0.95)/12.0;//�м��
			set_font(m_lRegInfoID,"-΢���ź�-15-*-*-*-*-*-ANSI_CHARSET-");//-FontName-Height-Width-Italic-Underlined-Strikeout-Bold-CharSet-
			set_color(m_lRegInfoID,"dark orchid");
			set_tposition(m_lRegInfoID,nPosRow,10);
			write_string(m_lRegInfoID,showExcludeInfo.strIndex.toLocal8Bit().constData());
			set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
			write_string(m_lRegInfoID,showExcludeInfo.strDetName.toLocal8Bit().constData());
			set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
			write_string(m_lRegInfoID,showExcludeInfo.strType.toLocal8Bit().constData());
			if (pShowChecker->m_vExcludeInfo.at(nindexi).bModify)
			{
				set_color(m_lRegInfoID,"dark orchid");
				showExcludeInfo.strModify += tr("TRUE");
			}
			else
			{
				set_color(m_lRegInfoID,"red");
				showExcludeInfo.strModify += tr("FALSE");
			}
			set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
			write_string(m_lRegInfoID,showExcludeInfo.strModify.toLocal8Bit().constData());
			//�����ų�ȱ��ԭ��
			switch(pShowChecker->m_vExcludeInfo.at(nindexi).nDefectCause)
			{
			case EXCLUDE_CAUSE_AREA://���
				showExcludeInfo.strCause += tr("AREA");
				set_color(m_lRegInfoID,"dark orchid");
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strCause.toLocal8Bit().constData());
				set_color(m_lRegInfoID,"red");
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strArea.toLocal8Bit().constData());	
				set_color(m_lRegInfoID,"dark orchid");
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strLength.toLocal8Bit().constData());	
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strWidth.toLocal8Bit().constData());	
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strInnerDia.toLocal8Bit().constData());	
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strAnisometry.toLocal8Bit().constData());	
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strAngle.toLocal8Bit().constData());	
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strMean.toLocal8Bit().constData());	
				break;
			case EXCLUDE_CAUSE_LENGTH://����
				showExcludeInfo.strCause += tr("LENGTH");
				set_color(m_lRegInfoID,"dark orchid");
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strCause.toLocal8Bit().constData());
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strArea.toLocal8Bit().constData());	
				set_color(m_lRegInfoID,"red");
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strLength.toLocal8Bit().constData());	
				set_color(m_lRegInfoID,"dark orchid");
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strWidth.toLocal8Bit().constData());
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strInnerDia.toLocal8Bit().constData());	
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strAnisometry.toLocal8Bit().constData());	
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strAngle.toLocal8Bit().constData());	
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strMean.toLocal8Bit().constData());
				break;
			case EXCLUDE_CAUSE_CIRCULARITY://Բ��
				showExcludeInfo.strCause += tr("CIRCULARITY");
				set_color(m_lRegInfoID,"red");
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strCause.toLocal8Bit().constData());
				set_color(m_lRegInfoID,"dark orchid");
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strArea.toLocal8Bit().constData());	
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strLength.toLocal8Bit().constData());	
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strWidth.toLocal8Bit().constData());
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strInnerDia.toLocal8Bit().constData());	
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strAnisometry.toLocal8Bit().constData());
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strAngle.toLocal8Bit().constData());	
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strMean.toLocal8Bit().constData());
				break;
			case EXCLUDE_CAUSE_PHI://�Ƕ�
				showExcludeInfo.strCause += tr("PHI");
				set_color(m_lRegInfoID,"dark orchid");
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strCause.toLocal8Bit().constData());
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strArea.toLocal8Bit().constData());	
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strLength.toLocal8Bit().constData());	
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strWidth.toLocal8Bit().constData());	
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strInnerDia.toLocal8Bit().constData());	
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strAnisometry.toLocal8Bit().constData());
				set_color(m_lRegInfoID,"red");
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strAngle.toLocal8Bit().constData());	
				set_color(m_lRegInfoID,"dark orchid");
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strMean.toLocal8Bit().constData());
				break;
			case EXCLUDE_CAUSE_AREA_AND_LENGTH://���&����
				showExcludeInfo.strCause += tr("AREA_AND_LENGTH");
				set_color(m_lRegInfoID,"dark orchid");
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strCause.toLocal8Bit().constData());
				set_color(m_lRegInfoID,"red");
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strArea.toLocal8Bit().constData());	
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strLength.toLocal8Bit().constData());	
				set_color(m_lRegInfoID,"dark orchid");
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strWidth.toLocal8Bit().constData());
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strInnerDia.toLocal8Bit().constData());	
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strAnisometry.toLocal8Bit().constData());
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strAngle.toLocal8Bit().constData());	
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strMean.toLocal8Bit().constData());
				break;
			case EXCLUDE_CAUSE_TYPICAL://����ȱ��
				showExcludeInfo.strCause += tr("TYPICAL");
				set_color(m_lRegInfoID,"red");
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strCause.toLocal8Bit().constData());
				set_color(m_lRegInfoID,"dark orchid");
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strArea.toLocal8Bit().constData());	
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strLength.toLocal8Bit().constData());	
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strWidth.toLocal8Bit().constData());
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strInnerDia.toLocal8Bit().constData());	
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strAnisometry.toLocal8Bit().constData());
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strAngle.toLocal8Bit().constData());	
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strMean.toLocal8Bit().constData());
				break;
			case EXCLUDE_CAUSE_STRIPES://����
				showExcludeInfo.strCause += tr("STRIPES");
				set_color(m_lRegInfoID,"red");
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strCause.toLocal8Bit().constData());
				set_color(m_lRegInfoID,"dark orchid");
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strArea.toLocal8Bit().constData());	
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strLength.toLocal8Bit().constData());	
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strWidth.toLocal8Bit().constData());
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strInnerDia.toLocal8Bit().constData());	
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strAnisometry.toLocal8Bit().constData());
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strAngle.toLocal8Bit().constData());	
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strMean.toLocal8Bit().constData());
				break;
			case EXCLUDE_CAUSE_WIDTH://���
				showExcludeInfo.strCause += tr("WIDTH");
				set_color(m_lRegInfoID,"dark orchid");
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strCause.toLocal8Bit().constData());
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strArea.toLocal8Bit().constData());	
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strLength.toLocal8Bit().constData());	
				set_color(m_lRegInfoID,"red");
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strWidth.toLocal8Bit().constData());	
				set_color(m_lRegInfoID,"dark orchid");
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strInnerDia.toLocal8Bit().constData());	
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strAnisometry.toLocal8Bit().constData());
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strAngle.toLocal8Bit().constData());	
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strMean.toLocal8Bit().constData());
				break;
			case EXCLUDE_CAUSE_ANISOMETRY://�����
				showExcludeInfo.strCause += tr("ANISOMETRY");
				set_color(m_lRegInfoID,"dark orchid");
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strCause.toLocal8Bit().constData());
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strArea.toLocal8Bit().constData());	
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strLength.toLocal8Bit().constData());	
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strWidth.toLocal8Bit().constData());
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strInnerDia.toLocal8Bit().constData());	
				set_color(m_lRegInfoID,"red");
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strAnisometry.toLocal8Bit().constData());
				set_color(m_lRegInfoID,"dark orchid");
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strAngle.toLocal8Bit().constData());	
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strMean.toLocal8Bit().constData());
				break;
			case EXCLUDE_CAUSE_HEIGHT://�߶�
				showExcludeInfo.strCause += tr("HEIGHT");
				set_color(m_lRegInfoID,"dark orchid");
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strCause.toLocal8Bit().constData());
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strArea.toLocal8Bit().constData());	
				set_color(m_lRegInfoID,"red");
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strLength.toLocal8Bit().constData());	
				set_color(m_lRegInfoID,"dark orchid");
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strWidth.toLocal8Bit().constData());
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strInnerDia.toLocal8Bit().constData());	
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strAnisometry.toLocal8Bit().constData());
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strAngle.toLocal8Bit().constData());	
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strMean.toLocal8Bit().constData());
				break;
			case EXCLUDE_CAUSE_GRAY://�Ҷ�
				showExcludeInfo.strCause += tr("GRAY");
				set_color(m_lRegInfoID,"dark orchid");
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strCause.toLocal8Bit().constData());
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strArea.toLocal8Bit().constData());	
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strLength.toLocal8Bit().constData());	
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strWidth.toLocal8Bit().constData());
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strInnerDia.toLocal8Bit().constData());	
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strAnisometry.toLocal8Bit().constData());
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strAngle.toLocal8Bit().constData());	
				set_color(m_lRegInfoID,"red");
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strMean.toLocal8Bit().constData());
				set_color(m_lRegInfoID,"dark orchid");
				break;
			case EXCLUDE_CAUSE_COMPACTNESS://���ն�
				showExcludeInfo.strCause += tr("COMPACTNESS");
				set_color(m_lRegInfoID,"red");
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strCause.toLocal8Bit().constData());
				set_color(m_lRegInfoID,"dark orchid");
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strArea.toLocal8Bit().constData());	
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strLength.toLocal8Bit().constData());	
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strWidth.toLocal8Bit().constData());
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strInnerDia.toLocal8Bit().constData());	
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strAnisometry.toLocal8Bit().constData());
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strAngle.toLocal8Bit().constData());	
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strMean.toLocal8Bit().constData());
				break;
			case EXCLUDE_CAUSE_WIDTH_AND_HEIGHT://���&�߶�
				showExcludeInfo.strCause += tr("WIDTH_AND_HEIGHT");
				set_color(m_lRegInfoID,"dark orchid");
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strCause.toLocal8Bit().constData());
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strArea.toLocal8Bit().constData());	
				set_color(m_lRegInfoID,"red");
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strLength.toLocal8Bit().constData());	
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strWidth.toLocal8Bit().constData());	
				set_color(m_lRegInfoID,"dark orchid");
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strInnerDia.toLocal8Bit().constData());	
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strAnisometry.toLocal8Bit().constData());
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strAngle.toLocal8Bit().constData());	
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strMean.toLocal8Bit().constData());
				break;
			case EXCLUDE_CAUSE_OPEN://������
				showExcludeInfo.strCause += tr("OPEN");
				set_color(m_lRegInfoID,"red");
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strCause.toLocal8Bit().constData());
				set_color(m_lRegInfoID,"dark orchid");
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strArea.toLocal8Bit().constData());	
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strLength.toLocal8Bit().constData());	
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strWidth.toLocal8Bit().constData());	
				set_color(m_lRegInfoID,"dark orchid");
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strInnerDia.toLocal8Bit().constData());	
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strAnisometry.toLocal8Bit().constData());
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strAngle.toLocal8Bit().constData());	
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strMean.toLocal8Bit().constData());
				break;
			case EXCLUDE_CAUSE_ARC://����
				showExcludeInfo.strCause += tr("ARC");
				set_color(m_lRegInfoID,"red");
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strCause.toLocal8Bit().constData());
				set_color(m_lRegInfoID,"dark orchid");
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strArea.toLocal8Bit().constData());	
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strLength.toLocal8Bit().constData());	
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strWidth.toLocal8Bit().constData());
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strInnerDia.toLocal8Bit().constData());	
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strAnisometry.toLocal8Bit().constData());
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strAngle.toLocal8Bit().constData());	
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strMean.toLocal8Bit().constData());
				break;
			case EXCLUDE_CAUSE_SHADOW://������Ӱ
				showExcludeInfo.strCause += tr("SHADOW");
				set_color(m_lRegInfoID,"red");
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strCause.toLocal8Bit().constData());
				set_color(m_lRegInfoID,"dark orchid");
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strArea.toLocal8Bit().constData());	
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strLength.toLocal8Bit().constData());	
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strWidth.toLocal8Bit().constData());
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strInnerDia.toLocal8Bit().constData());	
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strAnisometry.toLocal8Bit().constData());
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strAngle.toLocal8Bit().constData());	
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strMean.toLocal8Bit().constData());
				break;		
			case EXCLUDE_CAUSE_INRADIUS://�ڽ�Բ
				showExcludeInfo.strCause += tr("INRADIUS");
				set_color(m_lRegInfoID,"red");
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strCause.toLocal8Bit().constData());
				set_color(m_lRegInfoID,"dark orchid");
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strArea.toLocal8Bit().constData());	
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strLength.toLocal8Bit().constData());	
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strWidth.toLocal8Bit().constData());
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strInnerDia.toLocal8Bit().constData());	
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strAnisometry.toLocal8Bit().constData());
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strAngle.toLocal8Bit().constData());	
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strMean.toLocal8Bit().constData());
				break;
			case EXCLUDE_CAUSE_CIRCULARITY_AND_INRADIUS://Բ��&�ڽ�Բ
				showExcludeInfo.strCause += tr("CIRCULARITY_AND_INRADIUS");
				set_color(m_lRegInfoID,"red");
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strCause.toLocal8Bit().constData());
				set_color(m_lRegInfoID,"dark orchid");
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strArea.toLocal8Bit().constData());	
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strLength.toLocal8Bit().constData());	
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strWidth.toLocal8Bit().constData());
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strInnerDia.toLocal8Bit().constData());	
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strAnisometry.toLocal8Bit().constData());
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strAngle.toLocal8Bit().constData());	
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strMean.toLocal8Bit().constData());
				break;	
			case EXCLUDE_CAUSE_SIDEDISTANCE://�߾�
				showExcludeInfo.strCause += tr("SIDEDISTANCE");
				set_color(m_lRegInfoID,"red");
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strCause.toLocal8Bit().constData());
				set_color(m_lRegInfoID,"dark orchid");
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strArea.toLocal8Bit().constData());	
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strLength.toLocal8Bit().constData());	
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strWidth.toLocal8Bit().constData());
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strInnerDia.toLocal8Bit().constData());	
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strAnisometry.toLocal8Bit().constData());
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strAngle.toLocal8Bit().constData());	
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strMean.toLocal8Bit().constData());
				break;
			case EXCLUDE_CAUSE_BUBBLE://����
				showExcludeInfo.strCause += tr("BUBBLE");
				set_color(m_lRegInfoID,"red");
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strCause.toLocal8Bit().constData());
				set_color(m_lRegInfoID,"dark orchid");
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strArea.toLocal8Bit().constData());	
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strLength.toLocal8Bit().constData());	
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strWidth.toLocal8Bit().constData());
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strInnerDia.toLocal8Bit().constData());	
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strAnisometry.toLocal8Bit().constData());
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strAngle.toLocal8Bit().constData());	
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strMean.toLocal8Bit().constData());
				break;
			case EXCLUDE_CAUSE_MOULD_DIAMETER://ģ��ֱ��
				showExcludeInfo.strCause += tr("MOULD_DIAMETER");
				set_color(m_lRegInfoID,"red");
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strCause.toLocal8Bit().constData());
				set_color(m_lRegInfoID,"dark orchid");
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strArea.toLocal8Bit().constData());	
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				showExcludeInfo.strLength = tr("smallestRectangle1")+showExcludeInfo.strLength; //2017.8:��Ӿ��γ���
				write_string(m_lRegInfoID,showExcludeInfo.strLength.toLocal8Bit().constData());	
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				showExcludeInfo.strWidth = tr("smallestRectangle1")+showExcludeInfo.strWidth; //2017.8:��Ӿ��ο��
				write_string(m_lRegInfoID,showExcludeInfo.strWidth.toLocal8Bit().constData());
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strInnerDia.toLocal8Bit().constData());	
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strAnisometry.toLocal8Bit().constData());
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strAngle.toLocal8Bit().constData());	
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strMean.toLocal8Bit().constData());
				break;
			case EXCLUDE_CAUSE_GRAY_DIFFERENCE://�ҶȲ�
				showExcludeInfo.strCause += tr("GRAY_DIFFERENCE");
				set_color(m_lRegInfoID,"red");
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strCause.toLocal8Bit().constData());
				set_color(m_lRegInfoID,"dark orchid");
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strArea.toLocal8Bit().constData());	
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strLength.toLocal8Bit().constData());	
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strWidth.toLocal8Bit().constData());
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strInnerDia.toLocal8Bit().constData());	
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strAnisometry.toLocal8Bit().constData());
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strAngle.toLocal8Bit().constData());	
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strMean.toLocal8Bit().constData());
				break;
			default://����
				showExcludeInfo.strCause += tr("OTHER");
				set_color(m_lRegInfoID,"dark orchid");
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strCause.toLocal8Bit().constData());
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strArea.toLocal8Bit().constData());	
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strLength.toLocal8Bit().constData());	
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strWidth.toLocal8Bit().constData());
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strInnerDia.toLocal8Bit().constData());	
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strAnisometry.toLocal8Bit().constData());
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strAngle.toLocal8Bit().constData());	
				set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
				write_string(m_lRegInfoID,showExcludeInfo.strMean.toLocal8Bit().constData());
				break;
			}
		}	
	}
	catch(HException &e)
	{
		//Halcon�쳣		
		QString tempStr,strErr;
		tempStr=e.message;
		tempStr.remove(0,20);
		strErr = QString("abnormal:displayExcludeInfo,Display exclude defect info region")+ tempStr;//��ʾ�ų�ȱ����Ϣ��
		pChecker->writeErrDataRecord(strErr);
	}
	catch (...)
	{
		pChecker->writeErrDataRecord(QString("abnormal:displayExcludeInfo,Display exclude defect info region"));	//��ʾ�ų�ȱ����Ϣ��	
	}

	return true;
}
//*���ܣ���ʾ���Ƹ�������������ȡȱ��
void CDlgMainWindow::displayPickupDisReg(Hobject DisturbReg,int nMaskSize,int nEdge,QString strName,	
	bool bHoriStripe,int nHoriAng,int nHoriWidthL,int nHoriWidthH,float fHoriRabL,float fHoriRabH,float fHoriInRadiusL,float fHoriInRadiusH,
	bool bVertStripe,int nVertAng,int nVertWidthL,int nVertWidthH,float fVertRabL,float fVertRabH,float fVertInRadiusL,float fVertInRadiusH)
{
	QString strDis;
	disp_image(imgShow,m_lWindID);
	//�رմ�����Ϣ�Ի���
	if (m_lRegInfoID !=0)
	{
		close_window(m_lRegInfoID);
		m_lRegInfoID = 0;
	}

	gen_empty_obj(&pChecker->rtnInfo.regError);
	pChecker->rtnInfo.nType=GOOD_BOTTLE;
	pChecker->rtnInfo.strEx.clear();
	pChecker->rtnInfo.vExcludeInfo.clear();
	pChecker->m_vExcludeInfo.clear();
	//��ȡȱ��
	Hobject regCheck,regThresh,regStripe;
	Hobject imgReduce,imgMean;	
	Hlong nNum;
	nEdge = max(nEdge,5);
	gen_region_contour_xld(DisturbReg,&regCheck,"filled");
	clip_region(regCheck,&regCheck,0,0,pChecker->m_nHeight-1,pChecker->m_nWidth-1);
	select_shape(regCheck,&regCheck,"area","and",100,99999999);
	count_obj(regCheck,&nNum);
	if (nNum==0)
	{
		return;
	}

	reduce_domain(pChecker->m_ImageSrc,regCheck,&imgReduce);
	mean_image(imgReduce,&imgMean,nMaskSize,nMaskSize);
	dyn_threshold(imgReduce,imgMean,&regThresh,nEdge,"dark");
	//�ж�ȱ��
	Hobject regSel;
	int i;
	double Ra,Rb,Phi,InRadius;
	gen_empty_obj(&regStripe);
	connection(regThresh,&regThresh);
	count_obj(regThresh,&nNum);

	for (i=0;i<nNum;++i)
	{
		select_obj(regThresh,&regSel,i+1);
		elliptic_axis(regSel, &Ra, &Rb, &Phi);
		Rb = (Rb==0)?0.5:Rb;
		tuple_deg(Phi,&Phi);
		inner_circle(regSel,NULL,NULL,&InRadius);
		if (bHoriStripe)//ˮƽ����
		{
			if (fabs(Phi)<nHoriAng && 
				Rb*2>nHoriWidthL && Rb*2<nHoriWidthH &&
				Ra/Rb>fHoriRabL && Ra/Rb<fHoriRabH&&
				InRadius*2>fHoriInRadiusL&&InRadius*2<fHoriInRadiusH)
			{
				concat_obj(regStripe,regSel,&regStripe);
			}
		}
		if (bVertStripe)//��ֱ����
		{
			Phi=Phi<0?Phi+180.f:Phi;
			if ((0 == Rb) || fabs(90.f-Phi)<nVertAng &&
				Rb*2>nVertWidthL && Rb*2<nVertWidthH &&
				Ra/Rb>fVertRabL && Ra/Rb<fVertRabH&&
				InRadius*2>fVertInRadiusL&&InRadius*2<fVertInRadiusH)
			{
				concat_obj(regStripe,regSel,&regStripe);
			}
		}
	}
	count_obj(regStripe,&nNum);
	if (nNum>0)
	{
		ExcludeInfo eldInfo;
		copy_obj(regStripe,&eldInfo.regExclude,1,-1);
		eldInfo.nDefectCause = EXCLUDE_CAUSE_STRIPES;
		eldInfo.nDefectType = EXCLUDE_TYPE_DISTURB;
		eldInfo.strDetName = strName;
		eldInfo.bModify = true;
		pChecker->m_vExcludeInfo.push_back(eldInfo);
	}
	difference(regThresh,regStripe,&regThresh);
	select_shape(regThresh,&pChecker->rtnInfo.regError,"area","and",10,99999999);
	count_obj(pChecker->rtnInfo.regError,&nNum);
	if (nNum>0)
	{
		pChecker->rtnInfo.nType=ERROR_SPOT;	
	}
	//��ʾȱ��
	if (!bShowShape)
		return;
	set_color(m_lWindID,"gold");
	disp_obj(DisturbReg,m_lWindID);
	set_color(m_lWindID,"orange");
	if (pChecker->m_bExtExcludeDefect)
	{
		for (i = 0;i<pChecker->m_vExcludeInfo.count();++i)
		{	
			disp_obj(pChecker->m_vExcludeInfo.at(i).regExclude,m_lWindID);
		}
	}
	set_color(m_lWindID,"red");
	disp_obj(pChecker->rtnInfo.regError,m_lWindID);
}
void CDlgMainWindow::enableButtons(bool bFlag)
{
	// ��ť״̬
#ifdef DAHENGBLPKP_QT
	ui.pbtnImgOpen->setEnabled(bFlag);
	ui.pbtnImgSave->setEnabled(bFlag);
	ui.pbtnImgPre->setEnabled(bFlag&&sOpenLocalImg.bOpenImg);
	ui.pbtnImgNext->setEnabled(bFlag&&sOpenLocalImg.bOpenImg);
	ui.pbtnImgOriginal->setEnabled(bFlag);
	ui.pbtnImgPainted->setEnabled(bFlag);
	ui.pbtnRegReset->setEnabled(m_bDrawing);
	ui.pbtnImgMeasure->setEnabled(bFlag);
	ui.pbtnShowContinue->setEnabled(bFlag || pCheckerReal->m_bContinueShow);
	ui.pbtnShowStop->setEnabled(bFlag || pCheckerReal->m_bContinueShow);
	ui.combCamIdx->setEnabled(bFlag);
	ui.combLangIdx->setEnabled(bFlag);

	ui.pbtnAddItem->setEnabled(bFlag);
	ui.pbtnInsertItem->setEnabled(bFlag&&ui.processBox->bItemClicked);
	ui.pbtnDeleteItem->setEnabled(bFlag&&ui.processBox->bItemClicked);
	ui.pbtnRenameItem->setEnabled(bFlag&&ui.processBox->bItemClicked);
	ui.pbtnEnableItem->setEnabled(bFlag&&ui.processBox->bItemClicked);
	ui.pbtnCopyItem->setEnabled(bFlag&&ui.processBox->bItemClicked);
	ui.pbtnPasteItem->setEnabled(bFlag);  

	ui.paramFrame->setEnabled(bFlag);
#else
	ui.openImgAction->setEnabled(bFlag);
	ui.saveImgAction->setEnabled(bFlag);
	ui.prevImgAction->setEnabled(bFlag&&sOpenLocalImg.bOpenImg);
	ui.nextImgAction->setEnabled(bFlag&&sOpenLocalImg.bOpenImg);
	ui.oriImgAction->setEnabled(bFlag);
	ui.drawImgAction->setEnabled(bFlag);
	ui.resetShapeAction->setEnabled(m_bDrawing);
	ui.measureImgAction->setEnabled(bFlag);
	ui.continueShowAction->setEnabled(bFlag || pCheckerReal->m_bContinueShow);
	ui.stopAtErrorShowAction->setEnabled(bFlag || pCheckerReal->m_bContinueShow);
	comboCamIndex->setEnabled(bFlag);
	comboLanguage->setEnabled(bFlag);
#endif

	ui.btnTest->setEnabled(bFlag);
	ui.btnSaveModel->setEnabled(bFlag);
	ui.btnExportModel->setEnabled(bFlag); 
	ui.btnImportModel->setEnabled(bFlag);
	ui.btnCopyModel->setEnabled(bFlag);

	//�������
	ui.processBox->setEnabled(bFlag);
}
//*���ܣ�ģ���Ƿ�ı�
bool CDlgMainWindow::ModeChanged()
{

	bool bModelChanged=false;
	int i;
	if (ui.processBox->bAllItemsChange || bReadNewModel)
	{
		bModelChanged = true;
	}
	for (i=0;i<ui.processBox->vItemLabels.size();++i)
	{
		if (ui.processBox->vItemLabels[i]->bParaChanged || ui.processBox->vItemLabels[i]->bShapeChanged)
		{
			bModelChanged = true;
			break;
		}
	}
	return bModelChanged;
}
//*���ܣ���ͼ�رնԻ���
bool CDlgMainWindow::tryClose()
{
	//int i;
	//QVector<MyLabelItem *> vItemLabels = ui.processBox->vItemLabels;
	if (m_bDrawing)
	{
		strCloseWindow = tr("Can not close the window because it's drawing,\n"												
			"please right click to exit the drawing state and then close the window .");
		QMessageBox::information(this,tr("Note"),strCloseWindow);		
		return false;
	}
	if (bMeasure)
	{
		strCloseWindow = tr("Can not close the window because it's measuring,\n"
			"please complete the measurement and then close the window .");
		QMessageBox::information(this,tr("Note"),strCloseWindow);		
		return false;
	}
	if (pCheckerReal->m_bContinueShow)
	{
		strCloseWindow = tr("Can not close the window because it's displaying continuously,\n"
			"please cancel continuous display and then close the window .");
		QMessageBox::information(this,tr("Note"),strCloseWindow);		
		return false;
	}


	if (ModeChanged())
	{
		strCloseWindow = tr("Model has been modified and not saved, Are you sure to continue to exit?");
		QMessageBox::StandardButton rb = QMessageBox::question(this, tr("Note"), strCloseWindow,
			QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes); 
		if(rb == QMessageBox::No) 
		{ 
			return false; 
		}
		else
		{
			//nanjc 2013.9.5 �л����ʱ��ģ�����޸���ʾһ��
			ui.processBox->bAllItemsChange = false;
			bReadNewModel = false;
		}
	}
	return true;
}
//*���ܣ�����ر��¼�
void CDlgMainWindow::closeEvent(QCloseEvent *event)
{			
	if (!tryClose())
	{
		event->ignore();
		return;
	}
	if (pItemDlg!=NULL)
		pItemDlg->close();//�رռ����Ի���
	//2013.10.8 nanjc �����ڴ�й© +�ͷ�
	if (pChecker != NULL)
	{
		delete pChecker;
		pChecker = NULL;
	}
	delete [] sAlgCInp.sImgLocInfo.sXldPoint.nRowsAry;
	delete [] sAlgCInp.sImgLocInfo.sXldPoint.nColsAry;
	//�ͷŷ����ļ�
	if (translator!=NULL)
	{
		qApp->removeTranslator(translator);
		delete translator;
		translator = NULL;
	}
	event->accept();
}
//*����: �����Ի�������ƶ�
void CDlgMainWindow::moveEvent(QMoveEvent *event)
{
#ifndef DAHENGBLPKP_QT
	if (pItemDlg!=NULL)
		pItemDlg->move(QPoint(width()+10,0)+pos());
#endif
}
//*����: ��������¼�����Ҫ����ͼ������
void CDlgMainWindow::wheelEvent(QWheelEvent *event)
{
	Hlong row,col,width,height;
	if (pCheckerReal->m_bContinueShow)
	{
		event->ignore();
		return;
	}
	get_window_extents(m_lWindID,&row,&col,&width,&height);
	QRect imgRect = QRect(col,row,width,height);
	if (!imgRect.contains(event->globalPos()) || m_bDrawing || bMeasure)
	{
		event->ignore();
		return;
	}
	Hlong mRow,mCol;
	static int nStep;	
	nStep=event->delta()>0?nStep+=2:nStep-=2;
	if (nStep<0)
	{
		nStep=0;
		return;
	}
	if (nStep>40)
	{
		nStep=40;//���25��
		return;
	}
	//Halcon10.0 ����뿪ͼ�񴰿ں��쳣
	try
	{
		get_mposition(m_lWindID,&mRow,&mCol,NULL);
	}
	catch (...)
	{
		event->ignore();
		return;
	}	
	QRect viewRect = QRect(mCol-nImgWidth*(1-nStep/50.f)/2,mRow-nImgHeight*(1-nStep/50.f)/2,nImgWidth*(1-nStep/50.f),nImgHeight*(1-nStep/50.f));
	if (viewRect.top()<0)
	{		
		viewRect.setBottom(viewRect.bottom()-viewRect.top());
		viewRect.setTop(0);
	}
	if (viewRect.bottom()>nImgHeight-1)
	{
		viewRect.setTop(viewRect.top()-(viewRect.bottom()-nImgHeight+1));
		viewRect.setBottom(nImgHeight-1);
	}
	if (viewRect.left()<0)
	{
		viewRect.setRight(viewRect.right()-viewRect.left());
		viewRect.setLeft(0);
	}
	if (viewRect.right()>nImgWidth-1)
	{
		viewRect.setLeft(viewRect.left()-(viewRect.right()-nImgWidth+1));
		viewRect.setRight(nImgWidth-1);
	}
	set_part(m_lWindID,viewRect.top(),viewRect.left(),viewRect.bottom(),viewRect.right());
	displayObject();
	event->accept();
}
void CDlgMainWindow::mouseMoveEvent(QMouseEvent *event)
{
	Hlong row,col,width,height;
	Hlong mRow,mCol,mButton;
	Hlong row1,col1,row2,col2;
	int i,j;
	Hlong nNum,isInside;
	Hobject objSel;					

	//������ʾʱ����ͼʱ������ʱ������
	if (pCheckerReal->m_bContinueShow || m_bDrawing || bMeasure)
	{
		event->ignore();
		return;
	}
	//����ͼ�������ڲ�����
	get_window_extents(m_lWindID,&row,&col,&width,&height);
	QRect imgRect = QRect(col,row,width,height);
	if (!imgRect.contains(event->globalPos()))
	{
		statusBar()->clearMessage();
		event->ignore();
		return;
	}

	double gray;
	//Halcon10.0 ����뿪ͼ�񴰿ں��쳣
	try
	{
		get_mposition(m_lWindID,&mRow,&mCol,&mButton);
	}
	catch (...)
	{
		event->ignore();
		return;
	}
	if (mButton==0)//�ް���
	{
		//��ʾ������Ϣ
		get_grayval(imgShow,mRow,mCol,&gray);	
		statusBar()->showMessage(tr("Coordinate:%1,%2 GrayValue:%3").arg(mRow).arg(mCol).arg(gray));
		//ȱ�ݱ�ɫ��ʾ
		if (pChecker->rtnInfo.nType>0 && bShowShape)
		{
			count_obj(pChecker->rtnInfo.regError,&nNum);
			for (i=0;i<nNum;++i)
			{
				select_obj(pChecker->rtnInfo.regError,&objSel,i+1);
				test_region_point(objSel,mRow,mCol,&isInside);
				if (isInside)
				{
					set_color(m_lWindID,"slate blue");
					disp_obj(objSel,m_lWindID);					
					break;
				}
				else
				{
					set_color(m_lWindID,"red");
					disp_obj(objSel,m_lWindID);
				}
			}
		}
		//�ų�ȱ�ݱ�ɫ��ʾ
		if (pChecker->m_bExtExcludeDefect && bShowShape)
		{
			for (i=0;i<pChecker->m_vExcludeInfo.count();++i)
			{
				count_obj(pChecker->m_vExcludeInfo.at(i).regExclude,&nNum);
				for (j=0;j<nNum;++j)
				{
					select_obj(pChecker->m_vExcludeInfo.at(i).regExclude,&objSel,j+1);
					test_region_point(objSel,mRow,mCol,&isInside);
					if (isInside)
					{
						set_color(m_lWindID,"spring green");
						disp_obj(objSel,m_lWindID);					
						break;
					}
					else
					{
						set_color(m_lWindID,"orange");
						disp_obj(objSel,m_lWindID);
					}
				}
			}
			Hobject objSel;					
			count_obj(pChecker->rtnInfo.regError,&nNum);
		}
	}	
	else if (mButton==1 && !m_bDrawing)//������϶�
	{
		get_part(m_lWindID,&row1,&col1,&row2,&col2);
		//2013.9.5 nanjc ͼ��������ʱ������Ӧ
		if (col2-col1+1>=nImgWidth && row2-row1+1>=nImgHeight)
		{
			event->ignore();
			return;
		}		
		ui.imgFrame->setCursor(Qt::SizeAllCursor);
		set_mshape(m_lWindID,"Size All");

		if (lPressRow!=-1 && lPressCol!=-1)//������갴��ȱ����ϸ��Ϣ����ʱ�ƶ������Ͻ�
		{
			if (abs(lPressRow-mRow)>30 || abs(lPressCol-mCol)>30)
			{
				lPressRow = mRow;//�����ƶ�����
				lPressCol = mCol;
			}
			int test1 = lPressRow - mRow;
			int test2 = lPressCol - mCol;
			row1+=lPressRow-mRow;
			row2+=lPressRow-mRow;
			col1+=lPressCol-mCol;
			col2+=lPressCol-mCol;
			if (row1<0)
			{
				row2-=row1;
				row1=0;
			}
			if (col1<0)
			{
				col2-=col1;
				col1=0;
			}
			if (row2>nImgHeight-1)
			{
				row1-=(row2-nImgHeight+1);
				row2=nImgHeight-1;
			}
			if (col2>nImgWidth-1)
			{
				col1-=(col2-nImgWidth+1);
				col2=nImgWidth-1;
			}		
			set_part(m_lWindID,row1,col1,row2,col2);
			displayObject();
		}		
	}
}
void CDlgMainWindow::mouseReleaseEvent(QMouseEvent *event)
{
	//�϶�ͼ������ͷ�
	if (ui.imgFrame->cursor().shape()==Qt::SizeAllCursor)
	{
		ui.imgFrame->setCursor(Qt::ArrowCursor);
		set_mshape(m_lWindID,"default");
	}	
	//�رղ���
	if (bMeasure && bDistDone)
	{
		bMeasure = false;
		bDistDone = false;		
		bShowShape = true;
		displayObject();
		ui.drawImgAction->setChecked(true);
		ui.measureImgAction->setChecked(false);
		enableButtons(true);
	}
}
void CDlgMainWindow::mousePressEvent(QMouseEvent *event)
{
	Hlong row,col,width,height;

	////2017.7������趨����ʱ������Ҽ���ͼ�񴰿���ȷ���쳣����
	//if (event->button()==Qt::RightButton && m_bDrawing)
	//{
	//	get_window_extents(m_lWindID,&row,&col,&width,&height);
	//	QRect imgRect = QRect(col,row,width,height);
	//	if (!imgRect.contains(event->globalPos()))
	//	{
	//		SetCursorPos(col+width/2,row+height/2);
	//		return ;
	//	}
	//}

	if (event->button()!=Qt::LeftButton)
		return;	

	if (pCheckerReal->m_bContinueShow || m_bDrawing || bMeasure)
	{
		event->ignore();
		return;
	}
	get_window_extents(m_lWindID,&row,&col,&width,&height);
	QRect imgRect = QRect(col,row,width,height);
	if (!imgRect.contains(event->globalPos()))
	{
		statusBar()->clearMessage();
		event->ignore();
		return;
	}
	//��ȡ��ǰ���꣬����ƽ��
	//Halcon10.0 ����뿪ͼ�񴰿ں��쳣
	try
	{
		get_mposition(m_lWindID,&lPressRow,&lPressCol,NULL);
	}
	catch (...)
	{
		event->ignore();
		return;
	}

	bool bDisInfo = false;

	//��ʾȱ����ϸ��Ϣ
	if (m_lRegInfoID == 0)
	{		
		//���㴰�����Ͻ�����
		//int nWndScale = comboWndScale->currentIndex()+1;				
		Hlong nRow = event->y()-ui.imgFrame->mapTo(this,ui.imgFrame->rect().topLeft()).y();//lPressRow*(nWndScale/10.f);
		Hlong nCol = event->x()-ui.imgFrame->mapTo(this,ui.imgFrame->rect().topLeft()).x()+3;//lPressCol*(nWndScale/10.f);
		Hlong lWid=120;  //2017.3---110->120
		Hlong lHei=120;	
		//��ֹ���ڳ���ͼ��󴰿�
		Hlong maxRow = (pChecker->m_nHeight)*fWndScale/*(nWndScale/10.f)*/-lHei-10;
		Hlong maxCol = (pChecker->m_nWidth)*fWndScale/*(nWndScale/10.f)*/-lWid-10;
		nRow = nRow>maxRow?maxRow:nRow;
		nCol = nCol>maxCol?maxCol:nCol;	
		//ȱ������
		if (pChecker->rtnInfo.nType>0)
		{
			Hlong nNum,isInside;
			Hobject objError,objSel;
			int i;
			select_shape(pChecker->rtnInfo.regError,&objError,"area","and",1,99999999);//�������Ϊ0�����������
			count_obj(objError,&nNum);			
			for (i=0;i<nNum;++i)
			{
				//�ж��Ƿ���ȱ���ϰ���
				select_obj(objError,&objSel,i+1);
				test_region_point(objSel,lPressRow,lPressCol,&isInside);
				if (isInside)
				{
					//����ȱ����Ϣ
					Hlong nArea;
					double dArea;
					double dRa,dRb,dRab,dPhi,dMeanGray,dInnerDia,dCircularity;
					Hobject objSelClo;
					bDisInfo = true;
					area_center(objSel,&nArea,NULL,NULL);
					intensity(objSel,imgShow,&dMeanGray,NULL);
					inner_circle(objSel, NULL, NULL, &dInnerDia);
					circularity(objSel,&dCircularity); //2017.4

					//������仯ȱ�ݣ�����ӡ���ڱ��Ρ��⻷ȱ�ڣ�����Ƥ���ݵ�������
					Hobject objLOF,objLOFcon,regSkeleton,XldSel;
					double oriRow = pChecker->currentOri.Row;
					double oriCol = pChecker->currentOri.Col;
					Hlong row1,col1,row2,col2,num;
					switch(pChecker->rtnInfo.nType)
					{
					case ERROR_LOF:
						polar_trans_region(objSel,&objLOF,oriRow,oriCol,2*PI,0,0,pChecker->m_nHeight,
							pChecker->m_nWidth,pChecker->m_nHeight,"nearest_neighbor");	
						//2017.3.21---ȱ��������0��ʱ��������任�󱻲������,�������޸�
						connection(objLOF, &objLOFcon);
						count_obj(objLOFcon, &num);
						if (num > 1)
						{
							select_shape_std(objLOFcon,&objLOF,"max_area",70);
						}
						smallest_rectangle1(objLOF,&row1,&col1,&row2,&col2);
						dRa = row2-row1;
						dRb = col2-col1;
						dRb = dRb==0?1:dRb;
						dRab = dRa/(dRb);
						dPhi = 0;
						break;
					case ERROR_BREACH:
						polar_trans_region(objSel,&objLOF,oriRow,oriCol,2*PI,0,0,pChecker->m_nHeight,
							pChecker->m_nWidth,pChecker->m_nHeight,"nearest_neighbor");		
						smallest_rectangle1(objLOF,&row1,&col1,&row2,&col2);
						dRa = row2-row1;
						dRb = col2-col1;
						dRb = dRb==0?1:dRb;
						dRab = dRa/(dRb);
						dPhi = 0;
						break;
					case ERROR_BROKENRING://����
						contlength(objSel,&dRa);
						smallest_rectangle1(objSel,&row1,&col1,&row2,&col2);
						dRa /= 2;
						dRb = col2-col1;
						dRb = dRb==0?1:dRb;
						dRab = dRa/(dRb);
						dPhi = 0;
						break;
					case ERROR_MOUTHDEFORM:
						polar_trans_region(objSel,&objLOF,oriRow,oriCol,2*PI,0,0,pChecker->m_nHeight,
							pChecker->m_nWidth,pChecker->m_nHeight,"nearest_neighbor");		
						smallest_rectangle1(objLOF,&row1,&col1,&row2,&col2);
						dRa = row2-row1;
						dRb = col2-col1;
						dRb = dRb==0?1:dRb;
						dRab = dRa/(dRb);
						dPhi = 0;
						break;
					case ERROR_BOTTOM_STRIPE:
						//2018.3-�������⣺ȱ����ʾ���������Կ�߲�һ��
						polar_trans_region(objSel,&objLOF,oriRow,oriCol,2*PI,0,0,pChecker->m_nHeight,
							pChecker->m_nWidth,pChecker->m_nHeight,"nearest_neighbor");	
						smallest_rectangle1(objLOF,&row1,&col1,&row2,&col2);
						dRa = row2-row1;
						dRb = col2-col1;
						dRb = dRb==0?1:dRb;
						eccentricity(objLOF,&dRab,NULL,NULL);
						elliptic_axis(objLOF,NULL,NULL,&dPhi);
						tuple_deg(dPhi,&dPhi);
						//dPhi=dPhi<0?dPhi+180.f:dPhi;
						dPhi = fabs(dPhi);
						break;
					case ERROR_THIN_BUBBLE:  //region->xld,��ʾxld����ֵ
						skeleton(objSel, &regSkeleton);
						gen_contours_skeleton_xld(regSkeleton, &XldSel, 1, "filter");
						area_center_xld(XldSel, &dArea, NULL, NULL, NULL);
						nArea = Hlong(dArea);
						length_xld(XldSel, &dRa);						
						eccentricity_xld(XldSel, &dRab, NULL, NULL);
						smallest_rectangle2_xld(XldSel, NULL, NULL, &dPhi, NULL, NULL);
						tuple_deg(dPhi,&dPhi);
						circularity_xld(XldSel, &dCircularity);
						dRb = 0;         //�޲ο������ֵ��Ϊ0
						dInnerDia = 0;
						dMeanGray = 0;
						break;
					default:
						elliptic_axis(objSel,&dRa,&dRb,&dPhi);
						dRb = (dRb==0)?0.5:dRb;
						dRa*=2,dRb*=2,dRab=dRa/dRb;
						tuple_deg(dPhi,&dPhi);
						break;
					}				

					//��������				
					set_window_attr("border_width",1);
					set_window_attr("background_color","tan");
					open_window(nRow,nCol,lWid, lHei, m_lWindID, "visible", "", &m_lRegInfoID);	

					//��ʾ��Ϣ
					int nPosRow = 0;
					int nGapWid = (nMaxCamareWidth*0.95)/9.0;//�м��
					set_font(m_lRegInfoID,"-΢���ź�-15-*-*-*-*-*-ANSI_CHARSET-");//-FontName-Height-Width-Italic-Underlined-Strikeout-Bold-CharSet-
					set_color(m_lRegInfoID,"dark orchid");
					set_tposition(m_lRegInfoID,nPosRow,10);
					QString strDis;
					strDis=tr("Index:     %1").arg(i+1);
					write_string(m_lRegInfoID,strDis.toLocal8Bit().constData());
					set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
					strDis=tr("Area:      %1").arg(nArea);
					write_string(m_lRegInfoID,strDis.toLocal8Bit().constData());
					set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
					strDis=tr("Length:    %1").arg(QString::number(dRa,'f',1));
					write_string(m_lRegInfoID,strDis.toLocal8Bit().constData());
					set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
					strDis=tr("Width:     %1").arg(QString::number(dRb,'f',1));
					write_string(m_lRegInfoID,strDis.toLocal8Bit().constData());
					set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
					strDis=tr("InnerDia: %1").arg(QString::number(dInnerDia*2,'f',1));
					write_string(m_lRegInfoID,strDis.toLocal8Bit().constData());
					set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
					strDis=tr("Anisometry: %1").arg(QString::number(dRab,'f',1));
					write_string(m_lRegInfoID,strDis.toLocal8Bit().constData());
					set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
					strDis=tr("Angle:     %1").arg(QString::number(dPhi,'f',1));
					write_string(m_lRegInfoID,strDis.toLocal8Bit().constData());
					set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
					strDis=tr("Mean:      %1").arg(QString::number(dMeanGray,'f',0));
					write_string(m_lRegInfoID,strDis.toLocal8Bit().constData());
					set_tposition(m_lRegInfoID,nPosRow+=nGapWid,10);
					strDis=tr("Circularity: %1").arg(QString::number(dCircularity,'f',2));
					write_string(m_lRegInfoID,strDis.toLocal8Bit().constData());	
					break;
				}
			}
		}		
		//�ų�����
		/*bDisInfo = */displayExcludeInfo(pChecker,nRow,nCol);
	}
	else if (m_lRegInfoID !=0)
	{
		close_window(m_lRegInfoID);
		m_lRegInfoID = 0;
		bDisInfo = true;
	}
	if (!bDisInfo)
	{
		//ѡ����Ҫ���ڵļ������
		judgeObjStatus(lPressRow,lPressCol);
	}
}
//*���ܣ���ͼ�δ����л���ͼ��
bool CDlgMainWindow::adjustShape(QDialog *dlg,Hobject &oShape,int nType,bool bReset/*=false*/)
{	
	//��ʾ����
	clear_window(m_lWindID);
	//set_window_extents(m_lWindID,0,0,ui.imgFrame->width(),ui.imgFrame->height());
	try
	{
		//�ؼ�״̬
		m_bDrawing = true;
		dlg->setEnabled(false);
		//2015.3.31 QTϵͳ�������ʱ����������ť������
		enableButtons(false);
		ui.resetShapeAction->setEnabled(true);
		//��ʾͼ�񣬱�����״����
		disp_obj(imgShow,m_lWindID);
		//��������
		ui.imgFrame->setCursor(Qt::CrossCursor);
		set_mshape(m_lWindID,"crosshair");
		set_line_width(m_lWindID,3);
		set_color(m_lWindID,"green");
		//����
		Hobject oShapeBackup;
		copy_obj(oShape,&oShapeBackup,1,-1);
		//��ͼ
		double row,col,radius;
		double row1,col1,row2,col2;
		HTuple Row1,Col1,Row2,Col2,Radius;
		HTuple tpRow,tpCol;
		Hlong nNum;
		try
		{
			switch(nType)
			{
			case DRAW_LINE:
				{
					HTuple row,col;
					get_region_points(oShape,&row,&col);
					nNum = row.Num();
					if (nNum<2 || bReset)
					{
						row1 = 30,row2 = 30,col1 = 20,col2 = 200;
					} 
					else
					{
						if (col[0].D()>col[nNum-1].I())
						{
							row = row.Inverse();
							col = col.Sort();
						}
						row1 = row[0].I();
						col1 = col[0].I();
						row2 = row[nNum-1].I();
						col2 = col[nNum-1].I();
					}
					draw_line_mod(m_lWindID,row1,col1,row2,col2,&Row1,&Col1,&Row2,&Col2);
					if (Row1.Num()>0)
					{
						row1 = Row1[0].I();
						col1 = Col1[0].I();
						row2 = Row2[0].I();
						col2 = Col2[0].I();
					}
					gen_region_line(&oShape,row1,col1,row2,col2);
				}
				break;
			case DRAW_RECTANGLE:
				{
					count_obj(oShape,&nNum);
					if (nNum == 0 || bReset)
					{
						//gen_rectangle1(&oShape,10,10,100,100);
						gen_rectangle2_contour_xld(&oShape,55,55,0,45,45);
					}
					smallest_rectangle1_xld(oShape,&row1,&col1,&row2,&col2);
					draw_rectangle1_mod(m_lWindID,row1,col1,row2,col2,&Row1,&Col1,&Row2,&Col2);
					if (Row1.Num()>0)
					{
						row1 = Row1[0].I();
						col1 = Col1[0].I();
						row2 = Row2[0].I();
						col2 = Col2[0].I();
					}
					//gen_rectangle1(&oShape,row1,col1,row2,col2);
					gen_rectangle2_contour_xld(&oShape,(row1+row2)/2,(col1+col2)/2,0,(col2-col1)/2,(row2-row1)/2);
				}
				break;
			case DRAW_CIRCLE:
				{
					count_obj(oShape,&nNum);
					if (nNum == 0 || bReset)
					{
						gen_circle(&oShape,100,100,50);
					}
					smallest_circle(oShape,&row,&col,&radius);
					draw_circle_mod(m_lWindID,row,col,radius,&Row1,&Col1,&Radius);
					if (Row1.Num()>0)
					{
						row = Row1[0].D();
						col = Col1[0].D();
						radius = Radius[0].D();
					}
					gen_circle(&oShape,row,col,radius);
				}
				break;
			case DRAW_POLYGON:
				{					
 					Hobject oTemp;
					copy_obj(oShape,&oTemp,1,-1);
					count_obj(oShape,&nNum);
					if (nNum == 0 || bReset)
					{
						gen_contour_polygon_xld(&oShape,
							HTuple(100).Concat(57).Concat(57).Concat(100).Concat(143).Concat(143).Concat(100),
							HTuple(50).Concat(75).Concat(125).Concat(150).Concat(125).Concat(75).Concat(50));
					}	
					//2017.6---�ڴ�����������Ҽ�ȷ�����ʱ��halcon�쳣
					ui.pbtnRegReset->setEnabled(false);
					Hlong winRow,winCol,winWidth,winHeight;
					get_window_extents(m_lWindID,&winRow,&winCol,&winWidth,&winHeight);
					RECT rect;
					rect.top = winRow;
					rect.left = winCol;
					rect.bottom = winRow+winHeight-1;
					rect.right = winCol+winWidth-1;					
					ClipCursor(&rect); 
					draw_xld_mod(oShape,&oShape,m_lWindID,"true","true","true","true","true");
					ClipCursor(NULL);
					get_contour_xld(oShape,&tpRow,&tpCol);
					if (tpRow.Num()<3)
					{
						copy_obj(oTemp,&oShape,1,-1);
					}
				}
				break;
			case DRAW_TRIBASEXLD:
				{					
 					Hobject oTemp;
					copy_obj(oShape,&oTemp,1,-1);
					count_obj(oShape,&nNum);
					if (nNum == 0|| bReset)//resnet
					{
						gen_contour_polygon_xld(&oShape,HTuple(0).Concat(202).Concat(488).Concat(478).Concat(378).Concat(246).Concat(150).Concat(0),
							HTuple(186).Concat(0).Concat(180).Concat(334).Concat(452).Concat(498).Concat(502).Concat(186));
							/*HTuple(0).Concat(194).Concat(630).Concat(209).Concat(0),
							HTuple(182).Concat(0).Concat(256).Concat(630).Concat(182));*/
					}
					
					//2018.8--- 
					ui.pbtnRegReset->setEnabled(false);
					Hlong winRow,winCol,winWidth,winHeight;
					get_window_extents(m_lWindID,&winRow,&winCol,&winWidth,&winHeight);
					RECT rect;
					rect.top = winRow;
					rect.left = winCol;
					rect.bottom = winRow+winHeight-1;
					rect.right = winCol+winWidth-1;					
					ClipCursor(&rect); 
					draw_xld_mod(oShape,&oShape,m_lWindID,"true","true","true","true","true");
					ClipCursor(NULL);
					get_contour_xld(oShape,&tpRow,&tpCol);
					if (tpRow.Num()<3)
					{
						copy_obj(oTemp,&oShape,1,-1);
					}
				}
				break;
			case DRAW_BOTTLEXLD:
				{
					Hobject oTemp;
					copy_obj(oShape,&oTemp,1,-1);
					count_obj(oShape,&nNum);
					if (nNum == 0)
					{
						break;
					}
					if (bReset)
					{
						copy_obj(pChecker->m_normalbotXld,&oShape,1,-1);				
					}
					//2017.6---�ڴ�����������Ҽ�ȷ�����ʱ��halcon�쳣
					ui.pbtnRegReset->setEnabled(false);
					Hlong winRow,winCol,winWidth,winHeight;
					get_window_extents(m_lWindID,&winRow,&winCol,&winWidth,&winHeight);
					RECT rect;
					rect.top = winRow;
					rect.left = winCol;
					rect.bottom = winRow+winHeight-1;
					rect.right = winCol+winWidth-1;					
					ClipCursor(&rect); 
					draw_xld_mod(oShape,&oShape,m_lWindID,"true","true","false","false","false");
					ClipCursor(NULL);					
					get_contour_xld(oShape,&tpRow,&tpCol);
					if (tpRow.Num()<3)
					{
						copy_obj(oTemp,&oShape,1,-1);
					}
				}
				break;
			default:
				break;
			}
		}
		catch(HException &e)
		{
			//Halcon�쳣		
			QString tempStr,strErr;
			tempStr=e.message;
			tempStr.remove(0,20);
			strErr = QString("abnormal:adjustShape,Plot type:%1,").arg(nType)+ tempStr;//��ͼ����
			pChecker->writeErrDataRecord(strErr);
		}
		catch (...)
		{
			pChecker->writeErrDataRecord(QString("abnormal:adjustShape,Plot type:%1").arg(nType));	//��ͼ����	
		}

		//�ж��Ƿ�����
		if (bResetFlag)
		{
			bResetFlag = false;
			adjustShape(dlg,oShape,nType,true);		
			return true;
		}			
		//��������
		set_line_width(m_lWindID,1);
		ui.imgFrame->setCursor(Qt::ArrowCursor);
		set_mshape(m_lWindID,"default");	
		//�ؼ�״̬
		m_bDrawing = false;	
		dlg->setEnabled(true);
		//2015.3.31 QTϵͳ�������ʱ����������ť������
		enableButtons(true);
		ui.resetShapeAction->setEnabled(false);

		//�������״�ı��ʶ��Ϊ��
		((MyLabelItem *)pItemLabel)->bShapeChanged = true;
		//ģ��ԭ�����Ϊ��ǰ��ԭ�㣡
		pChecker->modelOri = pChecker->currentOri;
	}
	catch(HException &e)
	{
		//Halcon�쳣		
		QString tempStr,strErr;
		tempStr=e.message;
		tempStr.remove(0,20);
		strErr = QString("abnormal:adjustShape---,Plot type:%1,").arg(nType)+ tempStr;//��ͼ����
		pChecker->writeErrDataRecord(strErr);
	}
	catch (...)
	{
		pChecker->writeErrDataRecord(QString("abnormal:adjustShape---,Plot type:%1").arg(nType));//��ͼ����		
	}
	return true;
}
void CDlgMainWindow::openImg()
{
	Hobject hImg;
	Hlong nWidth,nHeight,nChannel;
	QString strError;
	HTuple strBmpNames;
	QString dirPath,fileName;
	uint i;	
	Hlong j;

	////��¼������־
	//pChecker->writeAlgOperationRecord(QString("CDlgMainWindow::openImg,��ͼ��"));

	//���ļ�ѡ��Ի���
	QString fullPath = QFileDialog::getOpenFileName(this, tr("OpenFile"), ".", tr("ImageFile(*.bmp)")); 
	if(fullPath.length() == 0) 
	{
		return;
	}		
	read_image(&hImg,fullPath.toLocal8Bit().constData());	
	//�ж�ͼ�����
	get_image_pointer1(hImg,NULL,NULL,&nWidth,&nHeight);
	count_channels(hImg,&nChannel);
	if (abs(nWidth - nImgWidth)>1 || abs(nHeight - nImgHeight)>1 )
	{
		strError = tr("Size of the image does not match");
	}
	else if (nChannel != nImgChannel)
	{
		strError= tr("Channel of the image does not match");
	}
	if (!strError.isEmpty())
	{
		QMessageBox::critical(this,tr("Error"),tr("Fail to open image!\nCause��")+strError);
		return;
	}	
	//��д���Ա���ͼ����Ϣ�ṹ��	
	sOpenLocalImg.vAllNames.clear();
	dirPath = fullPath.left(fullPath.lastIndexOf(tr("/")));
	fileName= fullPath.right(fullPath.length()-fullPath.lastIndexOf(tr("/"))-1);
	list_files(dirPath.toLocal8Bit().constData(),HTuple("files"),&strBmpNames);//�ļ�������������
	for (j=0;j<strBmpNames.Num();++j)
	{
		QString eachFileName = QString::fromLocal8Bit(strBmpNames[j].S());	
		if (eachFileName.right(4)!=".bmp" && eachFileName.right(4)!=".BMP")
		{
			continue;
		}
		eachFileName.replace(tr("\\"),tr("/"));  //�滻��б��Ϊ��б��
		sOpenLocalImg.vAllNames.push_back(eachFileName);
	}	
	sOpenLocalImg.bOpenImg = true;
	for (i=0;i<sOpenLocalImg.vAllNames.size();i++)
	{
		if (fullPath==sOpenLocalImg.vAllNames[i])
		{
			sOpenLocalImg.nCurIndex = i;
			break;
		}
	}
	//��ʾͼ��
	copy_obj(hImg,&imgShow,1,-1);
	disp_image(hImg,m_lWindID);	
	set_color(m_lWindID,"red");
	set_tposition(m_lWindID, 10, 20);
	write_string(m_lWindID, HTuple(fileName.toLocal8Bit().constData()));	
	//������һ�š���һ�Ű�ť״̬
	enableButtons(true);
}
void CDlgMainWindow::saveImg()
{
	////��¼������־
	//pChecker->writeAlgOperationRecord(QString("CDlgMainWindow::saveImg,����ͼ��"));

	//���ļ�ѡ��Ի���
	QString fullPath = QFileDialog::getSaveFileName(this, tr("SaveFile"), ".", tr("ImageFile(*.bmp)")); 
	if(fullPath.length() == 0) 
	{
		return;
	}	
	write_image(imgShow, "bmp", 0, fullPath.toLocal8Bit().constData());
}
void CDlgMainWindow::prevImg()
{
	Hobject hImg;
	Hlong nWidth,nHeight,nChannel;
	QString strError;	
	if (sOpenLocalImg.nCurIndex == 0)
	{
		QMessageBox::information(this,tr("Note"),tr("Already is the first"));
		return;
	}
	sOpenLocalImg.nCurIndex--;
	QString filePath = sOpenLocalImg.vAllNames[sOpenLocalImg.nCurIndex];
	read_image(&hImg,filePath.toLocal8Bit().constData());
	//�ж�ͼ�����
	get_image_pointer1(hImg,NULL,NULL,&nWidth,&nHeight);
	count_channels(hImg,&nChannel);
	if (abs(nWidth - nImgWidth)>1 || abs(nHeight - nImgHeight)>1 )
	{
		strError = tr("Size of the image does not match");
	}
	else if (nChannel != nImgChannel)
	{
		strError= tr("Channel of the image does not match");
	}
	if (!strError.isEmpty())
	{
		QMessageBox::critical(this,tr("Error"),tr("Fail to open image!\nCause��")+strError);
		sOpenLocalImg.nCurIndex++;
		return;
	}

	//��ʾͼ��
	QString fileName= filePath.right(filePath.length()-filePath.lastIndexOf(tr("/"))-1);
	copy_obj(hImg,&imgShow,1,-1);
	disp_image(hImg,m_lWindID);	
	set_color(m_lWindID,"red");
	set_tposition(m_lWindID, 10, 20);
	write_string(m_lWindID, HTuple(fileName.toLocal8Bit().constData()));
}
void CDlgMainWindow::nextImg()
{
	Hobject hImg;
	Hlong nWidth,nHeight,nChannel;
	QString strError;	
	if (sOpenLocalImg.nCurIndex == sOpenLocalImg.vAllNames.size()-1)
	{
		QMessageBox::information(this,tr("Note"),tr("Already is the last"));
		return;
	}
	sOpenLocalImg.nCurIndex++;
	QString filePath = sOpenLocalImg.vAllNames[sOpenLocalImg.nCurIndex];
	read_image(&hImg,filePath.toLocal8Bit().constData());
	//�ж�ͼ�����
	get_image_pointer1(hImg,NULL,NULL,&nWidth,&nHeight);
	count_channels(hImg,&nChannel);
	if (abs(nWidth - nImgWidth)>1 || abs(nHeight - nImgHeight)>1 )
	{
		strError = tr("Size of the image does not match");
	}
	else if (nChannel != nImgChannel)
	{
		strError= tr("Channel of the image does not match");
	}
	if (!strError.isEmpty())
	{
		QMessageBox::critical(this,tr("Error"),tr("Fail to open image!\nCause��")+strError);
		sOpenLocalImg.nCurIndex++;
		return;
	}
	//��ʾͼ��
	QString fileName= filePath.right(filePath.length()-filePath.lastIndexOf(tr("/"))-1);
	copy_obj(hImg,&imgShow,1,-1);
	disp_image(hImg,m_lWindID);	
	set_color(m_lWindID,"red");
	set_tposition(m_lWindID, 10, 20);
	write_string(m_lWindID, HTuple(fileName.toLocal8Bit().constData()));
}
void CDlgMainWindow::oriImg()
{
	bShowShape = false;
	displayObject();
}
void CDlgMainWindow::drawImg()
{
	bShowShape = true;
	clear_window(m_lWindID);
	displayObject();
}
void CDlgMainWindow::resetShape()
{
	if (QMessageBox::No==QMessageBox::question(this,tr("Reset"),
		tr("The current shape is reset,and whether to continue��"),QMessageBox::Yes | QMessageBox::No))
		return;
	bResetFlag = true;
	//�����Ҽ�
	QPoint endPT;
	POINT startPT;
	int     nFullWidth=GetSystemMetrics(SM_CXSCREEN);     
	int     nFullHeight=GetSystemMetrics(SM_CYSCREEN);   
	GetCursorPos(&startPT); //��õ�ǰ�����λ��
	endPT = ui.imgFrame->mapToGlobal(ui.imgFrame->pos());		
	mouse_event(MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_RIGHTDOWN|MOUSEEVENTF_RIGHTUP,(endPT.x()+1)*65535/nFullWidth,(endPT.y()+1)*65535/nFullHeight,0,0);		
	mouse_event(MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE,startPT.x*65535/nFullWidth,startPT.y*65535/nFullHeight,0,0);

	//Hlong row,col,width,height;
	//get_window_extents(m_lWindID,&row,&col,&width,&height);
	//SetCursorPos(col+width/2,row+height/2);
}
void CDlgMainWindow::measureImg()
{	
	double row1,col1,row2,col2,dist;
	QString strDis;
	bMeasure = true;	
	//���ð�ť
	enableButtons(false);
	clear_window(m_lWindID);
	displayObject();
	//�ı�ָ��
	ui.imgFrame->setCursor(Qt::CrossCursor);
	set_mshape(m_lWindID,"crosshair");
	//����
	set_line_width(m_lWindID,3);
	set_line_style(m_lWindID,(HTuple)(30,8,3,8));
	set_color(m_lWindID,"turquoise");
	draw_line(m_lWindID,&row1,&col1,&row2,&col2);
	distance_pp(row1,col1,row2,col2,&dist);
	strDis = tr("Distance:%1").arg(QString::number(dist,'f',1));
	//��ʾ
	disp_line(m_lWindID,row1,col1,row2,col2);
	set_line_style(m_lWindID,HTuple()); //2017.7:NULL->HTuple(),NULL�����
	set_tposition(m_lWindID,(row1+row2)/2-10,(col1+col2)/2);
	set_color(m_lWindID,"magenta");
	write_string(m_lWindID,strDis.toLocal8Bit().constData());	
	disp_circle(m_lWindID,row1,col1,3.5);
	disp_circle(m_lWindID,row2,col2,3.5);
	//��������
	set_line_width(m_lWindID,1);
	ui.imgFrame->setCursor(Qt::ArrowCursor);
	set_mshape(m_lWindID,"default");	
	//�ȴ��ر�
	bDistDone = true;	
}
void CDlgMainWindow::continueShow()
{
	int i;
	//���ü������ɫ
	for (i=0;i<ui.processBox->vItemLabels.size();++i)
	{
		ui.processBox->vItemLabels[i]->setColStyle();
	}

#ifdef DAHENGBLPKP_QT
	// ���ð�ť״̬ [7/27/2015 zhaodt]
	pCheckerReal->m_bContinueShow = !pCheckerReal->m_bContinueShow;
	if (pCheckerReal->m_bContinueShow)
	{
		pCheckerReal->m_bStopAtError = false;
		ui.pbtnShowContinue->setIcon(QPixmap(":/Resources/images/imgTool/stopShow.png"));
		enableButtons(false);
	}
	else
	{
		pCheckerReal->m_bStopAtError = false;
		ui.pbtnShowContinue->setIcon(QPixmap(":/Resources/images/imgTool/continueShow.png"));
		ui.pbtnShowStop->setIcon(QPixmap(":/Resources/images/imgTool/stopAtErrorShow.png"));
		enableButtons(true);
	}
#else
	if (ui.continueShowAction->isChecked())
	{
		pCheckerReal->m_bContinueShow = true;
		pCheckerReal->m_bStopAtError = false;
		ui.stopAtErrorShowAction->setChecked(false);
		enableButtons(false);
	}
	else
	{
		pCheckerReal->m_bContinueShow = false;
		pCheckerReal->m_bStopAtError = false;		
		enableButtons(true);
	}
#endif
	//�ر�ȱ����ϸ��Ϣ����
	if (m_lRegInfoID!=0)
	{
		close_window(m_lRegInfoID);
		m_lRegInfoID = 0;
	}
}
void CDlgMainWindow::stopAtError()
{
	int i;
	//���ü������ɫ
	for (i=0;i<ui.processBox->vItemLabels.size();++i)
	{
		ui.processBox->vItemLabels[i]->setColStyle();
	}
#ifdef DAHENGBLPKP_QT
	// ���ð�ť״̬ [7/27/2015 zhaodt]
	pCheckerReal->m_bStopAtError = !pCheckerReal->m_bStopAtError;
	if (pCheckerReal->m_bStopAtError)
	{
		pCheckerReal->m_bContinueShow = true;
		ui.pbtnShowStop->setIcon(QPixmap(":/Resources/images/imgTool/stopShow.png"));
		enableButtons(false);
	}
	else
	{
		pCheckerReal->m_bContinueShow = false;
		ui.pbtnShowStop->setIcon(QPixmap(":/Resources/images/imgTool/stopAtErrorShow.png"));
		ui.pbtnShowContinue->setIcon(QPixmap(":/Resources/images/imgTool/continueShow.png"));
		enableButtons(true);
	}
#else
	if (ui.stopAtErrorShowAction->isChecked())
	{
		pCheckerReal->m_bContinueShow = true;
		pCheckerReal->m_bStopAtError = true;
		ui.continueShowAction->setChecked(false);	
		enableButtons(false);
	}
	else
	{
		pCheckerReal->m_bContinueShow = false;
		pCheckerReal->m_bStopAtError = false;	
		enableButtons(true);
	}
#endif
	//�ر�ȱ����ϸ��Ϣ����
	if (m_lRegInfoID!=0)
	{
		close_window(m_lRegInfoID);
		m_lRegInfoID = 0;
	}
}

void CDlgMainWindow::checkStopStatus()
{
	int i;
	if (pCheckerReal->m_bContinueShow == false)
	{
#ifdef DAHENGBLPKP_QT
		ui.pbtnShowContinue->setIcon(QPixmap(":/Resources/images/imgTool/continueShow.png"));
		ui.pbtnShowStop->setIcon(QPixmap(":/Resources/images/imgTool/stopAtErrorShow.png"));
#else
		ui.stopAtErrorShowAction->setChecked(false);
#endif
		enableButtons(true);
		//��������Ⱦɫ,��Ϊ����̲߳��ܸ������̷߳���Ϣ
		int nItem = pChecker->rtnInfo.nItem;
		if (nItem>=0)
		{
			//��ʼ���������ɫ
			for (i=0;i<ui.processBox->vItemLabels.size();++i)
				ui.processBox->vItemLabels[i]->setColStyle();
			//��������Ⱦɫ
			QString styleError = ui.processBox->vItemLabels[nItem]->labelErrorStyle;
			ui.processBox->vItemLabels[nItem]->setStyleSheet(styleError);
		}	
	}
}

void CDlgMainWindow::saveModel()
{
	//��¼������־QString::fromLocal8Bit(
	QString strTemp;
	strTemp = QString("Cam%1_").arg(pChecker->m_nCamIndex+1)+"CDlgMainWindow::saveModel,";//+QString::fromUtf8("����ģ��");
	pChecker->writeAlgOperationRecord(strTemp);

	ui.btnSaveModel->setEnabled(false);
	int i,j;
	bool bUpdateOri = false;//��shape�ı�ʱ����Ҫ����ԭ��͡����С�shape
	QString strFilePath = pChecker->strModelPath+"\\ModelPara.ini";
	QSettings paraSet(strFilePath,QSettings::IniFormat);
	//QApplication::addLibraryPath("./QtPlugins");
	paraSet.setIniCodec("GBK");//utf-8

	QString strShapePath = pChecker->strModelPath+"\\ModelShape.ini";
	QSettings shapeSet(strShapePath,QSettings::IniFormat);
	////ƿ���ַ���λƥ��ģ��
	//QString strCharModel = pChecker->strModelPath+"\\CharModel.shm";
	//QByteArray ba = strCharModel.toLatin1();
	//const char *pCharModel = ba.data();
	//�ļ�������Ҳȫ������
	bool bFileExist = !QFile::exists(strFilePath) || !QFile::exists(strShapePath);

#ifdef DAHENGBLPKP_QT
	int nItemClicked = ui.processBox->nOnMouseItem;
	if (nItemClicked >= 0)
	{
		ui.processBox->applyItemDlg(ui.processBox->vItemLabels[nItemClicked]);
	}
#endif

	QVector<MyLabelItem *> vItemLabels = ui.processBox->vItemLabels;	
	//ȫ��itemsҪ�ش�
	if (ui.processBox->bAllItemsChange || bReadNewModel || bFileExist)
	{		
		ui.processBox->bAllItemsChange = false;
		bReadNewModel = false;
		bUpdateOri = true;
		//����
		paraSet.clear();
		shapeSet.clear();
		for (i=0;i<vItemLabels.size();++i)
		{ 
			paraSet.beginGroup("Item_"+QString::number(i+1));
			shapeSet.beginGroup("Item_"+QString::number(i+1));
			pChecker->saveParabyType(vItemLabels[i]->nID,paraSet,*vItemLabels[i]->pPara);
			pChecker->saveShapebyType(vItemLabels[i]->nID,shapeSet,*vItemLabels[i]->pShape);
			shapeSet.endGroup();
			paraSet.endGroup();
			vItemLabels[i]->bParaChanged = false;
			vItemLabels[i]->bShapeChanged = false;			
		}
		//���浽�ⲿ���	
		pCheckerReal->qmutex.lock();
		pCheckerReal->vModelParas.clear();
		pCheckerReal->vItemFlow.clear();
		for (j=0;j<pChecker->vItemFlow.size();++j)
		{
			pCheckerReal->vModelParas.push_back(pChecker->vModelParas[j]);//����(shape�ڸ���ԭ���б���)
			pCheckerReal->vItemFlow.push_back(pChecker->vItemFlow[j]);//����
		}
		pCheckerReal->qmutex.unlock();
	}
	else//ֻ��para�ı䣬�򱣴��Ӧ��item��para��shape�ı䣬�򱣴�����item��shape��
	{
		for (i=0;i<vItemLabels.size();++i)
		{
			if (vItemLabels[i]->bParaChanged)
			{
				//����
				paraSet.beginGroup("Item_"+QString::number(i+1));				
				pChecker->saveParabyType(vItemLabels[i]->nID,paraSet,*vItemLabels[i]->pPara);
				paraSet.endGroup();
				vItemLabels[i]->bParaChanged = false;
				//���浽�ⲿ���
				pCheckerReal->qmutex.lock();
				pCheckerReal->vModelParas[i] = pChecker->vModelParas[i];
				pCheckerReal->qmutex.unlock();
			}
			if (vItemLabels[i]->bShapeChanged)//������״ʱ��ȷ����ť���ᵼ�²���Ҳ�����棬����
			{
				bUpdateOri = true;		
				vItemLabels[i]->bShapeChanged = false;
			}
		}
	}
	//����ԭ��
	if (bUpdateOri)
	{	
		bUpdateOri = false;
		//2014.7.29 ��ֹ���������ֱ�ӱ���ģ����ɵ�����ƫ��
		Hobject tempobj;
		pChecker->fnFindCurrentPos(tempobj,true);
		pChecker->modelOri = pChecker->currentOri;

		pCheckerReal->qmutex.lock();
		for (i=0;i<vItemLabels.size();++i)
		{	
			//����shape����
			shapeSet.beginGroup("Item_"+QString::number(i+1));			
			pChecker->saveShapebyType(vItemLabels[i]->nID,shapeSet,*vItemLabels[i]->pShape);
			shapeSet.endGroup();
			//������ģ��ԭ�㵽�ⲿ���			
			if (vItemLabels[i]->nID == ITEM_SIDEWALL_LOCATE)
			{				
				pCheckerReal->modelOri.Row = vItemLabels[i]->pShape->value<s_oSideLoc>().ori.Row;
				pCheckerReal->modelOri.Col = vItemLabels[i]->pShape->value<s_oSideLoc>().ori.Col;
				pCheckerReal->modelOri.Angle = vItemLabels[i]->pShape->value<s_oSideLoc>().ori.Angle;
			}
			if (vItemLabels[i]->nID == ITEM_FINISH_LOCATE)
			{
				pCheckerReal->modelOri.Row = vItemLabels[i]->pShape->value<s_oFinLoc>().Row;
				pCheckerReal->modelOri.Col = vItemLabels[i]->pShape->value<s_oFinLoc>().Col;
			}
			if (vItemLabels[i]->nID == ITEM_BASE_LOCATE)
			{
				pCheckerReal->modelOri.Row = vItemLabels[i]->pShape->value<s_oBaseLoc>().Row;
				pCheckerReal->modelOri.Col = vItemLabels[i]->pShape->value<s_oBaseLoc>().Col;
				pCheckerReal->modelOri.Radius = vItemLabels[i]->pShape->value<s_oBaseLoc>().Radius;
				pCheckerReal->modelOri.Angle = vItemLabels[i]->pShape->value<s_oBaseLoc>().Angle;
				/**************---Location---savelc:1������1694713105*****************/
				/*sprintf(aLogInfo,"---Location---savelc:%d������%d",int(vItemLabels[i]->pShape->value<s_oBaseLoc>().ifGenSp),vItemLabels[i]->pShape->value<s_pBaseLoc>().nMethodIdx);*/
				if(vItemLabels[i]->pShape->value<s_oBaseLoc>().ModelID >= 0)
					write_shape_model(vItemLabels[i]->pShape->value<s_oBaseLoc>().ModelID, ".\\model_nut.shm");
			}
			if (vItemLabels[i]->nID == ITEM_BINNER_REGION)
			{
				//ƿ���ַ���λƥ��ģ��---2016.12-MJ
				QString strCharModel = pChecker->strModelPath+QString("\\CharModel_%1.shm").arg(i);
				QByteArray ba = strCharModel.toLatin1();
				const char *pCharModel = ba.data();

				s_oBInReg oBInReg = pChecker->vModelShapes[i].value<s_oBInReg>();
				s_pBInReg pBInReg = pChecker->vModelParas[i].value<s_pBInReg>();
				if (oBInReg.ModelID >= 0 && pBInReg.bChar==true)
				{
					write_shape_model(oBInReg.ModelID, pCharModel);
					pCheckerReal->m_nBaseCharModelID = oBInReg.ModelID;
				}
			}
		}
		//��������shape���ⲿ���
		//pCheckerReal->vModelShapes = pChecker->vModelShapes;����д���ڱ�������ģ�������쳣��ԭ������
		pCheckerReal->vModelShapes.clear();
		for (j=0;j<pChecker->vItemFlow.size();++j)
		{
			pCheckerReal->vModelShapes.push_back(pChecker->vModelShapes[j]);
		}
		pCheckerReal->qmutex.unlock();
	}
	ui.btnSaveModel->setEnabled(true);

}
//*���ܣ�����
void CDlgMainWindow::checkTest()
{
	//��¼������־
	QString strTemp;
	//QTextCodec::setCodecForCStrings(QTextCodec::codecForName("GBK"));
	strTemp = QString("Cam%1_").arg(pChecker->m_nCamIndex+1)+"CDlgMainWindow::checkTest";//,������
	pChecker->writeAlgOperationRecord(strTemp);

	ui.btnTest->setEnabled(false);
	int i;
#ifdef DAHENGBLPKP_QT
	int nItemClicked = ui.processBox->nOnMouseItem;
	if (nItemClicked >= 0)
	{
		ui.processBox->applyItemDlg(ui.processBox->vItemLabels[nItemClicked]);
	}
#endif
	//��ʼ���������ɫ
	for (i=0;i<ui.processBox->vItemLabels.size();++i)
		ui.processBox->vItemLabels[i]->setColStyle();
	//2013.9.25 nanjc ����ǰ�޸�ģ��ԭ�㣬��ֹ�޸Ķ�λ�ߺ��������ػ�
	Hobject tempobj;
	pChecker->fnFindCurrentPos(tempobj,true);
	pChecker->modelOri = pChecker->currentOri;

	check(imgShow,bottleOri,bottleContour);
	clear_window(m_lWindID);
	displayObject();	
	ui.btnTest->setEnabled(true);
}
//*���ܣ����ͼ��
int CDlgMainWindow::check(Hobject &img,MyOri ori,Hobject &bottleXld)
{
	try
	{
		s_AlgCheckResult *pAlgCheckResult=NULL;
		unsigned char *ptr;
		Hlong width,height,channel;
		Hobject mirrorImg;
		bool bCurThread=true;//������ʾʱ���ⲿ�̵߳��ã�Ϊfalse
		if (pCheckerReal->m_bContinueShow)
		{
			bCurThread = false;
		}
		mirror_image(img,&mirrorImg,"row");
		get_image_pointer1(mirrorImg,(Hlong*)&ptr,NULL,&width,&height);
		count_channels(mirrorImg,&channel);
		if (width>0 && height>0)
		{
			sAlgCInp.sInputParam.nWidth = width;
			sAlgCInp.sInputParam.nHeight = height;
			sAlgCInp.sInputParam.nChannel = channel;
			sAlgCInp.sInputParam.pcData = (char*)ptr;	
			sAlgCInp.sImgLocInfo.sLocOri.modelRow = ori.Row;
			sAlgCInp.sImgLocInfo.sLocOri.modelCol = ori.Col;
			sAlgCInp.sImgLocInfo.sLocOri.modelAngle = ori.Angle;
			sAlgCInp.sImgLocInfo.sLocOri.modelRadius = ori.Radius;

			pChecker->XLDToPts(bottleXld,sAlgCInp.sImgLocInfo.sXldPoint);	
			pChecker->Check(sAlgCInp,&pAlgCheckResult);
		}

		if (pAlgCheckResult->nSizeError >0 )
		{		
			//�ı�������ɫ��ע�⣺��������ʾʱ�Ÿı䣬��Ϊ��ͬ�߳��޷�������Ϣ
			//������ʾʱ�ı�ɫ���ڼ������ֹͣ״̬�Ķ�ʱ���¼���
			if (bCurThread)
			{
				int nItem = pChecker->rtnInfo.nItem;
				if (nItem>=0)
				{
					QString styleError = ui.processBox->vItemLabels[nItem]->labelErrorStyle;
					ui.processBox->vItemLabels[nItem]->setStyleSheet(styleError);
				}
			}
			//����ֵ
			return pAlgCheckResult->vErrorParaAry[0].nErrorType;	
		}	
		return GOOD_BOTTLE;
	}
	catch(HException &e)
	{
		//Halcon�쳣		
		QString tempStr,strErr;
		tempStr=e.message;
		tempStr.remove(0,20);
		strErr = QString("Inspection module abnormal:CDlgMainWindow::Check,")+ tempStr;//���ģ���쳣
		pChecker->writeErrDataRecord(strErr);
		//2013.12.13 �����쳣ͼ���ģ��
		if (pChecker->m_bSaveErrorInfo)
		{
			pChecker->m_bSaveErrorInfo = false;
			pChecker->writeErrorInfo(strErr);
		}
		return ERROR_DET_EXCEPTION; 
	}
	catch (...)
	{
		pChecker->writeErrDataRecord(QString("abnormal:CDlgMainWindow::Check,Inspection module abnormal"));//���ģ���쳣
		//2013.12.13 �����쳣ͼ���ģ��
		if (pChecker->m_bSaveErrorInfo)
		{
			pChecker->m_bSaveErrorInfo = false;
			pChecker->writeErrorInfo(QString("abnormal:CDlgMainWindow::Check,Inspection module abnormal"));//���ģ���쳣
		}
		return ERROR_DET_EXCEPTION;
	}
}
//*���ܣ�����ģ��
void CDlgMainWindow::exportModel()
{
	//��¼������־
	QString strTemp;
	strTemp = QString("Cam%1_").arg(pChecker->m_nCamIndex+1)+"CDlgMainWindow::exportModel,����ģ��";
	pChecker->writeAlgOperationRecord(strTemp);

	// 2017.7-ʹ��quazip.dll
	QString fullPath = QFileDialog::getSaveFileName(this, tr("ExportModel"), ".", tr("ModelFile(*.zip)")); 
	if(fullPath.length() == 0) 
	{
		return;
	}
	if (fullPath.right(4)!=".zip")
	{
		fullPath+=".zip";
	}
	JlCompress::compressDir(fullPath,pChecker->strModelPath); //ѹ��

}
//*���ܣ�����ģ��
void CDlgMainWindow::importModel()
{
	////��¼������־
	QString strTemp;
	strTemp = QString("Cam%1_").arg(pChecker->m_nCamIndex+1)+"CDlgMainWindow::importModel,����ģ��";
	pChecker->writeAlgOperationRecord(strTemp);

	// 2017.7---ʹ��quazip.dll
	//���ļ�ѡ��Ի���
	QString fullPath = QFileDialog::getOpenFileName(this, tr("ImportModel"), ".", tr("ModelFile(*.zip)")); 
	if(fullPath.length() == 0) 
	{
		return;
	}	
	QString strTempForder = pChecker->strAppPath+QString("ModelInfo\\Temp\\%1").arg(pChecker->m_nCamIndex);
	//2013.9.25 ����Ŀ¼
	QDir dir;
	if (!dir.exists(strTempForder))
		dir.mkpath(strTempForder);	

	JlCompress::extractDir(fullPath,strTempForder); //��ѹ����ָ���ļ���
	
	pChecker->readModel(strTempForder);
	//��ʼ���������
	ui.processBox->initItems();	
	//��Ⲣ��ʾ
	check(imgShow,bottleOri,bottleContour);
	clear_window(m_lWindID);
	displayObject();
	bReadNewModel = true;

}
//*���ܣ�����ģ��
void CDlgMainWindow::copyModel()
{
	//��¼������־
	QString strTemp;
	strTemp = QString("Cam%1_").arg(pChecker->m_nCamIndex+1)+"CDlgMainWindow::copyModel";//,����ģ��
	pChecker->writeAlgOperationRecord(strTemp);
	//ֻ�����ѱ����ģ��
	CDlgCopyModel *dlgCopyModel = new CDlgCopyModel(this);
	dlgCopyModel->exec();
}

//*���ܣ����ð�ť״̬
void CDlgMainWindow::setBtnStatus()
{
#ifdef DAHENGBLPKP_QT
	bool bStatus = ui.processBox->bItemClicked;
	ui.pbtnInsertItem->setEnabled(bStatus);
	ui.pbtnRenameItem->setEnabled(bStatus);
	ui.pbtnDeleteItem->setEnabled(bStatus);
	ui.pbtnEnableItem->setEnabled(bStatus);
	ui.pbtnCopyItem->setEnabled(bStatus);
	//ui.pbtnPasteItem->setEnabled(bStatus);
	if (m_bEnableItem)
	{
		ui.pbtnEnableItem->setIcon(QPixmap(":/Resources/images/imgTool/enableItem.png"));
	}
	else
	{
		ui.pbtnEnableItem->setIcon(QPixmap(":/Resources/images/imgTool/disableItem.png"));
	}
#endif
}