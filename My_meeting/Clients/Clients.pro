QT       += core gui multimedia network multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    QMyCamera.cpp \
    QMyCameraThread.cpp \
    QMyClients.cpp \
    QMyDataDecompression.cpp \
    QMyShareDesktop.cpp \
    QMyThreadPool.cpp \
    main.cpp \
    mainwindow.cpp \
    QMyAudio.cpp \
    QMyIODevice.cpp

HEADERS += \
    QMyCamera.h \
    QMyCameraThread.h \
    QMyClients.h \
    QMyDataDecompression.h \
    QMyShareDesktop.h \
    QMyThreadPool.h \
    mainwindow.h \
    QMyAudio.h  \
    QMyIODevice.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
