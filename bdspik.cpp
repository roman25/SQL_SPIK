#include "bdspik.h"

BDSpik::BDSpik(QString pathToInputDir, QString pathToOutputDir) :
    m_pathToDirWithCSV(pathToInputDir), m_pathToDirWithReport(pathToOutputDir)
{    
	isConnected = false;
}

BDSpik::~BDSpik()
{	
}

QString BDSpik::JoinToSQLServer()
{
    /*!
        Creates connection to SQL server
     */

    // Save status of connection
    QString statusConnect;

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
        UploadToSQL* uploadData = new UploadToSQL(m_pathToDirWithCSV);
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
				QMap <int, int> dataFromSQL;
				while (query.next())
				{
					for (int i = 3; i < 11; i++)
					{
                        QString strKey = query.value(i).toString();
                        
                        bool convert;
                        int key = strKey.toInt(&convert, 16);
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

				ErrorsInterpretation* erInter = new ErrorsInterpretation();
				QMap <int, QString> errors    = erInter->getErrorsInterpretation();                
				delete erInter;

                if (errors.contains(-1))
                {
                    QString statusErrorsInterpretation = errors[-1];
                    return statusErrorsInterpretation;
                }

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

				winResults = new ProcessResults(results, m_pathToDirWithReport);
				winResults->show();

				QString statusWriteReport = winResults->WriteReport(results);
                if (statusWriteReport != "0")
                {
                    return statusWriteReport;
                }
                statusFormReport = "0";


                QSqlQuery queryCollectInitialParameters;
                QString selectDistinctValuesToFormReport = expession.selectDistinctValuesToFormReport;
                bool selectData = queryCollectInitialParameters.exec(selectDistinctValuesToFormReport);

                if (selectData)
                {
                    int countRecords = queryCollectInitialParameters.numRowsAffected();

                    if (countRecords > 0)
                    {
                        while (queryCollectInitialParameters.next())
                        {
                            QString lotName    = queryCollectInitialParameters.value(0).toString();
                            QString startTime  = queryCollectInitialParameters.value(1).toString();
                            QString finishTime = queryCollectInitialParameters.value(2).toString();

                            QString selectMKMValues = expession.selectMKMValues;
                            selectMKMValues = selectMKMValues.arg(lotName).arg(startTime).arg(finishTime);


                            QSqlQuery getMKMValues;
                            QMap <int, int> collectedResults;
                            bool getData = getMKMValues.exec(selectMKMValues);
                            if (getData)
                            {
                                while (getMKMValues.next())
                                {
                                    for (int i = 0; i < 8; i++)
                                    {
                                        QString strKey = getMKMValues.value(i).toString();

                                        bool convert;
                                        int key = strKey.toInt(&convert, 16);
                                        if (collectedResults.contains(key))
                                        {
                                            int value = collectedResults[key];
                                            collectedResults[key] = ++value;
                                        }
                                        else
                                        {
                                            collectedResults[key] = 1;
                                        }
                                    }
                                }

                                statusFormReport = "0";
                            }
                            else
                            {
                                statusFormReport = getMKMValues.lastError().text();
                                return statusFormReport;
                            }

                            QSqlQuery getInOut;
                            QString selectInOut = expession.selectInOut;
                            selectInOut = selectInOut.arg(lotName).arg(startTime).arg(finishTime);
                            getData = getInOut.exec(selectInOut);

                            int in = 0;
                            int out = 0;
                            if (getData)
                            {
                                while (getInOut.next())
                                {
                                    in = getInOut.value(0).toInt();
                                    out = getInOut.value(1).toInt();
                                    break;

                                }

                                statusFormReport = "0";
                            }
                            else
                            {
                                statusFormReport = getInOut.lastError().text();
                                return statusFormReport;
                            }

                            QString sqlLineReport = expession.sqlLineReport;
                            foreach(int key, collectedResults.keys())
                            {
                                sqlLineReport += "Bin" + QString::number(key) + ",";
                                
                            }

                            sqlLineReport.chop(1);
                            sqlLineReport += ") values ('" + lotName + "', '" + startTime + "','" + finishTime + "'," + QString::number(in) + "," + QString::number(out) + ",";

                            foreach(int key, collectedResults.keys())
                            {
                                sqlLineReport += QString::number(collectedResults[key]) + "," ;

                            }

                            sqlLineReport.chop(1);
                            sqlLineReport += ")";
                                                                               
                            QString insertValuesReport = expession.insertValuesReport + sqlLineReport;
                            QSqlQuery createSQLReport;
                                
                            bool inserted = createSQLReport.exec(insertValuesReport);

                            if (inserted)
                            {
                                statusFormReport = "0";
                            }
                            else
                            {
                                statusFormReport = createSQLReport.lastError().text();
                                return statusFormReport;

                            }                            
                        }
                    }
                }



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

	return statusFormReport;
}
