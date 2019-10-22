#pragma once

#include <QObject>
#include <QDir>
#include <QTextStream>
#include <QDateTime>

class Logging : public QObject
{
	Q_OBJECT

public:
	Logging(QString pathToDirWithLog);
	~Logging();

	void WriteIntoLog(QString message);

private:	    
	QFile file;
	QTextStream stream;
};
