#pragma once

#include <QString>

struct SQLQueries
{
private:
	const QString tableName = "TestInfo";
	

public:	
	QString selectionByDate	= ("SELECT LotName, StartDateTime, FinishDateTime, MKM1, MKM2, MKM3, MKM4, MKM5, MKM6, MKM7, MKM8, DeviceAddress "
		" FROM " + tableName + 
		" WHERE(	DATEPART(yy, StartDateTime) =  %1 "
		" AND		DATEPART(mm, StartDateTime) = %2 "
		" AND		DATEPART(dd, StartDateTime) = %3) ");

	QString selectionRangeDate = ("SELECT LotName, StartDateTime, FinishDateTime, MKM1, MKM2, MKM3, MKM4, MKM5, MKM6, MKM7, MKM8, DeviceAddress "
		" FROM " + tableName +
		" WHERE (StartDateTime between '%1-%2-%3' AND '%4-%5-%6')");

	QString selectionOnlyLotName = ("SELECT LotName, StartDateTime, FinishDateTime, MKM1, MKM2, MKM3, MKM4, MKM5, MKM6, MKM7, MKM8, DeviceAddress "
		" FROM " + tableName +
		" WHERE LotName = '%1'");

	QString selectionAdditionalLotName = (" OR LotName = '%1'");

	QString createTable = ("CREATE TABLE " + tableName + 
		" (LotName VARCHAR (50) NOT NULL, "
		" StartDateTime DATETIME NOT NULL, "
		" FinishDateTime DATETIME NOT NULL, "
		" MKM1 VARCHAR (10), "
		" MKM2 VARCHAR (10), "
		" MKM3 VARCHAR (10), "
		" MKM4 VARCHAR (10), "
		" MKM5 VARCHAR (10), "
		" MKM6 VARCHAR (10), "
		" MKM7 VARCHAR (10), "
		" MKM8 VARCHAR (10), "
		" DeviceAddress VARCHAR (10) NULL) ");

	QString insertValues = ("INSERT INTO " + tableName + 
		" (LotName, StartDateTime, FinishDateTime, MKM1, MKM2, MKM3, MKM4, MKM5, MKM6, MKM7, MKM8, DeviceAddress) "
		" VALUES ('%1', '%2', '%3', '%4', '%5', '%6', '%7', '%8', '%9', '%10', '%11', '%12') ");

	QString updateFinishTime = ("UPDATE " + tableName +
		" SET FinishDateTime = '%1' "
		" WHERE StartDateTime = '%2' ");

	QString setDateFortmat = ("SET DATEFORMAT ymd");

    QString getTableName();

};
