# -------------------------------------------------
# Project created by QtCreator 2009-10-21T12:47:05
# -------------------------------------------------
TARGET = easyfg
TEMPLATE = app
SOURCES += main.cpp \
    mainwindow.cpp \
    buttons.cpp \
    reference.cpp \
    scale.cpp \
    colormap.cpp \
    scene.cpp \
    load.cpp \
    update.cpp \
    shortcuts.cpp \
    memory.cpp \
    settings.cpp \
    analysis.cpp \
    save.cpp
HEADERS += easyfg.h
FORMS += mainwindow.ui
RESOURCES += icon.qrc
OTHER_FILES += icon.rc
RC_FILE = icon.rc
CONFIG += qt
QT += widgets

win32 {
    INCLUDEPATH += "C:\\Program Files (x86)\\GnuWin32\\include"
    LIBS += "C:\\Program Files (x86)\\GnuWin32\\lib\\libtiff.lib"
}

!win32 {
    QMAKE_LFLAGS += -ltiff
}
