#include<iostream>
#include<iomanip>
#include<stdlib.h>

using namespace std;

int main()
{
    double  workingHours[5], wages[5];
    double hourlyRates[5] = {9.5, 6.4, 12.5, 5.5, 10.5};
    for (int i = 0; i < 5; i++){
        cin >> workingHours[i];
        wages[i] = hourlyRates[i]*workingHours[i];
    }
    cout << left << setw(30) << "Hourly Rate" << setw(30) << "Working Hour" << "Wage" << endl;
    for (int j = 0; j < 5; j++){
        cout << left << setw(30) <<setprecision(10) << fixed << hourlyRates[j] << setw(30) << workingHours[j] << wages[j] << endl;
    }
    // TODO
    return 0;
}