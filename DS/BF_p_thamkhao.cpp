string BF_Path(int graph[][30], int numVertices, char start, char end) {
    int startIndex = start - 'A';  // Chuyển ký tự đỉnh bắt đầu thành chỉ số
    int endIndex = end - 'A';

    // Kiểm tra đồ thị có trọng số âm không
    for (int i = 0; i < numVertices; ++i) {
        for (int j = 0; j < numVertices; ++j) {
            if (graph[i][j] < 0) {
                return "Đồ thị không hợp lệ (trọng số âm)!";
            }
        }
    }

    int Value[30], Previous[30];
    int Value1[30], Previous1[30];
    int graphValue[30][30], graphPrevious[30][30];

    // Khởi tạo giá trị ban đầu
    for (int i = 0; i < numVertices; ++i) {
        Value1[i] = -1;  // Khoảng cách ban đầu là vô cùng
        Previous1[i] = -1; // Chưa có đỉnh trước
    }

    Value1[startIndex] = 0;
    Previous1[startIndex] = startIndex;

    // Lặp qua tất cả các bước Bellman-Ford
    for (int k = 1; k < numVertices; ++k) {
        for (int i = 0; i < numVertices; ++i) {
            Value[i] = Value1[i];
            Previous[i] = Previous1[i];
        }

        for (int u = 0; u < numVertices; ++u) {
            for (int v = 0; v < numVertices; ++v) {
                if (graph[u][v] == 0 || Value[u] == -1) continue;

                int newDistance = Value[u] + graph[u][v];
                if (newDistance < Value1[v] || Value1[v] == -1) {
                    Value1[v] = newDistance;
                    Previous1[v] = u;
                }
            }
        }

        for (int i = 0; i < numVertices; ++i) {
            graphValue[k][i] = Value1[i];
            graphPrevious[k][i] = Previous1[i];
        }
    }

    // Truy ngược đường đi từ đỉnh kết thúc
    int path_reserve[30], path[30];
    int count = 0, n = endIndex;

    // Truy ngược từ endIndex về startIndex
    while (n != startIndex && n != -1) {
        path_reserve[count++] = n;
        n = Previous1[n]; // Di chuyển đến đỉnh trước đó
    }

    // Nếu không tìm được đường đi (n == -1), thì không có đường đi
    if (n == -1) return ""; // Không có đường đi

    // Đỉnh bắt đầu cũng phải vào đường đi
    path_reserve[count++] = startIndex;

    // Đảo ngược đường đi để đưa từ startIndex -> endIndex
    for (int i = 0; i < count; ++i) {
        path[i] = path_reserve[count - 1 - i];
    }

    // Tạo chuỗi kết quả
    string result;
    for (int i = 0; i < count; ++i) {
        result += ('A' + path[i]);  // Chuyển chỉ số thành ký tự
        if (i < count - 1) {
            result += ' '; // Thêm khoảng trắng giữa các đỉnh
        }
    }

    return result;
}