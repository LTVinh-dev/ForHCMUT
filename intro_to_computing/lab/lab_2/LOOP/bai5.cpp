#include<iostream>
#include<iomanip>
#include<stdlib.h>
#include<math.h>
using namespace std;
int main()
{
    int N;
    float pcount = 0, ncount = 0, a;
    cin >> N;
    for (int i = 0; i < N; i++){
        cin >> a;
        (a >= 0)? pcount++ : ncount++;
    }
    cout << pcount << " " << ncount;
    return 0;
    // TODO
    
}