#include "imgLabel.h"

//imgLabel::imgLabel()
//{}

imgLabel::imgLabel(QWidget * parent)
	: QLabel(parent)
{
	setCursor(Qt::BlankCursor);
	my_selection_rect = NULL;

	init_variables();

	connect(this,SIGNAL(mouse_moved_on_image(int,int)), this, SLOT(set_cursor_position(int,int)));

}

void
imgLabel::init_variables(void)
{
	draw_imagewide_cursor = true;
	draw_rowgraph = false;
	draw_colgraph = false;

	drawn_rects.resize(0);

	my_cshape = plain;
	cursor_size = 10;
}

void
imgLabel::mouseMoveEvent(QMouseEvent *event)
{
	emit mouse_moved_on_image(event->x(),event->y());
}

void
imgLabel::wheelEvent(QWheelEvent *event)
{
	if (event->orientation() == Qt::Vertical) {
		cursor_size += event->delta()/100;
		emit new_cursor_size(abs(cursor_size));
		update();
	}
}

void
imgLabel::mousePressEvent(QMouseEvent *event)
{
	// mettiamoci pure il drag&drop
	if (event->button() == Qt::RightButton) {
		QDrag *drag = new QDrag(this);
		QMimeData *mimeData = new QMimeData;
		
		//mimeData->setText(QString("(%1:%2)").arg(event->y()).arg(event->x()));
		// altra versione
		mimeData->setText(QString("%1:%2").arg(event->x()).arg(event->y()));


		drag->setMimeData(mimeData);
		//drag->setPixmap(iconPixmap);
		
		Qt::DropAction dropAction = drag->exec();
	}

	emit mouse_press(event->x(),event->y());
}

void
imgLabel::mouseReleaseEvent(QMouseEvent *event)
{
	emit mouse_release(event->x(),event->y());
}



// slots
void
imgLabel::set_selection_rect(int x_ul, int y_ul, int wsize, int hsize)
{
	//std::cout<<"("<<x_ul<<":"<<y_ul<<") - "<<wsize<<"_/_"<<hsize<<std::endl;
	if (my_selection_rect == NULL) my_selection_rect = new struct selection_rect;

	my_selection_rect->x_ul = x_ul;
	my_selection_rect->y_ul = y_ul;
	my_selection_rect->width = wsize;
	my_selection_rect->height = hsize;

	update();
}

void
imgLabel::draw_points_on_image(imagePointList p_vec)
{
//	if (draw_point_list.size()>0) {
//		int old_len = draw_point_list.size();
//		int i;
//		draw_point_list.resize(old_len+p_vec.size());
//		for (i=0; i<p_vec.size(); i++) 
//			draw_point_list[i+old_len] = p_vec[i];
//	} else
		draw_point_list = p_vec;

	update();
}

void
imgLabel::add_rect_on_image(QPolygonF add_poly)
{ drawn_rects.push_back(add_poly); update(); }


void
imgLabel::draw_levels_on_image(imagePointList p_vec)
{
	level_point_list = p_vec;
	update();
}

void 
imgLabel::resetPainter(void)
{
	// chiamato al cambio di immagine
	draw_point_list.resize(0);
	level_point_list.resize(0);
}


void
imgLabel::paintEvent(QPaintEvent *event)
{
	int i;
	QPainter painter(this);
	if (pixmap() != NULL)
		painter.drawPixmap(0,0,*pixmap());
	
	if (my_selection_rect != NULL) {
		QPen pen;
		pen.setColor(QColor(255,255,0,255));
		pen.setStyle(Qt::DashLine);
		//painter.setPen(QColor(255,255,0,255));
		painter.setPen(pen);
		painter.drawRect(my_selection_rect->x_ul,\
				my_selection_rect->y_ul,\
				my_selection_rect->width,\
				my_selection_rect->height);
	}

	if (draw_imagewide_cursor) {
		QPen pen;
		pen.setColor(QColor(255,255,0,128));
		pen.setStyle(Qt::DashLine);
		painter.setPen(pen);
		painter.drawLine(cursor_x,0,cursor_x,this->height());
		painter.drawLine(0,cursor_y,this->width(),cursor_y);
		if (my_cshape == circle) {
			painter.drawEllipse(cursor_x-cursor_size/2, cursor_y-cursor_size/2, cursor_size, cursor_size);
		}
	}

	if (draw_imagewide_reference) {
		QPen pen;
		pen.setColor(QColor(255,0,0,128));
		pen.setStyle(Qt::SolidLine);
		painter.setPen(pen);
		painter.drawLine(ref_x,0,ref_x,this->height());
		painter.drawLine(0,ref_y,this->width(),ref_y);
	}

	// externally supplied point list
	if (draw_point_list.size() > 0) {
		QPen pen;
		pen.setColor(QColor(255,255,0,255));
		pen.setStyle(Qt::DashLine);
		//painter.setPen(QColor(255,255,0,255));
		painter.setPen(pen);

		//cout<<"drawing "<<draw_point_list.size()<<" points"<<endl;
		for (i=0; i<draw_point_list.size(); i++) 
			painter.drawPoint(draw_point_list[i].x, draw_point_list[i].y);
		
	}

	// levels calculated by itself
	if (level_point_list.size() > 0) {
		
		QPen pen;
		pen.setColor(QColor(255,0,0,255));
		pen.setStyle(Qt::DashLine);
		painter.setPen(pen);

		for (i=0; i<level_point_list.size(); i++) 
			painter.drawPoint(draw_point_list[i].x, draw_point_list[i].y);
		
	}

	if (drawn_rects.size() > 0) {
		QPen pen;
		pen.setColor(QColor(255,128,0,255));
		pen.setStyle(Qt::DashLine);
		pen.setWidthF(.2);
		painter.setPen(pen);
		
		for (unsigned int i = 0; i < drawn_rects.size(); i++) {
			painter.drawPolyline(drawn_rects[i]);
		}
	}




}




void 
imgLabel::set_imagewide_cursor(bool status)	// cursore con estensioni su tutta l'immagine
{
	draw_imagewide_cursor = status;
	update();
}

void 
imgLabel::set_rowgraph(bool status)		// grafico delle intensita' sulla linea
{
	draw_rowgraph = status;
	update();
}

void 
imgLabel::set_colgraph(bool status)		// stessa cosa sulla colonna
{
	draw_colgraph = status;
	update();
}
	
void 
imgLabel::set_cursor_position(int x, int y)
{
	cursor_x = x;
	cursor_y = y;
	update();
}

void
imgLabel::drawGraph_state(int state)
{
	//std::cout<<"state: "<<state<<std::endl;
	if (state==0) {
		
	} else if (state==2) {
		//QwtPlot *horiz_plot;
		//horiz_plot = new QwtPlot("Horizontal", this, "cippa");
		
	}
}
