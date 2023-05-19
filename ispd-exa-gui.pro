SOURCES += \
  src/gridscene.cpp \
  src/gridview.cpp \
  src/main.cpp \
  src/mainwindow.cpp \
  src/userwindow.cpp \
  src/workloads.cpp \
  src/settingswindow.cpp \
  src/machineicon.cpp \
  src/clustericon.cpp \
  src/icon.cpp

HEADERS += \
  src/mainwindow.h \
  src/userwindow.h \
  src/workloads.h \
  src/gridscene.h \
  src/gridview.h \
  src/settingswindow.h \
  src/machineicon.h \
  src/clustericon.h \
  src/icon.h

QT += widgets

CONFIG += c++17

RESOURCES += \
  ispd-exa-gui.qrc

FORMS += \
  forms/userwindow.ui \
  forms/workloads.ui \
  forms/mainwindow.ui \
  forms/settingswindow.ui

DISTFILES +=
