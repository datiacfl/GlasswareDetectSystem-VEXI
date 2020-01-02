#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H

#include <QWidget>
#include <QSplitter>
#include <QToolButton>
#include <QPushButton>
#include <QLabel>
#include <QProgressBar>
#include <QPainter>
#include <QPen>
#include <QHBoxLayout>
#include <QEvent>
#include <QVBoxLayout>
#include "ui_image_widget.h"
#include "stateTool.h"
#include "myimageshowitem.h"
#pragma once 
class ImageWidget : public QWidget
{
	Q_OBJECT

public:
	ImageWidget(QWidget *parent = 0);
	~ImageWidget();
	
	void initDialog();
	bool leaveWidget();
	bool checkCamera();
	void showErrorCheck(int nItemID);

	Ui::ImageWidget ui;
protected:
	void resizeEvent(QResizeEvent *event);
public:
	bool bIsCarveWidgetShow;
signals:
	void signals_SetCameraStatus(int,int);
	void signals_showCarve();
	void signals_hideCarve();
public slots:
	void slots_intoWidget();
	void slots_showErrorImage(QImage*, int, int,double,QString,int, QList<QRect>, int);
	void slots_imageItemDoubleClick(int );
	void slots_addError(int nCamSN,int nSignalNo,QString nErrorType);
	void slots_turnImage();
	void slots_showCarve();

	void slots_showStartRefresh(int);
	void slots_showPrevious(int);
	void slots_showFollowing(int);

	void slots_showCheck(int nItemID);
	void slots_stopCheck(int nItemID);
	//void slots_stopAllStressCheck();
	void slots_startCheck(int nItemID);
	void slots_startShow(int nItemID);
	void slots_stopShow(int nItemID);
	void slots_startShowAll();

public:
// 	MyImageShowItem *imageShowItem;
	QImage *ImageError[CAMERA_MAX_COUNT];
	s_AlgImageLocInfo  sAlgImageLocInfo[CAMERA_MAX_COUNT];	

	QList<MyImageShowItem*> listImageShowItem;

	bool bIsShow[CAMERA_MAX_COUNT];//????????????,?????
	bool bIsShowErrorImage[CAMERA_MAX_COUNT];//????????????,?????
	bool bIsStopAllStessCheck;
	QPushButton *buttonTurnImage;
	QPushButton *buttonShowCarve;
// 	QPushButton *buttonCarve;
	
private:

// 	int shownWidthInTwoLine;
// 	int shownHeightInTwoLine;
	QWidget *widgetContent;
	QWidget *widgetContentStess;
	QGridLayout *gridLayoutImage;
	QGridLayout *gridLayoutStressImage;
	int minwidgetContentWidth;
	int minwidgetContentStessWidth;
	int iSpacing;
	int iImagePage;
 	int iShownMode;			//????:-1:?????1~n:????????
	int iBmpItemWidth;
	int iBmpItemHeight;
	int widgetWidth;
	int widgetHeight;

// 	int iFrameWid;//±ß¿òÏß¿í	
	int iCamCount;
	int nImageWidth[CAMERA_MAX_COUNT];
	int nImageHeight[CAMERA_MAX_COUNT];
	int nSignalNumber[CAMERA_MAX_COUNT];
	int iImagePosition[CAMERA_MAX_COUNT];

	QGridLayout *gridLayoutLeft;
	QGridLayout *gridLayoutMiddle;
	QGridLayout *gridLayoutRight;

	int cameraNumber;
};

#endif //IMAGEWIDGET_H