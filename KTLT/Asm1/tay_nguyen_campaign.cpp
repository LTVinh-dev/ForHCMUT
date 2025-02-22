#include "tay_nguyen_campaign.h"

////////////////////////////////////////////////////////////////////////
/// STUDENT'S ANSWER BEGINS HERE
/// Complete the following functions
/// DO NOT modify any parameters in the functions.
////////////////////////////////////////////////////////////////////////

const int MAX_LINES = 5;
const int MAX_LINE_LENGTH = 100;

void convertToIntaay(const char *input, int LF[], int lower_limit, int upper_limit, char delim)
{
  string str(input);

  // Loại bỏ dấu [ và ]
  if (str.front() == '[')
    str.erase(0, 1);
  if (str.back() == ']')
    str.pop_back();

  stringstream ss(str); // Tạo luồng chuỗi
  string token;
  int index = 0;

  while (getline(ss, token, delim))
  {
    int num = stoi(token);

    // Giới hạn giá trị trong khoảng [lower_limit, upper_limit]
    if (num > upper_limit)
      num = upper_limit;
    if (num < lower_limit)
      num = lower_limit;

    LF[index] = num;
    index++;
  }
}

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

  // TODO: Extract values from the `data` aay and store them in respective variables

  convertToIntaay(data[0], LF1, 0, 1000, ',');
  convertToIntaay(data[1], LF2, 0, 1000, ',');
  int temp1[2], temp2[2], temp3[1];
  convertToIntaay(data[2], temp1, 0, 600, ' ');
  EXP1 = temp1[0];
  EXP2 = temp1[1];
  convertToIntaay(data[3], temp2, 0, 3000, ' ');
  T1 = temp2[0];
  T2 = temp2[1];
  convertToIntaay(data[4], temp3, 0, 99, ' ');
  E = temp3[0];
  // cout << EXP1 << " " << EXP2 << " " << T1 << " " << T2 << " " << E << " ";
  return true;
}

// Task 1
int gatherForces(int LF1[], int LF2[])
{
  // TODO: Implement this function
  int LF1_p, LF2_p;
  for (int i = 0; i < 17; i++)
  {
    LF1_p += LF1[i] * (i + 1);
    LF2_p += LF2[i] * (i + 1);
  }
  return LF1_p + LF2_p;
}

// Task 2
string determineRightTarget(const string &target)
{
  // TODO: Implement this function
  int length = target.size();
  int count = 0;
  int ID[3];
  int targetID = 0;

  for (int i = 0; i < length; i++)
  {
    if (target[i] >= '0' && target[i] <= '9')
    { // Kiểm tra ký tự theo ASCII

      if (count < 3)
      { // Chỉ lưu tối đa 3 phần tử
        ID[count] = target[i] - '0';
      }
      count++;
    }
  }
  switch (count)
  {
  case 1:
    targetID = ID[0];
    break;
  case 2:
    targetID = ((ID[0] + ID[1]) % 5) + 3;
    break;
  case 3:
  {
    int max = ID[0];
    for (int i = 0; i < 3; i++)
    {
      if (ID[i] > max)
        max = ID[i];
    }
    targetID = (max % 5) + 3;
    break;
  }
  default:
    return "INVALID";
    break;
  }
  switch (targetID)
  {
  case 0:
    return "DECOY";
    break;
  case 1:
    return "DECOY";
    break;
  case 2:
    return "DECOY";
    break;
  case 3:
    return "Buon Ma Thuot";
    break;
  case 4:
    return "Duc Lap";
    break;
  case 5:
    return "Dak Lak";
    break;
  case 6:
    return "National Route 21";
    break;
  case 7:
    return "National Route 14";
    break;
  default:
    return "INVALID";
    break;
  }
}

string decodeTarget(const string &message, int EXP1, int EXP2)
{
  // TODO: Implement this function
  string tempDecode;
  int lenght = message.size();
  if (EXP1 >= 300 && EXP2 >= 300)
  {
    int shift = (EXP1 + EXP2) % 26;
    for (int i = 0; i < lenght; i++)
    {
      char c = message[i];
      if (!((c >= 'A' && c <= 'Z') ||
            (c >= 'a' && c <= 'z') ||
            (c >= '0' && c <= '9') ||
            (c == ' ')))
      {
        return "INVALID";
      }
      else if (c >= 'A' && c <= 'Z')
      {
        tempDecode += (c - 'A' + shift) % 26 + 'A';
      }
      else if (c >= 'a' && c <= 'z')
      {
        tempDecode += (c - 'a' + shift) % 26 + 'a';
      }
      else if ((c >= '0' && c <= '9') || (c == ' '))
        tempDecode += c;
    }
  }
  else
  {
    for (int i = 0; i < lenght; i++)
    {
      char c = message[lenght - i - 1];
      tempDecode += c;
    }
  }

  if (tempDecode == "Buon Ma Thuot" || tempDecode == "Duc Lap" || tempDecode == "Dak Lak" || tempDecode == "National Route 21" || tempDecode == "National Route 14")
  {
    return tempDecode;
  }
  return "INVALID";
}

// Task 3
void manageLogistics(int LF1, int LF2, int EXP1, int EXP2, int &T1, int &T2, int E)
{
  // TODO: Implement this function
  if (E >= 60 && E <= 99)
  {
    return; // Đường tiếp tế bị gián đoạn, không điều chỉnh
  }
  int totalSupply = T1 + T2;
  double deltaT1 = round(((double)LF1 / (LF1 + LF2)) * totalSupply * (1 + (EXP1 - EXP2) / 100.0));
  double deltaT2 = totalSupply - deltaT1;
  if (E == 0)
  {
    T1 += deltaT1;
    T2 += deltaT2;
  }
  else if (E >= 1 && E <= 9)
  {
    T1 -= round((E * 0.01) * T1);
    T2 -= round((E * 0.005) * T2);
  }
  else if (E >= 10 && E <= 29)
  {
    T1 += E * 50;
    T2 += E * 50;
  }
  else if (E >= 30 && E <= 59)
  {
    T1 += round((E * 0.005) * T1);
    T2 += round((E * 0.002) * T2);
  }
  if (T1 > 3000)
    T1 = 3000;
  if (T1 < 0)
    T1 = 0;
  if (T2 > 3000)
    T2 = 3000;
  if (T2 < 0)
    T2 = 0;
}

// Task 4
int planAttack(int LF1, int LF2, int EXP1, int EXP2, int T1, int T2, int battleField[10][10])
{
  // TODO: Implement this function
  double S = (LF1 + LF2) + (EXP1 + EXP2) * 5 + (T1 + T2) * 2;

  for (int i = 0; i < 10; ++i)
  {
    for (int j = 0; j < 10; ++j)
    {
      if (i % 2 == 1)
        S = S - (battleField[i][j] * 3.0 / 2);
      else
        S = S - (battleField[i][j] * 2.0 / 3);
    }
  }
  int result = ceil(S);
  return result;
}

// Task 5
int resupply(int shortfall, int supply[5][5])
{
  // TODO: Implement this function
  int a[25];
  int minSum = 3001;
  for (int i = 0; i < 5; i++)
  {
    for (int j = 0; j < 5; j++)
    {
      a[i * 5 + j] = supply[i][j];
    }
  } // copy mảng 2 chiều thành 1 chiều
  for (int i = 0; i < 25 - 4; i++)
  {
    for (int j = i + 1; j < 25 - 3; j++)
    {
      for (int k = j + 1; k < 25 - 2; k++)
      {
        for (int l = k + 1; l < 25 - 1; l++)
        {
          for (int m = l + 1; m < 25; m++)
          {
            int sum = a[i] + a[j] + a[k] + a[l] + a[m];
            if (sum >= shortfall && sum < minSum)
            {
              minSum = sum;
            }
          }
        }
      }
    }
  }
  return minSum;
}

////////////////////////////////////////////////
/// END OF STUDENT'S ANSWER
////////////////////////////////////////////////
