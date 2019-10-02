#include "uploadtosql.h"
#include <QDebug>

UploadToSQL::UploadToSQL()
{
	ui.setupUi(this);
		
	log = new Logging();
	CreateTable();
		
}

UploadToSQL::~UploadToSQL()
{
	delete log;
}


QStringList UploadToSQL::GetFiles()
{
	dirWithFiles = QFileDialog::getExistingDirectory(this, tr("Open Directory"));
	QDir recoredDir(dirWithFiles);

	QStringList filters{"*.csv"};
	QStringList listFiles = recoredDir.entryList(filters, QDir::Files);	

	return listFiles;
}

void UploadToSQL::ConvertCSV(QString dataPath)
{
	QFileInfo f(dataPath);
	
	QString nameWithExt = f.fileName();
	int strSize = nameWithExt.size();

	QString lotName = nameWithExt.left(strSize - 4);

	// Read input file
	QFile csvFile(dataPath);
	QTextStream csvStream(&csvFile);

	SQLQueries expession;
	

	// add conditions, errors etc to GUI
	if (csvFile.open(QIODevice::ReadOnly))
	{
		int count = 0;
		
		QSqlQuery query;

		SQLQueries expession;


		QStringList csvData;
		QString startTime;
		QString finishTime;

		// Read a row from input
		while (!csvStream.atEnd())
		{			

			// Read a line
			QString line			= csvStream.readLine();
			QStringList tempList	= line.split(";");

			if (line.contains("Start >"))
			{
				count = 1;
				continue;
			}
			
			if (count == 1)
			{
				// no '20' in year column of the source data
				if (tempList[7].size() == 2)
				{
					tempList[7] = "20" + tempList[7];
				}

				startTime = tempList[7] + "-" + tempList[6] + "-" + tempList[5] +
					" " + tempList[1] + ":" + tempList[2] + ":" + tempList[3];
				count++;
			}


			if (line.contains("End >"))
			{
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

				finishTime = tempList[7] + "-" + tempList[6] + "-" + tempList[5] +
					" " + tempList[1] + ":" + tempList[2] + ":" + tempList[3];

				QString sqlQuery = expession.updateFinishTime.arg(finishTime, startTime);
				bool updateFinishTime = query.exec(sqlQuery);

				if (!updateFinishTime)
				{
					QString mes = "Some error occured when update finish time";
					log->WriteIntoLog(mes);
				}
				break;
			}
			
			if (tempList[0] != "" && tempList[0] != "Device")
			{

				for (int i = 1; i < tempList.size(); i++)
				{
					if (tempList[i].startsWith(" "))
					{
						tempList[i] = tempList[i].simplified();
						tempList[i] = "0" + tempList[i];
					}
				}

				QString sqlQuery = expession.insertValues.arg(lotName).arg(startTime).arg(startTime).
					arg(tempList[1]).arg(tempList[2]).arg(tempList[3]).arg(tempList[4]).
					arg(tempList[5]).arg(tempList[6]).arg(tempList[7]).arg(tempList[8]).arg(tempList[0]);
				
				bool uploadData = query.exec(sqlQuery);

				if (!uploadData)
				{
					QString mes = "Some error occured while " + nameWithExt + " uploading";
					log->WriteIntoLog(mes);
				}
			}
			count++;
		}
	}
	else
	{
		QString mes = "Can not open " + dataPath;
		log->WriteIntoLog(mes);
	}
}

void UploadToSQL::CreateTable()
{
	QSqlQuery query;

	SQLQueries expession;
	QString sqlQuery = expession.createTable;

	// add exceptions	
	bool tableCreated = query.exec(sqlQuery);

	if (!tableCreated)
	{
		QString mes = "Can not create table";
		log->WriteIntoLog(mes);
	}

}

void UploadToSQL::Upload()
{
	QStringList listFiles = GetFiles();

	for (int i = 0; i < listFiles.size(); i++)
	{
		QString filePath = QDir(dirWithFiles).filePath(listFiles[i]);		
		ConvertCSV(filePath);
	}
	
}
