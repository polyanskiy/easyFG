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

    if(beamCheckBox->isChecked())
        CalculateBeam();
    else
        ellipse->setRect(0,0,0,0);
}


void MainWindow::on_XCheckBox_stateChanged()
{
    if(!dataloaded)
        return;

    if(XCheckBox->isChecked() || beamCheckBox->isChecked()){
        x1line->setLine(0.5, X1SpinBox->value()+0.5, datawidth-0.5, X1SpinBox->value()+0.5);
        x2line->setLine(0.5, X2SpinBox->value()+0.5, datawidth-0.5, X2SpinBox->value()+0.5);
    }

    if(XCheckBox->isChecked())
        CalculateX();

    UpdateVisibility();
    UpdateScene();
}


void MainWindow::on_YCheckBox_stateChanged()
{
    if(!dataloaded)
        return;

    if(YCheckBox->isChecked() || beamCheckBox->isChecked()) {
        y1line->setLine(Y1SpinBox->value()+0.5, 0.5, Y1SpinBox->value()+0.5, dataheight-0.5);
        y2line->setLine(Y2SpinBox->value()+0.5, 0.5, Y2SpinBox->value()+0.5, dataheight-0.5);
    }

    if(YCheckBox->isChecked())
        CalculateY();

    UpdateVisibility();
    UpdateScene();
}


void MainWindow::on_beamCheckBox_stateChanged()
{
    if(!dataloaded)
        return;

    if(beamCheckBox->isChecked()){
        x1line->setLine(0.5, X1SpinBox->value()+0.5, datawidth-0.5, X1SpinBox->value()+0.5);
        x2line->setLine(0.5, X2SpinBox->value()+0.5, datawidth-0.5, X2SpinBox->value()+0.5);
        y1line->setLine(Y1SpinBox->value(), 0.5, Y1SpinBox->value(), dataheight-0.5);
        y2line->setLine(Y2SpinBox->value(), 0.5, Y2SpinBox->value(), dataheight-0.5);
    }

    if(beamCheckBox->isChecked())
        CalculateBeam();

    UpdateVisibility();
    UpdateScene();
    UpdateStatus();
}


void MainWindow::on_X1SpinBox_valueChanged()
{
    if(!( (XCheckBox->isChecked()||beamCheckBox->isChecked()) && dataloaded ))
        return;

    x1line->setLine(0.5, X1SpinBox->value()+0.5, datawidth-0.5, X1SpinBox->value()+0.5);

    if(XCheckBox->isChecked())
        CalculateX();
    if(beamCheckBox->isChecked()){
        CalculateBeam();
        UpdateStatus();
    }

    UpdateScene();
}


void MainWindow::on_X2SpinBox_valueChanged()
{
    if(!( (XCheckBox->isChecked()||beamCheckBox->isChecked()) && dataloaded ))
        return;

    x2line->setLine(0.5, X2SpinBox->value()+0.5, datawidth-0.5, X2SpinBox->value()+0.5);

    if(XCheckBox->isChecked())
        CalculateX();
    if(beamCheckBox->isChecked()){
        CalculateBeam();
        UpdateStatus();
    }

    UpdateScene();
}


void MainWindow::on_Y1SpinBox_valueChanged()
{
    if(!( (YCheckBox->isChecked()||beamCheckBox->isChecked()) && dataloaded ))
        return;

    y1line->setLine(Y1SpinBox->value()+0.5, 0.5, Y1SpinBox->value()+0.5, dataheight-0.5);

    if(YCheckBox->isChecked())
        CalculateY();
    if(beamCheckBox->isChecked()){
        CalculateBeam();
        UpdateStatus();
    }

    UpdateScene();
}


void MainWindow::on_Y2SpinBox_valueChanged()
{
    if(!( (YCheckBox->isChecked()||beamCheckBox->isChecked()) && dataloaded ))
        return;

    y2line->setLine(Y2SpinBox->value()+0.5, 0.5, Y2SpinBox->value()+0.5, dataheight-0.5);

    if(YCheckBox->isChecked())
        CalculateY();
    if(beamCheckBox->isChecked()){
        CalculateBeam();
        UpdateStatus();
    }

    UpdateScene();
}


void MainWindow::on_XCopyButton_clicked()
{
    if(!dataloaded)
        return;
    QString str = QString();
    for(int i=0; i<datawidth; i++)
        str += QString::number(i) + "\t" +  QString::number(X[i]) + "\n";
    QApplication::clipboard()->setText(str);
}


void MainWindow::on_YCopyButton_clicked()
{
    if(!dataloaded)
        return;
    QString str = QString();
    for(int j=0; j<dataheight; j++)
        str += QString::number(j) + "\t" +  QString::number(Y[j]) + "\n";
    QApplication::clipboard()->setText(str);
}


void MainWindow::on_FixRangesButton_clicked()
{
    if(!dataloaded)
        return;

    X1SpinBox->setValue(centroidy-sigmay*6);
    X2SpinBox->setValue(centroidy+sigmay*6);
    Y1SpinBox->setValue(centroidx-sigmax*6);
    Y2SpinBox->setValue(centroidx+sigmax*6);

    UpdateRanges();

    CalculateBeam();
    if(XCheckBox->isChecked())
        CalculateX();
    if(YCheckBox->isChecked())
        CalculateY();

    UpdateScene();
    UpdateStatus();
}

void MainWindow::on_FixOffsetButton_clicked()
{
    if(!dataloaded)
        return;

    int i,j;
    int count=0;
    int offset=0;

    int ymin = (X1SpinBox->value() < X2SpinBox->value()) ? X1SpinBox->value() : X2SpinBox->value();
    int ymax = (X1SpinBox->value() < X2SpinBox->value()) ? X2SpinBox->value() : X1SpinBox->value();
    int xmin = (Y1SpinBox->value() < Y2SpinBox->value()) ? Y1SpinBox->value() : Y2SpinBox->value();
    int xmax = (Y1SpinBox->value() < Y2SpinBox->value()) ? Y2SpinBox->value() : Y1SpinBox->value();

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

    offsetSpinBox->setValue(offset);

    CalculateBeam();
    if(XCheckBox->isChecked())
        CalculateX();
    if(YCheckBox->isChecked())
        CalculateY();

    UpdateScene();
    UpdateStatus();
}

void MainWindow::CalculateX()
{
    if(!dataloaded)
        return;

    int tmp;
    int offset = offsetSpinBox->value();
    int min = (X1SpinBox->value() < X2SpinBox->value()) ? X1SpinBox->value() : X2SpinBox->value();
    int max = (X1SpinBox->value() < X2SpinBox->value()) ? X2SpinBox->value() : X1SpinBox->value();

    float xmax = 0;
    for(int i=0; i<datawidth; i++){
        X[i] = 0;
        for(int j=min; j<=max; j++){
            if(referenceComboBox->currentIndex()>0 && refloaded)
                tmp = CorrectedArray[i][j];
            else
                tmp = DataArray[i][j];

            X[i] += tmp - offset;
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
            path.moveTo(i+0.5, j);
        else
            path.lineTo(i+0.5, j);
    }
    xprojection->setPath(path);
}


void MainWindow::CalculateY()
{
    if(!dataloaded)
        return;

    int tmp;
    int offset = offsetSpinBox->value();
    int min = (Y1SpinBox->value() < Y2SpinBox->value()) ? Y1SpinBox->value() : Y2SpinBox->value();
    int max = (Y1SpinBox->value() < Y2SpinBox->value()) ? Y2SpinBox->value() : Y1SpinBox->value();

    float ymax = 0;
    for(int j=0; j<dataheight; j++){
        Y[j] = 0;
        for(int i=min; i<=max; i++){
            if(referenceComboBox->currentIndex()>0 && refloaded)
                tmp = CorrectedArray[i][j];
            else
                tmp = DataArray[i][j];

            Y[j] += tmp - offset;
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
            path.moveTo(i, j+0.5);
        else
            path.lineTo(i, j+0.5);
    }
    yprojection->setPath(path);
}


void MainWindow::CalculateBeam()
{
    if(!dataloaded)
	return;

    int ymin = (X1SpinBox->value() < X2SpinBox->value()) ? X1SpinBox->value() : X2SpinBox->value();
    int ymax = (X1SpinBox->value() < X2SpinBox->value()) ? X2SpinBox->value() : X1SpinBox->value();
    int xmin = (Y1SpinBox->value() < Y2SpinBox->value()) ? Y1SpinBox->value() : Y2SpinBox->value();
    int xmax = (Y1SpinBox->value() < Y2SpinBox->value()) ? Y2SpinBox->value() : Y1SpinBox->value();

    int i, j;
    float horiz[datawidth], vert[dataheight];
    float integrated=0, pixel;
    int offset;


    for(i=0; i<datawidth; i++)
	horiz[i] = 0;
    for(j=0; j<dataheight; j++)
	vert[j] = 0;

    offset = offsetSpinBox->value();

    // horizontal and vertical integration
    for(i=xmin; i<=xmax; i++){
            for(j=ymin; j<=ymax; j++){
            if(referenceComboBox->currentIndex()>0 && refloaded)
                pixel = CorrectedArray[i][j] - offset;
            else
                pixel = DataArray[i][j] - (float)offset;
            //if(pixel<0)
            //    pixel=0;
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

    /*centroidx = floor(centroidx+0.5);
    centroidy = floor(centroidy+0.5);
    sigmax = floor(sigmax+0.5);
    sigmay = floor(sigmay+0.5);*/

    // centroid mark
    centerAline->setLine(centroidx-2.5, centroidy-2.5, centroidx+3.5, centroidy+3.5);
    centerBline->setLine(centroidx-2.5, centroidy+3.5, centroidx+3.5, centroidy-2.5);

    // beam profile
    ellipse->setRect( centroidx+0.5-sigmax*2, centroidy+0.5-sigmay*2, sigmax*4, sigmay*4);
}
