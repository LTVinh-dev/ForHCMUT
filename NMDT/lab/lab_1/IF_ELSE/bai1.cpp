#include <iostream>
#include <iomanip>
using namespace std;
int main()
{
    float t, o;
    int s;
    cin >> s >> t;
    switch (s)
    {
    case 1:
        {
            o = (5.0/9)*(t - 32);
            cout << o;
            break;
        }
    case 2:
        {
            o = (9.0 / 5) * t + 32;
            cout << o;
            break;
        }
    default:
        cout << "Invalid option";
        break;
    }
    return 0;
    //test
}