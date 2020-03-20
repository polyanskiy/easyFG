#include "easyfg.h"


void MainWindow::RedoAnalysis()
{
    if(XCheckBox->isChecked())
        CalculateX();
    else
        xprojection->setPath(QPainterPath());

    if(YCheckBox->isChecked())
        CalculateY();
    else
        yprojection->setPath(QPainterPath());

    if(RCheckBox->isChecked())
        CalculateR();
    //else
    //    rprojection->setPath(QPainterPath());

    if(DCheckBox->isChecked())
        CalculateBeam();
    else
        ellipse->setRect(0,0,0,0);
}


void MainWindow::on_XCheckBox_stateChanged()
{
    if(!dataloaded)
        return;

    if(XCheckBox->isChecked())
        CalculateX();

    UpdateVisibility();
    UpdateScene();
}


void MainWindow::on_YCheckBox_stateChanged()
{
    if(!dataloaded)
        return;

    if(YCheckBox->isChecked())
        CalculateY();

    UpdateVisibility();
    UpdateScene();
}


void MainWindow::on_RCheckBox_stateChanged()
{
    if(!dataloaded)
        return;

    if(RCheckBox->isChecked())
        CalculateR();

    UpdateVisibility();
    UpdateScene();
}


void MainWindow::on_DCheckBox_stateChanged()
{
    if(!dataloaded)
        return;

    /*if(DCheckBox->isChecked()){
        h1line->setLine(0.5, H1SpinBox->value()+0.5, datawidth-0.5, H1SpinBox->value()+0.5);
        h2line->setLine(0.5, H2SpinBox->value()+0.5, datawidth-0.5, H2SpinBox->value()+0.5);
        v1line->setLine(V1SpinBox->value(), 0.5, V1SpinBox->value(), dataheight-0.5);
        v2line->setLine(V2SpinBox->value(), 0.5, V2SpinBox->value(), dataheight-0.5);
    }*/

    if(DCheckBox->isChecked())
        CalculateBeam();

    UpdateVisibility();
    UpdateScene();
    UpdateStatus();
}




void MainWindow::CalculateX()
{
    if(!dataloaded)
        return;

    float pixel;
    float offset = minSpinBox->value();
    int min = (H1SpinBox->value() < H2SpinBox->value()) ? H1SpinBox->value() : H2SpinBox->value();
    int max = (H1SpinBox->value() < H2SpinBox->value()) ? H2SpinBox->value() : H1SpinBox->value();

    float xmax = 0;
    for(int i=0; i<datawidth; i++){
        X[i] = 0;
        for(int j=min; j<=max; j++){
            if(referenceComboBox->currentIndex()>0 && refloaded)
                pixel = CorrectedArray[i][j];
            else
                pixel = DataArray[i][j];

            X[i] += pixel - offset;
        }
        X[i] /= max-min+1;
        if(X[i] > xmax)
            xmax = X[i];
    }

    QPainterPath path;
    for(int i=0; i<datawidth; i++){
        float j;
        dataheight<datawidth ? j = X[i]/xmax*dataheight/3 : j = X[i]/xmax*datawidth/3;
        if(j<0)
            j=0;
        if(i==0)
            path.moveTo(i+0.5, j+0.5);
        else
            path.lineTo(i+0.5, j+0.5);
    }
    xprojection->setPath(path);
}


void MainWindow::CalculateY()
{
    if(!dataloaded)
        return;

    float pixel;
    float offset = minSpinBox->value();
    int min = (V1SpinBox->value() < V2SpinBox->value()) ? V1SpinBox->value() : V2SpinBox->value();
    int max = (V1SpinBox->value() < V2SpinBox->value()) ? V2SpinBox->value() : V1SpinBox->value();

    float ymax = 0;
    for(int j=0; j<dataheight; j++){
        Y[j] = 0;
        for(int i=min; i<=max; i++){
            if(referenceComboBox->currentIndex()>0 && refloaded)
                pixel = CorrectedArray[i][j];
            else
                pixel = DataArray[i][j];

            Y[j] += pixel - offset;
        }
        Y[j] /= max-min+1;
        if(Y[j] > ymax)
            ymax = Y[j];
    }

    QPainterPath path;
    for(int j=0; j<dataheight; j++){
        float i;
        dataheight<datawidth ? i = Y[j]/ymax*dataheight/3 : i = Y[j]/ymax*datawidth/3;
        if(i<0)
            i=0;
        if(j==0)
            path.moveTo(i+0.5, j+0.5);
        else
            path.lineTo(i+0.5, j+0.5);
    }
    yprojection->setPath(path);
}


void MainWindow::CalculateR()
{
    if(!dataloaded)
        return;
}


void MainWindow::CalculateBeam()
{
    if(!dataloaded)
	return;

    int ymin = (H1SpinBox->value() < H2SpinBox->value()) ? H1SpinBox->value() : H2SpinBox->value();
    int ymax = (H1SpinBox->value() < H2SpinBox->value()) ? H2SpinBox->value() : H1SpinBox->value();
    int xmin = (V1SpinBox->value() < V2SpinBox->value()) ? V1SpinBox->value() : V2SpinBox->value();
    int xmax = (V1SpinBox->value() < V2SpinBox->value()) ? V2SpinBox->value() : V1SpinBox->value();

    int i, j;
    float horiz[datawidth], vert[dataheight];
    float integrated=0;
    float pixel;
    float offset;


    for(i=0; i<datawidth; i++)
        horiz[i] = 0;
    for(j=0; j<dataheight; j++)
        vert[j] = 0;

    offset = minSpinBox->value();

    // horizontal and vertical integration
    for(i=xmin; i<=xmax; i++){
        for(j=ymin; j<=ymax; j++){
            if(referenceComboBox->currentIndex()>0 && refloaded)
                pixel = CorrectedArray[i][j] - offset;
            else
                pixel = DataArray[i][j] - offset;
            horiz[i] += pixel;
            vert[j] += pixel;
            integrated += pixel;
        }
    }

    // centroid X, Y
    centroidx = 0;
    for(i=xmin; i<=xmax; i++)
        centroidx += horiz[i] * (float)i;
    centroidx /= integrated;

    centroidy = 0;
    for(j=ymin; j<=ymax; j++) 
        centroidy += vert[j] * (float)j;
    centroidy /= integrated;

    // sigma X, Y
    sigmax = 0;
    for(i=xmin; i<=xmax; i++)
            sigmax += horiz[i] * pow(centroidx-i,2);
    sigmax<=0||integrated<=0 ? sigmax=0 : sigmax=sqrt(sigmax/integrated);

    sigmay = 0;
    for(j=ymin; j<=ymax; j++)
            sigmay += vert[j] * pow(centroidy-j,2);
    sigmay<=0||integrated<=0 ? sigmay=0 : sigmay=sqrt(sigmay/integrated);

    // centroid mark
    centerAline->setLine(centroidx-2.5, centroidy-2.5, centroidx+3.5, centroidy+3.5);
    centerBline->setLine(centroidx-2.5, centroidy+3.5, centroidx+3.5, centroidy-2.5);

    // beam profile
    ellipse->setRect( centroidx+0.5-sigmax*2, centroidy+0.5-sigmay*2, sigmax*4, sigmay*4);
}
