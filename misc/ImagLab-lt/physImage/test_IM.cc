#include "physImage.h"
#include "IMimg.h"

int main(int argc, char **argv)
{
	IMimg *img;
	img = new IMimg(argv[1]);
	img->writePGM("test.pgm");
}
