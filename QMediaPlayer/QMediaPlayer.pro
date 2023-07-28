<<<<<<< HEAD
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets multimediawidgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    my_item.cpp \
    my_music.cpp \
    mynetwork.cpp \
    myplaintextedit.cpp \
    videowidget.cpp

HEADERS += \
    mainwindow.h \
    my_item.h \
    my_music.h \
    mynetwork.h \
    myplaintextedit.h \
    videowidget.h

FORMS += \
    mainwindow.ui

RESOURCES += \
    res.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
=======
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets multimediawidgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    my_item.cpp \
    my_music.cpp \
    mynetwork.cpp \
    myplaintextedit.cpp \
    videowidget.cpp

HEADERS += \
    mainwindow.h \
    my_item.h \
    my_music.h \
    mynetwork.h \
    myplaintextedit.h \
    videowidget.h

FORMS += \
    mainwindow.ui

RESOURCES += \
    res.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
>>>>>>> cdd08f869638039635144f291da04c841be7fc1c
