#include<iostream>
#include<iomanip>
#include<stdlib.h>
#include<math.h>

using namespace std;

const int maxnum = 90;
int main()
{
    long fib[maxnum] = {0,1};
    int n;
    cin >> n;
    for (int i = 2; i <= n-1; i++){
        fib[i] = fib[i-1] + fib [i-2];
    }
    cout << fib[n-1];
    // TODO
    
}