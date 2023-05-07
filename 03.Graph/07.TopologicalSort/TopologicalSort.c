#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TopologicalSort.h"

// 拓扑排序
int TopologicalSortAGraph(AGraph* G) {
    // 根据邻接表初始化入度表
    int *inDegree;
    inDegree = (int*) malloc(sizeof(int) * G->nodeNum);
    if (inDegree == NULL) {
        printf("fail to malloc!\n");
        return -1;
    }
    memset(inDegree, 0, sizeof(int) * G->nodeNum);
    for (int i = 0; i < G->nodeNum; ++i) {
        if (G->vex[i].firstEdge) { // 循环这条链表，如果该顶点有出边，对应的出度加1
            ArcEdge *edge = G->vex[i].firstEdge;
            while (edge) {
                ++inDegree[edge->index];
                edge = edge->next;
            }
        }
    }
    // 遍历入度表，找到度为0的顶点，压栈
    int *stack, top = -1;
    stack = (int*) malloc(sizeof(int) * G->nodeNum);
    if (stack == NULL) {
        free(inDegree);
        printf("fail to malloc!\n");
        return -1;
    }
    for (int i = 0; i < G->nodeNum; ++i) {
        if (inDegree[i] == 0) {
            stack[++top] = i;
        }
    }
    // 弹出栈中顶点，更新入度表，记录弹出栈的顶点个数，直到任务栈为空
    int index, cnt = 0;
    while (top != -1) {
        index = stack[top--];
        visitNode(&G->vex[index]);      // 打印顶点
        // 更新入度表
        ArcEdge *edge = G->vex[index].firstEdge;
        while (edge) {
            --inDegree[edge->index];
            if (inDegree[edge->index] == 0) { // 如果发现度变成0了，压入任务栈
                stack[++top] = edge->index;
            }
            edge = edge->next;
        }
        cnt++;
    }
    free(inDegree);
    free(stack);
    // 当cnt与邻接表顶点数目相等时，说明图为无环图，否则是有环图
    if (cnt == G->nodeNum) {
        return 0;
    }
    else {
        return 1;
    }
}