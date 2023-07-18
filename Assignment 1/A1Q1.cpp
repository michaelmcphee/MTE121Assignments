/*
A1Q1.cpp
Michael McPhee
September 14, 2022
Assumption: user will input a rational real number, no overflow
Prompts user for number and outputs the square and cube of said number
*/
#include <iostream>

using namespace std;

int main()

{
    //declarations
    double side_length = 0;

    //prompt user input
    cout << "Enter side length: ";
    
    //assign input to variable
    cin >> side_length;

    //calculate and output square and cube of side length
    cout << "The square of " << side_length << " is " << side_length*side_length << endl;
    cout << "& the cube of " << side_length << " is " << side_length*side_length*side_length << endl;

    return EXIT_SUCCESS;

    
}

/*
Enter side length: 8
The squre of 8 is 64 
& the cube of 8 is 512
--------------------------------
Process exited after 6.331 seconds with return value 0
Press any key to continue . . .
*/