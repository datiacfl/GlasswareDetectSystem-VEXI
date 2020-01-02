#include "SingleCameraPic.h"


SingleCameraPic::SingleCameraPic(void)
{
}

SingleCameraPic::SingleCameraPic( QImage imageShown,QString camera,QString imageSN,QString time, 
								  QString result,QString Mould,QList<QRect> listRect,int queenID,int grabImageCount)
{
	this->imageShown = imageShown;
	this->camera = camera;
	this->imageSN = imageSN;
	this->time = time;
	this->result = result;
	this->listRect = listRect;
	this->queenID = queenID;
	this->grabImageCount = grabImageCount;
	this->Mould=Mould;
}


SingleCameraPic::~SingleCameraPic(void)
{
}
