#pragma once

#include <QWidget>
#include <QDialog>
#include "QDebug"
#include "QtSql"

#include "ui_credentials.h"

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

private slots:	
	void on_pbOk_clicked();
	void on_pbCancel_clicked();

};
