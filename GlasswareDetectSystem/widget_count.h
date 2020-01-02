#ifndef WIDGET_COUNT_H
#define WIDGET_COUNT_H

#include <QWidget>
#include <QStackedWidget>
#include <QTableView>
#include <QScrollArea>
#include <QStandardItemModel>
#include <QPlainTextEdit>
#include <QMutex>
#include <QTimer>
#include <QTime>
#include <QFile>
// #include "ui_widget_count.h"

#include "stateTool.h"
#include "countset.h"
#include "qexcel.h"
/*#include "MyLogText.h"*/
#include<windows.h>
#include<tlhelp32.h>
#include<comdef.h>

class Widget_Count : public QWidget
{
	Q_OBJECT

public:
	Widget_Count(QWidget *parent = 0);
	~Widget_Count();


public:
	bool leaveWidget();
	void writeCountInfo(QFile *fileCount);
	void upDateListInfo();
	void openInNotePad(QString str);
	void InsertLastCountInfo();
	bool SaveCountInfoByTime();
	void ClearAllData();
	DWORD GetProcessIdFromName(const char*processName)   ;
public slots:
	bool slots_intoWidget();
	bool slots_SaveCountInfo();
	bool slots_SaveALLCountInfo();
private slots:
	void slots_timerClearCountInfo();
	void slots_OpenRecord();
	void slots_DeleteRecord();
	bool slots_SaveCountHourInfoBytime();
	bool slots_ClearCountInfo();
	void slots_saveRecordOK();
	void slots_saveRecordCancel();
	void slots_shiftOK();
	void slots_shiftCancel();
	void slots_turn();
	void slots_updateInfo();
	bool slots_InsertCountCameraInfo();
	bool slots_InsertCountHourInfo();	
public:
	CountSet *widgetCountSet;
	QPushButton *buttonTurn;
	QStackedWidget *pStackedCount;
	QPlainTextEdit *recordText;
private:
	QMutex m_mutexmAddRow;						//操作互斥
	QTableView *m_ListCountWidget;				//统计总数
	QTableView *m_ListhourWidget;				//每小时统计计数
	QTableView *m_ListCameraWidget;				//每小时统计计数
	QWidget *listWidget;
	QWidget *recordWidget;
	QScrollArea *scrollArea;

	QStandardItemModel *m_modelCount;			//错误数据模板
	QStandardItemModel *m_modelHour;			//错误数据模板
	QStandardItemModel *m_modelCamera;			//错误数据模板

	int iIfShown[ERRORTYPE_MAX_COUNT];
	int iListOrder[ERRORTYPE_MAX_COUNT];		//对应缺陷在表中顺序
	int m_nTimerId;
	QMutex QListCount;
//	QTimer *timerSaveRecord;
public:
	int m_iErrorCamCount[CAMERA_MAX_COUNT];// 每个相机的错误计数
	int m_iHourErrorCamCount[CAMERA_MAX_COUNT];// 每个相机的错误计数
	int m_iLastErrorCamCount[CAMERA_MAX_COUNT];// 上一小时每个相机的错误计数
	int m_iErrorTypeCount[ERRORTYPE_MAX_COUNT];//每个错误类型的错误计数
	cErrorTypeInfo m_cErrorTypeInfo[CAMERA_MAX_COUNT];//统计错误信息

	QTimer *timerSaveHourList;
	bool m_bIsErrorHour[24];//对应小时是否保存
	QTime m_timeByhour[24];
	int m_iErrorHour[24][ERRORTYPE_MAX_COUNT];//存储按时间的统计报表
	//
	bool bSaveRecord;
	int iSaveRecordInterval;
	//
	bool bAutoSetZero;
	QTime shift1;
	QTime shift2;
	QTime shift3;

	bool isClear1;
	bool isClear2;
	bool isClear3;
	bool bIsAutoSetZero;

	bool isSaved;
	bool isSavedHourInfo;
private:
//	Ui::Widget_Count ui;
	void init();
	//bool InsertCountCameraInfo();
	//bool InsertCountHourInfo();	
	bool SaveCountCameraInfo();	
	bool SaveCountHourInfo();	

	int nLastCheckedNum;
	int nLastFailureNumFromIOcard;
	int nLastErrorCamCount[CAMERA_MAX_COUNT];
	int nLastErrorTypeCount[ERRORTYPE_MAX_COUNT];//每个错误类型的错误计数
	double nLastErrorCamRate[CAMERA_MAX_COUNT];// 每个相机的错误计数
	cErrorTypeInfo nLastErrorTypeInfo[CAMERA_MAX_COUNT];//统计错误信息

	int nTempCheckedNum;
	int nTempFailureNumFromIOcard;
	int nTempErrorCamCount[CAMERA_MAX_COUNT];
	int nTempErrorTypeCount[ERRORTYPE_MAX_COUNT];//每个错误类型的错误计数
	double nTempErrorCamRate[CAMERA_MAX_COUNT];// 每个相机的错误计数
	cErrorTypeInfo nTempErrorTypeInfo[CAMERA_MAX_COUNT];//统计错误信息
};

#endif // WIDGET_COUNT_H
