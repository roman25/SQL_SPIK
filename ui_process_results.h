/********************************************************************************
** Form generated from reading UI file 'process_results.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROCESS_RESULTS_H
#define UI_PROCESS_RESULTS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ProcessResults
{
public:
    QTableWidget *twResults;

    void setupUi(QWidget *ProcessResults)
    {
        if (ProcessResults->objectName().isEmpty())
            ProcessResults->setObjectName(QStringLiteral("ProcessResults"));
        ProcessResults->resize(381, 300);
        twResults = new QTableWidget(ProcessResults);
        if (twResults->columnCount() < 3)
            twResults->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        twResults->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        twResults->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        twResults->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        twResults->setObjectName(QStringLiteral("twResults"));
        twResults->setGeometry(QRect(10, 10, 361, 281));

        retranslateUi(ProcessResults);

        QMetaObject::connectSlotsByName(ProcessResults);
    } // setupUi

    void retranslateUi(QWidget *ProcessResults)
    {
        ProcessResults->setWindowTitle(QApplication::translate("ProcessResults", "ProcessResults", nullptr));
        QTableWidgetItem *___qtablewidgetitem = twResults->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("ProcessResults", "Failure", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = twResults->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("ProcessResults", "Description", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = twResults->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("ProcessResults", "Count", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ProcessResults: public Ui_ProcessResults {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROCESS_RESULTS_H
