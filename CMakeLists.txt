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
        Multimedia
        REQUIRED)

find_package(AWSSDK REQUIRED COMPONENTS core polly)
find_package(CURL REQUIRED)
find_package(Python3 REQUIRED COMPONENTS Development)

find_path(SNDFILE_INCLUDE_DIR sndfile.h)
find_library(SNDFILE_LIBRARY sndfile)

if(NOT TARGET spdlog)
    find_package(spdlog)
endif()

include_directories(usr/include/curl)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/external/include)
include_directories(${Python3_INCLUDE_DIRS})
include_directories(${AWSSDK_INCLUDE_DIR})

add_executable(GPTinterface
        src/main.cpp
        src/gui/MainWindow.cpp
        src/utils/GlobalMediator.cpp
        src/gui/Workspace.cpp
        src/gui/widgets/RightToolBar.cpp
        src/gui/widgets/WSTabWidget.cpp
        src/gui/widgets/InputBox.cpp
        src/utils/RequestHandler.cpp
        src/gui/widgets/textboxes/customTextEdit.cpp
        src/gui/widgets/customScrollArea.cpp
        src/devtools/ToolTipEventFilter.cpp
        src/utils/TikTokenEncoder.cpp
        src/gui/widgets/BottomToolBar.cpp
        src/gui/widgets/textboxes/codeBlock.cpp
        QSourceHighlite/languagedata.cpp
        QSourceHighlite/qsourcehighliter.cpp
        QSourceHighlite/qsourcehighliterthemes.cpp
        src/gui/widgets/textboxes/aiText.cpp
        src/gui/widgets/textboxes/userText.cpp
        src/gui/widgets/LeftToolBar.cpp
        src/devtools/logger.cpp
        src/utils/MediaQueue.cpp
        src/utils/PollyUtility.cpp
        src/gui/widgets/HistoryList.cpp
        src/gui/widgets/history/HistoryButtonMenu.cpp
        src/gui/widgets/static_context/scBottomBar.cpp
        src/gui/widgets/static_context/scScrollArea.cpp
        src/gui/widgets/static_context/scItem.cpp
        )


set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "gpt")
target_link_libraries(GPTinterface
        Qt::Core
        Qt::Gui
        Qt::Widgets
        Qt::Network
        Qt::Multimedia
        /usr/lib/libcurl.so
        spdlog::spdlog_header_only
        ${SNDFILE_LIBRARY}
        ${Python3_LIBRARIES}
        ${AWSSDK_LINK_LIBRARIES}
        )

# Create output directory in build directory
add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/audio_clips)
add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/saved_chats)
