#include <iostream>
using namespace std;

int main() {
    double angle;
    cin >> angle;

    if (angle >= 0 && angle < 90) {
        cout << "first quadrant" << endl;
    } else if (angle >= 90 && angle < 180) {
        cout << "second quadrant" << endl;
    } else if (angle >= 180 && angle < 270) {
        cout << "third quadrant" << endl;
    } else if (angle >= 270 && angle < 360) {
        cout << "fourth quadrant" << endl;
    } else {
        cout << "not exist" << endl;
    }

    return 0;
}
