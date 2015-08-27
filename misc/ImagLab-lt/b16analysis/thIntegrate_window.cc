#include "thIntegrate_window.h"


//thIntegrate_window::thIntegrate_window(QWidget *parent, b16img *main_img)
//	: QWidget(parent)

// rev2 thIntegrate_window::thIntegrate_window(b16img *main_img)
thIntegrate_window::thIntegrate_window(physImage *main_img)
{
	my_img = main_img;
	create_paccottiglia();
}

void
thIntegrate_window::create_paccottiglia(void)
{
	QLabel *left_lbl, *down_result_lbl, *down_energy_lbl;
	QDoubleSpinBox *th_level_dsb;
	QSpinBox *zero_level_sb;
	QPushButton *calculate_pb;

	left_lbl = new QLabel(this);
	left_lbl->setFont(QFont("Verdana",8,-1,false));
	left_lbl->setGeometry(10,10,160,70);
	left_lbl->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
	left_lbl->setText(QString(tr("Threshold level [0->1]:\n\n\nBackground Level[0->%1]:")).arg(my_img->maximum_value));

	down_result_lbl = new QLabel(this);
	down_result_lbl->setGeometry(10,180, 200, 40);
	down_result_lbl->setText("(undefined)");
	down_result_lbl->setFont(QFont("Verdana",8,-1,false));

	down_energy_lbl = new QLabel(this);
	down_energy_lbl->setGeometry(10,220, 200, 20);
	down_energy_lbl->setText("--");
	connect(this, SIGNAL(set_integrated_energy_text(QString)), down_energy_lbl, SLOT(setText(QString)));



	th_level_dsb = new QDoubleSpinBox(this);
	th_level_dsb->setGeometry(110,35,100,20);
	th_level_dsb->setRange(0,1);
	th_level_dsb->setDecimals(4);
	th_level_dsb->setSingleStep(1e-1);
	th_level_dsb->setValue(5e-1);
	threshold = 5e-1;

	zero_level_sb = new QSpinBox(this);
	zero_level_sb->setGeometry(110,80,100,20);
	zero_level_sb->setRange(0,my_img->maximum_value);
	zero_level_sb->setValue(my_img->minimum_value);
	zero_level_sb->setSingleStep(10);
	zero_level = my_img->minimum_value;

	calculate_pb = new QPushButton(this);
	calculate_pb->setGeometry(10,110,100,20);
	calculate_pb->setText("Calculate");



	connect(th_level_dsb,SIGNAL(valueChanged(double)),SLOT(threshold_changed(double)));
	connect(zero_level_sb,SIGNAL(valueChanged(int)),SLOT(zero_level_changed(int)));

	//connect(this,SIGNAL(calculate_integral_parameters(int, double)),this,SLOT(calculate_integral(int,double)));
	connect(calculate_pb,SIGNAL(clicked()),this,SLOT(calculate_integral(void)));

	connect(this, SIGNAL(result_text(QString)),down_result_lbl,SLOT(setText(QString)));

	connect(this, SIGNAL(set_zero_level(int)), zero_level_sb, SLOT(setValue(int)));
	connect(this, SIGNAL(set_threshold(double)), th_level_dsb, SLOT(setValue(double)));



	// init_variables
	camera_calibration = 0;

	
}

void
// rev2 thIntegrate_window::img_buffer_update(b16img *new_img)
thIntegrate_window::img_buffer_update(physImage *new_img)
{
	my_img = new_img;

	emit set_zero_level(my_img->minimum_value);
	emit (draw_points_on_image(my_img->contour_points(zero_level, 0.135)));
}

void 
thIntegrate_window::threshold_changed(double value)
{ 
	threshold = value;
	//emit(calculate_integral_parameters(zero_level, threshold));
	emit(zero_and_th_changed(zero_level, threshold));
	emit(calculate_integral());	// metodo molto piu' leggero
}

void 
thIntegrate_window::zero_level_changed(int value)
{ 
	zero_level = value;
	//emit(calculate_integral_parameters(zero_level, threshold));
	emit(zero_and_th_changed(zero_level, threshold));
	emit(calculate_integral());
}

void 
//thIntegrate_window::calculate_integral(int zlevel, double thold)
thIntegrate_window::calculate_integral(void)
{
	std::cout<<"calculate"<<std::endl;
	emit (draw_points_on_image(my_img->contour_points(zero_level, threshold)));
	
	// immagine piena
	//total_integral = my_img->integrateImage(1e-6,0,zero_level); 
	//partial_integral = my_img->integrateImage(1e-6, threshold, zero_level);

	// immagine decimata
	// rev2 b16img *dec_img;

	// da riscrittura integrazione a trapezioidi, elimino decimazione
	//physImage *dec_img;
	//dec_img = my_img->decimated_image(4);
	
	//imgLabel *integral_image_show;
	//integral_image_show = new imgLabel();
	

	//total_integral = dec_img->integrateImage(1e-6,0,zero_level); 
	//partial_integral = dec_img->integrateImage(1e-6, threshold, zero_level);
	
	total_integral = my_img->integrateImage(1e-6,0,zero_level); 
	partial_integral = my_img->integrateImage(1e-6, threshold, zero_level);
	
	emit (result_text( QString("Result: (%1/%2) \n%3%").arg(partial_integral).arg(total_integral).arg(partial_integral*100/total_integral) ));
	emit (image_integral(partial_integral/total_integral));

	update_energy();
}

void
thIntegrate_window::get_camera_calibration(double new_cc)
{
	camera_calibration = new_cc;
	update_energy();
}

void
thIntegrate_window::update_energy(void)
{
	double int_energy;
	//int_energy = (partial_integral/total_integral)*my_img->width*my_img->height*(my_img->maximum_value-zero_level)*camera_calibration;
	int_energy = partial_integral*camera_calibration;
	emit(set_integrated_energy(int_energy));
	emit(set_integrated_energy_text(QString("Energy: %1 [mJ]").arg(int_energy*1e3)));
}

