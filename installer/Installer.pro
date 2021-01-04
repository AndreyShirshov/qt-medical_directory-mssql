# Before run make project, need to put executable file and dlls into
# $$PWD/Installer/packages/ru.fpn.spravochnik/data

TEMPLATE = aux

# В зависимости от режима сборки, определяем, куда именно будут собираться инсталляторы
CONFIG(debug, debug|release) {
    INSTALLER_OFFLINE = $$OUT_PWD/../../SpravochnikInstallerDebug/Spravochnik.offline
    INSTALLER_ONLINE = $$OUT_PWD/../../SpravochnikInstallerDebug/Spravochnik.online
    DESTDIR_WIN = $$PWD/packages/ru.fpn.spravochnik/data
    DESTDIR_WIN ~= s,/,\\,g
    PWD_WIN = $$OUT_PWD/../../SpravochnikDebug
    PWD_WIN ~= s,/,\\,g

    copydata.commands = $(COPY_DIR) $$PWD_WIN $$DESTDIR_WIN
    first.depends = $(first) copydata
    export(first.depends)
    export(copydata.commands)
    QMAKE_EXTRA_TARGETS += first copydata
} else {
    # Задаём переменные, которые будут содержать пути с названиями инсталляторов
    INSTALLER_OFFLINE = $$OUT_PWD/../../SpravochnikInstallerRelease/Spravochnik.offline
    INSTALLER_ONLINE = $$OUT_PWD/../../SpravochnikInstallerRelease/Spravochnik.online

    # Задаём переменную, которая должна содержать путь к папке с данными
    DESTDIR_WIN = $$PWD/packages/ru.fpn.spravochnik/data
    DESTDIR_WIN ~= s,/,\\,g
    # Задаём путь откуда всё приложение с DLL-ками нужно будет скопировать
    PWD_WIN = $$OUT_PWD/../../SpravochnikRelease
    PWD_WIN ~= s,/,\\,g

    # Прежде, чем выполнять сборку инсталляторов, необходимо скопировать файлы
    # из выходной папки проекта вместе со всеми DLL в папку data, которая относится
    # к собираемому пакету
    copydata.commands = $(COPY_DIR) $$PWD_WIN $$DESTDIR_WIN
    first.depends = $(first) copydata
    export(first.depends)
    export(copydata.commands)
    # задаём кастомную цель сборки, при которой сначала выполним копирование файлов
    # а потом уже и остальное, что следует по скрипту QMake
    QMAKE_EXTRA_TARGETS += first copydata
}

# Создаём цель по сборке Оффлайн Инсталлятора
INPUT = $$PWD/config/config.xml $$PWD/packages
offlineInstaller.depends = copydata
offlineInstaller.input = INPUT
offlineInstaller.output = $$INSTALLER_OFFLINE
offlineInstaller.commands = $$(QTDIR)/../../Tools/QtInstallerFramework/3.2/bin/binarycreator --offline-only -c $$PWD/config/config.xml -p $$PWD/packages ${QMAKE_FILE_OUT}
offlineInstaller.CONFIG += target_predeps no_link combine

QMAKE_EXTRA_COMPILERS += offlineInstaller

# Создаём цель по сборке Онлайн Инсталлятора
INPUT = $$PWD/config/config.xml $$PWD/packages
onlineInstaller.depends = copydata
onlineInstaller.input = INPUT
onlineInstaller.output = $$INSTALLER_ONLINE
onlineInstaller.commands = $$(QTDIR)/../../Tools/QtInstallerFramework/3.2/bin/binarycreator --online-only -c $$PWD/config/config.xml -p $$PWD/packages ${QMAKE_FILE_OUT}
onlineInstaller.CONFIG += target_predeps no_link combine

QMAKE_EXTRA_COMPILERS += onlineInstaller

# Сборка репозитория
# репозиторий будем собирать только в случае режима release
CONFIG(release, debug|release) {
INPUT = $$PWD/packages
repogenInstaller.depends = copydata
repogenInstaller.input = INPUT
repogenInstaller.output = $$OUT_PWD/../../repository
repogenInstaller.commands = $$(QTDIR)/../../Tools/QtInstallerFramework/3.2/bin/repogen -p $$PWD/packages -i ru.fpn.spravochnik --update ${QMAKE_FILE_OUT}
repogenInstaller.CONFIG += target_predeps no_link combine

QMAKE_EXTRA_COMPILERS += repogenInstaller
}

CONFIG += qtifw_auto_ts

DISTFILES += \
    packages/ru.fpn.spravochnik/meta/cc0.txt \
    packages/ru.fpn.spravochnik/meta/gpl3.txt \
    packages/ru.fpn.spravochnik/meta/installscript.qs \
    packages/ru.fpn.spravochnik/meta/package.xml \
    config/config.xml

FORMS += \
    packages/ru.fpn.spravochnik/meta/finishedcheckboxform.ui


