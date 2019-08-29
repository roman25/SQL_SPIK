#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QDebug"
#include "QtSql"

#include "credentials.h"
#include "setdate.h"
#include "sql_expressions.h"

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
	Credentials* credentials;

	bool setSQLConnection(QString serverName, QString dbName, QString login, QString password);

	bool isConnected;

private slots:
	void on_pbConnect_clicked();
	void on_pbReport_clicked();
};

#endif // MAINWINDOW_H
