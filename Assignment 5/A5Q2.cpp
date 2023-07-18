/*
Michael McPhee and Ryan Scomazzon
A5Q2.cpp
October 25, 2022
Assume valid file format
Program that reads info from a file about paving and fencing jobs, calculates 
the price of the job, and outputs the information into a file.
*/
#include <fstream>
#include <iostream>
#include <cmath>
#include <string>
#include <iomanip>

using namespace std;

//functions that calculate perimeter and area for each shape
double perimeterTri(double side1, double side2, double side3)
{
  double sum = side1 + side2 + side3;
  return sum;
}

double areaTri(double side1, double side2, double side3)
{
  double semiperim = (side1 + side2 + side3)/2.0;
  double area = sqrt(semiperim*(semiperim-side1)*
    (semiperim-side2)*(semiperim-side3));
  return area;
}

double perimeterQuad(double side1, double side2, double side3, double side4)
{
  double sum = side1 + side2 + side3 + side4;
  return sum;
}

double areaQuad(double side1, double side2, double diagonal, 
  double side3, double side4)
{
  double area = areaTri(side1, side2, diagonal) +
    areaTri(diagonal, side3, side4);
  return area;
}

//function that calculate price before tax
double subtotal(double fenceCost, double paveCost)
{
  const double ADMIN_FEE = 45;
  double cost = ADMIN_FEE + fenceCost + paveCost;
  return cost;
}

int main()
{
  //declare variables to read from file
  int jobNum = 0;
  int fenceJob = 0;
  string shape = " ";
  
  //open input and output files
  ifstream FileIn("Sep_jobs.txt");
  ofstream FileOut("Sep_jobs_final.txt");
  
  //check if files opened
  if (!(FileIn&&FileOut))
  {
    cout << "Unable to open file(s)";
    return EXIT_FAILURE;
  }
  
  //output the headings for each column in the file
  FileOut <<"Job#" <<setw(7) <<"Fence" <<setw(11) <<"PavedArea"
    <<setw(11) <<"PaveCost" <<setw(12) <<"FenceLength" <<setw(11)
    <<"FenceCost" <<setw(11) <<"Taxes" <<setw(11) <<"TotalCost" <<endl;
  
  //read from file 
  while (FileIn >> jobNum >> fenceJob >> shape)
  {
    //declare variables used only in the while loop
    const double PRICE_PER_SQUARE_METRE = 19.50;
    const double PRICE_PER_METRE = 27.00;
    const double FENCE_GATE = 150;
    const double HST = 0.13;
    double fenceLegnth = 0;
    double pavedArea = 0;
    double fenceCost = 0;
    double paveCost = 0;
    double taxes = 0;
    double total = 0;
    
    //use the functions shown above to calculate fence legnth and paved area
    //if statements to decide which function to use (triangle/quadrilateral)
    if (shape == "tri")
    {
      double side1 = 0;
      double side2 = 0;
      double side3 = 0;
      FileIn >> side1 >> side2 >> side3;
      fenceLegnth = fenceJob*perimeterTri(side1, side2, side3);
      pavedArea = areaTri(side1, side2, side3); 
    }
    else
    {
       double side1 = 0;
       double side2 = 0;
       double side3 = 0;
       double side4 = 0;
       double diagonal = 0;
      FileIn >> side1 >> side2 >> diagonal >> side3 >> side4;
      fenceLegnth = fenceJob*perimeterQuad(side1, side2, side3, side4);
      pavedArea = areaQuad(side1, side2, diagonal, side3, side4);
    }
  //calculate price of fencing, paving and taxes
  fenceCost = PRICE_PER_METRE*ceil(fenceLegnth) + FENCE_GATE*fenceJob;
  paveCost = PRICE_PER_SQUARE_METRE*pavedArea;
  taxes = HST*subtotal(fenceCost, paveCost);
  total = subtotal(fenceCost, paveCost) + taxes;
  
  //output job info, fence legnths, paved areas, and prices into the file
  FileOut <<jobNum <<setw(7) <<fenceJob <<fixed <<setprecision(2)
    <<setw(11) <<pavedArea <<setw(11) <<paveCost <<setw(11) <<fenceLegnth 
    <<setw(12) <<fenceCost <<setw(11) <<taxes <<setw(11) <<total <<endl;
  }
  //close files
  FileIn.close();
  FileOut.close();
  return EXIT_SUCCESS;
}

/*
Job#  Fence  PavedArea   PaveCost FenceLength  FenceCost      Taxes  TotalCost
7100      1     600.00   11700.00     120.00     3390.00    1967.55   17102.55
7101      0       9.00     175.50       0.00        0.00      28.66     249.16
7102      1     784.00   15288.00     112.00     3174.00    2405.91   20912.91
7103      0      70.16    1368.16       0.00        0.00     183.71    1596.87
7104      1    2323.24   45303.18     192.80     5361.00    6592.19   57301.37
7105      0     501.76    9784.32       0.00        0.00    1277.81   11107.13
7106      0       8.39     163.53       0.00        0.00      27.11     235.64
7107      1       3.90      75.99       9.00      393.00      66.82     580.81
7108      1      70.56    1375.92      33.60     1068.00     323.56    2812.48
*/
