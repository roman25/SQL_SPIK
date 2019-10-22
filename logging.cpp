#include "logging.h"

Logging::Logging(QString pathToDirWithLog)	
{
    const QString fileName     = "spik_sql.log";
	const QString fullFilePath = pathToDirWithLog + "/" + fileName;

	file.setFileName(fullFilePath);
}

Logging::~Logging()
{
}

void Logging::WriteIntoLog(QString message)
{
	QDateTime dateTime = QDateTime::currentDateTime();

	QString time = dateTime.toString("dd-MMM HH:mm:ss");
    if (file.open(QIODevice::WriteOnly | QIODevice::Append))
    {
        stream.setDevice(&file);
        stream << time << "\t"  << message << "\r\n";
    }
    file.close();
}
