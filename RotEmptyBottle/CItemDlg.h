#ifndef CITEMDLG_H
#define CITEMDLG_H
//�����Ի���Ļ��࣬����ά��һЩͨ�����Ժ���Ϊ
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
	CDlgMainWindow *pDlgMainWnd;//������ָ��
	MyLabelItem *pLabelItem;//�����ָ��
	QVariant *pPara;//��������ָ��
	QVariant *pShape;//�������״ָ��	
	QPushButton *pBtnOK;		//ȷ��
	QPushButton *pBtnCancle;	//ȡ��
	QPushButton *pBtnApply;		//Ӧ��
public:
	void addCtrLayout();		//����ȷ��ȡ����Ӧ��
	void setDlgSize();			//���ô�С
protected:
	void closeEvent(QCloseEvent *event);
	
private slots://ȷ��
	virtual void accept() = 0;
	virtual void apply() = 0;
};

#endif // CITEMDLG_H
