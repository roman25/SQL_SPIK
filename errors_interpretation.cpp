#include "errors_interpretation.h"

#include <QTextStream>
#include <QDir>

ErrorsInterpretation::ErrorsInterpretation()	
{
}

ErrorsInterpretation::~ErrorsInterpretation()
{
 
}


QMap <int, QString> ErrorsInterpretation::getErrorsInterpretation()
{
    /*!
        Reads the template with descripton of errors
    */

    // Get current directory
	QString currentDirectory = QDir::currentPath();

    // Set full path to the template
	QString fullFilePath = QDir(currentDirectory).filePath(templateName);

    // Create map to store error and its description
	QMap <int, QString> errors;

	// Read input file
	QFile dataFile(fullFilePath);
	QTextStream csvStream(&dataFile);
	if (dataFile.open(QIODevice::ReadOnly))
	{
        // Read the file
		while (!csvStream.atEnd())
		{

			// Read a line
            QString line     = csvStream.readLine();
			QStringList data = line.split("\t");

            // Get error
            bool convert;
			QString error = data[0];			
			int numError  = error.toInt(&convert, 16);

			if (convert)
			{
				// Get description of the error and collect into map
				QString description = data[1];
				errors[numError]    = description;
			}
			else
			{
				QString mes = "Can not convert hex to dec in " + templateName;
				errors[-1]	= mes;
                return errors;
			}
		}
	}
    else
    {
        QString mes = "Can not open the template with errors";
		errors[-1] = mes;
        
    }
	return errors;
}
