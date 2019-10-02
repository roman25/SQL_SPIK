#-------------------------------------------------
#
# Project created by QtCreator 2019-07-30T21:19:41
#
#-------------------------------------------------

QT      += core gui sql
CONFIG  += c++11 console

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SQL_SPIK
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    credentials.cpp \
    errors_interpretation.cpp \
    formreportbylot.cpp \
    logging.cpp \
    main.cpp \
    mainwindow.cpp \
    process_results.cpp \
    setdatelotparameters.cpp \
    sql_expressions.cpp \
    uploadtosql.cpp

HEADERS += \
    credentials.h \
    errors_interpretation.h \
    formreportbylot.h \
    logging.h \
    mainwindow.h \
    process_results.h \    
    setdatelotparameters.h \
    sql_expressions.h \
    uploadtosql.h
    resource.h \

FORMS += \
        credentials.ui
        mainwindow.ui
        process_results.ui
        setdate.ui
