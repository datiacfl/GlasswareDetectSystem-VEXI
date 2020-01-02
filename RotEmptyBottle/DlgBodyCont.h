#ifndef DLGBODYCONT_H
#define DLGBODYCONT_H

#include "CItemDlg.h"
#include "ui_DlgBodyCont.h"

class CDlgBodyCont : public CItemDlg
{
	Q_OBJECT

public:
	CDlgBodyCont(QWidget *parent,QVariant *pCheckPara,QVariant *pCheckShape);
	~CDlgBodyCont();
	void autoAccept();

private slots:
	void accept();
	void apply();
	void drawReg();
private:
	Ui::CDlgBodyCont ui;
	void initDialog();
	void setHelpTips();
};

#endif // DLGBODYCONT_H
