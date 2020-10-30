QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

win32:{
    VERSION = 1.0.0.1
    QMAKE_TARGET_COMPANY = Andrey Shirshov Co
    QMAKE_TARGET_PRODUCT = Medical directory
    QMAKE_TARGET_DESCRIPTION = Medical reference for Eidos
    QMAKE_TARGET_COPYRIGHT = Andrey Shirshov
    RC_ICONS = $$PWD/doc.ico
}

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    popup.cpp

HEADERS += \
    mainwindow.h \
    popup.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

RESOURCES += \
    rsc.qrc
