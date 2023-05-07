#include <stdio.h>
#include <stdlib.h>
#include "DijkstraShortestPath.h"

/* 1.根据传入的源节点，创建check数组，初始化dis和path数组，当作源节点被激活
 * 2.在dis数组中寻找权值最小的节点，激活这个节点，更新dis，path，check数组
 * 3.直到源节点到其他所有节点的最短路径都被找到，循环结束
 * */

void DijkstraMGraph(const MGraph* G, int start, int dis[], int path[]) {
    int* check;         // 存储节点的访问情况，被访问值为1
    check = (int*) malloc(sizeof(int) * G->nodeNum);
    if (check == NULL) return;

    // 根据start初始化
    for (int i = 0; i < G->nodeNum; ++i) {
        dis[i] = G->edges[start][i];
        check[i] = 0;
        if (dis[i] < INF) {
            path[i] = start;
        }
        else {
            path[i] = -1;
        }
    }
    dis[start] = 0;     // 源节点到自身的路径权值为0
    check[start] = 1;   // 源节点被激活
    // path[start] = -1;        前面循环中已经赋值完，可以不用更改

    // 循环n-1次，找到源节点到其他节点的最短路径，每次都在dis数组中找最小值
    int min;
    int minIndex;
    for (int i = 0; i < G->nodeNum - 1; ++i) {
        min = INF;
        // 在dis数组里未被激活的节点中，找到最小值，以及它的下标
        for (int j = 0; j < G->nodeNum; ++j) {
            if (check[j] == 0 && dis[j] < min) {
                min = dis[j];
                minIndex = j;
            }
        }
        // 在未被激活的节点中，更新数组信息
        check[minIndex] = 1; // 激活找到的节点
        for (int j = 0; j < G->nodeNum; ++j) {
            if (check[j] == 0 && dis[j] > dis[minIndex] + G->edges[minIndex][j]) {
                dis[j] = dis[minIndex] + G->edges[minIndex][j];
                path[j] = minIndex;
            }
        }
    }
    free(check);
}

// 从path信息里打印出 start为源点到其他节点pos的最短路径
void showPath(const int path[], int num, int pos) {
    int* stack;     // 定义一个顺序栈
    int top = -1;
    stack = (int*) malloc(sizeof(int) * num);
    if (stack == NULL) return;

    int cur = pos;
    while (path[cur] != -1) { // 即没有找到源节点
        stack[++top] = cur;
        cur = path[cur];
    }
    stack[++top] = cur;
    while (top > 0) { // 出栈
        printf("%d -> ", stack[top--]);
    }
    printf("%d\n", stack[top--]);
    free(stack);
}