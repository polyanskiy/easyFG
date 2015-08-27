#include "easyfg.h"



void MainWindow::on_offsetSpinBox_valueChanged()
{
    if(!dataloaded)
	return;

    RedoAnalysis();
    UpdateImage();
    UpdateScene();
}


void MainWindow::on_cutoffSpinBox_valueChanged()
{
    if(!dataloaded)
	return;

    RedoAnalysis();
    UpdateImage();
    UpdateScene();
}


void MainWindow::on_scaleComboBox_currentIndexChanged()
{
    if(!dataloaded)
	return;

    UpdateRanges();
    RedoAnalysis();
    UpdateImage();
    UpdateScene();
}
