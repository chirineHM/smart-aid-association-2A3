QT       += core gui sql
QT        +=core gui svg
QT        +=serialport
QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    animaux.cpp \
    arduino.cpp \
    connection.cpp \
    dons.cpp \
    employe.cpp \
    evenement.cpp \
    excel.cpp \
    gestion_employe.cpp \
    interventions.cpp \
    login.cpp \
    main.cpp \
    mainwindow.cpp \
    popup.cpp \
    profils.cpp \
    qcustomplot.cpp \
    qrcode.cpp \
    rfid.cpp \
    smtp.cpp

HEADERS += \
    animaux.h \
    arduino.h \
    connection.h \
    dons.h \
    employe.h \
    evenement.h \
    excel.h \
    gestion_employe.h \
    interventions.h \
    login.h \
    mainwindow.h \
    popup.h \
    profils.h \
    qcustomplot.h \
    qrcode.h \
    rfid.h \
    smtp.h

FORMS += \
    gestion_employe.ui \
    login.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
