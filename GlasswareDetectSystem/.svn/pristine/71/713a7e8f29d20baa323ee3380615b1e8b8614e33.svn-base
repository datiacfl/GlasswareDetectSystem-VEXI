#ifndef CAMERAOFFLINEMONITOR_H
#define CAMERAOFFLINEMONITOR_H

#include <QThread>
#include "FGCamera.h"
#pragma comment(lib,"FGCamera.lib")

class CCameraFrame;

typedef struct
{
	bool          LimitSpeed;                             // Limit speed
	bool          Busy;                                   // Busy status
	UINT32HL      Guid;                                   // GUID for this camera
	UINT8         NodeId;                                 // ID of this node
	char          DeviceName[128];                        // Name of device
	CCameraFrame *pCameraFrame;                           // Pointer to camera frame
}CAMERAINFO;


class CameraOffLineMonitor : public QThread
{
	Q_OBJECT

public:
	CameraOffLineMonitor(QObject *parent);
	~CameraOffLineMonitor();

public:
	void run();
	void stopMonitor();
	void setUsedCameraMarkNumber(QList<QString> listStrCameraMarkNumber,int nLength);
	void getOfflineCameraMarkNumber(QList<int> listnOffLineCameraNumber);
private:
	bool GetCameraMarkNo();
	void findOfflineCameraMarkNumber();
signals:
	void signals_CameraOffLine(bool bIsOffLine);
	void signals_MessageBox(QString);


private:
	QString strCameraMarkNo[50];
	QString strUsedCameraMarkNo[50];
	int iCameraCount;
	int iRealCameraCount;
	bool bMonitor;
	QList<QString> liststrCameraMarkNoUsed;
	int nCameraState[50];
};

#endif // CAMERAOFFLINEMONITOR_H
