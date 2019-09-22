#pragma once

#include <QObject>
#include <QString>
#include <QDebug>
#include <QMessageBox>
#include "uploadtosql.h"
#include "credentials.h"
#include "setdatelotparameters.h"
#include "errors_interpretation.h"
#include "process_results.h"

class FormReportByLot : public QObject
{
	Q_OBJECT

public:
	FormReportByLot();

	void UploadDataToSQL();
	void JoinToSQLServer();
	void FormReport();

	~FormReportByLot();

private:	
	Credentials* credentials;
	SetDateLotParameters* settingsDateLot;
	ProcessResults* winResults;
	
	bool isConnected;


	void setSQLConnection(QString driverName, QString serverName, QString dbName, QString login, QString password);
};
