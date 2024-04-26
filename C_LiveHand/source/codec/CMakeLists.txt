#set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/application)
set(TARGET_NAME Codec_p)

if (WIN32)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif ()

# 添加头文件路径到编译器的头文件搜索路径下，多个路径以空格分隔
include_directories(${ffmpeg_headers_DIR})
include_directories(..)
aux_source_directory(. SRC_LIST)

link_directories(${ffmpeg_libs_DIR})

add_library(${TARGET_NAME} SHARED ${SRC_LIST})

target_link_libraries(${TARGET_NAME} Qt5::Core Qt5::Gui Qt5::Widgets)
target_link_libraries(${TARGET_NAME}
        avcodec avdevice avfilter avformat avutil postproc swresample swscale
)


target_compile_definitions(${TARGET_NAME} PRIVATE CODEC_P_LIB)

install(TARGETS ${TARGET_NAME}
        RUNTIME DESTINATION bin
)

install(TARGETS ${TARGET_NAME}
        ARCHIVE DESTINATION lib OPTIONAL
)

if (WIN32)
    install(FILES $<TARGET_PDB_FILE:${TARGET_NAME}> DESTINATION pdb OPTIONAL)
endif ()
