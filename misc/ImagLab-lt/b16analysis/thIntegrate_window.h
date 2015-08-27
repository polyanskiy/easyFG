#include <QObject>
#include <QAction>
#include <QWidget>
#include <QMenu>
#include <QMenuBar>
#include <QtGui>
#include <QFileDialog>
#include <QMessageBox>

#include <QSpinBox>
#include <QDoubleSpinBox>

#include <QImage>
#include <QPixmap>

#include <QMouseEvent>

#include <iostream>

// mmmh, in dubbio se far interagire direttamente con 
// b16img o se delegare tutto a imageQW

// rev2
//#include "b16img.h"
#include "b16img2.h"
#include "physImage.h"



#ifndef __thIntegrate_window_h
#define __thIntegrate_window_h

class thIntegrate_window : public QWidget
{
	Q_OBJECT

public:
	// rev2 thIntegrate_window(b16img *);
	thIntegrate_window(physImage *);
	//thIntegrate_window(QWidget *, b16img *);

	void create_paccottiglia(void);

private:
	//rev2 b16img *my_img;
	physImage *my_img;

	void update_energy(void);


	double threshold;
	int zero_level;
	double partial_integral, total_integral;
	double camera_calibration;	// joule/count

private slots:
	void threshold_changed(double);
	void zero_level_changed(int);
	//void calculate_integral(int, double);
	void calculate_integral(void);

	// rev2 void img_buffer_update(b16img *);
	void img_buffer_update(physImage *);

	void get_camera_calibration(double);
	

signals:
	void calculate_integral_parameters(int, double);
	void zero_and_th_changed(int, double);
	void image_integral(double);
	void result_text(QString );
	void draw_points_on_image(imagePointList);

	void set_zero_level(int);
	void set_threshold(double);

	void set_integrated_energy(double);
	void set_integrated_energy_text(QString);
};


#endif

