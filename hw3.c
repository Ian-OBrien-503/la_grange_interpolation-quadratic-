// Ian O'Brien
// CS451 - Numeric Computation

/*
this program allows a user to specify the degree of a function and then select degree + 1 
points in the window to fit a curve w/ proper degree to that curve w/ a polynomail of up to degree of 100
*/

#include "FPToolkit.c"

double la_grande(double x, int degree, double yval[],double xval[]);
double calc_num(int x, int degree, double xval[], int i);
double calc_denom(int degree, double xval[], int i);



int main()
{
	int swidth, sheight, degree, n=0;
	double x, y, point[2], xval[100], yval[100];


	printf("\n\nspecify the degree of the function you want to fit:");
	scanf("%d", &degree);
	printf("%d", degree);
	

	// establish the height and init
	swidth = 700;	sheight = 700;
	G_init_graphics (swidth,sheight);  // interactive graphics

	// clear screen and set color
	G_rgb(0.5,0.5,0.5);
	G_clear();

	
	// set color to red for points
	// and have user click degree + 1 points to use the data to fit the curve
	G_rgb(1,0,0);

	for(int i = 0; i < degree + 1; ++i)
	{
		G_wait_click(point);
		xval[i] = point[0];
		yval[i] = point[1];	
		G_fill_circle(xval[i],yval[i],2);
		++n;
	}
    


	//set line color to green
	G_rgb(0, 0, 1);

    // run la_grande and plot the points
	for (int i = 0; i < swidth; ++i)
	{
        G_line(i, la_grande(i, degree,yval,xval), i+1, la_grande(i+1, degree, yval,xval));
	}

	// pause and hold before quitting program	
	int key;	
	key = G_wait_key();

	return 0;
}

// la grande interpolation function for up to three points selected in the window
double la_grande(double x, int degree, double yval[],double xval[])
{
    double fx = 1;

	double y;
	for(int i = 0; i < degree + 1; ++i)
	{
        fx += yval[i] + ((x - calc_num(x, degree, xval, i))/(calc_denom(degree, xval, i)));
	}	
	return fx;
}

// calculate numerator for la_grande
double calc_num(int x,int degree, double xval[], int i)
{
    double numerator = 1;
    for(int j = 0; j < degree + 1; ++j)
    {
       if(i != j)
       {
            numerator *= (x - xval[j]);
       }
    }
    
    return numerator;
}

double calc_denom(int degree, double xval[], int i)
{
    double denom = 1;

    for(int k = 0; k < degree + 1; ++k)
    {
        if(i != k)
        {
            denom *=  (xval[i] - xval[k]);
        }
    }
    return denom;
}
