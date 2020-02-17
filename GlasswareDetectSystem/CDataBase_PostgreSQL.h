#pragma once


#include<iostream>
#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>

#include "glasswaredetectsystem.h"
using namespace std;


namespace DataBase_PostgreSQL 
{

	static bool _bConnected = false;
	static QSqlDatabase db;


	static const QString& _QstrDatabase = "vexi";

	static const QString& _QstrCameraDeviceConfig = "camera_device_config";
	static const QString& _QstrDeviceTrackErrorType = "device_track_error_type";
	static const QString& _QstrErrorName = "error_name";
	static const QString& _QstrPLCStatusType = "plc_status_type";
	static const QString& _QstrSystemConfig = "system_config";
	class Database
	{
	public:
		static bool Connect();
		static bool Disconnect();
		static bool ExecuteCommand_NotQuery(const QString& strSql);
		static QSqlQuery ExecuteCommand_Query(const QString& strSql);
		static QSqlQuery Select(const QString& strTableName,const QVector<QString>& vectColumns , const QString& strCondition = "");
		static QSqlQuery Select(const QString& strTableName);
		static bool Update(const QString& strTableName, QVector<QString>& vectColumns, QVector<QString>& vectNewValues, const QString& strCondition);
		static bool Insert(const QString& strTableName, QVector<QString>& vectColumns, QVector<QString>& vectValues);
		static bool Delete(const QString& strTableName, const QString& strCondition);
		static bool AddColumn(const QString& strTableName, const QString& strColumn);
		static bool DeleteColumn(const QString& strTableName, const QString& strColumn);
	};

	class DALSystemConfigManager
	{
	public:
		static void ReadAllConfig(s_ConfigInfo& m_sConfigInfo, s_SystemInfo& sSystemInfo, s_ErrorInfo& sErrorInfo, s_RunningInfo& sRunningInfo, QVector<QString>& vstrPLCInfoType, s_RealCamInfo* m_sRealCamInfo, s_GBINITSTRUCT* sGBINITSTRUCT,int CameraTotal = CAMERA_MAX_COUNT);
		static void ReadCameraDeviceConfig(s_ConfigInfo& m_sConfigInfo, s_SystemInfo& sSystemInfo, s_RealCamInfo* m_sRealCamInfo, s_GBINITSTRUCT* sGBINITSTRUCT, int CameraTotal = CAMERA_MAX_COUNT);
		static void ReadDeviceTrackErrorType(s_SystemInfo& sSystemInfo);
		static void ReadErrorName(s_ErrorInfo& sErrorInfo);
		static void ReadPLCStatusType(QVector<QString>& vstrPLCInfoType);
		static void ReadSystemConfig(s_SystemInfo& sSystemInfo, s_ErrorInfo& sErrorInfo, s_RunningInfo& sRunningInfo);
	};






}