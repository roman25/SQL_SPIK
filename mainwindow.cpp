#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    formReport = new FormReportByLot("D:\\PROJECTS\\ATE_SPiK\\SQL\\Data");
    log = new Logging();

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

    QString hex="0x00";
    QString hex1="0xFA";
    bool ok;
    int h = hex.toInt(&ok, 16);
    int h1 = hex1.toInt(&ok, 16);
    qInfo()<<h<<" "<<h1;
}


void MainWindow::on_pbConnect_clicked()
{
	QString statusConnection = formReport->JoinToSQLServer();
    if (statusConnection != "0")
    {
        log->WriteIntoLog(statusConnection);
    }else{
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
