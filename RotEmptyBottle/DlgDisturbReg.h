#ifndef DLGDSITURBREG_H
#define DLGDSITURBREG_H

#include "CItemDlg.h"
#include "ui_DlgDisturbReg.h"

class CDlgDisturbReg : public CItemDlg
{
	Q_OBJECT

public:
	CDlgDisturbReg(QWidget *parent,QVariant *pCheckPara,QVariant *pCheckShape);
	~CDlgDisturbReg();
	void autoAccept();

private slots:
	void accept();
	void apply();
	void typeChanged(int index);
	void typeShapeChanged(int index);
	void drawDistReg();
	void PickUpReg();
	void ResetReg();

private:
	Ui::CDlgDisturbReg ui;
	void initDialog();
	void setHelpTips();
};

#endif // DLGDSITURBREG_H
