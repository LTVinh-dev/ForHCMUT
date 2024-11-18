#include <iostream>
using namespace std;
int checkPrimeNumber(int n)
{
    
    
        int count = 0;
        for (int j = 1; j < n; j++){
            if (n % j == 0) count++;
        }
        if (count == 1) return 1;
        else return 0;
        

    
}
int main() {
    int n;
    cin >> n;
    if (checkPrimeNumber(n))
        cout << n << " is a prime number.";
    else
        cout << n << " is not a prime number.";
    return 0;
}