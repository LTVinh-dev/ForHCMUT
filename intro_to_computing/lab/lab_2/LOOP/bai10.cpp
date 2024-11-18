#include<iostream>
#include<iomanip>
#include<stdlib.h>

using namespace std;
int main()
{
    int n;
    cin >> n;
    int a[100][100], b [100][100];
    for (int i = 0; i <= n-1; i++){
        for (int j = 0; j <= n-1; j++){
            cin >> a[i][j];
        }
    }
    for (int i = 0; i <= n-1; i++){
        for (int j = 0; j <= n-1; j++){
            b[i][j] = a[i][j];
        }
    }
    for (int i = 0; i <= n-1; i++){
        for (int j = 0; j <= n-1; j++){
            a[i][j] = a[j][i];
        }
    }
    for (int i = 0; i <= n-1; i++){
        for (int j = 0; j <= i-1; j++){
            a[i][j] = b[j][i];
        }
    }
    for (int i = 0; i <= n-1; i++){
        for (int j = 0; j <= n-1; j++){
            cout << a[i][j] << " ";
        }
        cout << endl;
    }
    // TODO
    return 0;
}