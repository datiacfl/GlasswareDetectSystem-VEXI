#include "widget_title.h"
#include <QCheckBox>
#include "glasswaredetectsystem.h"
extern GlasswareDetectSystem *pMainFrm;


WidgetTitle::WidgetTitle(QWidget *parent)
	: QWidget(parent)
{
	version_title = new QLabel();
    min_button = new PushButton();
    close_button = new PushButton();
//	min_button->setVisible(false);
//	close_button->setVisible(false);

//	version_title->setObjectName("whiteLabel");
	QFont ft;
	ft.setPointSize(12);
	version_title->setFont(ft);

// 	QLabel *title_label = new QLabel(this);
// 	QPixmap icon(":/sys/icon");
// 	title_label->setPixmap(icon);
// 	title_label->setFixedSize(icon.size());

	//设置图片
	min_button->setPicName(QString(":/sysButton/min"));
	close_button->setPicName(QString(":/sysButton/close"));
	close_button->hide();
	connect(min_button, SIGNAL(clicked()), this, SIGNAL(showMin()));
	connect(close_button, SIGNAL(clicked()), this, SIGNAL(closeWidget()));

    QHBoxLayout *title_layout = new QHBoxLayout();
//	title_layout->addWidget(title_label,0,Qt::AlignVCenter);
    title_layout->addStretch();
    title_layout->addWidget(version_title,0,Qt::AlignVCenter);
    title_layout->addStretch();
    title_layout->addWidget(min_button, 0, Qt::AlignTop);
    title_layout->addWidget(close_button, 0, Qt::AlignTop);
	title_layout->setSpacing(0);
	title_layout->setContentsMargins(5, 0, 0, 0);
	version_title->setContentsMargins(15, 0, 0, 0);

	QStringList string_list;
	string_list<<":/toolWidget/bottle"<<":/toolWidget/home"<<":/toolWidget/count"<<":/toolWidget/bottle"<<":/toolWidget/management"\
		<<":/toolWidget/set"<<":/toolWidget/algset"<<":/toolWidget/PLC"<<":/toolWidget/algset"<<":/toolWidget/algset"\
		<<":/toolWidget/algset"<<":/toolWidget/clear"<<":/toolWidget/start"<<":/toolWidget/exit"\
		<<":/toolWidget/debug";//工具按钮图片链表 

	QHBoxLayout *button_layout = new QHBoxLayout();//水平布局管理器

	QSignalMapper *signal_mapper = new QSignalMapper(this);//工具栏的信号管理
	for(int i=0; i<string_list.size(); i++)
	{ 
		ToolButton *tool_button = new ToolButton(string_list.at(i));
		tool_button->btnStyle = TITELSTYLE;
		button_list.append(tool_button);
		connect(tool_button, SIGNAL(clicked()), signal_mapper, SLOT(map()));
		signal_mapper->setMapping(tool_button, QString::number(i, 10));
		button_layout->addWidget(tool_button, 0, Qt::AlignBottom);
	}
	connect(signal_mapper, SIGNAL(mapped(QString)), this, SLOT(turnPage(QString)));
	
	QLabel *logo_label = new QLabel();
	QPixmap pixmap(":/toolWidget/daheng");
	logo_label->setPixmap(pixmap);
	logo_label->setFixedSize(pixmap.size());


	button_layout->addStretch();
	button_layout->addWidget(logo_label);
	button_layout->setSpacing(8);
	button_layout->setContentsMargins(15, 0, 15, 0);

	QVBoxLayout *main_layout = new QVBoxLayout();
	main_layout->addLayout(title_layout);
	main_layout->addLayout(button_layout);
	main_layout->setSpacing(0);
	main_layout->setContentsMargins(0, 0, 0, 0);

	this->addToolName();

    setLayout(main_layout); 
    setFixedHeight(TITEL_HEIGHT);
    is_move = false;

	button_list.at(0)->setVisible(false);
	if (!pMainFrm->m_sSystemInfo.m_bIsUsePLC)
	{
 		button_list.at(7)->setVisible(false);
	}
	button_list.at(8)->setVisible(false);
	button_list.at(9)->setVisible(false);
	button_list.at(10)->setVisible(false);
}

void WidgetTitle::addToolName()
{
	// 	labelVersion->setText(pMainFrm->sVersion);
	version_title->setText(pMainFrm->m_sSystemInfo.m_strWindowTitle);
	min_button->setToolTip(tr("minimize"));
	close_button->setToolTip(tr("close"));

	button_list.at(0)->setText(tr("Image"));
	button_list.at(1)->setText(tr("Infomation"));
	button_list.at(2)->setText(tr("Count"));
	//button_list.at(3)->setText(tr("Carve set"));	
	button_list.at(3)->setText(tr("Image"));	
	button_list.at(4)->setText(tr("Management"));
	button_list.at(5)->setText(tr("Test"));
	button_list.at(6)->setText(tr("Algorithm set"));
	button_list.at(7)->setText(tr("PLC Info"));
	button_list.at(8)->setText(tr("Other"));
	button_list.at(9)->setText(tr("Other"));
	button_list.at(10)->setText(tr("Other"));
	button_list.at(11)->setText(tr("Clear"));
	button_list.at(12)->setText(tr("Start detect"));
	button_list.at(13)->setText(tr("Exit"));
	button_list.at(14)->setText(tr("DeBug"));
}

void WidgetTitle::turnPage(QString current_page)
{
	bool ok;  
	int current_index = current_page.toInt(&ok, 10);
	if (11 == current_index)
	{
		emit turnPage(current_index);//发给main_widget
		button_list.at(11)->setMousePress(false);
		return;
	}
	if (12 == current_index)
	{
		emit turnPage(current_index);//发给main_widget
		button_list.at(12)->setMousePress(false);
		return;
	}
	if (13 == current_index)
	{
		emit turnPage(current_index);//发给main_widget
		button_list.at(13)->setMousePress(false);
		return;
	}
	for(int i=0; i<button_list.count()-1; i++)
	{
		ToolButton *tool_button = button_list.at(i);
		if(i == current_index)
		{
			tool_button->setMousePress(true);
		}
		else
		{
			tool_button->setMousePress(false);
		}

	}
	emit turnPage(current_index);//发给main_widget
}
