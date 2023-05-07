#include <stdio.h>
#include <stdlib.h>
#include "adjacencyMultiList.h"

// 产生n个顶点的邻接多重表
AdjacencyMultiList *createAdjacencyMultiList(int n) {
    AdjacencyMultiList *G = (AdjacencyMultiList*) malloc(sizeof(AdjacencyMultiList));
    G->vex = (MultiListVertex*) malloc(sizeof(MultiListVertex) * n);
    if (G == NULL || G->vex == NULL) return NULL;
    G->edgeNum = 0;
    G->nodeNum = n;
    return G;
}
// 释放邻接多重表
void releaseAdjacencyMultiList(AdjacencyMultiList* G) {

}
// 初始化邻接多重表
void initAdjacencyMultiList(AdjacencyMultiList* G, int num, char*names[]) {
    for (int i = 0; i < num; ++i) {
        G->vex[i].index = i;
        G->vex[i].show = names[i];
        G->vex[i].firstEdge = NULL;
    }
}
// 插入边
void insertMultiListEdge(AdjacencyMultiList* G, int a, int b, int weight) {
    // 产生新边
    MultiListEdge *edge = (MultiListEdge*) malloc(sizeof(MultiListEdge));
    if (edge == NULL) return;
    edge->weight = weight;
    // 处理a节点连接关系，头插法
    edge->iVex = a;
    edge->iNext = G->vex[a].firstEdge;
    G->vex[a].firstEdge = edge;
    // 处理b节点连接关系，头插法
    edge->jVex = b;
    edge->jNext = G->vex[b].firstEdge;
    G->vex[b].firstEdge = edge;
    G->edgeNum++;
}
// 删除边
void deleteMultiListEdge(AdjacencyMultiList* G, int a, int b) {
    // 删除边需找到节点的前驱节点，要删除边就要找到前一条边
    // 找到a节点的前一个节点
    MultiListEdge *aPreEdge = NULL;
    MultiListEdge *aCurEdge = G->vex[a].firstEdge;
    while (aCurEdge && !((aCurEdge->iVex == a && aCurEdge->jVex == b) || (aCurEdge->jVex == a && aCurEdge->iVex == b))) {
        // 有两种情况，i == a && j == b 和 i == b && j == a，两种情况满足一种就退出循环
        aPreEdge = aCurEdge;
        if (aCurEdge->iVex == a) {
            aCurEdge = aCurEdge->iNext;
        }
        else {
            aCurEdge = aCurEdge->jNext;
        }
    }
    if (aCurEdge == NULL) {
        return;     // 找不到这条边，直接返回
    }
    // 找到b节点的前一个节点
    MultiListEdge *bPreEdge = NULL;
    MultiListEdge *bCurEdge = G->vex[b].firstEdge;
    while (bCurEdge && !((bCurEdge->iVex == a && bCurEdge->jVex == b) || (bCurEdge->jVex == a && bCurEdge->iVex == b))) {
        bPreEdge = bCurEdge;
        if (bCurEdge->iVex == a) {
            bCurEdge = bCurEdge->iNext;
        }
        else {
            bCurEdge = bCurEdge->jNext;
        }
    }
    if (bCurEdge == NULL) {
        return;     // 找不到这条边，直接返回
    }
    // 删除边
    // 先处理a顶点的关系
    if (aPreEdge == NULL) { // 一开始就找到了这条边，从头节点处删除
        if (aCurEdge->iVex == a) {
            G->vex[a].firstEdge = aCurEdge->iNext;
        }
        else {
            G->vex[a].firstEdge = aCurEdge->jNext;
        }
    }
    else {  // aPreEdge存在
        if (aPreEdge->iVex == a) {
            if (aCurEdge->iVex == a)
                aPreEdge->iNext = aCurEdge->iNext;
            else
                aPreEdge->iNext = aCurEdge->jNext;
        }
        else {
            if (aCurEdge->iVex == a)
                aPreEdge->jNext = aCurEdge->iNext;
            else
                aPreEdge->jNext = aCurEdge->jNext;
        }
    }
    // 再处理b顶点关系
    if (bPreEdge == NULL) {
        if (bCurEdge->iVex == a) {
            G->vex[b].firstEdge = bCurEdge->iNext;
        }
        else {
            G->vex[b].firstEdge = bCurEdge->jNext;
        }
    }
    else {
        if (bPreEdge->iVex == a) {
            if (bCurEdge->iVex == a)
                bPreEdge->iNext = bCurEdge->iNext;
            else
                bPreEdge->iNext = bCurEdge->jNext;
        }
        else {
            if (bCurEdge->iVex == a)
                bPreEdge->jNext = bCurEdge->iNext;
            else
                bPreEdge->jNext = bCurEdge->jNext;
        }
    }
    // 释放边
    free(aCurEdge);
    G->edgeNum--;
}