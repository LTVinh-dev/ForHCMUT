#include <iostream>
using namespace std;
void printPrimes(int lower, int upper)
{
    
    for (int i = lower; i <= upper; i++){
        int count = 0;
        for (int j = 1; j < i; j++){
            if (i % j == 0) count++;
        }
        if (count == 1) cout << i << " ";
        
    }
    
}
int main()
{
    int lower, upper;
    cin>>lower;
    cin>>upper;
    // Calling function to print all primes between the given range.
    printPrimes(lower, upper);
    return 0;
}