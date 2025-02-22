#include<iostream>
#include<iomanip>
#include<stdlib.h>
#include<math.h>
using namespace std;
int main()
{
    int N;
    float max = 0, a;
    cin >> N;
    for (int i = 0; i < N; i++){
        cin >> a;
        (a>max)? max=a:1;
    }
    cout << setprecision(2) << fixed << max;
    return 0;
    // TODO
    
}