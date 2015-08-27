#include <QObject>
#include <QAction>
#include <QWidget>
#include <QMenu>
#include <QMenuBar>
#include <QtGui>
#include <QFileDialog>
#include <QDrag>

#include <QImage>
#include <QPixmap>

#include <QMouseEvent>
#include <QWheelEvent>


// qwt
//#include <qwt_plot.h>

#include <iostream>

// rev2
//#include "b16img.h"
#include "b16img2.h"
#include "physImage.h"



#ifndef __imgLabel_h__
#define __imgLabel_h__

struct selection_rect {
	int x_ul;
	int y_ul;
	int width;
	int height;
};

enum cursor_shape {plain, circle};

class imgLabel : public QLabel {

	Q_OBJECT
public:
	//imgLabel();
	imgLabel(QWidget *);

	void init_variables(void);

	void mouseMoveEvent(QMouseEvent *);
	void mousePressEvent(QMouseEvent *);
	void mouseReleaseEvent(QMouseEvent *);

	void wheelEvent(QWheelEvent *); 

	float cursor_size;
	enum cursor_shape my_cshape;


protected:
	void paintEvent(QPaintEvent *event);

signals:
	void mouse_moved_on_image(int, int);
	void mouse_press(int, int);
	void mouse_release(int, int);
	void new_cursor_size(float);


private:
	selection_rect *my_selection_rect;
	imagePointList draw_point_list, level_point_list;
	vector<QPolygonF> drawn_rects, QIT_drawn_polys;
	QPointF QIT_center;

	// status variables
	bool draw_imagewide_cursor, draw_rowgraph, draw_colgraph, draw_imagewide_reference;
	int cursor_x, cursor_y;
	int ref_x, ref_y;

public slots:
	void set_selection_rect(int, int, int, int);
	void set_cursor_position(int, int);
	void draw_points_on_image(imagePointList);
	void draw_levels_on_image(imagePointList);
	void resetPainter(void);

	// stato durante il movimento del mouse nell'immagine
	void set_imagewide_cursor(bool);	// cursore con estensioni su tutta l'immagine
	void drawGraph_state(int);
	void set_rowgraph(bool);		// grafico delle intensita' sulla linea
	void set_colgraph(bool);		// stessa cosa sulla colonna

	void toggle_origin_plot(bool val)
	{ draw_imagewide_reference = val; }
	void set_origin_point(int x, int y)
	{ ref_x = x; ref_y = y; }
	void toggle_cursor_shape()
	{
		if (my_cshape == plain)
			my_cshape = circle;
		else
			my_cshape = plain;
	}


	// PHM (= polyhist manager) communication
	void add_rect_on_image(QPolygonF);


	// v2. complete track status


};



#endif

