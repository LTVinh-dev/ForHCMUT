
#include <cstring>
#include <cmath>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <fstream>

using namespace std;
int minCost = -1;

int pathlength(int graph[30][30], int n, int path[])
{
    int cost = 0;
    for (int i = 0; i < n - 1; ++i)
    {
        cost += graph[path[i]][path[i + 1]];
    }
    cost += graph[path[n - 1]][path[0]]; // Chi phí quay lại điểm xuất phát
    return cost;
}

string Traveling(int graph[30][30], int n, char startPoint)
{
    int cities[30];
    //int minCost = -1;
    for (int i = 0; i < n; ++i)
    {
        cities[i] = i;
    }
    int startVIndex = startPoint - 'A';

    int bestPath[30];
    // Sắp xếp mảng `cities` để startPoint là thành phần đầu tiên
    swap(cities[0], cities[startVIndex]);
    do
    {
        // Đảm bảo lộ trình bắt đầu từ thành phố khởi đầu
        if (cities[0] != startVIndex)
            continue;

        int cost = 0;
        for (int i = 0; i < n - 1; ++i)
        {
            cost += graph[cities[i]][cities[i + 1]];
        }
        cost += graph[cities[n - 1]][cities[0]];

        if (cost < minCost || minCost == -1)
        {
            minCost = cost;
            copy(cities, cities + n, bestPath);
        }
    } while (next_permutation(cities + 1, cities + n));
    // Bỏ qua hoán vị đầu tiên
    // Xây dựng chuỗi kết quả từ lộ trình tốt nhất
    string path;
    for (int i = 0; i < n; ++i)
    {
        path += string(1, 'A' + bestPath[i]) + " ";
    }
    path += startPoint;
    // Quay lại điểm bắt đầu
    cout << "Shortest path: " << path << endl;
    return path;
}

int main()
{
    ifstream fin;
    int G[30][30];
    fin.open("inMat_tv2.txt");
    int n = 12;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            fin >> G[i][j];
        }
    }
    string output = Traveling(G, n, 'C');
    int cost = minCost;
    cout << minCost;
    double partile = 0.1;
    if ((204 - 204 * partile) <= cost && cost <= (204 + 204 * partile))
    {
        cout << "your output is at least 90% correct";
    }
    fin.close();
}