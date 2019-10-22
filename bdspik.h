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

class BDSpik : public QObject
{
	Q_OBJECT

public:
    BDSpik(QString pathToInputDir, QString pathToOutputDir);

	QString UploadDataToSQL(QStringList pathToCSVFiles);
	QString JoinToSQLServer();
	QString FormReport();

	~BDSpik();

private:
    QString  m_pathToDirWithCSV, m_pathToDirWithReport;
	Credentials* credentials;
	SetDateLotParameters* settingsDateLot;
	ProcessResults* winResults;
	bool isConnected;
};
