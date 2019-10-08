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
    UploadToSQL(QString path="");
    void Upload(QStringList pathToCSVFiles);
	~UploadToSQL();

private:
	Ui::UploadToSQL ui;
	QString dirWithFiles;
	Logging* log;
    QString pathToDir;
    QStringList GetFiles(QString path);
	void ConvertCSV(QString dataPath);
	void CreateTable();
	
};
