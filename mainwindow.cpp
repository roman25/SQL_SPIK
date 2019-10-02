#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);		
	formReport = new FormReportByLot();
}

MainWindow::~MainWindow()
{
	delete formReport;
}

void MainWindow::on_pbReport_clicked()
{	
	QString pathToOutputReport = "D:/projects/GS_docs/SQL_SPIK/reports";
	QString createReport = formReport->FormReport(pathToOutputReport);
	if (createReport != "0")
	{
		qDebug() << createReport;
	}
}


void MainWindow::on_pbConnect_clicked()
{

	QString statusConnection = formReport->JoinToSQLServer();
	if (statusConnection != "0")
	{
		qDebug() << statusConnection;
	}
}


void MainWindow::on_pbUploadToSql_clicked()
{
	QStringList pathToCSVFiles = {};
	QString statusUpload = formReport->UploadDataToSQL(pathToCSVFiles);
	
	if (statusUpload != "0")
	{
		qDebug() << statusUpload;
	}
}