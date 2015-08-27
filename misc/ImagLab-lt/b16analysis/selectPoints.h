#include <QObject>
#include <QAction>
#include <QWidget>
#include <QMenu>
#include <QMenuBar>
#include <QtGui>
#include <QFileDialog>
#include <QMessageBox>
#include <QInputDialog>
#include <QTableWidget>
#include <fstream>

#include "physImage.h"


#ifndef __selectPoints_h
#define __selectPoints_h


class selectPoints : public QWidget
{
Q_OBJECT

public:
	selectPoints();
	~selectPoints() {}

	imagePointList_collector *my_point_matrix;

public slots:
	void set_new_point_list(void);
	void set_end_point_list(void);
	void add_point_to_list(int, int);
	void delete_point_list(void);
	void mouse_clicked_on_image(int, int);

private slots:
	void write_out(void);

signals:
	void add_point_on_image(imagePointList);

private:
	int inserted_list_count;
	imagePointList *current;
	bool acquiring_state;


};

#endif
