cmake_minimum_required(VERSION 3.14)

project(demo_music VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (WIN32 OR UNIX)
    set(QT_DIR $ENV{QTDIR})
    message(STATUS "QT_DIR=$ENV{QT_DIR}")
    find_program(QMAKE_EXECUTABLENAMES qmake HINTS $ENV{QT_DIR} PATH_SUFFIXES bin)
    set(CMAKE_PREFIX_PATH ${QT_DIR})
endif ()

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

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Quick)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Quick)

include_directories(headers)

set(PROJECT_SOURCES
    Resources/qml.qrc
    Resources/images.qrc
    Src/HttpUtils.h
    Src/HttpUtils.cpp
    Src/App.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(demo_music
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET demo_music APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(demo_music SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(demo_music
          ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(demo_music
  PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.demo_music)
endif()
set_target_properties(demo_music PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS demo_music
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_import_qml_plugins(demo_music)
    qt_finalize_executable(demo_music)
endif()
