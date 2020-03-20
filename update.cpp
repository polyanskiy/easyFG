#include "easyfg.h"


void MainWindow::UpdateImage()
{
    if(!dataloaded)
	return;
    int i, j;
    int pixel;
    float offset = minSpinBox->value();
    float cutoff = maxSpinBox->value();

    image = QImage(datawidth, dataheight, QImage::Format_Indexed8);
    SetColorTable();

    for(i=0; i<datawidth; i++){
        for(j=0; j<dataheight; j++){
            if(referenceComboBox->currentIndex()>0 && refloaded)
                pixel = (int)((CorrectedArray[i][j]-offset)*255.0/(cutoff-offset)+0.5);
            else
                pixel = (int)((DataArray[i][j]-offset)*255.0/(cutoff-offset)+0.5);

            if(pixel>255)
                pixel = 255;
            if(pixel<0)
                pixel = 0;

            image.setPixel(i, j, pixel);
        }
    }
    pixmap->setPixmap(QPixmap::fromImage(image));
}


void MainWindow::UpdateScene()
{
    scene.setSceneRect(scene.itemsBoundingRect());
    scene.update(scene.sceneRect());
}


void MainWindow::UpdateScale()
{
    if(!dataloaded)
        return;

    minSpinBox->blockSignals(true);
    maxSpinBox->blockSignals(true);

    switch(minComboBox->currentIndex()){
        case 0: // "Auto"
            minSpinBox->setValue( referenceComboBox->currentIndex() == 0 ? datamin : correctedmin );
            break;
        case 1: // "Manual"
            break;
        case 2: // "Average outside cursors"
            CalculateBackground();
            break;
    }

    switch(maxComboBox->currentIndex()){
        case 0: // "Auto"
            maxSpinBox->setValue( referenceComboBox->currentIndex() == 0 ? datamax : correctedmax );
            break;
        case 1: // "Manual"
            break;
        case 2: // "Auto (bits)"
            if(datamax<=255)
                maxSpinBox->setValue(255);
            if(datamax>255 && datamax<=511)
                maxSpinBox->setValue(511);
            if(datamax>511 && datamax<=1023)
                maxSpinBox->setValue(1023);
            if(datamax>1023 && datamax<=2045)
                maxSpinBox->setValue(2045);
            if(datamax>2045 && datamax<=4095)
                maxSpinBox->setValue(4095);
            if(datamax>4095 && datamax<=8191)
                maxSpinBox->setValue(8191);
            if(datamax>8191 && datamax<=16383)
                maxSpinBox->setValue(16383);
            if(datamax>16383 && datamax<=32767)
                maxSpinBox->setValue(32767);
            if(datamax>32767)
                maxSpinBox->setValue(65535);
            break;
        case 3: // "7 bit"
            maxSpinBox->setValue(127);
            break;
        case 4: // "8 bit"
            maxSpinBox->setValue(255);
            break;
        case 5: // "9 bit"
            maxSpinBox->setValue(511);
            break;
        case 6: // "10 bit"
            maxSpinBox->setValue(1023);
            break;
        case 7: // "11 bit"
            maxSpinBox->setValue(2047);
            break;
        case 8: // "12 bit"
            maxSpinBox->setValue(4095);
            break;
        case 9: // "13 bit"
            maxSpinBox->setValue(8191);
        break;
        case 10: // "14 bit"
            maxSpinBox->setValue(16383);
            break;
        case 11: // "15 bit"
            maxSpinBox->setValue(32767);
            break;
        case 12: // "16 bit"
            maxSpinBox->setValue(65535);
            break;
    }

    minSpinBox->blockSignals(false);
    maxSpinBox->blockSignals(false);
}


void MainWindow::UpdateRanges()
{
    if(!dataloaded)
        return;

    dataloaded = false; // avoid ui update due to ranges change

    H1SpinBox->setRange(0, dataheight-1);
    H2SpinBox->setRange(0, dataheight-1);
    V1SpinBox->setRange(0, datawidth-1);
    V2SpinBox->setRange(0, datawidth-1);

    h1line->setLine(0.5, H1SpinBox->value()+0.5, datawidth-0.5, H1SpinBox->value()+0.5);
    h2line->setLine(0.5, H2SpinBox->value()+0.5, datawidth-0.5, H2SpinBox->value()+0.5);
    v1line->setLine(V1SpinBox->value()+0.5, 0.5, V1SpinBox->value()+0.5, dataheight-0.5);
    v2line->setLine(V2SpinBox->value()+0.5, 0.5, V2SpinBox->value()+0.5, dataheight-0.5);

    dataloaded = true;
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

    if(dataloaded && DCheckBox->isChecked()){
        status << "     CENTR: "
               << QString::number(centroidx,'f',1) << "x" << QString::number(centroidy,'f',1)
               << "     DIA: "
               << QString::number(sigmax*4,'f',1) << "x" << QString::number(sigmay*4,'f',1);
    }

    if(refloaded && referenceComboBox->currentIndex()>0)
        status << "     REF: " << reffile;

    myStatusBar->showMessage(status_string);
}


void MainWindow::UpdateVisibility()
{
    h1line->setVisible(HCheckBox->isChecked());
    h2line->setVisible(HCheckBox->isChecked());
    v1line->setVisible(VCheckBox->isChecked());
    v2line->setVisible(VCheckBox->isChecked());

    xprojection->setVisible(XCheckBox->isChecked());
    yprojection->setVisible(YCheckBox->isChecked());
    ellipse->setVisible(DCheckBox->isChecked());
    centerAline->setVisible(DCheckBox->isChecked());
    centerBline->setVisible(DCheckBox->isChecked());

    scaleGroupBox->setEnabled(dataloaded);
    colormapGroupBox->setEnabled(dataloaded);
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
    //FixOffsetButton->setEnabled( (DCheckBox->isChecked() || (XCheckBox->isChecked()&&YCheckBox->isChecked())) && scaleComboBox->currentIndex()!=2);//disable if offset is automatic (auto min:max)
    CursorsButton->setEnabled( DCheckBox->isChecked() );
}
