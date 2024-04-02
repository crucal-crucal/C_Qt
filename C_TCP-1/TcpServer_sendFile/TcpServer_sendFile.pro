<<<<<<< HEAD
<<<<<<< HEAD
QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
=======
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport
>>>>>>> 47b8f66 (update)

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
<<<<<<< HEAD
    form.cpp \
    main.cpp \
    mainwindow.cpp \
    mytcpserver.cpp \
    recvfile.cpp

HEADERS += \
    form.h \
    mainwindow.h \
    mytcpserver.h \
    recvfile.h
=======
<<<<<<<< HEAD:axis-tags/axis-tags.pro
    AxisTag.cpp \
========
    form.cpp \
>>>>>>>> 47b8f66 (update):TCP-1/TcpServer_sendFile/TcpServer_sendFile.pro
    main.cpp \
    mainwindow.cpp \
    qcustomplot.cpp

HEADERS += \
<<<<<<<< HEAD:axis-tags/axis-tags.pro
    AxisTag.h \
========
    form.h \
>>>>>>>> 47b8f66 (update):TCP-1/TcpServer_sendFile/TcpServer_sendFile.pro
    mainwindow.h \
    qcustomplot.h
>>>>>>> 47b8f66 (update)

FORMS += \
    form.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
<<<<<<< HEAD
=======
QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    form.cpp \
    main.cpp \
    mainwindow.cpp \
    mytcpserver.cpp \
    recvfile.cpp

HEADERS += \
    form.h \
    mainwindow.h \
    mytcpserver.h \
    recvfile.h

FORMS += \
    form.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
>>>>>>> cdd08f869638039635144f291da04c841be7fc1c
=======
>>>>>>> 47b8f66 (update)
