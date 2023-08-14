<<<<<<< HEAD
<<<<<<< HEAD
QT       += core gui network
=======
QT       += core gui
>>>>>>> 47b8f66 (update)

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
<<<<<<< HEAD
    form.cpp \
    main.cpp \
    mainwindow.cpp \
    sendfile.cpp

HEADERS += \
    form.h \
    mainwindow.h \
    sendfile.h
=======
<<<<<<<< HEAD:Chinese_to_pingyin/Chinese_to_pingyin.pro
    ZH_TO_PY.cpp \
========
    form.cpp \
>>>>>>>> 47b8f66 (update):TCP-1/TcpClient_sendFile/TcpClient_sendFile.pro
    main.cpp \
    mainwindow.cpp

HEADERS += \
<<<<<<<< HEAD:Chinese_to_pingyin/Chinese_to_pingyin.pro
    ZH_TO_PY.h \
    mainwindow.h
========
    form.h \
    mainwindow.h \
    sendfile.h
>>>>>>>> 47b8f66 (update):TCP-1/TcpClient_sendFile/TcpClient_sendFile.pro
>>>>>>> 47b8f66 (update)

FORMS += \
    form.ui \
    mainwindow.ui

<<<<<<< HEAD
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
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
    sendfile.cpp

HEADERS += \
    form.h \
    mainwindow.h \
    sendfile.h

FORMS += \
    form.ui \
    mainwindow.ui
=======
RESOURCES += \
    main.qrc
>>>>>>> 47b8f66 (update)

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
<<<<<<< HEAD
>>>>>>> cdd08f869638039635144f291da04c841be7fc1c
=======
>>>>>>> 47b8f66 (update)
