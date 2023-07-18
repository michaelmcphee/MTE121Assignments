/*
A1Q2.cpp
Michael McPhee
September 14, 2022
Assumption: user will input positive rational real numbers, no overflow
Prompts user for pyramid height and length and outputs pyramid volume
*/

#include <iostream>
#include <cmath>
#include <cstdlib>

using namespace std;

int main()

{
	//declarations
	double pyramid_height = 0; 
	double pyramid_length = 0;
	
	cout << "Enter pyramid height: " ;
	
	cin >> pyramid_height;
	
	cout << "Enter pyramid length: " ;
	
	cin >> pyramid_length;
	
	cout << "The volume of the pyramid is " 
	<< pyramid_height*pyramid_length*pyramid_length/3;
	
	return EXIT_SUCCESS;

}

/* 
Enter pyramid height: 4.5678
Enter pyramid length: 3.2
The volume of the pyramid is 15.5914
--------------------------------
Process exited after 18.53 seconds with return value 0
Press any key to continue . . .
*/