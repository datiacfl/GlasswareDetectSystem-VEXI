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
	QVector<MyLabelItem *> vItemLabels;//检测项标签
	bool bAllItemsChange;//标识符，为真表示全部items要重存
	void writeLogFile(QString str);
	void initItems(bool bRefresh = true);//初始化当前检测流程中的检测项
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
	CDlgCheckItemWizard *dlgWizard;//检测项添加向导对话框

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
	void readSaveNames(int nID, QVariant *pPara, QString &strName, bool bFlag = true);//bFlag: true=读, false=写
	void readSaveStatus(int nID, QVariant *pPara, bool &bStatus, bool bFlag = true);//bFlag: true=读, false=写
	
public:
	int nOnMouseItem;//鼠标右键时选中的检测项索引,用于配置和删除
	int nRightMouseItem;//在鼠标右键点击时，右边的检测项索引，用于在其前面插入
	bool bItemClicked;

	//2017.2---用于右键复制和粘贴
	int tempID;
	QString tempStrName;
	QVariant paraTemp;
	QVariant shapeTemp;

private://2014.6.21 增加纵向显示
	int iShowType;	//显示类型0:横向显示 1:纵向显示
};

#endif // MYGROUPBOXPROCESS_H
