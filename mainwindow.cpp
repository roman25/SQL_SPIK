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
	formReport->FormReport();
}


void MainWindow::on_pbConnect_clicked()
{

	formReport->JoinToSQLServer();
}


void MainWindow::on_pbUploadToSql_clicked()
{
	formReport->UploadDataToSQL();
	
}