/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindowClass
{
public:
    QWidget *myCentralWidget;
    QGridLayout *gridLayout_7;
    QLabel *scaleLabel;
    QScrollArea *Sidebar;
    QWidget *scrollAreaWidgetContents_3;
    QGridLayout *gridLayout_6;
    QGridLayout *gridLayout_5;
    QToolButton *backButton;
    QPushButton *openButton;
    QToolButton *forwardButton;
    QPushButton *saveButton;
    QGroupBox *referenceGroupBox;
    QGridLayout *gridLayout;
    QPushButton *currentButton;
    QPushButton *referenceButton;
    QSpinBox *xshiftSpinBox;
    QSpinBox *yshiftSpinBox;
    QLabel *xshiftLabel;
    QLabel *yshiftLabel;
    QComboBox *referenceComboBox;
    QSpacerItem *verticalSpacer;
    QGroupBox *scaleGroupBox;
    QGridLayout *gridLayout_3;
    QComboBox *scaleComboBox;
    QHBoxLayout *horizontalLayout;
    QSpinBox *offsetSpinBox;
    QLabel *minMaxLabel;
    QSpinBox *cutoffSpinBox;
    QGroupBox *analysisGroupBox;
    QGridLayout *gridLayout_4;
    QCheckBox *XCheckBox;
    QPushButton *XCopyButton;
    QHBoxLayout *horizontalLayout_2;
    QSpinBox *X1SpinBox;
    QLabel *minMaxLabel_2;
    QSpinBox *X2SpinBox;
    QSpacerItem *verticalSpacer_6;
    QCheckBox *YCheckBox;
    QPushButton *YCopyButton;
    QHBoxLayout *horizontalLayout_3;
    QSpinBox *Y1SpinBox;
    QLabel *minMaxLabel_3;
    QSpinBox *Y2SpinBox;
    QCheckBox *beamCheckBox;
    QSpacerItem *verticalSpacer_2;
    QGroupBox *colormapGroupBox;
    QGridLayout *gridLayout_2;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *ZoomInButton;
    QPushButton *ZoomOutButton;
    QPushButton *UnzoomButton;
    QCheckBox *pseudocolorCheckBox;
    QCheckBox *invertedCheckBox;
    QGraphicsView *graphicsView;
    QToolButton *hideSidebarButton;
    QStatusBar *myStatusBar;

    void setupUi(QMainWindow *MainWindowClass)
    {
        if (MainWindowClass->objectName().isEmpty())
            MainWindowClass->setObjectName(QStringLiteral("MainWindowClass"));
        MainWindowClass->resize(746, 811);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindowClass->sizePolicy().hasHeightForWidth());
        MainWindowClass->setSizePolicy(sizePolicy);
        QIcon icon;
        icon.addFile(QStringLiteral(":/icon/valenky/valenky_48x48.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindowClass->setWindowIcon(icon);
        myCentralWidget = new QWidget(MainWindowClass);
        myCentralWidget->setObjectName(QStringLiteral("myCentralWidget"));
        gridLayout_7 = new QGridLayout(myCentralWidget);
        gridLayout_7->setSpacing(6);
        gridLayout_7->setContentsMargins(0, 0, 0, 0);
        gridLayout_7->setObjectName(QStringLiteral("gridLayout_7"));
        gridLayout_7->setHorizontalSpacing(1);
        gridLayout_7->setVerticalSpacing(0);
        scaleLabel = new QLabel(myCentralWidget);
        scaleLabel->setObjectName(QStringLiteral("scaleLabel"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(18);
        sizePolicy1.setVerticalStretch(10);
        sizePolicy1.setHeightForWidth(scaleLabel->sizePolicy().hasHeightForWidth());
        scaleLabel->setSizePolicy(sizePolicy1);
        scaleLabel->setMinimumSize(QSize(18, 0));
        scaleLabel->setMaximumSize(QSize(18, 16777215));
        scaleLabel->setContextMenuPolicy(Qt::CustomContextMenu);
        scaleLabel->setFrameShape(QFrame::NoFrame);

        gridLayout_7->addWidget(scaleLabel, 0, 0, 1, 1);

        Sidebar = new QScrollArea(myCentralWidget);
        Sidebar->setObjectName(QStringLiteral("Sidebar"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(Sidebar->sizePolicy().hasHeightForWidth());
        Sidebar->setSizePolicy(sizePolicy2);
        Sidebar->setFrameShape(QFrame::NoFrame);
        Sidebar->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        Sidebar->setWidgetResizable(true);
        scrollAreaWidgetContents_3 = new QWidget();
        scrollAreaWidgetContents_3->setObjectName(QStringLiteral("scrollAreaWidgetContents_3"));
        scrollAreaWidgetContents_3->setGeometry(QRect(0, 0, 194, 791));
        QSizePolicy sizePolicy3(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(scrollAreaWidgetContents_3->sizePolicy().hasHeightForWidth());
        scrollAreaWidgetContents_3->setSizePolicy(sizePolicy3);
        gridLayout_6 = new QGridLayout(scrollAreaWidgetContents_3);
        gridLayout_6->setSpacing(6);
        gridLayout_6->setContentsMargins(11, 11, 11, 11);
        gridLayout_6->setObjectName(QStringLiteral("gridLayout_6"));
        gridLayout_5 = new QGridLayout();
        gridLayout_5->setSpacing(6);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        backButton = new QToolButton(scrollAreaWidgetContents_3);
        backButton->setObjectName(QStringLiteral("backButton"));
        QSizePolicy sizePolicy4(QSizePolicy::Fixed, QSizePolicy::Minimum);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(backButton->sizePolicy().hasHeightForWidth());
        backButton->setSizePolicy(sizePolicy4);
#ifndef QT_NO_TOOLTIP
        backButton->setToolTip(QString::fromUtf8("\342\206\220"));
#endif // QT_NO_TOOLTIP
        backButton->setArrowType(Qt::LeftArrow);

        gridLayout_5->addWidget(backButton, 0, 0, 2, 1);

        openButton = new QPushButton(scrollAreaWidgetContents_3);
        openButton->setObjectName(QStringLiteral("openButton"));

        gridLayout_5->addWidget(openButton, 0, 1, 1, 1);

        forwardButton = new QToolButton(scrollAreaWidgetContents_3);
        forwardButton->setObjectName(QStringLiteral("forwardButton"));
        sizePolicy4.setHeightForWidth(forwardButton->sizePolicy().hasHeightForWidth());
        forwardButton->setSizePolicy(sizePolicy4);
#ifndef QT_NO_TOOLTIP
        forwardButton->setToolTip(QString::fromUtf8("\342\206\222"));
#endif // QT_NO_TOOLTIP
        forwardButton->setArrowType(Qt::RightArrow);

        gridLayout_5->addWidget(forwardButton, 0, 2, 2, 1);

        saveButton = new QPushButton(scrollAreaWidgetContents_3);
        saveButton->setObjectName(QStringLiteral("saveButton"));
#ifndef QT_NO_TOOLTIP
        saveButton->setToolTip(QStringLiteral("Ctrl+S"));
#endif // QT_NO_TOOLTIP

        gridLayout_5->addWidget(saveButton, 1, 1, 1, 1);


        gridLayout_6->addLayout(gridLayout_5, 0, 0, 1, 1);

        referenceGroupBox = new QGroupBox(scrollAreaWidgetContents_3);
        referenceGroupBox->setObjectName(QStringLiteral("referenceGroupBox"));
        gridLayout = new QGridLayout(referenceGroupBox);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        currentButton = new QPushButton(referenceGroupBox);
        currentButton->setObjectName(QStringLiteral("currentButton"));
#ifndef QT_NO_TOOLTIP
        currentButton->setToolTip(QStringLiteral("U"));
#endif // QT_NO_TOOLTIP

        gridLayout->addWidget(currentButton, 1, 1, 1, 1);

        referenceButton = new QPushButton(referenceGroupBox);
        referenceButton->setObjectName(QStringLiteral("referenceButton"));
#ifndef QT_NO_TOOLTIP
        referenceButton->setToolTip(QStringLiteral("L"));
#endif // QT_NO_TOOLTIP

        gridLayout->addWidget(referenceButton, 1, 0, 1, 1);

        xshiftSpinBox = new QSpinBox(referenceGroupBox);
        xshiftSpinBox->setObjectName(QStringLiteral("xshiftSpinBox"));
        xshiftSpinBox->setAccelerated(true);
        xshiftSpinBox->setMinimum(-10000);
        xshiftSpinBox->setMaximum(10000);

        gridLayout->addWidget(xshiftSpinBox, 2, 1, 1, 1);

        yshiftSpinBox = new QSpinBox(referenceGroupBox);
        yshiftSpinBox->setObjectName(QStringLiteral("yshiftSpinBox"));
        yshiftSpinBox->setAccelerated(true);
        yshiftSpinBox->setMinimum(-10000);
        yshiftSpinBox->setMaximum(10000);

        gridLayout->addWidget(yshiftSpinBox, 3, 1, 1, 1);

        xshiftLabel = new QLabel(referenceGroupBox);
        xshiftLabel->setObjectName(QStringLiteral("xshiftLabel"));

        gridLayout->addWidget(xshiftLabel, 2, 0, 1, 1);

        yshiftLabel = new QLabel(referenceGroupBox);
        yshiftLabel->setObjectName(QStringLiteral("yshiftLabel"));

        gridLayout->addWidget(yshiftLabel, 3, 0, 1, 1);

        referenceComboBox = new QComboBox(referenceGroupBox);
        referenceComboBox->setObjectName(QStringLiteral("referenceComboBox"));
        QSizePolicy sizePolicy5(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(referenceComboBox->sizePolicy().hasHeightForWidth());
        referenceComboBox->setSizePolicy(sizePolicy5);

        gridLayout->addWidget(referenceComboBox, 0, 0, 1, 2);


        gridLayout_6->addWidget(referenceGroupBox, 5, 0, 1, 1);

        verticalSpacer = new QSpacerItem(166, 13, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_6->addItem(verticalSpacer, 7, 0, 1, 1);

        scaleGroupBox = new QGroupBox(scrollAreaWidgetContents_3);
        scaleGroupBox->setObjectName(QStringLiteral("scaleGroupBox"));
        gridLayout_3 = new QGridLayout(scaleGroupBox);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        scaleComboBox = new QComboBox(scaleGroupBox);
        scaleComboBox->setObjectName(QStringLiteral("scaleComboBox"));
        sizePolicy5.setHeightForWidth(scaleComboBox->sizePolicy().hasHeightForWidth());
        scaleComboBox->setSizePolicy(sizePolicy5);

        gridLayout_3->addWidget(scaleComboBox, 0, 0, 1, 2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        offsetSpinBox = new QSpinBox(scaleGroupBox);
        offsetSpinBox->setObjectName(QStringLiteral("offsetSpinBox"));
        offsetSpinBox->setAccelerated(true);
        offsetSpinBox->setMinimum(-1000000);
        offsetSpinBox->setMaximum(1000000);

        horizontalLayout->addWidget(offsetSpinBox);

        minMaxLabel = new QLabel(scaleGroupBox);
        minMaxLabel->setObjectName(QStringLiteral("minMaxLabel"));
        QSizePolicy sizePolicy6(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy6.setHorizontalStretch(0);
        sizePolicy6.setVerticalStretch(0);
        sizePolicy6.setHeightForWidth(minMaxLabel->sizePolicy().hasHeightForWidth());
        minMaxLabel->setSizePolicy(sizePolicy6);

        horizontalLayout->addWidget(minMaxLabel);

        cutoffSpinBox = new QSpinBox(scaleGroupBox);
        cutoffSpinBox->setObjectName(QStringLiteral("cutoffSpinBox"));
        cutoffSpinBox->setAccelerated(true);
        cutoffSpinBox->setMinimum(-1000000);
        cutoffSpinBox->setMaximum(1000000);

        horizontalLayout->addWidget(cutoffSpinBox);


        gridLayout_3->addLayout(horizontalLayout, 1, 0, 1, 2);


        gridLayout_6->addWidget(scaleGroupBox, 2, 0, 1, 1);

        analysisGroupBox = new QGroupBox(scrollAreaWidgetContents_3);
        analysisGroupBox->setObjectName(QStringLiteral("analysisGroupBox"));
        gridLayout_4 = new QGridLayout(analysisGroupBox);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        XCheckBox = new QCheckBox(analysisGroupBox);
        XCheckBox->setObjectName(QStringLiteral("XCheckBox"));

        gridLayout_4->addWidget(XCheckBox, 0, 0, 1, 1);

        XCopyButton = new QPushButton(analysisGroupBox);
        XCopyButton->setObjectName(QStringLiteral("XCopyButton"));
#ifndef QT_NO_TOOLTIP
        XCopyButton->setToolTip(QStringLiteral("Alt+X"));
#endif // QT_NO_TOOLTIP

        gridLayout_4->addWidget(XCopyButton, 0, 1, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        X1SpinBox = new QSpinBox(analysisGroupBox);
        X1SpinBox->setObjectName(QStringLiteral("X1SpinBox"));
        X1SpinBox->setAccelerated(true);
        X1SpinBox->setSingleStep(1);

        horizontalLayout_2->addWidget(X1SpinBox);

        minMaxLabel_2 = new QLabel(analysisGroupBox);
        minMaxLabel_2->setObjectName(QStringLiteral("minMaxLabel_2"));
        sizePolicy6.setHeightForWidth(minMaxLabel_2->sizePolicy().hasHeightForWidth());
        minMaxLabel_2->setSizePolicy(sizePolicy6);

        horizontalLayout_2->addWidget(minMaxLabel_2);

        X2SpinBox = new QSpinBox(analysisGroupBox);
        X2SpinBox->setObjectName(QStringLiteral("X2SpinBox"));
        X2SpinBox->setAccelerated(true);
        X2SpinBox->setSingleStep(1);

        horizontalLayout_2->addWidget(X2SpinBox);


        gridLayout_4->addLayout(horizontalLayout_2, 1, 0, 1, 2);

        verticalSpacer_6 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout_4->addItem(verticalSpacer_6, 2, 0, 1, 1);

        YCheckBox = new QCheckBox(analysisGroupBox);
        YCheckBox->setObjectName(QStringLiteral("YCheckBox"));

        gridLayout_4->addWidget(YCheckBox, 3, 0, 1, 1);

        YCopyButton = new QPushButton(analysisGroupBox);
        YCopyButton->setObjectName(QStringLiteral("YCopyButton"));
#ifndef QT_NO_TOOLTIP
        YCopyButton->setToolTip(QStringLiteral("Alt+Y"));
#endif // QT_NO_TOOLTIP

        gridLayout_4->addWidget(YCopyButton, 3, 1, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        Y1SpinBox = new QSpinBox(analysisGroupBox);
        Y1SpinBox->setObjectName(QStringLiteral("Y1SpinBox"));
        Y1SpinBox->setAccelerated(true);
        Y1SpinBox->setSingleStep(1);

        horizontalLayout_3->addWidget(Y1SpinBox);

        minMaxLabel_3 = new QLabel(analysisGroupBox);
        minMaxLabel_3->setObjectName(QStringLiteral("minMaxLabel_3"));
        sizePolicy6.setHeightForWidth(minMaxLabel_3->sizePolicy().hasHeightForWidth());
        minMaxLabel_3->setSizePolicy(sizePolicy6);

        horizontalLayout_3->addWidget(minMaxLabel_3);

        Y2SpinBox = new QSpinBox(analysisGroupBox);
        Y2SpinBox->setObjectName(QStringLiteral("Y2SpinBox"));
        Y2SpinBox->setAccelerated(true);
        Y2SpinBox->setSingleStep(1);

        horizontalLayout_3->addWidget(Y2SpinBox);


        gridLayout_4->addLayout(horizontalLayout_3, 5, 0, 1, 2);

        beamCheckBox = new QCheckBox(analysisGroupBox);
        beamCheckBox->setObjectName(QStringLiteral("beamCheckBox"));

        gridLayout_4->addWidget(beamCheckBox, 7, 0, 1, 2);

        verticalSpacer_2 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout_4->addItem(verticalSpacer_2, 6, 0, 1, 1);


        gridLayout_6->addWidget(analysisGroupBox, 4, 0, 1, 1);

        colormapGroupBox = new QGroupBox(scrollAreaWidgetContents_3);
        colormapGroupBox->setObjectName(QStringLiteral("colormapGroupBox"));
        gridLayout_2 = new QGridLayout(colormapGroupBox);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        ZoomInButton = new QPushButton(colormapGroupBox);
        ZoomInButton->setObjectName(QStringLiteral("ZoomInButton"));
        sizePolicy5.setHeightForWidth(ZoomInButton->sizePolicy().hasHeightForWidth());
        ZoomInButton->setSizePolicy(sizePolicy5);
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/icon/zoom-in.png"), QSize(), QIcon::Normal, QIcon::Off);
        ZoomInButton->setIcon(icon1);
        ZoomInButton->setIconSize(QSize(22, 22));

        horizontalLayout_4->addWidget(ZoomInButton);

        ZoomOutButton = new QPushButton(colormapGroupBox);
        ZoomOutButton->setObjectName(QStringLiteral("ZoomOutButton"));
        sizePolicy5.setHeightForWidth(ZoomOutButton->sizePolicy().hasHeightForWidth());
        ZoomOutButton->setSizePolicy(sizePolicy5);
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/icon/zoom-out.png"), QSize(), QIcon::Normal, QIcon::Off);
        ZoomOutButton->setIcon(icon2);
        ZoomOutButton->setIconSize(QSize(22, 22));

        horizontalLayout_4->addWidget(ZoomOutButton);

        UnzoomButton = new QPushButton(colormapGroupBox);
        UnzoomButton->setObjectName(QStringLiteral("UnzoomButton"));
        sizePolicy5.setHeightForWidth(UnzoomButton->sizePolicy().hasHeightForWidth());
        UnzoomButton->setSizePolicy(sizePolicy5);
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/icon/zoom-100.png"), QSize(), QIcon::Normal, QIcon::Off);
        UnzoomButton->setIcon(icon3);
        UnzoomButton->setIconSize(QSize(22, 22));

        horizontalLayout_4->addWidget(UnzoomButton);


        gridLayout_2->addLayout(horizontalLayout_4, 1, 0, 1, 2);

        pseudocolorCheckBox = new QCheckBox(colormapGroupBox);
        pseudocolorCheckBox->setObjectName(QStringLiteral("pseudocolorCheckBox"));

        gridLayout_2->addWidget(pseudocolorCheckBox, 0, 0, 1, 1);

        invertedCheckBox = new QCheckBox(colormapGroupBox);
        invertedCheckBox->setObjectName(QStringLiteral("invertedCheckBox"));

        gridLayout_2->addWidget(invertedCheckBox, 0, 1, 1, 1);


        gridLayout_6->addWidget(colormapGroupBox, 3, 0, 1, 1);

        Sidebar->setWidget(scrollAreaWidgetContents_3);

        gridLayout_7->addWidget(Sidebar, 0, 1, 2, 1);

        graphicsView = new QGraphicsView(myCentralWidget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->setMouseTracking(true);
        graphicsView->setFrameShape(QFrame::NoFrame);
        graphicsView->setInteractive(true);
        graphicsView->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);

        gridLayout_7->addWidget(graphicsView, 0, 2, 2, 1);

        hideSidebarButton = new QToolButton(myCentralWidget);
        hideSidebarButton->setObjectName(QStringLiteral("hideSidebarButton"));
        sizePolicy5.setHeightForWidth(hideSidebarButton->sizePolicy().hasHeightForWidth());
        hideSidebarButton->setSizePolicy(sizePolicy5);
        hideSidebarButton->setMinimumSize(QSize(18, 0));
        hideSidebarButton->setMaximumSize(QSize(18, 16777215));
        hideSidebarButton->setCheckable(true);
        hideSidebarButton->setChecked(true);
        hideSidebarButton->setArrowType(Qt::LeftArrow);

        gridLayout_7->addWidget(hideSidebarButton, 1, 0, 1, 1);

        MainWindowClass->setCentralWidget(myCentralWidget);
        myStatusBar = new QStatusBar(MainWindowClass);
        myStatusBar->setObjectName(QStringLiteral("myStatusBar"));
        MainWindowClass->setStatusBar(myStatusBar);
        QWidget::setTabOrder(backButton, openButton);
        QWidget::setTabOrder(openButton, saveButton);
        QWidget::setTabOrder(saveButton, forwardButton);
        QWidget::setTabOrder(forwardButton, scaleComboBox);
        QWidget::setTabOrder(scaleComboBox, offsetSpinBox);
        QWidget::setTabOrder(offsetSpinBox, cutoffSpinBox);
        QWidget::setTabOrder(cutoffSpinBox, XCheckBox);
        QWidget::setTabOrder(XCheckBox, XCopyButton);
        QWidget::setTabOrder(XCopyButton, X1SpinBox);
        QWidget::setTabOrder(X1SpinBox, X2SpinBox);
        QWidget::setTabOrder(X2SpinBox, YCheckBox);
        QWidget::setTabOrder(YCheckBox, YCopyButton);
        QWidget::setTabOrder(YCopyButton, Y1SpinBox);
        QWidget::setTabOrder(Y1SpinBox, Y2SpinBox);
        QWidget::setTabOrder(Y2SpinBox, referenceComboBox);
        QWidget::setTabOrder(referenceComboBox, referenceButton);
        QWidget::setTabOrder(referenceButton, currentButton);
        QWidget::setTabOrder(currentButton, xshiftSpinBox);
        QWidget::setTabOrder(xshiftSpinBox, yshiftSpinBox);
        QWidget::setTabOrder(yshiftSpinBox, hideSidebarButton);
        QWidget::setTabOrder(hideSidebarButton, Sidebar);
        QWidget::setTabOrder(Sidebar, graphicsView);

        retranslateUi(MainWindowClass);
        QObject::connect(hideSidebarButton, SIGNAL(toggled(bool)), Sidebar, SLOT(setVisible(bool)));

        QMetaObject::connectSlotsByName(MainWindowClass);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindowClass)
    {
        MainWindowClass->setWindowTitle(QApplication::translate("MainWindowClass", "easyFG", 0));
        scaleLabel->setText(QApplication::translate("MainWindowClass", "[*]", 0));
        backButton->setText(QApplication::translate("MainWindowClass", "<", 0));
#ifndef QT_NO_TOOLTIP
        openButton->setToolTip(QApplication::translate("MainWindowClass", "Ctrl+O", 0));
#endif // QT_NO_TOOLTIP
        openButton->setText(QApplication::translate("MainWindowClass", "Open...", 0));
        forwardButton->setText(QApplication::translate("MainWindowClass", ">", 0));
        saveButton->setText(QApplication::translate("MainWindowClass", "Save image...", 0));
        referenceGroupBox->setTitle(QApplication::translate("MainWindowClass", "Reference", 0));
        currentButton->setText(QApplication::translate("MainWindowClass", "Use current", 0));
        referenceButton->setText(QApplication::translate("MainWindowClass", "Load...", 0));
        xshiftLabel->setText(QApplication::translate("MainWindowClass", "X shift", 0));
        yshiftLabel->setText(QApplication::translate("MainWindowClass", "Y shift", 0));
        referenceComboBox->clear();
        referenceComboBox->insertItems(0, QStringList()
         << QApplication::translate("MainWindowClass", "OFF", 0)
         << QApplication::translate("MainWindowClass", "Substract (data-ref)", 0)
         << QApplication::translate("MainWindowClass", "Divide (data/ref*const)", 0)
         << QApplication::translate("MainWindowClass", "Show reference", 0)
        );
#ifndef QT_NO_TOOLTIP
        referenceComboBox->setToolTip(QApplication::translate("MainWindowClass", "= (OFF)\n"
"- (Substract)\n"
"/ (Divide)\n"
"R (Show reference)", 0));
#endif // QT_NO_TOOLTIP
        scaleGroupBox->setTitle(QApplication::translate("MainWindowClass", "Scale", 0));
        scaleComboBox->clear();
        scaleComboBox->insertItems(0, QStringList()
         << QApplication::translate("MainWindowClass", "Auto", 0)
         << QApplication::translate("MainWindowClass", "Custom", 0)
         << QApplication::translate("MainWindowClass", "Min:Max", 0)
         << QApplication::translate("MainWindowClass", "7 bit", 0)
         << QApplication::translate("MainWindowClass", "8 bit", 0)
         << QApplication::translate("MainWindowClass", "9 bit", 0)
         << QApplication::translate("MainWindowClass", "10 bit", 0)
         << QApplication::translate("MainWindowClass", "11 bit", 0)
         << QApplication::translate("MainWindowClass", "12 bit", 0)
         << QApplication::translate("MainWindowClass", "13 bit", 0)
         << QApplication::translate("MainWindowClass", "14 bit", 0)
         << QApplication::translate("MainWindowClass", "15 bit", 0)
         << QApplication::translate("MainWindowClass", "16 bit", 0)
        );
#ifndef QT_NO_TOOLTIP
        scaleComboBox->setToolTip(QApplication::translate("MainWindowClass", "A (Auto)\n"
"C (Custom)\n"
"M (Min:Max)\n"
"7 (7 bit)\n"
"8 (8 bit)\n"
"9 (9 bit)\n"
"0 (10 bit)\n"
"1 (11 bit)\n"
"2 (12 bit)\n"
"3 (13 bit)\n"
"4 (14 bit)\n"
"5 (15 bit)\n"
"6 (16 bit)", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        offsetSpinBox->setToolTip(QApplication::translate("MainWindowClass", "o (0)", 0));
#endif // QT_NO_TOOLTIP
        minMaxLabel->setText(QApplication::translate("MainWindowClass", "<b>:</b>", 0));
        analysisGroupBox->setTitle(QApplication::translate("MainWindowClass", "Analysis", 0));
#ifndef QT_NO_TOOLTIP
        XCheckBox->setToolTip(QApplication::translate("MainWindowClass", "X", 0));
#endif // QT_NO_TOOLTIP
        XCheckBox->setText(QApplication::translate("MainWindowClass", "X", 0));
        XCopyButton->setText(QApplication::translate("MainWindowClass", "Copy", 0));
#ifndef QT_NO_TOOLTIP
        X1SpinBox->setToolTip(QApplication::translate("MainWindowClass", "Ctrl+A: whole image", 0));
#endif // QT_NO_TOOLTIP
        minMaxLabel_2->setText(QApplication::translate("MainWindowClass", "<b>:</b>", 0));
#ifndef QT_NO_TOOLTIP
        X2SpinBox->setToolTip(QApplication::translate("MainWindowClass", "Ctrl+A: whole image", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        YCheckBox->setToolTip(QApplication::translate("MainWindowClass", "Y", 0));
#endif // QT_NO_TOOLTIP
        YCheckBox->setText(QApplication::translate("MainWindowClass", "Y", 0));
        YCopyButton->setText(QApplication::translate("MainWindowClass", "Copy", 0));
#ifndef QT_NO_TOOLTIP
        Y1SpinBox->setToolTip(QApplication::translate("MainWindowClass", "Ctrl+A: whole image", 0));
#endif // QT_NO_TOOLTIP
        minMaxLabel_3->setText(QApplication::translate("MainWindowClass", "<b>:</b>", 0));
#ifndef QT_NO_TOOLTIP
        Y2SpinBox->setToolTip(QApplication::translate("MainWindowClass", "Ctrl+A: whole image", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        beamCheckBox->setToolTip(QApplication::translate("MainWindowClass", "B", 0));
#endif // QT_NO_TOOLTIP
        beamCheckBox->setText(QApplication::translate("MainWindowClass", "Beam size (D4\317\203)", 0));
        colormapGroupBox->setTitle(QApplication::translate("MainWindowClass", "Image", 0));
#ifndef QT_NO_TOOLTIP
        ZoomInButton->setToolTip(QApplication::translate("MainWindowClass", "Ctrl ++", 0));
#endif // QT_NO_TOOLTIP
        ZoomInButton->setText(QString());
#ifndef QT_NO_TOOLTIP
        ZoomOutButton->setToolTip(QApplication::translate("MainWindowClass", "Ctrl +-", 0));
#endif // QT_NO_TOOLTIP
        ZoomOutButton->setText(QString());
#ifndef QT_NO_TOOLTIP
        UnzoomButton->setToolTip(QApplication::translate("MainWindowClass", "Ctrl+0", 0));
#endif // QT_NO_TOOLTIP
        UnzoomButton->setText(QString());
#ifndef QT_NO_TOOLTIP
        pseudocolorCheckBox->setToolTip(QApplication::translate("MainWindowClass", "P", 0));
#endif // QT_NO_TOOLTIP
        pseudocolorCheckBox->setText(QApplication::translate("MainWindowClass", "Pseudocolor", 0));
#ifndef QT_NO_TOOLTIP
        invertedCheckBox->setToolTip(QApplication::translate("MainWindowClass", "i", 0));
#endif // QT_NO_TOOLTIP
        invertedCheckBox->setText(QApplication::translate("MainWindowClass", "Inverted", 0));
#ifndef QT_NO_TOOLTIP
        hideSidebarButton->setToolTip(QApplication::translate("MainWindowClass", "S (F11 for fullscreen)", 0));
#endif // QT_NO_TOOLTIP
        hideSidebarButton->setText(QString());
        hideSidebarButton->setShortcut(QApplication::translate("MainWindowClass", "S", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindowClass: public Ui_MainWindowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
