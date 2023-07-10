QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    my_openinterface.cpp

HEADERS += \
    mainwindow.h \
    my_openinterface.h

FORMS += \
    mainwindow.ui \
    my_openinterface.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images.qrc

DISTFILES += \
    images/103.bmp \
    images/120.bmp \
    images/20.ico \
    images/430.bmp \
    images/BLD.BMP \
    images/DBLUNDR.BMP \
    images/ITL.BMP \
    images/Save_as.jpg \
    images/UNDRLN.BMP \
    images/WORDUNDR.BMP \
    images/cut.bmp \
    images/exit.bmp \
    images/new2.bmp \
    images/open3.bmp \
    images/paste.bmp
