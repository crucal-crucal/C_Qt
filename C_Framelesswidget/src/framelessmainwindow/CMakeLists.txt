#set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/framelessmainwindow)
set(TARGET_NAME framelessmainwindow)

if (WIN32)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif ()

aux_source_directory(. SRC_LIST)

add_library(${TARGET_NAME} SHARED ${SRC_LIST})
target_link_libraries(${TARGET_NAME} Qt5::Core Qt5::Gui Qt5::Widgets)

target_compile_definitions(${TARGET_NAME} PRIVATE FRAMELESSMAINWINDOW_LIB)

#install(TARGETS ${TARGET_NAME}
#        RUNTIME DESTINATION bin/framelessmainwindow
#)
#
#install(TARGETS ${TARGET_NAME}
#        ARCHIVE  DESTINATION lib/framelessmainwindow OPTIONAL
#)
#
#install(FILES $<TARGET_PDB_FILE:${TARGET_NAME}> DESTINATION pdb/framelessmainwindow OPTIONAL)