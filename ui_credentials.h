/********************************************************************************
** Form generated from reading UI file 'credentials.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CREDENTIALS_H
#define UI_CREDENTIALS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Credentials
{
public:
    QLabel *lbServerName;
    QLabel *lbLogin;
    QLabel *lbPassword;
    QLineEdit *lineLogin;
    QLineEdit *linePassword;
    QPushButton *pbOk;
    QPushButton *pbCancel;
    QLineEdit *lineServer;
    QLabel *lbServerName_2;
    QLineEdit *lineDbName;
    QLabel *lbDriverName;
    QLineEdit *lineDriver;

    void setupUi(QWidget *Credentials)
    {
        if (Credentials->objectName().isEmpty())
            Credentials->setObjectName(QStringLiteral("Credentials"));
        Credentials->resize(310, 206);
        lbServerName = new QLabel(Credentials);
        lbServerName->setObjectName(QStringLiteral("lbServerName"));
        lbServerName->setGeometry(QRect(10, 40, 81, 16));
        lbLogin = new QLabel(Credentials);
        lbLogin->setObjectName(QStringLiteral("lbLogin"));
        lbLogin->setGeometry(QRect(10, 100, 81, 16));
        lbPassword = new QLabel(Credentials);
        lbPassword->setObjectName(QStringLiteral("lbPassword"));
        lbPassword->setGeometry(QRect(10, 130, 81, 16));
        lineLogin = new QLineEdit(Credentials);
        lineLogin->setObjectName(QStringLiteral("lineLogin"));
        lineLogin->setGeometry(QRect(110, 100, 191, 20));
        linePassword = new QLineEdit(Credentials);
        linePassword->setObjectName(QStringLiteral("linePassword"));
        linePassword->setGeometry(QRect(110, 130, 191, 20));
        pbOk = new QPushButton(Credentials);
        pbOk->setObjectName(QStringLiteral("pbOk"));
        pbOk->setGeometry(QRect(40, 170, 75, 23));
        pbCancel = new QPushButton(Credentials);
        pbCancel->setObjectName(QStringLiteral("pbCancel"));
        pbCancel->setGeometry(QRect(140, 170, 75, 23));
        lineServer = new QLineEdit(Credentials);
        lineServer->setObjectName(QStringLiteral("lineServer"));
        lineServer->setGeometry(QRect(110, 40, 191, 20));
        lbServerName_2 = new QLabel(Credentials);
        lbServerName_2->setObjectName(QStringLiteral("lbServerName_2"));
        lbServerName_2->setGeometry(QRect(10, 70, 81, 16));
        lineDbName = new QLineEdit(Credentials);
        lineDbName->setObjectName(QStringLiteral("lineDbName"));
        lineDbName->setGeometry(QRect(110, 70, 191, 20));
        lbDriverName = new QLabel(Credentials);
        lbDriverName->setObjectName(QStringLiteral("lbDriverName"));
        lbDriverName->setGeometry(QRect(10, 10, 81, 16));
        lineDriver = new QLineEdit(Credentials);
        lineDriver->setObjectName(QStringLiteral("lineDriver"));
        lineDriver->setGeometry(QRect(110, 10, 191, 20));

        retranslateUi(Credentials);

        QMetaObject::connectSlotsByName(Credentials);
    } // setupUi

    void retranslateUi(QWidget *Credentials)
    {
        Credentials->setWindowTitle(QApplication::translate("Credentials", "Credentials", nullptr));
        lbServerName->setText(QApplication::translate("Credentials", "Server name", nullptr));
        lbLogin->setText(QApplication::translate("Credentials", "Login", nullptr));
        lbPassword->setText(QApplication::translate("Credentials", "Password", nullptr));
        pbOk->setText(QApplication::translate("Credentials", "OK", nullptr));
        pbCancel->setText(QApplication::translate("Credentials", "Cancel", nullptr));
        lineServer->setText(QApplication::translate("Credentials", "DESKTOP-IAHG3FS\\SQLEXPRESS", nullptr));
        lbServerName_2->setText(QApplication::translate("Credentials", "Database name", nullptr));
        lineDbName->setText(QApplication::translate("Credentials", "SpikSQL", nullptr));
        lbDriverName->setText(QApplication::translate("Credentials", "Driver name", nullptr));
        lineDriver->setText(QApplication::translate("Credentials", "QODBC3", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Credentials: public Ui_Credentials {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREDENTIALS_H
