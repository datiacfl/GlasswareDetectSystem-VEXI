#include "dhbasewidget.h"
#include <QPainter>
#include <QStyleOption>

DHBaseWidget::DHBaseWidget(QWidget *parent)
	: QWidget(parent)
{
//	layouttopmargin;
// 	QFont font;
// 	font.setPointSize(15);
// 	setFont(font);

	setAutoFillBackground(true);
	QPalette palette;
//	palette.setColor(QPalette::Background, QColor(90,90,90,120));
	//palette.setBrush(QPalette::Background, QBrush(QPixmap(":/background.png")));
	setPalette(palette);

	widgetName = new QLabel(this);
	widgetName->setObjectName("whiteLabel");
	widgetName->setText("");
	widgetName->setMaximumHeight(25);
	widgetName->setMinimumHeight(25);
//	widgetName->move(5,0);

	widgetColor = new QColor(90,90,90,255);
}

DHBaseWidget::~DHBaseWidget()
{

}
void DHBaseWidget::paintEvent(QPaintEvent *event)
{
	QStyleOption opt;
	opt.init(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);

	QWidget::paintEvent(event);

	QPainter painter(this);
 	painter.setPen(Qt::NoPen);
	int iHeight = widgetName->geometry().height();
	QLinearGradient linearGradient(0, 0, 0, iHeight); 
	linearGradient.setColorAt(0.3, QColor(widgetColor->red(),widgetColor->green(),widgetColor->blue(),widgetColor->alpha())); 
	linearGradient.setColorAt(1.0,  QColor(20,20,20,200)); 
	painter.setBrush(QBrush(linearGradient)); 
	painter.drawRect(QRect(0, 0, this->width(), iHeight));

	painter.drawText(QPoint(0, 0), widgetName->text());
}
void DHBaseWidget::setWidgetName(QString str)
{
	widgetName->setText(" "+ str);
//	widgetName->move(5,0);

	update();
}
void DHBaseWidget::setWidgetNameColor(QColor color)
{
	widgetColor->setRed(color.red());
	widgetColor->setGreen(color.green());
	widgetColor->setBlue(color.blue());
	widgetColor->setAlpha(color.alpha());

	QPalette palette;
	palette.setColor(QPalette::Background,QColor(color.red(),color.green(),color.blue(),120));
	//palette.setBrush(QPalette::Background, QBrush(QPixmap(":/background.png")));
	setPalette(palette);

	update();
}
void DHBaseWidget::setWidgetFont(QFont font)
{
	setFont(font);
}
