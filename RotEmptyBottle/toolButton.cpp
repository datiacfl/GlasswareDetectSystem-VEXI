#include "toolButton.h"

ToolButton::ToolButton(QString pic_name, QWidget *parent)
	:QToolButton(parent)
{
	//�����ı���ɫ
	QPalette text_palette = palette();
	text_palette.setColor(QPalette::ButtonText, QColor(23, 23, 23));
	setPalette(text_palette);

	//�����ı�����
	//QFont &text_font = const_cast<QFont &>(font());
	//text_font.setWeight(QFont::Bold);

	setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

	//����ͼ��
	QPixmap pixmap(pic_name);
	setIcon(pixmap);
	setIconSize(pixmap.size());

	//���ô�С
	setFixedSize(pixmap.width()+25, pixmap.height()+25);
	setAutoRaise(true);
	setObjectName("transparentToolButton");

	mouse_over = false;
	mouse_press = false;
	btnStyle = 1;
}

ToolButton::~ToolButton()
{

}

void ToolButton::enterEvent(QEvent *)
{
	mouse_over = true;
}

void ToolButton::leaveEvent(QEvent *)
{
	mouse_over = false;
}

void ToolButton::mousePressEvent(QMouseEvent *event)
{
	if(event->button() == Qt::LeftButton)
	{
		emit clicked();
	}
}

void ToolButton::setMousePress(bool mouse_press)
{
	this->mouse_press = mouse_press;
	update();
}

void ToolButton::paintEvent(QPaintEvent *event)
{
	if(mouse_over)
	{
		//��������Ƶ���ť�ϵİ�ťЧ��
		//painterInfo(0, 100, 150);
	}
	else
	{
		if(mouse_press)
		{
			painterInfo(0, 100, 250);
		}
	}

	QToolButton::paintEvent(event);
}

void ToolButton::painterInfo(int light_color, int middle_color, int heavy_color)
{
	if(btnStyle == TITELSTYLE)
	{
		QPainter painter(this);
		QPen pen(Qt::NoBrush, 1);
		painter.setPen(pen);
		QLinearGradient linear(rect().topLeft(), rect().bottomLeft());
		linear.setColorAt(0, QColor(230, 230, 230, light_color));
		linear.setColorAt(0.5, QColor(130, 130, 130, middle_color));
		linear.setColorAt(1, QColor(40, 40, 40, heavy_color));
		painter.setBrush(linear);
		painter.drawRect(rect());
	}
	if(btnStyle == SETTINGSTYLE)
	{
		QPainter painter(this);
		QPen pen(Qt::NoBrush, 1);
		painter.setPen(pen);
		QLinearGradient linear(rect().topLeft(), rect().topRight());
		linear.setColorAt(0, QColor(100, 100, 100, light_color));
		linear.setColorAt(0.5, QColor(100, 100, 100, middle_color));
		linear.setColorAt(1, QColor(100, 100, 100, heavy_color));
		painter.setBrush(linear);
		painter.drawRect(rect());

	}

}