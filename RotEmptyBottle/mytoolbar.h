#ifndef MYTOOLBAR_H
#define MYTOOLBAR_H

#include <QToolBar>

class MyToolBar : public QToolBar
{
	Q_OBJECT

public:
	MyToolBar(QWidget *parent);
	~MyToolBar();
	void contextMenuEvent(QContextMenuEvent* e);

private:
	
};

#endif // MYTOOLBAR_H
