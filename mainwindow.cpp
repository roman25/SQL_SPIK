#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QString pathToInputDirWithCSV     = "D:\\projects\\GS_docs\\SQL_SPIK";
    QString pathToOutputDirWithReport = "D:\\projects\\GS_docs\\SQL_SPIK\\reports";
    QString pathToDirWithLogFile      = "D:\\projects\\SQL_SPIK\\logs";


    bdSpik = new BDSpik(pathToInputDirWithCSV, pathToOutputDirWithReport);
    log    = new Logging(pathToDirWithLogFile);

}

MainWindow::~MainWindow()
{
	delete bdSpik;
    delete log;
}

void MainWindow::on_pbReport_clicked()
{		
	QString createReport = bdSpik->FormReport();
    if (createReport != "0")
	{
        log->WriteIntoLog(createReport);
    }
}


void MainWindow::on_pbConnect_clicked()
{
	QString statusConnection = bdSpik->JoinToSQLServer();
    // set date time format
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
    QStringList listFilesName = recoredDir.entryList(filters, QDir::Files);

    QString statusUpload = bdSpik->UploadDataToSQL(listFilesName); // file names only
	
	if (statusUpload != "0")
	{
        log->WriteIntoLog(statusUpload);
    }
}
