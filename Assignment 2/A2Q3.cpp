/*
A2Q3.cpp
Michael McPhee and Vinesh Vivekanand
September 20, 2022
Assumption: inputs are valid for side lengths and angles, negative values and angles > 180 are invalid
User inputs 2 side lengths and an angle and outputs remaining side length and angles in degrees and radians
*/

#include <iostream>
#include <cmath>

using namespace std;

int main()

{
    double a_side = 0; // initialize 2 side and 1 angle variables
    double b_side = 0;
    double c_angle_deg = 0;
    double degToRad = M_PI/180;

    cout << "Please input a side length: "; //input vales for variables
    cin >> a_side;
    cout << "Input another side length: ";
    cin >> b_side;
    cout << "Input the contained angle: ";
    cin >> c_angle_deg;

    double c_angle_rad = c_angle_deg*degToRad; //convert degrees to radians

    double c_side = sqrt((a_side*a_side) + (b_side*b_side) - (2*a_side*b_side*cos(c_angle_rad))); //cosine law for c side length

    double a_angle_rad = acos(((a_side*a_side) - (b_side*b_side) - (c_side*c_side))/(-2*b_side*c_side)); //cosine law for a angle

    double b_angle_rad = acos(((b_side*b_side) - (a_side*a_side) - (c_side*c_side))/(-2*a_side*c_side)); //cosine law for b angle

    double a_angle_deg = a_angle_rad/degToRad; //convert deg to rad
    double b_angle_deg = b_angle_rad/degToRad;

    if (c_angle_deg>0 && c_angle_deg<180) //check if valid triangle
    {
        cout << "Angle A in Degrees: " << a_angle_deg << endl
             << "Angle B in Degrees: " << b_angle_deg << endl
             << "Angle C in Degrees: " << c_angle_deg << endl
             << "Angle A in Radians: " << a_angle_rad << endl
             << "Angle B in Radians: " << b_angle_rad << endl
             << "Angle C in Radians: " << c_angle_rad << endl
             << "Side A: " << a_side << endl
             << "Side B: " << b_side << endl
             << "Side C: " << c_side << endl;
    }
    else
    {
        cout << "Invalid triangle";
    }

    return EXIT_SUCCESS;
}

/*
Please input a side length: 2
Input another side length: 3
Input the contained angle: 30
Angle A in Degrees: 38.262
Angle B in Degrees: 111.738
Angle C in Degrees: 30
Angle A in Radians: 0.667797
Angle B in Radians: 1.9502
Angle C in Radians: 0.523599
Side A: 2
Side B: 3
Side C: 1.61484
--------------------------------
Process exited after 4.774 seconds with return value 0
Press any key to continue . . .


Please input a side length: 14
Input another side length: 14
Input the contained angle: 90
Angle A in Degrees: 45
Angle B in Degrees: 45
Angle C in Degrees: 90
Angle A in Radians: 0.785398
Angle B in Radians: 0.785398
Angle C in Radians: 1.5708
Side A: 14
Side B: 14
Side C: 19.799
--------------------------------
Process exited after 10.15 seconds with return value 0
Press any key to continue . . .


Please input a side length: 25
Input another side length: 32
Input the contained angle: 155
Angle A in Degrees: 10.9405
Angle B in Degrees: 14.0595
Angle C in Degrees: 155
Angle A in Radians: 0.190947
Angle B in Radians: 0.245385
Angle C in Radians: 2.70526
Side A: 25
Side B: 32
Side C: 55.6695
--------------------------------
Process exited after 7.137 seconds with return value 0
Press any key to continue . . .

Please input a side length: 6
Input another side length: 9
Input the contained angle: 200
Invalid triangle
--------------------------------
Process exited after 12.31 seconds with return value 0
Press any key to continue . . .

*/