#pragma once

#include <QWidget>
#include "ui_process_results.h"

class ProcessResults : public QWidget
{
	Q_OBJECT

public:
	ProcessResults(QStringList result);
	~ProcessResults();

private:
	Ui::ProcessResults* ui;
};
