/********************************************************************************
** Form generated from reading UI file 'uploadtosql.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UPLOADTOSQL_H
#define UI_UPLOADTOSQL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_UploadToSQL
{
public:

    void setupUi(QWidget *UploadToSQL)
    {
        if (UploadToSQL->objectName().isEmpty())
            UploadToSQL->setObjectName(QStringLiteral("UploadToSQL"));
        UploadToSQL->resize(400, 300);

        retranslateUi(UploadToSQL);

        QMetaObject::connectSlotsByName(UploadToSQL);
    } // setupUi

    void retranslateUi(QWidget *UploadToSQL)
    {
        UploadToSQL->setWindowTitle(QApplication::translate("UploadToSQL", "UploadToSQL", nullptr));
    } // retranslateUi

};

namespace Ui {
    class UploadToSQL: public Ui_UploadToSQL {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UPLOADTOSQL_H
