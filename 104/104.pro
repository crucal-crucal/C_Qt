QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Client_Info_Form.cpp \
    Client_Telemetry_Info_Form.cpp \
    Client_Telesigna_Info_Form.cpp \
    Server_Info_Form.cpp \
    Server_Telemetry_Info_Form.cpp \
    Server_Telesigna_Info_Form.cpp \
    SaveXml.cpp \
    new_Form.cpp \
    Client_delete_Form.cpp \
    deleteXml.cpp \
    Server_delete_Form.cpp \
    addXml.cpp \
    Client_CheckForm.cpp \
    Server_CheckForm.cpp \
    Server_Form.cpp \
    Client_Form.cpp \
    Client_Telemetry_Form.cpp \
    Client_Telesigna_Form.cpp \
    Server_Telemetry_Form.cpp \
    Server_Telesigna_Form.cpp \
    main.cpp \
    mainwindow.cpp \
    modifyXml.cpp \
    readXml.cpp \

HEADERS += \
    Client_Info_Form.h \
    Client_Telemetry_Info_Form.h \
    Client_Telesigna_Info_Form.h \
    Server_Info_Form.h \
    Server_Telemetry_Info_Form.h \
    Server_Telesigna_Info_Form.h \
    SaveXml.h \
    Client_delete_Form.h \
    deleteXml.h \
    Server_delete_Form.h \
    addXml.h \
    Client_CheckForm.h \
    Server_CheckForm.h \
    Server_Form.h \
    Client_Telemetry_Form.h \
    Client_Telesigna_Form.h \
    Server_Telemetry_Form.h \
    Server_Telesigna_Form.h \
    mainwindow.h \
    modifyXml.h \
    readXml.h \
    Client_Form.h \
    new_Form.h

FORMS += \
    Client_Info_Form.ui \
    Client_Telemetry_Info_Form.ui \
    Client_Telesigna_Info_Form.ui \
    Server_Info_Form.ui \
    Server_Telemetry_Info_Form.ui \
    Server_Telesigna_Info_Form.ui \
    new_Form.ui \
    Client_delete_Form.ui \
    Server_delete_Form.ui \
    Client_CheckForm.ui \
    Server_CheckForm.ui \
    Server_Form.ui \
    Client_Form.ui \
    Client_Telemetry_Form.ui \
    Client_Telesigna_Form.ui \
    Server_Telemetry_Form.ui \
    Server_Telesigna_Form.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

#RESOURCES += \
#    res.qrc
