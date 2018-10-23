#include "BSEur.hpp"
#include <math.h>
#include <chrono>
#include "NormalFunction.hpp"
#include <random>
#include <vector>


    BSEur::BSEur()
    {
        K=101;
        r=0.03;       //risk free rate
        t=1;       //time to expiration
        sig=0.2;     //volatility
        q=0.05;       //dividend yield
        string type="c";    //type call or put
    }

    BSEur::BSEur(const BSEur& source)
    {
        K=source.K;
        r=source.r;
        t=source.t;
        sig=source.sig;
        q=source.q;
        type=source.type;
    }

    BSEur::BSEur(double k2, double r2, double t2, double sig2, double q2, string type2)
    {
        K=k2;
        r=r2;
        t=t2;
        sig=sig2;
        q=q2;
        type=type2;
    }


    BSEur::~BSEur()
    {

    }

    double BSEur::price(const double S)
    {
        double answer;
        double d1 = ((log(S/K))+(r-q+sig*sig/2)*t)/(sig*sqrt(t));
        double d2 = ((log(S/K))+(r-q-sig*sig/2)*t)/(sig*sqrt(t));


        if(type=="c" || type=="C")  //for call options
        {
            answer= S*exp(-q*t)*(N(d1))-K*exp(-r*t)*(N(d2));
        }
        else                        //for put options
        {
            answer= -S*exp(-q*t)*(N(-d1))+K*exp(-r*t)*(N(-d2));
        }
        return answer;
    }

    void BSEur::optype(const string type2)
    {
        type=type2;
    }

    void BSEur::opsig(const double sig2)
    {
        sig=sig2;
    }


	void BSEur::optime(const double t2)
	{
		t=t2;
	}


	double BSEur::delta(const double S)
	{
		double d1 = ((log(S/K))+(r-q+sig*sig/2)*t)/(sig*sqrt(t));
		return N(d1);
	}


vector<vector <double> > BSEur::hedge(int N, double S_0, double u)
{
	vector< vector <double> > answer;		//final vector

	//Random numbers standard tools
	unsigned seed = static_cast<int> (std::chrono::system_clock::now().time_since_epoch().count());
	std::mt19937 generator(seed);
	std::normal_distribution<double> dist(0,1);

	vector <double> S_i;			//stock prices
	vector <double> C_i;			//option prices
	vector <double> delta_i;		//deltas
	vector <double> B_i;			//useful variable	
	vector <double> HE_i;			//Hedging error
	vector <double> HE_cum;			//cummulative hedging error
	vector <double> PNL_i;			//wealth without hedge

	double S=S_0;
	double T= t;
	double tmpTime=t;
	double sigma=sig;
	double R= r;
	double C, deltas, B, HEc;

	for(int i=0;i<N;i++)
	{
		//Calculating stock price
		if (i==0)
		{
			S_i.push_back(S);
		}

		else
		{
			S=S_i[i-1]+u*S_i[i-1]*(T/N)+sigma*S_i[i-1]*sqrt(T/N)*dist(generator);
			S_i.push_back(S);
		}

		//calculating option price
		t=T-T/N*i;
		C=price(S);
		C_i.push_back(C);

		//calculating deltas
		deltas=delta(S);
		delta_i.push_back(deltas);

		//calculating B_i
		if(i==0)
		{
			B=C_i[i]-delta_i[i]*S_i[i];
		}
		else
		{
			B=delta_i[i-1]*S_i[i]+B_i[i-1]*exp(R*T/N)-delta_i[i]*S_i[i];
		}
		B_i.push_back(B);
		
		if (i==0)
		{	
			HE_i.push_back(0);
			HE_cum.push_back(0);
		}

		else
		{
			//calculating Hedging error and Cumulative Hedging error
			HEc=delta_i[i-1]*S_i[i]+B_i[i-1]*exp(R*T/N)-C_i[i];
			HE_cum.push_back(HEc);
			HE_i.push_back(HE_cum[i]-HE_cum[i-1]);
		}

		PNL_i.push_back(C_i[i]-C_i[0]);
	}

	//inserting information in the matrix answer
	answer.push_back(S_i); answer.push_back(C_i); answer.push_back(delta_i); 
	answer.push_back(HE_i); answer.push_back(HE_cum); answer.push_back(PNL_i);

	t=tmpTime;

	return answer;
}



