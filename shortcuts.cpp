#include "easyfg.h"


void MainWindow::InitializeShortcuts()
{
    QShortcut *shortcut;

    flag_fullscreen = false;
    shortcut = new QShortcut(QKeySequence("F11"),this);
    connect(shortcut, SIGNAL(activated()), this, SLOT(Shortcut_F11()));

    shortcut = new QShortcut(QKeySequence("ESC"),this);
    connect(shortcut, SIGNAL(activated()), this, SLOT(Shortcut_ESC()));

    shortcut = new QShortcut(QKeySequence("Ctrl+O"),this);
    connect(shortcut, SIGNAL(activated()), this, SLOT(on_openButton_clicked()));

    shortcut = new QShortcut(QKeySequence("Ctrl+S"),this);
    connect(shortcut, SIGNAL(activated()), this, SLOT(on_saveButton_clicked()));

    shortcut = new QShortcut(QKeySequence("Right"),this);
    connect(shortcut, SIGNAL(activated()), this, SLOT(on_forwardButton_clicked()));

    shortcut = new QShortcut(QKeySequence("Left"),this);
    connect(shortcut, SIGNAL(activated()), this, SLOT(on_backButton_clicked()));

    shortcut = new QShortcut(QKeySequence("Ctrl++"),this);
    connect(shortcut, SIGNAL(activated()), this, SLOT(on_ZoomInButton_clicked()));
    shortcut = new QShortcut(QKeySequence("Ctrl+="),this);
    connect(shortcut, SIGNAL(activated()), this, SLOT(on_ZoomInButton_clicked()));
    shortcut = new QShortcut(QKeySequence("Ctrl+MouseWheelUp"),this);
    connect(shortcut, SIGNAL(activated()), this, SLOT(on_ZoomInButton_clicked()));

    shortcut = new QShortcut(QKeySequence("Ctrl+-"),this);
    connect(shortcut, SIGNAL(activated()), this, SLOT(on_ZoomOutButton_clicked()));

    shortcut = new QShortcut(QKeySequence("Ctrl+0"),this);
    connect(shortcut, SIGNAL(activated()), this, SLOT(on_UnzoomButton_clicked()));

    shortcut = new QShortcut(QKeySequence("A"),this);
    connect(shortcut, SIGNAL(activated()), this, SLOT(Shortcut_A()));

    shortcut = new QShortcut(QKeySequence("C"),this);
    connect(shortcut, SIGNAL(activated()), this, SLOT(Shortcut_C()));

    shortcut = new QShortcut(QKeySequence("M"),this);
    connect(shortcut, SIGNAL(activated()), this, SLOT(Shortcut_M()));

    shortcut = new QShortcut(QKeySequence("0"),this);
    connect(shortcut, SIGNAL(activated()), this, SLOT(Shortcut_0()));

    shortcut = new QShortcut(QKeySequence("1"),this);
    connect(shortcut, SIGNAL(activated()), this, SLOT(Shortcut_1()));

    shortcut = new QShortcut(QKeySequence("2"),this);
    connect(shortcut, SIGNAL(activated()), this, SLOT(Shortcut_2()));

    shortcut = new QShortcut(QKeySequence("3"),this);
    connect(shortcut, SIGNAL(activated()), this, SLOT(Shortcut_3()));

    shortcut = new QShortcut(QKeySequence("4"),this);
    connect(shortcut, SIGNAL(activated()), this, SLOT(Shortcut_4()));

    shortcut = new QShortcut(QKeySequence("5"),this);
    connect(shortcut, SIGNAL(activated()), this, SLOT(Shortcut_5()));

    shortcut = new QShortcut(QKeySequence("6"),this);
    connect(shortcut, SIGNAL(activated()), this, SLOT(Shortcut_6()));

    shortcut = new QShortcut(QKeySequence("7"),this);
    connect(shortcut, SIGNAL(activated()), this, SLOT(Shortcut_7()));

    shortcut = new QShortcut(QKeySequence("8"),this);
    connect(shortcut, SIGNAL(activated()), this, SLOT(Shortcut_8()));

    shortcut = new QShortcut(QKeySequence("9"),this);
    connect(shortcut, SIGNAL(activated()), this, SLOT(Shortcut_9()));

    shortcut = new QShortcut(QKeySequence("o"),this);
    connect(shortcut, SIGNAL(activated()), this, SLOT(Shortcut_o()));

    shortcut = new QShortcut(QKeySequence("P"),this);
    connect(shortcut, SIGNAL(activated()), this, SLOT(Shortcut_P()));

    shortcut = new QShortcut(QKeySequence("I"),this);
    connect(shortcut, SIGNAL(activated()), this, SLOT(Shortcut_I()));

    shortcut = new QShortcut(QKeySequence("X"),this);
    connect(shortcut, SIGNAL(activated()), this, SLOT(Shortcut_X()));

    shortcut = new QShortcut(QKeySequence("Y"),this);
    connect(shortcut, SIGNAL(activated()), this, SLOT(Shortcut_Y()));

    shortcut = new QShortcut(QKeySequence("Ctrl+A"),this);
    connect(shortcut, SIGNAL(activated()), this, SLOT(Shortcut_CtrlA()));

    shortcut = new QShortcut(QKeySequence("Alt+X"),this);
    connect(shortcut, SIGNAL(activated()), this, SLOT(on_XCopyButton_clicked()));

    shortcut = new QShortcut(QKeySequence("Alt+Y"),this);
    connect(shortcut, SIGNAL(activated()), this, SLOT(on_YCopyButton_clicked()));

    shortcut = new QShortcut(QKeySequence("Alt+I"),this);
    connect(shortcut, SIGNAL(activated()), this, SLOT(CopyFigure()));

    shortcut = new QShortcut(QKeySequence("B"),this);
    connect(shortcut, SIGNAL(activated()), this, SLOT(Shortcut_B()));

    shortcut = new QShortcut(QKeySequence("L"),this);
    connect(shortcut, SIGNAL(activated()), this, SLOT(on_referenceButton_clicked()));

    shortcut = new QShortcut(QKeySequence("U"),this);
    connect(shortcut, SIGNAL(activated()), this, SLOT(on_currentButton_clicked()));

    shortcut = new QShortcut(QKeySequence("="),this);
    connect(shortcut, SIGNAL(activated()), this, SLOT(Shortcut_equal()));

    shortcut = new QShortcut(QKeySequence("-"),this);
    connect(shortcut, SIGNAL(activated()), this, SLOT(Shortcut_substract()));

    shortcut = new QShortcut(QKeySequence("/"),this);
    connect(shortcut, SIGNAL(activated()), this, SLOT(Shortcut_divide()));

    shortcut = new QShortcut(QKeySequence("R"),this);
    connect(shortcut, SIGNAL(activated()), this, SLOT(Shortcut_R()));
}


void MainWindow::Shortcut_F11() // fullscreen
{
    QSettings settings("ATF", "easyFG");
    if(flag_fullscreen){
        showNormal();
        restoreGeometry(settings.value("window_geometry").toByteArray());
        flag_fullscreen = false;
    }
    else{
        settings.setValue("window_geometry", saveGeometry());
        showFullScreen();
        flag_fullscreen = true;
    }

}


void MainWindow::Shortcut_ESC() // leave fullscreen
{
    QSettings settings("ATF", "easyFG");
    if(flag_fullscreen){
        showNormal();
        restoreGeometry(settings.value("window_geometry").toByteArray());
        flag_fullscreen = false;
    }
}


void MainWindow::Shortcut_X()
{
        XCheckBox->setChecked(!XCheckBox->isChecked());
}


void MainWindow::Shortcut_Y()
{
        YCheckBox->setChecked(!YCheckBox->isChecked());
}

void MainWindow::Shortcut_CtrlA()
{
	X1SpinBox->setValue(0);
	X2SpinBox->setValue(dataheight - 1);
	Y1SpinBox->setValue(0);
	Y2SpinBox->setValue(datawidth - 1);
}

void MainWindow::Shortcut_B()
{
	beamCheckBox->setChecked(!beamCheckBox->isChecked());
}

void MainWindow::Shortcut_P()
{
        pseudocolorCheckBox->setChecked(!pseudocolorCheckBox->isChecked());
}

void MainWindow::Shortcut_I()
{
        invertedCheckBox->setChecked(!invertedCheckBox->isChecked());
}

void MainWindow::Shortcut_equal()
{
        referenceComboBox->setCurrentIndex(0); // Reference: OFF
}

void MainWindow::Shortcut_substract()
{
        referenceComboBox->setCurrentIndex(1); // Reference: Substract
}

void MainWindow::Shortcut_divide()
{
        referenceComboBox->setCurrentIndex(2); // Reference: Divide
}

void MainWindow::Shortcut_R()
{
        referenceComboBox->setCurrentIndex(3); // Reference: Show reference
}

void MainWindow::Shortcut_A()
{
        scaleComboBox->setCurrentIndex(0); // Scale: Auto
}

void MainWindow::Shortcut_C()
{
        scaleComboBox->setCurrentIndex(1); // Scale: Custom
}

void MainWindow::Shortcut_M()
{
        scaleComboBox->setCurrentIndex(2); // Scale: Min:Max
}

void MainWindow::Shortcut_7()
{
        scaleComboBox->setCurrentIndex(3); // Scale: 7 bit
}

void MainWindow::Shortcut_8()
{
        scaleComboBox->setCurrentIndex(4); // Scale: 8 bit
}

void MainWindow::Shortcut_9()
{
        scaleComboBox->setCurrentIndex(5); // Scale: 9 bit
}

void MainWindow::Shortcut_0()
{
        scaleComboBox->setCurrentIndex(6); // Scale: 10 bit
}

void MainWindow::Shortcut_1()
{
        scaleComboBox->setCurrentIndex(7); // Scale: 11 bit
}

void MainWindow::Shortcut_2()
{
        scaleComboBox->setCurrentIndex(8); // Scale: 12 bit
}

void MainWindow::Shortcut_3()
{
        scaleComboBox->setCurrentIndex(9); // Scale: 13 bit
}

void MainWindow::Shortcut_4()
{
        scaleComboBox->setCurrentIndex(10); // Scale: 14 bit
}

void MainWindow::Shortcut_5()
{
        scaleComboBox->setCurrentIndex(11); // Scale: 15 bit
}

void MainWindow::Shortcut_6()
{
        scaleComboBox->setCurrentIndex(12); // Scale: 16 bit
}

void MainWindow::Shortcut_o()
{
    if(scaleComboBox->currentIndex() == 2) // if Scale: Min:Max
        scaleComboBox->setCurrentIndex(1); // Scale: Custom
    offsetSpinBox->setValue(0);// Min: 0
}
