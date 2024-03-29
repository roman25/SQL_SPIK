#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QDebug"
#include <QtSql>

#include "bdspik.h"
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

    BDSpik* bdSpik;
    Logging* log;

private slots:
	void on_pbConnect_clicked();
	void on_pbReport_clicked();
	void on_pbUploadToSql_clicked();
};

#endif // MAINWINDOW_H
