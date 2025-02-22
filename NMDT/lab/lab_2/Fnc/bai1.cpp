#include <iostream>
#include <string>
#include <cmath>
using namespace std;
int convertBinaryToDecimal(string n)
{
    int decNum;
    for (int i=0; i<= n.length()-1; i++){
        string temp(n, n.length()-1-i,1);
        if (temp == "1"){
            decNum += pow(2, i);
        }
    }
    return decNum;
    //TODO
}
int main()
{
    string n;
    cin >> n;
    cout << n << " in binary = " << convertBinaryToDecimal(n) << " in decimal";
    return 0;
}