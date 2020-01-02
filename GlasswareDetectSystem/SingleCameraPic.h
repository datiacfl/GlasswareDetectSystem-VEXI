#include <QImage>
#include <QString>
#include <QList>
#include <QRect>
#pragma once
class SingleCameraPic
{
public:
	SingleCameraPic(void);
	SingleCameraPic(QImage imageShown,QString camera,QString imageSN,QString time,
					QString result,QString Mould,QList<QRect> listRect,int queenID,int grabImageCount);
	~SingleCameraPic(void);
	/*QImage* GetImageShown() const { return &imageShown; }
	void SetImageShown(QImage val) { imageShown = val; }*/
	QString GetCamera() const { return camera; }
	void SetCamera(QString val) { camera = val; }
	QString GetImageSN() const { return imageSN; }
	void SetImageSN(QString val) { imageSN = val; }
	QString GetTime() const { return time; }
	void SetTime(QString val) { time = val; }
	QString GetResult() const { return result; }
	QString GetMould() const {return Mould;}
	void SetResult(QString val) { result = val; }
	QList<QRect> GetListRect() const { return listRect; }
	void SetListRect(QList<QRect> val) { listRect = val; }
	int GetQueryId() const {return queenID;}
	int SetQueryId(int var) {queenID = var;}
	int GetGrabImageCount() const { return grabImageCount; }
	void SetGrabImageCount(int val) { grabImageCount = val; }
public:
	QImage imageShown;
	QString camera;
	QString imageSN;
	QString time;
	QString result; 
	QString Mould;
	QList<QRect> listRect;
	int queenID;
	int grabImageCount;
};

