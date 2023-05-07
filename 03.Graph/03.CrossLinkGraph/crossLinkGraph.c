#include <stdio.h>
#include <stdlib.h>
#include "crossLinkGraph.h"

// 产生n个顶点的十字链表
CrossLinkGraph *createCrossLinkGraph(int n) {
    CrossLinkGraph *G = (CrossLinkGraph*) malloc(sizeof(CrossLinkGraph));
    G->vex = (CrossLinkVertex*) malloc(sizeof(CrossLinkVertex) * n);
    if (G == NULL || G->vex == NULL) {
        printf("fail to malloc!\n");
        return NULL;
    }
    G->edgeNum = 0;
    G->vexNum = n;
    return G;
}
// 释放十字链表
void releaseCrossLinkGraph(CrossLinkGraph* G) {
    if (G == NULL || G->vex == NULL) return;
    int cnt = 0;
    for (int i = 0; i < G->vexNum; ++i) { // 遍历所有节点，释放出度（不需再释放入度，在释放出度时该节点就被释放了）
        CrossLinkEdge *edge = G->vex[i].firstOut;
        CrossLinkEdge *temp;
        while (edge) {
            temp = edge;
            edge = edge->tailNext;
            free(temp);
            cnt++;
        }

    }
    printf("release %d edges!", cnt);
    free(G->vex);
    free(G);
}
// 初始化图，设置节点信息
void initCrossLinkGraph(CrossLinkGraph* G, int num, char *names[]) {
    for (int i = 0; i < num; ++i) {
        G->vex[i].index = i;
        G->vex[i].show = names[i];
        G->vex[i].firstOut = G->vex[i].firstIn = NULL;
    }
}
// 添加边，从tail到head
void addCrossLinkEdge(CrossLinkGraph* G, int tail, int head, int weight) {
    CrossLinkEdge *edge = (CrossLinkEdge*) malloc(sizeof(CrossLinkEdge));
    if (edge == NULL) return;
    edge->weight = weight;
    // 使用头插法，出度
    edge->tailIndex = tail;
    edge->tailNext = G->vex[tail].firstOut;
    G->vex[tail].firstOut = edge;
    // 使用头插法，入度
    edge->headIndex = head;
    edge->headNext = G->vex[head].firstIn;
    G->vex[head].firstIn = edge;
    G->edgeNum++;
}
// 计算v节点的入度
int inDegreeCrossLink(CrossLinkGraph* G, int v) {
    if (G == NULL || G->vex == NULL) return -1;
    CrossLinkEdge *edge = G->vex[v].firstIn;
    int cnt = 0;
    while (edge) {
        cnt++;
        edge = edge->headNext; // 同一终点
    }
    return cnt;
}
// 计算v节点的出度
int outDegreeCrossLink(CrossLinkGraph* G, int v) {
    if (G == NULL || G->vex == NULL) return -1;
    CrossLinkEdge *edge = G->vex[v].firstOut;
    int cnt = 0;
    while (edge) {
        cnt++;
        edge = edge->tailNext; // 同一起点
    }
    return cnt;
}