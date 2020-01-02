#ifndef WIDGET_DEBUG_H
#define WIDGET_DEBUG_H

#include <QWidget>
#include <QtGui/QScrollArea>

#include "dhbasewidget.h"
#include "myLogText.h"
class Widget_Debug : public QWidget
{
	Q_OBJECT

public:
	Widget_Debug(QWidget *parent);
	~Widget_Debug();

	bool leaveWidget();
public slots:
	void slots_intoWidget();
	void slots_ShowDebugLog(QString str,QColor color = Qt::black);
private:
	void initial();

	void getSystemInfo();
	void getRunningInfo();
	void getCameraInfo();
	void getRealCameraInfo();
	void getqueueInfo1Info();
	void getqueueInfo2Info();
	void geterrorInfoInfo();
private slots:
	void slots_updateDebugInfo();
private:
	QScrollArea *scrollArea;
	DHBaseWidget *widget_systemInfo; 
	DHBaseWidget *widget_runningInfo; 
	DHBaseWidget *widget_errorInfo; 
	DHBaseWidget *widget_cameraInfo; 
	DHBaseWidget *widget_realCameraInfo; 
	DHBaseWidget *widget_queueInfo1; 
	DHBaseWidget *widget_queueInfo2; 
	CMyLogText *DebugLogText;
	QWidget *scrollAreaWidgetContents;
	QLabel *label_systemInfo;
	QLabel *label_runningInfo;
	QLabel *label_errorInfo;
	QLabel *label_cameraInfo;
	QLabel *label_realCameraInfo;
	QLabel *label_queueInfo1;
	QLabel *label_queueInfo2;

	QTimer	*timerUpdateDebugInfo;
};

#endif // WIDGET_DEBUG_H
