#include "easyfg.h"


void MainWindow::on_hideSidebarButton_clicked()
{
    if(hideSidebarButton->isChecked())
        hideSidebarButton->setArrowType(Qt::LeftArrow);
    else
        hideSidebarButton->setArrowType(Qt::RightArrow);
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


void MainWindow::on_ZoomOutButton_clicked(){
    if(zoom == -10)
        return;

    graphicsView->scale(pow(2, -0.5*zoom), pow(2, -0.5*zoom)); // unzoom
    zoom--;
    graphicsView->scale(pow(2, 0.5*zoom), pow(2, 0.5*zoom));   // zoom
    UpdateStatus();
    UpdateVisibility();
}


void MainWindow::on_ZoomInButton_clicked(){
    if(zoom == 10)
        return;

    graphicsView->scale(pow(2, -0.5*zoom), pow(2, -0.5*zoom)); // unzoom
    zoom++;
    graphicsView->scale(pow(2, 0.5*zoom), pow(2, 0.5*zoom));   // zoom
    UpdateStatus();
    UpdateVisibility();
}


void MainWindow::on_UnzoomButton_clicked(){
    if(zoom == 0)
        return;

    graphicsView->scale(pow(2,-0.5*zoom), pow(2,-0.5*zoom)); // unzoom
    zoom = 0;
    UpdateStatus();
    UpdateVisibility();
}


void MainWindow::on_referenceButton_clicked()
{
    if(!QFile::exists(reffile))
        reffile = datafile;
    QFileDialog dialog(this, "Load reference file", reffile, "All supported (*.asc *.csv *.tiff *.tif *.sif *.raw);;ASCII (*.asc *.csv);;TIFF (*.tiff *.tif);;Andor SIF (*.sif);;Pyrocam RAW (*.raw)");
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setAcceptMode(QFileDialog::AcceptOpen);
    if(dialog.exec()){
        QStringList path = dialog.selectedFiles();
        LoadRef(path[0]);
    }
}


void MainWindow::on_currentButton_clicked()
{
    if(!QFile::exists(datafile))
        return;

    reffile = datafile;
    LoadRef(reffile);
}
