
#include <cstring>
#include <cmath>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <fstream>

using namespace std;
int minCost = -1; //biến toàn cục để cập nhật trong main

string Traveling(int graph[30][30], int n, char startV)
{
    int startVIndex = startV - 'A';
    int bestPath[30];
    //int minCost = -1;
    int cities[30];
    
    for (int i = 0; i < n; ++i)
    {
        cities[i] = i;
    }
    
    //Sắp xếp mảng "cities" để startV là thành phần đầu tiên
    swap(cities[0], cities[startVIndex]);
    do
    {
        //Đảm bảo lộ trình bắt đầu từ thành phố khởi đầu
        if (cities[0] != startVIndex)
            continue;

        int cost = 0;
        for (int i = 0; i < n - 1; ++i)
        {
            cost += graph[cities[i]][cities[i + 1]];
            if (graph[cities[i]][cities[i + 1]] == 0)
            {
            cost = pow(2,30);
            break;
            }
        }
        cost += graph[cities[n - 1]][cities[0]];

        if ((cost < minCost || minCost == -1) && (graph[cities[n - 1]][cities[0]] != 0))
        {
            minCost = cost;
            copy(cities, cities + n, bestPath);
        }
    } while (next_permutation(cities + 1, cities + n));
    //Không hoán vị vị trí đầu tiên
    
    string path;
    for (int i = 0; i < n; ++i)
    {
        path += string(1, 'A' + bestPath[i]) + " ";
    }
    path += startV;
    //Thêm điểm bắt đầu vào cuối chuỗi
    
    //cout << "Shortest path: " << path << endl;
    return path;
}

int main()
{
    ifstream fin;
    int G[30][30];
    fin.open("Trave_in14.txt");
    int n = 14;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            fin >> G[i][j];
        }
    }
    string output = Traveling(G, n, 'A');
    int cost = minCost;
    cout << output << endl;
    cout << minCost << endl;
    //double partile = 0;
    //if ((204 - 204 * partile) <= cost && cost <= (204 + 204 * partile))
    //{
    //    cout << "your output is correct";
    //}
    fin.close();
}