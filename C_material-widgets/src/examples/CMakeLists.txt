set(TARGET_NAME examples)

setupQt()

include_directories(.)
include_directories(../components)

set(examples_SOURCES
        mainwidget.hpp
        mainwidget.cc
)

add_executable(${TARGET_NAME}
        main.cc
        ${examples_SOURCES}
)

target_link_libraries(${TARGET_NAME} Qt5::Core Qt5::Gui Qt5::Widgets)
target_link_libraries(${TARGET_NAME}
        uvappbarsettingseditor
        uvautocompletesettingseditor
        uvavatarsettingseditor
        uvbadgesettingseditor
)

install(TARGETS ${TARGET_NAME}
        RUNTIME DESTINATION bin
)

add_subdirectory(uvappbarsettingseditor)
add_subdirectory(uvautocompletesettingseditor)
add_subdirectory(uvavatarsettingseditor)
add_subdirectory(uvbadgesettingseditor)

