#include <iostream>
using namespace std;
int getMaxElement(int arr[], int n)
{
    int max = arr[0];
    for (int i = 1; i <= n-1;i++){
        if (arr[i] > max)
        max = arr[i];
    }
    return max;

}
int main()
{
    int n;
    cin>>n;
    int ar[n];
    for(int i=0;i<n;i++) cin>>ar[i];
    cout<<getMaxElement(ar,n);
    return 0;
}