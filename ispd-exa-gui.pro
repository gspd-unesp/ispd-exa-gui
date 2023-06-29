SOURCES += \
  src/ispd-exa-gui.cpp \
  src/window/main.cpp \
  src/window/users.cpp \
  src/window/workloads.cpp \
  src/window/settings.cpp \
  src/window/cluster.cpp \
  src/item/machineicon.cpp \
  src/item/clustericon.cpp \
  src/item/icon.cpp \
  src/item/link.cpp \ 
  src/drawingtable/scene.cpp \
  src/drawingtable/view.cpp \
  src/load/machineload.cpp

INCLUDEPATH += include/
HEADERS += \
  include/window/main.h \
  include/window/users.h \
  include/window/workloads.h \
  include/window/settings.h \
  include/window/cluster.h \
  include/drawingtable/scene.h \
  include/drawingtable/view.h \
  include/item/machineicon.h \
  include/item/clustericon.h \
  include/item/icon.h \
  include/item/link.h \
  include/load/linkload.h \ 
  include/load/machineload.h

QT += widgets

CONFIG += c++17

RESOURCES += \
  ispd-exa-gui.qrc

FORMS += \
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

