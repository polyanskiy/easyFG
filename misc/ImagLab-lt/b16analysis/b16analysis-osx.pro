CONFIG += qt
QT += script scripttools
QMAKE_LFLAGS += -m32
QMAKE_CFLAGS += -m32
QMAKE_CXXFLAGS += -m32

# b16 base files
HEADERS += imageQW.h \
	imgLabel.h \
	imgSelection.h \
	thIntegrate_window.h \
	betterQSpinBox.h \
	imageView.h \
	dLineEdit.h \
	dSpinBox.h \
	dDoubleSpinBox.h \
	plotWidget.h \
	histoWidget.h \
	selectPoints.h \
	QTrack.h

	
SOURCES += imageQW.cc \
	imgLabel.cc \
	imgSelection.cc \
	thIntegrate_window.cc \
	plotWidget.cc \
	histoWidget.cc \
	selectPoints.cc \
	main.cc

# physImage
INCLUDEPATH += ../physImage
LIBS += -L../physImage
LIBS += ../physImage/b16img2.o \
	../physImage/physImage.o \
	../physImage/sifimg.o \
	../physImage/pgmimg.o \
	../physImage/tiffimg.o \
	../physImage/bmpimg.o

# SYSTEM
INCLUDEPATH += /sw/include
LIBS += -L/sw/lib 


# QWT
INCLUDEPATH += /sw/lib/qt4-x11/include/qwt 
LIBS += -L/sw/lib/qt4-x11/lib \
	-lqwt \
	-ltiff \
	-lnetpbm
