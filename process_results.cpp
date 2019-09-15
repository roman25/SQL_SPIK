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
