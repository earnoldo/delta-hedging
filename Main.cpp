//#include <ql/quantlib.hpp>
#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <random>
#include <string>
#include "BSEur.hpp"
#include "CsvFun.hpp"
#include "ImpVol.hpp"
using namespace std;
//using namespace QuantLib;

int main()
{
	//EXERCISE 1
	BSEur opt(105,0.025,0.4,0.24,0,"C");		//creating option object	 
	vector<vector<double> > options= opt.hedge(100,100,0.05);	//hedging the option S_0=100, K=100 and u=0.05
	
	//Headers of the csv file
	vector<string> headers;	
	headers.push_back("Date"); headers.push_back("S"); headers.push_back("V"); headers.push_back("Delta"); headers.push_back("Hedging Error"); 
	headers.push_back("Cumulative Hedging Error"); headers.push_back("PNL");

	/*
	//exporting results to csv file
	exportcsv(options,"TestHedge.csv",headers);
	*/

	/*
	//EXERCISE 2
	//asking user for preferences
	string stdt; 
	cout<<"Insert start date in format YYYY-MM-DD"<<endl;
	cin>>stdt;
	//stdt="2011-01-03";

	string hdt;
	cout<<"Insert last hedging date in format YYYY-MM-DD"<<endl;
	cin>>hdt;
	//hdt="2011-06-17";

	string exdt;
	cout<<"Insert expiration date in format YYYY-MM-DD"<<endl;
	cin>>exdt;
	//exdt="2011-06-18";

	double stk;
	cout<<"Insert the strike price"<<endl;
	cin>>stk;
	//stk=660;

	string type;
	cout<<"Insert the type"<<endl;
	cin>>type;
	//type="C";

	//reading csv files
	vector<vector<string> > prices= importcsv2("op_GOOG1.csv",exdt,stk, type);
	vector<vector<string> > interest= importcsv("interest.csv");
	vector<vector<string> > sprices= importcsv("sec_GOOG.csv");

	// double haha= impvol(15000, 0.129555, 0.025, 15247.92,640);   //testing implied volaility solver	

	
	//filtering data between start date and final date
	int jj=0;								//when jj=1 will the user wants to get the prices for that date 

	//call prices
	vector<string> dates; vector<double> call; 
	for(int i=0;i<prices.size();i++)
	{
		if (prices[i][0]==stdt)
			jj=1;
		if(jj==1)
		{
			dates.push_back(prices[i][0]);
			call.push_back( (atof(prices[i][4].c_str()) + atof(prices[i][5].c_str()))/2);
		}
		if (prices[i][0]==hdt)
			jj=0;
	}	

	//vector of rates
	vector<double> rates; 
	jj=0;
	for(int i=1;i<interest.size();i++)
	{
		if (interest[i][0]==stdt)
			jj=1;
		if (jj==1)
		{
			rates.push_back(atof(interest[i][1].c_str())/100);
		}
		if (interest[i][0]==hdt)
			jj=0;
	}

	//vector of prices
	vector<double> prices2;
	jj=0;
	for(int i=1;i<sprices.size();i++)
	{
		if (sprices[i][0]==stdt)
			jj=1;
		if (jj==1)
		{
			prices2.push_back(atof(sprices[i][1].c_str()));
		}
		if (sprices[i][0]==hdt)
			jj=0;
	}

	
	//**********QUANTLIB PART**********************
	
	//transforming stdt, hdt, exdt into times to expiration
	//Getting time to expiration  This is a simulation before quantlib-boost
	Date t_0, t_n, t_exp;
	Calendar uscalend = UnitedStates();
	t_0=DateParser::parseFormatted(stdt, "%Y-%m-%d");
	t_n=DateParser::parseFormatted(hdt, "%Y-%m-%d");
	t_exp=DateParser::parseFormatted(exdt, "%Y-%m-%d");
	double busday= uscalend.businessDaysBetween(t_0,t_exp, true, true);

	//***********QUANTLIB PART**********************
	vector<double> timexp;
	//****just fot experiment******
	for (double i = 0.0; i < prices2.size(); i++)
	{
		timexp.push_back((busday-i)/252);
		//timexp.push_back(0.5-i/252);

	}
	//****just fot experiment******


	//matrix with implied volatilities, B, Hedging Errors and Cumulative Hedging Errors
	vector<vector<double> > real= realhedge(timexp, rates, prices2, call, stk);

	//merging in other vector to report
	vector<vector<double> > report;
	report.push_back(prices2); report.push_back(call); report.push_back(real[0]); report.push_back(real[1]);
	report.push_back(real[2]); report.push_back(real[3]); report.push_back(real[4]);

	//headers to report
	vector<string> headers2;	
	headers2.push_back("Date"); headers2.push_back("S"); headers2.push_back("V"); headers2.push_back("sigma"); 	
	headers2.push_back("Delta"); headers2.push_back("HE"); headers2.push_back("Cum HE"); headers2.push_back("PNL");

	//reporting file
	exportcsv2(report, "RealHedge.csv", headers2, dates);


	double HE_mean = average(real[2]);
	double HE_std = std_dev(real[2]);

	//HE_mean   HE_std
	int j = 0;
	for (int i = 0; i<real[2].size(); i++)
	{
		if (real[2][i]>HE_mean - 2 * HE_std)
		{
			if (real[2][i]<HE_mean + 2 * HE_std)
			{
				j++;
			}
		}
	}

	j = 100 * j / real[2].size();

	cout << "The hedging error mean is " << HE_mean << " the standard deviation is " << HE_std << endl;
	cout << "The " << j << "% of the Hedging errors are within 2 standard deviations" << endl;
	*/


	return 0;
} 