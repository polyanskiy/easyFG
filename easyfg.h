#ifndef EASYFG_H
#define EASYFG_H

#include <QMainWindow>
#include <QShortcut>
#include <QWheelEvent>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QMenu>
#include <QClipboard>
#include <QSettings>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QMessageBox>
#include <QImageReader>
#include <math.h>
#include "hdf5_hl.h"
#include "ui_mainwindow.h"

#define MAX_WIDTH 2048
#define MAX_HEIGHT 2048


class MyScene : public QGraphicsScene
{
    Q_OBJECT
    public:
        MyScene();

	int x, y;

    signals:
        void mouseMoved();
        void mousePressed();
        void mouseReleased();
        void mouseLeft();

    private:
        bool event(QEvent*);
};

class MainWindow : public QMainWindow, public Ui::MainWindowClass
{
    Q_OBJECT

    public:
        MainWindow(QWidget *parent = 0);
        ~MainWindow();
        QString datafile;

    private:
        QString version;
        MyScene scene;
        QImage image, scale;
        QGraphicsPixmapItem *pixmap;
        QGraphicsLineItem *h1line, *h2line, *v1line, *v2line, *centerAline, *centerBline;
        QGraphicsEllipseItem *ellipse;
        QGraphicsPathItem *xprojection, *yprojection;
        QString reffile, savefile;
        bool flag_fullscreen;
        int **DataArray, **RefArray, **CorrectedArray;
        float *X, *Y;
        int datawidth, dataheight, refwidth, refheight;
        int datamin, datamax, correctedmin, correctedmax;
        int cursorh1, cursorh2, cursorv1, cursorv2;
        float centroidx, centroidy, sigmax, sigmay;
        bool dataloaded, refloaded;
        float refaverage;
        bool inimage, h1drag, h2drag, v1drag, v2drag;
        int zoom;

        // session.cpp
        void SaveSession(), RestoreSession();
        // shortcuts.cpp
        void InitializeShortcuts();
        // memory.cpp
        void AllocateMemory(), ClearMemory();
        // load.cpp
        void LoadData(QString);
        void LoadRef(QString);
        void LoadAscii(QString, int**, int*, int*);
        void LoadSif(QString, int**, int*, int*);
        void LoadTiff(QString, int**, int*, int*);
        void LoadRaw(QString, int**, int*, int*);
        void LoadBgdata(QString, int**, int*, int*);
        // save.cpp
        void SaveAscii(QString, int**);
        void CalculateCorrectedArray();
        // update.cpp
        void UpdateImage(), UpdateScale(), UpdateScene(), UpdateStatus(), UpdateVisibility(), UpdateRanges();
        // clipboard.cpp
        void CopyImage(), CopyX(), CopyY(), CopyD();
        // image.cpp
        void SetColorTable();
        // scale.cpp
        void CalculateBackground();
        // analysis.cpp
        void CalculateX(), CalculateY(), CalculateR(), CalculateBeam();
        void RedoAnalysis();

    private slots:
        // mainwindow.cpp
        void on_openButton_clicked();
        void on_backButton_clicked();
        void on_forwardButton_clicked();
        void on_saveButton_clicked();
        void on_hideSidebarButton_clicked();

        // image.cpp
        void on_pseudocolorCheckBox_stateChanged();
        void on_invertedCheckBox_stateChanged();
        void on_ZoomInButton_clicked();
        void on_ZoomOutButton_clicked();
        void on_UnzoomButton_clicked();

        // scale.cpp
        void on_minSpinBox_valueChanged();
        void on_minComboBox_currentIndexChanged();
        void on_maxSpinBox_valueChanged();
        void on_maxComboBox_currentIndexChanged();

        // cursors.cpp
        void on_HCheckBox_stateChanged();
        void on_H1SpinBox_valueChanged();
        void on_H2SpinBox_valueChanged();
        void on_VCheckBox_stateChanged();
        void on_V1SpinBox_valueChanged();
        void on_V2SpinBox_valueChanged();
        void on_CursorsButton_clicked();

        // analysis.cpp
        void on_XCheckBox_stateChanged();
        void on_YCheckBox_stateChanged();
        void on_DCheckBox_stateChanged();
        void on_RCheckBox_stateChanged();

        // reference.cpp
        void on_referenceButton_clicked();
        void on_currentButton_clicked();
        void on_referenceComboBox_currentIndexChanged();
        void on_xshiftSpinBox_valueChanged();
        void on_yshiftSpinBox_valueChanged();

        // scene.cpp
        void mouseMovedOnScene();
        void mousePressedOnScene();
        void mouseReleasedOnScene();
        void mouseLeftScene();

        // shortcuts.cpp
        void Shortcut_F11();
        void Shortcut_ESC();

        // clipboard.cpp
        void on_graphicsView_customContextMenuRequested();
        void on_scaleLabel_customContextMenuRequested();
};



#endif // EASYFG_H
