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
        if(( VCheckBox->isChecked() && x <= cursorv2+2 && x >= cursorv2-2) || v2drag)
            setCursor(Qt::SplitHCursor);
        if(( VCheckBox->isChecked() && x <= cursorv1+2 && x >= cursorv1-2) || v1drag)
            setCursor(Qt::SplitHCursor);
        if(( HCheckBox->isChecked() && y <= cursorh2+2 && y >= cursorh2-2) || h2drag)
            setCursor(Qt::SplitVCursor);
        if(( HCheckBox->isChecked() && y <= cursorh1+2 && y >= cursorh1-2) || h1drag)
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

    if(h1drag){
        h1line->setLine(0.5, y+0.5, datawidth-0.5, y+0.5);
        UpdateScene();
    }
    if(h2drag){
        h2line->setLine(0.5, y+0.5, datawidth-0.5, y+0.5);
        UpdateScene();
    }
    if(v1drag){
        v1line->setLine(x+0.5, 0.5, x+0.5, dataheight-0.5);
        UpdateScene();
    }
    if(v2drag){
        v2line->setLine(x+0.5, 0.5, x+0.5, dataheight-0.5);
        UpdateScene();
    }

    UpdateStatus();
}


void MainWindow::mousePressedOnScene()
{
    if( VCheckBox->isChecked() && scene.x <= cursorv2+2 && scene.x >= cursorv2-2){
        h1drag=false;
        h2drag=false;
        v1drag=false;
        v2drag=true;
    }
    if( VCheckBox->isChecked() && scene.x <= cursorv1+2 && scene.x >= cursorv1-2){
        h1drag=false;
        h2drag=false;
        v1drag=true;
        v2drag=false;
    }
    if( HCheckBox->isChecked() && scene.y <= cursorh2+2 && scene.y >= cursorh2-2){
        h1drag=false;
        h2drag=true;
        v1drag=false;
        v2drag=false;
    }
    if( HCheckBox->isChecked() && scene.y <= cursorh1+2 && scene.y >= cursorh1-2){
        h1drag=true;
        h2drag=false;
        v1drag=false;
        v2drag=false;
    }
}


void MainWindow::mouseReleasedOnScene()
{
    if(h1drag){
        H1SpinBox->setValue(scene.y);
    }
    if(h2drag){
        H2SpinBox->setValue(scene.y);
    }
    if(v1drag){
        V1SpinBox->setValue(scene.x);
    }
    if(v2drag){
        V2SpinBox->setValue(scene.x);
    }
    h1drag=false;
    h2drag=false;
    v1drag=false;
    v2drag=false;
    UpdateCursors();
}


void MainWindow::mouseLeftScene()
{
    setCursor(Qt::ArrowCursor);
    inimage = false;
    UpdateStatus();
}


void MainWindow::UpdateScene()
{
    scene.setSceneRect(scene.itemsBoundingRect());
    scene.update(scene.sceneRect());
}
