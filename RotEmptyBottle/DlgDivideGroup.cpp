#include "DlgDivideGroup.h"
#include "check.h"
CDlgDivideGroup::CDlgDivideGroup(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	//禁用按钮
	ui.btnLeft->setEnabled(false);
	ui.btnRight->setEnabled(false);
	//传递数据
	pParent = (CDlgCopyModel*)parentWidget();
	vGroup1 = pParent->vGroup1;
	vGroup2 = pParent->vGroup2;
	vGroup3 = pParent->vGroup3;
	vGroup4 = pParent->vGroup4;
	vNoGroup = pParent->vNoGroup;
	//禁用缩放，由布局调整大小
	layout()->setSizeConstraint(QLayout::SetFixedSize);
	//连接组合框信号槽
	connect(ui.comboSelectGroup,SIGNAL(currentIndexChanged(int)),this,SLOT(curGroupChanged(int)));
	connect(ui.btnLeft,SIGNAL(clicked()),this,SLOT(clickLeft()));
	connect(ui.btnRight,SIGNAL(clicked()),this,SLOT(clickRight()));
	connect(ui.listCurGroup,SIGNAL(itemClicked(QListWidgetItem *)),this,SLOT(curGroupClicked()));
	connect(ui.listNoGroup,SIGNAL(itemClicked(QListWidgetItem *)),this,SLOT(noGroupClicked()));
	//初始化对话框
	initDialog();
	//设置“这是什么”文本
	setHelpTips();
}

CDlgDivideGroup::~CDlgDivideGroup()
{

}
void CDlgDivideGroup::initDialog()
{
	QStringList strlGroup;
	int i;
	strlGroup<<tr("Group1")<<tr("Group2")<<tr("Group3")<<tr("Group4");
	ui.comboSelectGroup->addItems(strlGroup);
	nCurGroup = 0;
	//显示右边列表	
	for (i=0;i<vNoGroup.size();++i)
	{
		ui.listNoGroup->addItem(new QListWidgetItem(QString::number(vNoGroup[i])));
	}
}
void CDlgDivideGroup::setHelpTips()
{

}
void CDlgDivideGroup::curGroupChanged(int nIndex)
{
	int i;
	nCurGroup = nIndex;
	//更新显示
	ui.labelCurGroup->setText(tr("Group%1Cams:").arg(nCurGroup+1));
	ui.listCurGroup->clear();
	switch(nCurGroup)
	{
	case 0:
		for (i=0;i<vGroup1.size();++i)
			ui.listCurGroup->addItem(new QListWidgetItem(QString::number(vGroup1[i])));
		break;
	case 1:
		for (i=0;i<vGroup2.size();++i)
			ui.listCurGroup->addItem(new QListWidgetItem(QString::number(vGroup2[i])));
		break;
	case 2:
		for (i=0;i<vGroup3.size();++i)
			ui.listCurGroup->addItem(new QListWidgetItem(QString::number(vGroup3[i])));
		break;
	case 3:
		for (i=0;i<vGroup4.size();++i)
			ui.listCurGroup->addItem(new QListWidgetItem(QString::number(vGroup4[i])));
		break;
	default:
		break;
	}
}
void CDlgDivideGroup::curGroupClicked()
{
	ui.btnRight->setEnabled(true);
	ui.btnLeft->setEnabled(false);
}
void CDlgDivideGroup::noGroupClicked()
{
	ui.btnLeft->setEnabled(true);
	ui.btnRight->setEnabled(false);
}
void CDlgDivideGroup::clickLeft()
{
	QListWidgetItem * curItem = ui.listNoGroup->currentItem();
	int nCurRow = ui.listNoGroup->currentRow();
	//改变分组信息
	vNoGroup.remove(nCurRow);
	switch(nCurGroup)
	{
	case 0:
		vGroup1.push_back(curItem->text().toInt());
		break;
	case 1:
		vGroup2.push_back(curItem->text().toInt());
		break;
	case 2:
		vGroup3.push_back(curItem->text().toInt());
		break;
	case 3:
		vGroup4.push_back(curItem->text().toInt());
		break;
	default:
		break;
	}
	//改变显示	
	ui.listNoGroup->removeItemWidget(curItem);	
	ui.listCurGroup->addItem(new QListWidgetItem(curItem->text()));
	delete curItem;
	ui.btnLeft->setEnabled(false);	
}
void CDlgDivideGroup::clickRight()
{
	QListWidgetItem * curItem = ui.listCurGroup->currentItem();	
	int nCurRow = ui.listCurGroup->currentRow();
	//改变分组信息
	switch(nCurGroup)
	{
	case 0:
		vGroup1.remove(nCurRow);
		break;
	case 1:
		vGroup2.remove(nCurRow);
		break;
	case 2:
		vGroup3.remove(nCurRow);
		break;
	case 3:
		vGroup4.remove(nCurRow);
		break;
	default:
		break;
	}
	vNoGroup.push_back(curItem->text().toInt());
	//改变显示
	ui.listCurGroup->removeItemWidget(curItem);	
	ui.listNoGroup->addItem(new QListWidgetItem(curItem->text()));
	delete curItem;
	ui.btnRight->setEnabled(false);
}
void CDlgDivideGroup::accept()
{
	//写入配置
	QString strConfigPath = pParent->pChecker->strAppPath+"Config\\CamGroup.ini";
	QSettings groupSet(strConfigPath,QSettings::IniFormat);
	QString strMember;
	int i;

	groupSet.beginGroup("Group1");
	strMember.clear();
	for (i=0;i<vGroup1.size();++i)
	{
		strMember+=QString::number(vGroup1[i]);
		if (i!=vGroup1.size()-1)
			strMember+=",";
	}
	groupSet.setValue("member",strMember);
	groupSet.endGroup();

	groupSet.beginGroup("Group2");
	strMember.clear();
	for (i=0;i<vGroup2.size();++i)
	{
		strMember+=QString::number(vGroup2[i]);
		if (i!=vGroup2.size()-1)
			strMember+=",";
	}
	groupSet.setValue("member",strMember);
	groupSet.endGroup();

	groupSet.beginGroup("Group3");
	strMember.clear();
	for (i=0;i<vGroup3.size();++i)
	{
		strMember+=QString::number(vGroup3[i]);
		if (i!=vGroup3.size()-1)
			strMember+=",";
	}
	groupSet.setValue("member",strMember);
	groupSet.endGroup();

	groupSet.beginGroup("Group4");
	strMember.clear();
	for (i=0;i<vGroup4.size();++i)
	{
		strMember+=QString::number(vGroup4[i]);
		if (i!=vGroup4.size()-1)
			strMember+=",";
	}
	groupSet.setValue("member",strMember);
	groupSet.endGroup();

	groupSet.beginGroup("NoGroup");
	strMember.clear();
	for (i=0;i<vNoGroup.size();++i)
	{
		strMember+=QString::number(vNoGroup[i]);
		if (i!=vNoGroup.size()-1)
			strMember+=",";
	}
	groupSet.setValue("member",strMember);
	groupSet.endGroup();
	//传递数据
	pParent->vGroup1 = vGroup1;
	pParent->vGroup2 = vGroup2;
	pParent->vGroup3 = vGroup3;
	pParent->vGroup4 = vGroup4;
	pParent->vNoGroup = vNoGroup;
	return QDialog::accept();
}
