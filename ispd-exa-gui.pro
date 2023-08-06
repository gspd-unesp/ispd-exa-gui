SOURCES += \
  qcustomplot.cpp \
  src/components/*.cpp \
  src/components/conf/*.cpp \
  src/window/*.cpp \
  src/window/drawingtable/*.cpp \
  src/icon/*.cpp \
  src/ispd-exa-gui.cpp \

INCLUDEPATH += include/
HEADERS += \
  packCircles.h \
  include/components/*.h \
  include/components/conf/*.h \
  include/window/*.h \
  include/window/drawingtable/*.h \
  include/icon/*.h \
  include/utils/*.h \
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

