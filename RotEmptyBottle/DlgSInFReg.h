#ifndef DLGSINFREG_H
#define DLGSINFREG_H

#include "CItemDlg.h"
#include "ui_DlgSInFReg.h"

class CDlgSInFReg : public CItemDlg
{
	Q_OBJECT

public:
	CDlgSInFReg(QWidget *parent,QVariant *pCheckPara,QVariant *pCheckShape);
	~CDlgSInFReg();
	void autoAccept();

private slots:
	void accept();	
	void apply();
	void drawReg();
	void ResetReg();
private:
	Ui::CDlgSInFReg ui;
	void initDialog();
	void setHelpTips();
};

#endif // DLGSINFREG_H
