CONFIG += qt


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

# QWT
INCLUDEPATH += /usr/include/qwt-qt4
LIBS += -L/usr/lib \
	-lqwt-qt4 \
	-ltiff \
	-lnetpbm

# histograms
INCLUDEPATH += ../hist_analysis
LIBS += -L../hist_analysis
LIBS += ../hist_analysis/polyhist.o
HEADERS += QPolyHist_win.h QPolyHist.h 
SOURCES += QPolyHist_win.cc

HEADERS += QPolyHist2.h QPH_sub.h QPH_painter.h
SOURCES += QPolyHist2.cc QPH_sub.cc 

# monitors
#HEADERS += interfMonitor.h
#SOURCES += interfMonitor.cc

# ion Trajectories
INCLUDEPATH += ../ionTraj ../external/include ../home/include
LIBS += -L../external/lib -L../home/lib


HEADERS += QIonTraj.h \
	   tpImageParameters.h \
	../ionTraj/tpSystem.h
SOURCES += QIonTraj.cc
LIBS += -lconfig++ \
	-lgsl -lgslcblas -lm



# pco support
DEFINES += __have_PCO
CXXFLAGS += -D__have_PCO
INCLUDEPATH += ../PCO/pcclib ../PCO/pccdrvh
LIBS += -L../PCO/pcclib/rel \
	-lpfcam
HEADERS += PCOcontroller.h \
	PCOreader.h
SOURCES += PCOcontroller.cc \
	PCOreader.cc

