#include "CDataBase_PostgreSQL.h"
#include <qDebug>
#include <QSqlError>

namespace DataBase_PostgreSQL
{
#pragma region Database
	bool Database::Connect() //use QSqlDatabase to connect postgresql
	{
		/*QSqlDatabase db;*/
		if (QSqlDatabase::contains("vexi"))
		{
			db = QSqlDatabase::database("vexi");
		}
		else
		{
			db = QSqlDatabase::addDatabase("QPSQL7", "vexi");
		}

		db.setDatabaseName("datia");
		db.setHostName("127.0.0.1");
		db.setPort(5432);

		bool bRet = db.open("postgres", "root");

		/*if (bRet)
		{
			QSqlQuery qsQuery = QSqlQuery(db);
			bool buscess = qsQuery.exec(QString("create table vexi.mer030 \
			( \
			device_id   int ,\
			width   int ,\
			height   int ,\
			offset_x   int ,\
			offset_y   int ,\
			exposure_mode   int ,\
			exposure_time   int ,\
			exposure_auto   int ,\
			gain   int ,\
			gain_atuo   int ,\
			black_level   int ,\
			black_level_auto   int ,\
			balance_ratio   real ,\
			blaance_ratio_auto   int ,\
			trigger_mode   int ,\
			trigger_activation   int ,\
			acq_speed_level int)"));
			QSqlError warningText = qsQuery.lastError();
			QString ss = warningText.text();
			int xx = 0;
			xx++;
		}*/
		return bRet;
	}

	bool Database::Disconnect()
	{
		if (QSqlDatabase::contains("vexi"))
		{
			db.close();
		}
		return true;
	}
	//initialize the Query
	bool Database::ExecuteCommand_NotQuery(const QString& strSql)
	{
		QSqlQuery qsQuery = QSqlQuery(db);
		return qsQuery.exec(strSql);
	}
	QSqlQuery Database::ExecuteCommand_Query(const QString& strSql)
	{
		QSqlQuery qsQuery = QSqlQuery(db);
		qsQuery.exec(strSql);
		return qsQuery;
	}
	QSqlQuery Database::Select(const QString& strTableName,const QVector<QString>& vectColumns, const QString& strCondition)
	{
		QString strColumns;
		size_t colSize = vectColumns.size();
		if (colSize != 0)
		{
			for (size_t i = 0; i < colSize; i++)
			{
				strColumns.append(vectColumns.at(i));
				strColumns.push_back(',');
			}
			strColumns = strColumns.left(strColumns.size() - 1);
		}
		else
		{
			strColumns = "*";
		}
		QString strSql = (strCondition.size() == 0)
			? "SELECT " + strColumns + " FROM " + _QstrDatabase + "." + strTableName
			: "SELECT " + strColumns + " FROM " + _QstrDatabase + "." + strTableName + " WHERE " + strCondition;
		return ExecuteCommand_Query(strSql);
	}
	QSqlQuery Database::Select(const QString& strTableName)
	{
		QVector<QString> vectColumns_tmp;
		return Select(strTableName, vectColumns_tmp);
	}

	bool Database::Update(const QString& strTableName, QVector<QString>& vectColumns, QVector<QString>& vectNewValues, const QString& strCondition)
	{
		QString setStr = "SET ";
		if (vectColumns.size() != vectNewValues.size())
			return false;
		for (int index = 0; index < vectColumns.size(); index++)
		{
			setStr += vectColumns[index] + "='" + vectNewValues[index] + "',";
		}
		setStr = setStr.left(setStr.size() - 1);
		QString strSql = (strCondition.size() == 0)
			? "UPDATE " + _QstrDatabase + "." + strTableName + " " + setStr
			: "UPDATE " + _QstrDatabase + "." + strTableName + " " + setStr + " WHERE " + strCondition;

		return ExecuteCommand_NotQuery(strSql);
	}

	bool Database::Insert(const QString& strTableName, QVector<QString>& vectColumns, QVector<QString>& vectValues)
	{
		QString strColumns;
		QString strValues;
		if (vectValues.size() % vectColumns.size() != 0)
		{
			return false;
		}
		for (unsigned int index = 0; index < vectColumns.size(); index++)
		{
			strColumns += vectColumns[index] + ",";
		}
		strColumns = "(" + strColumns.left(strColumns.size() - 1) + ")";
		int nCount = 0;
		for (unsigned int index = 0; index < vectValues.size(); index++)
		{
			if (nCount == 0)
			{
				strValues += "(";
			}
			strValues += "'" + vectValues[index] + "',";
			nCount++;
			if (nCount == vectColumns.size())
			{
				nCount = 0;
				strValues = strValues.left(strValues.size() - 1) + "),";
			}
		}
		strValues = strValues.left(strValues.size() - 1);
		QString strSql = "INSERT INTO " + _QstrDatabase + "." + strTableName + " " + strColumns + " VALUES " + strValues;

		return ExecuteCommand_NotQuery(strSql);
	}

	bool Database::Delete(const QString& strTableName, const QString& strCondition)
	{
		QString strSql = "DELETE FROM " + _QstrDatabase + "." + strTableName + " WHERE " + strCondition;
		return ExecuteCommand_NotQuery(strSql);
	}

	bool Database::AddColumn(const QString& strTableName, const QString& strColumn)
	{
		QString strSql = "ALTER TABLE " + _QstrDatabase + "." + strTableName + " ADD COLUMN" + strColumn;
		return ExecuteCommand_NotQuery(strSql);
	}
	bool Database::DeleteColumn(const QString& strTableName, const QString& strColumn)
	{
		QString strSql = "ALTER TABLE " + _QstrDatabase + "." + strTableName + " DROP COLUMN" + strColumn;
		return ExecuteCommand_NotQuery(strSql);
	}
#pragma endregion

#pragma region DALSystemConfigManager
	void DALSystemConfigManager::ReadAllConfig(s_ConfigInfo& m_sConfigInfo, s_SystemInfo& sSystemInfo, s_ErrorInfo& sErrorInfo, s_RunningInfo& sRunningInfo, QVector<QString>& vstrPLCInfoType, s_RealCamInfo* m_sRealCamInfo, s_GBINITSTRUCT* sGBINITSTRUCT, int CameraTotal)
	{
		ReadErrorName(sErrorInfo);
		ReadSystemConfig(sSystemInfo, sErrorInfo, sRunningInfo);
		ReadCameraDeviceConfig(m_sConfigInfo, sSystemInfo, m_sRealCamInfo,  sGBINITSTRUCT, CameraTotal);
		ReadDeviceTrackErrorType(sSystemInfo);
		ReadPLCStatusType(vstrPLCInfoType);
	}
	void DALSystemConfigManager::ReadCameraDeviceConfig(s_ConfigInfo& m_sConfigInfo, s_SystemInfo& sSystemInfo, s_RealCamInfo* m_sRealCamInfo, s_GBINITSTRUCT* sGBINITSTRUCT, int CameraTotal)
	{
		QSqlQuery result = Database::Select(_QstrCameraDeviceConfig);
		int i = 0;
		while (result.next())
		{
			if (i == CameraTotal)
			{
				break;
			}
			sSystemInfo.m_iNoRejectIfNoOrigin[i] = result.value("device_no_reject_if_no_origin").toInt();
			sSystemInfo.m_iNoStaticIfNoOrigin[i] = result.value("device_no_static_if_no_origin").toInt();
			m_sRealCamInfo[i].m_iImageTargetNo = result.value("device_image_targetno").toInt();

			sGBINITSTRUCT[i].iGrabberTypeSN = 1;
			sGBINITSTRUCT[i].nGrabberSN = result.value("device_id").toInt() + 1;
			strcpy_s(sGBINITSTRUCT[i].strDeviceName, result.value("device_name").toString().toLocal8Bit().data());
			strcpy_s(sGBINITSTRUCT[i].strDeviceMark, result.value("device_mark").toString().toLocal8Bit().data());
			QString strGrabInitFile;//存储相机初始化位置
			strGrabInitFile = result.value("device_init_file").toString();
			strGrabInitFile = m_sConfigInfo.m_strConfigPath.left(m_sConfigInfo.m_strConfigPath.lastIndexOf("/") + 1) + strGrabInitFile;
			memcpy(sGBINITSTRUCT[i].strGrabberFile, strGrabInitFile.toLocal8Bit().data(), GBMaxTextLen);

			m_sRealCamInfo[i].m_iGrabPosition = result.value("device_station").toInt();
			m_sRealCamInfo[i].m_iImageRoAngle = result.value("device_ro_angle").toInt();
			m_sRealCamInfo[i].m_iImageType = result.value("device_image_type").toInt();
			m_sRealCamInfo[i].m_iIOCardSN = result.value("device_iocard_sn").toInt();
			i++;
		}
	}
	void DALSystemConfigManager::ReadDeviceTrackErrorType(s_SystemInfo& sSystemInfo)
	{
		QSqlQuery result = Database::Select(_QstrDeviceTrackErrorType);
		int i = 0;
		while (result.next())
		{
			sSystemInfo.m_iIsTrackErrorType[i] = result.value(1).toInt();
			sSystemInfo.m_iTrackAlertRateMax[i] = result.value(2).toInt();
			sSystemInfo.m_iTrackAlertRateMin[i] = result.value(3).toInt();

			i++;
		}
	}
	void DALSystemConfigManager::ReadErrorName(s_ErrorInfo& sErrorInfo)
	{
		QSqlQuery result = Database::Select(_QstrErrorName);
		sErrorInfo.m_bErrorType[0] = false;
		sErrorInfo.m_vstrErrorType.append(QObject::tr("Good"));//.toLatin1().data()));
		int tmp = 1;
		while (result.next())
		{
			sErrorInfo.m_bErrorType[tmp] = true;
			sErrorInfo.m_vstrErrorType.append(result.value(1).toString());
			sErrorInfo.m_cErrorReject.iErrorCountByType[tmp] = 0;

			tmp++;
		}
		sErrorInfo.m_vstrErrorType.append(QObject::tr("Other"));
	}
	void DALSystemConfigManager::ReadPLCStatusType(QVector<QString>& vstrPLCInfoType)
	{
		QSqlQuery result = Database::Select(_QstrPLCStatusType);
		while (result.next())
		{
			vstrPLCInfoType.append(result.value(1).toString());
		}
	}
	void DALSystemConfigManager::ReadSystemConfig(s_SystemInfo& sSystemInfo, s_ErrorInfo& sErrorInfo,s_RunningInfo& sRunningInfo)
	{
		QSqlQuery result = Database::Select(_QstrSystemConfig);//Get the sql result
		while (result.next())  //by the .ini order first
		{
			sErrorInfo.m_iErrorTypeCount = result.value(0).toInt();
			sRunningInfo.m_failureNumFromIOcard = result.value(1).toInt();
			sRunningInfo.m_checkedNum = result.value(2).toInt();
			//temporary ,not used the 3.
			sSystemInfo.nLoginHoldTime = 10;	//是否报警统计
			sSystemInfo.m_strWindowTitle = QObject::tr("Glass Bottle Detect System");//读取系统标题
			sSystemInfo.m_iSimulate = 0;
			sSystemInfo.m_bDebugMode = result.value("debug_mode").toInt();	//读取是否debug
			sSystemInfo.m_iSystemType = e_SystemType(result.value("system_type").toInt());	//读取系统类型
			sSystemInfo.m_bIsUsePLC = result.value("is_use_plc").toBool();	//是否使用PLC
			sSystemInfo.m_bIsIOCardOK = result.value("is_use_io_card").toBool();	//是否使用IO卡
			sSystemInfo.m_bIsStopNeedPermission = result.value("is_stop_permission").toBool();	//
			sSystemInfo.iIOCardCount = result.value("io_card_count").toInt();	//读取IO卡个数
			sSystemInfo.iRealCamCount = result.value("device_num").toInt();	//真实相机个数
			sSystemInfo.m_bIsCarve = result.value("is_carve").toInt();	//获取是否切割设置
			sSystemInfo.m_bIsTest = result.value("test").toInt();//是否是测试模式
			sSystemInfo.iIsButtomStress = result.value("is_buttom_stree").toInt();//是否有瓶底应力
			sSystemInfo.iIsSaveCountInfoByTime = result.value("is_save_count_info_by_time").toInt();//是否保存指定时间段内的统计信息
			sSystemInfo.iIsSample = result.value("is_sample").toInt();//是否取样
			sSystemInfo.iIsCameraCount = result.value("is_camera_count").toInt();//是否统计各相机踢废率
			sSystemInfo.LastModelName = result.value("last_model_name").toString();	//读取上次使用模板
			sSystemInfo.m_iIsTrackStatistics = result.value("is_track_statistics").toInt();	//是否报警统计
			sSystemInfo.m_iTrackNumber = result.value("track_number").toInt();	//报警统计个数
			sSystemInfo.m_NoKickIfNoFind = result.value("no_kick_if_no_find").toInt();	//报警类型
			sSystemInfo.m_NoKickIfROIFail = result.value("no_kick_if_roi_fail").toInt();	//报警类型	
			sSystemInfo.m_iTwoImagePage = result.value("two_image_page").toInt();	//是否两页显示图像
			sSystemInfo.m_iImageStyle = result.value("image_style").toInt();	//图像横向排布还是上下排布
			sSystemInfo.m_iImageStretch = result.value("image_stretch").toInt();	//图像横向排布还是上下排布
			sSystemInfo.m_iSaveNormalErrorImageByTime = result.value("save_normal_error_image_by_time").toInt();
			sSystemInfo.m_iSaveStressErrorImageByTime = result.value("save_stress_error_image_by_time").toInt();
			sSystemInfo.m_iStopOnConveyorStoped = 0;	//输送带停止是否停止检测
			sSystemInfo.fPressScale = result.value("f_press_scale").toDouble();	//瓶身应力增强系数
			sSystemInfo.fBasePressScale = result.value("f_base_press_scale").toDouble();	//瓶底应力增强系数
			sSystemInfo.m_strModelName = sSystemInfo.LastModelName;
			sSystemInfo.bSaveRecord = true;
			sSystemInfo.iSaveRecordInterval = 60;
			sSystemInfo.bAutoSetZero = result.value("b_auto_set_zero").toBool();
			sSystemInfo.iIsSampleAndAlamConflict = result.value("is_sample_and_alam_conflict").toInt();
			sSystemInfo.m_iIs3Sensor = result.value("is_3sensor").toInt();

			sSystemInfo.bVEXIDoubleReject = result.value("b_vexi_double_reject").toBool();
			sSystemInfo.bVEXICleanLightSource = result.value("b_vexi_clean_light_source").toBool();
			sSystemInfo.nVEXICleanLightSourceInterval = result.value("n_vexi_clean_light_source_interval").toInt();
			sSystemInfo.nVEXICleanLightSourceWidth = result.value("n_vexi_clean_light_source_width").toInt();


			int iShift[3];
			iShift[0] = result.value("shift1").toInt();
			iShift[1] = result.value("shift2").toInt();
			iShift[2] = result.value("shift3").toInt();
			for (int i = 0; i < 2; i++)
			{
				if (iShift[i] > iShift[i + 1])
				{
					int temp = iShift[i];
					iShift[i] = iShift[i + 1];
					iShift[i + 1] = temp;
				}
			}
			sSystemInfo.shift1.setHMS(iShift[0] / 10000, (iShift[0] % 10000) / 100, iShift[0] % 100);
			sSystemInfo.shift2.setHMS(iShift[1] / 10000, (iShift[1] % 10000) / 100, iShift[1] % 100);
			sSystemInfo.shift3.setHMS(iShift[2] / 10000, (iShift[2] % 10000) / 100, iShift[2] % 100);


			sSystemInfo.iCamCount = sSystemInfo.iRealCamCount;


		}
	}

#pragma endregion


}