#include <QWidget>
#include <QPen>
#include <QMouseEvent>

#include <qwt_plot_curve.h>
#include <qwt_plot.h>
#include <qwt_text_label.h>
#include <qwt_plot_marker.h>
#include <qwt_symbol.h>

// ma porco cazzo
#include <assert.h>

#include <iostream>

#ifndef __histoWidget_h
#define __histoWidget_h

class histoWidget : public QWidget 
{
	Q_OBJECT
public:
	histoWidget(const char *);

protected:
	void resizeEvent(QResizeEvent *e) {
		//thePlot->resizeEvent(e);
		myPlot->setMinimumSize(QWidget::size());
		myPlot->setMaximumSize(QWidget::size());
	}

	void mousePressEvent(QMouseEvent *ev)
	{
		if (ev->button() == Qt::LeftButton) {
			QDrag *drag = new QDrag(this);
			QMimeData *mimeData = new QMimeData;
	
			if (curve1->dataSize() > 0) {	

				QString dump_data;
				for (int i=0; i<curve1->dataSize(); i++)
					dump_data.append(QString("%1\t%2\n").arg(curve1->x(i)).arg(curve1->y(i)));
				mimeData->setText(dump_data);
				drag->setMimeData(mimeData);
				Qt::DropAction dropAction = drag->exec();
			}

		}

	}


private:
	QwtPlot *myPlot;
	QwtPlotCurve *curve1;
	QwtPlotMarker *position_marker, *level_marker_left, *level_marker_right, *level_marker_center, *zero_level_marker;


	void init_variables(void);

	void draw_level(void);

	int find_max(QwtData &);

	// status
	bool draw_level_isset;
	bool data_isset;
	int my_zero_level;
	double my_thres;
	double my_plot_scale;

	QString *plot_unit;
	int *check_points;

public slots:
	void plot_data(double *, double *, int);
	void plot_data_marker(int);			// position marker
	void set_axis_scale(double,QString);
	void unset_axis_scale(void);
	void draw_level_changed(int, double);			// larghezza, passa threshold e level
	void draw_level_set(bool);				// se disegnare o no

signals:
	void graph_label_update(QwtText );
	void move_plot_marker(double);
};

#endif

