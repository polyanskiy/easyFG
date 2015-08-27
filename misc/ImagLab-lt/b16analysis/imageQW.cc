#include "imageQW.h"
#include "colormaps.h"


imageQW *imageQW::the_imageQW = 0;

/**************************************** costruzione wid ******************************************/

imageQW::imageQW() {
	class_init();

	setMinimumSize(370,200);
	setMaximumSize(1000,1000);
	init_variables();
	create_menus();
	create_canvas();
	create_buttons();
	create_plots();

	
	my_bitmap = new physImage();

	build_colormap();
}


imageQW::~imageQW()
{}

void
imageQW::closeEvent(QCloseEvent *event)
{
	std::cout<<"[close]"<<std::endl;
	emit(close_all_windows());

}

void
imageQW::init_variables(void)
{
	image_scale_isset = false;
	my_image_scale = 0;
	
	pulse_energy_isset = false;
	my_pulse_energy = 0;

	camera_calibration_isset = true;
	my_camera_calibration = __joule_per_count_800nm;

	origin_isset = false;
	origin_x = 0;
	origin_y = 0;


	horiz_plot_isset = false;
	vert_plot_isset = false;

}

// menus
void
imageQW::create_menus(void) {
	QMenuBar *menuBar = new QMenuBar(this);
	QMenu *fileMenu = new QMenu();
	QMenu *viewMenu = new QMenu();
	QMenu *analyzeMenu = new QMenu();
	QMenu *helpMenu = new QMenu();
	QMenu *spectroMenu = new QMenu();

	
	// FILE MENU ------------------------------------------------------------------------
	fileMenu = menuBar->addMenu("File");

	// open file
	QAction *openFile_act = new QAction("&Open",this);
	openFile_act->setShortcut(QKeySequence(Qt::CTRL+0x4F));
	fileMenu->addAction(openFile_act);
	connect(openFile_act, SIGNAL(triggered()), SLOT(loadfile()));

	QAction *saveFile_act = new QAction("&Save",this);
	fileMenu->addAction(saveFile_act);
	connect(saveFile_act, SIGNAL(triggered()), SLOT(savefile()));

	//QAction *saveFile8_act = new QAction("&Save 8bit",this);
	//fileMenu->addAction(saveFile8_act);
	//connect(saveFile8_act, SIGNAL(triggered()), SLOT(savefile8()));

	fileMenu->addSeparator();
	QAction *watchFolder_act = new QAction("Watch Folder",this);
	fileMenu->addAction(watchFolder_act);
	connect(watchFolder_act, SIGNAL(triggered()), SLOT(watchFolder()));
	
	
	fileMenu->addSeparator();
	
	// quit
	QAction *quit_act = new QAction("&Exit",this);
	quit_act->setShortcut(QKeySequence(Qt::CTRL+0x51));
	fileMenu->addAction(quit_act);
	connect(quit_act, SIGNAL(triggered()), SLOT(close()));
	
	// VIEW MENU	
	viewMenu = menuBar->addMenu("View");

	// image visualisation parameters
	QAction *enable_contrast_act = new QAction("Bright/Contrast",this);
	viewMenu->addAction(enable_contrast_act);
	connect(enable_contrast_act, SIGNAL(triggered()), SLOT( askContrast() ));
	
	// enable/disable plots
	QAction *enable_plots_act = new QAction("H-V Plots",this);
	enable_plots_act->setShortcut(QKeySequence(Qt::CTRL+0x48));	// probabilmente sbagliato
	viewMenu->addAction(enable_plots_act);
	connect(enable_plots_act, SIGNAL(triggered()), SLOT( enable_hv_plots_slot() ));

	// set origin
	QAction *set_origin_act = new QAction("Set Origin",this);
	set_origin_act->setShortcut(tr("r"));	// probabilmente sbagliato
	viewMenu->addAction(set_origin_act);
	connect(set_origin_act, SIGNAL(triggered()), SLOT( set_origin_slot() ));
	
	// set origin
	QAction *set_cursor_shape_act = new QAction("Cursor Shape",this);
	set_cursor_shape_act->setShortcut(tr("s"));	// probabilmente sbagliato
	viewMenu->addAction(set_cursor_shape_act);
	connect(set_cursor_shape_act, SIGNAL(triggered()), SLOT( toggle_cursor_shape() ));
	
	// toggle colormap
	QAction *toggle_color_act = new QAction("Toggle Color",this);
	toggle_color_act->setShortcut(tr("c"));
	viewMenu->addAction(toggle_color_act);
	connect(toggle_color_act, SIGNAL(triggered()), SLOT( toggle_color_slot() ));
	
	
	// ANALYZE MENU ------------------------------------------------------------------------
	analyzeMenu = menuBar->addMenu("Analyze");


	// set scale
	QAction *askScale_act = new QAction("set &Scale",this);
	analyzeMenu->addAction(askScale_act);
	connect(askScale_act, SIGNAL(triggered()), SLOT(askImageScale()));

	// set energy
	QAction *askEnergy_act = new QAction("set &Pulse Energy",this);
	analyzeMenu->addAction(askEnergy_act);
	connect(askEnergy_act, SIGNAL(triggered()), SLOT(askEnergy()));

	// set CCD calibration
	QAction *askCalibration_act = new QAction("set &CCD Calib",this);
	analyzeMenu->addAction(askCalibration_act);
	connect(askCalibration_act, SIGNAL(triggered()), SLOT(askCalibration()));

	////////////////////////////
	analyzeMenu->addSeparator();

	QAction *openBackFile_act = new QAction("Subtract image...",this);
	analyzeMenu->addAction(openBackFile_act);
	connect(openBackFile_act, SIGNAL(triggered()), SLOT(loadbackfile()));

	QAction *openDivideFile_act = new QAction("Divide by...",this);
	openDivideFile_act->setShortcut(QKeySequence(Qt::CTRL+0x44));
	analyzeMenu->addAction(openDivideFile_act);
	connect(openDivideFile_act, SIGNAL(triggered()), SLOT(loaddividefile()));


	QAction *thresIntegrate_act = new QAction("T&hreshold integrate",this);
	analyzeMenu->addAction(thresIntegrate_act);
	connect(thresIntegrate_act, SIGNAL(triggered()), SLOT(threshold_integrate_menu()));


	////////////////////////////
	analyzeMenu->addSeparator();
	
	QAction *selectPoints_act = new QAction("Select points on image",this);
	analyzeMenu->addAction(selectPoints_act);
	connect(selectPoints_act, SIGNAL(triggered()), SLOT(selectPoints_menu()));


	// HELP MENU ---------------------------------------------------------------------------
	helpMenu = menuBar->addMenu("Help");
	QAction *about_act = new QAction("About...",this);
	helpMenu->addAction(about_act);
	connect(about_act, SIGNAL(triggered()), SLOT(about_box()));
		
}

void
imageQW::create_canvas() {

	// visualizzazione immagine
	central_lbl = new imgLabel(this);
	central_lbl->setMouseTracking(true);
	central_lbl->setGeometry(80,25,300,175);
	central_lbl->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	central_lbl->setText("(no image loaded)");
	
	central_pm = new QPixmap();

	connect(this,SIGNAL(reset_painter_on_image(void)),central_lbl,SLOT(resetPainter(void)));
	connect(this,SIGNAL(draw_points_on_image(imagePointList)),central_lbl,SLOT(draw_points_on_image(imagePointList)));
	connect(this, SIGNAL(add_rect_on_image(QPolygonF)), central_lbl, SLOT(add_rect_on_image(QPolygonF)));

	// info e coordinate (a sx)
	left_info_lbl = new QLabel(this);
	left_info_lbl->setGeometry(0,25,80,70);
	left_info_lbl->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	left_info_lbl->setFrameStyle(QFrame::Box);
	left_info_lbl->setFont(QFont("Verdana",8,-1,false));
	//left_info_lbl->setText("(--:--)\n--");
	

	connect(central_lbl,SIGNAL(mouse_moved_on_image(int,int)),this,SLOT(new_mouse_position_on_img(int,int)));
	connect(central_lbl, SIGNAL(mouse_moved_on_image(int, int)), this, SLOT(recalculate_graphs(int, int)));
	connect(this, SIGNAL(toggle_cursor_shape_sig()), central_lbl, SLOT(toggle_cursor_shape()));
	connect(central_lbl, SIGNAL(new_cursor_size(float)), this, SLOT(new_cursor_size(float)));

}

void 
imageQW::create_buttons(void)
{
	// attiva modalita' selezione (per ora non serve ad una pippa)
	//QPushButton *selection_pb;
	//selection_pb = new QPushButton(this);
	//selection_pb->setGeometry(0,75,25,25);

	//connect(selection_pb,SIGNAL(clicked()),this,SLOT(activate_selection_mode()));

	// attiva grafici riga-colonna
	QLabel *draw_graph_lbl = new QLabel(this);
	draw_graph_lbl->setText("h-v plots");
	draw_graph_lbl->setFont(QFont("Verdana",7,-1,false));
	draw_graph_lbl->setGeometry(0,105,50,25);

	QCheckBox *drawGraph_cb;
	QShortcut *enable_sc;
	enable_sc = new QShortcut(this);
	//enable_sc->setKey("t");

	drawGraph_cb = new QCheckBox(this);
	drawGraph_cb->setGeometry(45,109,15,15);

	connect(drawGraph_cb,SIGNAL(stateChanged(int)),this,SLOT(drawGraph_state(int)));
	//connect(enable_sc, SIGNAL(activated()), drawGraph_cb, SLOT(click()));
	connect(this, SIGNAL(enable_hv_plots()), drawGraph_cb, SLOT(click()));

	// zero level and check level
	QLabel *zero_level_lbl = new QLabel(this);
	zero_level_lbl->setText("zero level");
	zero_level_lbl->setFont(QFont("Verdana",7,-1,false));
	zero_level_lbl->setGeometry(0,130,70,20);

	
	betterQSpinBox *zero_level_sb;
	zero_level_sb = new betterQSpinBox(this);
	zero_level_sb->setGeometry(10,150,60,20);
	zero_level_sb->setRange(0,0);
	zero_level_sb->setValue(0);
	zero_level_sb->setSingleStep(10);


	QLabel *ch_level_lbl = new QLabel(this);
	ch_level_lbl->setText("check level");
	ch_level_lbl->setFont(QFont("Verdana",7,-1,false));
	ch_level_lbl->setGeometry(0,170,70,20);

	QDoubleSpinBox *ch_level_dsb;
	ch_level_dsb = new QDoubleSpinBox(this);
	ch_level_dsb->setGeometry(10,190,60,20);
	ch_level_dsb->setRange(0,1);
	ch_level_dsb->setDecimals(4);
	ch_level_dsb->setSingleStep(1e-1);
	ch_level_dsb->setValue(5e-1);

	zero_level = 0;
	th_level = .5;

	connect(zero_level_sb, SIGNAL(valueChanged(int)), this, SLOT(zero_level_changed(int)));
	connect(ch_level_dsb, SIGNAL(valueChanged(double)), this, SLOT(ch_level_changed(double)));
	connect(this, SIGNAL(new_image_minimum_value(int)), zero_level_sb, SLOT(setMinimum_slot(int)));
	connect(this, SIGNAL(new_image_maximum_value(int)), zero_level_sb, SLOT(setMaximum_slot(int)));
	connect(this, SIGNAL(new_image_minimum_value(int)), zero_level_sb, SLOT(setValue(int)));


	QPushButton *next_file, *prev_file;
	prev_file = new QPushButton(this);	
	next_file = new QPushButton(this);

	prev_file->setText("<");
	prev_file->setGeometry(10, 220, 25, 25);
	next_file->setText(">");
	next_file->setGeometry(42, 220, 25, 25);

	connect(prev_file, SIGNAL(clicked()), this, SLOT(loadPrevFile()));
	connect(next_file, SIGNAL(clicked()), this, SLOT(loadNextFile()));

		

}

void
imageQW::create_plots(void)
{
	std::cout<<"[create plots]"<<std::endl;
	plotWidget *horiz_plot, *vert_plot;
	horiz_plot = new plotWidget("Horizontal intensity");
	vert_plot = new plotWidget("Vertical intensity");

	horiz_plot->setWindowTitle("Horizontal Cut");
	vert_plot->setWindowTitle("Vertical Cut");

	horiz_plot->show();
	vert_plot->show();

	connect(this,SIGNAL(on_mouse_horizontal_section(double *, double *, int)),horiz_plot, SLOT(plot_data(double *, double *, int)));
	connect(this,SIGNAL(on_mouse_vertical_section(double *, double *, int)),vert_plot, SLOT(plot_data(double *, double *, int)));
	connect(this,SIGNAL(on_mouse_horizontal_section_marker(int)),horiz_plot, SLOT(plot_data_marker(int)));
	connect(this,SIGNAL(on_mouse_vertical_section_marker(int)),vert_plot, SLOT(plot_data_marker(int)));
	connect(this, SIGNAL(set_image_scale(double)), horiz_plot, SLOT(set_axis_scale(double)));
	connect(this, SIGNAL(set_image_scale(double)), vert_plot, SLOT(set_axis_scale(double)));
	connect(this, SIGNAL(unset_image_scale(void)), horiz_plot, SLOT(unset_axis_scale(void)));
	connect(this, SIGNAL(unset_image_scale(void)), vert_plot, SLOT(unset_axis_scale(void)));

	// cambio livelli da thIntegrateWindow, rimbalzato da imageQW
	connect(this, SIGNAL(zero_and_th_changed_signal(int, double)), horiz_plot, SLOT(draw_level_changed(int, double)));
	connect(this, SIGNAL(zero_and_th_changed_signal(int, double)), vert_plot, SLOT(draw_level_changed(int, double)));

	// muori
	connect(this, SIGNAL(close_all_windows(void)), horiz_plot, SLOT(close(void)));
	connect(this, SIGNAL(close_all_windows(void)), vert_plot, SLOT(close(void)));

	

}

void
imageQW::qlabel_refresh() {

}

/*void
imageQW::mouseMoveEvent(QMouseEvent *event)
{
	std::cout<<"event: "<<event->x()<<std::endl;
}*/

void
imageQW::mousePressEvent(QMouseEvent *event)
{
	// mettiamoci pure il drag&drop
	if (event->button() == Qt::RightButton) {
		QDrag *drag = new QDrag(this);
		QMimeData *mimeData = new QMimeData;
		
		mimeData->setText( last_filename );
		std::cout<<"Drag: "<<my_bitmap->filename<<std::endl;
		drag->setMimeData(mimeData);
		//drag->setPixmap(iconPixmap);
		
		Qt::DropAction dropAction = drag->exec();
	}


}

/*********************************************** slots ******************************************/

void
imageQW::loadfile() {

	my_bitmap = loadImage("Choose input file...",NULL);
	
	if (my_bitmap != NULL) {
		if (my_bitmap->filename != NULL)
			setWindowTitle(my_bitmap->filename);
	       	image_refresh();
	} 

}

void
imageQW::loadPrevFile(void)
{

	if ( (!(last_filename.isEmpty())) ) {
		QStringList filters;
   		filters << "*.sif" << "*.b16" << "*.pgm";
	   	last_dirname.setNameFilters(filters);
		last_dirname.setFilter(QDir::Files);
	   	last_dirname.setSorting(QDir::Name);

	   	QFileInfoList list = last_dirname.entryInfoList();

		for (int i=1; i<(list.size()); i++) {
			QFileInfo fileInfo = list.at(i);

			if (QString(last_dirname.absolutePath()+QString("/")+fileInfo.fileName()).compare(last_filename) == 0) {
				std::cout<<"prev filename: "<<list.at(i-1).fileName().toAscii().constData()<<std::endl;
				loadfile_ext(QString(last_dirname.absolutePath()+QString("/")+list.at(i-1).fileName()).toAscii().constData());
				break;
			}
		}
	}
}

void
imageQW::loadNextFile(void)
{
	if ( (!(last_filename.isEmpty())) ) {
		QStringList filters;
   		filters << "*.sif" << "*.b16" << "*.pgm";
	   	last_dirname.setNameFilters(filters);
		last_dirname.setFilter(QDir::Files);
	   	last_dirname.setSorting(QDir::Name);

	   	QFileInfoList list = last_dirname.entryInfoList();


		for (int i=0; i<(list.size()-1); i++) {
			QFileInfo fileInfo = list.at(i);


			if (QString(last_dirname.absolutePath()+QString("/")+fileInfo.fileName()).compare(last_filename) == 0) {
				std::cout<<"next filename: "<<list.at(i+1).fileName().toAscii().constData()<<std::endl;
				loadfile_ext(QString(last_dirname.absolutePath()+QString("/")+list.at(i+1).fileName()).toAscii().constData());
				break;
			}
		}
	}

}

void
imageQW::watchFolder(void)
{
	QString wdir = QFileDialog::getExistingDirectory(this, tr("Select Watch Directory"),
                                                 "/home",
                                                 QFileDialog::ShowDirsOnly
                                                 | QFileDialog::DontResolveSymlinks);
	if (!wdir.isEmpty()) {
		if (my_watch_folder != NULL)
			delete my_watch_folder;
	
		my_watch_folder = new QFileSystemWatcher(this);
		my_watch_folder->addPath(wdir);

		connect(my_watch_folder, SIGNAL(directoryChanged(QString)), this, SLOT(openLastFile(QString)));
	}
}

void
imageQW::openLastFile(QString path)
{
	QStringList filters;
   	filters << "*.sif" << "*.b16" ;
	
	QDir wdir(path);
	wdir.setNameFilters(filters);
	wdir.setSorting(QDir::Time | QDir::Reversed);
	QFileInfoList list = wdir.entryInfoList();
	if (list.size()>0)
		loadfile_ext(QString(wdir.absolutePath()+QString("/")+list.at(list.size()-1).fileName()).toAscii().constData());
}

// called by main.cc to refresh staff in the event of external loading
void
imageQW::loadfile_ext( const char *ext_filename) {
	my_bitmap = loadImage(NULL, ext_filename);
	
	if (my_bitmap->filename != NULL)
		setWindowTitle(my_bitmap->filename);

	if (my_bitmap != NULL)
	       	image_refresh();
}

void
imageQW::loadbackfile() {
	my_back_bitmap = loadImage("Choose background image...", NULL);
	my_bitmap->background_subtract(my_back_bitmap);
	my_bitmap->switch_to_aligned();
	//setWindowTitle(windowTitle().append(QString(" - background corrected")));

	image_refresh();

}

void
imageQW::loaddividefile() {
	physImage * my_divide_bitmap;
	my_divide_bitmap = loadImage("Choose image...", NULL);
	my_bitmap->divide_by_image(my_divide_bitmap);
	//my_bitmap->switch_to_aligned();	OBSOLETE

	image_refresh();

}

void
imageQW::savefile()
{
	QString filename;
	QFileDialog *my_QFileDialog;

	if (!my_bitmap->isValid())
		return;

	filename = my_QFileDialog->getSaveFileName(this, "Save to...", "untitled.pgm","Images (*.raw *.pgm *.bmp *.sif *.b16 *.fits);;All (*.*)");

	if (filename != NULL) {
		if (filename.indexOf(QString("pgm"),-4) != -1) {
			// per ora default su pgm5, che non ho voglia di sbattermi
			//my_bitmap->writePGM5(filename.toAscii().constData());
			my_bitmap->writePGM5(filename.toAscii().constData());
		} else if (filename.indexOf(QString("bmp"),-4) != -1) {
			physImage my_fc_bitmap(my_bitmap);
			my_fc_bitmap.fullContrast8bit();
			my_fc_bitmap.write(filename.toAscii().constData(), bmp);
		} else if (filename.indexOf(QString("raw"),-4) != -1) {
			my_bitmap->writeRAW(filename.toAscii().constData());
		} else if (filename.indexOf(QString("asc"),-4) != -1) {
			my_bitmap->writeASC(filename.toAscii().constData());
		} else {
			int ret = QMessageBox::warning(this, tr("save format"), QString("Not a valid format\nchoose between pgm, raw, asc"), QMessageBox::Ok);
		}
		
	}
}

physImage*
imageQW::loadImage(const char *window_title, const char *external_filename)
{

	QString filename;
	physImage *buffer;

	// no filename supplied, ask for one
	if (external_filename == NULL) {	
		QFileDialog *my_QFileDialog;
		my_QFileDialog = new QFileDialog();
		my_QFileDialog->setViewMode(QFileDialog::List);

		if (last_dirname.exists()) 
			filename = my_QFileDialog->getOpenFileName(this, window_title, last_dirname.absolutePath(), "Images (*.b16 *.sif *.pgm *.tif *.tiff *.bmp);;B16 Image (*.b16);;Andor SIF Image (*.sif);;All (*.*)");
		else 
			filename = my_QFileDialog->getOpenFileName(this, window_title, "~", "Images (*.b16 *.sif);;B16 Image (*.b16);;Andor SIF Image (*.sif);;All (*.*)");
	} else {
		// open external
		filename = QString(external_filename);
	}

	// build b16 img
	if (!filename.isEmpty()) {
		std::cout<<"[imageQW::loadfile] Opening "<<filename.toAscii().constData()<<std::endl;
		last_filename = QString(filename);
		last_dirname = QDir(filename); // orribile..
		last_dirname.cdUp();

		// capire che tipo di file
		if (filename.indexOf(QString("b16"),-4) != -1) {
			my_b16image = new b16img2(filename.toAscii().constData());
			//matrix_version buffer = new physImage(*my_b16image);
			buffer = (physImage *) my_b16image;
			//matrix_version delete my_b16image;
		} else if ((filename.indexOf(QString("sif"),-4) != -1)) {
			sifimg *my_sifimage = new sifimg(filename.toAscii().constData());
			//matrix_version buffer = new physImage(*my_sifimage);
			buffer = (physImage *) my_sifimage;
			//matrix_version delete my_sifimage;
		} else if ((filename.indexOf(QString("pgm"),-4) != -1)) {
			pgmimg *my_pgmimage = new pgmimg(filename.toAscii().constData());
			// matrix_version buffer = new physImage(*my_pgmimage);
			buffer = (physImage *) my_pgmimage;
			// matrix_version delete my_pgmimage;
//		} else if ((filename.indexOf(QString("tif"),-4) != -1) || (filename.indexOf(QString("tiff"),-5) != -1) ) {
//			tiffimg *my_tiffimage = new tiffimg(filename.toAscii().constData());
//			buffer = new physImage(*my_tiffimage);
//			delete my_tiffimage;
//		} else if ((filename.indexOf(QString("bmp"),-4) != -1)) {
//			bmpimg *my_bmpimage = new bmpimg(filename.toAscii().constData());
//			buffer = new physImage(*my_bmpimage);
//			delete my_bmpimage;
		} else
			return NULL;
		
		// v2. uso matrix aligned
		buffer->scanBrightness();
		low_visual = buffer->minimum_value;
		high_visual = buffer->maximum_value;
		//matrix_version buffer->switch_to_aligned();

		// c'e' un cazzo di buffer??
		std::cout<<"[loadImage] buffer: "<<buffer<<std::endl;
		buffer->filename = filename.toAscii().constData();

		return buffer;
		
	}

	return NULL;

}



void
imageQW::askImageScale(void)
{
	bool ok;


	double imageScale = QInputDialog::getDouble(this, tr("Set image scale"), tr("Image resolution [um/px]"), my_image_scale, 0, 2147483647, 5, &ok);
	
	if (ok) {
		if (imageScale>0) {
			emit set_image_scale(imageScale);
			my_image_scale = imageScale;
			image_scale_isset = true;
			std::cout<<"[imageScale] set image scale to "<<imageScale<<" um/px"<<std::endl;
		} else {
			// unset scale
			my_image_scale = 1;
			image_scale_isset = false;
			emit unset_image_scale();
		}
	}
}

void
imageQW::askEnergy(void)
{
	bool ok;
	double pulse_energy = QInputDialog::getDouble(this, tr("Set pulse energy"), tr("Energy per pulse [mJ]"), my_pulse_energy, 0, 2147483647, 3, &ok);
	
	if (ok) {
		if (pulse_energy>0) {
			emit set_pulse_energy(pulse_energy);
			my_pulse_energy = pulse_energy;
			pulse_energy_isset = true;
			std::cout<<"[imageScale] set pulse energy to "<<pulse_energy<<" mJ"<<std::endl;
		} else {
			// unset scale
			my_pulse_energy = 0;
			pulse_energy_isset = false;
			emit unset_pulse_energy();
		}
	}

}

void
imageQW::askCalibration(void)
{
	bool ok;
	//double camera_calibration = QInputDialog::getDouble(this, tr("Set CCD Calibration"), tr("Joule per count"), my_camera_calibration, 0, 2147483647, 5, &ok);
	double camera_calibration = QInputDialog::getText(this, tr("Set CCD Calibration"), tr("Joule per count\n (multiply by 10 for every OD)"), QLineEdit::Normal, QString("%1").arg(my_camera_calibration), &ok).toDouble(&ok);
	
	if (ok) {
		if (camera_calibration>0) {
			emit set_camera_calibration(camera_calibration);
			my_camera_calibration = camera_calibration;
			camera_calibration_isset = true;
			std::cout<<"[imageScale] set CCD calibration to "<<camera_calibration<<" J/count"<<std::endl;
		} else {
			// unset scale
			my_camera_calibration = 0;
			camera_calibration_isset = false;
			emit unset_camera_calibration();
		}
	} else {
		int ret = QMessageBox::warning(this, tr("set CCD Calibration"), QString("Not a valid calibration"), QMessageBox::Ok);
	}

}


void
imageQW::askContrast(void)
{
	imageView *myview;
	myview = new imageView();
	
	connect(this, SIGNAL(new_image_maximum_value(int)), myview, SLOT(setUpLimit(int)));
	connect(this, SIGNAL(new_image_minimum_value(int)), myview, SLOT(setLowLimit(int)));
	connect(this, SIGNAL(close_all_windows(void)), myview, SLOT(close(void)));
	connect(myview, SIGNAL(setImageVisualisationRange(int, int)), this, SLOT(setImageVisualisationRange(int, int)));

	if (my_bitmap != NULL) {
		myview->setUpLimit(my_bitmap->maximum_value);
		myview->setLowLimit(my_bitmap->minimum_value);
	}

	myview->show();
	
}

// -------------------------------------------------------------------------------------

void
imageQW::new_image_waiting(void)
{
	my_bitmap->scanBrightness();
	low_visual = my_bitmap->minimum_value;
	high_visual = my_bitmap->maximum_value;
	image_refresh();
	recalculate_graphs(mouse_position_x, mouse_position_y);
	new_mouse_position_on_img(mouse_position_x, mouse_position_y);
}

void
imageQW::set_new_image(physImage *ptr)
{
	my_bitmap = ptr;
	new_image_waiting();
}

void
imageQW::image_refresh(void) {

	if (my_bitmap == NULL) {
		std::cout<<"[image refresh]: NULL bitmap"<<std::endl;
		return;
	}

	emit reset_painter_on_image();


	//std::cout<<"[imageQW] called image_refresh()"<<std::endl;

	if (my_bitmap->img_buffer == NULL) {
		// non c'e' immagine, mettici la pezza nera
		std::cout<<"No image loaded: "<<my_bitmap->img_buffer<<std::endl;
	} else {
		QImage *my_QImage;
		// c'e'...
		//std::cout<<"E' qui che scazzi?? - 1"<<std::endl;
		
		// rev2 - l'aligned e' costruito direttamente in physImage
/*		*central_pm = QPixmap::fromImage(QImage(\
					(const unsigned char *)my_bitmap->ailigned_buffer(),\
					my_bitmap->width,\
					my_bitmap->height,\
					QImage::Format_RGB32) );*/
	
		//my_bitmap->scanBrightness();	// certamente ridondante, trovare perche' scazza in mod. PCO
		//my_bitmap->sync_to_8bit(30,800);
		my_bitmap->sync_to_8bit(low_visual, high_visual);
		
		my_QImage = new	QImage(\
					my_bitmap->cont_8bit_img_buffer,\
					my_bitmap->width,\
					my_bitmap->height,\
					my_bitmap->width,\
					QImage::Format_Indexed8);

		// color map selection
		if (use_graymap)
			my_QImage->setColorTable(gray_colormap);
		else
			my_QImage->setColorTable(def_colormap);
		
		*central_pm = QPixmap::fromImage(*my_QImage);

		/* *central_pm = QPixmap::fromImage(QImage(\
					my_bitmap->cont_8bit_img_buffer,\
					my_bitmap->width,\
					my_bitmap->height,\
					QImage::Format_Indexed8) );*/


		/* *central_pm = QPixmap::fromImage(QImage(\
					(const unsigned char *)my_bitmap->fullContrast8bit_buffer(),\
					my_bitmap->width,\
					my_bitmap->height,\
					QImage::Format_Indexed8) );*/

		// schifezzaq temporanea
		//std::cout<<"E' qui che scazzi?? - 2"<<std::endl;

		if (central_pm->isNull()) central_lbl->setText("cazzo di pixmap nullo...");
		else {
			this->setMaximumSize(QSize(my_bitmap->width+70, my_bitmap->height+25));
			this->resize(my_bitmap->width+70, my_bitmap->height+25);
			central_lbl->setMaximumSize(QSize(my_bitmap->width, my_bitmap->height));
			central_lbl->resize(my_bitmap->width, my_bitmap->height);
			central_lbl->setPixmap(*central_pm);
		}
		//central_lbl->setText("qui dovrei vedere una cazzo di immagine...");
		
		emit new_img_loaded(my_bitmap);
		emit new_image_minimum_value(my_bitmap->minimum_value);
		emit new_image_maximum_value(my_bitmap->maximum_value);
	}
}


void
imageQW::new_mouse_position_on_img(int x, int y)
{
	mouse_position_x = x;
	mouse_position_y = y;
	
	if (!central_pm->isNull()) {
		if (x>0 && x<my_bitmap->width && y>0 && y<my_bitmap->height) {
			int pixel_value = my_bitmap->img_buffer[y][x];

			QString lbl_text =  QString("(%1:%2)\n%3").arg(x).arg(y).arg(pixel_value);

			if (origin_isset || image_scale_isset) {
				if (image_scale_isset)
					lbl_text.append(QString("\n[dx=%1\ndy=%2\ndr=%3] um").arg((x-origin_x)*my_image_scale).arg((y-origin_y)*my_image_scale).arg(my_image_scale*bidimvec<float>(x-origin_x, y-origin_y).mod()));
				else
					lbl_text.append(QString("\n[dx=%1\ndy=%2\ndr=%3]").arg(x-origin_x).arg(y-origin_y).arg(bidimvec<float>(x-origin_x, y-origin_y).mod()));

			}
			
			left_info_lbl->setText( lbl_text );
		} else {
			left_info_lbl->setText("(--:--)");
		}
	}
}

void
imageQW::drawGraph_state(int state)
{
	if (state ==  Qt::Unchecked) {
		horiz_plot_isset = false;
		vert_plot_isset = false;
	} else if (state == Qt::Checked) {
		horiz_plot_isset = true;
		vert_plot_isset = true;
	}
}

void
imageQW::set_origin_slot(void)
{
	if (origin_isset)
	{
		origin_isset = false;
		origin_x=0; origin_y=0;
		central_lbl->toggle_origin_plot(false);
		central_lbl->update();
	} else {
		origin_isset = true;
		origin_x = mouse_position_x;
		origin_y = mouse_position_y;
		central_lbl->toggle_origin_plot(true);
		central_lbl->set_origin_point(origin_x, origin_y);
		central_lbl->update();
	}
}

void
imageQW::toggle_color_slot(void)
{
	use_graymap = !use_graymap;
	image_refresh();
}

void
imageQW::toggle_cursor_shape(void)
{
	emit toggle_cursor_shape_sig();
	central_lbl->update();
}

void
imageQW::new_cursor_size(float size)
{
	QString stext;
	stext = QString("[imageQW] Cursor size: %1").arg(size*my_image_scale);
	if (image_scale_isset) 
		stext.append("um");
	cout<<stext.toAscii().constData()<<endl;
}

void
imageQW::activate_selection_mode(void)
{
	current_selection = new imgSelection();
	connect(central_lbl,SIGNAL(mouse_press(int,int)),current_selection,SLOT(set_new_upper_left(int,int)));
	connect(central_lbl,SIGNAL(mouse_release(int,int)),current_selection,SLOT(set_new_lower_right(int,int)));

	connect (central_lbl, SIGNAL(mouse_moved_on_image(int,int)), current_selection, SLOT(mouse_moved_in_selection(int,int)));
	connect (current_selection, SIGNAL(selection_coords(int,int,int,int)), central_lbl, SLOT(set_selection_rect(int,int,int,int)));
}



void
imageQW::threshold_integrate_menu(void)
{
	if (my_bitmap->isValid()) {
		std::cout<<"image integrate with thresholds"<<std::endl;
		thIntegrate_window *int_win;
		int_win = new thIntegrate_window(my_bitmap);

		// definizioni energia
		connect(this, SIGNAL(set_camera_calibration(double)), int_win, SLOT(get_camera_calibration(double)));
		emit(set_camera_calibration(my_camera_calibration));

		// unico segnale utile: il disegno dei punti
		connect(int_win, SIGNAL(draw_points_on_image(imagePointList)), central_lbl, SLOT(draw_points_on_image(imagePointList)));

		// rev2
		//connect(this, SIGNAL(new_img_loaded(b16img *)), int_win, SLOT(img_buffer_update(b16img *)));
		connect(this, SIGNAL(new_img_loaded(physImage *)), int_win, SLOT(img_buffer_update(physImage *)));


		connect(int_win, SIGNAL(zero_and_th_changed(int, double)), this, SLOT(zero_and_th_changed_slot(int, double)));
		connect(this, SIGNAL(close_all_windows(void)), int_win, SLOT(close(void)));

		int_win->show();
	} else {
		int ret = QMessageBox::critical(this,"Porca paletta","Integrate what?\n?",QMessageBox::Ok);
	}
}

void
imageQW::zero_and_th_changed_slot(int z_level, double thres)
{ emit zero_and_th_changed_signal(z_level, thres); }

void
imageQW::zero_level_changed(int new_zero_level)
{ zero_level = new_zero_level; emit zero_and_th_changed_signal(zero_level, th_level); }

void
imageQW::ch_level_changed(double new_ch_level)
{ th_level = new_ch_level; emit zero_and_th_changed_signal(zero_level, th_level); }

void 
imageQW::setImageVisualisationRange(int low, int high)
{
	low_visual = low;
	high_visual = high;

	image_refresh();
}


// recalculates intensity graphs on image to be sent to plotting section
void
imageQW::recalculate_graphs(int x, int y)
{
	int i;

	// set to 1 and disable label
	if (!image_scale_isset) my_image_scale = 1;

	// horiz
	if ( y>0 && y<my_bitmap->height && horiz_plot_isset) {
		static double *counter = new double [my_bitmap->width];
		static double *horiz_section = new double [my_bitmap->width];
		for (i=0; i<my_bitmap->width; i++) {
			counter[i] = i*my_image_scale;
			horiz_section[i] = my_bitmap->img_buffer[y][i];
		}
		emit on_mouse_horizontal_section(counter, horiz_section, my_bitmap->width);
		emit on_mouse_horizontal_section_marker(x);
		//std::cout<<"horiz recalculation"<<std::endl;
	}
	// vert
	if ( x>0 && x<my_bitmap->width && vert_plot_isset) {
		static double *counter = new double [my_bitmap->height];
		static double *vertical_section = new double [my_bitmap->height];
		for (i=0; i<my_bitmap->height; i++) {
			counter[i] = i*my_image_scale;
			vertical_section[i] = my_bitmap->img_buffer[i][x];
		}
		emit on_mouse_vertical_section(counter, vertical_section, my_bitmap->height);
		emit on_mouse_vertical_section_marker(y);
		//std::cout<<"horiz recalculation"<<std::endl;
	}

}

void
imageQW::selectPoints_menu(void)
{
	selectPoints *my_sP_win;
	my_sP_win = new selectPoints();

	connect(central_lbl, SIGNAL(mouse_press(int,int)), my_sP_win, SLOT(mouse_clicked_on_image(int,int)));
	connect(my_sP_win, SIGNAL(add_point_on_image(imagePointList)), central_lbl, SLOT(draw_points_on_image(imagePointList)));
	connect(this, SIGNAL(close_all_windows(void)), my_sP_win, SLOT(close(void)));

	my_sP_win->show();

}

void
imageQW::about_box(void)
{
	// devo trovare il modo di metterlo statico
	//QPixmap *logo = new QPixmap("logo.png");
	QPixmap *logo = new QPixmap(static_logo);

	QMessageBox *about_box = new QMessageBox(this);
	QLabel *logo_box = new QLabel(about_box);
	logo_box->setPixmap(*logo);

	about_box->setText(tr("<b>B16 Image analyzer Lite</b>,<br><br><br><br><br><br> without any claim of completeness <br>but better described as a dirty bunch of <br>C++ lines solving experimental<br> emergencies...<br><br>(C) 2007-2010 Alessandro Flacco<br>alessandro.flacco@polytechnique.edu"));

	logo_box->setGeometry(70,42,300,60);

	about_box->exec();

}
/***************************************************************************************************/




