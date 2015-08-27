
#include "imgSelection.h"

imgSelection::imgSelection()
{}

void
imgSelection::set_new_upper_left(int x, int y)
{ x_ul = x; y_ul = y; }

void
imgSelection::set_new_lower_right(int x, int y)
{ x_ul = x; y_ul = y; }

void
imgSelection::set_point(int x, int y)
{

}

void
imgSelection::mouse_moved_in_selection(int x, int y)
{
	emit selection_coords(x_ul, y_ul, x-x_ul+1, y-y_ul+1);
}

//void
//imgSelection::draw_rectangle_on_image(QPoint upper_left, QPoint lower_right)
//{}
