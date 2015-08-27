#include "plotWidget.h"


plotWidget::plotWidget(const char *name) 
{
	setMinimumSize(400,400);
	init_variables();
	
	myPlot = new QwtPlot(QwtText(name), this);
	myPlot->setMinimumSize(400,400);
	myPlot->setAxisTitle(QwtPlot::xBottom, QString("distance [px]"));
	myPlot->setAxisTitle(QwtPlot::yLeft, QString("intensity [counts]"));

	QwtTextLabel *graph_label;
	graph_label = new QwtTextLabel(myPlot);
	graph_label->setGeometry(250,20,120,50);
	//graph_label->setText("pippazza");
	//
	
	connect(this, SIGNAL(graph_label_update(QwtText )), graph_label, SLOT(setText(QwtText )));

	QPen marker_pen;
	marker_pen.setColor(QColor(255,0,0));

	QPen yellow_pen;
	yellow_pen.setColor(QColor(255,255,0));
	
	QwtSymbol marker_symbol;
	marker_symbol.setSize(10);

	position_marker = new QwtPlotMarker();
	position_marker->setLineStyle(QwtPlotMarker::VLine);
	position_marker->setLinePen(marker_pen);
	position_marker->attach(myPlot);

	level_marker_left = new QwtPlotMarker();
	level_marker_left->setLineStyle(QwtPlotMarker::NoLine);
	marker_symbol.setStyle(QwtSymbol::RTriangle);
	level_marker_left->setSymbol(marker_symbol);
	level_marker_left->attach(myPlot);


	level_marker_right = new QwtPlotMarker();
	level_marker_right->setLineStyle(QwtPlotMarker::NoLine);
	marker_symbol.setStyle(QwtSymbol::LTriangle);
	level_marker_right->setSymbol(marker_symbol);
	level_marker_right->attach(myPlot);

	zero_level_marker = new QwtPlotMarker();
	zero_level_marker->setLineStyle(QwtPlotMarker::HLine);
	zero_level_marker->setLinePen(yellow_pen);
	zero_level_marker->attach(myPlot);
	
	// add curves
	curve1 = new QwtPlotCurve("Curve 1");

}

void 
plotWidget::init_variables(void)
{
	draw_level_isset = true;
	my_zero_level = 0;
	my_thres = .5;
	my_plot_scale = 1;

	plot_unit = new QString("[px]");
}

void
plotWidget::plot_data(double *x, double *y, int length)
{
	curve1->attach(myPlot);
	curve1->setData(x,y,length);
	draw_level();
	myPlot->replot();
}

void
plotWidget::plot_data_marker(int position)
{
	position_marker->setXValue(my_plot_scale*(double)position);
	myPlot->replot();
}


// slots
void
plotWidget::set_axis_scale(double scale)
{
	if (scale > 0) 
		myPlot->setAxisTitle(QwtPlot::xBottom, QString("distance [um]"));
	plot_unit = new QString("[um]");
	my_plot_scale = scale;
	myPlot->replot();
	
}

void
plotWidget::unset_axis_scale(void)
{
	myPlot->setAxisTitle(QwtPlot::xBottom, QString("distance [px]"));
	plot_unit = new QString("[px]");
	my_plot_scale = 1;
	myPlot->replot();

}

void
plotWidget::draw_level_changed(int zero_level, double threshold)
{
	my_zero_level = zero_level;
	my_thres = threshold;
	draw_level();
}

void
plotWidget::draw_level(void)
{
	int max_i = find_max(curve1->data());
	double max_val = curve1->y(max_i);
	double check_level = ((double)max_val-(double)my_zero_level)*my_thres+my_zero_level;
	int left_i = curve1->dataSize()+1, right_i = 0;
	int i;

	
	i=0;
	while (i<curve1->dataSize()) {
		if (curve1->y(i) > check_level) 
			break;
		i++;
	}
	left_i = i;

	i=curve1->dataSize()-1;
	while (i > 0) {
		if (curve1->y(i) > check_level) 
			break;
		i--;
	}
	right_i = i;

	//std::cout<<"left: "<<left_i<<", right: "<<right_i<<std::endl;
	emit(graph_label_update( QwtText( QString("width = %1 ").arg( (right_i-left_i)*my_plot_scale ).append(*plot_unit) ) ) );

	level_marker_left->setXValue((double)left_i*my_plot_scale);
	level_marker_left->setYValue(check_level);
	
	level_marker_right->setXValue((double)right_i*my_plot_scale);
	level_marker_right->setYValue(check_level);

	zero_level_marker->setYValue(my_zero_level);
	
	myPlot->replot();

}

void
plotWidget::draw_level_set(bool)
{}

//////////////// external functions /////////////////////
int find_max(QwtData &data)
{
	int i, max_i;
	double max_y = data.y(0);
	max_i = 0;


	for (i=1; i<data.size(); i++)
		if (data.y(i) > max_y) {
			max_y = data.y(i);
			max_i = i;
		}

	return max_i;
}
