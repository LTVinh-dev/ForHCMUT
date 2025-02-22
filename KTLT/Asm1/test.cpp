#include <iostream>
using namespace std;

int main() {
    int a = 1050;
    int b[5][5] = {
        {150, 200, 180,  90, 110},
        { 70,  80, 120, 140, 160},
        {220, 240, 200, 190, 130},
        {100, 110, 300, 280, 320},
        {170, 210, 260, 230, 290}
    };
    // Write C++ code here
    //cout <<  resupply(1050, b);
    int z = 1;
    for (int i = 0; i < 25-4; i++) {
        for (int j = i + 1; j < 25 - 3; j++) {
            for (int k = j + 1; k < 25 - 2; k++) {
                for (int l = k + 1; l < 25 - 1; l++) {
                    for (int m = l + 1; m < 25; m++) {
                        cout << z << endl;
                        z++;
                    }
                }
            }
        }
    }
                        
    return 0;
}