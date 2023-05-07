#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "adjacentGraph.h"

// 产生n个节点的邻接表的图
AGraph *createAGraph(int n) {
    AGraph *G = (AGraph*) malloc(sizeof(AGraph));
    if (G == NULL) {
        fprintf(stderr, "fail to malloc!\n");
        // printf("fail to malloc!\n");
        return NULL;
    }
    G->edgeNum = 0;
    G->nodeNum = n;
    G->vex = (ArcVertex*) malloc(sizeof(ArcVertex) * n);
    G->Visited = (int*) malloc(sizeof(int) * n);
    if (G->vex == NULL || G->Visited == NULL) {
        fprintf(stderr, "fail to malloc nodes!\n");
        // printf("fail to malloc!\n");
        free(G);
        return NULL;
    }
    // 初始化链表
    memset(G->vex, 0, sizeof(G->vex) * n);
    resetVisited(G);
    return G;
}
void releaseAGraph(AGraph *G) {
    ArcEdge *temp;
    int cnt = 0;
    if (G == NULL) return;
    for (int i = 0; i < G->nodeNum; ++i) { // 遍历每一个节点
        ArcEdge *edge = G->vex[i].firstEdge;
        while (edge) {
            temp = edge;
            edge = edge->next;
            free(temp);
            cnt++;
        }
    }
    free(G->vex);
    free(G->Visited);
    free(G);
    printf("release %d edges!\n", cnt);
}

// 初始化邻接表
void initAGraph(AGraph *G, int num, char *names[], int direction) {
    G->direction = direction;
    for (int i = 0; i < num; ++i) { // 初始化数组空间中的n个节点
        G->vex[i].index = i;
        G->vex[i].show = names[i];
        G->vex[i].firstEdge = NULL;
    }
}

// 创建新边
static ArcEdge *createEdge(int y, int weight) {
    ArcEdge *edge = (ArcEdge*) malloc(sizeof(ArcEdge));
    if (edge == NULL) return NULL;
    edge->index = y;
    edge->next = NULL;
    edge->weight = weight;
    return edge;
}

// 添加边
void addAGraphEdge(AGraph *G, int x, int y, int weight) {
    if (x < 0 || x > G->nodeNum || y < 0 || y > G->nodeNum)
        return;
    if (x == y)
        return;
    // 边节点采用头插法
    ArcEdge *edge = createEdge(y, weight);
    edge->next = G->vex[x].firstEdge;
    G->vex[x].firstEdge = edge;
    G->edgeNum++;
    if (G->direction == 0) { // // 不是自环边，并且是无向图，无向图要做双向处理
        edge = createEdge(x, weight);
        edge->next = G->vex[y].firstEdge;
        G->vex[y].firstEdge = edge;
        G->edgeNum++;
    }
}

// 访问节点
void visitNode(ArcVertex* node) {
    printf("\t%s", node->show);
}
// 重置Visited数组
void resetVisited(AGraph* G) {
    if (G && G->Visited) {
        memset(G->Visited, 0, sizeof(int) * G->nodeNum);
    }
}
// 深度搜索
void DFSAGraph(AGraph* G, int v) {
    ArcEdge *edge;
    visitNode(&G->vex[v]);
    G->Visited[v] = 1;
    edge = G->vex[v].firstEdge;
    // 邻接表，循环遍历v节点中其他边的情况，找到下一个节点，继续DFS
    while (edge) {
        if (G->Visited[edge->index] == 0)
            DFSAGraph(G, edge->index);
        edge = edge->next;
    }
}
// 广度搜索
void BFSAGraph(AGraph* G, int v) {
    int *queue = (int*) malloc(sizeof(int) * G->nodeNum);
    if (queue == NULL) return;
    int front = 0, rear = 0;
    int cur;
    ArcEdge *edge;

    rear = (rear + 1) % G->nodeNum;
    queue[rear] = v;
    while (front != rear) {
        front = (front + 1) % G->nodeNum;
        cur = queue[front];
        visitNode(&G->vex[cur]);
        G->Visited[cur] = 1;
        edge = G->vex[cur].firstEdge;
        while (edge) {
            if (G->Visited[edge->index] == 0) {
                rear = (rear + 1) % G->nodeNum;
                queue[rear] = edge->index;
                G->Visited[edge->index] = 1;
            }
            edge = edge->next;
        }
    }
    free(queue);
}