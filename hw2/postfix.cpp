#include "stackdbl.h"
#include <string>
#include <fstream>
#include <sstream>
#include <cstring>
#include <stdlib.h>
#include <iostream>

using namespace std;

double calculate(string& expr, bool& success){
	char buffer[128];
	double result = -1;
	double a = 0;
	double b = 0;
	double c = 0;
	success = false;
	StackDbl calcu;
	stringstream trans(expr);


		trans >> buffer;
	while(trans && !expr.empty())
	{
		if (buffer[0] == '-')
		{
			if (calcu.empty())	return result;
			else{
				a = calcu.top();
				calcu.pop();
				if (calcu.empty()) return result;

				b = calcu.top();
				calcu.pop();

				c = b - a;
				calcu.push(c);
			}
		}
		else if (buffer[0] == '+')
		{
			if (calcu.empty())	return result;
			else{
				a = calcu.top();
				calcu.pop();
				if (calcu.empty()) return result;

				b = calcu.top();
				calcu.pop();

				c = b + a;
				calcu.push(c);
			}
		}
		else if (buffer[0] == '*')
		{
			if (calcu.empty())	return result;
			else{
				a = calcu.top();
				calcu.pop();
				if (calcu.empty()) return result;

				b = calcu.top();
				calcu.pop();

				c = b * a;
				calcu.push(c);
			}
		}
		else if (buffer[0] == '/')
		{
			if (calcu.empty())	return result;
			else{
				a = calcu.top();
				calcu.pop();
				if (calcu.empty()) return result;

				b = calcu.top();
				calcu.pop();

				c = b / a;
				calcu.push(c);
			}
		}
		else{
			a = atof(buffer);
			calcu.push(a);
		}

		trans >> buffer;
	}

	result = calcu.top();
	calcu.pop();

	if (!calcu.empty())
	{
		return -1;
	}
		success = true;
		return result;
}



int main(int argc, const char * argv[])
{
	bool success = false;
    ifstream myfile;
    ofstream ofile;
    string line;

    myfile.open(argv[1]);
  	ofile.open(argv[2]);

    if(!myfile.is_open() || !ofile.is_open()){
    	cout<<"Please enter the correct input/output file's name."<<endl;
    	return 0;
 	 }

    while(getline(myfile, line))
    {
    	double result = calculate(line, success);
    	if (success)
   		{
		    ofile << result << " \n"; 
    	}
    	else{
		    ofile << "Invalid \n"; 
    	}
    }


    myfile.close();
	return 0;
}

