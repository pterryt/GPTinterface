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
find_package(Python3 REQUIRED COMPONENTS Development)

include_directories(usr/include/curl)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/external/include)
include_directories(${Python3_INCLUDE_DIRS})

add_executable(GPTinterface
        src/main.cpp
        src/gui/MainWindow.cpp
        src/utils/GlobalMediator.cpp
        src/gui/Workspace.cpp
        src/gui/widgets/RightToolBar.cpp
        src/gui/widgets/WSTabWidget.cpp
        src/gui/widgets/InputBox.cpp
        src/utils/RequestHandler.cpp
        src/gui/widgets/customTextEdit.cpp
        src/gui/widgets/customScrollArea.cpp
        src/devtools/ToolTipEventFilter.cpp
        src/utils/TikTokenEncoder.cpp
        src/gui/widgets/BottomToolBar.cpp)

target_link_libraries(GPTinterface
        Qt::Core
        Qt::Gui
        Qt::Widgets
        Qt::Network
        /usr/lib/libcurl.so
        ${Python3_LIBRARIES}
        )
