#include "easyfg.h"


void MainWindow::InitializeShortcuts()
{
    QShortcut *shortcut;

    flag_fullscreen = false;
    shortcut = new QShortcut(QKeySequence("F11"),this);
    connect(shortcut, SIGNAL(activated()), this, SLOT(Shortcut_F11()));

    shortcut = new QShortcut(QKeySequence("ESC"),this);
    connect(shortcut, SIGNAL(activated()), this, SLOT(Shortcut_ESC()));

    // setting two shortcuts for single button from GUI designer doesn't work: setting up here
    shortcut = new QShortcut(QKeySequence("Ctrl++"),this);
    connect(shortcut, SIGNAL(activated()), this, SLOT(on_ZoomInButton_clicked()));
    shortcut = new QShortcut(QKeySequence("Ctrl+="),this);
    connect(shortcut, SIGNAL(activated()), this, SLOT(on_ZoomInButton_clicked()));
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

