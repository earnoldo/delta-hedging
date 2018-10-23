/*  Class implementation of an European Option
    Private elements strike price, risk free rate, maturity, volatility, dividend and type
    Includes a pricing function S
*/
#ifndef BSEUR_HPP_INCLUDED
#define BSEUR_HPP_INCLUDED
#include <string>
#include <vector>
using namespace std;

class BSEur
{
private:
    double K;       //strike price
    double r;       //risk free rate
    double t;       //time to expiration
    double sig;     //volatility
    double q;       //dividend yield
    string type;    //type call or put

public:
    BSEur();
    BSEur(const BSEur& source);
    BSEur(double k2, double r2, double t2, double sig2, double q2, string type2);
    ~BSEur();

    //Pricing function
    double price(const double S);

    //setting functions
    void optype(const string type2);        //changes type
    void opsig(const double sig2);          //changes volatility
	void optime(const double t2);			//changes time to expiration

	//calculate value of delta
	double delta(const double S);
	
	//Hedging function
	vector<vector<double> >  hedge(int N, double S_0, double u);
};

#endif // BSEUR_HPP_INCLUDED
