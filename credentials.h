#pragma once

#include <QWidget>
#include <QDialog>
#include "QDebug"
#include "QtSql"
#include <QSettings>

#include "ui_credentials.h"

#define ORGANIZATION_NAME "GS NANOTECH"
#define APPLICATION_NAME "SPiK"
#define SETTINGS_TRAY "settings/tray"

class Credentials : public QDialog
{
	Q_OBJECT

public:
	Credentials(QWidget *parent = Q_NULLPTR);
	QStringList getCredentials();
	~Credentials();

private:
	Ui::Credentials* ui;
	QStringList listCredentials;

	QSettings* appSettings;

	void LoadLastSettings();
	void SaveLastSettings(int driverValue, QString serverName, QString dbName, QString login);

private slots:	
	void on_pbOk_clicked();
	void on_pbCancel_clicked();

};
