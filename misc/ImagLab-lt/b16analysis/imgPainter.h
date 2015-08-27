#include <QObject>
#include <QAction>
#include <QWidget>
#include <QMenu>
#include <QMenuBar>
#include <QtGui>
#include <QFileDialog>

#include <QImage>
#include <QPixmap>
#include <QPainter>

#include <QMouseEvent>

#include <iostream>


#ifndef __imgPainter_h__
#define __imgPainter_h__

// beh, certe cose un po' ti si attaccano ai coglioni...
//

// in futuro dovro' implementare l'enum sui parametri

class imgPainter : public QPainter {
	Q_OBJECT

public:
	imgPainter();
	imgPainter(QWidget *parent = 0);

protected:
	void paintEvent(QPaintEvent *event);

public slots:
	void set_init_poit(int, int);
	void set_size(int, int);

private:
	int i1,i2,i3,i4; // usi vari

};

#endif


