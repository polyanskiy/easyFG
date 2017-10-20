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

    shortcut = new QShortcut(QKeySequence(QKeySequence::ZoomIn),this);
    connect(shortcut, SIGNAL(activated()), this, SLOT(on_ZoomInButton_clicked()));
    shortcut = new QShortcut(QKeySequence("Ctrl+="),this);
    connect(shortcut, SIGNAL(activated()), this, SLOT(on_ZoomInButton_clicked()));

    shortcut = new QShortcut(QKeySequence(QKeySequence::ZoomOut),this);
    connect(shortcut, SIGNAL(activated()), this, SLOT(on_ZoomOutButton_clicked()));

    shortcut = new QShortcut(QKeySequence("Ctrl+0"),this);
    connect(shortcut, SIGNAL(activated()), this, SLOT(on_UnzoomButton_clicked()));


    shortcut = new QShortcut(QKeySequence("P"),this);
    connect(shortcut, SIGNAL(activated()), this, SLOT(Shortcut_P()));

    shortcut = new QShortcut(QKeySequence("I"),this);
    connect(shortcut, SIGNAL(activated()), this, SLOT(Shortcut_I()));

    shortcut = new QShortcut(QKeySequence("X"),this);
    connect(shortcut, SIGNAL(activated()), this, SLOT(Shortcut_X()));

    shortcut = new QShortcut(QKeySequence("Y"),this);
    connect(shortcut, SIGNAL(activated()), this, SLOT(Shortcut_Y()));

    shortcut = new QShortcut(QKeySequence("D"),this);
    connect(shortcut, SIGNAL(activated()), this, SLOT(Shortcut_D()));

    shortcut = new QShortcut(QKeySequence("Ctrl+C"),this);
    connect(shortcut, SIGNAL(activated()), this, SLOT(CopyImage()));
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

void MainWindow::Shortcut_D()
{
    DCheckBox->setChecked(!DCheckBox->isChecked());
}

void MainWindow::Shortcut_P()
{
        pseudocolorCheckBox->setChecked(!pseudocolorCheckBox->isChecked());
}

void MainWindow::Shortcut_I()
{
        invertedCheckBox->setChecked(!invertedCheckBox->isChecked());
}
