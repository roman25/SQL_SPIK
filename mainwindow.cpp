#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    formReport = new FormReportByLot("D:\\projects\\GS_docs\\SQL_SPIK");
    log        = new Logging();

}

MainWindow::~MainWindow()
{
	delete formReport;
    delete log;
}

void MainWindow::on_pbReport_clicked()
{	
	QString pathToOutputReport = "D:/projects/GS_docs/SQL_SPIK/reports";
	QString createReport = formReport->FormReport(pathToOutputReport);
    if (createReport != "0")
	{
        log->WriteIntoLog(createReport);
    }
}


void MainWindow::on_pbConnect_clicked()
{
	QString statusConnection = formReport->JoinToSQLServer();
    if (statusConnection != "0")
    {
        log->WriteIntoLog(statusConnection);
    }
	else{
        ui->connectLabel->setText("Success connected");
    }
}


void MainWindow::on_pbUploadToSql_clicked()
{
    QString dirWithFiles = QFileDialog::getExistingDirectory(this, tr("Open Directory"));
    QDir recoredDir(dirWithFiles);
    QStringList filters{"*.csv"};
    QStringList listFiles = recoredDir.entryList(filters, QDir::Files);

    QString statusUpload = formReport->UploadDataToSQL(listFiles);
	
	if (statusUpload != "0")
	{
        log->WriteIntoLog(statusUpload);
    }else{
        //!!!
    }
}
