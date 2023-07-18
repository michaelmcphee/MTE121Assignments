/*
Michael McPhee and Aly Ahmed
November 2, 2022
Assume user wants to calculate distance NOT DISPLACEMENT
Program that reads data from a file captured from an accelerometer on a car at 
regular time intervals, and outputs the distance travelled of the car.
*/
#include <fstream>
#include <iostream>
#include <cmath>

using namespace std;

void positionvelocityupdate (double & position, double & velocity, 
  double acceleration, double time)
{
  position += velocity*time + acceleration*pow(time,2)/2;
  velocity += acceleration*time;
  return;
}

double distance (ifstream &FileIn, double time)
{
  double position = 0;
  double position1 = 0;
  double acceleration = 0;
  double velocity = 0;
  double distance = 0;
  
  while(FileIn>>acceleration)
  {
    position1 = position;
    positionvelocityupdate(position, velocity, acceleration, time);
    distance += (abs(position - position1));
  }
  return distance; 
}

int main()
{
  double const TIME_INCREMENT = 0.25;
  
  ifstream FileIn("accel_data.txt");
  if (!FileIn)
  {
    cout << "Unable to open file";
    return EXIT_FAILURE;
  }
  
  cout << "The distance travelled is " << distance(FileIn, TIME_INCREMENT) 
    << " m/s^2.";
  
  FileIn.close();
  return EXIT_SUCCESS;
}

/*
The distance travelled is 47.7177 m/s^2.
*/