#include <cstring>
#include "bellman.h"

string BF_Path(int graph[30][30], int numV, char startV, char endV) {
    
    int startVIndex = startV - 'A'; 
    int endVIndex = endV - 'A';

    int value[30], preV[30];
    int valueCopy[30], preVCopy[30];
    int graphValue[30][30], graphPrevious[30][30];

    //Khởi tạo giá trị
    for (int i = 0; i < numV; ++i) {
        valueCopy[i] = -1;  
        preVCopy[i] = -1; 
    }

    valueCopy[startVIndex] = 0;
    preVCopy[startVIndex] = startVIndex;

    //Lặp tối đa số bước
    for (int k = 1; k < numV; k++) {
        for (int i = 0; i < numV; ++i) {
            value[i] = valueCopy[i];
            preV[i] = preVCopy[i];
        }

        for (int u = 0; u < numV; ++u) {
            for (int v = 0; v < numV; ++v) {
                if (graph[u][v] == 0 || value[u] == -1) continue;

                if ((value[u] + graph[u][v]) < valueCopy[v] || valueCopy[v] == -1) {
                    valueCopy[v] = value[u] + graph[u][v];
                    preVCopy[v] = u;
                }
            }
        }

        for (int i = 0; i < numV; ++i) {
            graphValue[k][i] = valueCopy[i];
            graphPrevious[k][i] = preVCopy[i];
        }
    }

    //Truy ngược đường đi từ đỉnh cuối
    int pathReserve[30], path[30];
    int count = 0, n = endVIndex;

    //Truy ngược từ endVIndex về startVIndex
    while (n != startVIndex && n != -1) {
        pathReserve[count++] = n;
        n = preVCopy[n];
    }

    if (n == -1) return " ";

    //Đỉnh đầu tiên trong đường đi
    pathReserve[count++] = startVIndex;

    //Đảo ngược startVIndex => endVIndex
    for (int i = 0; i < count; ++i) {
        path[i] = pathReserve[count - 1 - i];
    }

    // Tạo kết quả
    string result;
    for (int i = 0; i < count; ++i) {
        result += ('A' + path[i]);  //Index thành char
        if (i < count - 1) {
            result += ' ';
        }
    }

    return result;
}