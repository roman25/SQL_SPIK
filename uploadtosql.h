#pragma once

#include <QWidget>
#include <QDialog>
#include "QtSql"

#include <QFileDialog>

#include "sql_expressions.h"
#include "ui_uploadtosql.h"
#include "logging.h"

class UploadToSQL : public QDialog
{
	Q_OBJECT

public:
	UploadToSQL();
	void Upload();
	~UploadToSQL();

private:
	Ui::UploadToSQL ui;
	QString dirWithFiles;
	Logging* log;

	QStringList GetFiles();
	void ConvertCSV(QString dataPath);
	void CreateTable();
	
};
