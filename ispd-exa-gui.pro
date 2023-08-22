SOURCES += \
    forms/scatterplot.cpp \
    src/components/link.cpp \
    src/components/machine.cpp \
    src/components/schema.cpp \
    src/components/conf/linkconf.cpp \
    src/components/conf/machineconf.cpp \
    src/components/switch.cpp \
    src/window/adduser.cpp \
    src/window/machineconfiguration.cpp \
    src/window/main.cpp \
    src/window/schemawindow.cpp \
    src/window/settings.cpp \
    src/window/simulation.cpp \
    src/window/users.cpp \
    src/window/workloads.cpp \
    src/window/drawingtable/drawingtable.cpp \
    src/window/drawingtable/scene.cpp \
    src/window/drawingtable/view.cpp \
    src/icon/icon.cpp \
    src/icon/linkicon.cpp \
    src/icon/machineicon.cpp \
    src/icon/schemaicon.cpp \
    src/icon/switchicon.cpp \
    src/ispd-exa-gui.cpp \
    qcustomplot.cpp

INCLUDEPATH += include/
HEADERS += \
    forms/scatterplot.h \
    packCircles.h \
    include/components/link.h \
    include/components/machine.h \
    include/components/schema.h \
    include/components/item.h \
    include/components/connection.h \
    include/components/conf/linkconf.h \
    include/components/conf/machineconf.h \
    include/components/switch.h \
    include/window/adduser.h \
    include/window/machineconfiguration.h \
    include/window/main.h \
    include/window/schemawindow.h \
    include/window/settings.h \
    include/window/simulation.h \
    include/window/users.h \
    include/window/workloads.h \
    include/window/drawingtable/drawingtable.h \
    include/window/drawingtable/scene.h \
    include/window/drawingtable/view.h \
    include/icon/icon.h \
    include/icon/linkicon.h \
    include/icon/machineicon.h \
    include/icon/schemaicon.h \
    include/icon/switchicon.h \
    include/utils/iconSize.h \
    qcustomplot.h

QT += widgets svg printsupport

CONFIG += c++17

RESOURCES += \
    ispd-exa-gui.qrc

FORMS += \
    forms/adduser.ui \
    forms/machineconfiguration.ui \
    forms/scatterplot.ui \
    forms/simulation.ui \
    forms/userwindow.ui \
    forms/workloads.ui \
    forms/mainwindow.ui \
    forms/settingswindow.ui

CONFIG(debug, debug|release) {
    DESTDIR = build/debug
}
CONFIG(release, debug|release) {
    DESTDIR = build/release
}

# Define os diretórios para arquivos intermediários
OBJECTS_DIR = $$DESTDIR/.obj
MOC_DIR = $$DESTDIR/.moc
RCC_DIR = $$DESTDIR/.qrc
UI_DIR = $$DESTDIR/.u

# Adicione outros arquivos gerados automaticamente (caso necessário) à lista de DISTFILES
DISTFILES += \
    packCircles \
    results.json