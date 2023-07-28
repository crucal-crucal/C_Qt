<<<<<<< HEAD
QT       += core gui  multimedia network multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    QMyServer.cpp \
    QMyThread.cpp \
    QMyThreadPool.cpp \
    main.cpp \
    mainwindow.cpp \
    QMyDataDecompression.cpp \
    MyTcpServer.cpp

HEADERS += \
    QMyServer.h \
    QMyThread.h \
    QMyThreadPool.h \
    mainwindow.h \
    QMyDataDecompression.h \
    MyTcpServer.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

=======
QT       += core gui  multimedia network multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    QMyServer.cpp \
    QMyThread.cpp \
    QMyThreadPool.cpp \
    main.cpp \
    mainwindow.cpp \
    QMyDataDecompression.cpp \
    MyTcpServer.cpp

HEADERS += \
    QMyServer.h \
    QMyThread.h \
    QMyThreadPool.h \
    mainwindow.h \
    QMyDataDecompression.h \
    MyTcpServer.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    Server.pro.user
>>>>>>> cdd08f869638039635144f291da04c841be7fc1c
