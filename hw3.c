// Ian O'Brien
// CS451 - Numeric Computation

/*
this program allows a user to specify the degree of a function and then select degree + 1 points in the window to fit a curve w/ proper degree to that curve there will be funcationality for functions up to degree 100 or so.
*/

#include "FPToolkit.c"

double la_grande(int x, int degree, double yval[],double xval[]);
double calc_num(int x, int degree, double xval[], int i);
double calc_denom(int degree, double xval[],int i);
int n = 0;



int main()
{
	int swidth, sheight, degree;
    double point[2];


	printf("\n\nspecify the degree of the function you want to fit:");
	scanf("%d", &degree);
	
    double xval[degree+1], yval[degree+1];

	// establish the height and init
	swidth = 700;	sheight = 700;
	G_init_graphics (swidth,sheight);  // interactive graphics

	// clear screen and set color
	G_rgb(0.5,0.5,0.5);
	G_clear();

	
	// set color to red for points
	// and have user click degree + 1 points to use the data to fit the curve
	G_rgb(1,0,0);

	for(int i = 0; i < degree+1; ++i)
	{
		G_wait_click(point);
		xval[i] = point[0];
		yval[i] = point[1];	
		G_fill_circle(xval[i],yval[i],2);
	}

	//set line color to green
	G_rgb(0, 0, 1);

    // run la_grande and plot the points
	for (int x = 1; x < swidth; ++x)
	{
        G_line(x, la_grande(x, degree,yval,xval), x+1, la_grande(x+1, degree, yval,xval));
        //G_point(x, la_grande(x, degree, yval, xval));
        //printf("%d\t%lf\n", x, la_grande(x, degree, yval, xval));
	}

	// pause and hold before quitting program	
	int key;	
	key = G_wait_key();

	return 0;
}

// la grande interpolation function for up to three points selected in the window
double la_grande(int x, int degree, double yval[],double xval[])
{
    double fx = 0;
    double temp;
    
	for(int i = 0; i < degree + 1; ++i)
	{
        fx += yval[i] *((calc_num(x, degree, xval, i))/(calc_denom(degree, xval,i)));
	}	
	return fx;
}

// calculate numerator for la_grande interpolation
double calc_num(int x,int degree, double xval[], int i)
{
    double numerator = 1;
    for(int j = 0; j < degree + 1; ++j)
    {
       if(i != j)
            numerator *= (x - xval[j]);
       if(i == j)
            numerator *= 1;  
    }
    //printf("%lf\n", numerator);
    return numerator;
}


// calculate denominator for la_grande interpolation
double calc_denom(int degree, double xval[],int i)
{
    double denom = 1;
    for(int k = 0; k < degree + 1; ++k)
    {
        if(i != k)
        {
            denom *=  (xval[i] - xval[k]);
        }
        if(i == k)
            denom *= 1;
        //printf("%lf\n", denom);

    }
    return denom;
}