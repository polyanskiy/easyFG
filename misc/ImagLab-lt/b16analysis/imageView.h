#include <iostream>
#include <fstream>

#include <QObject>
#include <QWidget>
#include <QtGui>
#include <QSlider>

#ifndef __imageView_h
#define __imageView_h

class imageView : public QWidget
{
Q_OBJECT
public:
	imageView() {
		QLabel *d1_lbl, *d2_lbl;

		d1_lbl = new QLabel(this);
		d1_lbl->setGeometry(0,0,200,30);
		d1_lbl->setText("Upper Limit");
		d1_lbl->setFont(QFont("Verdana",8,-1,false));

		upper_sl = new QSlider(this);
		upper_sl->setGeometry(20,30,160,20);
		upper_sl->setOrientation(Qt::Horizontal);
	
		d2_lbl = new QLabel(this);
		d2_lbl->setGeometry(0,60,100,30);
		d2_lbl->setText("Lower Limit");
		d2_lbl->setFont(QFont("Verdana",8,-1,false));
	
		lower_sl = new QSlider(this);
		lower_sl->setGeometry(20,90,160,20);
		lower_sl->setOrientation(Qt::Horizontal);

		connect(lower_sl, SIGNAL(valueChanged(int)), this, SLOT(lowerChanged(int)));
		connect(upper_sl, SIGNAL(valueChanged(int)), this, SLOT(upperChanged(int)));
	}
	~imageView()
	{ }

public slots:
	void setCurrentValues(int low_val, int up_val)
	{ upper_sl->setValue(up_val); lower_sl->setValue(low_val); }

	void setLowLimit(int new_min)
	{ upper_sl->setMinimum(new_min); lower_sl->setMinimum(new_min); } 
	
	void setUpLimit(int new_max)
	{ upper_sl->setMaximum(new_max); lower_sl->setMaximum(new_max); } 

	void lowerChanged(int new_val)
	{ my_lower = new_val; emit(setImageVisualisationRange(my_lower, my_upper)); }

	void upperChanged(int new_val)
	{ my_upper = new_val; emit setImageVisualisationRange(my_lower, my_upper); }

signals:
	void setImageVisualisationRange(int, int);	

private:
	QSlider *upper_sl, *lower_sl;

	int my_lower, my_upper;
};

#endif
