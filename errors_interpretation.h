#pragma once

#include <QObject>
#include <QMap>
#include <QString>

#include "logging.h"

class ErrorsInterpretation : public QObject
{
	Q_OBJECT

public:
	ErrorsInterpretation();

	QMap <QString,  QString> getErrorsInterpretation();

	~ErrorsInterpretation();
private:
	const QString templateName = "errors_decoding.tab";

    Logging* log;
};
