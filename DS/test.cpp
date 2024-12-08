string BF_Path(int graph[30][30], int numV, char startV, char endV) {

    for (int u = 0; u < numV; u++) { //quét đầy đủ tất cả hàng, cột trong ma trận đồ thị
        for (int v = 0; v < numV; v++) {
            cout << graph[u][v] << " ";
        }
        cout << endl;
    }
    cout << endl;
    BF(graph, 8, 1, 1, 1);
    return "A";
}