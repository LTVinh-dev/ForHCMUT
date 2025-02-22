void BF(int graph[][30], int numVertices, char start, int Value[], int Previous[]) {
    int startIndex = start - 'A';  // Chuyển ký tự đỉnh bắt đầu thành chỉ số (A -> 0, B -> 1, C -> 2, ...)


    // Khoảng cách từ đỉnh bắt đầu đến chính nó là 0
    Value[startIndex] = 0;

    // Lặp qua tất cả các cạnh của đồ thị để tính một bước Bellman-Ford
    int Value1[30];
    int Previous1[30];
    for (int i = 0; i < numVertices; ++i) {
        Value1[i] = Value[i];  // Sao chép giá trị hiện tại
        Previous1[i] = Previous[i];  // Sao chép đỉnh trước đó
    }

    // Lặp qua tất cả các cạnh của đồ thị
    for (int u = 0; u < numVertices; ++u) {
        for (int v = 0; v < numVertices; ++v) {
            // Bỏ qua nếu không có cạnh từ u đến v hoặc nếu u có khoảng cách vô cùng (Value[u] == -1)
            if (graph[u][v] == 0 || Value[u] == -1) continue;

            // Tính khoảng cách mới từ u đến v
            int newDistance = Value[u] + graph[u][v];

            // Nếu khoảng cách mới nhỏ hơn khoảng cách hiện tại của v, cập nhật giá trị
            if (newDistance < Value1[v] || Value1[v] == -1) {
                Value1[v] = newDistance;
                Previous1[v] = u;
            }
        }
    }

    // Cập nhật mảng Value và Previous sau một bước
    for (int i = 0; i < numVertices; ++i) {
        Value[i] = Value1[i];
        Previous[i] = Previous1[i];
    }
}