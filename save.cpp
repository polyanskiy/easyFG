#include "easyfg.h"


void MainWindow::on_saveButton_clicked()
{
    QFileInfo datafileinfo(datafile);
    QFileInfo savefileinfo(savefile);

    QString filter = "ASCII (*.asc)";
    if(savefileinfo.suffix() == "png")
        filter = "PNG (*.png)";
    if(savefileinfo.suffix() == "bmp")
        filter = "BMP (*.bmp)";
    if(savefileinfo.suffix() == "jpg")
        filter = "JPG (*.jpg)";

    QFileInfo fi;
    if(QFile::exists(savefile))
        fi.setFile(savefileinfo.dir(), datafileinfo.baseName());
    else
        fi.setFile(datafileinfo.dir(), datafileinfo.baseName());

    /*#ifdef Q_OS_X11
    QFileDialog dialog(this, "Save", fi.absoluteFilePath(), "ASCII (*.asc);;PNG (*.png);;BMP (*.bmp);;JPG (*.jpg)");
    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    dialog.selectFilter(filter);
    if(dialog.exec())
    {
        QStringList path = dialog.selectedFiles();
        savefileinfo.setFile(path[0]);
        if(dialog.selectedFilter() == "ASCII (*.asc)")
            savefileinfo.setFile(savefileinfo.dir(), savefileinfo.baseName()+".asc");
        if(dialog.selectedFilter() == "PNG (*.png)")
            savefileinfo.setFile(savefileinfo.dir(), savefileinfo.baseName()+".png");
        if(dialog.selectedFilter() == "BMP (*.bmp)")
            savefileinfo.setFile(savefileinfo.dir(), savefileinfo.baseName()+".bmp");
        if(dialog.selectedFilter() == "JPG (*.jpg)")
            savefileinfo.setFile(savefileinfo.dir(), savefileinfo.baseName()+".jpg");
        savefile = savefileinfo.absoluteFilePath();
        if(savefileinfo.suffix() == "asc"){

        }
        else
            image.save(savefile);
    }
    #else*/
    QString fileName = QFileDialog::getSaveFileName(this, "Save", fi.absoluteFilePath(), "ASCII (*.asc);;PNG (*.png);;BMP (*.bmp);;JPG (*.jpg)", &filter);
    if(fileName != QString()){
        savefile = fileName;
        savefileinfo = QFileInfo(savefile);
        if(savefileinfo.suffix() == "asc"){
            if(referenceComboBox->currentIndex()>0 && refloaded)
                SaveAscii(savefile, CorrectedArray);
            else
                SaveAscii(savefile, DataArray);
        }
        else{
            QImage img(scene.sceneRect().size().toSize()*pow(2.0,zoom/2.0), QImage::Format_ARGB32);
            img.fill(0);
            QPainter painter(&img);
            scene.render(&painter);
            img.save(savefile);
        }
    }
    //#endif
}


void MainWindow::SaveAscii(QString filename, int **Array)
{
    QFile file;
    file.setFileName(filename);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream stream(&file);

    for(int i=0; i<dataheight; i++){
        for(int j=0; j<datawidth; j++){
            stream << Array[j][i];//-(int)round(offsetSpinBox->value());
            if(j<datawidth-1)
                stream<<",";
        }
        if(i<dataheight-1)
            stream<<"\n";
    }

    file.close();
}
