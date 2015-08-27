#include <iostream>
#include <sstream>
#include <cmath>
#include <string>

#include <QObject>
#include <QAction>
#include <QWidget>
#include <QMenu>
#include <QMenuBar>
#include <QtGui>
#include <QDir>
#include <QFileDialog>
#include <QMessageBox>
#include <QSlider>
#include <QInputDialog>
#include <QShortcut>
#include <QFileSystemWatcher>

#include <QImage>
#include <QPixmap>
#include <QPolygonF>

#include <QMouseEvent>
#include <QDrag>

// oggetto b16
//#include "b16img.h"

// label con movimenti mouse
#include "imgLabel.h"
#include "imgSelection.h"
#include "thIntegrate_window.h"
#include "selectPoints.h"
#include "plotWidget.h"


// paccottiglissima
#include "betterQSpinBox.h"
#include "imageView.h"

// rev2
//#include "../b16tools/b16img.h"
#include "physImage.h"
#include "b16img2.h"
#include "sifimg.h"
#include "pgmimg.h"
#include "tiffimg.h"
#include "bmpimg.h"

// static images
#include "statics.h"

// definitions
#include "defs.h"

#include "bidimvec.h"


#ifndef __imageQW_h
#define __imageQW_h

#define __dmsg(X) std::cerr<<"check: "<<X<<std::endl;


class QIonTraj;

class imageQW : public QWidget 
{
	Q_OBJECT
public:
	imageQW();

	//imageQW(physImage *); teoricamente non chiamato piu' da nessuno...
	~imageQW();

	static imageQW *the_imageQW; // init static pointer
	void class_init(void)
	{ the_imageQW = this; my_watch_folder = NULL; }

	double get_image_scale(void)
	{ while (!image_scale_isset) askImageScale(); return my_image_scale; }

	int imgWidth(void)
	{ return (my_bitmap == NULL) ? 0 : my_bitmap->width; }
	int imgHeight(void)
	{ return (my_bitmap == NULL) ? 0 : my_bitmap->height; }

	QRect imgLabelGeometry()
	{ return central_lbl->geometry(); }
	imgLabel *theImgLabel(void)
	{ return central_lbl; }
private:
	void closeEvent(QCloseEvent *);
	void init_variables(void);
	void create_menus(void);
	void create_canvas(void);
	void create_buttons(void);
	void create_plots(void);

	// dovrei creare una superclasse img per i metodi comuni
	// rev2
	//b16img *my_bitmap, *my_back_bitmap;
	
	b16img2 *my_b16image;
	physImage *my_bitmap, *my_back_bitmap;

	int mouse_position_x, mouse_position_y;
	bool origin_isset;
	int origin_x, origin_y;
	int low_visual, high_visual;

	//void mouseMoveEvent(QMouseEvent *);
	void mousePressEvent(QMouseEvent *);


private:
	void image_refresh(void);
	physImage * loadImage(const char *, const char *);

	QString last_filename;
	QDir last_dirname;
	QFileSystemWatcher *my_watch_folder;
	
	imgLabel *central_lbl;
	QPixmap *central_pm;
	QLabel *left_info_lbl;

	// tools
	imgSelection *current_selection;

	// values
	bool image_scale_isset;
	double my_image_scale;

	bool pulse_energy_isset;
	double my_pulse_energy;

	bool camera_calibration_isset;
	double my_camera_calibration;

	bool horiz_plot_isset, vert_plot_isset, histo_plot_isset;

	int zero_level;
	double th_level;

	bool use_graymap;


public slots:
	// functions to be integrated in scripting system
	void loadfile_ext(const char *);
	void loadfile(void);
	void loadNextFile(void);
	void loadPrevFile(void);

private slots:
	void watchFolder(void);
	void openLastFile(QString);
	void savefile(void);
	void loadbackfile(void);
	void loaddividefile(void);

	void zero_level_changed(int);
	void ch_level_changed(double);

	void qlabel_refresh(void);
	void new_mouse_position_on_img(int, int);
	void activate_selection_mode(void);
	void toggle_cursor_shape(void);
	void new_cursor_size(float);

	void askImageScale(void);
	void askEnergy(void);
	void askCalibration(void);
	void askContrast(void);


	void about_box(void);

	void drawGraph_state(int);

	// actions
	void threshold_integrate_menu(void);
	void selectPoints_menu(void);
	void recalculate_graphs(int, int);
	void zero_and_th_changed_slot(int, double); // rimbalzo di segnale
	void setImageVisualisationRange(int, int);

	void new_image_waiting(void);
	void set_new_image(physImage *);

	// MIRROR slots ----------------------------------------------------------
	void enable_hv_plots_slot(void)
	{ emit enable_hv_plots(); }

	void set_imageRotation_slot(double ival)
	{ emit set_image_rotation(ival); }

	void set_origin_slot(void);
	void toggle_color_slot(void);

	

signals:

	// general
	void close_all_windows(void);

	void reset_painter_on_image(void);
	
	// rev2
	//void new_img_loaded(b16img *);
	void new_img_loaded(physImage *);

	void on_mouse_horizontal_section(double *, double *, int);
	void on_mouse_vertical_section(double *, double *, int);
	void on_mouse_horizontal_section_marker(int);
	void on_mouse_vertical_section_marker(int);

	void set_image_scale(double);
	void unset_image_scale(void);

	void set_pulse_energy(double);
	void unset_pulse_energy(void);

	void set_camera_calibration(double);
	void unset_camera_calibration(void);

	void set_image_rotation(double);

	void zero_and_th_changed_signal(int, double);

	void new_image_maximum_value(int);
	void new_image_minimum_value(int);

	void draw_points_on_image(imagePointList);
	void add_rect_on_image(QPolygonF);


	// signals from MIRROR SLOTS 
	void enable_hv_plots(void);

	void toggle_cursor_shape_sig(void);



};


#endif

