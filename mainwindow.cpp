#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "errors_interpretation.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
	
	isConnected = false;
	ui->pbReport->setEnabled(false);
	ui->pbUploadToSql->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
	delete winResults;
	delete settingsDate;
}

void MainWindow::on_pbReport_clicked()
{
	settingsDate = new SetDate();

	if (settingsDate->exec() == QDialog::Accepted)
	{
		bool useLotNameOnly = settingsDate->getUseOnlyLotName();

		QString sQuery;
		SQLQueries expession;
		QSqlQuery query;
		QString lotName = settingsDate->getLotName();

		if (useLotNameOnly)
		{
			sQuery = expession.selectionOnlyLotName.arg(lotName);
		}
		else
		{

			QList <int> dateSettings = settingsDate->getDateSettings();

			if (dateSettings[0] == 9999)
			{
				int startDay = dateSettings[1];
				int startMonth = dateSettings[2];
				int startYear = dateSettings[3];
				int finishDay = dateSettings[4];
				int finishMonth = dateSettings[5];
				int finishYear = dateSettings[6];

				sQuery = expession.selectionRangeDate.arg(QString::number(startYear), QString::number(finishYear),
					QString::number(startMonth), QString::number(finishMonth),
					QString::number(startDay), QString::number(finishDay));
			}
			else
			{
				int startDay = dateSettings[0];
				int startMonth = dateSettings[1];
				int startYear = dateSettings[2];

				sQuery = expession.selectionByDate.arg(QString::number(startYear),
					QString::number(startMonth),
					QString::number(startDay));
			}
		}
		
		if (!lotName.isEmpty())
		{
			sQuery = sQuery + expession.selectionAdditionalLotName.arg(lotName);
		}

		query.exec(sQuery);

		QMap <QString, int> dataFromSQL;

		while (query.next())
		{

			for (int i = 3; i < 11; i++)
			{
				QString key = query.value(i).toString();
				if (dataFromSQL.contains(key))
				{
					int value			= dataFromSQL[key];
					dataFromSQL[key]	= ++value;
				}
				else
				{					
					dataFromSQL[key] = 1;
				}
			}
		}

		
		ErrorsInterpretation* erInter = new ErrorsInterpretation();
		QMap <QString, QString> errors = erInter->getErrorsInterpretation();
		delete erInter;
		
		int rows = 1;
		QStringList results;
		foreach(QString key, dataFromSQL.keys())
		{
			QString strRes = "0x";
			if (errors.contains(key))
			{				
				strRes += key + ";" + errors[key] + ";" + QString::number(dataFromSQL[key]);
				
			}
			else
			{
				strRes += key + ";Undefined error;-";
			}
			results.push_back(strRes);
			rows++;
		}

		winResults = new ProcessResults(results);
		winResults->show();

		WriteReport(results);
	}
}

void MainWindow::WriteReport(QStringList results)
{
	int rows = results.size();

	// Get current directory and set path to out file
	QString currDir = QDir::currentPath();

	QDate date = QDate::currentDate();

	

	QString filePath = currDir + "/" + "Summary_" + date.toString("yyyy_MM_dd") + ".csv";
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

void MainWindow::on_pbConnect_clicked()
{
	credentials = new Credentials();
	
	if (credentials->exec() == QDialog::Accepted)
	{
		QStringList cred = credentials->getCredentials();

		QString driverName	= cred[0];
		QString serverName	= cred[1];
		QString dbName		= cred[2];
		QString login		= cred[3];
		QString password	= cred[4];

		isConnected = setSQLConnection(driverName, serverName, dbName, login, password);
	}

	delete credentials;
}

bool MainWindow::setSQLConnection(QString driverName, QString serverName, QString dbName, QString login, QString password)
{
	QSqlDatabase db = QSqlDatabase::addDatabase(driverName);

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
		ui->pbUploadToSql->setEnabled(true);

	}

	return true;
}



void MainWindow::on_pbUploadToSql_clicked()
{
	uploadData = new UploadToSQL();

	uploadData->Upload();

	delete uploadData;
	
}