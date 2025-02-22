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
    if (n == 1){
        cout << fib[0];
    } else
    cout << fib[0] << " " << fib[1];
    for (int i = 2; i <= n-1; i++){
        fib[i] = fib[i-1] + fib [i-2];
        cout << " " << fib[i] ;
    }
    
    // TODO
    return 0;
}