#include "easyfg.h"



void MainWindow::on_minSpinBox_valueChanged()
{
    if(!dataloaded)
        return;

    minComboBox->setCurrentIndex(1); // set to manual
    RedoAnalysis();
    UpdateImage();
    UpdateScene();
    UpdateStatus();
}


void MainWindow::on_maxSpinBox_valueChanged()
{
    if(!dataloaded)
        return;

    maxComboBox->setCurrentIndex(1); // set to manual
    RedoAnalysis();
    UpdateImage();
    UpdateScene();
}


void MainWindow::on_minComboBox_currentIndexChanged()
{
    if(!dataloaded)
        return;

    UpdateScale();
    RedoAnalysis();
    UpdateImage();
    UpdateScene();
    UpdateStatus();
}


void MainWindow::on_maxComboBox_currentIndexChanged()
{
    if(!dataloaded)
        return;

    UpdateScale();
    RedoAnalysis();
    UpdateImage();
    UpdateScene();
    UpdateStatus();
}


void MainWindow::CalculateBackground()
{
    if(!dataloaded)
        return;

    int i,j;
    int count=0;
    float offset=0;

    int ymin = (H1SpinBox->value() < H2SpinBox->value()) ? H1SpinBox->value() : H2SpinBox->value();
    int ymax = (H1SpinBox->value() < H2SpinBox->value()) ? H2SpinBox->value() : H1SpinBox->value();
    int xmin = (V1SpinBox->value() < V2SpinBox->value()) ? V1SpinBox->value() : V2SpinBox->value();
    int xmax = (V1SpinBox->value() < V2SpinBox->value()) ? V2SpinBox->value() : V1SpinBox->value();

    for(i=0; i<datawidth; i++){
        for(j=0; j<dataheight; j++) {
            if(i<xmin||i>xmax||j<ymin||j>ymax){
                count++;
                if(referenceComboBox->currentIndex()>0 && refloaded)
                    offset += CorrectedArray[i][j];
                else
                    offset += DataArray[i][j];
            }
        }
    }
    if(count)
        offset /= count;

    minSpinBox->blockSignals(true);
    minSpinBox->setValue(offset);
    minSpinBox->blockSignals(false);
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
