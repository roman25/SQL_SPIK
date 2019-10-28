#include "uploadtosql.h"
#include <QDebug>

UploadToSQL::UploadToSQL(QString path) :
    m_pathToDir(path)
{
	ui.setupUi(this);
}

UploadToSQL::~UploadToSQL()
{
}

QString UploadToSQL::CheckLotExists(QString lotName, QString startTime)
{
    QString statusLotExists;
    QSqlQuery query;     
    SQLQueries expession;
    QString sQuery = expession.checkDataUploadedToSQLServer.arg(lotName).arg(startTime);

    bool succsessQuery = query.exec(sQuery);

    if (!succsessQuery)
    {
        statusLotExists = query.lastError().text();
        return statusLotExists;
    }
    else
    {
        statusLotExists = "0";
    }

    int countRecords = query.numRowsAffected();
    if (countRecords > 0)
    {
        statusLotExists = "Lot '" + lotName + "' exists";
    }
    else
    {
        statusLotExists = "0";
    }

    return statusLotExists;
}

QString UploadToSQL::ConvertCSV(QString dataPath)
{
    /*!
        Reads csv and uploads to SQL server
    */

	QString statusConvert;

    //Create object to get info about csv file
    QFileInfo inFile(dataPath);
	
    // Get file name with extension
    QString nameWithExt = inFile.fileName();

    // Convert file name to lot name.
    int strSize     = nameWithExt.size();
    QString lotName = nameWithExt.left(strSize - 4); // Lot name is file name without extension

	// Read input file
	QFile csvFile(dataPath);
	QTextStream csvStream(&csvFile);

    // Open file to read
	if (csvFile.open(QIODevice::ReadOnly))
	{
		int count = 0;
		
		QSqlQuery query;

        // Define object to get SQL expressions
		SQLQueries expession;

        // Save start and finish time
        QString startTime;
		QString finishTime;

        // Read csv
		while (!csvStream.atEnd())
		{			

			// Read a line
			QString line = csvStream.readLine();

            // Split data to get components
            QStringList tempList = line.split(";");

            // Find key row
			if (line.contains("Start >"))
			{
                // Set flag as count = 1 to skip first line
				count = 1;
				continue;
			}
			
            // Read base data
			if (count == 1)
			{
				// no '20' in year column of the source data
				if (tempList[7].size() == 2)
				{
					tempList[7] = "20" + tempList[7];
				}

                // Get start time from file
				startTime = tempList[7] + "-" + tempList[6] + "-" + tempList[5] +
					" " + tempList[1] + ":" + tempList[2] + ":" + tempList[3];

                statusConvert = CheckLotExists(lotName ,startTime);

                if (statusConvert != "0")
                {
                    return statusConvert;
                }

				count++;
			}

            // Find key row
			if (line.contains("End >"))
			{
                // Set flag as count = -1 to skip last line
				count = -1;
				continue;
			}


			if (count == -1)
			{
				// no '20' in year column of the source data
				if (tempList[7].size() == 2)
				{
					tempList[7] = "20" + tempList[7];
				}

                // Get finish time from file
				finishTime = tempList[7] + "-" + tempList[6] + "-" + tempList[5] +
					" " + tempList[1] + ":" + tempList[2] + ":" + tempList[3];

                // Update finish time in SQL table
                QString sqlQuery      = expession.updateFinishTime.arg(finishTime, startTime);
                bool updateFinishTime = query.exec(sqlQuery);
				if (!updateFinishTime)
				{
                    statusConvert = "Some error occured when update finish time;" + query.lastError().text();
					return statusConvert;
				}
				else
				{
					statusConvert = "0";
				}
                count = -100;
			}
			
            if (line.contains("IN"))
            {
                bool convert;
                int in  = tempList[1].toInt(&convert, 10);
                int out = tempList[4].toInt(&convert, 10);
                QString sqlQuery = expession.updateInOut.arg(in).arg(out).arg(lotName).arg(startTime).arg(finishTime);

                bool updateInOut = query.exec(sqlQuery);
                if (!updateInOut)
                {
                    statusConvert = "Some error occured when update IN and OUT values;" + query.lastError().text();
                    return statusConvert;
                }
                else
                {
                    statusConvert = "0";
                }
                break;
            }

            // Collect information from csv
			if (tempList[0] != "" && tempList[0] != "Device")
			{

				for (int i = 1; i < tempList.size(); i++)
				{
					if (tempList[i].startsWith(" "))
					{
                        // Remove whitespaces in row
						tempList[i] = tempList[i].simplified();
						tempList[i] = "0" + tempList[i];
					}
				}

                // Union data to get SQL query
				QString sqlQuery = expession.insertValues.arg(lotName).arg(startTime).arg(startTime).
					arg(tempList[1]).arg(tempList[2]).arg(tempList[3]).arg(tempList[4]).
					arg(tempList[5]).arg(tempList[6]).arg(tempList[7]).arg(tempList[8]).arg(tempList[0]);
				
                // Insert data into SQL table
				bool uploadData = query.exec(sqlQuery);
				if (!uploadData)
				{
					statusConvert = "Some error occured while " + nameWithExt + " uploading;" + query.lastError().text();
					return statusConvert;
				}
				else
				{
					statusConvert = "0";
				}
			}
			count++;
		}
	}
	else
	{
		statusConvert = "Can not open " + dataPath;
		
	}

	return statusConvert;
}

QString UploadToSQL::CreateTable()
{
    /*!
        Creates table on SQL server
    */

	QString statusCreateTable;

    // Get predefined SQL query
    SQLQueries expression;
    QString sqlQuery = expression.createBaseTable;

    // Execute SQL query
    QSqlQuery queryBaseTable;
    bool baseTableCreated = queryBaseTable.exec(sqlQuery);

    sqlQuery = expression.createGSTable;
    QSqlQuery gsTable;
    bool gsTableCreated = gsTable.exec(sqlQuery);

    // Verify result of SQL execution
    if ( (!baseTableCreated) || (!gsTableCreated) )
    {       

        // Test the table is exists
        QSqlQuery checkTable;
        QString sqlQueryExists = expression.checkBaseTableExists;
        bool tableExist = checkTable.exec(sqlQueryExists);

        if (!tableExist)
        {
			statusCreateTable = "Can not create table;" + checkTable.lastError().text();
            return statusCreateTable;
        }
        else
        {
            statusCreateTable = "0";
        }

        sqlQueryExists = expression.checkGSTableExists;
        tableExist = checkTable.exec(sqlQueryExists);

        if (!tableExist)
        {
            statusCreateTable = "Can not create table;" + checkTable.lastError().text();
            return statusCreateTable;
        }
        else
        {
            statusCreateTable = "0";
        }

    }
    else
    {
        statusCreateTable = "0";
    }

	return statusCreateTable;
}

QString UploadToSQL::Upload(QStringList listCSVFiles)
{
    /*!
        Reads input data and uploads on SQL
    */

	QString statusUpload;
    // Create table on SQL server if it need
	statusUpload = CreateTable();

    if (statusUpload != "0")
    {
        return statusUpload;
    }

    // Iterate for every value in input list
    for (int i = 0; i < listCSVFiles.size(); i++)
    {
        // Get info about file
        // This is file or directory
        QString path = m_pathToDir + "\\" + listCSVFiles[i];
        QFileInfo fInfo(path);
        bool isInputFile = fInfo.isFile();        

        // Check input data is file
        if (isInputFile)
        {
            // Upload input data
            statusUpload = ConvertCSV(path);

            if (statusUpload != "0")
            {
                return statusUpload;
            }
        }
        else
        {
            statusUpload = path + " is not file";
            return statusUpload;
        }
    }

	return statusUpload;
}
