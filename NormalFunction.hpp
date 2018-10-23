#ifndef NORMAL_HPP
#define NORMAL_HPP

#include <cmath>
#include <math.h>
#define pi 3.14159265358


double  N(double x)
{

    if (x>=0)
    {
        double z=1/(1+0.2316419*x);
        double r = 0.319381530*z -0.356563782 *z*z + 1.781477937 *z*z*z -1.821255978 *z*z*z*z + 1.330274429 *z*z*z*z*z;
        double N = 1- 1/sqrt(2*pi) * exp(-x*x/2)*r;
        return N;
    }
    else
    {
        double X=(-1)*x;
        double z=1/(1+0.2316419*X);
        double r = 0.319381530*z -0.356563782 *z*z + 1.781477937 *z*z*z -1.821255978 *z*z*z*z + 1.330274429 *z*z*z*z*z;
        double N = 1- 1/sqrt(2*pi) * exp(-X*X/2)*r;
        return 1-N;
    }
}



#endif
