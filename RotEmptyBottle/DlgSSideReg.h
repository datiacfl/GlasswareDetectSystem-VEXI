#ifndef DLGSSIDEREG_H
#define DLGSSIDEREG_H

#include "CItemDlg.h"
#include "ui_DlgSSideReg.h"

class CDlgSSideReg : public CItemDlg
{
	Q_OBJECT

public:
	CDlgSSideReg(QWidget *parent,QVariant *pCheckPara,QVariant *pCheckShape);
	~CDlgSSideReg();
	void autoAccept();

private slots:
	void apply();
	void accept();	
	void drawReg();
	void ResetReg();
	void typeChanged(int index);
	void beStone();
	void beCrack();
private:
	Ui::CDlgSSideReg ui;
	void initDialog();
	void setHelpTips();
};

#endif // DLGSSIDEREG_H
