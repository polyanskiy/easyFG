#include <string>
#include <iostream>

#include <QApplication>

#include "imageQW.h"

#include "physImage.h"
#include "b16img2.h"
#include "sifimg.h"

int main (int argc, char **argv)
{
	QApplication *qapp;
	physImage *extern_image;

	imageQW *my_QW;

	qapp = new QApplication(argc,argv);

//	if (argc > 1) {
//		if ( (extern_image = new b16img2(argv[1]))->img_buffer != NULL) 
//			my_QW = new imageQW(extern_image);
//		else if ( (extern_image = new sifimg(argv[1]))->img_buffer != NULL)
//			my_QW = new imageQW(extern_image);
//		else 
//			my_QW = new imageQW();
//	
//	} else my_QW = new imageQW();
//

	// v2 for external file calling
	my_QW = new imageQW();
	if (argc > 1) {
		my_QW->loadfile_ext(argv[1]);
	}

	//imageQW *my_QW = new imageQW();
	my_QW->show();

	qapp->exec();
}
