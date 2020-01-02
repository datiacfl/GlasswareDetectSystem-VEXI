#ifndef TESTWIDGET_H
#define TESTWIDGET_H

#include <QWidget>
#include <QTimer>
#include <QButtonGroup>  //QT 5.12.6 update
#include <QTextCodec>  //QT 5.12.6 update
#include "widget_sample.h"
#include "widget_errortype.h"
#include "widget_camera.h"
#include "ui_widget_test.h"

// 

class WidgetTest : public QWidget
{
	Q_OBJECT

public:

	WidgetTest(QWidget *parent = 0);
	~WidgetTest();
	Ui::WidgetTest ui;

	Widget_Sample *widget_Sample;
	Widget_ErrorType *widget_ErrorType;
	Widget_Camera *widget_Camera;
	QList<QCheckBox *> listCheckBoxErrorType;
	QList<QSpinBox *> listSpinboxStatisMaxNumber;
	QList<QSpinBox *> listSpinboxStatisMaxTime;
public:
	void init();
	void initWidgetName();
	bool leaveWidget();
	void updateIOCardParam();
	void getIOCardParam();
	void updateIOCardParamVEXI();
	void getIOCardParamVEXI();

//	void InitIOCardInfo();
	void initInformation();
	
	void ShowAssert(int);
signals:
	void signals_changeStatisMode(int iStatisMode,int iMinute,int iStatisNumber);
	void signals_ReadDistance1();
	void signals_ReadDistance2();
	void signals_sendAlarm(int warningType, QString warningInfo);
public:
	double GetMinKickOutRate() {return ui.doubleSpinBox->value();}
	double GetMaxKickOutRate() {return ui.doubleSpinBox_2->value();}
	QString GetKickOutInterval() {return ui.spinBox->text();}
	QString CompareDoubleString(QString);
public slots:
	void slots_intoWidget();

	void slots_ChoseCamera();
	void slots_ChoseErrorType();
	void slots_OKSave();
	void slots_OKStatis();
	void slots_OKCameraSurveillance();

	void slots_OK();
	void slots_Cancel();
	void slots_KickModeChanged(int iMode);
	void slots_KickModeChanged2(int iMode);
	void slots_KickModeChangedVEXI(int iMode);
	void slots_setIOCard1OutPut(int ComNo);
	void slots_setIOCard2OutPut(int ComNo);
	void slots_SaveModeChanged(int index);
	void slots_StatisModeChanged(int index);

	void slots_readDelay();
	void slots_setToCard();
	void slots_setToFile();
	void slots_setToCard1();
	void slots_setToCard2();
	void slots_setToFile1();
	void slots_setToFile2();

	void slots_readIOCard1Distance();
	void slots_readIOCard2Distance();
	void slots_advance1();
	void slots_advance2();
	//void slots_setToCard1();
	//void slots_setToCard2();
	//void slots_setToFile1();
	//void slots_setToFile2();

	void slots_choseAllCamera();
	void slots_choseNoneCamera();
	void slots_choseAllErrorType();
	void slots_choseNoneErrorType();
	void slots_ShowErrorType();

	void slots_updateIOcardCounter();
	//void slots_updatePLCCounter(int iCounter);
	void slots_VEXIIOCardSet();
	void slots_VEXIIOCardSave();
	void slots_VEXIIOCardAdvance();
	void slots_VEXIIOCardCancel();
	void slots_CheckIsSendKickOut();
	void slots_onStateChanged(int);
	void CloseAssert();
private:
	void saveSampleInfo();
	
private:
	int iSaveMode;
	int iLastSaveMode;
	int iKickMode;
	int iKickMode2;
	int iLastKickMode;
	int iLastKickMode2;
	int iSaveImgCount;
	int iLastSaveImgCount;
	int bIsShowStatisErrorType;
	int iStatisMode;
	//int iIsTrackErrorType;
	
	int iMinute;
	int iStatisNumber;
	
// 	int iLastStatisMode;
// 	int iLastIsTrackErrorType[ERRORTYPE_MAX_COUNT];
// 	int iLastMinute;
// 	int iLastStatisNumber;
// 	int iLastStatisMaxRate;
// 	int iLastStatisMinRate;

	int iChoseCamera;
	int iChoseErrorType;

	int m_nDistinct1to4;
	int m_nDistinct4to5;
	int m_nDistinct2to3;
	int m_nDistinct3to4;
	int m_nDelay1;
	int m_nDelay2;
	int m_nDelay3;
	int m_nDelay4;
	int m_nDelay5;
	int m_nDelay6;
	int m_nDelay7;
	int m_nDelay8;

	int m_nKickDelay;
	int m_nKickWidth;
	int m_nSampleDelay;
	int m_nSampleWidth;

	s_VEXIIOCardInfo sVEXIIOCardInfo;

	QTimer* timerUpdateIOCardCounter;

	double MaxRate;
	double MinRate;
	int resultTime;
public:
	QTimer* kickOutTimer;
	int m_lastAllNumber;
	QCheckBox* checkBoxAll;
	int iStatisMaxTime[ERRORTYPE_MAX_COUNT];
	int iStatisMaxNumber[ERRORTYPE_MAX_COUNT];
	int iIsTrackErrorType[ERRORTYPE_MAX_COUNT];	
};

#endif // TESTWIDGET_H