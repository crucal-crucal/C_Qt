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
