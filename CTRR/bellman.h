#ifndef BM_H
#define BM_H

#include <string>
using namespace std;

void BF(int graph[30][30], int numV, char startV, int value[30], int preV[30]);
string BF_Path(int graph[30][30], int numV, char startV, char endV);

#endif
