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
        REQUIRED)

add_executable(GPTinterface main.cpp gui/mainwindow.cpp gui/mainwindow.h gui/mainwindow.ui gui/workspace.cpp gui/workspace.h gui/widgets/promptInput.cpp gui/widgets/promptInput.h)
target_link_libraries(GPTinterface
        Qt::Core
        Qt::Gui
        Qt::Widgets
        )

