#include "imgPainter.h"

imgPainter::imgPainter()
{}

	
imgPainter::imgPainter(QWidget *parent)
	: QWidget(parent)
{}

// slots
void
imgPainter::set_init_point(int x, int y)
{
	i1 = x; 
	i2 = y;

	update();
}
	
void
imgPainter::set_size(int ws, int hs)
{
	i3 = ws; 
	i4 = hs;

	update();
}

void
imgPainter::paintEvent(QPaintEvent *event)
{
	drawRect(i1,i2,i3,i4);
}
