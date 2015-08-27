#include "selectPoints.h"

selectPoints::selectPoints()
{
	setWindowTitle(QString("select points on image.."));
	// setMinimumSize
	// setMaximumSize
	
	QPushButton *newLine_pb, *endSelect_pb, *exportLines_pb, *wOut_pb;

	newLine_pb = new QPushButton(QString("New"), this);
	newLine_pb->setGeometry(10,10,50,40);
	connect(newLine_pb, SIGNAL(clicked()), SLOT(set_new_point_list()));

	endSelect_pb = new QPushButton(QString("End"), this);
	endSelect_pb->setGeometry(70,10,50,40);
	connect(endSelect_pb, SIGNAL(clicked()), SLOT(set_end_point_list()));
	
	wOut_pb = new QPushButton(QString("Write"), this);
	wOut_pb->setGeometry(130,10,50,40);
	connect(wOut_pb, SIGNAL(clicked()), SLOT(write_out()));
	
	QTableWidget *pointList_table;
	pointList_table = new QTableWidget(2,2,this);
	pointList_table->setGeometry(10,60,300,100);

	my_point_matrix = new imagePointList_collector(100);
	inserted_list_count = -1;
}

void
selectPoints::set_new_point_list(void)
{
	if (acquiring_state)
		set_end_point_list();

	inserted_list_count++;
	imagePointList *cur_pt_list;
	current = new imagePointList(0);
	(*my_point_matrix)[inserted_list_count] = current;
	std::cout<<"[selectPoints] opening point list "<<inserted_list_count+1<<std::endl;
	acquiring_state = true;
}

void
selectPoints::set_end_point_list(void)
{
	if (acquiring_state) {
		std::cout<<"[selectPoints] closing vector #"<<inserted_list_count<<" with "<<((*my_point_matrix)[inserted_list_count])->size()<<" points"<<std::endl;
		acquiring_state = false;
	}
}

void
selectPoints::add_point_to_list(int x, int y)
{
	//current = (*my_point_matrix)[inserted_list_count];

	current->push_back(imagePoint(x,y));

	emit add_point_on_image(*current);
}

void
selectPoints::delete_point_list(void)
{}

void
selectPoints::mouse_clicked_on_image(int x, int y)
{
	std::cout<<"[selectPoints] mouse clicked: ("<<x<<":"<<y<<")"<<std::endl;
	if (acquiring_state) {
		add_point_to_list(x,y);
	}
}

void
selectPoints::write_out(void)
{
	ofstream ofile("selPoints_dumpfile.dat");
	ofile<<"# created by b16analysis - live point selection on B16 image"<<std::endl;

	imagePointList *cur_pt_list;

	for (int s_vector=0; s_vector<inserted_list_count+1; s_vector++) {
		
		cur_pt_list = (*my_point_matrix)[s_vector];

		ofile<<"# name: vector_"<<s_vector<<"\n";
		ofile<<"# type: matrix\n";
		ofile<<"# rows: "<<cur_pt_list->size()<<"\n";
		ofile<<"# columns: 2\n";
		for (int i=0; i<cur_pt_list->size(); i++) {
			ofile<<" "<<((*cur_pt_list)[i]).x<<" "<<((*cur_pt_list)[i]).y<<"\n";
		}
	}

	ofile<<std::flush;
	ofile.close();

}

