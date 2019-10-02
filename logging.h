#pragma once

#include <QObject>
#include <QDir>
#include <QTextStream>
#include <QDateTime>

class Logging : public QObject
{
	Q_OBJECT

public:
	Logging();
	~Logging();

	void WriteIntoLog(QString message);

private:
	const QString folderName = "logs";
	const QString fileName	 = "spik_sql.log";
	QFile file;
	QTextStream stream;
};
