#include "credentials.h"
#include <QStringList>
#include "uploadtosql.h"


Credentials::Credentials(QWidget *parent)
	: QDialog(parent),
	ui(new Ui::Credentials)
{

	ui->setupUi(this);
	appSettings = new QSettings(ORGANIZATION_NAME, APPLICATION_NAME);


	LoadLastSettings();

}

Credentials::~Credentials()
{
	delete appSettings;
}


void Credentials::on_pbOk_clicked()
{
	/*!
		Gets data from UI and sets new values after push on OK button
	*/
	QString driverName	= ui->cbDriver->currentText();
	int driverValue		= ui->cbDriver->currentIndex();
	QString serverName	= ui->lineServer->text();
	QString dbName		= ui->lineDbName->text();
	QString login		= ui->lineLogin->text();
	QString password	= ui->linePassword->text();

	listCredentials.push_back(driverName);
	listCredentials.push_back(serverName);
	listCredentials.push_back(dbName);
	listCredentials.push_back(login);
	listCredentials.push_back(password);

	SaveLastSettings(driverValue, serverName, dbName, login);

	// Close UI
	QDialog::accept();
	close();
}

void Credentials::LoadLastSettings()
{
	int driverValue		= appSettings->value("Driver").toInt();	
	QString serverName	= appSettings->value("Server").toString();
	QString dbName		= appSettings->value("DataBase").toString();
	QString login		= appSettings->value("Login").toString();
	

	ui->cbDriver->setCurrentIndex(driverValue);
	ui->lineServer->setText(serverName);
	ui->lineDbName->setText(dbName);
	ui->lineLogin->setText(login);

}

void Credentials::SaveLastSettings(int driverValue, QString serverName, QString dbName, QString login)
{
	appSettings->setValue("Driver", driverValue);
	appSettings->setValue("Server", serverName);
	appSettings->setValue("DataBase", dbName);
	appSettings->setValue("Login", login);
}

void Credentials::on_pbCancel_clicked()
{
	/*!
		Process Cancel button
	*/

	// Close UI
	QDialog::Rejected;
	close();
}


QStringList Credentials::getCredentials()
{
	return listCredentials;
}