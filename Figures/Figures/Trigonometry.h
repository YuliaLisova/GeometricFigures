#ifndef Trigonometry_H
#define  Trigonometry_H

#include <math.h>
#define PI 3.14

class Trigonometry
{ 
public:
	static double MySinus (double angle);
	
	static double MyCosinus (double angle);
	
};

#endif

/////////////////////////////////////////////////////////

double Trigonometry :: MySinus (double angle)
{
	if (angle == 30) return 0.5;
	else if (angle == 90) return 1;
	else if (angle == 150) return 0.5;
     else if (angle == 180) return 0;
	 else return sin(angle * PI/180);
}

double Trigonometry :: MyCosinus (double angle)
	{  
	   if (angle == 60) return 0.5;
	   else if (angle == 90) return 0;
	   else if (angle == 120) return -0.5;
	   else if (angle == 180) return -1;
	   else return cos(angle * PI/180);

	}