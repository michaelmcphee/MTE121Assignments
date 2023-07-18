/*
A1Q3.cpp
Michael McPhee
September 14, 2022
Assumption: user will input rational real numbers, no overflow
*/

#include <iostream>
#include <cmath>
#include <cstdlib>

using namespace std;

int main()

{
	//declarations, double to accomodate decimals
	double chains = 0;
	const int FEET = 66;
	const int YARDS = 22;
	const int LINKS = 100;
	const int RODS = 4;
	const int FURLONGS = 10;
	
	//ask user for length
	cout << "Enter length in chains: ";
	
	//assign input to chains
	cin >> chains;
	
	//convert and output lenths
	cout << chains << " chains is equal to " << endl
	<< chains*FEET << " feet " << endl
	<< chains*YARDS << " yards " << endl
	<< chains*LINKS << " links " << endl
	<< chains*RODS << " rods " << endl
	<< "and " << chains/FURLONGS << " furlongs";
	
	return EXIT_SUCCESS;	
}

/* 
Enter length in chains: 25
25 chains is equal to
1650 feet
550 yards
2500 links
100 rods
and 2.5 furlongs
--------------------------------
Process exited after 2.236 seconds with return value 0
Press any key to continue . . .
*/