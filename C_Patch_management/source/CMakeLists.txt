set(TARGET_NAME test)

include_directories(..)

FILE(GLOB source "./*.cc")
FIlE(GLOB header "./*.h")

add_executable(${TARGET_NAME}
        ${header}
        ${source}
)

target_link_libraries(${TARGET_NAME} Qt5::Core Qt5::Gui Qt5::Widgets)
target_link_libraries(${TARGET_NAME}
        logger
        framelessmainwindow
        framelessMessageBox_1
)

add_subdirectory(framelessmainwindow)
add_subdirectory(framelessMessageBox-1)
add_subdirectory(logger)

install(TARGETS ${TARGET_NAME}
        RUNTIME DESTINATION bin
)