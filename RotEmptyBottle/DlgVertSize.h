#ifndef CDLGVERTSIZE_H
#define CDLGVERTSIZE_H

#include "CItemDlg.h"
#include "ui_DlgVertSize.h"

class CDlgVertSize : public CItemDlg
{
	Q_OBJECT

public:
	CDlgVertSize(QWidget *parent,QVariant *pCheckPara,QVariant *pCheckShape);
	~CDlgVertSize();
	void autoAccept();
	
private slots:
	void accept();	
	void apply();
	void calibRuler();
	void drawSizeRect();
	void changeGroupName(int index);
private:
	Ui::CDlgVertSize ui;
	void initDialog();
	void setHelpTips();
};

#endif // CDLGVERTSIZE_H
