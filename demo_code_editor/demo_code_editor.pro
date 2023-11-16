QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

qtHaveModule(printsupport): QT += printsupport

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Src/source/MyCodeEditor.cpp \
    Src/source/MyTextEditByCode.cpp \
    Src/source/MyHighlighter.cpp \
    Src/source/MyTextEdit.cpp \
    Src/source/main.cpp \
    Src/source/mainwindow.cpp

HEADERS += \
    Src/include/MyCodeEditor.h \
    Src/include/MyTextEditByCode.h \
    Src/include/MyHighlighter.h \
    Src/include/MyTextEdit.h \
    Src/include/mainwindow.h

FORMS += \
    Src/form/MyTextEdit.ui \
    Src/form/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    code.qrc \
    images.qrc
