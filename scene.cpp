#include "easyfg.h"


MyScene::MyScene()
{
    x = 0;
    y = 0;
}


bool MyScene::event(QEvent* event)
{
    switch(event->type()){
        case QEvent::Leave:
            emit mouseLeft();
            break;
        case QEvent::GraphicsSceneMouseMove:
            x = (int)(static_cast<QGraphicsSceneMouseEvent*>(event)->scenePos().x());
            y = (int)(static_cast<QGraphicsSceneMouseEvent*>(event)->scenePos().y());
            emit mouseMoved();
            break;
        case QEvent::GraphicsSceneMousePress:
            emit mousePressed();;
            break;
        case QEvent::GraphicsSceneMouseRelease:
            emit mouseReleased();
            break;
        default:
            return false;
    }
    return false;
}


void MainWindow::mouseMovedOnScene()
{
    int x = scene.x;
    int y = scene.y;
    if(x > datawidth-1 || x < 0 || y > dataheight || y < 0)
	inimage = false;
    else
	inimage = true;

    if(inimage){
        setCursor(Qt::CrossCursor);
        if(( (YCheckBox->isChecked()||beamCheckBox->isChecked()) && x <= Y2SpinBox->value()+2/pow(2,zoom/2) && x >= Y2SpinBox->value()-2/pow(2,zoom/2)) || y2drag)
            setCursor(Qt::SplitHCursor);
        if(( (YCheckBox->isChecked()||beamCheckBox->isChecked()) && x <= Y1SpinBox->value()+2/pow(2,zoom/2) && x >= Y1SpinBox->value()-2/pow(2,zoom/2)) || y1drag)
            setCursor(Qt::SplitHCursor);
        if(( (XCheckBox->isChecked()||beamCheckBox->isChecked()) && y <= X2SpinBox->value()+2/pow(2,zoom/2) && y >= X2SpinBox->value()-2/pow(2,zoom/2)) || x2drag)
            setCursor(Qt::SplitVCursor);
        if(( (XCheckBox->isChecked()||beamCheckBox->isChecked()) && y <= X1SpinBox->value()+2/pow(2,zoom/2) && y >= X1SpinBox->value()-2/pow(2,zoom/2)) || x1drag)
            setCursor(Qt::SplitVCursor);
    }
    else
	setCursor(Qt::ArrowCursor);

    if(x > datawidth-1)
        x = datawidth-1;
    if(x < 0)
        x = 0;
    if(y > dataheight-1)
        y = dataheight-1;
    if(y < 0)
        y = 0;

    if(x1drag){
        x1line->setLine(0.5, y+0.5, datawidth-0.5, y+0.5);
        UpdateScene();
    }
    if(x2drag){
        x2line->setLine(0.5, y+0.5, datawidth-0.5, y+0.5);
        UpdateScene();
    }
    if(y1drag){
        y1line->setLine(x+0.5, 0.5, x+0.5, dataheight-0.5);
        UpdateScene();
    }
    if(y2drag){
        y2line->setLine(x+0.5, 0.5, x+0.5, dataheight-0.5);
        UpdateScene();
    }

    UpdateStatus();
}


void MainWindow::mousePressedOnScene()
{
    if( (YCheckBox->isChecked()||beamCheckBox->isChecked()) && scene.x <= Y2SpinBox->value()+2/pow(2,zoom/2) && scene.x >= Y2SpinBox->value()-2/pow(2,zoom/2)){
        x1drag=false;
        x2drag=false;
        y1drag=false;
        y2drag=true;
    }
    if( (YCheckBox->isChecked()||beamCheckBox->isChecked()) && scene.x <= Y1SpinBox->value()+2/pow(2,zoom/2) && scene.x >= Y1SpinBox->value()-2/pow(2,zoom/2)){
        x1drag=false;
        x2drag=false;
        y1drag=true;
        y2drag=false;
    }
    if( (XCheckBox->isChecked()||beamCheckBox->isChecked()) && scene.y <= X2SpinBox->value()+2/pow(2,zoom/2) && scene.y >= X2SpinBox->value()-2/pow(2,zoom/2)){
        x1drag=false;
        x2drag=true;
        y1drag=false;
        y2drag=false;
    }
    if( (XCheckBox->isChecked()||beamCheckBox->isChecked()) && scene.y <= X1SpinBox->value()+2/pow(2,zoom/2) && scene.y >= X1SpinBox->value()-2/pow(2,zoom/2)){
        x1drag=true;
        x2drag=false;
        y1drag=false;
        y2drag=false;
    }
}


void MainWindow::mouseReleasedOnScene()
{
    if(x1drag)
	X1SpinBox->setValue(scene.y);
    if(x2drag)
	X2SpinBox->setValue(scene.y);
    if(y1drag)
	Y1SpinBox->setValue(scene.x);
    if(y2drag)
	Y2SpinBox->setValue(scene.x);
    x1drag=false;
    x2drag=false;
    y1drag=false;
    y2drag=false;
}


void MainWindow::mouseLeftScene()
{
    setCursor(Qt::ArrowCursor);
    inimage = false;
    UpdateStatus();
}


//Copy image to clipboard
void MainWindow::CopyFigure()
{
    QApplication::clipboard()->setPixmap(QPixmap::fromImage(image));
}


// Copy frame image or projection data to clipboard
void MainWindow::on_graphicsView_customContextMenuRequested()
{
    if(!dataloaded)
	return;

    QAction *img = new QAction("Copy image [Alt+i]", this);
    QAction *x = new QAction("Copy X data [Alt+X]", this);
    QAction *y = new QAction("Copy Y data [Alt+Y]", this);

    QMenu menu("");
    menu.addAction(img);
    if(XCheckBox->isChecked())
        menu.addAction(x);
    if(YCheckBox->isChecked())
        menu.addAction(y);

    connect(img, SIGNAL(triggered()), this, SLOT(CopyFigure()));
    connect(x, SIGNAL(triggered()), this, SLOT(on_XCopyButton_clicked()));
    connect(y, SIGNAL(triggered()), this, SLOT(on_YCopyButton_clicked()));

    menu.exec(QCursor::pos());
}


// Right-button-cick menu
void MainWindow::on_scaleLabel_customContextMenuRequested()
{
    QMenu menu("");
    menu.addAction("Copy image");
    if( menu.exec(QCursor::pos()) )
	QApplication::clipboard()->setPixmap(QPixmap::fromImage(scale));
}
