#include <QSpinBox>

#ifndef __betterQSpinBox_h
#define __betterQSpinBox_h

class betterQSpinBox : public QSpinBox {
	Q_OBJECT
public:
	betterQSpinBox(QWidget *parent) 
		: QSpinBox(parent) {}

	~betterQSpinBox()
	{}

public slots:
	void setMinimum_slot(int new_val)
	{ setMinimum(new_val); }
	
	void setMaximum_slot(int new_val)
	{ setMaximum(new_val); }
};

#endif
