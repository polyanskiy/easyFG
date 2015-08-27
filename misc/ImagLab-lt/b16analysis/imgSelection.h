

#include <QObject>
#include <QAction>
#include <QWidget>
#include <QMenu>
#include <QMenuBar>
#include <QtGui>
#include <QFileDialog>

#include <QImage>
#include <QPixmap>
#include <QPoint>
#include <QMouseEvent>

#include <iostream>


// selezione su immagine
//

#ifndef __imgSelection
#define __imgSelection

class imgSelection : public QObject
{
	Q_OBJECT
public:
	imgSelection();

	QPoint upperLeft, lowerRight;

signals:
//	void draw_rectangle_on_image(QPoint&, QPoint&);
	void selection_coords(int, int, int, int);

public slots:
	void set_point(int,int);
	void set_new_lower_right(int,int);
	void set_new_upper_left(int,int);

	void mouse_moved_in_selection(int,int);

private:
	int x_ul, y_ul, x_lr, y_lr;

};

#endif
