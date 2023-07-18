/*
Michael McPhee and Daniel Luchian
A3Q2.cpp
September 28th, 2022
Program that decides what board game to play based day of week, whether or
not it is a school night, and the start time. 
*/

#include <iostream>
#include <cstdlib>
#include<fstream>
using namespace std;

int main()

{
  //set file
  ifstream FileIn ("BoardGameDecision.txt");
  
  //check if able to access file
  if(!FileIn)
  {
    cout << "Unable to open file";
    return EXIT_FAILURE;
  }
  
  //for loop that repeats once for each test case
  for(int i = 0; i < 5; i++)
  {
    //declarations
    string DayofWeek = " ";
    bool SchoolNight = 0;
    int StartTime = 0;
    string BoardGame = " ";
  
    //read data
    FileIn>>DayofWeek>>SchoolNight>>StartTime;
    
    //series of if statements to decide game
    if(DayofWeek == "Friday" || DayofWeek == "Saturday") 
    {
      BoardGame = "Ticket to Ride";
    }
    else
    {
      if(StartTime == 6)
      {
        if(DayofWeek == "Sunday") 
        {
          BoardGame = "Flash Point";
        }
        
        else 
        {
          BoardGame = "Spirit Island";
        }
      }
      else 
      {
        if(SchoolNight == 1) 
        {
          BoardGame = "Code Names";
        }
        else
        {
          BoardGame = "Settlers of Catan";
        }
      }
    }
    
  //output which game to play
  cout << "On " << DayofWeek << " " << SchoolNight << " " << StartTime
       << " play " << BoardGame << endl;
  }
  
//close file
FileIn.close();

return EXIT_SUCCESS;
}

/*
Test cases: 

On Weekday 1 6 play Spirit Island
On Weekday 1 9 play Code Names
On Weekday 0 9 play Settlers of Catan
On Friday 1 6 play Ticket to Ride
On Sunday 1 6 play Flash Point

--------------------------------
Process exited after 0.04493 seconds with return value 0
Press any key to continue . . .
*/