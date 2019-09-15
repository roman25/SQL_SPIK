/********************************************************************************
** Form generated from reading UI file 'setdate.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETDATE_H
#define UI_SETDATE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SetDate
{
public:
    QGroupBox *gbFinish;
    QComboBox *cbFinishDay;
    QComboBox *cbFinishMonth;
    QComboBox *cbFinishYear;
    QCheckBox *cbRange;
    QGroupBox *gbStart;
    QComboBox *cbStartDay;
    QComboBox *cbStartMonth;
    QComboBox *cbStartYear;
    QPushButton *pbOk;
    QPushButton *pbCancel;
    QLineEdit *lineLotName;
    QCheckBox *cbUseLotName;

    void setupUi(QWidget *SetDate)
    {
        if (SetDate->objectName().isEmpty())
            SetDate->setObjectName(QStringLiteral("SetDate"));
        SetDate->resize(338, 235);
        gbFinish = new QGroupBox(SetDate);
        gbFinish->setObjectName(QStringLiteral("gbFinish"));
        gbFinish->setGeometry(QRect(10, 70, 321, 81));
        cbFinishDay = new QComboBox(gbFinish);
        cbFinishDay->setObjectName(QStringLiteral("cbFinishDay"));
        cbFinishDay->setGeometry(QRect(20, 50, 69, 22));
        cbFinishMonth = new QComboBox(gbFinish);
        cbFinishMonth->setObjectName(QStringLiteral("cbFinishMonth"));
        cbFinishMonth->setGeometry(QRect(110, 50, 111, 22));
        cbFinishYear = new QComboBox(gbFinish);
        cbFinishYear->setObjectName(QStringLiteral("cbFinishYear"));
        cbFinishYear->setGeometry(QRect(240, 50, 69, 22));
        cbRange = new QCheckBox(gbFinish);
        cbRange->setObjectName(QStringLiteral("cbRange"));
        cbRange->setGeometry(QRect(20, 20, 101, 21));
        gbStart = new QGroupBox(SetDate);
        gbStart->setObjectName(QStringLiteral("gbStart"));
        gbStart->setGeometry(QRect(10, 10, 321, 51));
        cbStartDay = new QComboBox(gbStart);
        cbStartDay->setObjectName(QStringLiteral("cbStartDay"));
        cbStartDay->setGeometry(QRect(20, 20, 69, 22));
        cbStartMonth = new QComboBox(gbStart);
        cbStartMonth->setObjectName(QStringLiteral("cbStartMonth"));
        cbStartMonth->setGeometry(QRect(110, 20, 111, 22));
        cbStartYear = new QComboBox(gbStart);
        cbStartYear->setObjectName(QStringLiteral("cbStartYear"));
        cbStartYear->setGeometry(QRect(240, 20, 69, 22));
        pbOk = new QPushButton(SetDate);
        pbOk->setObjectName(QStringLiteral("pbOk"));
        pbOk->setGeometry(QRect(160, 200, 75, 23));
        pbCancel = new QPushButton(SetDate);
        pbCancel->setObjectName(QStringLiteral("pbCancel"));
        pbCancel->setGeometry(QRect(250, 200, 75, 23));
        lineLotName = new QLineEdit(SetDate);
        lineLotName->setObjectName(QStringLiteral("lineLotName"));
        lineLotName->setGeometry(QRect(120, 160, 111, 20));
        cbUseLotName = new QCheckBox(SetDate);
        cbUseLotName->setObjectName(QStringLiteral("cbUseLotName"));
        cbUseLotName->setGeometry(QRect(30, 150, 71, 41));

        retranslateUi(SetDate);

        QMetaObject::connectSlotsByName(SetDate);
    } // setupUi

    void retranslateUi(QWidget *SetDate)
    {
        SetDate->setWindowTitle(QApplication::translate("SetDate", "SetDate", nullptr));
        gbFinish->setTitle(QApplication::translate("SetDate", "Finish date", nullptr));
        cbRange->setText(QApplication::translate("SetDate", "Use date  range", nullptr));
        gbStart->setTitle(QApplication::translate("SetDate", "Start date", nullptr));
        pbOk->setText(QApplication::translate("SetDate", "OK", nullptr));
        pbCancel->setText(QApplication::translate("SetDate", "Cancel", nullptr));
        lineLotName->setText(QString());
        lineLotName->setPlaceholderText(QApplication::translate("SetDate", "Enter lot name", nullptr));
        cbUseLotName->setText(QApplication::translate("SetDate", "Use only\n"
"lot name", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SetDate: public Ui_SetDate {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETDATE_H
