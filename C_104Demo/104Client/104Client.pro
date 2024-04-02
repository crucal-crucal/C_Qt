QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/config.cpp \
    src/Client_Info_Form.cpp \
    src/Client_Telemetry_Info_Form.cpp \
    src/Client_Telesigna_Info_Form.cpp \
    src/Server_Info_Form.cpp \
    src/Server_Telemetry_Info_Form.cpp \
    src/Server_Telesigna_Info_Form.cpp \
    src/SaveXml.cpp \
    src/new_Form.cpp \
    src/Client_delete_Form.cpp \
    src/deleteXml.cpp \
    src/Server_delete_Form.cpp \
    src/addXml.cpp \
    src/Client_CheckForm.cpp \
    src/Server_CheckForm.cpp \
    src/Server_Form.cpp \
    src/Client_Form.cpp \
    src/Client_Telemetry_Form.cpp \
    src/Client_Telesigna_Form.cpp \
    src/Server_Telemetry_Form.cpp \
    src/Server_Telesigna_Form.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/modifyXml.cpp \
    src/readXml.cpp \

HEADERS += \
    include/config.h \
    include/Client_Info_Form.h \
    include/Client_Telemetry_Info_Form.h \
    include/Client_Telesigna_Info_Form.h \
    include/Server_Info_Form.h \
    include/Server_Telemetry_Info_Form.h \
    include/Server_Telesigna_Info_Form.h \
    include/SaveXml.h \
    include/Client_delete_Form.h \
    include/deleteXml.h \
    include/Server_delete_Form.h \
    include/addXml.h \
    include/Client_CheckForm.h \
    include/Server_CheckForm.h \
    include/Server_Form.h \
    include/Client_Telemetry_Form.h \
    include/Client_Telesigna_Form.h \
    include/Server_Telemetry_Form.h \
    include/Server_Telesigna_Form.h \
    include/mainwindow.h \
    include/modifyXml.h \
    include/readXml.h \
    include/Client_Form.h \
    include/new_Form.h

FORMS += \
    ui/Client_Info_Form.ui \
    ui/Client_Telemetry_Info_Form.ui \
    ui/Client_Telesigna_Info_Form.ui \
    ui/Server_Info_Form.ui \
    ui/Server_Telemetry_Info_Form.ui \
    ui/Server_Telesigna_Info_Form.ui \
    ui/new_Form.ui \
    ui/Client_delete_Form.ui \
    ui/Server_delete_Form.ui \
    ui/Client_CheckForm.ui \
    ui/Server_CheckForm.ui \
    ui/Server_Form.ui \
    ui/Client_Form.ui \
    ui/Client_Telemetry_Form.ui \
    ui/Client_Telesigna_Form.ui \
    ui/Server_Telemetry_Form.ui \
    ui/Server_Telesigna_Form.ui \
    ui/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
