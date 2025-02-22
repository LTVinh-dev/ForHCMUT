// Phần include và khai báo sử dụng thư viện
#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    // Khai báo và nhập vào các giá trị đầu vào
    double bmi, kg, h;	
    cin >> kg>> h;
    bmi = kg/h/h;
    if (bmi < 18.5)
    	cout << "You are Thin and the risk of disease is Low";
    else if (bmi >= 18.5 && bmi <= 25)
    	cout << "You are Normal and the risk of disease is Medium";
    else if (bmi > 25 && bmi <= 30)
    	cout << "You are Overweight and the risk of disease is High";
    else if (bmi > 30 && bmi <= 35)
    	cout << "You are Class 1 Obese and the risk of disease is High";
    else if (bmi > 35 && bmi <= 40)
    	cout << "You are Class 2 Obese and the risk of disease is Very High";
    else 
    	cout << "You are Class 3 Obese and the risk of disease is Extremely High";
    return 0;
}
