#ifndef WIDGET_SAMPLE_H
#define WIDGET_SAMPLE_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <QPushButton>
#include <QSignalMapper>
#include "dhbasewidget.h"
#include "ConfigInfo.h"

class Widget_Sample : public DHBaseWidget
{
	Q_OBJECT

public:
	Widget_Sample(QWidget *parent = 0);
	~Widget_Sample();

	void recoverChanged(){bIsChanged = false;}
	void setChanged(){bIsChanged = true;}
	bool isChanged(){return bIsChanged;}
	void initail();
	void setSimpleCount(int iSimpleCount);

	QLabel *label_sampleCount;
	QPushButton *button_OK;
	QLineEdit *lineEdit_sampleCount;
	s_SampleInfo sSampleInfo;
	bool bIsChanged;
	QList<QCheckBox*> listCheckBox;
	QSignalMapper *signalmapper;
public slots:
 	void changeCheckState(int);
	void changeSimpleCount();

private:
};

#endif // WIDGET_SAMPLE_H
