#include<iostream>
using namespace std;

int linearSearch( int [], int, int);
int main()
{
    int arraySize;
    cin >> arraySize;
    int a[arraySize], searchKey, element;
    for (int x = 0; x < arraySize; x++) // create some data
        a[x] = 2*x;
    cout<< "Enter integer search key: "<< endl;
    cin >> searchKey;
    element = linearSearch(a, searchKey, arraySize);
    if(element != -1)
        cout<<"Found value in element "<< element << endl;
    else
        cout<< "Value not found " << endl;
    return 0;
}
int linearSearch(int array[], int key, int sizeofArray)
{
    for(int n = 0; n< sizeofArray; n++)
    if (array[n] == key)
        return n;
    return -1;
}