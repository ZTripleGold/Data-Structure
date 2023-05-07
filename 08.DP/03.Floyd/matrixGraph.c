#include <string.h>
#include <stdio.h>
#include "matrixGraph.h"

/* 邻接矩阵的初始化，初始化顶点集
 * num:         顶点的个数
 * names:       顶点显示的字符串，以字符指针来保存，上层空间他的值有效
 * edgeValue:   边的权值
 * direction:   是否是有向图
 */
void initMGraph(MGraph *G, int num, char *names[], int edgeValue, int direction) {
    G->direction = direction; // 为0是无向图，1为有向图
    G->edgeNum = 0;     // 只初始化了顶点集，边数量为0
    G->nodeNum = num;
    memset(G->vex, 0, sizeof(G->vex));  // 初始化顶点都为0
    memset(G->edges, 0, sizeof(MatrixEdge) * MaxNodeNum * MaxNodeNum);    // 初始化边的关系都为0，即都不相连
    // 初始化顶点
    for (int i = 0; i < num; ++i) {
        G->vex[i].index = i;
        G->vex[i].show = names[i];
        for (int j = 0; j < num; ++j) {
            G->edges[i][j] = edgeValue; // 初始化边的权值
        }
    }
}

// 判断是否有边
static int IsEdge(int weight) {
    if (weight > 0 && weight < INF)
        return 1; // 符合条件返回1
    return 0;
}

/* 添加边的信息
 * x:       边的起始编号
 * y:       边的终止编号
 * weight:  边的权值
 */
// 简单图 不能有自环 不能有重边
void addEdge(MGraph *G, int x, int y, int weight) {
    if (x < 0 || x >= G->nodeNum || y < 0 || y >= G->nodeNum) // 判断传入的x,y值是否合理
        return;
    if (IsEdge(G->edges[x][y])) // 判断传入的weight是否合理
        return;
    G->edges[x][y] = weight;
    if (G->direction == 0) { // 如果是无向图，edges[y][x]也要处理
        G->edges[y][x] = weight;
    }
    G->edgeNum++;
}

// 访问节点
void visitedNode(MatrixVertex *node) {
    printf("\t%s", node->show);
}

// 定义数组来记录是否访问过这个节点
static int Visited[MaxNodeNum]; // 静态变量初始值为0

// 清除Visited数组
void clearVisited() {
    memset(Visited, 0, sizeof(Visited)); // 将数组置0，即都没有访问过
}

// 深度搜索，递归实现
void DFSMGraph(MGraph *G, int v) {
    visitedNode(&G->vex[v]); // 从传入的节点开始访问
    Visited[v] = 1;
    // 从v号节点开始，根据邻接矩阵的边的关系，找到一个未被访问的节点继续DFS
    for (int i = 0; i < G->nodeNum; ++i) {
        if (IsEdge(G->edges[v][i]) && Visited[i] == 0) {
            DFSMGraph(G, i);
        }
    }
}
// 广度搜索
/* 初始化一个（循环）队列，将要访问的第一个节点压入队列
 * 只要队列不为空，就一直循环
 * 出队一个元素A，设置该元素A已经访问，将A的m个节点（未被访问）放入队列，设置为已访问状态
 * 避免任务队列里已经有待处理的任务，而其他节点激活后，又放入到任务队列
 */
void BFSMGraph(MGraph *G, int v) {
    int queue[MaxNodeNum];
    int rear = 0, front = 0;
    int cur;

    rear = (rear + 1) % MaxNodeNum; // 留一个空间以解决假溢出
    queue[rear] = v; // 将第一个节点压入队列
    while (rear != front) { // 当rear和front相等时，队列为空
        // 出队
        front = (front + 1) % MaxNodeNum;
        cur = queue[front];
        // 访问出队的节点
        visitedNode(&G->vex[cur]);
        Visited[cur] = 1;
        // 将A的m个未被访问的节点放入队列
        for (int i = 0; i < G->nodeNum; ++i) {
            if (IsEdge(G->edges[cur][i]) && Visited[i] == 0) {
                rear = (rear + 1) % MaxNodeNum;
                queue[rear] = i;
                Visited[i] = 1; // 防止重复任务
            }
        }
    }

}