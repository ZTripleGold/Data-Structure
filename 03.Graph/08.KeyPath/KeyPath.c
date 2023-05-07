#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "KeyPath.h"

/* 通过拓扑排序填充ETV，将拓扑排序的结果放入栈中，出栈，根据倒序以求出LTV
 * stack: 用来更新入度记录表
 * topOut: 拓扑排序的输出结果，此结果出栈，就可以算出从汇点反向计算LTV
 * */
static int TopologicalOrder(AGraph *G, int* ETV, int* LTV) {
    int *stack, *topOut;
    int top = -1;
    int *inDegree = (int*) malloc(sizeof(int) * G->nodeNum);
    if (inDegree == NULL) {
        printf("fail to malloc!\n");
        return -1;
    }
    memset(inDegree, 0, sizeof(int) * G->nodeNum);
    // 初始化入度表
    for (int i = 0; i < G->nodeNum; ++i) {
        if (G->vex[i].firstEdge) {
            ArcEdge *edge = G->vex[i].firstEdge;
            while (edge) {
                ++inDegree[edge->index];
                edge = edge->next;
            }
        }
    }
    // 遍历入度表，找到度为0的顶点，压栈，出栈时就判断是否更新ETV
    stack = (int*) malloc(sizeof(int) * G->nodeNum);
    topOut = (int*) malloc(sizeof(int) * G->nodeNum);
    if (stack == NULL || topOut == NULL) {
        printf("fail to malloc!\n");
        return -1;
    }
    for (int i = 0; i < G->nodeNum; ++i) {
        if (inDegree[i] == 0) {
            stack[++top] = i;
            break;          // 关键路径，入度为0的顶点即源点，只有一个
        }
    }
    // 出栈，更新入度表，以及ETV
    int index;
    int topIndex = 0;       // topOut的栈顶索引
    while (top != -1) {
        index = stack[top--];
        topOut[topIndex++] = index;
        ArcEdge *edge = G->vex[index].firstEdge;
        while (edge) {
            --inDegree[edge->index];
            // 更新入度表
            if (inDegree[edge->index] == 0) {
                stack[++top] = edge->index;
            }
            // 更新ETV
            if (ETV[index] + edge->weight > ETV[edge->index]) { // 当弧尾顶点的ETV加上这条边的权值大于弧头顶点的ETV时，更新弧头顶点的ETV
                ETV[edge->index] = ETV[index] + edge->weight;
            }
            edge = edge->next;
        }
    }
    free(inDegree);
    free(stack);
    if (topIndex < G->nodeNum) { // 说明有环
        free(topOut);
        return -1;
    }
    // 拓扑排序计算完，此时index指向汇点，根据topOut栈填充LTV
    // 初始化LTV
    for (int i = 0; i < G->nodeNum; ++i) {
        LTV[i] = ETV[index]; // 全部更新为汇点的最早发生时间，同时汇点的最早发生时间与最晚发生时间相等
    }
    int getTopNo;
    while (topIndex) { // topIndex从0开始计数，所以等于0时即可退出循环
        // 出栈，根据出栈节点更新LTV
        getTopNo = topOut[--topIndex]; // 由于汇点没有出边，取到也没有关系
        ArcEdge* edge = G->vex[getTopNo].firstEdge;
        while (edge) {
            if (LTV[edge->index] - edge->weight < LTV[getTopNo]) { // 当弧头顶点的LTV减去这条边的权值小于弧尾顶点的LTV时，更新弧尾顶点的LTV
                LTV[getTopNo] = LTV[edge->index] - edge->weight;
            }
            edge = edge->next;
        }
    }
    free(topOut);
    return 0;
}

static void showTable(int *table, int n, char* name) {
    printf("%s", name);
    for (int i = 0; i < n; ++i) {
        printf("\t%d", table[i]);
    }
    printf("\n");
}

/* 为了求出AOE网中的关键路径，需求出四个时间
 * 对于AOE网中的顶点有两个时间：
 * ETV：事件发生的最早时间
 * LTV：事件发生的最晚事件
 * 对于AOE网中的边也有两个时间：
 * ETE：活动发生的最早时间
 * LTE：活动发生的最晚时间
 * 找出关键路径的方法：对于所有边来说，当活动发生的最晚时间等于活动发生的最早时间时，这条边就表示为关键路径
 * */
void keyPath(AGraph* G) {
    // 初始化ETV和LTV
    int* ETV = (int*) malloc(sizeof(int) * G->nodeNum);
    int* LTV = (int*) malloc(sizeof(int) * G->nodeNum);
    if (ETV == NULL || LTV == NULL) {
        printf("fail to malloc!\n");
        return;
    }
    memset(ETV, 0, sizeof(int) * G->nodeNum);
    memset(LTV, 0, sizeof(int) * G->nodeNum);
    // 填充ETV和LTV
    TopologicalOrder(G, ETV, LTV);
    showTable(ETV, G->nodeNum, "ETV: ");
    showTable(LTV, G->nodeNum, "LTV: ");
    // 计算ETE和LTE
    for (int i = 0; i < G->nodeNum; ++i) {
        ArcEdge *edge = G->vex[i].firstEdge;
        while (edge) {
            // 每个边的最早发生时间就是边的弧尾的ETV
            // 每个边的最晚发生时间就是边的弧头的LTV 减去 当前边的权值
            if (ETV[i] == LTV[edge->index] - edge->weight) { // 当活动最早发生时间ETE等于活动最晚发生时间LTE时，该边表示为关键路径
                printf("<%s> ---%d--- <%s>\n",
                       G->vex[i].show, edge->weight, G->vex[edge->index].show);
            }
            edge = edge->next;
        }
    }
    free(ETV);
    free(LTV);
}