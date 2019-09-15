#pragma once

#include <QWidget>
#include "ui_setdate.h"
#include "QDebug"
#include <QDialog>

class SetDate : public QDialog
{
	Q_OBJECT

public:
	SetDate(QWidget *parent = Q_NULLPTR);
	~SetDate();
	QList <int> getDateSettings();
	QString getLotName();
	bool getUseOnlyLotName();

private:
	Ui::SetDate* ui;

	QList <int> dateSettings;
	QString lotName;
	bool useLotName;

private slots:
	void on_pbOk_clicked();
	void on_pbCancel_clicked();
	void on_cbRange_clicked();

};
