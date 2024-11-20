#include<iostream>
#include<iomanip>
#include<stdlib.h>
#include<math.h>
using namespace std;
int main()
{
    int N;
    float sum = 0, a;
    cin >> N;
    for (int i = 0; i < N; i++){
        cin >> a;
        sum += a;
    }
    cout << setprecision(2) << fixed << (sum*1.0/N);
    return 0;
    //test
}