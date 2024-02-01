cmake_minimum_required(VERSION 3.27)
project(GraphicsItme)

set(CMAKE_CXX_STANDARD 17)
# 使用指定 C++ 标准
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# 从环境变量中获取 Qt 路径，查找 qmake
if(WIN32)
    set(QT_DIR $ENV{QTDIR})
    message(STATUS QT_DIR=$ENV{QTDIR})
    find_program(QMAKE_EXECUTABLE NAMES qmake HINTS $ENV{QTDIR} PATH_SUFFIXES bin)
endif()
# 查询 Qt 版本 并存储在 QT_VERSION 中
execute_process(COMMAND ${QMAKE_EXECUTABLE} -query QT_VERSION OUTPUT_VARIABLE QT_VERSION)
if (QT_VERSION)
    message(STATUS "Qt version is ${QT_VERSION}")
    string(REPLACE "." ";" QT_VERSION_LIST ${QT_VERSION})
    list(GET QT_VERSION_LIST 0 QT_VERSION_MAJOR)
    set(Qt "Qt${QT_VERSION_MAJOR}")
else()
    message(FATAL_ERROR "Con not find valid qt version!")
endif()

include_directories(${QT_DIR}/include)

find_package(${Qt}
        COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED
)

add_executable(GraphicsItme main.cpp
        MyPointGraphicsItem.h
        MyPointGraphicsItem.cpp)

target_link_libraries(${PROJECT_NAME} ${Qt}::Core ${Qt}::Gui ${Qt}::Widgets)