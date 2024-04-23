set(TARGET_NAME application)

include_directories(.)

FILE(GLOB source "./*.cc")
FIlE(GLOB header "./*.h")

add_executable(${TARGET_NAME} icon.rc
        ${header}
        ${source}
)

target_link_libraries(${TARGET_NAME} Qt5::Core Qt5::Gui Qt5::Widgets)
target_link_libraries(${TARGET_NAME}
        logger
        framelessmainwindow
        framelessMessageBox_1
        mergedir_p
)

add_subdirectory(framelessmainwindow)
add_subdirectory(framelessMessageBox)
add_subdirectory(logger)
add_subdirectory(mergedir)

install(TARGETS ${TARGET_NAME}
        RUNTIME DESTINATION bin
)
