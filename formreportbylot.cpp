#include "formreportbylot.h"

FormReportByLot::FormReportByLot(QString pathToDir)
{
    pathToResultFiles = pathToDir;
	isConnected = false;
	log = new Logging();
}

FormReportByLot::~FormReportByLot()
{
	delete log;
}

QString FormReportByLot::JoinToSQLServer()
{
    /*!
        Creates connection to SQL server
     */

    // Save status of connection
    QString statusConnect = "";

    // Open window to get credentials
	credentials = new Credentials();
	if (credentials->exec() == QDialog::Accepted)
	{

        // Get credentials to connect
        QStringList cred    = credentials->getCredentials();
        QString driverName	= cred[0];
		QString serverName	= cred[1];
		QString dbName		= cred[2];
		QString login		= cred[3];
		QString password	= cred[4];

        // Create connection
		QSqlDatabase db = QSqlDatabase::addDatabase(driverName);
		db.setDatabaseName("DRIVER={SQL Server};SERVER=" + serverName + ";DATABASE=" + dbName);
		db.setUserName(login);
		db.setPassword(password);

        // Test connection to database
		if (!db.open())
		{
            // Get errors
			statusConnect = QSqlError(db.lastError()).text();            

            // Create window to show error
            QMessageBox msgBox;
			msgBox.setIcon(QMessageBox::Critical);
			msgBox.setWindowTitle("Error!");
			msgBox.setText(statusConnect);
			msgBox.exec();
		}
		else
		{
            isConnected   = true;
            statusConnect = "0";
			SQLQueries expession;

            // Set parameters of date format in SQL and execute the query
			QString sQuery = expession.setDateFortmat;
			QSqlQuery query;
            query.exec(sQuery);//где Обработка ошибки?!
		}
	}

	delete credentials;

	return statusConnect;
}

QString FormReportByLot::UploadDataToSQL(QStringList pathToCSVFiles)
{
    /*!
        Uploads data on SQL server
    */

    // Status of uploading
    QString statusUpload = "";

    // Upload if connection is present
    if (isConnected)
	{
        statusUpload = "0";
        UploadToSQL* uploadData = new UploadToSQL(pathToResultFiles);
        uploadData->Upload(pathToCSVFiles);//Where?! return status!!!
		delete uploadData;
	}
	else
	{
		statusUpload = "Connection to SQL not found";
		QMessageBox msgBox;
		msgBox.setIcon(QMessageBox::Warning);
		msgBox.setWindowTitle("Warning!");
		msgBox.setText(statusUpload);
		msgBox.exec();

	}

	return statusUpload;
}

QString FormReportByLot::FormReport(QString pathToOutputReport)
{
    /*!
        Forms output report based on input parameters
     */

    QString statusFormReport = "";

    // Open window with parameters
	settingsDateLot = new SetDateLotParameters();

	if (settingsDateLot->exec() == QDialog::Accepted)
	{
        // Get info about using of lot name
		bool useLotNameOnly = settingsDateLot->getUseOnlyLotName();

		QString sQuery;
		SQLQueries expession;
		QSqlQuery query;
		QString lotName = settingsDateLot->getLotName();

		if (useLotNameOnly)
		{
			sQuery = expession.selectionOnlyLotName.arg(lotName);
		}
		else
		{

			QList <int> dateSettings = settingsDateLot->getDateSettings();

			if (dateSettings[0] == 9999)
			{
				int startDay = dateSettings[1];
				int startMonth = dateSettings[2];
				int startYear = dateSettings[3];
				int finishDay = dateSettings[4];
				int finishMonth = dateSettings[5];
				int finishYear = dateSettings[6];


				sQuery = expession.selectionRangeDate.arg(QString::number(startYear), QString::number(startMonth), 
				QString::number(startDay),				
				QString::number(finishYear), 
				QString::number(finishMonth),
				QString::number(finishDay));
			}
			else
			{
				int startDay = dateSettings[0];
				int startMonth = dateSettings[1];
				int startYear = dateSettings[2];

				sQuery = expession.selectionByDate.arg(QString::number(startYear),				
				QString::number(startMonth),
				QString::number(startDay));
			}
		}

		if (!lotName.isEmpty())
		{
			sQuery = sQuery + expession.selectionAdditionalLotName.arg(lotName);
		}

		bool succsessQuery = query.exec(sQuery);
		
		if (succsessQuery)
		{
			int countRecords = query.numRowsAffected();

			if (countRecords > 0)
			{
				QMap <QString, int> dataFromSQL;
				while (query.next())
				{
					for (int i = 3; i < 11; i++)
					{
						QString key = query.value(i).toString();
						if (dataFromSQL.contains(key))
						{
							int value = dataFromSQL[key];
							dataFromSQL[key] = ++value;
						}
						else
						{
							dataFromSQL[key] = 1;
						}
					}
				}

				ErrorsInterpretation* erInter = new ErrorsInterpretation();
				QMap <QString, QString> errors = erInter->getErrorsInterpretation();
				delete erInter;

				QStringList results;

				foreach(QString key, dataFromSQL.keys())
				{
					QString strRes = "0x";
					if (errors.contains(key))
					{
						strRes += key + ";" + errors[key] + ";" + QString::number(dataFromSQL[key]);
					}
					else
					{
						strRes += key + ";Undefined error;" + QString::number(dataFromSQL[key]);
					}
					results.push_back(strRes);
				}

				winResults = new ProcessResults(results, pathToOutputReport);
				winResults->show();

				winResults->WriteReport(results);
                statusFormReport = "0";
			}
			else
			{
				QMessageBox msgBox;
				msgBox.setIcon(QMessageBox::Information);
				msgBox.setWindowTitle("Message");
				statusFormReport = "No data on SQL server for your input parameters";
				msgBox.setText(statusFormReport);
				msgBox.exec();
			}
		}
		else
		{
			statusFormReport = query.lastError().text();
			QMessageBox msgBox;
			msgBox.setIcon(QMessageBox::Critical);
			msgBox.setWindowTitle("Error!");
			msgBox.setText(statusFormReport);
			msgBox.exec();
		}
	}

	return statusFormReport;
}
