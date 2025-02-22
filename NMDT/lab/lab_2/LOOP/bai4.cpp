#include<iostream>
#include<iomanip>
#include<stdlib.h>

using namespace std;
int main()
{
    int n;
    double positivePower =1, negativePower =1, number;
    cin >> n;
    cin >> number;
    for (int i = 0; i <= n-1; i++){
        positivePower *= number;
        negativePower /= number;
    }
    cout << setprecision(2) << fixed << positivePower << " " << negativePower;
    // TODO
    return 0;
}