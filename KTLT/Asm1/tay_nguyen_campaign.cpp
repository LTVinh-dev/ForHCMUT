#include "tay_nguyen_campaign.h"

////////////////////////////////////////////////////////////////////////
/// STUDENT'S ANSWER BEGINS HERE
/// Complete the following functions
/// DO NOT modify any parameters in the functions.
////////////////////////////////////////////////////////////////////////

const int MAX_LINES = 5;         
const int MAX_LINE_LENGTH = 100;

// Task 0: Read input file
bool readFile(
    const string &filename,
    int LF1[], int LF2[],
    int &EXP1, int &EXP2,
    int &T1, int &T2, int &E)
{
  char data[MAX_LINES][MAX_LINE_LENGTH];
  int numLines = 0;

  ifstream ifs(filename);
  if (!ifs.is_open())
  {
    return false;
  }

  while (numLines < MAX_LINES && ifs.getline(data[numLines], MAX_LINE_LENGTH))
  {
    numLines++;
  }
  ifs.close();

  if (numLines < MAX_LINES)
  {
    return false;
  }

  // TODO: Extract values from the `data` array and store them in respective variables

  return true;
}

// Task 1
int gatherForces(int LF1[], int LF2[])
{
  // TODO: Implement this function
  return 0;
}

// Task 2
string determineRightTarget(const string &target)
{
  // TODO: Implement this function
  return "INVALID";
}

string decodeTarget(const string &message, int EXP1, int EXP2)
{
  // TODO: Implement this function
  return "INVALID";
}

// Task 3
void manageLogistics(int LF1, int LF2, int EXP1, int EXP2, int &T1, int &T2, int E)
{
  // TODO: Implement this function
}

// Task 4
int planAttack(int LF1, int LF2, int EXP1, int EXP2, int T1, int T2, int battleField[10][10])
{
  // TODO: Implement this function
  return 0;
}

// Task 5
int resupply(int shortfall, int supply[5][5])
{
  // TODO: Implement this function
  return 0;
}

////////////////////////////////////////////////
/// END OF STUDENT'S ANSWER
////////////////////////////////////////////////
