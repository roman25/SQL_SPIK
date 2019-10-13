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
    FormReportByLot(QString pathToResultFiles = "");

	QString UploadDataToSQL(QStringList pathToCSVFiles);
	QString JoinToSQLServer();
	QString FormReport(QString pathToOutputReport);

	~FormReportByLot();

private:
    QString m_pathToDirWithCSV;
	Credentials* credentials;
	SetDateLotParameters* settingsDateLot;
	ProcessResults* winResults;
	bool isConnected;
};
