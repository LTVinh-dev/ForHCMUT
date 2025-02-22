#include "bellman.h"
#include <cstring>
#include <cmath>
#include <fstream>
#include <iostream>

using namespace std;

int main()
{
    ifstream fin;
    int G[30][30];
    int G2[30][30];
    int BFValue[30];
    int BFPrev[30];
    fin.open("inMat1.txt");
    int n = 8;
    for (int i = 0; i < n; i++)
    {
        BFValue[i] = -1;
        BFPrev[i] = -1;
        for (int j = 0; j < n; j++)
        {
            fin >> G[i][j];
        }
    }
    fin.close();
    fin.open("inMat2.txt");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            fin >> G2[i][j];
        }
    }
    for (int i = 0; i < n; i++)
    {
        if (i % 2)
            BF(G, n, 'D', BFValue, BFPrev);
        else
            BF(G2, n, 'D', BFValue, BFPrev);
        cout << "step" << i + 1 << ":" << endl;
        for (int j = 0; j < n; j++)
        {
            cout << BFValue[j] << " ";
        }
        cout << endl;
        for (int j = 0; j < n; j++)
        {
            cout << BFPrev[j] << " ";
        }
        cout << endl;
    }
    fin.close();
    cout << "=====BF_path=====" << endl;
    
    fin.open("inMat1.txt");
    for (int i = 0; i < n; i++)
    {
        BFValue[i] = -1;
        BFPrev[i] = -1;
        for (int j = 0; j < n; j++)
        {
            fin >> G[i][j];
        }
    }
    cout << BF_Path(G, n, 'A', 'D');
    fin.close();
}