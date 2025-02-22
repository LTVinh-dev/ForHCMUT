#include<iostream>
#include<iomanip>
#include<stdlib.h>
#include<math.h>

using namespace std;
int main()
{
    float pi = 3.14;
    for (int i = 5; i <= 85; i+= 5){
        cout << setprecision(2) << fixed << sin(i*pi/180) << " " << cos(i*pi/180) << " " << tan(i*pi/180) << endl;
    }
    // TODO
    
}