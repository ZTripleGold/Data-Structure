#include <stdlib.h>
#include <string.h>
#include "Kruskal.h"

// 使用邻接矩阵表示无向图，再通过邻接矩阵初始化边集数组，返回边集数组存储的边的数量
// 邻接矩阵表示的无向图，只要上三角的数据
int initEdgeSet(MGraph* G, EdgeSet* edgeSet) {
    int num = 0;
    for (int i = 0; i < G->nodeNum; ++i) {
        for (int j = i + 1; j < G->nodeNum; ++j) {
            if (G->edges[i][j] > 0) {
                edgeSet[num].begin = i;
                edgeSet[num].end = j;
                edgeSet[num].weight = G->edges[i][j];
                num++;
            }
        }
    }
    return num;
}

// 排序边集数组，按权值的大小从小到大排序
void sortEdgeSet(MGraph* G, EdgeSet* edgeSet, int num) {
    // 用冒泡来排序
    EdgeSet temp;
    for (int i = 0; i < num; ++i) {
        for (int j = i + 1; j < num; ++j) {
            if (edgeSet[j].weight < edgeSet[i].weight) {
                memcpy(&temp, &edgeSet[i], sizeof (EdgeSet)); // 将edgeSet[i]赋值给temp
                memcpy(&edgeSet[i], &edgeSet[j], sizeof (EdgeSet));
                memcpy(&edgeSet[j], &temp, sizeof (EdgeSet));
            }
        }
    }
}

// 找到a元素的根节点
int findRoot(const int *ufSet, int a) {
    if (ufSet == NULL) return -1;
    while (ufSet[a] != a) {
        a = ufSet[a];
    }
    return a;
}

// Kruskal算法
int KruskalMiniTree(const MGraph* G, const EdgeSet* edgeSet, int num, EdgeSet* result) {
    // 通过并查集来判断是否会构成回路，这里使用QuickUnion
    int *ufSet;
    int sumWeight = 0, cnt = 0;
    int a, b;
    ufSet = (int*) malloc(sizeof(int) * G->nodeNum);
    if (ufSet == NULL) return 0;
    for (int i = 0; i < G->nodeNum; ++i) { // 初始化并查集
        ufSet[i] = i; // 每个元素的初始父节点都是自己
    }
    for (int i = 0; (cnt < G->nodeNum - 1) && i < num; ++i) { // 当遍历完所有边或者result数组中的边数等于 n - 1时退出循环
        a = findRoot(ufSet, edgeSet[i].begin);
        b = findRoot(ufSet, edgeSet[i].end);
        if (a != b) { // 当不构成回路时，继续操作
            result[cnt].begin = edgeSet[i].begin;
            result[cnt].end = edgeSet[i].end;
            result[cnt].weight = edgeSet[i].weight;
            sumWeight += edgeSet[i].weight;
            ufSet[a] = b;
            cnt++;
        }
    }
    free(ufSet);
    return sumWeight;
}