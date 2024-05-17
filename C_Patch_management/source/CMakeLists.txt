set(TARGET_NAME application)

include_directories(.)

FILE(GLOB source "./*.cc")
FIlE(GLOB header "./*.h")

add_executable(${TARGET_NAME} icon.rc
        ${header}
        ${source}
        global/cglobal.h
)

target_link_libraries(${TARGET_NAME} Qt5::Core Qt5::Gui Qt5::Widgets)
target_link_libraries(${TARGET_NAME}
        logger
        framelessmainwindow
        framelessMessageBox
        mergedir_p
        SplashScreen
        logger_redirection
        logger_p
)

add_subdirectory(framelessmainwindow)
add_subdirectory(framelessMessageBox)
add_subdirectory(logger)
add_subdirectory(mergedir)
add_subdirectory(splashscreen)
add_subdirectory(logger_redirection)
add_subdirectory(logger_p)

install(TARGETS ${TARGET_NAME}
        RUNTIME DESTINATION bin
)
