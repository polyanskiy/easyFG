#include "easyfg.h"


MainWindow::MainWindow( QWidget * parent) : QMainWindow(parent)
{
    setupUi(this);

    version = "2020-03-18";

    inimage = false;
    x1drag = false;
    x2drag = false;
    y1drag = false;
    y2drag = false;

    image = QImage();
    pixmap = scene.addPixmap(QPixmap());
    pixmap->setZValue(0);

    QPen pen;
    pen.setColor(QColor(255,255,0));
    pen.setStyle(Qt::DashLine);
    // limit lines
    x1line = scene.addLine(QLineF(), pen);
    x1line->setZValue(1);
    x2line = scene.addLine(QLineF(), pen);
    x2line->setZValue(1);
    y1line = scene.addLine(QLineF(), pen);
    y1line->setZValue(1);
    y2line = scene.addLine(QLineF(), pen);
    y2line->setZValue(1);

    pen.setColor(QColor(255,0,0));
    pen.setStyle(Qt::SolidLine);
    // projections, beam profile, centroid
    xprojection = scene.addPath(QPainterPath(), pen);
    xprojection->setZValue(2);
    yprojection = scene.addPath(QPainterPath(), pen);
    yprojection->setZValue(2);
    ellipse = scene.addEllipse(0,0,0,0, pen);
    ellipse->setZValue(2);
    centerAline = scene.addLine(QLineF(), pen);
    centerAline->setZValue(2);
    centerBline = scene.addLine(QLineF(), pen);
    centerBline->setZValue(2);

    QObject::connect(&scene, SIGNAL(mouseMoved()), this, SLOT(mouseMovedOnScene()));
    QObject::connect(&scene, SIGNAL(mousePressed()), this, SLOT(mousePressedOnScene()));
    QObject::connect(&scene, SIGNAL(mouseReleased()), this, SLOT(mouseReleasedOnScene()));
    QObject::connect(&scene, SIGNAL(mouseLeft()), this, SLOT(mouseLeftScene()));

    graphicsView->setScene(&scene);
    graphicsView->setContextMenuPolicy(Qt::CustomContextMenu);

    X1SpinBox->setRange(0, MAX_HEIGHT-1);
    X2SpinBox->setRange(0, MAX_HEIGHT-1);
    Y1SpinBox->setRange(0, MAX_WIDTH-1);
    Y2SpinBox->setRange(0, MAX_WIDTH-1);

    scaleLabel->setScaledContents(true);

    AllocateMemory();

    dataloaded = false;
    refloaded = false;
    RestoreSession();

    LoadRef(reffile);
    LoadData(datafile);

    // Scale image
    scale = QImage(20, 256, QImage::Format_Indexed8);
    SetColorTable();
    for(int i=0; i<20; i++)
	for(int j=0; j<=255; j++)
	    scale.setPixel(i, j, 255-j);
    scaleLabel->setPixmap(QPixmap::fromImage(scale));

    graphicsView->scale(pow(2,zoom/2), pow(2,zoom/2));

    InitializeShortcuts();
    UpdateVisibility();
}


MainWindow::~MainWindow()
{
    SaveSession();
    ClearMemory();
}
