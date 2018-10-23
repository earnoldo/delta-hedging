#ifndef CSVFUN_HPP
#define CSVFUN_HPP

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <stdlib.h>
//#include <boost\tokenizer.hpp>
using namespace  std;

//exporting function code
void exportcsv(vector<vector<double> > source, string title, vector<string> headers)
{
    ofstream pricefile;
    pricefile.open(title.c_str());


    // headers for the file
	pricefile<<headers[0];
    for (int i=1; i<headers.size();i++)
        pricefile<<","<<headers[i];
    pricefile<<endl;

	//Information of the file
    for(int i=0;i<source[0].size();i++)
    {
		pricefile<<i;
		for(int j=0;j<source.size();j++)
		{
		   pricefile<<","<<source[j][i];
		}
        pricefile<<endl;
    } 
    pricefile.close();
}


 //Implementation for the extract data function
 vector<vector<string> > importcsv(string address)
{
    vector<vector<string> > result;
	vector<string> answer;
    string sline;
    ifstream csvfile(address.c_str());
	string token;
		while (getline(csvfile, sline))		//iterate the row while exists information
		{
			istringstream stream1(sline);
				while(getline(stream1,token, ','))				//separates the data with commas ","
				{
					answer.push_back(token);  //inserting the rates in the vector
				}
				result.push_back(answer);
				answer.clear();
		}
	return result;
}


//Implementation for the extract data function from "op_GOOG1.csv"
 vector<vector<string> > importcsv2(string address, string exp_date, double stk_pice, string type)
{
    vector<vector<string> > result;
	vector<string> answer;
    string sline;
    ifstream csvfile(address.c_str());
	//string token;
	string t0, t1, t2, t3, t4, t5;
	int i=0;
	cout<<"Reading "<<address<<" file..."<<endl;
	while (getline(csvfile, sline))		//iterate the row while exists information
	{
		if ((i%20000)==0)
		{cout<<"line "<<i<<endl;}
		istringstream stream1(sline);
		getline(stream1,t0, ','); 
		getline(stream1,t1, ','); 
		getline(stream1,t2, ','); 
		getline(stream1,t3, ','); 
		getline(stream1,t4, ','); 
		getline(stream1,t5, ','); 
		if (t1==exp_date)
		{
			if(stk_pice==atof(t3.c_str()))
			{
				if (type==t2)
				{
					answer.push_back(t0); answer.push_back(t1); answer.push_back(t2); answer.push_back(t3); 
					answer.push_back(t4); answer.push_back(t5); 
					result.push_back(answer);
					answer.clear();
				}
			}
		}
		i++;
	}
	return result;
}


//Reporting function for file with headers and rows 
//exporting function code
void exportcsv2(vector<vector<double> > source, string title, vector<string> headers, vector<string> rows)
{
    ofstream pricefile;
    pricefile.open(title.c_str());


    // headers for the file
	pricefile<<headers[0];
    for (int i=1; i<headers.size();i++)
        pricefile<<","<<headers[i];
    pricefile<<endl;

	//Information of the file
    for(int i=0;i<source[0].size();i++)
    {
		pricefile<<rows[i];
		for(int j=0;j<source.size();j++)
		{
		   pricefile<<","<<source[j][i];
		}
        pricefile<<endl;
    } 
    pricefile.close();
}


//Statistics funcionalities

//function to calculate average
double average(vector<double> v)
{
	// code for calculating average of members of v
	// and returning the average
	double result = 0;
	vector<double>::iterator a;		//this is the iterator for the vector
	for (a = v.begin(); a != v.end(); a++)
	{
		result += *a;
	}
	return result / v.size();
}

//function to calculate standar deviation
double std_dev(vector<double> X)
{
	double result = 0;
	double mean = average(X);
	for (int i = 0; i<X.size(); i++)
	{
		result = result + (mean - X[i])*(mean - X[i]);
	}
	return sqrt(result);
}


#endif
