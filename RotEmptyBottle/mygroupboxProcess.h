#ifndef MYGROUPBOXPROCESS_H
#define MYGROUPBOXPROCESS_H

#include <QGroupBox>
#include <QAction>
#include <QMenu>
#include <QVector>
#include "DlgCheckItemWizard.h"
#include "mylabelitem.h"
#include "check.h"

class MyGroupBoxProcess : public QGroupBox
{
	Q_OBJECT

public:
	MyGroupBoxProcess(QWidget *parent);
	~MyGroupBoxProcess();

	CCheck *pChecker;
	QVector<MyLabelItem *> vItemLabels;//������ǩ
	bool bAllItemsChange;//��ʶ����Ϊ���ʾȫ��itemsҪ�ش�
	void writeLogFile(QString str);
	void initItems(bool bRefresh = true);//��ʼ����ǰ��������еļ����
protected:
	void contextMenuEvent(QContextMenuEvent *event);
	void mousePressEvent(QMouseEvent *event);
private:
	QAction *addAction;
	QAction *insertAction;
	QAction *renameAction;
	QAction *deleteAction;
	QAction *copyitemAction;
	QAction *pasteitemAction;
	QMenu *contextMenu;
	CDlgCheckItemWizard *dlgWizard;//���������򵼶Ի���

public slots:
	void showItems();
	void addItem();
	void insertItem();
	void renameItem();
	void deleteItem();
	void copyItem();
	void pasteItem();
	void enableItem();

public:
	void createActions();
	void updateItemDlg(MyLabelItem *pLabelItem);
	void applyItemDlg(MyLabelItem *pLabelItem);
	void judgeName(QString &strName);
	void readSaveNames(int nID, QVariant *pPara, QString &strName, bool bFlag = true);//bFlag: true=��, false=д
	void readSaveStatus(int nID, QVariant *pPara, bool &bStatus, bool bFlag = true);//bFlag: true=��, false=д
	
public:
	int nOnMouseItem;//����Ҽ�ʱѡ�еļ��������,�������ú�ɾ��
	int nRightMouseItem;//������Ҽ����ʱ���ұߵļ������������������ǰ�����
	bool bItemClicked;

	//2017.2---�����Ҽ����ƺ�ճ��
	int tempID;
	QString tempStrName;
	QVariant paraTemp;
	QVariant shapeTemp;

private://2014.6.21 ����������ʾ
	int iShowType;	//��ʾ����0:������ʾ 1:������ʾ
};

#endif // MYGROUPBOXPROCESS_H
