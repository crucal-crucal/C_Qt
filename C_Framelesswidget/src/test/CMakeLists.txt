set(TARGET_NAME test)

include_directories(..)

set(test_SOURCES
        test.h
        test.cc
        framelesswidget_p.h
        framelessdialog_p.h
        framelessmainwindow_p.h
        framelesswidget_p.cc
        framelessdialog_p.cc
        framelessmainwindow_p.cc
)

add_executable(${TARGET_NAME}
        WIN32
        main.cpp
        ${test_SOURCES}
)

target_link_libraries(${TARGET_NAME} Qt5::Core Qt5::Gui Qt5::Widgets)
target_link_libraries(${TARGET_NAME}
        framelessdialog
        framelessmainwindow
        framelesswidget
        framelessMessageBox_1
        framelessMessageBox_2
)

install(TARGETS ${TARGET_NAME}
        RUNTIME DESTINATION bin
)

