#ifndef ADJACENCYMULTILIST_H
#define ADJACENCYMULTILIST_H
/* 邻接多重表，使用于无向图，边的删除
 * 无向图如果用邻接表存储的话，一条边处理了2次，删除较为复杂
 * */
// 邻接多重表的边结构
typedef struct MultiListEdge{
    int iVex;       // 边的顶点i的编号
    struct MultiListEdge *iNext;      // 顶点i的下一条边
    int jVex;
    struct MultiListEdge *jNext;
    int weight;
}MultiListEdge;
// 邻接多重表的顶点结构
typedef struct {
    int index;
    char *show;
    MultiListEdge *firstEdge;
}MultiListVertex;
// 邻接多重表
typedef struct {
    MultiListVertex *vex;
    int nodeNum;
    int edgeNum;
}AdjacencyMultiList;

// 产生n个顶点的邻接多重表
AdjacencyMultiList *createAdjacencyMultiList(int n);
// 释放邻接多重表
void releaseAdjacencyMultiList(AdjacencyMultiList* G);
// 初始化邻接多重表
void initAdjacencyMultiList(AdjacencyMultiList* G, int num, char*names[]);
// 插入边
void insertMultiListEdge(AdjacencyMultiList* G, int a, int b, int weight);
// 删除边
void deleteMultiListEdge(AdjacencyMultiList* G, int a, int b);
#endif //ADJACENCYMULTILIST_H
