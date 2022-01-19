/*******************************************************************************
 * Name    : sqrt.cpp
 * Author  : Robert Miller
 * Version : 1.0
 * Date    : September 2, 2021
 * Description : Computes the square root of the command-line argument.
 * Pledge : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/

#include <limits>
#include <sstream>
#include <iostream>
#include <iomanip>
using namespace std;

double sqrt(double num, double epsilon){
	double last_guess, next_guess;
	last_guess = num;
	next_guess = 0;
	if(num < 0){
		return numeric_limits<double>::quiet_NaN();
	} else if(num == 1 || num == 0){
		return num;
	}
	while(true){
		next_guess = (last_guess + num/last_guess) / 2;
		if(abs(last_guess - next_guess) <= epsilon){
		break;
		}
		last_guess = next_guess;
	}
return next_guess;
}


int main(int argc, char* argv[]){
	double num, epsilon;
	cout << fixed << setprecision(8);
	if(argc < 2 || argc > 3){
		cerr << "Usage: " << argv[0] << " <value> [epsilon]" << endl;
		return 1;
	}
	istringstream iss;
	iss.str(argv[1]);
	if(!(iss >> num)){
		cerr << "Error: Value argument must be a double." << endl;
		return 1;
	}
	iss >> num;
	iss.clear(); 
	if(argc == 2){
		epsilon = 1e-7;
	} else {
		iss.str(argv[2]);
		if(!(iss >> epsilon)){
			cerr << "Error: Epsilon argument must be a positive double." << endl;
			return 1;
		} else if(epsilon <= 0){	
			cerr << "Error: Epsilon argument must be a positive double." << endl;
			return 1;
		}
	}

		cout  << sqrt(num, epsilon);

		return 0;
}
