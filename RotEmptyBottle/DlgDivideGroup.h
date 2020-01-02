#ifndef CDLGDIVIDEGROUP_H
#define CDLGDIVIDEGROUP_H

#include <QDialog>
#include "ui_DlgDivideGroup.h"
#include "DlgCopyModel.h"
class CDlgDivideGroup : public QDialog
{
	Q_OBJECT

public:
	CDlgDivideGroup(QWidget *parent = 0);
	~CDlgDivideGroup();

	QVector <int> vGroup1;
	QVector <int> vGroup2;
	QVector <int> vGroup3;
	QVector <int> vGroup4;
	QVector <int> vNoGroup;
	int nCurGroup;
private slots:
	void accept();
	void curGroupChanged(int nIndex);
	void clickLeft();
	void clickRight();
	void curGroupClicked();
	void noGroupClicked();
	
private:
	Ui::DlgDivideGroup ui;
	void initDialog();
	void setHelpTips(); 
	CDlgCopyModel *pParent;
};

#endif // CDLGDIVIDEGROUP_H
