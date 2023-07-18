/*
Author: Michael McPhee
Version: 1.0
Date: November 9, 2022
Program that reads files and organizes UW parking lot
Assume valid file format
*/

#include <iostream>
#include <fstream>
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <iomanip>

using namespace std;

//initialize global constants
const int NUM_ROWS = 50;
const int BEST_SPOT = 25;
const int NUM_ADD = 22;
const int NUM_REMOVE = 25;

//function to read current parking file
void current_parking (ifstream & FileInCurrent, string names [], int staff [])
{
  //initialize
  int status = 0;
  string name = " ";
  int parking_spot = 0;
  
  //set all status to -1, full spots will override this, empty spots stay at -1
  for(int i = 0; i < NUM_ROWS; i++)
  {
    staff[i] = -1;
  }
  
  //read from  file, using parking spot at the index for 2 parallel arrays
  while (FileInCurrent >> status >> name >> parking_spot)
  {
    names[parking_spot - 1] = name;
    staff[parking_spot - 1] = status;
  }
}

//function to read from add/remove parking files
void change_parking (ifstream & FileIn, string names[], int staff[])
{
  //initialize
  int status = 0;
  string name = " ";
  int spot = 0;

  //read from file storing info in 2 parallel arrays
  while (FileIn >> status >> name)
  {
    names[spot] = name;
    staff[spot] = status;
    spot++;
  }
}

//function to remove names from current parking arrays
void remove_name (string names[], int staff [], string name)
{
  //initialize variable to break loop when person is removed
  bool person_removed = false;
  
  /*in this loop we must look backwards through the arrays, since the staff
  priority function first adds a name earlier in the arrray before deleting a 
  name, and we want to delete the second copy of their name*/
  
  for (int i = NUM_ROWS; (i >= 0) && (!person_removed); i--)
  {
    //if name to be deleted matches name in array
    if (name == names[i])
    {
      //remove entry from arrays
      names [i] = " ";
      staff [i] = -1;
      person_removed = true;
    }
  }
}

//function to find lowest available parking spot
int lowest_valid_spot (string names[], int staff[], int isStaff)
{
  
  int starting_spot = 0;
  if (isStaff == 0) 
  {
    starting_spot = BEST_SPOT; //if student starting spot is 25
  }
  else starting_spot = 0; //if staff starting spot is 0
  
  for(int spot = starting_spot; spot < NUM_ROWS; spot++)
  {
    if (staff[spot] == -1) //if empty return parking spot number
    {
      return spot;
    }
  }
  return -1; //no spot available
}

//function that adds name and status to arrays
bool add_name (string names[], int staff[], string name, int isStaff)
{
  //call lowest available parking spot function
  int location = lowest_valid_spot(names, staff, isStaff);
  

  if (location == -1)
  {
    cout << name << " could not be added" << endl; //if no space available
    return false;
  }
  
  //store name and status in the empty spot
  names[location] = name;
  staff[location] = isStaff;
  return true;
}

//function that reorganizes staff to priority parking spots
void staff_priority (string names[], int staff[])
{
  //searches spots 25-50 for staff
  for (int spot = BEST_SPOT; spot < NUM_ROWS; spot++)
  {
    if (staff[spot] == 1)
    {
      //checks for open spots
      bool open_spot = add_name(names, staff, names[spot], staff[spot]);
      if (open_spot) remove_name(names, staff, names[spot]); //delete old entry      
    }
  }
}

//output updated arrays
void output (ofstream & FileOut, string names[], int staff[])
{
  for (int spot = 0; spot < NUM_ROWS; spot++)
  {
    if (staff[spot] != -1)
    {
      FileOut << staff[spot] << setw(20) << names[spot] 
              << setw(5) << spot + 1 << endl;
    }
  }
}


int main()
{
 //initialize arrays
 string current_names [NUM_ROWS] = {" "};
 int current_staff [NUM_ROWS] = {0};
 
 string remove_names [NUM_REMOVE] = {" "};
 int remove_staff [NUM_REMOVE] = {0};
 
 string add_names [NUM_ADD] = {" "};
 int add_staff [NUM_ADD] = {0};

 //open files to read 
 ifstream FileInCurrent ("parking_current.txt");
 ifstream FileInRemove ("parking_remove.txt");
 ifstream FileInAdd ("parking_add.txt");
 
 //check if able to access files
 if (!FileInCurrent||!FileInRemove||!FileInAdd)
 {
   cout << "Unable to open  file.";
   return EXIT_FAILURE;
 }
 
 //store current parking data in array
 current_parking (FileInCurrent, current_names, current_staff);
 
 //store remove parking data in array
 change_parking (FileInRemove, remove_names, remove_staff);

 //remove people
 for (int spot = 0; spot < NUM_REMOVE; spot++)
 {
   remove_name (current_names, current_staff, remove_names[spot]);
 }

 //prioritize staff to new open spots
 staff_priority (current_names, current_staff);
 
 //store add parking data in array
 change_parking (FileInAdd, add_names, add_staff);
 
 //add people
 for (int spot = 0; spot < NUM_ADD; spot++)
 {
   add_name(current_names, current_staff, add_names[spot], add_staff[spot]);
 }
 
 //output to file
 ofstream FileOut("parking_final.txt");
 
 //first subject row
 FileOut << "Status" << setw(10) << "Name" << setw(15) << "Spot #" << endl;
 
 //call output function
 output(FileOut, current_names, current_staff);
 
 //close files
 FileOut.close();
 FileInAdd.close();
 FileInRemove.close();
 FileInCurrent.close();
 
 return EXIT_SUCCESS;
}
/*
OUTPUT FROM FILE:

Status      Name         Spot #
1     Teertstra_Peter    1
1        Milne_Andrew    2
1         Hulls_Carol    3
1       Rennick_Chris    4
1     Musselman_Kevin    5
1           Owen_Bill    6
1     Nassar_Mohammed    7
1      Lokker_Shirley    8
1       Trelford_Ryan    9
0        Lovelace_Ada   10
1         Davison_Dan   11
1        Grguc_Andrew   12
1      Casale_Matthew   13
1       Brown_Natalie   14
0           Bell_Alex   15
1      Beltaos_Andrew   16
1    Strickland_Donna   18
1         Nairn_David   20
1        Consell_Ryan   21
1      Gerlich_Adrian   23
1  Vandekerckhove_Sam   25
0        Payette_Jill   26
0          Eiffel_Gus   27
0        Wozniak_Stef   28
0           Turing_Al   29
0        Akter_Sabiha   30
0        Archimedes_A   31
0        da_Vinci_Leo   32
0      Stephenson_Geo   33
0          Imahara_Gr   34
0        Hopper_Grace   35
0            Oh_Henry   36
0             Tepe_Go   37
0          Clarke_Edi   38
0         Roebling_Em   39
0         Jemison_May   40
0          Woods_Gran   41
0   Moniz_Christopher   42
0         Johnson_Kat   43
0         Vaughan_Dot   44
0        Babbage_Chip   45
0            Tlaa_Sha   46
0            Dyck_Lil   47
0          Curie_Mary   48
0       Stroustrup_Bj   49
0           Imhotep_P   50
*/