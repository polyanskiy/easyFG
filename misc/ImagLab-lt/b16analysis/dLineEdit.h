
#include <QLineEdit>
#include <QLabel>

#ifndef __dLineEdit_h
#define __dLineEdit_h

class dLineEdit : public QWidget {
	Q_OBJECT

public:
	
	dLineEdit(QWidget *parent, const char *description)
		: QWidget(parent)
	{ 
		my_lbl = new QLabel(this);
		my_lbl->setGeometry(1,1,120,25);
		my_lbl->setText(description);
		my_lbl->setFont(QFont("Verdana",8,-1,false));
		
		my_le = new QLineEdit(this);
		my_le->setGeometry(120,1,60,25);

	}

	~dLineEdit()
	{ }

	void setPosition(int x, int y)
	{ setGeometry(x,y,180,25); }

	QLineEdit *my_le;
	QLabel *my_lbl;
	
	
};

#endif
