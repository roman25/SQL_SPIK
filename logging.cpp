#include "logging.h"

Logging::Logging()	
{
	QDir().mkdir(folderName);

	QString currentDirectory = QDir::currentPath();
	const QString fullFilePath = QDir(currentDirectory).filePath(folderName + "/" + fileName);

	file.setFileName(fullFilePath);
	
	if (file.open(QIODevice::ReadWrite))
	{
		stream.setDevice(&file);
	}
	else
	{
		WriteIntoLog("Some error occurred while creating log file");
	}

}

Logging::~Logging()
{
}

void Logging::WriteIntoLog(QString message)
{
	QDateTime dateTime = QDateTime::currentDateTime();

	QString time = dateTime.toString("dd-MMM HH:mm:ss");
	stream << time << "\t"  << message << "\n";
	
}