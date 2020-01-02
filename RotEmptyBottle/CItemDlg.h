#ifndef CITEMDLG_H
#define CITEMDLG_H
//检测项对话框的基类，用于维护一些通用属性和行为
#include <QDialog>
#include <QVariant>
#include <QWhatsThis>
#include "DlgMainWindow.h"
#include "check.h"
class CItemDlg : public QDialog
{
	Q_OBJECT

public:
	CItemDlg(QWidget *parent,QVariant *pCheckPara,QVariant *pCheckShape);
	~CItemDlg();
	CDlgMainWindow *pDlgMainWnd;//主窗口指针
	MyLabelItem *pLabelItem;//检测项指针
	QVariant *pPara;//检测项参数指针
	QVariant *pShape;//检测项形状指针	
	QPushButton *pBtnOK;		//确定
	QPushButton *pBtnCancle;	//取消
	QPushButton *pBtnApply;		//应用
public:
	void addCtrLayout();		//增加确定取消、应用
	void setDlgSize();			//设置大小
protected:
	void closeEvent(QCloseEvent *event);
	
private slots://确定
	virtual void accept() = 0;
	virtual void apply() = 0;
};

#endif // CITEMDLG_H
