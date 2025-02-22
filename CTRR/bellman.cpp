#include "bellman.h"
#include <iostream>

void BF(int graph[30][30], int numV, char startV, int value[], int preV[])
{
    int startVIndex = startV - 'A'; // char thành số, cách tham chiếu của chương trình

    value[startVIndex] = 0; // k.cách tới chính nó = 0. Đây là step 0, khi mọi khoảng cách khác là vô cùng.

    // Phải có bản copy vì ta sẽ cập nhật giá trị khoảng cách hiện tại khi quét đồ thị. Không có bản copy sẽ làm giá trị bị thay đổi nhiều lần. Trong khi 1 bước chỉ đi từ 1 đỉnh
    int valueCopy[30];
    for (int i = 0; i < numV; i++)
    {
        valueCopy[i] = value[i];
    }

    for (int u = 0; u < numV; u++)
    { // quét đầy đủ tất cả hàng, cột trong ma trận đồ thị
        for (int v = 0; v < numV; v++)
        {
            // value[u] = -1 nghĩa là giá trị khoảng cách của đỉnh u là vô cùng. Giá trị giữa 2 đỉnh trong ma trận = 0 là ko kết nối
            if ((graph[u][v] != 0) && (valueCopy[u] != -1))
            {
                // Nếu khoảng cách mới nhỏ hơn khoảng cách hiện tại của v, cập nhật giá trị. Kcách hiện tại tới đỉnh v bằng vô cùng cũng sẽ bị cập nhật
                if (((valueCopy[u] + graph[u][v]) < value[v]) || (value[v] == -1))
                {
                    value[v] = valueCopy[u] + graph[u][v];
                    preV[v] = u;
                }
            }
        }
    }
}

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