QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

qtHaveModule(printsupport): QT += printsupport

LIBS  += -L$${PWD}
CONFIG   -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Src/source/Client_Infomation.cpp \
    CustomLineEdit.cpp \
    MyTextEdit.cpp \
    Src/source/saveXml.cpp \
    Src/source/config.cpp \
    Src/source/Client_Info_Form.cpp \
    Src/source/Client_Telemetry_Info_Form.cpp \
    Src/source/Client_Telesigna_Info_Form.cpp \
    Src/source/Server_Info_Form.cpp \
    Src/source/Server_Telemetry_Info_Form.cpp \
    Src/source/Server_Telesigna_Info_Form.cpp \
    Src/source/main.cpp \
    Src/source/mainwindow.cpp \

HEADERS += \
    Src/include/Client_Infomation.h \
    CustomLineEdit.h \
    MyTextEdit.h \
    Src/include/saveXml.h \
    Src/include/config.h \
    Src/include/Client_Info_Form.h \
    Src/include/Client_Telemetry_Info_Form.h \
    Src/include/Client_Telesigna_Info_Form.h \
    Src/include/Server_Info_Form.h \
    Src/include/Server_Telemetry_Info_Form.h \
    Src/include/Server_Telesigna_Info_Form.h \
    Src/include/mainwindow.h \

FORMS += \
    Src/form/Client_Info_Form.ui \
    Src/form/Client_Telemetry_Info_Form.ui \
    Src/form/Client_Telesigna_Info_Form.ui \
    Src/form/Server_Info_Form.ui \
    Src/form/Server_Telemetry_Info_Form.ui \
    Src/form/Server_Telesigna_Info_Form.ui \
    Src/form/mainwindow.ui \
    Src/form/Client_Infomation.ui \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
