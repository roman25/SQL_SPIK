#include "setdatelotparameters.h"
#include <QDateTime>

SetDateLotParameters::SetDateLotParameters(QWidget *parent)
	: QDialog(parent),
	ui(new Ui::SetDate)
{

	ui->setupUi(this);

	QStringList year, day;

	QStringList month = { "January", "February", "March", "April", "May", "June",
		"July", "August", "September", "October", "November", "December" };

	for (int i = 1; i < 2100; i++)
	{
		year.push_back(QString::number(i));
	}

	for (int i = 1; i < 32; i++)
	{
		day.push_back(QString::number(i));
	}

	
	ui->cbStartDay->addItems(day);
	ui->cbFinishDay->addItems(day);

	ui->cbStartMonth->addItems(month);
	ui->cbFinishMonth->addItems(month);

	ui->cbStartYear->addItems(year);
	ui->cbFinishYear->addItems(year);


	// Set current day in menu settings
	QDate date = QDate::currentDate();
	
	int currentDay		= date.day() - 1;
	int currentMonth	= date.month() - 1;
	int currentYear		= date.year() - 1;

	ui->cbStartDay->setCurrentIndex(currentDay);
	ui->cbFinishDay->setCurrentIndex(currentDay);

	ui->cbStartMonth->setCurrentIndex(currentMonth);
	ui->cbFinishMonth->setCurrentIndex(currentMonth);

	ui->cbStartYear->setCurrentIndex(currentYear);
	ui->cbFinishYear->setCurrentIndex(currentYear);

	ui->cbFinishDay->setDisabled(true);
	ui->cbFinishMonth->setDisabled(true);
	ui->cbFinishYear->setDisabled(true);
}

SetDateLotParameters::~SetDateLotParameters()
{
}

void SetDateLotParameters::on_cbRange_clicked()
{
	if (ui->cbRange->isChecked())
	{
		ui->cbFinishDay->setDisabled(false);
		ui->cbFinishMonth->setDisabled(false);
		ui->cbFinishYear->setDisabled(false);
	}
	else
	{
		ui->cbFinishDay->setDisabled(true);
		ui->cbFinishMonth->setDisabled(true);
		ui->cbFinishYear->setDisabled(true);
	}
		
}

void SetDateLotParameters::on_pbOk_clicked()
{
	/*!
	Gets data from UI and sets new values after push on OK button
	*/
	if (ui->cbRange->isChecked())
	{
		dateSettings.push_back(9999);
	}

	dateSettings.push_back(ui->cbStartDay->currentIndex() + 1);
	dateSettings.push_back(ui->cbStartMonth->currentIndex() + 1);
	dateSettings.push_back(ui->cbStartYear->currentIndex() + 1);
	dateSettings.push_back(ui->cbFinishDay->currentIndex() + 1);
	dateSettings.push_back(ui->cbFinishMonth->currentIndex() + 1);
	dateSettings.push_back(ui->cbFinishYear->currentIndex() + 1);

	lotName = ui->lineLotName->text();
	useLotName = ui->cbUseLotName->checkState();
	// Close UI
	QDialog::accept();
	close();
}

void SetDateLotParameters::on_pbCancel_clicked()
{
	/*!
	Process Cancel button
	*/

	// Close UI
	QDialog::Rejected;
	close();
}

QList <int> SetDateLotParameters::getDateSettings()
{
	return dateSettings;
}

QString SetDateLotParameters::getLotName()
{
	return lotName;
}

bool SetDateLotParameters::getUseOnlyLotName()
{
	return useLotName;
}