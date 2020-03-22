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
    else{
        rprojection1->setPath(QPainterPath());
        rprojection2->setPath(QPainterPath());
    }

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
    else{
        rprojection1->setPath(QPainterPath());
        rprojection2->setPath(QPainterPath());
    }

    UpdateVisibility();
    UpdateScene();
}


void MainWindow::on_DCheckBox_stateChanged()
{
    if(!dataloaded)
        return;

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

    float xmax = -1e38;
    for(int i=0; i<datawidth; i++){
        X[i] = 0;
        for(int j=min; j<=max; j++){
            if(referenceComboBox->currentIndex()>0 && refloaded)
                pixel = CorrectedArray[i][j] - offset;
            else
                pixel = DataArray[i][j] - offset;

            X[i] += pixel;
        }
        X[i] /= max-min+1;
        if(X[i] > xmax)
            xmax = X[i];
    }

    // plot projection curve
    QPainterPath path;
    for(int i=0; i<datawidth; i++){
        float j;
        dataheight<datawidth ? j = X[i]/xmax*dataheight/3 : j = X[i]/xmax*datawidth/3;
        if(j<0)
            j=0;
        if(i==0)
            path.moveTo(i+0.5, dataheight-(j+0.5));
        else
            path.lineTo(i+0.5, dataheight-(j+0.5));
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

    float ymax = -1e38;
    for(int j=0; j<dataheight; j++){
        Y[j] = 0;
        for(int i=min; i<=max; i++){
            if(referenceComboBox->currentIndex()>0 && refloaded)
                pixel = CorrectedArray[i][j] - offset;
            else
                pixel = DataArray[i][j] - offset;

            Y[j] += pixel;
        }
        Y[j] /= max-min+1;
        if(Y[j] > ymax)
            ymax = Y[j];
    }

    // plot projection curve
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

    int ymin = (H1SpinBox->value() < H2SpinBox->value()) ? H1SpinBox->value() : H2SpinBox->value();
    int ymax = (H1SpinBox->value() < H2SpinBox->value()) ? H2SpinBox->value() : H1SpinBox->value();
    int xmin = (V1SpinBox->value() < V2SpinBox->value()) ? V1SpinBox->value() : V2SpinBox->value();
    int xmax = (V1SpinBox->value() < V2SpinBox->value()) ? V2SpinBox->value() : V1SpinBox->value();

    int i, j, k;
    float* horiz = (float*)malloc(datawidth*sizeof(float));
    float* vert = (float*)malloc(dataheight*sizeof(float));
    int maxpoints = ceil(sqrt(pow(datawidth,2)+pow(dataheight,2)));
    int* npixels = (int*)malloc(maxpoints*sizeof(int));

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

    for(k=0; k<maxpoints; k++){
        R[k] = -1e38;
        npixels[k] = 0;
    }

    for(i=0; i<datawidth; i++){
        for(j=0; j<dataheight; j++){
            if(referenceComboBox->currentIndex()>0 && refloaded)
                pixel = CorrectedArray[i][j] - offset;
            else
                pixel = DataArray[i][j] - offset;
            // radial coordinate (in pix number)
            //k = floor(sqrt( pow(i-centroidx,2) + pow(j-centroidy,2) ) + 0.5);
            float dist_from_centr = sqrt( pow(i-centroidx,2) + pow(j-centroidy,2) );
            dist_from_centr==0 ? k=0 : k=(int)ceil(dist_from_centr-1);
            npixels[k]==0 ? R[k]=pixel : R[k]+=pixel;
            npixels[k]++;
        }
    }

    float rmax = -1e38;
    k = 0;
    //while(npixels[k]>0 && k<maxpoints){
    //while(k<maxpoints){
    while(R[k]>-1e37 && k<maxpoints){
        R[k] /= npixels[k];
        if(R[k] > rmax)
            rmax = R[k];
        k++;
    }

    free(horiz);
    free(vert);
    free(npixels);

    // draw centroid mark
    centerAline->setLine(centroidx-2.5, centroidy-2.5, centroidx+3.5, centroidy+3.5);
    centerBline->setLine(centroidx-2.5, centroidy+3.5, centroidx+3.5, centroidy-2.5);

    // plot projection curve
    QPainterPath path1, path2;
    k=0;
    //while(npixels[k]>0 && k<maxpoints){
    //while(k<maxpoints){
    while(R[k]>-1e37 && k<maxpoints){
        //float i = k+centroidx;
        float j;
        dataheight<datawidth ? j = R[k]/rmax*dataheight/3 : j = R[k]/rmax*datawidth/3;
        //if(j<0)
            //j=0;
        if(k==0)
            path1.moveTo(centroidx+0.5+k, centroidy-(j+0.5));
        else
            path1.lineTo(centroidx+0.5+k, centroidy-(j+0.5));
        k++;
    }
    path2.moveTo(centroidx+0.5, centroidy+0.5);
    path2.lineTo(centroidx+k+0.5, centroidy+0.5);

    rprojection1->setPath(path1);
    rprojection2->setPath(path2);
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
    float* horiz = (float*)malloc(datawidth*sizeof(float));
    float* vert = (float*)malloc(dataheight*sizeof(float));
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

    free(horiz);
    free(vert);

    // draw centroid mark
    centerAline->setLine(centroidx-2.5, centroidy-2.5, centroidx+3.5, centroidy+3.5);
    centerBline->setLine(centroidx-2.5, centroidy+3.5, centroidx+3.5, centroidy-2.5);

    // plot beam size ellipse
    ellipse->setRect( centroidx+0.5-sigmax*2, centroidy+0.5-sigmay*2, sigmax*4, sigmay*4);
}
