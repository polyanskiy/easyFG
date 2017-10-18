#ifndef EASYFG_H
#define EASYFG_H

#include <QMainWindow>
#include <QShortcut>
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
#include <math.h>
#include "tiffio.h"
#include "hdf5.h"
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
    QGraphicsLineItem *x1line, *x2line, *y1line, *y2line, *centerAline, *centerBline;
    QGraphicsEllipseItem *ellipse;
    QGraphicsPathItem *xprojection, *yprojection;
    QString reffile, savefile;
    bool flag_fullscreen;
    int **DataArray, **RefArray, **CorrectedArray;
    float *X, *Y;
    int datawidth, dataheight, refwidth, refheight;
    int datamin, datamax, correctedmin, correctedmax;
    float centroidx, centroidy, sigmax, sigmay;
    bool dataloaded, refloaded;
    float refaverage;
    bool inimage, x1drag, x2drag, y1drag, y2drag;
    int zoom;

    void AllocateMemory(), ClearMemory();
    void SaveSession(), RestoreSession();
    void InitializeShortcuts();
    void SetColorTable();
    void LoadData(QString);
    void LoadRef(QString);
    void LoadAscii(QString, int**, int*, int*);
    void LoadSif(QString, int**, int*, int*);
    void LoadTiff(QString, int**, int*, int*);
    void LoadRaw(QString, int**, int*, int*);
    void LoadBgdata(QString, int**, int*, int*);
    void SaveAscii(QString, int**);
    void CalculateCorrectedArray();
    void CalculateX(), CalculateY(), CalculateBeam();
    void RedoAnalysis();
    void UpdateImage(), UpdateScene(), UpdateStatus(), UpdateVisibility(), UpdateRanges();

private slots:
    void Shortcut_F11();
    void Shortcut_ESC();
    void Shortcut_P();
    void Shortcut_I();
    void Shortcut_X();
    void Shortcut_Y();
    void Shortcut_CtrlA();
    void Shortcut_B();
    void Shortcut_equal();
    void Shortcut_substract();
    void Shortcut_divide();
    void Shortcut_R();
    void Shortcut_A();
    void Shortcut_C();
    void Shortcut_M();
    void Shortcut_0();
    void Shortcut_1();
    void Shortcut_2();
    void Shortcut_3();
    void Shortcut_4();
    void Shortcut_5();
    void Shortcut_6();
    void Shortcut_7();
    void Shortcut_8();
    void Shortcut_9();
    void Shortcut_o();
    void on_openButton_clicked();
    void on_backButton_clicked();
    void on_forwardButton_clicked();
    void on_saveButton_clicked();
    void on_scaleComboBox_currentIndexChanged();
    void on_offsetSpinBox_valueChanged();
    void on_cutoffSpinBox_valueChanged();
    void on_referenceButton_clicked();
    void on_currentButton_clicked();
    void on_referenceComboBox_currentIndexChanged();
    void on_pseudocolorCheckBox_stateChanged();
    void on_invertedCheckBox_stateChanged();
    void on_ZoomInButton_clicked();
    void on_ZoomOutButton_clicked();
    void on_UnzoomButton_clicked();
    void on_XCheckBox_stateChanged();
    void on_X1SpinBox_valueChanged();
    void on_X2SpinBox_valueChanged();
    void on_XCopyButton_clicked();
    void on_YCopyButton_clicked();
    void on_YCheckBox_stateChanged();
    void on_Y1SpinBox_valueChanged();
    void on_Y2SpinBox_valueChanged();
    void on_xshiftSpinBox_valueChanged();
    void on_yshiftSpinBox_valueChanged();
    void on_beamCheckBox_stateChanged();
    void on_FixRangesButton_clicked();
    void on_FixOffsetButton_clicked();
    void on_graphicsView_customContextMenuRequested();
    void on_scaleLabel_customContextMenuRequested();
    void on_hideSidebarButton_clicked();
    void mouseMovedOnScene();
    void mousePressedOnScene();
    void mouseReleasedOnScene();
    void mouseLeftScene();
    void CopyFigure();
};



#endif // EASYFG_H
