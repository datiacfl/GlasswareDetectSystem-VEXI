#include "CameraOffLineMonitor.h"

#include  "qt_windows.h"
#include "glasswaredetectsystem.h"
#include <QMessageBox>

extern GlasswareDetectSystem *pMainFrm;

CameraOffLineMonitor::CameraOffLineMonitor(QObject *parent)
	: QThread(parent)
{
	iCameraCount = 0;
	iRealCameraCount = 0;
	for (int i=0; i<50; i++)
	{
		nCameraState[i] = -1;
	}
	bMonitor = true;
}

CameraOffLineMonitor::~CameraOffLineMonitor()
{

}
bool CameraOffLineMonitor::GetCameraMarkNo()
{
	// TODO: Add extra initialization here
	return false;
}
void CameraOffLineMonitor::findOfflineCameraMarkNumber()
{
	for (int i=0; i<iRealCameraCount; i++)
	{
		for (int j=0; j<iCameraCount;j++)
		{
			if (strUsedCameraMarkNo[i] == strCameraMarkNo[j])
			{
				nCameraState[i] = 1;
				break;
			}
		}
		nCameraState[i]=0;
	}
}

void CameraOffLineMonitor::run()
{
	bMonitor = true;

	while (bMonitor)
	{
		pMainFrm->m_mutexmGrab.lock();						//Ïà»ú²Ù×÷»¥³â
		bool bRet = GetCameraMarkNo();
		pMainFrm->m_mutexmGrab.unlock();
		if (bRet)
		{
//			findOfflineCameraMarkNumber();
			emit signals_CameraOffLine(true);
		}
		else
		{
			emit signals_CameraOffLine(false);
		}
		Sleep(6000);
	}
}
void CameraOffLineMonitor::stopMonitor()
{
	bMonitor = false;
}

void CameraOffLineMonitor::setUsedCameraMarkNumber(QList<QString> listStrCameraMarkNumber,int nRealCameraNumber)
{
	iRealCameraCount = nRealCameraNumber;
	for (int i=0; i<nRealCameraNumber; i++)
	{
		strUsedCameraMarkNo[i] = listStrCameraMarkNumber.at(i);
	}

}

void CameraOffLineMonitor::getOfflineCameraMarkNumber(QList<int> listnOffLineCameraNumber)
{
	listnOffLineCameraNumber.clear();
	for (int i=0; i<iRealCameraCount; i++)
	{
		if (0 == nCameraState[i])
		{
			listnOffLineCameraNumber.append(i);
		}
	}
}


