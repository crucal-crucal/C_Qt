<<<<<<< HEAD
cmake_minimum_required(VERSION 3.5)

project(sieve_pool VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        mywork.cpp
        mywork.h
        res.qrc
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(sieve_pool
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET sieve_pool APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(sieve_pool SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(sieve_pool
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(sieve_pool PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(sieve_pool PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS sieve_pool
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(sieve_pool)
endif()
=======
# CMake指定最小版本
cmake_minimum_required(VERSION 3.5)
# 工程名字（随便设置，不影响
project(sieve_pool)
# 用于自动生成MOC(meta-object complier)文件
# 它们是Qt框架中用于实现信号和槽机制的元对象代码。
# 当使用Qt元对象系统时，CMake需要生成MOC文件以支持信号和槽机制。
# 这将自动启用MOC文件的生成。
set(CMAKE_AUTOMOC on)
# 用于自动编译Qt资源文件（.qrc文件）
# 这些文件包含了应用程序中使用的图片、字体、样式表等资源。
# 这将自动启用Qt资源文件的编译
set(CMAKE_AUTORCC on)
# 用于自动生成UI（user interface）文件，
# 这些文件描述了Qt Designer中设计的用户界面。
# 当使用Qt Designer设计用户界面时，CMake需要生成UI文件以支持用户界面代码的自动生成。
# 这将自动启用UI文件的生成。
set(CMAKE_AUTOUIC on)
# 支持的C++版本
set(CMAKE_CXX_STANDARD 17)
# CMake强制要求编译器使用C++标准的版本
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)
# 设置库文件的输出路径在LIBRARY_OUTPUT_PATH变量中
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
# 设置Qt6开发工具包的安装路径
set(Qt6_SDK_PATH "/home/crucal/Qt")

# 查找Qt里的cmake.conf配置文件
set(Qt6_DIR /home/crucal/Qt/6.3.2/gcc_64/lib/cmake/Qt6)
# 指定外部库路径
set(CMAKE_PREFIX_PATH /home/crucal/Qt/6.3.2/gcc_64/)
# 查找Qt6 模块(COMPONENTS) -Core Widgets  -REQUIRED(没有找到就终止)
find_package(Qt6 COMPONENTS Gui Core  Sql Multimedia Widgets
                            Network REQUIRED)

# 指定资源文件
aux_source_directory(./ SOURCES)
# 加入指定的资源文件qrc
qt_add_resources(SOURCES res.qrc)

# 生成可执行文件
add_executable(sieve_pool ${SOURCES})

# 连接Qt里的模块
target_link_libraries(sieve_pool Qt6::Core Qt6::Widgets Qt6::Multimedia Qt6::Sql
                            Qt6::Network Qt6::Gui)
>>>>>>> cdd08f869638039635144f291da04c841be7fc1c
