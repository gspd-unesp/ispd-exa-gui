cmake_minimum_required(VERSION 3.16)

project(ispd-exa-gui VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Svg PrintSupport)
qt_standard_project_setup()

set(CMAKE_AUTOUIC_SEARCH_PATHS forms)

add_executable(ispd-exa-gui src/ispd-exa-gui.cpp
  forms/userwindow.ui
  include/window/packcircles.h
  src/window/qcustomplot.cpp include/window/qcustomplot.h
  src/window/scatterplot.cpp include/window/scatterplot.h forms/scatterplot.ui
  src/window/settings.cpp include/window/settings.h forms/settingswindow.ui
  src/window/adduser.cpp include/window/adduser.h forms/adduser.ui
  src/window/drawingtable/view.cpp include/window/drawingtable/view.h 
  src/window/drawingtable/scene.cpp include/window/drawingtable/scene.h 
  src/window/drawingtable/drawingtable.cpp include/window/drawingtable/drawingtable.h 
  src/window/machineconfigurationwindow.cpp include/window/machineconfigurationwindow.h forms/machineconfigurationwindow.ui
  src/window/main.cpp include/window/main.h forms/mainwindow.ui
  src/window/schemawindow.cpp include/window/schemawindow.h 
  src/window/simulation.cpp include/window/simulation.h forms/simulation.ui
  src/window/workloads.cpp include/window/workloads.h forms/workloads.ui
  src/window/users.cpp include/window/users.h 

  include/components/conf/itemconfiguration.h 
  src/components/conf/machineconfiguration.cpp include/components/conf/machineconfiguration.h 
  src/components/conf/linkconfiguration.cpp include/components/conf/linkconfiguration.h 
  src/components/conf/schemaconfiguration.cpp include/components/conf/schemaconfiguration.h 
  src/components/conf/switchconfiguration.cpp include/components/conf/switchconfiguration.h 
  src/components/conf/connectablesetconfiguration.cpp

  include/components/cloner/cloner.h 
  src/components/cloner/linkcloner.cpp include/components/cloner/linkcloner.h 
  src/components/cloner/machinecloner.cpp include/components/cloner/machinecloner.h 
  src/components/cloner/switchcloner.cpp include/components/cloner/switchcloner.h 
  src/components/cloner/schemacloner.cpp include/components/cloner/schemacloner.h 

  src/components/link.cpp include/components/link.h 

  include/components/component.h 
  include/components/connectable.h 
  include/icon/icon.h 
  src/components/switch.cpp include/components/switch.h 
  src/components/switchbuilder.cpp include/components/switchbuilder.h 
  src/components/machine.cpp include/components/machine.h 
  src/components/machinebuilder.cpp include/components/machinebuilder.h 
  src/components/schema.cpp include/components/schema.h 
  src/components/connectableset.cpp include/components/connectableset.h

  src/icon/machineiconfactory.cpp include/icon/machineiconfactory.h 
  src/icon/pixmapiconbuilder.cpp include/icon/pixmapiconbuilder.h 
  src/icon/pixmapicon.cpp include/icon/pixmapicon.h 
  src/icon/linkicon.cpp include/icon/linkicon.h 


  include/utils/iconSize.h 
  include/utils/iconPath.h 

  include/icon/pixmapbuilder.h 
  include/icon/pixmappair.h 
)

qt_add_resources(helloworld imageresources
    PREFIX "/icons"
    FILES add_icon.png cluster.png clusterSelected.png
        connection.png
        cursor.png
        engine.png
        ethernet.png
        folder-new.svg
        head.png
        icons8-tower-pc-32.png
        machine.bmp
        machine.png
        pc.png
        pcSelected.png
        perfil.png
        save.png
        switchSelected.png
        switch.svg
        torre.png
        x_button.png
)

target_link_libraries(ispd-exa-gui PRIVATE Qt6::Widgets Qt6::PrintSupport)
target_link_libraries(ispd-exa-gui PRIVATE Qt6::Svg)
target_include_directories(ispd-exa-gui PUBLIC include)
target_include_directories(ispd-exa-gui PUBLIC forms)


set_target_properties(ispd-exa-gui PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)
