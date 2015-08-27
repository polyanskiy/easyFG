#include <QDoubleSpinBox>
#include <QLabel>

#ifndef __dDoubleSpinBox_h
#define __dDoubleSpinBox_h

class dDoubleSpinBox : public QWidget {
	Q_OBJECT

public:
	
	dDoubleSpinBox(QWidget *parent, const char *description)
		: QWidget(parent)
	{ 
		my_lbl = new QLabel(this);
		my_lbl->setGeometry(1,1,120,25);
		my_lbl->setText(description);
		my_lbl->setFont(QFont("Verdana",8,-1,false));
		
		my_sb = new QDoubleSpinBox(this);
		my_sb->setGeometry(120,1,60,25);
		my_sb->setFont(QFont("Verdana",7,-1,false));
		my_sb->setDecimals(5);

	}

	~dDoubleSpinBox()
	{ }

	void setPosition(int x, int y)
	{ setGeometry(x,y,180,25); }

	QDoubleSpinBox *my_sb;
	QLabel *my_lbl;
	
	
};

#endif
