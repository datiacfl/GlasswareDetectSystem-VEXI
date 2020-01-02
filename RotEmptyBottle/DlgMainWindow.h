#pragma once
#include <QtGui/QMainWindow>
#include <QtGui/QComboBox>
#include <QtGui/QLabel>
#include <QtGui/QActionGroup>
#include <QtGui/QLayout>
#include <QtGui/QMessageBox>
#include <QtGui/QFileDialog>
#include <QtGui/QPainter>
#include <QtGui/QCloseEvent>
#include <QTimer>
#include <QTranslator>

//QT系统类型
#define DAHENGBLPKP_QT			//QT系统时定义该类型，否则注释掉

extern int g_nAlgType;

// 类前置声明 [7/24/2015 zhaodt]
class CCheck;
/**
*s_OpenOutImg结构体用于存贮调试本地文件夹内图像的信息
**/
typedef struct _sOpenLocalImg
{
	bool bOpenImg;//是否打开了外部图像
	int nCurIndex;//当前图像在文件夹内序号
	vector <QString> vAllNames;//当前文件夹内所有图像全路径
	
	_sOpenLocalImg()
	{
		bOpenImg = false;
	}
}s_OpenLocalImg;

class CDlgMainWindow :
	public QMainWindow
{
	Q_OBJECT
public:
	CDlgMainWindow(s_AlgModelPara &imgData);
public:
	//void init(QWidget *parent = NULL);
	bool init(QWidget *parent = NULL);  //2017.5---初始化失败时返回错误
	void initToolBar();
	void initStatusBar();
	void enableButtons(bool bFlag);
	void writeAlgLog1(char *acLoginfo);
	//2013.9.6 nanjc 重载显示方法，修改定位部分内容
	void displayObject(int iMethodIdx = -1);
	void displayRoiHighLight(int nID,QVariant &vModelPara,QVariant &vModelShape); //2017.11---选中某个检测项时，对应的检测区域高亮显示
	bool ModeChanged();
	bool tryClose();
	void translateUi();
	QWidget* paramWidget();//返回参数设置widget
	// 设置按钮状态 [7/31/2015 zhaodt]
	void setBtnStatus();
	// 设置控件注释信息
	void setCtrlTips();
	// 判断某个区域是否选中
	void judgeObjStatus(int nPressRow, int nPressCol);
public:	
	//图像
	//2013.9.22 nanjc 用于应力图像定位，瓶子圆心&轮廓
	//内部调试对象指针
	CCheck *pChecker;
	//外部检测对象指针
	CCheck *pCheckerReal;
	//是否处于画图状态
	bool m_bDrawing;
	//检测项对话框指针
	QDialog *pItemDlg;
	//当前选中的检测项指针
	QWidget *pItemLabel;
	//尺寸综合-尺寸组名称
	QVector <QString> m_vSizeGroupName;		

	//关闭对话框提示
	QString strCloseWindow;
	//检测项使能开关
	bool m_bEnableItem;

protected:
	void closeEvent(QCloseEvent *event);
	void moveEvent(QMoveEvent *event);
	void wheelEvent(QWheelEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
private slots:
	void openImg();
	void saveImg();
	void prevImg();
	void nextImg();
	void oriImg();
	void drawImg();
	void resetShape();
	void measureImg();
	void continueShow();
	void stopAtError();
	void changeWndScale(int index,bool bRefresh = true);
	void setWndScale(bool bRefresh = true,float fScale = 1.0);//设定窗口比例
	void changeCamIndex(int index);	
	void changeLanguage(int index);
	//处理定时器事件,当外部检测连续显示遇错停止时，弹起调试窗口按钮
	void checkStopStatus();
	//保存模板
	void saveModel();
	//导出模板
	void exportModel();
	//导入模板
	void importModel();
	//复制模板
	void copyModel();
	//检测测试
	void checkTest();
	
private:	
	//根据不同算法类型启动不同界面
	//翻译文件
	QTranslator *translator;
	//图像信息
	int nImgWidth;
	int nImgHeight;
	int nImgChannel;
	char *cImgData;
	//check 输入参数
	s_AlgCInP sAlgCInp;

	//窗口比例
	float fWndScale;
	int nWndScale;
	int nLangIndex;
	//父窗口大小
	int nParentWndWidth;
	int nParentWndHeight;
	//标题栏高度
	int nTittleHeight;
	//调试本地图像的信息
	s_OpenLocalImg sOpenLocalImg;
	bool bShowShape;//true:显示形状 false:显示原图
	bool bMeasure;//true:测量状态
	bool bDistDone;//true:完成测量，等待关闭
	bool bReadNewModel;//是否导入模板
	//图形重置标识符
	bool bResetFlag;
	//定时器
//	QTimer *timer ;
	//各类控件
	QComboBox *comboWndScale;
	QLabel *labelWndScale;
	QComboBox *comboCamIndex;
	QLabel *labelCamIndex;
	QComboBox *comboLanguage;
	QLabel *labelLanguage;
	QLabel *labelVisionName;
	QLabel *labelVision;
};

