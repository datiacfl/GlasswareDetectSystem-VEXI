#ifndef DLGSSCREWFREG_H
#define DLGSSCREWFREG_H

#include "CItemDlg.h"
#include "ui_DlgSScrewFReg.h"

class CDlgSScrewFReg : public CItemDlg
{
	Q_OBJECT

public:
	CDlgSScrewFReg(QWidget *parent,QVariant *pCheckPara,QVariant *pCheckShape);
	~CDlgSScrewFReg();
	void autoAccept();

private slots:
	void apply();
	void accept();	
	void drawReg();
	void ResetReg();
	void typeChanged(int index);
private:
	Ui::CDlgSScrewFReg ui;
	void initDialog();
	void setHelpTips();
};

#endif // DLGSSCREWFREG_H
