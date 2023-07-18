/*
A2Q2.cpp
Michael McPhee and Vinesh Vivekanand
September 20, 2022
Assumption: user will input integers in the thousands (4-6 digits)
Prompts user for an integer (in the thousands) and outputs it using commas
*/

#include <iostream>
#include <cmath>

using namespace std;

int main()

{
    //initialize variable
    int num = 0;
    
    //ask user for number in thousands
    cout << "Enter a number in the thousands (positive or negative): ";

    //assign input to num
    cin >> num;

    //assign variable for thousands
    int thousands = num/1000;

    //assign variable for remainder after dividing by 1000
    int remainder = abs(num%1000);

    //output thousands,remainder accounting for remainder being <3 digits
    if (remainder < 10)
    {
        cout << "The number is " << thousands << ",00" << remainder;
    }
    else if (remainder < 100)
    {
        cout << "The number is " << thousands << ",0" << remainder;
    }
    else
    {
        cout << "The number is " << thousands << "," << remainder;
    }

    return EXIT_SUCCESS;
}

/*
Test case 1:

Enter a number in the thousands: 425081
The number is 425,081
--------------------------------
Process exited after 8.271 seconds with return value 0
Press any key to continue . . .

Test case 2:

Enter a number in the thousands: 1000
The number is 1,000
--------------------------------
Process exited after 54.71 seconds with return value 0
Press any key to continue . . .

Test case 3:

Enter a number in the thousands: -11004
The number is -11,004
--------------------------------
Process exited after 13.22 seconds with return value 0
Press any key to continue . . .

Test case 4:

Enter a number in the thousands: -987654
The number is -987,654
--------------------------------
Process exited after 46.42 seconds with return value 0
Press any key to continue . . .
*/