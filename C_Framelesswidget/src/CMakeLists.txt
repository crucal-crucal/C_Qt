set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_CXX_STANDARD 17)

# 从环境变量中获取 Qt 路径，查找 qmake
if (WIN32 OR UNIX)
    set(QT_DIR $ENV{QTDIR})
    message(STATUS "QT_DIR=$ENV{QT_DIR}")
    find_program(QMAKE_EXECUTABLENAMES qmake HINTS $ENV{QT_DIR} PATH_SUFFIXES bin)
endif ()

# 查询 Qt 版本 并存储再 QT_VERSION 中
execute_process(COMMAND ${QMAKE_EXECUTABLENAMES} -query QT_VERSION OUTPUT_VARIABLE QT_VERSION)
if (QT_VERSION)
    message(STATUS "Qt version: " ${QT_VERSION})
    string(REPLACE "." ";" QT_VERSION_LIST ${QT_VERSION})
    list(GET QT_VERSION_LIST 0 QT_VERSION_MAJOR)
    set(Qt "Qt${QT_VERSION_MAJOR}")
else ()
    message(FATAL_ERROR "Qt version not found. Please check if the QTDIR environment variable is set correctly.")
endif ()

include_directories(${QT_DIR}/include)

find_package(Qt5
        COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED
)

add_subdirectory(test)
add_subdirectory(framelessdialog)
add_subdirectory(framelessmainwindow)
add_subdirectory(framelesswidget)