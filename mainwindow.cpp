#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
	
	isConnected = false;
	ui->pbReport->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pbReport_clicked()
{
	SetDate* s = new SetDate();

	if (s->exec() == QDialog::Accepted)
	{
		QList <int> dateSettings  = s->getDateSettings();

		QSqlQuery query;
		SQLQueries expession;
		QString myQuery;

		if (dateSettings[0] == 9999)
		{
			int startDay	= dateSettings[1];
			int startMonth	= dateSettings[2];
			int startYear	= dateSettings[3];
			int finishDay	= dateSettings[4];
			int finishMonth = dateSettings[5];
			int finishYear	= dateSettings[6];
			
			myQuery = expession.selectionRangeDate.arg(	QString::number(startYear), QString::number(finishYear),
														QString::number(startMonth), QString::number(finishMonth),
														QString::number(startDay), QString::number(finishDay));
		}
		else
		{
			int startDay	= dateSettings[0];
			int startMonth	= dateSettings[1];
			int startYear	= dateSettings[2];

			myQuery = expession.selectionByDate.arg(	QString::number(startYear),
													QString::number(startMonth),
													QString::number(startDay));
		}
		
		query.exec(myQuery);

		while (query.next())
		{
			qDebug() << 
				query.value(0).toString() <<
				query.value(1).toString() << 
				query.value(2).toString() << 
				query.value(3).toString() << 
				query.value(4).toString() << 
				query.value(5).toString() << 
				query.value(6).toString() << 
				query.value(7).toString() << 
				query.value(8).toString() << 
				query.value(9).toString() << 
				query.value(10).toString();
		}
	}
}

void MainWindow::on_pbConnect_clicked()
{
	credentials = new Credentials();
	
	if (credentials->exec() == QDialog::Accepted)
	{
		QStringList cred = credentials->getCredentials();

		QString serverName	= cred[0];
		QString dbName		= cred[1];
		QString login		= cred[2];
		QString password	= cred[3];

		isConnected = setSQLConnection(serverName, dbName, login, password);
	}

	delete credentials;
}

bool MainWindow::setSQLConnection(QString serverName, QString dbName, QString login, QString password)
{
	QSqlDatabase db = QSqlDatabase::addDatabase("QODBC3");

	db.setDatabaseName("DRIVER={SQL Server};SERVER=" + serverName + ";DATABASE=" + dbName);
	db.setUserName(login);
	db.setPassword(password);

	if (!db.open())
	{
		qDebug() << "This is error: " << QSqlError(db.lastError()).text();
	}
	else
	{

		ui->pbReport->setEnabled(true);

	}

	return true;
}