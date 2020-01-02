#include "CIOCard.h"
#include "clogfile.h"
#include <QSettings>
CIOCard::CIOCard(s_ConfigIOCardInfo sConfigIOCardInfo,int index)
{
	//����
	m_bIsPopMessagebox = true;
	strMessageboxTittle = QObject::tr("IOCARD ERROR");		//�������
	//��ʼ���ļ�·��
	m_bIsIOCardOK = 1;		//IO���Ƿ�����
	if (m_bIsIOCardOK)
	{
		//������ֵ��ʼ��
		m_sConfigIOCardInfo = sConfigIOCardInfo;//sSystemInfo.m_sConfigIOCardInfo[index];	
	}
	m_vSignalQueue.clear();
	ReadQeueu();
}

CIOCard::~CIOCard()
{
	m_vSignalQueue.clear();
}


//��ʼ��IO��:��ʼ��ʱ��ʹ�ܣ��������ʱenable,Ҳ��ͨ�����������Ƿ��߷�
s_IOCardErrorInfo CIOCard::InitIOCard()	
{
	s_IOCardErrorInfo sInfo;
	try
	{
		//��ʼ��ʱҲ�����жϣ��ж������ļ��е��Ƿ��ʼ���ӿڿ�
		if (m_bIsIOCardOK)
		{
			//update to QT 5.12.6
			QByteArray v_CardInitFile = m_sConfigIOCardInfo.strCardInitFile.toLatin1(), v_CardName = m_sConfigIOCardInfo.strCardName.toLatin1();
			const char* c_CardInitFile = v_CardInitFile.data();
			const char* c_CardName = v_CardName.data();

			if(m_Pio24b.openCard(m_sConfigIOCardInfo.iCardID))
			{
				m_Pio24b.hardReset();
				//m_Pio24b.initRegisters(m_sConfigIOCardInfo.strCardInitFile, m_sConfigIOCardInfo.strCardName);
				m_Pio24b.initRegisters(c_CardInitFile, c_CardName);
				m_Pio24b.softReset();
				m_Pio24b.enable(false);// true->false [11/11/2010 zhaodt]
				m_bIsIOCardOK = true;
			}
			else
			{
				//m_Pio24b.initRegisters(m_sConfigIOCardInfo.strCardInitFile, m_sConfigIOCardInfo.strCardName);
				m_Pio24b.initRegisters(c_CardInitFile, c_CardName);
				m_bIsIOCardOK = false;
				sInfo.bResult = false;
				sInfo.strSummaryInfo = QObject::tr("Failed to initialize IOCard%1").arg(m_sConfigIOCardInfo.iCardID+1);//IO��%1��ʼ��ʧ�� !
				sInfo.strDetailedInfo = sInfo.strSummaryInfo;
				if (m_bIsPopMessagebox)
				{
					s_MSGBoxInfo msginfo;
					msginfo.strMsgInfo = sInfo.strSummaryInfo;
					msginfo.strMsgtitle = strMessageboxTittle;
					emit emitMessageBoxMainThread(msginfo);
				}
				else
				{
					//QT 5.12.6
					//qDebug(sInfo.strSummaryInfo);
					CLogFile::write(sInfo.strSummaryInfo, DebugLog);
				}
			}
			////һ��Ҫ��ʼ������ӿڿ�
			//if(m_iSystemType == 2 || m_iSystemType == 3 || m_iSystemType == 5)
			//{
			//	if(m_pio24b1.openCard(1))
			//	{
			//		m_pio24b1.hardReset();
			//		m_pio24b1.initRegisters("\\PIO24B_reg_init1.txt", "PIO24B");
			//		m_pio24b1.softReset();
			//		m_pio24b1.enable(false);// true->false [11/11/2010 zhaodt]
			//	}
			//	else
			//	{
			//		m_bIsIOCardOK = FALSE;
			//		CString strValue;
			//		strValue.LoadString(ID_MSG6);
			//		AfxMessageBox(strValue) ;

			//		//CString strInfo;
			//		CString strError,strInfo;
			//		strError.LoadString(IDS_LOG_ERRORINFO);
			//		strInfo.LoadString(IDS_LOG_INITCARD1ERROR);
			//		//strInfo.Format(tr("IO��1��ʼ��ʧ��!"));
			//		m_LogManager.MyWriteLogFile(strError,strInfo,OperationLog);
			//	}
			//}
		}
	}
	catch (...)
	{
		m_bIsIOCardOK = false;
		sInfo.bResult = false;
		sInfo.strSummaryInfo = QObject::tr("Initialize the IOCard%1 abnormal!").arg(m_sConfigIOCardInfo.iCardID+1);//IO��%1��ʼ���쳣!
		sInfo.strDetailedInfo = sInfo.strSummaryInfo;
		if (m_bIsPopMessagebox)
		{
			s_MSGBoxInfo msginfo;
			msginfo.strMsgInfo = sInfo.strSummaryInfo;
			msginfo.strMsgtitle = strMessageboxTittle;
			emit emitMessageBoxMainThread(msginfo);
		}
		else
		{
			//QT 5.12.6
			//qDebug(sInfo.strSummaryInfo);
			CLogFile::write(sInfo.strSummaryInfo, DebugLog);
		}
	}
	return sInfo;
}

//�ͷ�IO��
s_IOCardErrorInfo CIOCard::CloseIOCard()
{
	s_IOCardErrorInfo sInfo;
	try
	{
		//ֹͣIO�� [11/11/2010 zhaodt]
		if (m_bIsIOCardOK)
		{
			m_bIsIOCardOK = false;
			m_mutexmIOCard.lock();
			m_Pio24b.softReset();
			m_Pio24b.enable(false);
			m_mutexmIOCard.unlock();
			qDebug("---�ӿڿ�-%d--Stop--\n",m_sConfigIOCardInfo.iCardID+1);
		}
	}
	catch (...)
	{
		sInfo.bResult = false;
		sInfo.strSummaryInfo = QObject::tr("Close the IOCard%1 abnormal!!").arg(m_sConfigIOCardInfo.iCardID+1);//�ر�IO��%1�쳣!
		sInfo.strDetailedInfo = sInfo.strSummaryInfo;
		if (m_bIsPopMessagebox)
		{
			s_MSGBoxInfo msginfo;
			msginfo.strMsgInfo = sInfo.strSummaryInfo;
			msginfo.strMsgtitle = strMessageboxTittle;
			emit emitMessageBoxMainThread(msginfo);
		}
		else
		{
			// QT 5.12.6
			//qDebug(strMessageboxTittle);
			CLogFile::write(strMessageboxTittle, DebugLog);
		}
	}
	return sInfo;
}

//��ȡ����--�ҵģ������дһ�飬���޸�Ϊ���ж���
void CIOCard::ReadQeueu()
{
	s_IOSignal sSignal;
	sSignal.iGrabCount = 0;
	sSignal.iGrabDelay = 0;
	QSettings SignalQueue(m_sConfigIOCardInfo.strCardInitFile,QSettings::IniFormat);//GrabInfo.ini
	//�ɼ�����-iniGrabInfo
	int iText = SignalQueue.value(QString("/PIO24B/18"),0xffffffff).toInt();
	iText = iText % 16;


//	m_vSignalQueue.push_back(sSignal);
}

//��ȡͼ���
int CIOCard::ReadImageSignal(int iStation)
{
	int iSignalCount = -1;
	if (m_bIsIOCardOK)
	{
		//m_mutexmIOCard.lock();
		iSignalCount = m_Pio24b.readCounter(iStation)&0xFF; //��ȡͼ���
		//m_mutexmIOCard.unlock();
	}
	return iSignalCount;
}
int CIOCard::ReadCounter(int param)
{
	int iSignalCount = -1;
	if (m_bIsIOCardOK)
	{
		iSignalCount = m_Pio24b.readCounter(param); //��ȡͼ���
	}
	return iSignalCount;
}

void CIOCard::SendResult(s_ResultInfo sResultInfo)
{
	//����ӿڿ�ͬʱ��������쳣�������滥�⡣
// 	m_mutexmIOCard.lock();
  	m_Pio24b.sendChckRslt(sResultInfo.tmpResult,sResultInfo.nImgNo,0);
//	m_mutexmIOCard.unlock();

}
void CIOCard::GetSample(s_ResultInfo sResultInfo)
{
	//����ӿڿ�ͬʱ��������쳣�������滥�⡣
//	m_mutexmIOCard.lock();
	m_Pio24b.sendChckRslt(sResultInfo.tmpResult,sResultInfo.nImgNo,3);									
//	m_mutexmIOCard.unlock();
}

unsigned short CIOCard::readParam(int paramIndex)
{
	return m_Pio24b.readParam(paramIndex);
}

void CIOCard::writeParam(int paramIndex, unsigned short data)
{
	m_Pio24b.writeParam(paramIndex, data);
}

unsigned short CIOCard::readStatus(int counterIndex)
{
	return m_Pio24b.readStatus(counterIndex);
}

int CIOCard::Show_PIO24B_DebugDialog(void *pParentWnd)
{
	int i = m_Pio24b.Show_PIO24B_DebugDialog(pParentWnd);
	return i;
}

void CIOCard::enable(bool bSign)
{
	m_mutexmIOCard.lock();
	if (bSign == true)
	{
		m_Pio24b.softReset();
	}
	m_Pio24b.enable(bSign);
	m_mutexmIOCard.unlock();

}
void CIOCard::TestOutPut(int ComNo)
{
	m_mutexmIOCard.lock();
	m_Pio24b.setCardOutput(ComNo,1);
	Sleep(20);
	m_Pio24b.setCardOutput(ComNo,0);
	m_mutexmIOCard.unlock();

}
void CIOCard::SetOutHighLevel(int ComNo)
{
	m_mutexmIOCard.lock();
	m_Pio24b.setCardOutput(ComNo,1);
	m_mutexmIOCard.unlock();

}
void CIOCard::SetOutLowLevel(int ComNo)
{
	m_mutexmIOCard.lock();
	m_Pio24b.setCardOutput(ComNo,0);
	m_mutexmIOCard.unlock();

}

