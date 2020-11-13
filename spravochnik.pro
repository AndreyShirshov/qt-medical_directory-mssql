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

win32:{
    VERSION = 1.0.0.1
    QMAKE_TARGET_COMPANY = Andrey Shirshov Co
    QMAKE_TARGET_PRODUCT = Medical directory
    QMAKE_TARGET_DESCRIPTION = Medical reference for Eidos
    QMAKE_TARGET_COPYRIGHT = Andrey Shirshov
    RC_ICONS = $$PWD/source/images/icons/doc.ico
}

# Выбираем директорию сборки исполняемого файла
# в зависимости от режима сборки проекта
CONFIG(debug, debug|release) {
    DESTDIR = $$PWD/common/build/SpravochnikDebug
} else {
    DESTDIR = $$PWD/common/build/SpravochnikRelease
}

# Разделяем по директориям все выходные файлы проекта
MOC_DIR = $$PWD/common/build/moc
RCC_DIR = $$PWD/common/build/rcc
UI_DIR = $$PWD/common/build/ui
unix:OBJECTS_DIR = $$PWD/common/build/o/unix
win32:OBJECTS_DIR = $$PWD/common/build/o/win32
macx:OBJECTS_DIR = $$PWD/common/build/o/mac

# В зависимости от режима сборки проекта
# запускаем win deploy приложения в целевой директории, то есть собираем все dll
# копируем settings.ini
CONFIG(debug, debug|release) {
    QMAKE_POST_LINK = $$(QTDIR)/bin/windeployqt $$PWD/common/build/SpravochnikDebug
    copyFilesToDir($$PWD/settings.ini, $$PWD/common/build/SpravochnikDebug)
} else {
    QMAKE_POST_LINK = $$(QTDIR)/bin/windeployqt $$PWD/common/build/SpravochnikRelease
    copyFilesToDir($$PWD/settings.ini, $$PWD/common/build/SpravochnikRelease)
}
