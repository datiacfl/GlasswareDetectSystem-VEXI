#ifndef DLGSBRISPOTREG_H
#define DLGSBRISPOTREG_H

#include "CItemDlg.h"
#include "ui_DlgSBriSpotReg.h"

class CDlgSBriSpotReg : public CItemDlg
{
	Q_OBJECT

public:
	CDlgSBriSpotReg(QWidget *parent,QVariant *pCheckPara,QVariant *pCheckShape);
	~CDlgSBriSpotReg();
	void autoAccept();

private slots:
	void accept();
	void apply();
	void drawReg();
	void ResetReg();
	void typeChanged(int index);

private:
	Ui::CDlgSBriSpotReg ui;
	void initDialog();
	void setHelpTips();

};

#endif // DLGSBRISPOTREG_H
