set(TARGET_NAME application)

include_directories(.)

set(header
        test.h
        playbackwidget.h
)

set(source
        main.cc
        test.cc
        playbackwidget.cc
)

add_executable(${TARGET_NAME}
        ${header}
        ${source}
)

target_link_libraries(${TARGET_NAME} Qt5::Widgets Qt5::Core Qt5::Gui Qt5::Multimedia Qt5::MultimediaWidgets Qt5::Xml)
target_link_libraries(${TARGET_NAME} framelessmainwindow framelessMessageBox SplashScreen logger Codec_p)

add_subdirectory(framelessmainwindow)
add_subdirectory(framelessMessageBox)
add_subdirectory(splashscreen)
add_subdirectory(logger)
add_subdirectory(codec)

install(TARGETS ${TARGET_NAME}
        RUNTIME DESTINATION bin
)
