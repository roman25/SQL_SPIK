#include "credentials.h"
#include <QStringList>

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

	serverName	= ui->lineServer->text();
	dbName		= ui->lineDbName->text();
	login		= ui->lineLogin->text();
	password	= ui->linePassword->text();

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