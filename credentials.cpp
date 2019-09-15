#include "credentials.h"
#include <QStringList>
#include "uploadtosql.h"


Credentials::Credentials(QWidget *parent)
	: QDialog(parent),
	ui(new Ui::Credentials)
{

	ui->setupUi(this);

}

Credentials::~Credentials()
{
}


void Credentials::on_pbOk_clicked()
{
	/*!
		Gets data from UI and sets new values after push on OK button
	*/
	QString driverName	= ui->lineDriver->text();
	QString serverName	= ui->lineServer->text();
	QString dbName		= ui->lineDbName->text();
	QString login		= ui->lineLogin->text();
	QString password	= ui->linePassword->text();

	listCredentials.push_back(driverName);
	listCredentials.push_back(serverName);
	listCredentials.push_back(dbName);
	listCredentials.push_back(login);
	listCredentials.push_back(password);

	// Close UI
	QDialog::accept();
	close();
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