#ifndef DLGFBLINREG_H
#define DLGFBLINREG_H

#include "CItemDlg.h"
#include "ui_DlgFBLInReg.h"

class CDlgFBLInReg : public CItemDlg
{
	Q_OBJECT

public:
	CDlgFBLInReg(QWidget *parent,QVariant *pCheckPara,QVariant *pCheckShape);
	~CDlgFBLInReg();
	void autoAccept();

private slots:
	void accept();	
	void apply();
	void drawOutCircle();
	void drawInCircle();
	void drawPolygon(); 
private:
	Ui::CDlgFBLInReg ui;
	void initDialog();
	void setHelpTips();
};

#endif // DLGFBLINREG_H
