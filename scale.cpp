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
