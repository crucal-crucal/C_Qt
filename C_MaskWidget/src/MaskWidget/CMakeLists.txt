set(TARGET_NAME MaskWidget)

if (WIN32)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif ()

aux_source_directory(. SRC_LIST)

add_library(${TARGET_NAME} SHARED ${SRC_LIST})
target_link_libraries(${TARGET_NAME} Qt5::Core Qt5::Gui Qt5::Widgets)

target_compile_definitions(${TARGET_NAME} PRIVATE MASKWIDGET)

install(TARGETS ${TARGET_NAME}
        RUNTIME DESTINATION bin
)

install(TARGETS ${TARGET_NAME}
        ARCHIVE  DESTINATION lib OPTIONAL
)
if (WIN32)
install(FILES $<TARGET_PDB_FILE:${TARGET_NAME}> DESTINATION pdb OPTIONAL)
endif ()
