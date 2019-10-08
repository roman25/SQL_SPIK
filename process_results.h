#pragma once

#include <QWidget>
#include <QDir>
#include <QDateTime>
#include <QTextStream>
#include <QFileDialog>
#include "ui_process_results.h"
#include "logging.h"

class ProcessResults : public QWidget
{
	Q_OBJECT

public:
	ProcessResults(QStringList result, QString pathToOutputReport);
	~ProcessResults();

	void WriteReport(QStringList results);
private:
	Ui::ProcessResults* ui;
	QString m_pathToReport;
    Logging* log;

};
