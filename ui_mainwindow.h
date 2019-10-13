/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *pbConnect;
    QPushButton *pbReport;
    QPushButton *pbUploadToSql;
    QLabel *connectLabel;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(400, 300);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        pbConnect = new QPushButton(centralWidget);
        pbConnect->setObjectName(QStringLiteral("pbConnect"));
        pbConnect->setGeometry(QRect(20, 20, 91, 31));
        pbReport = new QPushButton(centralWidget);
        pbReport->setObjectName(QStringLiteral("pbReport"));
        pbReport->setGeometry(QRect(20, 70, 91, 31));
        pbUploadToSql = new QPushButton(centralWidget);
        pbUploadToSql->setObjectName(QStringLiteral("pbUploadToSql"));
        pbUploadToSql->setGeometry(QRect(20, 120, 91, 31));
        connectLabel = new QLabel(centralWidget);
        connectLabel->setObjectName(QStringLiteral("connectLabel"));
        connectLabel->setGeometry(QRect(10, 240, 91, 16));
        MainWindow->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        pbConnect->setText(QApplication::translate("MainWindow", "Connect to SQL", nullptr));
        pbReport->setText(QApplication::translate("MainWindow", "Form report", nullptr));
        pbUploadToSql->setText(QApplication::translate("MainWindow", "Upload to SQL", nullptr));
        connectLabel->setText(QApplication::translate("MainWindow", "No connection", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
