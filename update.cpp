#include "easyfg.h"


void MainWindow::UpdateImage()
{
    if(!dataloaded)
	return;
    int i, j;
    int pixel;
    float offset = offsetSpinBox->value();
    float cutoff = cutoffSpinBox->value();

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


void MainWindow::UpdateRanges()
{
    if(!dataloaded)
        return;

    dataloaded = false; // avoid ui update due to ranges change

    X1SpinBox->setRange(0, dataheight-1);
    X2SpinBox->setRange(0, dataheight-1);
    Y1SpinBox->setRange(0, datawidth-1);
    Y2SpinBox->setRange(0, datawidth-1);

    x1line->setLine(0.5, X1SpinBox->value()+0.5, datawidth-0.5, X1SpinBox->value()+0.5);
    x2line->setLine(0.5, X2SpinBox->value()+0.5, datawidth-0.5, X2SpinBox->value()+0.5);
    y1line->setLine(Y1SpinBox->value()+0.5, 0.5, Y1SpinBox->value()+0.5, dataheight-0.5);
    y2line->setLine(Y2SpinBox->value()+0.5, 0.5, Y2SpinBox->value()+0.5, dataheight-0.5);

    switch(scaleComboBox->currentIndex()){
        case 0: // "Auto MAX"
            cutoffSpinBox->setValue( referenceComboBox->currentIndex() == 0 ? datamax : correctedmax );
            offsetSpinBox->setEnabled(true);
            cutoffSpinBox->setEnabled(false);
            FixOffsetButton->setEnabled(true);
            break;
        case 1: // "Manual"
            offsetSpinBox->setEnabled(true);
            cutoffSpinBox->setEnabled(true);
            FixOffsetButton->setEnabled(true);
            break;
        case 2: // "Auto MIN:MAX"
            offsetSpinBox->setValue( referenceComboBox->currentIndex() == 0 ? datamin : correctedmin );
            cutoffSpinBox->setValue( referenceComboBox->currentIndex() == 0 ? datamax : correctedmax );
            offsetSpinBox->setEnabled(false);
            cutoffSpinBox->setEnabled(false);
            FixOffsetButton->setEnabled(false);
            break;
        case 3: // "Auto MAX (bits)"
            if(datamax<=255)
                cutoffSpinBox->setValue(255);
            if(datamax>255 && datamax<=511)
                cutoffSpinBox->setValue(511);
            if(datamax>511 && datamax<=1023)
                cutoffSpinBox->setValue(1023);
            if(datamax>1023 && datamax<=2045)
                cutoffSpinBox->setValue(2045);
            if(datamax>2045 && datamax<=4095)
                cutoffSpinBox->setValue(4095);
            if(datamax>4095 && datamax<=8191)
                cutoffSpinBox->setValue(8191);
            if(datamax>8191 && datamax<=16383)
                cutoffSpinBox->setValue(16383);
            if(datamax>16383 && datamax<=32767)
                cutoffSpinBox->setValue(32767);
            if(datamax>32767)
                cutoffSpinBox->setValue(65535);
            offsetSpinBox->setEnabled(true);
            cutoffSpinBox->setEnabled(false);
            FixOffsetButton->setEnabled(true);
            break;
        case 4: // "7 bit"
            cutoffSpinBox->setValue(127);
            offsetSpinBox->setEnabled(true);
            cutoffSpinBox->setEnabled(false);
            FixOffsetButton->setEnabled(true);
            break;
        case 5: // "8 bit"
            cutoffSpinBox->setValue(255);
            offsetSpinBox->setEnabled(true);
            cutoffSpinBox->setEnabled(false);
            FixOffsetButton->setEnabled(true);
            break;
        case 6: // "9 bit"
            cutoffSpinBox->setValue(511);
            offsetSpinBox->setEnabled(true);
            cutoffSpinBox->setEnabled(false);
            FixOffsetButton->setEnabled(true);
            break;
        case 7: // "10 bit"
            cutoffSpinBox->setValue(1023);
            offsetSpinBox->setEnabled(true);
            cutoffSpinBox->setEnabled(false);
            FixOffsetButton->setEnabled(true);
            break;
        case 8: // "11 bit"
            cutoffSpinBox->setValue(2047);
            offsetSpinBox->setEnabled(true);
            cutoffSpinBox->setEnabled(false);
            FixOffsetButton->setEnabled(true);
            break;
        case 9: // "12 bit"
            cutoffSpinBox->setValue(4095);
            offsetSpinBox->setEnabled(true);
            cutoffSpinBox->setEnabled(false);
            FixOffsetButton->setEnabled(true);
            break;
        case 10: // "13 bit"
            cutoffSpinBox->setValue(8191);
            offsetSpinBox->setEnabled(true);
            cutoffSpinBox->setEnabled(false);
            FixOffsetButton->setEnabled(true);
        break;
        case 11: // "14 bit"
            cutoffSpinBox->setValue(16383);
            offsetSpinBox->setEnabled(true);
            cutoffSpinBox->setEnabled(false);
            FixOffsetButton->setEnabled(true);
            break;
        case 12: // "15 bit"
            cutoffSpinBox->setValue(32767);
            offsetSpinBox->setEnabled(true);
            cutoffSpinBox->setEnabled(false);
            FixOffsetButton->setEnabled(true);
            break;
        case 13: // "16 bit"
            cutoffSpinBox->setValue(65535);
            offsetSpinBox->setEnabled(true);
            cutoffSpinBox->setEnabled(false);
            FixOffsetButton->setEnabled(true);
            break;
    }

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
    x1line->setVisible(XCheckBox->isChecked() || DCheckBox->isChecked());
    x2line->setVisible(XCheckBox->isChecked() || DCheckBox->isChecked());
    y1line->setVisible(YCheckBox->isChecked() || DCheckBox->isChecked());
    y2line->setVisible(YCheckBox->isChecked() || DCheckBox->isChecked());

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
    xshiftSpinBox->setEnabled( xshiftLabel->isEnabled() );
    yshiftLabel->setEnabled( xshiftLabel->isEnabled() );
    yshiftSpinBox->setEnabled( xshiftLabel->isEnabled() );
    X1SpinBox->setEnabled( XCheckBox->isChecked()||DCheckBox->isChecked() );
    X2SpinBox->setEnabled( XCheckBox->isChecked()||DCheckBox->isChecked() );
    minMaxLabel_2->setEnabled( XCheckBox->isChecked()||DCheckBox->isChecked() );
    Y1SpinBox->setEnabled( YCheckBox->isChecked()||DCheckBox->isChecked() );
    Y2SpinBox->setEnabled( YCheckBox->isChecked()||DCheckBox->isChecked() );
    minMaxLabel_3->setEnabled( YCheckBox->isChecked()||DCheckBox->isChecked() );
    FixOffsetButton->setEnabled( (DCheckBox->isChecked() || (XCheckBox->isChecked()&&YCheckBox->isChecked())) && scaleComboBox->currentIndex()!=2);//disable if offset is automatic (auto min:max)
    FixRangesButton->setEnabled( DCheckBox->isChecked() );
}
