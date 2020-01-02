#ifndef MYIMAGESHOWITEM_H
#define MYIMAGESHOWITEM_H

#include <QWidget>
#include <QMenu>
#include <QAction>
#include <QTimer>
#include <QGridLayout>
#include <QPushButton>
#include <vector>
#include "pushButton.h"
#include "SingleCameraPic.h"
#include <QMutex>
class MyImageShowItem : public QWidget
{
	Q_OBJECT

public:
	MyImageShowItem(QWidget *parent);
	~MyImageShowItem();

	void inital(int);
	void SetRectColor();
	void setMaxShow(bool bSatus);
	void updateImage(QImage*, QString, QString, QString, QString, QString,QList<QRect>);
//	void clearErrorInfo();

	bool bIsCheck;

signals:
	void signals_imageItemDoubleClick(int );
	void signals_showPrevious(int);
	void signals_showFollowing(int);
	void signals_showStartRefresh(int);
	void signals_startShowAll();

	void signals_showCheck(int );
	void signals_stopCheck(int );
	void signals_stopAllStressCheck( );
	void signals_startCheck(int );
	void signals_startShow(int );
	void signals_stopShow(int );
		
public slots:
// 	void slots_updateImage(QString,QString,QString,QString);
	void slots_updateImage(QImage*, QString, QString, QString, QString,QString, QList<QRect>,int);
	void slots_updateMaxImageItem(QImage, QString, QString, QString, QString, QString,QList<QRect>,int,int);
	void slots_showErrorInfo(QString error,int time = 0, bool bError = true);
	void slots_showWarningInfo(QString error,int time = 1, bool bError = true);
	void slots_update();

	void slots_clearErrorInfo();
	void slots_clearWarningInfo();

	void slots_saveImage();
	void slots_showCheck();
	void slots_stopCheck();
	void slots_stopAllStressCheck();
	void slots_startCheck();
	void slots_startAllStressCheck();
	void slots_startShow();
	void slots_stopShow();

	void slots_showPrevious();
	void slots_showFollowing();
	void slots_showStartRefresh();
	void slots_startShowAll();
	void slots_showButtonToPic();

protected:
	void createActions();
	void paintEvent(QPaintEvent *event);
	void mouseDoubleClickEvent(QMouseEvent *event);
// 	void resizeEvent(QResizeEvent *event);
	void contextMenuEvent(QContextMenuEvent *event);
	virtual void enterEvent(QEvent *);
	virtual void leaveEvent(QEvent *);
public:
	void ShowErrorPicButtonLayout();
	bool ShowAllPicButton(bool isMaxShow, bool isShow);
	void AllPicButtonLayout();
	void ConnectThreadAndShowItem();
	void SetButtonInitialStatus();
	void updatapic();
	void updataLastPic();
private:
	int iCameraNo;
	int iImageWidth;
	int iImageHeight;
	QString strCamera;
	QString strImageSN;
	QString strTime;
	QString strResult;
	QString nMouldID;
	QPixmap pixmapShown;
	QImage imageForWidget;
	QString strError;
	QString strWarning;
	bool bIsHaveError;
	bool bIsHaveWarning;
	QList<QRect> listErrorRect;

	QTimer *timerErrorInfo;
	QTimer *timerWarningInfo;

	QAction *saveAction;
	QAction *showCheck;
	QAction *stopCheck;
	QAction *stopAllStressCheck;
	QAction *startCheck;
	QAction *startAllStressCheck;
//	QAction *startShow;
	QAction *startFreshAll;

	QMenu *contextMenu;

	PushButton *btnPrevious;
	PushButton *btnFollowing;
	PushButton *btnStartRefresh;

	QColor colorRect;
	bool bIsUpdateImage;
// 	bool bIsCameraOK;
	QVector<QRgb> m_vcolorTable;

	
	std::vector<QPushButton*> m_vecCameraAllPic;
	//以前三个显示错误图片的布局
	QHBoxLayout *layoutButton;
	QVBoxLayout *mainLayout;
	//增加显示每张图片的按钮的布局
	QGridLayout *PicButtonLayout;
	QVBoxLayout *mainBoxLayout;
	std::vector<SingleCameraPic> m_vecSingleCameraPic;
	std::vector<SingleCameraPic> m_PicDataTemp;
	std::list<std::vector<SingleCameraPic>> m_LastAllCameraPic;
	QString imgNumber;
	int singleCameraCount;
	int m_LastNumber;
	QMutex m_lockData;
	QImage m_tempImage;
public:
	bool bIsMaxShow;
};

#endif // MYIMAGESHOWITEM_H
