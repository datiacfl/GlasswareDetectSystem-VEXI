#include "widget_sample.h"

#include "glasswaredetectsystem.h"

extern GlasswareDetectSystem *pMainFrm;

Widget_Sample::Widget_Sample(QWidget *parent)
	: DHBaseWidget(parent)
{
	QFont font;
	font.setPointSize(9);
	setFont(font);

	setWidgetName(tr("Sample"));
	setWidgetFont(font);
	initail();
}

Widget_Sample::~Widget_Sample()
{

}

void Widget_Sample::initail()
{
	QGridLayout *gridlayout = new QGridLayout();
	signalmapper = new QSignalMapper(this);//工具栏的信号管理
	for (int i = 0;i<pMainFrm->m_sErrorInfo.m_iErrorTypeCount;i++)
	{
		QCheckBox *checkBox = new QCheckBox(this);
		checkBox->setText(pMainFrm->m_sErrorInfo.m_vstrErrorType.at(i));

		listCheckBox.append(checkBox);
		connect(checkBox, SIGNAL(stateChanged(int)), signalmapper, SLOT(map()));
		signalmapper->setMapping(checkBox, i);
		gridlayout->addWidget(checkBox,i/4,i%4);
	}
	button_OK = new QPushButton(this);
	button_OK->setText(tr("OK"));


	label_sampleCount = new QLabel;
	lineEdit_sampleCount = new QLineEdit;
	label_sampleCount->setText(tr("Number of Sampling:"));
	QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Fixed);
	lineEdit_sampleCount->setSizePolicy(sizePolicy2);
	lineEdit_sampleCount->setValidator(new QIntValidator(0, 10000, this));
	gridlayout->addWidget(label_sampleCount,(pMainFrm->m_sErrorInfo.m_iErrorTypeCount-1)/4+1,1);
	gridlayout->addWidget(lineEdit_sampleCount,(pMainFrm->m_sErrorInfo.m_iErrorTypeCount-1)/4+1,2);
	gridlayout->addWidget(button_OK,(pMainFrm->m_sErrorInfo.m_iErrorTypeCount-1)/4+1,3);
	
	connect(signalmapper, SIGNAL(mapped(int)), this, SLOT(changeCheckState(int)));
	connect(lineEdit_sampleCount,SIGNAL(textChanged(QString)), this ,SLOT(changeSimpleCount()));

	QHBoxLayout *namelayout = new QHBoxLayout();
	namelayout->addWidget(widgetName);

	QVBoxLayout *mainLayout = new QVBoxLayout();
	mainLayout->addLayout(namelayout);
	mainLayout->addLayout(gridlayout);
	mainLayout->setSpacing(6);
	mainLayout->setContentsMargins(9,0,9,9);

	setLayout(mainLayout);
}
 void Widget_Sample::changeCheckState(int index)
 {
 	bIsChanged = true;
	sSampleInfo.m_iSampleTypeCount = 0;
	for (int i=0;i<pMainFrm->m_sErrorInfo.m_iErrorTypeCount;i++)
	{
		if (listCheckBox.at(i)->isChecked())
		{
  			sSampleInfo.m_bSampleType[i] = true;
  			sSampleInfo.m_iSampleTypeCount++;
		}
		else
		{
			sSampleInfo.m_bSampleType[i] = false;
		}
	}
//  	if (listCheckBox.at(index)->isChecked())
//  	{
//  		sSampleInfo.m_bSampleType[index] = true;
//  		sSampleInfo.m_iSampleTypeCount++;
//  	}
//  	else
//  	{
//  		sSampleInfo.m_bSampleType[index] = false;
//  		sSampleInfo.m_iSampleTypeCount--;
//  	}
 	
 }
 void Widget_Sample::changeSimpleCount()
 {
	 bIsChanged = true;
	 sSampleInfo.m_iSampleCount = lineEdit_sampleCount->text().toInt();
 }
 void Widget_Sample::setSimpleCount(int iSimpleCount)
 {
	 bIsChanged = true;
	 lineEdit_sampleCount->setText(QString::number( iSimpleCount));
 }