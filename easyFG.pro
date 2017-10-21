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
INCLUDEPATH += "C:\\Program Files (x86)\\GnuWin32\\include"
LIBS += "C:\\Program Files (x86)\\GnuWin32\\lib\\libtiff.lib"
INCLUDEPATH += "C:\\Program Files (x86)\\HDF_Group\\HDF5\\1.10.1\\include"
LIBS += "C:\\Program Files (x86)\\HDF_Group\\HDF5\\1.10.1\\lib\\hdf5.lib"
LIBS += "C:\\Program Files (x86)\\HDF_Group\\HDF5\\1.10.1\\lib\\hdf5_hl.lib"
}

!win32 {
QMAKE_LFLAGS += -ltiff
}
