#include "errors_interpretation.h"

#include <QTextStream>
#include <QDir>

ErrorsInterpretation::ErrorsInterpretation()	
{
}

ErrorsInterpretation::~ErrorsInterpretation()
{
}


QMap <QString, QString> ErrorsInterpretation::getErrorsInterpretation()
{
	QString currentDirectory = QDir::currentPath();

	QString fullFilePath = QDir(currentDirectory).filePath(templateName);

	QMap <QString, QString> errors;

	// Read input file
	QFile dataFile(fullFilePath);
	QTextStream csvStream(&dataFile);

	if (dataFile.open(QIODevice::ReadOnly))
	{
		// Read a row from input
		while (!csvStream.atEnd())
		{

			// Read a line
			QString line = csvStream.readLine();
			QStringList data = line.split("\t");

			QString error		= data[0];
			QString description = data[1];

			errors[error] = description;

		}
	}

	return errors;
}