#include <iostream>
using namespace std;

int main() {
    char code;
    cin >> code;

    switch (code) {
        case 'M':
        case 'm':
            cout << "Individual is married" << endl;
            break;
        case 'D':
        case 'd':
            cout << "Individual is divorced" << endl;
            break;
        case 'W':
        case 'w':
            cout << "Individual is widowed" << endl;
            break;
        default:
            cout << "An invalid code was entered" << endl;
    }

    return 0;
}
