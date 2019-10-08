#include "credentials.h"
#include <QStringList>
#include "uploadtosql.h"

Credentials::Credentials(QWidget *parent)
	: QDialog(parent),
	ui(new Ui::Credentials)
{

	ui->setupUi(this);
	appSettings = new QSettings(ORGANIZATION_NAME, APPLICATION_NAME);

    // Load settings from registry
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

    // Read input parameters
	QString driverName	= ui->cbDriver->currentText();
	int driverValue		= ui->cbDriver->currentIndex();
	QString serverName	= ui->lineServer->text();
	QString dbName		= ui->lineDbName->text();
	QString login		= ui->lineLogin->text();
	QString password	= ui->linePassword->text();

    // Collect input parameters as list
	listCredentials.push_back(driverName);
	listCredentials.push_back(serverName);
	listCredentials.push_back(dbName);
	listCredentials.push_back(login);
	listCredentials.push_back(password);

    // Save settings in registry
	SaveLastSettings(driverValue, serverName, dbName, login);

	// Close UI
	QDialog::accept();
	close();
}

void Credentials::LoadLastSettings()
{
    /*!
        Loads settings from registry
    */

    // Get settings from registry
	int driverValue		= appSettings->value("Driver").toInt();	
	QString serverName	= appSettings->value("Server").toString();
	QString dbName		= appSettings->value("DataBase").toString();
	QString login		= appSettings->value("Login").toString();
	
    // Set settings in UI
	ui->cbDriver->setCurrentIndex(driverValue);
	ui->lineServer->setText(serverName);
	ui->lineDbName->setText(dbName);
	ui->lineLogin->setText(login);
}

void Credentials::SaveLastSettings(int driverValue, QString serverName, QString dbName, QString login)
{
    /*!
        Saves settings in registry
    */

    // Save settings
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
    /*!
        Returns list with credentials
    */
	return listCredentials;
}
