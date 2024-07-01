set(TARGET_NAME CLiveHand)

include_directories(.)
include_directories(${ffmpeg_headers_DIR})

set(header
        clivehand.h
        CPlayBackWidget.h
        CObserverProcess.h
)

set(source
        main.cc
        clivehand.cc
        CPlayBackWidget.cc
        CObserverProcess.cc
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

file(GLOB FFMPEG_DLLS ${ffmpeg_bin_DIR}/*.dll)

add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${FFMPEG_DLLS} ${CMAKE_SOURCE_DIR}/bin/resource/C_testffmpeg.rcc
        $<TARGET_FILE_DIR:${TARGET_NAME}>
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/bin/style $<TARGET_FILE_DIR:${TARGET_NAME}>/style
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/bin/translation $<TARGET_FILE_DIR:${TARGET_NAME}>/translation
        COMMENT "Copying FFmpeg DLLs, resource file, style and translation directories to output directory"
)
