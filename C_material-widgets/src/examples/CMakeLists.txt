set(TARGET_NAME examples)

include_directories(..)

set(examples_SOURCES
        mainwidget.hpp
        mainwidget.cc
)

add_executable(${TARGET_NAME}
        WIN32
        main.cc
        ${examples_SOURCES}
)

target_link_libraries(${TARGET_NAME} Qt5::Core Qt5::Gui Qt5::Widgets)

install(TARGETS ${TARGET_NAME}
        RUNTIME DESTINATION bin
)

