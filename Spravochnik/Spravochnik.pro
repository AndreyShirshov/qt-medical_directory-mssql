# Функция создания каталога, если он не существует, а затем копирование некоторых файлов в этот каталог
defineTest(copyFilesToDir) {
    FILES = $$shell_path($$1)  # full filepath (split spaces) or masks * ?
    DIR = $$shell_path($$2)    # directory path
    RETURN = $$escape_expand(\n\t)
    QMAKE_POST_LINK += $$RETURN $$sprintf($$QMAKE_MKDIR_CMD, $$DIR)
    for(FILE,FILES){
        QMAKE_POST_LINK += $$RETURN $$QMAKE_COPY $$quote($$FILE) $$quote($$DIR)
    }
    export(QMAKE_POST_LINK)
}

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

TARGET = Spravochnik
CONFIG -= app_bundle
TEMPLATE = app

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    popup.cpp
	
DISTFILES += \
    README.txt \
    settings.ini

HEADERS += \
    mainwindow.h \
    popup.h

FORMS += \
    mainwindow.ui

DISTFILES +=

RESOURCES += \
    rsc.qrc

win32:{
    VERSION = 1.0.2
    QMAKE_TARGET_COMPANY = Andrey Shirshov Co
    QMAKE_TARGET_PRODUCT = Medical directory
    QMAKE_TARGET_DESCRIPTION = Medical reference for Eidos
    QMAKE_TARGET_COPYRIGHT = Andrey Shirshov
    RC_ICONS = $$PWD/source/images/icons/doc.ico
}

# Выбираем директорию сборки исполняемого файла
# в зависимости от режима сборки проекта
CONFIG(debug, debug|release) {
    DESTDIR = $$OUT_PWD/../../SpravochnikDebug
} else {
    DESTDIR = $$OUT_PWD/../../SpravochnikRelease
}

# Разделяем по директориям все выходные файлы проекта
MOC_DIR = ../common/build/moc
RCC_DIR = ../common/build/rcc
UI_DIR = ../common/build/ui
unix:OBJECTS_DIR = ../common/build/o/unix
win32:OBJECTS_DIR = ../common/build/o/win32
macx:OBJECTS_DIR = ../common/build/o/mac

# В зависимости от режима сборки проекта
# запускаем win deploy приложения в целевой директории, то есть собираем все dll
# копируем settings.ini и README.txt
CONFIG(debug, debug|release) {
    QMAKE_POST_LINK = $$(QTDIR)/bin/windeployqt $$OUT_PWD/../../SpravochnikDebug
    copyFilesToDir($$PWD/settings.ini, $$OUT_PWD/../../SpravochnikDebug)
    copyFilesToDir($$PWD/README.txt, $$OUT_PWD/../../SpravochnikDebug)
} else {
    QMAKE_POST_LINK = $$(QTDIR)/bin/windeployqt $$OUT_PWD/../../SpravochnikRelease
    copyFilesToDir($$PWD/settings.ini, $$OUT_PWD/../../SpravochnikRelease)
    copyFilesToDir($$PWD/README.txt, $$OUT_PWD/../../SpravochnikRelease)
}

