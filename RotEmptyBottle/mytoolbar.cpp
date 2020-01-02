#include "mytoolbar.h"
#include <QContextMenuEvent>

MyToolBar::MyToolBar(QWidget *parent)
	: QToolBar(parent)
{

}

MyToolBar::~MyToolBar()
{

}

void MyToolBar::contextMenuEvent(QContextMenuEvent* e)  
{
	return;
}