#ifndef DLGBINREG_H
#define DLGBINREG_H

#include "CItemDlg.h"
#include "ui_DlgBInReg.h"

class CDlgBInReg : public CItemDlg
{
	Q_OBJECT

public:
	CDlgBInReg(QWidget *parent,QVariant *pCheckPara,QVariant *pCheckShape);
	~CDlgBInReg();
	void autoAccept();
private slots:
	void accept();	
	void apply();
	void methodChanged(int index);
	void drawInCircle();
	void drawOutCircle();
	void autodraw();
	void drawMark();
	void drawPolyShape();
	void ResetBaseShape();
	void drawChar();
	void enableMark();
	void fbtnBinRegExp_Def();
private:
	Ui::CDlgBInReg ui;
	void initDialog();
	void setHelpTips();
};

#endif // DLGBINREG_H
