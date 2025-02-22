#include<iostream>
using namespace std;

int reverseNum(int n)
{
    int reversedNum = 0;
    while (n!=0){
        reversedNum = reversedNum * 10 + (n % 10);
        n /= 10;
    }
    return reversedNum;
}
int main()
{
    int n;
    cin>>n;
    cout<<reverseNum(n);
    return 0;
}