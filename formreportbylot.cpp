#include "formreportbylot.h"

FormReportByLot::FormReportByLot()
{
	isConnected = false;
	log = new Logging();
}

FormReportByLot::~FormReportByLot()
{
	delete log;
}

QString FormReportByLot::JoinToSQLServer()
{
	credentials = new Credentials();

	if (credentials->exec() == QDialog::Accepted)
	{
		QStringList cred = credentials->getCredentials();

		QString driverName	= cred[0];
		QString serverName	= cred[1];
		QString dbName		= cred[2];
		QString login		= cred[3];
		QString password	= cred[4];

		setSQLConnection(driverName, serverName, dbName, login, password);
	}

	delete credentials;

	return "0";
}

QString FormReportByLot::UploadDataToSQL(QStringList pathToCSVFiles)
{
	QString statusUpload = "";
	if (isConnected)
	{
		UploadToSQL* uploadData = new UploadToSQL();
		uploadData->Upload();
		delete uploadData;
		statusUpload = "0";
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

void FormReportByLot::setSQLConnection(QString driverName, QString serverName, QString dbName, QString login, QString password)
{
	QSqlDatabase db = QSqlDatabase::addDatabase(driverName);

	db.setDatabaseName("DRIVER={SQL Server};SERVER=" + serverName + ";DATABASE=" + dbName);
	db.setUserName(login);
	db.setPassword(password);

	if (!db.open())
	{
		QString error = QSqlError(db.lastError()).text();
		QMessageBox msgBox;
		msgBox.setIcon(QMessageBox::Critical);
		msgBox.setWindowTitle("Error!");
		msgBox.setText(error);
		msgBox.exec();
	}
	else
	{
		isConnected = true;
		qDebug() << "Connected";		
		SQLQueries expession;
		QString sQuery = expession.setDateFortmat;
		QSqlQuery query;
		query.exec(sQuery);
	}	
}


QString FormReportByLot::FormReport(QString pathToOutputReport)
{
	settingsDateLot = new SetDateLotParameters();

	if (settingsDateLot->exec() == QDialog::Accepted)
	{
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
			}
			else
			{
				QMessageBox msgBox;
				msgBox.setIcon(QMessageBox::Information);
				msgBox.setWindowTitle("Message");
				msgBox.setText("No data on SQL server for your input parameters");
				msgBox.exec();
			}
		}
		else
		{
			QString error = query.lastError().text();
			QMessageBox msgBox;
			msgBox.setIcon(QMessageBox::Critical);
			msgBox.setWindowTitle("Error!");
			msgBox.setText(error);
			msgBox.exec();
		}
	}

	return "0";
}