#pragma once

#include <QWidget>
#include <QDir>
#include <QDate>
#include <QTextStream>
#include <QFileDialog>
#include "ui_process_results.h"

class ProcessResults : public QWidget
{
	Q_OBJECT

public:
	ProcessResults(QStringList result);
	~ProcessResults();

	void WriteReport(QStringList results);
private:
	Ui::ProcessResults* ui;
};
