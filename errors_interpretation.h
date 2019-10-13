#pragma once

#include <QObject>
#include <QMap>
#include <QString>

class ErrorsInterpretation : public QObject
{
	Q_OBJECT

public:
	ErrorsInterpretation();

	QMap <int,  QString> getErrorsInterpretation();

	~ErrorsInterpretation();
private:
	const QString templateName = "errors_decoding.tab";
};
