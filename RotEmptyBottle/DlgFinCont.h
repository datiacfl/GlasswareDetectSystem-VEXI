#ifndef DLGFINCONT_H
#define DLGFINCONT_H

#include "CItemDlg.h"
#include "ui_DlgFinCont.h"

class CDlgFinCont : public CItemDlg
{
	Q_OBJECT

public:
	CDlgFinCont(QWidget *parent,QVariant *pCheckPara,QVariant *pCheckShape);
	~CDlgFinCont();
	void autoAccept();

private slots:
	void accept();
	void apply();

private:
	Ui::CDlgFinCont ui;
	void initDialog();
	void setHelpTips();
};

#endif // DLGFINCONT_H
