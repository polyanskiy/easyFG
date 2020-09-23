#include "easyfg.h"


MainWindow::MainWindow( QWidget * parent) : QMainWindow(parent)
{
    setupUi(this);

    version = "2020-09-23";

    inimage = false;
    h1drag = false;
    h2drag = false;
    v1drag = false;
    v2drag = false;

    image = QImage();
    pixmap = scene.addPixmap(QPixmap());
    pixmap->setZValue(0);

    QPen pen;
    pen.setColor(QColor(255,255,0));
    pen.setStyle(Qt::DashLine);
    // limit lines
    h1line = scene.addLine(QLineF(), pen);
    h1line->setZValue(1);
    h2line = scene.addLine(QLineF(), pen);
    h2line->setZValue(1);
    v1line = scene.addLine(QLineF(), pen);
    v1line->setZValue(1);
    v2line = scene.addLine(QLineF(), pen);
    v2line->setZValue(1);

    pen.setColor(QColor(255,0,0));
    pen.setStyle(Qt::SolidLine);
    // projections, beam profile, centroid
    xprojection = scene.addPath(QPainterPath(), pen);
    xprojection->setZValue(2);
    yprojection = scene.addPath(QPainterPath(), pen);
    yprojection->setZValue(2);
    rprojection1 = scene.addPath(QPainterPath(), pen);
    rprojection1->setZValue(2);
    ellipse = scene.addEllipse(0,0,0,0, pen);
    ellipse->setZValue(2);
    centerAline = scene.addLine(QLineF(), pen);
    centerAline->setZValue(2);
    centerBline = scene.addLine(QLineF(), pen);
    centerBline->setZValue(2);

    pen.setColor(QColor(0,0,0));
    pen.setStyle(Qt::DashLine);
    rprojection2 = scene.addPath(QPainterPath(), pen);
    rprojection2->setZValue(2);

    QObject::connect(&scene, SIGNAL(mouseMoved()), this, SLOT(mouseMovedOnScene()));
    QObject::connect(&scene, SIGNAL(mousePressed()), this, SLOT(mousePressedOnScene()));
    QObject::connect(&scene, SIGNAL(mouseReleased()), this, SLOT(mouseReleasedOnScene()));
    QObject::connect(&scene, SIGNAL(mouseLeft()), this, SLOT(mouseLeftScene()));

    graphicsView->setScene(&scene);
    graphicsView->setContextMenuPolicy(Qt::CustomContextMenu);

    H1SpinBox->setRange(0, MAX_HEIGHT-1);
    H2SpinBox->setRange(0, MAX_HEIGHT-1);
    V1SpinBox->setRange(0, MAX_WIDTH-1);
    V2SpinBox->setRange(0, MAX_WIDTH-1);

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


 void MainWindow::on_openButton_clicked()
{
    QFileInfo fi(datafile);
    QString fileName = QFileDialog::getOpenFileName(this, "Open data file", fi.path(), "All supported (*.asc *.csv *.tiff *.tif *.sif *.raw *.bgdata);;ASCII (*.asc *.csv);;TIFF (*.tiff *.tif);;Andor SIF (*.sif);;Pyrocam III RAW (*.raw);;Pyrocam IV bgData (*.bgdata)");
    if(fileName != QString())
        LoadData(fileName);
}


void MainWindow::on_forwardButton_clicked()
{
    QFileInfo fileinfo(datafile);
    QDir dir(fileinfo.dir());
    QStringList extensions = (QStringList() << "*.asc" << "*.csv" << "*.tiff" << "*.tif" << "*.sif" << "*.raw" << "*.bgdata");
    QStringList filelist = dir.entryList(extensions, QDir::Files, QDir::Name);
    int index = filelist.indexOf(fileinfo.fileName());
    if(index+1 < filelist.count()){
        fileinfo.setFile(dir, filelist.value(index+1));
    LoadData(fileinfo.absoluteFilePath());
    }
}


void MainWindow::on_backButton_clicked()
{
    QFileInfo fileinfo(datafile);
    QDir dir(fileinfo.dir());
    QStringList extensions = (QStringList() << "*.asc" << "*.csv" << "*.tiff" << "*.tif" << "*.sif" << "*.raw" << "*.bgdata");
    QStringList filelist = dir.entryList(extensions, QDir::Files, QDir::Name);
    int index = filelist.indexOf(fileinfo.fileName());
    if(index-1 >= 0){
        fileinfo.setFile(dir, filelist.value(index-1));
        LoadData(fileinfo.absoluteFilePath());
    }
}


void MainWindow::on_hideSidebarButton_clicked()
{
    if(hideSidebarButton->isChecked())
        hideSidebarButton->setArrowType(Qt::LeftArrow);
    else
        hideSidebarButton->setArrowType(Qt::RightArrow);
}


void MainWindow::UpdateStatus()
{
    // WINDOW TITLE
    if(dataloaded)
        setWindowTitle("easyFG v." + version +":  " + datafile);
    else
        setWindowTitle("easyFG v." + version);

    // STATUIS BAR
    QString status_string = QString();
    QTextStream status(&status_string);
    if(dataloaded){
        status << datawidth << "x" << dataheight;
        if(zoom)
            status << "     ZOOM: " << QString::number(pow(2.0,zoom/2.0),'g',3);
        if(inimage){
            status << "     POS: " << scene.x << ";" << scene.y;
            status << "     VAL: ";
            if(refloaded && referenceComboBox->currentIndex()>0)
                status << CorrectedArray[scene.x][scene.y];
            else
                status << DataArray[scene.x][scene.y];
        }
    }

    if(dataloaded && (DCheckBox->isChecked()||RCheckBox->isChecked())){
        status << "     CENTR: "
               << QString::number(centroidx,'f',1) << "x" << QString::number(centroidy,'f',1);
    }

    if(dataloaded && DCheckBox->isChecked()){
        status << "     DIA: "
               << QString::number(sigmax*4,'f',1) << "x" << QString::number(sigmay*4,'f',1);
    }

    if(refloaded && referenceComboBox->currentIndex()>0)
        status << "     REF: " << reffile;

    myStatusBar->showMessage(status_string);
}


void MainWindow::UpdateVisibility()
{
    h1line->setVisible(HCheckBox->isChecked()&&dataloaded);
    h2line->setVisible(HCheckBox->isChecked()&&dataloaded);
    v1line->setVisible(VCheckBox->isChecked()&&dataloaded);
    v2line->setVisible(VCheckBox->isChecked()&&dataloaded);

    deltaHLabel->setVisible(HCheckBox->isChecked());
    deltaVLabel->setVisible(VCheckBox->isChecked());

    xprojection->setVisible(XCheckBox->isChecked());
    yprojection->setVisible(YCheckBox->isChecked());
    rprojection1->setVisible(RCheckBox->isChecked());
    rprojection2->setVisible(RCheckBox->isChecked());
    ellipse->setVisible(DCheckBox->isChecked());
    centerAline->setVisible(DCheckBox->isChecked() || RCheckBox->isChecked());
    centerBline->setVisible(DCheckBox->isChecked() || RCheckBox->isChecked());

    imageGroupBox->setEnabled(dataloaded);
    scaleGroupBox->setEnabled(dataloaded);
    cursorsGroupBox->setEnabled(dataloaded);
    analysisGroupBox->setEnabled(dataloaded);
    referenceGroupBox->setEnabled(dataloaded);

    backButton->setEnabled(dataloaded);
    forwardButton->setEnabled(dataloaded);
    saveButton->setEnabled(dataloaded);

    ZoomInButton->setEnabled(zoom < 10);
    ZoomOutButton->setEnabled(zoom > -10);
    UnzoomButton->setEnabled(zoom != 0);

    if(!(dataloaded && refloaded))
        referenceComboBox->setCurrentIndex(0); // reference OFF

    referenceComboBox->setEnabled( refloaded );
    xshiftLabel->setEnabled (referenceComboBox->isEnabled() && referenceComboBox->currentIndex()>0 );
    xshiftSpinBox->setEnabled(xshiftLabel->isEnabled());
    yshiftLabel->setEnabled(xshiftLabel->isEnabled());
    yshiftSpinBox->setEnabled(xshiftLabel->isEnabled());
    H1SpinBox->setEnabled(HCheckBox->isChecked());
    H2SpinBox->setEnabled(HCheckBox->isChecked());
    V1SpinBox->setEnabled(VCheckBox->isChecked());
    V2SpinBox->setEnabled(VCheckBox->isChecked());
    D4sigmaButton->setEnabled(DCheckBox->isChecked());
    ThreeD4sigmaButton->setEnabled(DCheckBox->isChecked());
}
