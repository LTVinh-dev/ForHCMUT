#include <iostream>
#include <cmath>
using namespace std;

int main() {
    double a, b, c;
    cin >> a >> b >> c;

        // Check for Equilateral
        if (a == b && b == c) {
            cout << "The triangle is Equilateral." << endl;
        }
        // Check for Isosceles
        else if (a == b || a == c || b == c) {
            cout << "The triangle is Isosceles." << endl;
        }
        // Check for Right-angled
        else if (pow(a, 2) == pow(b, 2) + pow(c, 2) || 
                 pow(b, 2) == pow(a, 2) + pow(c, 2) || 
                 pow(c, 2) == pow(a, 2) + pow(b, 2)) {
            cout << "The triangle is Right-angled." << endl;
        }
        // Otherwise, it's Scalene
        else {
            cout << "The triangle is Scalene." << endl;
        }

    return 0;
}
