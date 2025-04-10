
#include <iostream>
#include <vector>
using namespace std;
int main() {
    // Write C++ code here
    vector<int> num = { 4,4,2,1,2 };
    int target = 6;
    int size = num.size();
    vector<int> inx = { -1,-1,-1,-1,-1 };
    int cur = 0;
    for (int i = 0;i < size - 1;i++)
    {
        for (int j = i + 1;j < size;j++)
        {
            if (num[i] + num[j] == target)
            {
                bool canAdd = true;
                for (int k = 0;k <= cur;k++)
                {
                    if (inx[k] == i || inx[k] == j)
                    {
                        canAdd = false;
                        break;
                    }
                }
                if (canAdd)
                {
                    inx[cur] = i;
                    inx[cur + 1] = j;
                    cur = cur + 2;
                }
            }
        }
    }
    // for (int i=0;i<size;i++){
    //     cout << inx[i] << " ";
    // }
    // cout << inx[5];
    // cout << endl;
    cout << cur / 2;
    return 0;
}