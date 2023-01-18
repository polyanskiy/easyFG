#include "easyfg.h"


void MainWindow::InitializeShortcuts()
{
    /*
     * SHORTCUTS SET UP IN GUI DESIGNER ARE NOT WORKING
     * IF CORREPONDING CONTROLS ARE HIDDEN
     * SET UP SHORTCUTS HERE!!!
    */
    QShortcut *shortcut;

    flag_fullscreen = false;
    shortcut = new QShortcut(QKeySequence::FullScreen,this);
    connect(shortcut, SIGNAL(activated()), this, SLOT(Shortcut_F11()));

    shortcut = new QShortcut(QKeySequence("F10"),this);
    connect(shortcut, SIGNAL(activated()), this, SLOT(on_hideSidebarButton_clicked()));

    shortcut = new QShortcut(QKeySequence::Cancel,this);
    connect(shortcut, SIGNAL(activated()), this, SLOT(Shortcut_ESC()));


    shortcut = new QShortcut(QKeySequence::ZoomIn,this);
    connect(shortcut, SIGNAL(activated()), this, SLOT(on_ZoomInButton_clicked()));
    shortcut = new QShortcut(QKeySequence("Ctrl+="),this);
    connect(shortcut, SIGNAL(activated()), this, SLOT(on_ZoomInButton_clicked()));

    shortcut = new QShortcut(QKeySequence::ZoomOut,this);
    connect(shortcut, SIGNAL(activated()), this, SLOT(on_ZoomOutButton_clicked()));

    shortcut = new QShortcut(QKeySequence::Open,this);
    connect(shortcut, SIGNAL(activated()), this, SLOT(on_openButton_clicked()));

    shortcut = new QShortcut(QKeySequence::Save,this);
    connect(shortcut, SIGNAL(activated()), this, SLOT(on_saveButton_clicked()));

    // next frame
    shortcut = new QShortcut(QKeySequence::Forward,this);
    connect(shortcut, SIGNAL(activated()), this, SLOT(on_forwardButton_clicked()));
    shortcut = new QShortcut(QKeySequence::MoveToNextChar,this);
    connect(shortcut, SIGNAL(activated()), this, SLOT(on_forwardButton_clicked()));

    // previouse frame
    shortcut = new QShortcut(QKeySequence::Back,this);
    connect(shortcut, SIGNAL(activated()), this, SLOT(on_backButton_clicked()));
    shortcut = new QShortcut(QKeySequence::MoveToPreviousChar,this);
    connect(shortcut, SIGNAL(activated()), this, SLOT(on_backButton_clicked()));

    shortcut = new QShortcut(QKeySequence("I"),this);
    connect(shortcut, SIGNAL(activated()), this, SLOT(Shortcut_I()));
    shortcut = new QShortcut(QKeySequence("P"),this);
    connect(shortcut, SIGNAL(activated()), this, SLOT(Shortcut_P()));
    shortcut = new QShortcut(QKeySequence("L"),this);
    connect(shortcut, SIGNAL(activated()), this, SLOT(Shortcut_L()));

    shortcut = new QShortcut(QKeySequence("H"),this);
    connect(shortcut, SIGNAL(activated()), this, SLOT(Shortcut_H()));
    shortcut = new QShortcut(QKeySequence("V"),this);
    connect(shortcut, SIGNAL(activated()), this, SLOT(Shortcut_V()));

    shortcut = new QShortcut(QKeySequence("X"),this);
    connect(shortcut, SIGNAL(activated()), this, SLOT(Shortcut_X()));
    shortcut = new QShortcut(QKeySequence("Y"),this);
    connect(shortcut, SIGNAL(activated()), this, SLOT(Shortcut_Y()));
    shortcut = new QShortcut(QKeySequence("R"),this);
    connect(shortcut, SIGNAL(activated()), this, SLOT(Shortcut_R()));
    shortcut = new QShortcut(QKeySequence("D"),this);
    connect(shortcut, SIGNAL(activated()), this, SLOT(Shortcut_D()));
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


void MainWindow::Shortcut_I()
{
    invertedCheckBox->toggle();
}

void MainWindow::Shortcut_P()
{
    pseudocolorCheckBox->toggle();
}

void MainWindow::Shortcut_L()
{
    logarithmicCheckBox->toggle();
}

void MainWindow::Shortcut_H()
{
    HCheckBox->toggle();
}

void MainWindow::Shortcut_V()
{
    VCheckBox->toggle();
}

void MainWindow::Shortcut_X()
{
    XCheckBox->toggle();
}

void MainWindow::Shortcut_Y()
{
    YCheckBox->toggle();
}

void MainWindow::Shortcut_R()
{
    RCheckBox->toggle();
}

void MainWindow::Shortcut_D()
{
    DCheckBox->toggle();
}
