#include<iostream>
#include<iomanip>
#include<string.h>

using namespace std;

const int MAX = 100;

struct student{
    char name[20];
    long int rollno;
    char sex;
    float height;
    float weight;
};

int main() {
    student cls[MAX];
    int i,n;
    float sumh = 0, sumw = 0; 
    cout << "How many names ? \n";
    cin >> n;

    for (i = 0; i <= n-1; ++i){
        cout << "record = "<< i+1 << endl;
        cout << "name : "; cin>> cls[i].name;
        cout << "rollno : "; cin>> cls[i].rollno;
        cout << "sex : "; cin>> cls[i].sex;
        cout << "height : "; cin>> cls[i].height;
        cout << "weight : "; cin>> cls[i].weight;
        cout << endl;
        sumh += cls[i].height;
        sumw += cls[i].weight;
    }
    cout << left << setw(20) << "Name" << setw(20) << "Rollno" << setw(20) << "Sex" << setw(20) << "Height" << "Weight" << endl;
    for (int j = 0; j <= n-1; j++){
        cout << left << setw(20) <<setprecision(2) << fixed << cls[j].name << setw(20) << cls[j].rollno << setw(20) << cls[j].sex << setw(20) << cls[j].height  <<  cls[j].weight << endl;
    }
    cout << setprecision(5) << fixed << (sumh/n) << " " << (sumw/n);
    // TODO
    return 0;
}