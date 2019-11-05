#include "process_results.h"
#include <QTableWidget>
#include <QTableWidgetItem>

ProcessResults::ProcessResults(QStringList result, QString pathToOutputReport)
	: ui(new Ui::ProcessResults), m_pathToReport(pathToOutputReport)
{
	ui->setupUi(this);

	int rows = result.size();
	ui->twResults->setRowCount(rows);
	ui->twResults->setColumnCount(3);

	for (int i = 0; i < rows; i++)
	{
		QStringList tempRes = result[i].split(";");

        // Get error
        bool convert;
        QString error = tempRes[0];
        int numError = error.toInt(&convert, 16);

		for (int j = 0; j < 3; j++)
		{
			QTableWidgetItem *newCell = new QTableWidgetItem(tempRes[j]);
            tableData.append(newCell);
			ui->twResults->setItem(i, j, newCell);
		}									
	}	
}

ProcessResults::~ProcessResults()
{
    foreach(QTableWidgetItem *newCell, tableData)
    {
        delete newCell;
    }
}

QString ProcessResults::WriteReport(QStringList results)
{
    QString statusWriteReport;

	int rows           = results.size();
	QDateTime dateTime = QDateTime::currentDateTime();

	QString filePath = m_pathToReport + "/" + "Summary_" + dateTime.toString("yyyy_MM_dd HH.mm.ss") + ".csv";
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

        statusWriteReport = "0";
	}
    else
    {
        statusWriteReport = "Some errors occurred while creating output report";
    }

	file.close();
    
    return statusWriteReport;
}
