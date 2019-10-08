#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QDebug"
#include <QtSql>

#include "formreportbylot.h"
#include "logging.h"

namespace Ui
{
	class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

	FormReportByLot* formReport;
    Logging* log;

private slots:
	void on_pbConnect_clicked();
	void on_pbReport_clicked();
	void on_pbUploadToSql_clicked();
};

#endif // MAINWINDOW_H
