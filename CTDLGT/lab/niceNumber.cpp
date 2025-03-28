// Nice number contain only 2 and 5
// first nice number is 2, then 5,...
// 2, 5, 22, 25, 52, 55, 222, 225, 252, 255, 522, 525, 552, 555 




#include <iostream>
#include <queue>
using namespace std;

int main()
{
    int n = 100000;
    
    int digit = 1;
    int level = 2;
    while (n > level)
    {
        n -= level;
        level = level*2;
        digit++;
    }

    queue<int> bin;
    n--;
    if (n==0) bin.push(0);
    while (n > 0)
    {
        bin.push((n%2));
        n = n/2;
    }
    // queue<int> bin1=bin;
    // while (!bin1.empty()) {
    //     cout << bin1.front();
    //     bin1.pop();
    // }
    cout << digit;
    cout << endl;
    long long num = 0.0;
    num += (bin.front())?5:2;
    bin.pop();
    for (int i=2; i<=digit;i++)
    {
        long long dec = 1;
        for (int j=1;j<i;j++)
        {
            dec *= 10;
        }
        num += ((bin.front())?5:2)*dec;
        bin.pop();
    }
    
    cout << num;
    return 0;

}