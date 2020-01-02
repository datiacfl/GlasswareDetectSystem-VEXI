#ifndef CDLGHORISIZE_H
#define CDLGHORISIZE_H

#include "CItemDlg.h"
#include "ui_DlgHoriSize.h"

class CDlgHoriSize : public CItemDlg
{
	Q_OBJECT

public:
	CDlgHoriSize(QWidget *parent,QVariant *pCheckPara,QVariant *pCheckShape);
	~CDlgHoriSize();
	void autoAccept();

private slots:
	void accept();	
	void apply();
	void calibRuler();
	void drawSizeRect();
	void changeGroupName(int index);
private:
	Ui::CDlgHoriSize ui;
	void initDialog();
	void setHelpTips();
};

#endif // CDLGHORISIZE_H
