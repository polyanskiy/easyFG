# -------------------------------------------------
# Project created by QtCreator 2009-10-21T12:47:05
# -------------------------------------------------
TARGET = easyfg
TEMPLATE = app
SOURCES += main.cpp \
    cursors.cpp \
    image.cpp \
mainwindow.cpp \
reference.cpp \
scale.cpp \
scene.cpp \
load.cpp \
    session.cpp \
update.cpp \
shortcuts.cpp \
memory.cpp \
analysis.cpp \
save.cpp \
clipboard.cpp
HEADERS += easyfg.h
FORMS += mainwindow.ui
RESOURCES += icon.qrc
OTHER_FILES += icon.rc
RC_FILE = icon.rc
CONFIG += qt
QT += widgets

win32 {
INCLUDEPATH += "C:\\Program Files\\HDF_Group\\HDF5\\1.12.0\\include"
LIBS += "C:\\Program Files\\HDF_Group\\HDF5\\1.12.0\\lib\\hdf5.lib"
LIBS += "C:\\Program Files\\HDF_Group\\HDF5\\1.12.0\\lib\\hdf5_hl.lib"
}
