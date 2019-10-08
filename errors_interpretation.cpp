#include "errors_interpretation.h"

#include <QTextStream>
#include <QDir>

ErrorsInterpretation::ErrorsInterpretation()	
{
    log = new Logging();
}

ErrorsInterpretation::~ErrorsInterpretation()
{
    delete log;
}


QMap <QString, QString> ErrorsInterpretation::getErrorsInterpretation()
{
    /*!
        Reads the template with descripton of errors
    */

    // Get current directory
	QString currentDirectory = QDir::currentPath();

    // Set full path to the template
	QString fullFilePath = QDir(currentDirectory).filePath(templateName);

    // Create map to save error and its description
	QMap <QString, QString> errors;

	// Read input file
	QFile dataFile(fullFilePath);
	QTextStream csvStream(&dataFile);
	if (dataFile.open(QIODevice::ReadOnly))
	{
        // Read the file
		while (!csvStream.atEnd())
		{

			// Read a line
            QString line    = csvStream.readLine();
			QStringList data = line.split("\t");

            // Get error
			QString error		= data[0];

            // Get description of the error
            QString description = data[1];

            // Collect into map
			errors[error] = description;
		}
	}
    else
    {
        QString mes = "Can not open the template with errors";
        log->WriteIntoLog(mes);
    }
	return errors;
}
