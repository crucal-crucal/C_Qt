cmake_minimum_required(VERSION 3.27)
project(CustomSignalDemo)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if (WIN32)
    set(QT_DIR $ENV{QTDIR})
    message(STATUS QT_DIR=$ENV{QTDIR})
    find_program(QMAKE_EXECUTABLE NAMES qmake HINTS $ENV{QTDIR} PATH_SUFFIXES bin)
endif ()

execute_process(COMMAND ${QMAKE_EXECUTABLE} -query QT_VERSION OUTPUT_VARIABLE QT_VERSION)
if (QT_VERSION)
    message(STATUS "Qt version: ${QT_VERSION}")
    string(REPLACE "." ";" VERSION_LIST ${QT_VERSION})
    list(GET VERSION_LIST 0 QT_MAJOR_VERSION)
    set(Qt "Qt${QT_MAJOR_VERSION}")
else ()
    message(FATAL_ERROR "Qt version not found")
endif ()

include_directories(${QT_DIR}/include)

if (WIN32)
    list(PREPEND CMAKE_PREFIX_PATH $ENV{QT_DIR})
endif ()

find_package(${Qt} COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED
)

add_executable(CustomSignalDemo main.cpp
        defstruct.h
        SignalTest.h
        SignalTest.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE ${Qt}::Core ${Qt}::Gui ${Qt}::Widgets)
