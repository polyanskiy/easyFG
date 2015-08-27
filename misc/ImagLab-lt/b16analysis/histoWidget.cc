#include "histoWidget.h"


histoWidget::histoWidget(const char *name) 
 : data_isset(false) {
	setMinimumSize(400,400);
	init_variables();
	
	myPlot = new QwtPlot(QwtText(name), this);
	myPlot->setMinimumSize(400,400);
	myPlot->setAxisTitle(QwtPlot::xBottom, QString("distance [px]"));
	myPlot->setAxisTitle(QwtPlot::yLeft, QString("intensity [counts]"));

	QwtTextLabel *graph_label;
	graph_label = new QwtTextLabel(myPlot);
	graph_label->setGeometry(75,20,350,50);
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

	level_marker_center = new QwtPlotMarker();
	level_marker_center->setLineStyle(QwtPlotMarker::NoLine);
	marker_symbol.setStyle(QwtSymbol::Diamond);
	level_marker_center->setSymbol(marker_symbol);
	level_marker_center->attach(myPlot);


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
histoWidget::init_variables(void)
{
	draw_level_isset = true;
	my_zero_level = 0;
	my_thres = .5;
	my_plot_scale = 1;

	plot_unit = new QString("[px]");
	check_points = new int[128];
}

void
histoWidget::plot_data(double *x, double *y, int length)
{
	curve1->attach(myPlot);
	curve1->setData(x,y,length);
	data_isset = true;
	draw_level();
	myPlot->replot();
}

void
histoWidget::plot_data_marker(int position)
{
	position_marker->setXValue(my_plot_scale*(double)position);
	myPlot->replot();
}


// slots
void
histoWidget::set_axis_scale(double scale, QString m_unit)
{
	if (scale > 0) 
		myPlot->setAxisTitle(QwtPlot::xBottom, m_unit);
	plot_unit = new QString(m_unit);
	my_plot_scale = scale;
	myPlot->replot();
	
}

void
histoWidget::unset_axis_scale(void)
{
	myPlot->setAxisTitle(QwtPlot::xBottom, QString("distance [px]"));
	plot_unit = new QString("[px]");
	my_plot_scale = 1;
	myPlot->replot();

}

void
histoWidget::draw_level_changed(int zero_level, double threshold)
{
	my_zero_level = zero_level;
	my_thres = threshold;
	//std::cerr<<"qui, cosa cazzo ci sei entrato a fare??"<<std::endl;
	if (data_isset) draw_level();
}

void
histoWidget::draw_level(void)
{
	int max_i = find_max(curve1->data());
	double max_val = curve1->y(max_i);
	double check_level = ((double)max_val-(double)my_zero_level)*my_thres+my_zero_level;
	bool start_state, cur_state;
	int left_i = curve1->dataSize()+1, right_i = 0, center_i;
	int i;


	std::cout<<"check level: "<<check_level<<std::endl;

	// marker from the left
	i=0;
	start_state = (curve1->y(0) > check_level);
	cur_state = start_state;

	while ((start_state == cur_state) && (i<curve1->dataSize())) {
		cur_state = (curve1->y(i) > check_level);
		i++;
	}
	left_i = i-1;

	// second marker from the left
	i=left_i+1;
	start_state = (curve1->y(i) > check_level);
	cur_state = start_state;

	while ((start_state == cur_state) && (i<curve1->dataSize())) {
		cur_state = (curve1->y(i) > check_level);
		i++;
	}
	center_i = i-1;

	// marker from the right
	i=curve1->dataSize()-1;
	start_state = (curve1->y(i) > check_level);
	cur_state = start_state;

	while ((start_state == cur_state) && (i<curve1->dataSize())) {
		cur_state = (curve1->y(i) > check_level);
		i--;
	}
	right_i = i+1;



	//std::cout<<"left: "<<left_i<<", right: "<<right_i<<std::endl;
	emit(graph_label_update( QwtText( QString("left = %1, center = %2, right = %3 ").arg(curve1->x(left_i)*my_plot_scale).arg(curve1->x(center_i)*my_plot_scale).arg(curve1->x(right_i)*my_plot_scale).append(*plot_unit) ) ) );

	level_marker_left->setXValue((double)curve1->x(left_i)*my_plot_scale);
	level_marker_left->setYValue(check_level);
	
	level_marker_center->setXValue((double)curve1->x(center_i)*my_plot_scale);
	level_marker_center->setYValue(check_level);

	level_marker_right->setXValue((double)curve1->x(right_i)*my_plot_scale);
	level_marker_right->setYValue(check_level);

	zero_level_marker->setYValue(my_zero_level);
	
	myPlot->replot();

}

void
histoWidget::draw_level_set(bool)
{}

//////////////// external functions /////////////////////
int 
histoWidget::find_max(QwtData &data)
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
