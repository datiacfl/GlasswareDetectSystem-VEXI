#ifndef DLGCOPYMODEL_H
#define DLGCOPYMODEL_H

#include <QDialog>
#include "ui_DlgCopyModel.h"
#include <QVector>
#include <QCheckBox>

class CCheck;
class CDlgCopyModel : public QDialog
{
	Q_OBJECT

public:
	CDlgCopyModel(QWidget *parent = 0);
	~CDlgCopyModel();
	CCheck *pChecker;

	int nCurGroup;//当前属于哪个分组
	QVector <int> vGroup1;
	QVector <int> vGroup2;
	QVector <int> vGroup3;
	QVector <int> vGroup4;
	QVector <int> vNoGroup;

private:
	QList<QCheckBox *> CheckBox_list;			//工具按钮列表
	int iCheckItemsCols;						//分3列显示检测项
private slots:
	void divideGroups();
	void GroupChanged(bool checked);
	void CopyChanged(bool checked);
	void startCopy();

private:
	Ui::CDlgCopyModel ui;
	bool checkConfig();
	void checkGroup();
	void initDialog();
	void setHelpTips();

};

#endif // DLGCOPYMODEL_H
