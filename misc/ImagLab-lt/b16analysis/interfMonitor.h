/********************************************************************************
** Form generated from reading ui file 'interfMonitor.ui'
**
** Created: Tue Jul 10 21:13:28 2007
**      by: Qt User Interface Compiler version 4.2.2
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef INTERFMONITOR_H
#define INTERFMONITOR_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QFrame>
#include <QtGui/QGroupBox>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

class Ui_interfMonitor 
{
public:
    QGroupBox *groupBox;
    QCheckBox *zeroOrderPeak_toggle;
    QCheckBox *vCut_toggle;
    QCheckBox *hCut_toggle;
    QCheckBox *Fplane_toggle;
    QFrame *line;
    QLabel *label;
    QGroupBox *groupBox_2;
    QCheckBox *extTrig_toggle;
    QCheckBox *stepMotor_toggle;
    QPushButton *stopMonitor_pb;
    QPushButton *startMonitor_pb;
    QPushButton *clearHist_pb;

    void setupUi(QWidget *interfMonitor)
    {
    interfMonitor->setObjectName(QString::fromUtf8("interfMonitor"));
    groupBox = new QGroupBox(interfMonitor);
    groupBox->setObjectName(QString::fromUtf8("groupBox"));
    groupBox->setGeometry(QRect(10, 10, 381, 80));
    zeroOrderPeak_toggle = new QCheckBox(groupBox);
    zeroOrderPeak_toggle->setObjectName(QString::fromUtf8("zeroOrderPeak_toggle"));
    zeroOrderPeak_toggle->setGeometry(QRect(20, 20, 161, 23));
    vCut_toggle = new QCheckBox(groupBox);
    vCut_toggle->setObjectName(QString::fromUtf8("vCut_toggle"));
    vCut_toggle->setGeometry(QRect(190, 20, 171, 23));
    hCut_toggle = new QCheckBox(groupBox);
    hCut_toggle->setObjectName(QString::fromUtf8("hCut_toggle"));
    hCut_toggle->setGeometry(QRect(20, 50, 151, 23));
    Fplane_toggle = new QCheckBox(groupBox);
    Fplane_toggle->setObjectName(QString::fromUtf8("Fplane_toggle"));
    Fplane_toggle->setGeometry(QRect(190, 50, 171, 23));
    line = new QFrame(interfMonitor);
    line->setObjectName(QString::fromUtf8("line"));
    line->setGeometry(QRect(10, 310, 381, 16));
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);
    label = new QLabel(interfMonitor);
    label->setObjectName(QString::fromUtf8("label"));
    label->setGeometry(QRect(10, 320, 381, 91));
    QFont font;
    font.setPointSize(6);
    label->setFont(font);
    label->setAlignment(Qt::AlignJustify|Qt::AlignVCenter);
    label->setWordWrap(true);
    groupBox_2 = new QGroupBox(interfMonitor);
    groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
    groupBox_2->setGeometry(QRect(10, 100, 381, 81));
    extTrig_toggle = new QCheckBox(groupBox_2);
    extTrig_toggle->setObjectName(QString::fromUtf8("extTrig_toggle"));
    extTrig_toggle->setGeometry(QRect(20, 20, 161, 23));
    stepMotor_toggle = new QCheckBox(groupBox_2);
    stepMotor_toggle->setObjectName(QString::fromUtf8("stepMotor_toggle"));
    stepMotor_toggle->setGeometry(QRect(20, 50, 161, 23));
    stopMonitor_pb = new QPushButton(interfMonitor);
    stopMonitor_pb->setObjectName(QString::fromUtf8("stopMonitor_pb"));
    stopMonitor_pb->setGeometry(QRect(320, 220, 61, 27));
    startMonitor_pb = new QPushButton(interfMonitor);
    startMonitor_pb->setObjectName(QString::fromUtf8("startMonitor_pb"));
    startMonitor_pb->setGeometry(QRect(320, 190, 61, 27));
    clearHist_pb = new QPushButton(interfMonitor);
    clearHist_pb->setObjectName(QString::fromUtf8("clearHist_pb"));
    clearHist_pb->setGeometry(QRect(10, 190, 121, 27));

    retranslateUi(interfMonitor);

    QSize size(400, 413);
    size = size.expandedTo(interfMonitor->minimumSizeHint());
    interfMonitor->resize(size);


    QMetaObject::connectSlotsByName(interfMonitor);
    } // setupUi

    void retranslateUi(QWidget *interfMonitor)
    {
    interfMonitor->setWindowTitle(QApplication::translate("interfMonitor", "2D FFT Monitor", 0, QApplication::UnicodeUTF8));
    groupBox->setTitle(QApplication::translate("interfMonitor", "display variables", 0, QApplication::UnicodeUTF8));
    zeroOrderPeak_toggle->setText(QApplication::translate("interfMonitor", "zero order peak level", 0, QApplication::UnicodeUTF8));
    vCut_toggle->setText(QApplication::translate("interfMonitor", "vertical cut", 0, QApplication::UnicodeUTF8));
    hCut_toggle->setText(QApplication::translate("interfMonitor", "horizontal cut", 0, QApplication::UnicodeUTF8));
    Fplane_toggle->setText(QApplication::translate("interfMonitor", "F plane rotation", 0, QApplication::UnicodeUTF8));
    label->setText(QApplication::translate("interfMonitor", "<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans Serif'; font-size:6pt; font-weight:400; font-style:normal; text-decoration:none;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:9pt;\"><span style=\" font-weight:600;\">2D FFT Monitor</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:9pt;\">When running PCO real time acquisition, it calculates the (normalized) 2D FFT of every frame and displays various results (useful to look for interference condition in the image).</p></body></html>", 0, QApplication::UnicodeUTF8));
    groupBox_2->setTitle(QApplication::translate("interfMonitor", "controls", 0, QApplication::UnicodeUTF8));
    extTrig_toggle->setText(QApplication::translate("interfMonitor", "external trigger", 0, QApplication::UnicodeUTF8));
    stepMotor_toggle->setText(QApplication::translate("interfMonitor", "send motor steps", 0, QApplication::UnicodeUTF8));
    stopMonitor_pb->setText(QApplication::translate("interfMonitor", "Stop", 0, QApplication::UnicodeUTF8));
    startMonitor_pb->setText(QApplication::translate("interfMonitor", "Start", 0, QApplication::UnicodeUTF8));
    clearHist_pb->setText(QApplication::translate("interfMonitor", "Clear History", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(interfMonitor);
    } // retranslateUi

};


class interfMonitor: public QWidget {
	Q_OBJECT

public:
	interfMonitor(void);
	~interfMonitor(void);


};

#endif // INTERFMONITOR_H
