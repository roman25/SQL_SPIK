#include "process_results.h"
#include <QTableWidget>
#include <QTableWidgetItem>

ProcessResults::ProcessResults(QStringList result)
	: ui(new Ui::ProcessResults)
{
	ui->setupUi(this);

	int rows = result.size();
	ui->twResults->setRowCount(rows);
	ui->twResults->setColumnCount(3);

	for (int i = 0; i < rows; i++)
	{
		QStringList tempRes = result[i].split(";");
		for (int j = 0; j < 3; j++)
		{
			QTableWidgetItem* newCell = new QTableWidgetItem(tempRes[j]);
			ui->twResults->setItem(i, j, newCell);
		}									
	}	
}

ProcessResults::~ProcessResults()
{
}

void ProcessResults::WriteReport(QStringList results)
{
	int rows = results.size();
	QString pathToReport = QFileDialog::getExistingDirectory(this, tr("Choose a directory to save results"));
	QDate date = QDate::currentDate();

	QString filePath = pathToReport + "/" + "Summary_" + date.toString("yyyy_MM_dd") + ".csv";
	QFile file(filePath);

	// Remove old report if it exists
	file.remove();

	// Write to .rst from input
	if (file.open(QIODevice::ReadWrite))
	{
		QTextStream stream(&file);

		stream << "Failture;Description;Count\n";
		for (int i = 0; i < rows; i++)
		{
			stream << results[i] + "\n";
		}
	}

	file.close();
}
