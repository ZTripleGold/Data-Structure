#include <stdio.h>
#include "matrixGraph.h"

#define MAXSIZE 20

static int dist[MAXSIZE][MAXSIZE];      // 最短路径
static int path[MAXSIZE][MAXSIZE];      // 路径数组

static void setupMGraph(MGraph *graph) {
    char *nodeNames[] = {"V0", "V1", "V2", "V3"};

    initMGraph(graph, sizeof(nodeNames) / sizeof(nodeNames[0]), nodeNames, INF, 1);
    for (int i = 0; i < graph->nodeNum; ++i) {
        graph->edges[i][i] = 0;     // 自己到自己的最短距离为0
    }
    addEdge(graph, 0, 1, 1);
    addEdge(graph, 0, 3, 4);
    addEdge(graph, 1, 2, 9);
    addEdge(graph, 1, 3, 2);
    addEdge(graph, 2, 0, 3);
    addEdge(graph, 2, 1, 5);
    addEdge(graph, 2, 3, 8);
    addEdge(graph, 3, 2, 6);
}

// 最短路径Floyd
void shortPathFloyd(MGraph *graph) {
    // 初始化
    for (int i = 0; i < graph->nodeNum; ++i) {
        for (int j = 0; j < graph->nodeNum; ++j) {
            dist[i][j] = graph->edges[i][j];
            if (dist[i][j] < INF && dist[i][j] != 0) {
                path[i][j] = i;
            }
            else {
                // 设两节点没有路径或到节点自身的路径数组为-1，即没有i到j
                path[i][j] = -1;
            }
        }
    }
    // 第一层循环，分别激活节点
    for (int k = 0; k < graph->nodeNum; ++k) {
        // 第二层循环，第k个状态的行
        for (int i = 0; i < graph->nodeNum; ++i) {
            // 第三层循环，第k个状态的列
            for (int j = 0; j < graph->nodeNum; ++j) {
                if (dist[i][k] < INF && dist[k][j] < INF &&
                    dist[i][j] > dist[i][k] + dist[k][j]) {
                    // 当发现更小值时，更新dist和path
                    dist[i][j] = dist[i][k] + dist[k][j];
                    path[i][j] = path[k][j];
                }
            }
        }
    }
}

void printfPath(int i, int j) {
    if (i == j) {
        printf("%d ", i);
        return;
    }
    int k = path[i][j];
    printfPath(i, k);
    printf("%d ", j);
}

int main() {
    MGraph graph;

    setupMGraph(&graph);
    shortPathFloyd(&graph);
    for (int i = 0; i < graph.nodeNum; ++i) {
        for (int j = 0; j < graph.nodeNum; ++j) {
            printf("%d\t", dist[i][j]);
        }
        printf("\n");
    }
    printf("====================\n");
    for (int i = 0; i < graph.nodeNum; ++i) {
        for (int j = 0; j < graph.nodeNum; ++j) {
            printf("%d\t", path[i][j]);
        }
        printf("\n");
    }
    printf("====================\n");
    printfPath(1, 0);
    return 0;
}