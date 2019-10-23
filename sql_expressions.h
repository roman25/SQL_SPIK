#pragma once

#include <QString>

struct SQLQueries
{
private:
    const QString tableGSName   = "GSNTestInfo";
    const QString tableNameBase = "GSNTestInfoBase";
    QString GetBinText();

public:
    QString checkBaseTableExists = "IF NOT EXISTS (SELECT * FROM INFORMATION_SCHEMA.TABLES WHERE TABLE_NAME = N'" + tableNameBase + "')"
        " RAISERROR('No tables',16,1);";

    QString checkGSTableExists = "IF NOT EXISTS (SELECT * FROM INFORMATION_SCHEMA.TABLES WHERE TABLE_NAME = N'T_" + tableGSName + "')"
        " RAISERROR('No tables',16,1);";

    QString selectionByDate = ("SELECT LotName, StartDateTime, FinishDateTime, MKM1, MKM2, MKM3, MKM4, MKM5, MKM6, MKM7, MKM8, DeviceAddress "
        " FROM " + tableNameBase +
        " WHERE(	DATEPART(yy, StartDateTime) =  %1 "
        " AND		DATEPART(mm, StartDateTime) = %2 "
        " AND		DATEPART(dd, StartDateTime) = %3) ");

    QString selectionRangeDate = ("SELECT LotName, StartDateTime, FinishDateTime, MKM1, MKM2, MKM3, MKM4, MKM5, MKM6, MKM7, MKM8, DeviceAddress "
        " FROM " + tableNameBase +
        " WHERE (StartDateTime between '%1-%2-%3' AND '%4-%5-%6')");

    QString selectionOnlyLotName = ("SELECT LotName, StartDateTime, FinishDateTime, MKM1, MKM2, MKM3, MKM4, MKM5, MKM6, MKM7, MKM8, DeviceAddress "
        " FROM " + tableNameBase +
        " WHERE LotName = '%1'");

    QString selectionAdditionalLotName = (" OR LotName = '%1'");

    QString createBaseTable = ("CREATE TABLE " + tableNameBase +
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
        " DeviceAddress VARCHAR (10) NULL, "
        " InCount int, "
        " OutCount int) ");


    QString createGSTable = (" CREATE TABLE [dbo].[T_" + tableGSName + "]"
    " ("
    " [" + tableGSName + "Id] [bigint] IDENTITY(1,1) NOT FOR REPLICATION NOT NULL,"
    " [LotName] VARCHAR (50) NOT NULL, "
    " [LotType] VARCHAR (50) NOT NULL, "
    " [StartDateTime] DATETIME NOT NULL, "
    " [FinishDateTime] DATETIME NOT NULL, "
    " [In] [int] NOT NULL,"
    " [Out][int] NOT NULL,"
        + GetBinText() +
    " CONSTRAINT [PK_GSNTest] PRIMARY KEY CLUSTERED"
    " ("
    " [" + tableGSName + "Id] ASC"
    " )WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = OFF) ON [PRIMARY]"
    " ) ");

    QString insertValues = ("INSERT INTO " + tableNameBase +
        " (LotName, StartDateTime, FinishDateTime, MKM1, MKM2, MKM3, MKM4, MKM5, MKM6, MKM7, MKM8, DeviceAddress) "
        " VALUES ('%1', '%2', '%3', '%4', '%5', '%6', '%7', '%8', '%9', '%10', '%11', '%12') ");

    QString updateInOut = ("UPDATE " + tableNameBase +
        " SET InCount = %1, OutCount = %2 "
        " WHERE LotName = '%3' AND StartDateTime = '%4' AND FinishDateTime = '%5'");

    QString updateFinishTime = ("UPDATE " + tableNameBase +
        " SET FinishDateTime = '%1' "
        " WHERE StartDateTime = '%2' ");

    QString setDateFortmat = ("SET LANGUAGE English SET DATEFORMAT ymd");

    QString checkDataUploadedToSQLServer = ("SELECT LotName, StartDateTime"
        " FROM T_" + tableGSName + 
        " WHERE LotName = '%1' AND StartDateTime = '%2'");

};