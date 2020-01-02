#include "MyQueue.h"
#include "glasswaredetectsystem.h"


CMyQueue::CMyQueue(void)
{
	pBaseBuffer = NULL;
	listGrab.clear();
//	listDetect.clear();
//	listStressImg.clear();

	vColorTable.clear();
	for (int i = 0; i < 256; i++)  
	{  
		vColorTable.append(qRgb(i, i, i)); 
	} 
	InitID = 0;
}


CMyQueue::~CMyQueue(void)
{
	releaseMemory();
}

//功能：初始化队列
bool CMyQueue::InitQueue(int nWidth,int nHeight,int nBitCount,int nBlockCount,bool bAllocMemeroy/* =true */)
{
 	InitID++;
	releaseMemory();
	if (bAllocMemeroy)
	{
		int nBlockSize = nWidth*nHeight*nBitCount/8;
		for (int i=0;i<nBlockCount;i++)
		{		
			CGrabElement *pElement = new CGrabElement;
			pElement->sImgLocInfo.sXldPoint.nColsAry = new int[4*BOTTLEXLD_POINTNUM];
			pElement->sImgLocInfo.sXldPoint.nRowsAry = new int[4*BOTTLEXLD_POINTNUM];
			pElement->myImage = new QImage(nWidth,nHeight,nBitCount);// 用于实时显示
			pElement->myImage->setColorTable(vColorTable);
			pElement->initID = InitID;
// 			pElement->myImage.Init(nBlockSize);
// 			pElement->myImage.SetImgSize(nWidth,nHeight,nBitCount);
			listGrab.push_back(pElement);
// 			pElement = NULL;
		}
	}
	return true;
}

void CMyQueue::releaseMemory()
{
	CGrabElement *pElement = NULL;
// 	while (!listStressImg.isEmpty())
// 	{
// // 		mLocker.lock();
// 		pElement = listStressImg.first();
// 		listStressImg.removeFirst();
// 		listGrab.push_back(pElement);
// 		pElement = NULL;
// //		mLocker.unlock();
// 	}	
// 	while (!listDetect.isEmpty())
// 	{
// // 		mLocker.lock();
// 		pElement = listDetect.first();
// 		//listDetect.removeFirst();
// 		listGrab.push_back(pElement);
// 		pElement = NULL;
// // 		mLocker.unlock();
// 	}
	int i = listGrab.length();
	while (!listGrab.isEmpty())
	{
// 		mLocker.lock();
		pElement = listGrab.first();
		listGrab.removeFirst();

		if (pElement->sImgLocInfo.sXldPoint.nColsAry != NULL)
		{
			delete []pElement->sImgLocInfo.sXldPoint.nColsAry;
			pElement->sImgLocInfo.sXldPoint.nColsAry = NULL;
		}
		if (pElement->sImgLocInfo.sXldPoint.nRowsAry != NULL)
		{
			delete []pElement->sImgLocInfo.sXldPoint.nRowsAry;
			pElement->sImgLocInfo.sXldPoint.nRowsAry = NULL;
		}
		if (pElement->myImage != NULL)
		{
			delete pElement->myImage;
			pElement->myImage = NULL;
		}
// 		mLocker.unlock();
		if (pElement != NULL)
		{
			delete pElement;
			pElement = NULL;
		}
	}
	if (pBaseBuffer)
	{
		delete []pBaseBuffer;
	}

}

