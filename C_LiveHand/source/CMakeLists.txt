set(TARGET_NAME CLiveHand)

include_directories(.)
include_directories(${ffmpeg_headers_DIR})

set(header
        clivehand.h
        CPlayBackWidget.h
)

set(source
        main.cc
        clivehand.cc
        CPlayBackWidget.cc
)

link_directories(${ffmpeg_libs_DIR})

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
