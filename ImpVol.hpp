
#ifndef IMP_VOL_HPP
#define IMP_VOL_HPP

#include <iostream>
#include <vector>
#include <cmath>
using namespace  std;


//Normal Distribution Calculator
double  N2(double x)
{

    if (x>=0)
    {
        double z=1/(1+0.2316419*x);
        double r = 0.319381530*z -0.356563782 *z*z + 1.781477937 *z*z*z -1.821255978 *z*z*z*z + 1.330274429 *z*z*z*z*z;
        double N2 = 1- 1/sqrt(2*3.141592653589) * exp(-x*x/2)*r;
        return N2;
    }
    else
    {
        double X=(-1)*x;
        double z=1/(1+0.2316419*X);
        double r = 0.319381530*z -0.356563782 *z*z + 1.781477937 *z*z*z -1.821255978 *z*z*z*z + 1.330274429 *z*z*z*z*z;
        double N2 = 1- 1/sqrt(2*3.141592653589) * exp(-X*X/2)*r;
        return 1-N2;
    }
}


//Implied Volatility Calculator--- Newton Raphson Method
double impvol(double K, double T, double r, double S_0, double cal)
{
	double sig=0.22;
	double d1;
	double d2;
	double C;
	double vega;
	double error=1;
	double temp;
	while(abs(error)>0.000001)
	{
		temp=sig;
		d1= (log(S_0/K)+(r+sig*sig/2)*T) / (sig*sqrt(T));
		d2= d1-sig*sqrt(T);
		C=S_0*N2(d1)-K*exp(-r*T)*N2(d2);
		vega= S_0*sqrt(T)*(1/sqrt(2*3.141592653589))*exp(-(d1*d1)/2);
		sig=sig+(cal-C)/vega;
		error=temp-sig;
	}
	return sig;
}


//Hedging Tester for Real Values
vector<vector<double> > realhedge(vector<double> t, vector<double> r, vector<double> s, vector<double> C, double K)
{
	vector<vector<double> > answer;
	vector<double> sigma;				//vector of implied volatilities
	vector<double> deltas;				//vector of implied deltas
	vector<double> B;					//vector of implied B_i
	vector<double> HE;					//vector of hedging errors
	vector<double> HEcum;				//vector of cum hedging error
	vector<double> PNL;					//walth whothout hedge

	for (int i = 0; i < t.size(); i++)
	{
		if(i==92)
		{
			double xx=0;
		}

		sigma.push_back(impvol(K, t[i],  r[i], s[i], C[i]));			//calculating sigma with newton raphson
		deltas.push_back(N2(((log(s[i]/K))+(r[i]+sigma[i]*sigma[i]/2)*t[i])/(sigma[i]*sqrt(t[i]))));
		if (i==0)
		{
			B.push_back(C[i]-deltas[i]*s[i]);
			HEcum.push_back(0);
			HE.push_back(0);
		}
		else
		{
			B.push_back(deltas[i-1]*s[i]+B[i-1]*exp(r[i-1]*(t[i]-t[i-1]))-deltas[i]*s[i]);
			HEcum.push_back(deltas[i-1]*s[i]+B[i-1]*exp(r[i-1]*(t[i]-t[i-1]))-C[i]);
			HE.push_back(HEcum[i]-HEcum[i-1]);
		}
		PNL.push_back(C[i]-C[0]);
	}
	answer.push_back(sigma); answer.push_back(deltas); answer.push_back(HE); answer.push_back(HEcum); answer.push_back(PNL);
	return answer;
}
#endif

