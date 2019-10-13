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


QStringList UploadToSQL::GetFiles(QString path)
{
    /*!
        Gets csv files from input directory
    */

    // Define filter to find files in directory
	QStringList filters{"*.csv"};

    // Get files in directory
    QDir recoredDir(path);
	QStringList listFiles = recoredDir.entryList(filters, QDir::Files);	

	return listFiles;
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
					statusConvert = "Some error occured when update finish time";
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
					statusConvert = "Some error occured while " + nameWithExt + " uploading";
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
    QString sqlQuery = expression.createTable;

    // Execute SQL query
    QSqlQuery query;
    bool tableCreated = query.exec(sqlQuery);

    // Verify result of SQL execution
    if (!tableCreated)
    {       

        // Test the table is exists
        QString sqlQueryExists = expression.checkTableExists;            
        bool tableExist = query.exec(sqlQueryExists);

        if (!tableExist)
        {
			statusCreateTable = "Can not create table";
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
            QString statusConvert = ConvertCSV(path);

            if (statusConvert != "0")
            {
                return statusConvert;
            }
        }
        else
        {
            statusUpload = "Input data is not file";
            return statusUpload;
        }
    }

	return statusUpload;
}
