set(LIBRARY_OUTPUT_PATH ${OUT_PUT_LX_PATH}/uvframelesshelper)
set(TARGET_NAME UVFramelessHelper)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(QT NAMES Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

if(QX_FRAMELESS_CONFIG_BUILD_STATIC)
    add_compile_definitions(QX_FRAMELESS_LIBRARY_STATIC)
    set(QX_FRAMELESS_LIB_TYPE "STATIC")
else()
    add_compile_definitions(QX_FRAMELESS_LIBRARY)
    set(QX_FRAMELESS_LIB_TYPE "SHARED")
endif()

#if(QX_FRAMELESS_CONFIG_NATIVE OR WIN32)
#    add_compile_definitions(QX_FRAMELESS_NATIVE)
#endif()

set(QX_FRAMELESS_PUBLIC_HEADERS
    qxframeless_global.h
    framelesshelper.h
)

set(QX_FRAMELESS_PRIVATE_HEADERS
    framelesshelper_p.h
)

set(QX_FRAMELESS_SOURCES
    framelesshelper.cpp
)

add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

add_library(${TARGET_NAME} ${QX_FRAMELESS_LIB_TYPE}
    ${QX_FRAMELESS_PUBLIC_HEADERS}
    ${QX_FRAMELESS_PRIVATE_HEADERS}
    ${QX_FRAMELESS_SOURCES}
)

target_include_directories(${TARGET_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(${TARGET_NAME} PUBLIC
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::Widgets
)

install(TARGETS ${TARGET_NAME}
        RUNTIME DESTINATION bin/uvframelesshelper
)

install(TARGETS ${TARGET_NAME}
        ARCHIVE DESTINATION lib/uvframelesshelper OPTIONAL
)

install(FILES $<TARGET_PDB_FILE:${TARGET_NAME}> DESTINATION pdb/uvframelesshelper OPTIONAL)
