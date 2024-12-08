void BF(int graph[30][30], int numV, char startV, int value[], int preV[]) {
    int startVIndex = startV - 'A'; //char thành số, cách tham chiếu của chương trình

    value[startVIndex] = 0; //k.cách tới chính nó = 0. Đây là step 0, khi mọi khoảng cách khác là vô cùng.
    
    //Phải có bản copy vì ta sẽ cập nhật giá trị khoảng cách hiện tại khi quét đồ thị. Không có bản copy sẽ làm giá trị bị thay đổi nhiều lần. Trong khi 1 bước chỉ đi từ 1 đỉnh
    int valueCopy[30];
    for (int i = 0; i<numV; i++){
        valueCopy[i] = value[i];
    }

    for (int u = 0; u < numV; u++) { //quét đầy đủ tất cả hàng, cột trong ma trận đồ thị
        for (int v = 0; v < numV; v++) {
            // value[u] = -1 nghĩa là giá trị khoảng cách của đỉnh u là vô cùng. Giá trị giữa 2 đỉnh trong ma trận = 0 là ko kết nối
            if ((graph[u][v] != 0) && (valueCopy[u] != -1)){
                // Nếu khoảng cách mới nhỏ hơn khoảng cách hiện tại của v, cập nhật giá trị. Kcách hiện tại tới đỉnh v bằng vô cùng cũng sẽ bị cập nhật
                if (((valueCopy[u] + graph[u][v]) < value[v]) || (value[v] == -1)) {
                value[v] = valueCopy[u] + graph[u][v];
                preV[v] = u;
                }
            }
        }
    }
}