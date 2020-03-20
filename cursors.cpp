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

    UpdateVisibility();
    UpdateScene();
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

    UpdateVisibility();
    UpdateScene();
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
    if(DCheckBox->isChecked()){
        CalculateBeam();
        UpdateStatus();
    }
    if(minComboBox->currentIndex()==2) // background = "Average outside cursors"
        CalculateBackground();

    UpdateScene();
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
    if(DCheckBox->isChecked()){
        CalculateBeam();
        UpdateStatus();
    }
    if(minComboBox->currentIndex()==2) // background = "Average outside cursors"
        CalculateBackground();

    UpdateScene();
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
    if(DCheckBox->isChecked()){
        CalculateBeam();
        UpdateStatus();
    }
    if(minComboBox->currentIndex()==2) // background = "Average outside cursors"
        CalculateBackground();

    UpdateScene();
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
    if(DCheckBox->isChecked()){
        CalculateBeam();
        UpdateStatus();
    }
    if(minComboBox->currentIndex()==2) // background = "Average outside cursors"
        CalculateBackground();

    UpdateScene();
}


void MainWindow::on_CursorsButton_clicked()
{
    if(!dataloaded)
        return;

    H1SpinBox->setValue(round(centroidy-sigmay*6));
    H2SpinBox->setValue(round(centroidy+sigmay*6));
    V1SpinBox->setValue(round(centroidx-sigmax*6));
    V2SpinBox->setValue(round(centroidx+sigmax*6));

    UpdateRanges();

    CalculateBeam();
    if(XCheckBox->isChecked())
        CalculateX();
    if(YCheckBox->isChecked())
        CalculateY();

    UpdateScene();
    UpdateStatus();
}
