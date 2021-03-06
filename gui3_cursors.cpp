#include "easyfg.h"


void MainWindow::on_HCheckBox_stateChanged()
{
    if(!dataloaded)
        return;

    if(HCheckBox->isChecked()){
        if(cursorh1>dataheight-1)
            cursorh1 = dataheight-1;
        if(cursorh2>dataheight-1)
            cursorh2 = dataheight-1;
        H1SpinBox->setValue(cursorh1);
        H2SpinBox->setValue(cursorh2);
        h1line->setLine(0.5, cursorh1+0.5, datawidth-0.5, cursorh1+0.5);
        h2line->setLine(0.5, cursorh2+0.5, datawidth-0.5, cursorh2+0.5);
    }
    else{
        H1SpinBox->setValue(0);
        H2SpinBox->setValue(dataheight-1);
    }

    if(XCheckBox->isChecked())
        CalculateX();
    if(RCheckBox->isChecked())
        CalculateR();
    if(DCheckBox->isChecked())
        CalculateBeam();

    UpdateVisibility();
    UpdateScene();
    UpdateStatus();
}


void MainWindow::on_VCheckBox_stateChanged()
{
    if(!dataloaded)
        return;

    if(VCheckBox->isChecked() ) {
        if(cursorv1>datawidth-1)
            cursorv1 = datawidth-1;
        if(cursorv2>datawidth-1)
            cursorv2 = datawidth-1;
        V1SpinBox->setValue(cursorv1);
        V2SpinBox->setValue(cursorv2);
        v1line->setLine(cursorv1+0.5, 0.5, cursorv1+0.5, dataheight-0.5);
        v2line->setLine(cursorv2+0.5, 0.5, cursorv2+0.5, dataheight-0.5);
    }
    else{
        V1SpinBox->setValue(0);
        V2SpinBox->setValue(datawidth-1);
    }

    if(YCheckBox->isChecked())
        CalculateY();
    if(RCheckBox->isChecked())
        CalculateR();
    if(DCheckBox->isChecked())
        CalculateBeam();

    UpdateVisibility();
    UpdateScene();
    UpdateStatus();
}


void MainWindow::on_H1SpinBox_valueChanged()
{
    if(!dataloaded )
        return;

    if(HCheckBox->isChecked()){
        cursorh1 = H1SpinBox->value();
        h1line->setLine(0.5, cursorh1+0.5, datawidth-0.5, cursorh1+0.5);
    }

    if(XCheckBox->isChecked())
        CalculateX();
    if(RCheckBox->isChecked())
        CalculateR();
    if(DCheckBox->isChecked())
        CalculateBeam();
    if(minComboBox->currentIndex()==2) // background = "Average outside cursors"
        CalculateBackground();

    deltaHLabel->setText("Δ = " + QString::number(cursorh2-cursorh1));

    UpdateScene();
    UpdateStatus();
}


void MainWindow::on_H2SpinBox_valueChanged()
{
    if(!dataloaded )
        return;

    if(HCheckBox->isChecked()){
        cursorh2 = H2SpinBox->value();
        h2line->setLine(0.5, cursorh2+0.5, datawidth-0.5, cursorh2+0.5);
    }

    if(XCheckBox->isChecked())
        CalculateX();
    if(RCheckBox->isChecked())
        CalculateR();
    if(DCheckBox->isChecked())
        CalculateBeam();
    if(minComboBox->currentIndex()==2) // background = "Average outside cursors"
        CalculateBackground();

    deltaHLabel->setText("Δ = " + QString::number(cursorh2-cursorh1));

    UpdateScene();
    UpdateStatus();
}


void MainWindow::on_V1SpinBox_valueChanged()
{
    if(!dataloaded )
        return;

    if(VCheckBox->isChecked()){
        cursorv1 = V1SpinBox->value();
        v1line->setLine(cursorv1+0.5, 0.5, cursorv1+0.5, dataheight-0.5);
    }

    if(YCheckBox->isChecked())
        CalculateY();
    if(RCheckBox->isChecked())
        CalculateR();
    if(DCheckBox->isChecked())
        CalculateBeam();

    if(minComboBox->currentIndex()==2) // background = "Average outside cursors"
        CalculateBackground();

    deltaVLabel->setText("Δ = " + QString::number(cursorv2-cursorv1));

    UpdateScene();
    UpdateStatus();
}


void MainWindow::on_V2SpinBox_valueChanged()
{
    if(!dataloaded )
        return;

    if(VCheckBox->isChecked()){
        cursorv2 = V2SpinBox->value();
        v2line->setLine(cursorv2+0.5, 0.5, cursorv2+0.5, dataheight-0.5);
    }

    if(YCheckBox->isChecked())
        CalculateY();
    if(RCheckBox->isChecked())
        CalculateR();
    if(DCheckBox->isChecked())
        CalculateBeam();

    if(minComboBox->currentIndex()==2) // background = "Average outside cursors"
        CalculateBackground();

    deltaVLabel->setText("Δ = " + QString::number(cursorv2-cursorv1));

    UpdateScene();
    UpdateStatus();
}


void MainWindow::on_ThreeD4sigmaButton_clicked()
{
    if(!dataloaded)
        return;

    cursorh1 = round(centroidy-sigmay*6);
    cursorh2 = round(centroidy+sigmay*6);
    cursorv1 = round(centroidx-sigmax*6);
    cursorv2 = round(centroidx+sigmax*6);
    HCheckBox->setChecked(true);
    VCheckBox->setChecked(true);
    H1SpinBox->setValue(cursorh1);
    H2SpinBox->setValue(cursorh2);
    V1SpinBox->setValue(cursorv1);
    V2SpinBox->setValue(cursorv2);


    UpdateCursors();

    CalculateBeam();
    if(XCheckBox->isChecked())
        CalculateX();
    if(YCheckBox->isChecked())
        CalculateY();
    if(RCheckBox->isChecked())
        CalculateR();

    UpdateScene();
    UpdateStatus();
}

void MainWindow::on_D4sigmaButton_clicked()
{
    if(!dataloaded)
        return;

    cursorh1 = round(centroidy-sigmay*2);
    cursorh2 = round(centroidy+sigmay*2);
    cursorv1 = round(centroidx-sigmax*2);
    cursorv2 = round(centroidx+sigmax*2);
    HCheckBox->setChecked(true);
    VCheckBox->setChecked(true);
    H1SpinBox->setValue(cursorh1);
    H2SpinBox->setValue(cursorh2);
    V1SpinBox->setValue(cursorv1);
    V2SpinBox->setValue(cursorv2);

    UpdateCursors();

    CalculateBeam();
    if(XCheckBox->isChecked())
        CalculateX();
    if(YCheckBox->isChecked())
        CalculateY();
    if(RCheckBox->isChecked())
        CalculateR();

    UpdateScene();
    UpdateStatus();
}


void MainWindow::UpdateCursors()
{
    if(!dataloaded)
        return;

    dataloaded = false; // don't trigger analysis before everything is updated (can crash otherwise)
    H1SpinBox->setRange(0, dataheight-1);
    H2SpinBox->setRange(0, dataheight-1);
    V1SpinBox->setRange(0, datawidth-1);
    V2SpinBox->setRange(0, datawidth-1);
    dataloaded = true;

    if(HCheckBox->isChecked()){
        cursorh1 = H1SpinBox->value();
        cursorh2 = H2SpinBox->value();
        h1line->setLine(0.5, cursorh1+0.5, datawidth-0.5, cursorh1+0.5);
        h2line->setLine(0.5, cursorh2+0.5, datawidth-0.5, cursorh2+0.5);
        deltaHLabel->setText("Δ = " + QString::number(cursorh2-cursorh1));
    }
    if(VCheckBox->isChecked()){
        cursorv1 = V1SpinBox->value();
        cursorv2 = V2SpinBox->value();
        v1line->setLine(cursorv1+0.5, 0.5, cursorv1+0.5, dataheight-0.5);
        v2line->setLine(cursorv2+0.5, 0.5, cursorv2+0.5, dataheight-0.5);
        deltaVLabel->setText("Δ = " + QString::number(cursorv2-cursorv1));
    }
}
