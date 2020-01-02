#include "DlgCopyModel.h"
#include "DlgDivideGroup.h"
#include "DlgMainWindow.h"
#include <QSettings>

CDlgCopyModel::CDlgCopyModel(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	iCheckItemsCols = 3;
	////传递检测指针
	//pChecker = ((CDlgMainWindow *)parentWidget())->pChecker;
	//2013.10.8 nanjc 用于复制参数，只复制已保存的模板参数，传递外部检测指针
	pChecker = new CCheck;
	*pChecker = *(((CDlgMainWindow *)parentWidget())->pCheckerReal);
	//添加检测项复选框
	CheckBox_list.clear();
	QGridLayout *checkBox_layout = new QGridLayout(ui.groupBoxCheckItems);
	int i;
	//将检测项添加到groupbox中
	QString strpara = pChecker->strModelPath+"\\ModelPara.ini";
	QSettings paraSet(strpara,QSettings::IniFormat);
	paraSet.setIniCodec("GBK");	
	//if (paraSet.childGroups().size()==0)
	//	return;//模板为空			
	//读取文件中检测项
	for (i = 0;i<paraSet.childGroups().size();++i)
	{
		paraSet.beginGroup("Item_"+QString::number(i+1));
		QString strname = paraSet.value("name").toString();
		paraSet.endGroup();
		QCheckBox *checkBox;
		checkBox = new QCheckBox(this);
		checkBox->setChecked(false);
		checkBox->setText(strname);
		CheckBox_list.append(checkBox);
		checkBox_layout->addWidget(checkBox, i/iCheckItemsCols, i%iCheckItemsCols);
	}
	checkBox_layout->setSpacing(6);
	checkBox_layout->setContentsMargins(9,9,9,9);
	//初始化
	ui.progressBar->setMinimum(0);
	ui.progressBar->setMaximum(100);
	ui.progressBar->setValue(0);
	vGroup1.clear();
	vGroup2.clear();
	vGroup3.clear();
	vGroup4.clear();
	vNoGroup.clear();
	//禁用缩放，由布局调整大小
	layout()->setSizeConstraint(QLayout::SetFixedSize);
	//连接组合框信号槽
	connect(ui.btnGroup,SIGNAL(clicked()),this,SLOT(divideGroups()));
	connect(ui.radioGroup1,SIGNAL(toggled(bool)),this,SLOT(GroupChanged(bool)));
	connect(ui.radioGroup2,SIGNAL(toggled(bool)),this,SLOT(GroupChanged(bool)));
	connect(ui.radioGroup3,SIGNAL(toggled(bool)),this,SLOT(GroupChanged(bool)));
	connect(ui.radioGroup4,SIGNAL(toggled(bool)),this,SLOT(GroupChanged(bool)));
	connect(ui.radioPara,SIGNAL(toggled(bool)),this,SLOT(CopyChanged(bool)));
	connect(ui.radioAll,SIGNAL(toggled(bool)),this,SLOT(CopyChanged(bool)));
	connect(ui.radioCheckItems,SIGNAL(toggled(bool)),this,SLOT(CopyChanged(bool)));
	connect(ui.btnStart,SIGNAL(clicked()),this,SLOT(startCopy()));
	//初始化对话框
	initDialog();
	//设置“这是什么”文本
	setHelpTips();
	
}

CDlgCopyModel::~CDlgCopyModel()
{
	//2013.10.8 nanjc 用于复制参数，只复制已保存的模板参数，传递外部检测指针--对应new的delete
	if (pChecker != NULL)
	{
		delete pChecker;
		pChecker = NULL;
	}
}
bool CDlgCopyModel::checkConfig()
{
	int i,j;
	QString strConfigPath = pChecker->strAppPath+"Config\\CamGroup.ini";
	QSettings groupSet(strConfigPath,QSettings::IniFormat);
	QString strMember;
	QStringList strlMember;
	bool bPass=true,bFlag;
	//读取分组配置信息
	groupSet.beginGroup("Group1");
	strMember = groupSet.value("member").toString();
	if (strMember != "")
	{
		strlMember = strMember.split(",");
		for (i=0;i<strlMember.size();++i)
		{
			vGroup1.push_back(strlMember[i].toInt());
		}
	}
	groupSet.endGroup();

	groupSet.beginGroup("Group2");
	strMember = groupSet.value("member").toString();
	if (strMember != "")
	{
		strlMember = strMember.split(",");
		for (i=0;i<strlMember.size();++i)
		{
			vGroup2.push_back(strlMember[i].toInt());
		}
	}
	groupSet.endGroup();

	groupSet.beginGroup("Group3");
	strMember = groupSet.value("member").toString();
	if (strMember != "")
	{
		strlMember = strMember.split(",");
		for (i=0;i<strlMember.size();++i)
		{
			vGroup3.push_back(strlMember[i].toInt());
		}
	}
	groupSet.endGroup();

	groupSet.beginGroup("Group4");
	strMember = groupSet.value("member").toString();
	if (strMember != "")
	{
		strlMember = strMember.split(",");
		for (i=0;i<strlMember.size();++i)
		{
			vGroup4.push_back(strlMember[i].toInt());
		}
	}
	groupSet.endGroup();

	groupSet.beginGroup("NoGroup");
	strMember = groupSet.value("member").toString();
	if (strMember != "")
	{
		strlMember = strMember.split(",");
		for (i=0;i<strlMember.size();++i)
		{
			vNoGroup.push_back(strlMember[i].toInt());
		}
	}
	groupSet.endGroup();
	//合并数据
	QVector <int> vAll;
	for (i=0;i<vGroup1.size();++i)
		vAll.push_back(vGroup1[i]);
	for (i=0;i<vGroup2.size();++i)
		vAll.push_back(vGroup2[i]);
	for (i=0;i<vGroup3.size();++i)
		vAll.push_back(vGroup3[i]);
	for (i=0;i<vGroup4.size();++i)
		vAll.push_back(vGroup4[i]);
	for (i=0;i<vNoGroup.size();++i)
		vAll.push_back(vNoGroup[i]);
	if (vAll.size()!=pChecker->checkerAry.iValidNum)
	{
		bPass = false;
	}
	//检查重复性
	for (j=1;j<vAll.size()+1;++j)
	{
		bFlag=false;
		for (i=0;i<vAll.size();++i)
		{
			if (vAll[i]==j)
			{
				bFlag=true;
				break;
			}
		}
		if (!bFlag)
		{
			bPass=false;
			break;
		}
	}
	return bPass;
}
void CDlgCopyModel::initDialog()
{
	ui.radioPara->setChecked(true);
	ui.groupBoxCheckItems->setEnabled(false);
	ui.groupToWhere->setTitle(tr("Copy camera%1 to:").arg(pChecker->m_nCamIndex+1));
	//检查分组配置
	int i;
	bool bConfig = checkConfig();
	if (!bConfig)
	{
		ui.btnStart->setEnabled(false);
		ui.labelDetail->setText(tr("<font color=red>Error: grouping configuration information does not match with the actual and need to reset!/font>"));
		vGroup1.clear();
		vGroup2.clear();
		vGroup3.clear();
		vGroup4.clear();
		vNoGroup.clear();
		for (i=1;i<pChecker->checkerAry.iValidNum+1;++i)
		{
			vNoGroup.push_back(i);
		}
		return;
	}
	//判断属于哪个分组
	checkGroup();	
}
void CDlgCopyModel::setHelpTips()
{

}
void CDlgCopyModel::checkGroup()
{
	int i;
	int nGroup;
	bool bFind=false;
	int nCurCam = pChecker->m_nCamIndex+1;

	if (!bFind)
	{
		for (i=0;i<vGroup1.size();++i)
		{
			if (nCurCam == vGroup1[i])
			{
				bFind = true;
				nGroup = 1;
				break;
			}
		}
	}
	if (!bFind)
	{
		for (i=0;i<vGroup2.size();++i)
		{
			if (nCurCam == vGroup2[i])
			{
				bFind = true;
				nGroup = 2;
				break;
			}
		}
	}
	if (!bFind)
	{
		for (i=0;i<vGroup3.size();++i)
		{
			if (nCurCam == vGroup3[i])
			{
				bFind = true;
				nGroup = 3;
				break;
			}
		}
	}
	if (!bFind)
	{
		for (i=0;i<vGroup4.size();++i)
		{
			if (nCurCam == vGroup4[i])
			{
				bFind = true;
				nGroup = 4;
				break;
			}
		}
	}
	if (!bFind)
	{
		for (i=0;i<vNoGroup.size();++i)
		{
			if (nCurCam == vNoGroup[i])
			{
				bFind = true;
				nGroup = 5;
				break;
			}
		}
	}
	nCurGroup = nGroup;
	ui.btnStart->setEnabled(true);
	switch(nGroup)
	{
	case 1:
		ui.radioGroup1->setChecked(true);
		break;
	case 2:
		ui.radioGroup2->setChecked(true);
		break;
	case 3:
		ui.radioGroup3->setChecked(true);
		break;
	case 4:
		ui.radioGroup4->setChecked(true);
		break;
	case 5:
		ui.btnStart->setEnabled(false);
		ui.labelDetail->setText(tr("<font color=red>Error: The current camera has not been grouped!</font>"));
		ui.btnStart->setEnabled(false);
		break;
	default:
		break;
	}
	return ;	
}
void CDlgCopyModel::divideGroups()
{
	CDlgDivideGroup *dlgDivideGroup  = new CDlgDivideGroup(this);
	if (QDialog::Rejected == dlgDivideGroup->exec())
	{
		return;
	}
	ui.btnStart->setEnabled(true);
	checkGroup();
	emit GroupChanged(true);

}
void CDlgCopyModel::CopyChanged(bool checked)
{
	if (!checked)
		return;
	ui.groupBoxCheckItems->setEnabled(ui.radioCheckItems->isChecked());
}

void CDlgCopyModel::GroupChanged(bool checked)
{
	if (!checked)
		return;
	int i;
	QString strDis,strTail;		
	strTail = tr("<br><font color=red>Note: The current camera isn't part of the group!</font>");
	if (ui.radioGroup1->isChecked())
	{
		strDis.clear();
		for (i=0;i<vGroup1.size();++i)
		{
			strDis+=QString::number(vGroup1[i]);
			if (i==vGroup1.size()-1)
			{
				strDis+=".";
			}
			else
				strDis+=",";
		}
		if (nCurGroup!=1)
		{
			strDis+=strTail;
			ui.btnStart->setEnabled(false);
		}
		else
			ui.btnStart->setEnabled(true);
	}
	if (ui.radioGroup2->isChecked())
	{
		strDis.clear();
		for (i=0;i<vGroup2.size();++i)
		{
			strDis+=QString::number(vGroup2[i]);
			if (i==vGroup2.size()-1)
			{
				strDis+=".";
			}
			else
				strDis+=",";
		}
		if (nCurGroup!=2)
		{
			strDis+=strTail;
			ui.btnStart->setEnabled(false);
		}
		else
			ui.btnStart->setEnabled(true);
	}
	if (ui.radioGroup3->isChecked())
	{
		strDis.clear();
		for (i=0;i<vGroup3.size();++i)
		{
			strDis+=QString::number(vGroup3[i]);
			if (i==vGroup3.size()-1)
			{
				strDis+=".";
			}
			else
				strDis+=",";
		}
		if (nCurGroup!=3)
		{
			strDis+=strTail;
			ui.btnStart->setEnabled(false);
		}
		else
			ui.btnStart->setEnabled(true);
	}
	if (ui.radioGroup4->isChecked())
	{
		strDis.clear();
		for (i=0;i<vGroup4.size();++i)
		{
			strDis+=QString::number(vGroup4[i]);
			if (i==vGroup4.size()-1)
			{
				strDis+=".";
			}
			else
				strDis+=",";
		}
		if (nCurGroup!=4)
		{
			strDis+=strTail;
			ui.btnStart->setEnabled(false);
		}
		else
			ui.btnStart->setEnabled(true);
	}
	ui.labelDetail->setText(tr("IncludedCameras:")+strDis);	
}

// 2017.8-复制模板完成时偶尔出现程序崩溃(已加互斥)
void CDlgCopyModel::startCopy()
{
	QVector <int>vDest;
	int i,ii;
	int j;
	CCheck * tempChecker;
	QString strOld,strNew,strTail,strCamTail,strDetTail;
	bool bExist,bsigCamExist,bsigDetExist;
	strTail = tr("<font color=red>Note:");
	strCamTail = "";
	bExist = true;
	ui.btnStart->setEnabled(false);

	//记录操作日志
	QString strTemp;
	strTemp = QString("Cam%1_").arg(pChecker->m_nCamIndex+1)+"CDlgCopyModel::startCopy,starting to copy";//,开始复制
	pChecker->writeAlgOperationRecord(strTemp);

	//获得要复制的目标相机序号
	switch(nCurGroup)
	{
	case 1:
		vDest = vGroup1;
		break;
	case 2:
		vDest = vGroup2;
		break;
	case 3:
		vDest = vGroup3;
		break;
	case  4:
		vDest = vGroup4;
		break;
	default:
		break;
	}
	for (i=0;i<vDest.size();++i)
	{
		if (pChecker->m_nCamIndex+1==vDest[i])
		{
			vDest.remove(i);
			break;
		}
	}
	//开始复制
	for (i=0;i<vDest.size();++i)
	{
		//获得目标检测指针
		for (j=0;j<pChecker->checkerAry.iValidNum;++j)
		{
			if (vDest[i]-1==pChecker->checkerAry.pCheckerlist[j].nID)
			{ 
				tempChecker = (CCheck *)(pChecker->checkerAry.pCheckerlist[j].pChecker->m_pAlg);
				break;
			}
		}
		//删除并复制模板文件
		if (ui.radioPara->isChecked())//参数
		{
			strOld = pChecker->strModelPath+"\\ModelPara.ini";
			strNew = tempChecker->strModelPath+"\\ModelPara.ini";
/*			if (QFile::exists(strNew))
			{
				QFile::remove(strNew);
			}
			QFile::copy(strOld,strNew);*/	
			//2013.9.28 nanjc 检测项顺序或个数不一致时，会导致参数混乱的异常。
			QSettings oldparaSet(strOld,QSettings::IniFormat);
			QSettings newparaSet(strNew,QSettings::IniFormat);
			//QApplication::addLibraryPath("./QtPlugins");
			oldparaSet.setIniCodec("GBK");	
			newparaSet.setIniCodec("GBK");	

			if (oldparaSet.childGroups().size()==0)
				return;//模板为空
				
			bsigCamExist = true;
			strDetTail = "";
			//仅修改items中名称和类型均一致的参数	
			//foreach(QString oldgroup,oldparaSet.childGroups())
			//{
			//	oldparaSet.beginGroup("Item_"+QString::number(ii+1));
			//	oldparaSet.beginGroup(oldgroup);
			for (ii = 0;ii<oldparaSet.childGroups().size();++ii)
			{
				oldparaSet.beginGroup("Item_"+QString::number(ii+1));
				int noldtype = oldparaSet.value("type").toInt();
				QString stroldname = oldparaSet.value("name").toString();
				oldparaSet.endGroup();
				bsigDetExist = false;
				foreach(QString newgroup,newparaSet.childGroups())
				{				
					newparaSet.beginGroup(newgroup);
					int nnewtype = newparaSet.value("type").toInt();
					QString strnewname = newparaSet.value("name").toString();
					if (noldtype == nnewtype && stroldname == strnewname)
					{
						//旧模板参数保存到新模板文件中
						tempChecker->saveParabyType(nnewtype,newparaSet,pChecker->vModelParas[ii],true);
						newparaSet.endGroup();
						bsigDetExist = true;
						break;
					}
					newparaSet.endGroup();
				}
				//复制模板提示信息
				if (!bsigDetExist)
				{
					strDetTail = strDetTail + stroldname + tr(";");
					bsigCamExist = false;
				}			
			}

			if (!bsigCamExist)
			{
				strCamTail = strCamTail + tr("<br>Camera%1<font color=black>isn't found detectionItem of the same name or type：</font>")
					.arg(vDest[i]) + strDetTail + tr("<font color=black>the detectionItem of the camera</font>can not copy！");
				bExist = false;
			}	
		}		
		if (ui.radioAll->isChecked())//全部
		{
			strOld = pChecker->strModelPath+"\\ModelPara.ini";
			strNew = tempChecker->strModelPath+"\\ModelPara.ini";
			if (QFile::exists(strNew))
			{
				QFile::remove(strNew);
			}
			QFile::copy(strOld,strNew);
			strOld = pChecker->strModelPath+"\\ModelShape.ini";
			strNew = tempChecker->strModelPath+"\\ModelShape.ini";
			if (QFile::exists(strNew))
			{
				QFile::remove(strNew);
			}
			QFile::copy(strOld,strNew);			
		}
		if (ui.radioCheckItems->isChecked())//检测项
		{
			strOld = pChecker->strModelPath+"\\ModelPara.ini";
			QString strNewPara = tempChecker->strModelPath+"\\ModelPara.ini";
			QString strNewShape = tempChecker->strModelPath+"\\ModelShape.ini";
			//2014.10.27 nanjc 复制单个检测项，检测项存在（名称类型均一致）时，替换；若不存在，新增
			QSettings oldparaSet(strOld,QSettings::IniFormat);
			QSettings newparaSet(strNewPara,QSettings::IniFormat);
			QSettings newshapeSet(strNewShape,QSettings::IniFormat);
			oldparaSet.setIniCodec("GBK");	
			newparaSet.setIniCodec("GBK");	
			if (oldparaSet.childGroups().size()==0)
				return;//模板为空				
			bsigCamExist = true;
			strDetTail = "";
			int iGroupSize = newparaSet.childGroups().size();//若检测项存在直接修改，若不存在，则在结尾新增，总数+1
			for (ii = 0;ii<oldparaSet.childGroups().size();++ii)
			{
				//选中才复制
				if (ii>=CheckBox_list.size())
				{
					continue;
				}
				if (!CheckBox_list.at(ii)->isChecked())
				{
					continue;
				}
				oldparaSet.beginGroup("Item_"+QString::number(ii+1));
				int noldtype = oldparaSet.value("type").toInt();
				QString stroldname = oldparaSet.value("name").toString();
				oldparaSet.endGroup();
				bsigDetExist = false;
				foreach(QString newgroup,newparaSet.childGroups())
				{				
					newparaSet.beginGroup(newgroup);
					int nnewtype = newparaSet.value("type").toInt();
					QString strnewname = newparaSet.value("name").toString();
					if (noldtype == nnewtype && stroldname == strnewname)
					{
						//旧模板参数保存到新模板文件中
						tempChecker->saveParabyType(nnewtype,newparaSet,pChecker->vModelParas[ii],true);
						newparaSet.endGroup();
						//图形
						newshapeSet.beginGroup(newgroup);
						tempChecker->saveShapebyType(nnewtype,newshapeSet,pChecker->vModelShapes[ii]);
						newshapeSet.endGroup();
						bsigDetExist = true;
						break;
					}
					newparaSet.endGroup();
				}
				//复制模板提示信息
				if (!bsigDetExist)
				{
					//strDetTail = strDetTail + stroldname + tr(";");
					//bsigCamExist = false;
					iGroupSize += 1;
					newparaSet.beginGroup("Item_"+QString::number(iGroupSize));
					tempChecker->saveParabyType(noldtype,newparaSet,pChecker->vModelParas[ii],true);
					newparaSet.endGroup();
					//图形
					newshapeSet.beginGroup("Item_"+QString::number(iGroupSize));
					tempChecker->saveShapebyType(noldtype,newshapeSet,pChecker->vModelShapes[ii]);
					newshapeSet.endGroup();
				}			
			}
			//if (!bsigCamExist)
			//{
			//	strCamTail = strCamTail + tr("<br>Camera%1<font color=black>isn't found detectionItem of the same name or type：</font>")
			//		.arg(vDest[i]) + strDetTail + tr("<font color=black>the detectionItem of the camera</font>can not copy！");
			//	bExist = false;
			//}	
		}
		//读入模板	
		tempChecker->qmutex.lock();
		tempChecker->readModel(tempChecker->strModelPath);
		ui.progressBar->setValue((float)(i+1)/(float)vDest.size()*100.f);
		tempChecker->qmutex.unlock();
	}
	if (!bExist)
	{
		strTail = strTail + strCamTail + tr("<br>Please modify the same name or type, before the detection is copyed！</font>");
		ui.labelDetail->setText(strTail);	
	}
	else
	{
		strTail = tr("The copy is complete！");
		ui.labelDetail->setText(strTail);	
	}
	ui.btnStart->setEnabled(true);

}