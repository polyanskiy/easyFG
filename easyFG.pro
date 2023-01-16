# -------------------------------------------------
# Project created by QtCreator 2009-10-21T12:47:05
# -------------------------------------------------
TARGET = easyfg
TEMPLATE = app
SOURCES += main.cpp \
    gui0_mainwindow.cpp \
    gui1_image.cpp \
    gui2_scale.cpp \
    gui3_cursors.cpp \
    gui4_analysis.cpp \
    gui5_reference.cpp \
    gui6_scene.cpp \
load.cpp \
    session.cpp \
shortcuts.cpp \
memory.cpp \
save.cpp \
clipboard.cpp
HEADERS += easyfg.h
FORMS += \
    mainwindow.ui
RESOURCES += icon.qrc
OTHER_FILES += icon.rc
RC_FILE = icon.rc
CONFIG += qt
QT += widgets

win32 {
INCLUDEPATH += "C:\\Program Files\\HDF_Group\\HDF5\\1.14.0\\include"
LIBS += "C:\\Program Files\\HDF_Group\\HDF5\\1.14.0\\lib\\hdf5.lib"
LIBS += "C:\\Program Files\\HDF_Group\\HDF5\\1.14.0\\lib\\hdf5_hl.lib"
}
