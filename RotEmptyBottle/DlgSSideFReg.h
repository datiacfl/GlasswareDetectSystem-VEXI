#ifndef DLGSSIDEFREG_H
#define DLGSSIDEFREG_H

#include "CItemDlg.h"
#include "ui_DlgSSideFReg.h"

class CDlgSSideFReg : public CItemDlg
{
	Q_OBJECT

public:
	CDlgSSideFReg(QWidget *parent,QVariant *pCheckPara,QVariant *pCheckShape);
	~CDlgSSideFReg();
	void autoAccept();

private slots:
	void accept();
	void apply();
	void expandDlg();
	void drawReg();
	void ResetReg();
	void typeChanged(int index);
private:
	Ui::CDlgSSideFReg ui;
	void initDialog();
	void setHelpTips();
};

#endif // DLGSSIDEFREG_H
