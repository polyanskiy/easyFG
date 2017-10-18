#include "easyfg.h"


void MainWindow::on_pseudocolorCheckBox_stateChanged()
{
    if(dataloaded){
        SetColorTable();
        pixmap->setPixmap(QPixmap::fromImage(image));
        scene.update(scene.sceneRect());
        scaleLabel->setPixmap(QPixmap::fromImage(scale));
    }
}


void MainWindow::on_invertedCheckBox_stateChanged()
{
    if(dataloaded){
        SetColorTable();
        pixmap->setPixmap(QPixmap::fromImage(image));
        scene.update(scene.sceneRect());
        scaleLabel->setPixmap(QPixmap::fromImage(scale));
    }
}


void MainWindow::SetColorTable()
{
    QVector<QRgb> colortable(256);
    QVector<QRgb> inverted_colortable(256);
    QColor color;
    for(int i=0; i<=255; i++){
        if(pseudocolorCheckBox->isChecked()){
            if(i<=32)
                color.setRgb( 0, 0, 127+(int)((i/64.0)*255+0.5) );
            else{
                if(i<=96)
                    color.setRgb( 0, (int)(((i-32)/64.0)*255+0.5), 255 );
                else{
                    if(i<=160)
                        color.setRgb( (int)(((i-96)/64.0)*255+0.5), 255, 255-(int)(((i-96)/64.0)*255+0.5) );
                    else{
                        if(i<=224)
                            color.setRgb( 255, 255-(int)(((i-160)/64.0)*255+0.5), 0 );
                        else
                            color.setRgb( 255-(int)(((i-224)/64.0)*255+0.5), 0, 0 );
                    }
                }
            }
        }
        else
            color.setRgb(i,i,i);
        colortable[i] = color.rgb();
        inverted_colortable[255-i] = color.rgb();
    }

    if(invertedCheckBox->isChecked()){
        image.setColorTable(inverted_colortable);
        scale.setColorTable(inverted_colortable);
    }
    else{
        image.setColorTable(colortable);
        scale.setColorTable(colortable);
    }
}
