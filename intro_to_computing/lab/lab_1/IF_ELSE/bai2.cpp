#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std; 

int main()
{
    double a, b, c;
    cin >> a >> b >> c;
    if (a == 0) {
        if (b == 0) {
            if (c == 0) {
                cout << "Countless solutions" << endl;
            } else {
                cout << "No solution" << endl;
            }
        } else {
            cout << fixed << setprecision(4) << -c / b << endl;
        }
    } else {
        double d = b * b - 4 * a * c;
        if (d > 0) {
            double x1 = (-b + sqrt(d)) / (2 * a);
            double x2 = (-b - sqrt(d)) / (2 * a);
            cout << fixed << setprecision(4) << x1 << endl;
            cout << fixed << setprecision(4) << x2 << endl;
        } else if (d == 0) {
            double x0 = -b / (2 * a);
            cout << fixed << setprecision(4) << x0 << endl;
        } else {
            double realPart = -b / (2 * a);
            double imaginaryPart = sqrt(-d) / (2 * a);
            cout << fixed << setprecision(4) << realPart << " + " << imaginaryPart << "*i" << endl;
            cout << fixed << setprecision(4) << realPart << " - " << imaginaryPart << "*i" << endl;
        }
    }
    return 0;
}

