cmake_minimum_required(VERSION 3.24)
project(GPTinterface)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        Network
        REQUIRED)

find_package(CURL REQUIRED)

include_directories(usr/include/curl)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/external/include)

add_executable(GPTinterface src/main.cpp src/gui/MainWindow.cpp src/gui/MainWindow.h src/gui/mainwindow.ui
        src/gui/Workspace.cpp src/gui/Workspace.h src/gui/widgets/RightToolBar.cpp
        src/gui/widgets/WSTabWidget.cpp src/gui/widgets/InputBox.cpp
        src/utils/RequestHandler.cpp src/utils/RequestHandler.h
        src/gui/widgets/customTextEdit.cpp src/gui/widgets/customScrollArea.cpp src/devtools/ToolTipEventFilter.cpp)

target_link_libraries(GPTinterface
        Qt::Core
        Qt::Gui
        Qt::Widgets
        Qt::Network
        /usr/lib/libcurl.so
        )
