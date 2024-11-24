#include <cmath>
#include <iostream>
#include <string>
using namespace std;
/******************************************************************************
 * Support Functions: these functions below are optional. If you want your code
                      to be clearer, you can implement them. However if you
                      dont know how to use funtion in programming, dont worry, 
                      you dont have to implement them, and you just add a comment 
                      in each of them.
*******************************************************************************/
int move(string moves)
{
    /*TODO: add your code here*/
    int x = 0, y=0;
    for (long unsigned int i = 0; i < moves.length(); i += 2){
        if (moves[i] == 'U')
        {
            y += (moves[i+1] - '0');
        }
        if (moves[i] == 'D')
        {
            y -= (moves[i+1] - '0');
        }
        if (moves[i] == 'R')
        {
            x += (moves[i+1] - '0');
        }
        if (moves[i] == 'L')
        {
            x -= (moves[i+1] - '0');
        }
        
    }
    return round(sqrt(x * x + y * y));
}
bool isPrime(int n)
{
    /*TODO: add your code here*/
    
    if (n <= 1) {
        return false;
    }
    // Số 2 và 3 là số nguyên tố
    if (n <= 3) {
        return true;
    }
    // Loại trừ các số chia hết cho 2 hoặc 3
    if (n % 2 == 0 || n % 3 == 0) {
        return false;
    }
    // Kiểm tra các số từ 5 đến căn bậc hai của n
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) {
            return false;
        }
    }
    return true;
}


bool isSquared(int n) {
    if (n < 0) return false;
    int sqrt_num = sqrt(n);
    return (sqrt_num * sqrt_num == n);
}

int main()
{
    string moves;
    int distance;
    bool primality, squared;
    /// =======================================================
    /*
        The following code initializes variable `moves`
    */
    /// BEGIN   TESTCASE
    cin >> moves;
    /// END     TESTCASE
    /*---------------------------------
        * Calculate the distance
        * Remember to assign calculated value to variable `distance`
    */
    /*TODO: add your code here*/
    distance = move(moves);
    
    /*---------------------------------*/
    cout << "The distance the vehicle has moved from the origin to the current point is: "<< distance << '\n';

    /*---------------------------------
        * Check if distance is prime
        * Remember to assign appropriate value to variable `primality`
    */
    /*TODO: add your code here*/
    primality = isPrime(distance);
    squared = isSquared(distance);
    /*---------------------------------*/
    /*---------------------------------
        * Check if distance is squared
        * Remember to assign appropriate value to variable `squared`
    */
    /*TODO: add your code here*/
    
    /*---------------------------------*/
    if (primality) {
        cout << "Number " << distance << " is prime number\n";
    }
    if (squared) {
        cout << "Number " << distance << " is square number\n";
    }
    return 0;
}