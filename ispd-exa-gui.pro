SOURCES += \
  qcustomplot.cpp \
  src/ispd-exa-gui.cpp \
  src/item/linkicon.cpp \
  src/item/machineicon.cpp \
  src/window/adduser.cpp \
  src/window/machineconfiguration.cpp \
  src/window/main.cpp \
  src/window/simulation.cpp \
  src/window/users.cpp \
  src/window/workloads.cpp \
  src/window/settings.cpp \
  src/window/schemawindow.cpp \
  src/item/schemaicon.cpp \
  src/item/icon.cpp \
  src/item/link.cpp \ 
  src/drawingtable/drawingtable.cpp \
  src/drawingtable/scene.cpp \
  src/drawingtable/view.cpp \
  src/load/machineload.cpp \
  src/load/linkload.cpp \ 
  src/schema.cpp

INCLUDEPATH += include/
HEADERS += \
  include/item/linkicon.h \
  include/window/adduser.h \
  include/window/machineconfiguration.h \
  include/window/main.h \
  include/window/simulation.h \
  include/window/users.h \
  include/window/workloads.h \
  include/window/settings.h \
  include/window/schemawindow.h \
  include/drawingtable/drawingtable.h \
  include/drawingtable/scene.h \
  include/drawingtable/view.h \
  include/item/machineicon.h \
  include/item/schemaicon.h \
  include/item/icon.h \
  include/item/link.h \
  include/load/linkload.h \
  include/load/machineload.h \
  include/schema.h \
  packCircles.h \
  qcustomplot.h

QT += widgets svg printsupport

CONFIG += c++17

RESOURCES += \
  ispd-exa-gui.qrc

FORMS += \
  forms/adduser.ui \
  forms/machineconfiguration.ui \
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

OBJECTS_DIR = $$DESTDIR/.obj
MOC_DIR = $$DESTDIR/.moc
RCC_DIR = $$DESTDIR/.qrc
UI_DIR = $$DESTDIR/.u

DISTFILES += \
    packCircles \
    results.json

