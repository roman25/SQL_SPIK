#include "bdspik.h"

BDSpik::BDSpik(QString pathToInputDir, QString pathToOutputDir) :
    m_pathToDirWithCSV(pathToInputDir), m_pathToDirWithReport(pathToOutputDir)
{    
	isConnected = false;
}

BDSpik::~BDSpik()
{
    foreach (ProcessResults *objRes, procRes)
    {
        delete objRes;
    }
}

QString BDSpik::JoinToSQLServer()
{
    /*!
        Creates connection to SQL server
     */

    // Save status of connection
    QString statusConnect;

    // Open window to get credentials
    Credentials *credentials = new Credentials();
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
		}
		else
		{
            // Set parameters of date format in SQL and execute the query
			SQLQueries expession;
			QString sQuery = expession.setDateFortmat;
			
			QSqlQuery query;
			bool execute = query.exec(sQuery);
			if (!execute)
			{
				statusConnect = "Some errors occurred when change date format of SQL server";
			}
			else
			{
				isConnected   = true;
                statusConnect = "0";
			}
		}
	}

	delete credentials;

	return statusConnect;
}

QString BDSpik::UploadDataToSQL(QStringList listCSVFiles)
{
    /*!
        Uploads data on SQL server
    */

    // Status of uploading
    QString statusUpload;

    // Upload if connection is present
    if (isConnected)
	{        
        UploadToSQL *uploadData = new UploadToSQL(m_pathToDirWithCSV);
		statusUpload = uploadData->Upload(listCSVFiles);
		delete uploadData;

        if (statusUpload != "0")
        {
            return statusUpload;
        }
	}
	else
	{
		statusUpload = "Connection to SQL not found";
	}

	return statusUpload;
}

QString BDSpik::FormReport()
{
    /*!
        Forms output report based on input parameters
     */

    QString statusFormReport;

    // Open window with parameters
    SetDateLotParameters *settingsDateLot = new SetDateLotParameters();

	if (settingsDateLot->exec() == QDialog::Accepted)
	{
        // Get info about using of lot name
		bool useLotNameOnly = settingsDateLot->getUseOnlyLotName();

		QString sQuery;
		SQLQueries expession;
		QSqlQuery query;
		QString lotName = settingsDateLot->getLotName();

        // Check - using lot names only
		if (useLotNameOnly)
		{
			sQuery = expession.selectionOnlyLotName.arg(lotName);
		}
		else
		{
            // Get date parameters
			QList <int> dateSettings = settingsDateLot->getDateSettings();

            // Choose settings based on single date or range
			if (dateSettings[0] == 9999)
			{
				int startDay    = dateSettings[1];
				int startMonth  = dateSettings[2];
				int startYear   = dateSettings[3];
				int finishDay   = dateSettings[4];
				int finishMonth = dateSettings[5];
				int finishYear  = dateSettings[6];

				sQuery = expession.selectionRangeDate.arg(QString::number(startYear), QString::number(startMonth), 
				QString::number(startDay),				
				QString::number(finishYear), 
				QString::number(finishMonth),
				QString::number(finishDay));
			}
			else
			{
				int startDay   = dateSettings[0];
				int startMonth = dateSettings[1];
				int startYear  = dateSettings[2];

				sQuery = expession.selectionByDate.arg(QString::number(startYear),				
				QString::number(startMonth),
				QString::number(startDay));
			}
		}

        // Choose parameters when using date and lot name
		if (!lotName.isEmpty())
		{
			sQuery = sQuery + expession.selectionAdditionalLotName.arg(lotName);
		}

        // Execute expression
		bool succsessQuery = query.exec(sQuery);		
		if (succsessQuery)
		{
            // Get count records of returned data
			int countRecords = query.numRowsAffected();

			if (countRecords > 0)
			{
                // Read data from SQL
				QMap <int, int> dataFromSQL;
				while (query.next())
				{
                    // Values 3 and 10 because MKM columns have order from 3 to 10
					for (int i = 3; i < 11; i++)
					{
                        // Read value and convert it from hex to dec
                        QString strKey = query.value(i).toString();                        
                        bool convert;
                        int key = strKey.toInt(&convert, 16);

                        // Collect data from SQL
						if (dataFromSQL.contains(key))
						{
							int value        = dataFromSQL[key];
							dataFromSQL[key] = ++value;
						}
						else
						{
							dataFromSQL[key] = 1;
						}
					}
				}

                // Get errors description
				ErrorsInterpretation* erInter = new ErrorsInterpretation();
				QMap <int, QString> errors    = erInter->getErrorsInterpretation();                
				delete erInter;

                // Check error from SQL in predefined description
                if (errors.contains(-1))
                {
                    statusFormReport = errors[-1];
                    return statusFormReport;
                }

                // Collecting results to output to report
				QStringList results;
				foreach(int key, dataFromSQL.keys())
				{
					QString strRes = "0x";
					if (errors.contains(key))
					{
                        QString errorType = QString::number(key, 16);
                        if (errorType == "0")
                        {
                            errorType += "0";
                        }

						strRes += errorType + ";" + errors[key] + ";" + QString::number(dataFromSQL[key]);
					}
					else
					{
                        QString errorType = QString::number(key, 16);
                        if (errorType == "0")
                        {
                            errorType += "0";
                        }

						strRes += errorType + ";Undefined error;" + QString::number(dataFromSQL[key]);
					}
					results.push_back(strRes);
				}

                // Create window with report
                ProcessResults *winResults = new ProcessResults(results, m_pathToDirWithReport);
                procRes.append(winResults);
				winResults->show();

                // Write csv report
                statusFormReport = winResults->WriteReport(results);
                if (statusFormReport != "0")
                {
                    return statusFormReport;
                }
                statusFormReport = "0";

			}
			else
			{
				statusFormReport = "No data on SQL server for your input parameters";
			}
		}
		else
		{
			statusFormReport = query.lastError().text();

		}
	}

    delete settingsDateLot;

	return statusFormReport;
}
