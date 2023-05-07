#ifndef ADJACENTGRAPH_H
#define ADJACENTGRAPH_H
/* 图的邻接表，在节点集合中，增加指向边的指针
 * 边节点里包含了下一个和首节点连接的边，即每个节点里面对应的链表里面存的都是与首元素相连的边
 */
#include "../common.h"
// 邻接表边的结构
typedef struct arcEdge {
    int index;      //（首节点为弧尾）其他节点的编号
    int weight;     // 边的权值
    struct arcEdge *next;   // （从首节点）指向下一条边
}ArcEdge;
// 邻接表顶点结构
typedef struct {
    int index;      // 顶点的编号
    char *show;     // 顶点的显示内容
    ArcEdge *firstEdge;     // 当前节点指向的边，后面跟着一条链表
}ArcVertex;
// 邻接表的图结构
typedef struct {
    ArcVertex *vex;     // 图中顶点的集合
    int *Visited;       // 记录节点是否被访问
    int nodeNum;        // 顶点的个数
    int edgeNum;        // 边的个数
    int direction;      // 是否是有向图
}AGraph;

// 产生n个节点的邻接表的图
AGraph *createAGraph(int n);
void releaseAGraph(AGraph *G);

// 初始化邻接表
void initAGraph(AGraph *G, int num, char *names[], int direction);
// 添加边
void addAGraphEdge(AGraph *G, int x, int y, int weight);

// 访问节点
void visitNode(ArcVertex* node);
// 重置Visited数组
void resetVisited(AGraph* G);
// 深度搜索
void DFSAGraph(AGraph* G, int v);
// 广度搜索
void BFSAGraph(AGraph* G, int v);
#endif //ADJACENTGRAPH_H
