#include <stdio.h>
#include <stdlib.h>
#include "Prim.h"

// Prim算法
int Prim(MGraph* G, int startV, EdgeSet* result) {
    int *cost;              // 代价权值数组，存储与顶点有关的边中最小的权值
    int *mark;              // 标志着该顶点是否被访问
    int *visit;             // 记录从哪个节点访问到这个节点的，-1即表示没有被访问
    int sumWeight = 0;      // 存储总的边权值之和
    int min, k;

    cost = (int*) malloc(sizeof(int) * G->nodeNum);
    mark = (int*) malloc(sizeof(int) * G->nodeNum);
    visit = (int*) malloc(sizeof(int) * G->nodeNum);
    if (cost == NULL || mark == NULL || visit == NULL) {
        printf("fail to malloc!\n");
        return 0;
    }

    // 根据传入的第一个节点startV，进行初始化
    for (int i = 0; i < G->nodeNum; ++i) {
        cost[i] = G->edges[startV][i];
        mark[i] = 0;
        if (cost[i] < INF) { // 即该顶点初始化时有边
            visit[i] = startV;
        }
        else {
            visit[i] = -1;
        }
    }
    mark[startV] = 1;
    // 遍历n-1次，找出最小生成树的n-1条边
    for (int i = 0; i < G->nodeNum - 1; ++i) {
        min = INF;  // 令min等于无穷大，寻找代价权值数组中的最小值
        for (int j = 0; j < G->nodeNum; ++j) {
            if (mark[j] == 0 && cost[j] < min) { // 在未被访问的节点中寻找
                min = cost[j];      // 记录最小权值
                k = j;              // 记录对应顶点的下标
            }
        }
        // 找到最小顶点，激活这个节点，以及结果数组和权值之和
        mark[k] = 1;
        result[i].begin = visit[k];
        result[i].end = k;
        result[i].weight = min;
        sumWeight += min;
        // 更新代价权值数组和访问记录
        for (int j = 0; j < G->nodeNum; ++j) {
            if (mark[j] == 0 && G->edges[k][j] < cost[j]) { // 在未被访问的节点中寻找
                cost[j] = G->edges[k][j];
                visit[j] = k;
            }
        }
    }
    // 循环结束，释放申请的空间
    free(cost);
    free(mark);
    free(visit);
    return sumWeight;
}