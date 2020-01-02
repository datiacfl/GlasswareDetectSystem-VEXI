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

//QTϵͳ����
#define DAHENGBLPKP_QT			//QTϵͳʱ��������ͣ�����ע�͵�

extern int g_nAlgType;

// ��ǰ������ [7/24/2015 zhaodt]
class CCheck;
/**
*s_OpenOutImg�ṹ�����ڴ������Ա����ļ�����ͼ�����Ϣ
**/
typedef struct _sOpenLocalImg
{
	bool bOpenImg;//�Ƿ�����ⲿͼ��
	int nCurIndex;//��ǰͼ�����ļ��������
	vector <QString> vAllNames;//��ǰ�ļ���������ͼ��ȫ·��
	
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
	bool init(QWidget *parent = NULL);  //2017.5---��ʼ��ʧ��ʱ���ش���
	void initToolBar();
	void initStatusBar();
	void enableButtons(bool bFlag);
	void writeAlgLog1(char *acLoginfo);
	//2013.9.6 nanjc ������ʾ�������޸Ķ�λ��������
	void displayObject(int iMethodIdx = -1);
	void displayRoiHighLight(int nID,QVariant &vModelPara,QVariant &vModelShape); //2017.11---ѡ��ĳ�������ʱ����Ӧ�ļ�����������ʾ
	bool ModeChanged();
	bool tryClose();
	void translateUi();
	QWidget* paramWidget();//���ز�������widget
	// ���ð�ť״̬ [7/31/2015 zhaodt]
	void setBtnStatus();
	// ���ÿؼ�ע����Ϣ
	void setCtrlTips();
	// �ж�ĳ�������Ƿ�ѡ��
	void judgeObjStatus(int nPressRow, int nPressCol);
public:	
	//ͼ��
	//2013.9.22 nanjc ����Ӧ��ͼ��λ��ƿ��Բ��&����
	//�ڲ����Զ���ָ��
	CCheck *pChecker;
	//�ⲿ������ָ��
	CCheck *pCheckerReal;
	//�Ƿ��ڻ�ͼ״̬
	bool m_bDrawing;
	//�����Ի���ָ��
	QDialog *pItemDlg;
	//��ǰѡ�еļ����ָ��
	QWidget *pItemLabel;
	//�ߴ��ۺ�-�ߴ�������
	QVector <QString> m_vSizeGroupName;		

	//�رնԻ�����ʾ
	QString strCloseWindow;
	//�����ʹ�ܿ���
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
	void setWndScale(bool bRefresh = true,float fScale = 1.0);//�趨���ڱ���
	void changeCamIndex(int index);	
	void changeLanguage(int index);
	//����ʱ���¼�,���ⲿ���������ʾ����ֹͣʱ��������Դ��ڰ�ť
	void checkStopStatus();
	//����ģ��
	void saveModel();
	//����ģ��
	void exportModel();
	//����ģ��
	void importModel();
	//����ģ��
	void copyModel();
	//������
	void checkTest();
	
private:	
	//���ݲ�ͬ�㷨����������ͬ����
	//�����ļ�
	QTranslator *translator;
	//ͼ����Ϣ
	int nImgWidth;
	int nImgHeight;
	int nImgChannel;
	char *cImgData;
	//check �������
	s_AlgCInP sAlgCInp;

	//���ڱ���
	float fWndScale;
	int nWndScale;
	int nLangIndex;
	//�����ڴ�С
	int nParentWndWidth;
	int nParentWndHeight;
	//�������߶�
	int nTittleHeight;
	//���Ա���ͼ�����Ϣ
	s_OpenLocalImg sOpenLocalImg;
	bool bShowShape;//true:��ʾ��״ false:��ʾԭͼ
	bool bMeasure;//true:����״̬
	bool bDistDone;//true:��ɲ������ȴ��ر�
	bool bReadNewModel;//�Ƿ���ģ��
	//ͼ�����ñ�ʶ��
	bool bResetFlag;
	//��ʱ��
//	QTimer *timer ;
	//����ؼ�
	QComboBox *comboWndScale;
	QLabel *labelWndScale;
	QComboBox *comboCamIndex;
	QLabel *labelCamIndex;
	QComboBox *comboLanguage;
	QLabel *labelLanguage;
	QLabel *labelVisionName;
	QLabel *labelVision;
};

