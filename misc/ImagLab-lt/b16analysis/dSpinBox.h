#include <QSpinBox>
#include <QLabel>

#ifndef __dSpinBox_h
#define __dSpinBox_h

class dSpinBox : public QWidget {
	Q_OBJECT

public:
	
	dSpinBox(QWidget *parent, const char *description)
		: QWidget(parent)
	{ 
		my_lbl = new QLabel(this);
		my_lbl->setGeometry(1,1,120,25);
		my_lbl->setText(description);
		my_lbl->setFont(QFont("Verdana",8,-1,false));
		
		my_sb = new QSpinBox(this);
		my_sb->setGeometry(120,1,40,25);
		my_sb->setFont(QFont("Verdana",7,-1,false));

		connect(my_sb, SIGNAL(valueChanged(int)), this, SLOT(mysb_valueChanged(int)));

	}

	~dSpinBox()
	{ }

	void setPosition(int x, int y)
	{ setGeometry(x,y,160,25); }

	void setValue(int val)
	{ my_sb->setValue(val); }

	QSpinBox *my_sb;
	QLabel *my_lbl;

signals:
	void valueChanged(int);

private slots:
	void mysb_valueChanged(int val)
	{ emit valueChanged(val); }
	
	
};

#endif
