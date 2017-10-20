#include "easyfg.h"


// Copy frame image or projection data to clipboard
void MainWindow::on_graphicsView_customContextMenuRequested()
{
    if(!dataloaded)
    return;

    QAction *img = new QAction("Copy image [Ctrl+C]", this);
    //QAction *frm = new QAction("Copy frame image", this);
    QAction *x = new QAction("Copy X data", this);
    QAction *y = new QAction("Copy Y data", this);
    QAction *d = new QAction("Copy beam size data", this);

    QMenu menu("");
    menu.addAction(img);
    //menu.addAction(frm);
    if(XCheckBox->isChecked())
        menu.addAction(x);
    if(YCheckBox->isChecked())
        menu.addAction(y);
    if(DCheckBox->isChecked())
        menu.addAction(d);

    connect(img, SIGNAL(triggered()), this, SLOT(CopyImage()));
    connect(x, SIGNAL(triggered()), this, SLOT(CopyX()));
    connect(y, SIGNAL(triggered()), this, SLOT(CopyY()));
    connect(d, SIGNAL(triggered()), this, SLOT(CopyD()));

    menu.exec(QCursor::pos());
}


// Copy image (with all lines) to clipboard
void MainWindow::CopyImage()
{
    QImage img(scene.sceneRect().size().toSize()*pow(2.0,zoom/2.0), QImage::Format_ARGB32);
    img.fill(0);
    QPainter painter(&img);
    scene.render(&painter);
    QApplication::clipboard()->setPixmap(QPixmap::fromImage(img));
}

// Copy frame only (no lines) to clipboard
/*void MainWindow::CopyFrame()
{
    QApplication::clipboard()->setPixmap(QPixmap::fromImage(image));
}*/


// Copy X (horizontal) projection data to clipboard
void MainWindow::CopyX()
{
    if(!dataloaded)
        return;
    QString str = QString();
    for(int i=0; i<datawidth; i++)
        str += QString::number(i) + "\t" +  QString::number(X[i]) + "\n";
    QApplication::clipboard()->setText(str);
}

// Copy Y (vertical) projection data to clipboard
void MainWindow::CopyY()
{
    if(!dataloaded)
        return;
    QString str = QString();
    for(int j=0; j<dataheight; j++)
        str += QString::number(j) + "\t" +  QString::number(Y[j]) + "\n";
    QApplication::clipboard()->setText(str);
}

void MainWindow::CopyD()
{
    if(!dataloaded)
        return;
    QString str = QString();
    str.sprintf("%.1f\t%.1f",sigmax*4, sigmay*4);
    QApplication::clipboard()->setText(str);
}

// Copy colormap image to clipboard
void MainWindow::on_scaleLabel_customContextMenuRequested()
{
    QMenu menu("");
    menu.addAction("Copy colormap image");
    if( menu.exec(QCursor::pos()) )
        QApplication::clipboard()->setPixmap(QPixmap::fromImage(scale));
}
