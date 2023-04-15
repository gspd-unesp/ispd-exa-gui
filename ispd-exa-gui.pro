SOURCES += \
  src/griditem.cpp \
  src/gridscene.cpp \
  src/gridview.cpp \
  src/main.cpp \
  src/mainwindow.cpp \
  src/userwindow.cpp \
  src/workloads.cpp

HEADERS += \
  src/griditem.h \
  src/mainwindow.h \
  src/userwindow.h \
  src/workloads.h \
  src/gridscene.h \
  src/gridview.h

QT += widgets

CONFIG += c++17

RESOURCES += \
  ispd-exa-gui.qrc

FORMS += \
  forms/userwindow.ui \
  forms/workloads.ui \
  forms/mainwindow.ui
