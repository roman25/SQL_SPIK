#pragma once

#include <QWidget>
#include <QDialog>
#include "QtSql"

#include <QFileDialog>
#include <QFileInfo>

#include "sql_expressions.h"
#include "ui_uploadtosql.h"
#include "logging.h"

class UploadToSQL : public QDialog
{
	Q_OBJECT

public:
    UploadToSQL(QString pathToDirWithCSV);
    ~UploadToSQL();
	QString Upload(QStringList pathToCSVFiles);
	
private:
	Ui::UploadToSQL ui;
	QString dirWithFiles;	
    QString m_pathToDir;
    
	QString ConvertCSV(QString dataPath);
	QString CreateTable();
    QString CheckLotExists(QString lotName, QString startTime);
    QString UploadToReportTable();
	
};
