#include <iostream>
using namespace std;

int main() {
    double num;
    cin >> num;

    if (num > 0) {
        cout << num << " is a positive number." << endl;
    } else if (num < 0) {
        cout << num << " is a negative number." << endl;
    } else {
        cout << num << " is zero." << endl;
    }

    return 0;
}
