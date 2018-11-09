// Ian O'Brien
// CS451 - Numeric Computation

// this program uses la_grande interpolation methods to fit a quadraditic curve between three selected points on a window, it utilizes an 
// external graphics library cal FPToolkit

#include "FPToolkit.c"

// la grande interpolation function for up to three points selected in the window
double la_grande(double x, double y0, double y1, double y2, double x0, double x1, double x2)
{
	double y;

	y = (y0*(x - x1)* (x - x2)) / ((x0 - x1)*(x0 - x2))+

		(y1*(x - x0)* (x - x2)) / ((x1 - x0)*(x1 - x2))+

		(y2*(x - x1)* (x - x0)) / ((x2 - x1)*(x2 - x0));

	return y;
}


int main()
{
	int swidth, sheight;
	double p0[2], p1[2], p2[2];
	double x,y;

	// establish the height and init
	swidth = 700;	sheight = 700;
	G_init_graphics (swidth,sheight);  // interactive graphics

	// clear screen and set color
	G_rgb(0.5,0.5,0.5);
	G_clear();

	
	// set color to red for points
	G_rgb(1,0,0);

	// select first point
	G_wait_click(p0);
	G_fill_circle(p0[0],p0[1],2);

	// select second point
	G_wait_click(p1);
	G_fill_circle(p1[0],p1[1],2);

	// select third point
	G_wait_click(p2);
	G_fill_circle(p2[0],p2[1],2);

	//set line color to green
	G_rgb(0, 0, 1);

	//loop to hit each pixel and evaluate lagrande interpolation @ each x value
	for (int i = 0; i < swidth; ++i)
	{
		G_line(i, la_grande(i, p0[1], p1[1], p2[1], p0[0], p1[0], p2[0]), i+1, la_grande(i+1, p0[1], p1[1], p2[1], p0[0], p1[0], p2[0]));
	}

	// pause and hold before quitting program	
	int key;	
	key = G_wait_key();

	return 0;
}