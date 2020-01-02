#include "Widget_CarveInfo.h"
#include "glasswaredetectsystem.h"
extern GlasswareDetectSystem *pMainFrm;

Widget_CarveInfo::Widget_CarveInfo(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	ui.widget_image->setWidgetName(tr("ImageSet"));
 	toolButtonToCamera = new QToolButton(ui.widget_image);
 	toolButtonToCamera->setMaximumHeight(25);
	toolButtonToCamera->setToolButtonStyle(Qt::ToolButtonIconOnly);
	toolButtonToCamera->setText(tr("CameraSet"));
	QPixmap pixmap(":/sysButton/arrow");
	toolButtonToCamera->setIcon(pixmap);
	ui.layoutImage->addWidget(ui.widget_image->widgetName, 0, Qt::AlignTop);
	ui.layoutImage->addStretch();
	ui.layoutImage->addWidget(toolButtonToCamera, 0, Qt::AlignTop);
	ui.layoutImage->setSpacing(0);
	ui.layoutImage->setContentsMargins(0, 0, 0, 0);

	ui.widget_camera->setWidgetName(tr("CameraSet"));
	toolButtonToImage = new QToolButton(ui.widget_camera);
	toolButtonToImage->setMaximumHeight(25);
	toolButtonToImage->setToolButtonStyle(Qt::ToolButtonIconOnly);
	toolButtonToImage->setText(tr("ImageSet"));
	QPixmap pixmap2(":/sysButton/arrow");
	toolButtonToImage->setIcon(pixmap2);
	ui.layoutCamera->addWidget(ui.widget_camera->widgetName, 0, Qt::AlignTop);
	ui.layoutCamera->addStretch();
	ui.layoutCamera->addWidget(toolButtonToImage, 0, Qt::AlignTop);
	ui.layoutCamera->setSpacing(0);
	ui.layoutCamera->setContentsMargins(0, 0, 0, 0);


	connect(toolButtonToCamera,SIGNAL(clicked()),this,SLOT(TrunCameraSet()));
	connect(toolButtonToImage,SIGNAL(clicked()),this,SLOT(TrunImageSet()));
	connect(ui.pushButton_setToCamera_2,SIGNAL(clicked()),ui.pushButton_setToCamera,SLOT(click()));

	ui.stackedWidget->setCurrentIndex(0);

	if(!pMainFrm->m_sSystemInfo.m_bIsCarve)//Èç¹û²»¼ôÇĞÍ¼Ïñ,Òş²Ø
	{
		ui.pushButton_carve->setVisible(false);
		ui.pushButton_cancel->setVisible(false);
		ui.pushButton_save->setVisible(false);
	}

}

Widget_CarveInfo::~Widget_CarveInfo()
{

}
void Widget_CarveInfo::TrunCameraSet()
{
	ui.stackedWidget->setCurrentIndex(1);
}
void Widget_CarveInfo::TrunImageSet()
{
	ui.stackedWidget->setCurrentIndex(0);

}