SOURCES += \
  src/main.cpp \
  src/mainwindow.cpp \
  src/userwindow.cpp \
  src/workloads.cpp

HEADERS += \
  include/mainwindow.h \
  include/userwindow.h \
  include/workloads.h

QT += widgets

CONFIG += c++17
RESOURCES += \
  grid_test.qrc

FORMS += \
  forms/userwindow.ui \
  forms/workloads.ui \
  forms/mainwindow.ui
