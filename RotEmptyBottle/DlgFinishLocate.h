#ifndef DLGFINISHLOCATE_H
#define DLGFINISHLOCATE_H

#include "CItemDlg.h"
#include "ui_DlgFinishLocate.h"

class CDlgFinishLocate : public CItemDlg
{
	Q_OBJECT

public:
	CDlgFinishLocate(QWidget *parent,QVariant *pCheckPara,QVariant *pCheckShape);
	~CDlgFinishLocate();
	void autoAccept();

private slots:
	void accept();
	void apply();
	void methodChanged(int index);
	void drawOutRing();
	void drawInRing();
private:
	Ui::CDlgFinishLocate ui;	
	void initDialog();
	void setHelpTips();
};

#endif // DLGFINISHLOCATE_H
