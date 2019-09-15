#pragma once

#include <QWidget>
#include <QDialog>
#include "QtSql"

#include <QFileDialog>

#include "sql_expressions.h"
#include "ui_uploadtosql.h"

class UploadToSQL : public QDialog
{
	Q_OBJECT

public:
	UploadToSQL(QWidget *parent = Q_NULLPTR);
	void Upload();
	~UploadToSQL();

private:
	Ui::UploadToSQL ui;

	QStringList GetFiles();
	void ConvertCSV(QString dataPath);
	void CreateTable();
	
};
