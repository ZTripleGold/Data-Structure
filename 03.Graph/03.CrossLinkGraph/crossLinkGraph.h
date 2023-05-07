#ifndef CROSSLINKGRAPH_H
#define CROSSLINKGRAPH_H
/* 十字链表的图表示法，将邻接表和逆邻接表整合到一个结构中，
 * 方便求入度和出度，一般用于有向图
 * */
// 十字链表的边的结构
typedef struct crossLinkEdge {
    int tailIndex;                      // 弧尾编号，出度的信息
    struct crossLinkGraph* tailNext;    // 下一个弧尾，指向起点相同的下一条边
    int headIndex;                      // 弧头编号，入度的信息
    struct crossLinkGraph* headNext;    // 下一个弧头，指向终点相同的下一条边
    int weight;
}CrossLinkEdge;
// 十字链表的顶点结构
typedef struct {
    int index;
    char *show;
    CrossLinkEdge *firstIn;        // 第一个入的节点
    CrossLinkEdge *firstOut;       // 第一个出的节点
}CrossLinkVertex;
// 十字链表图结构
typedef struct {
    CrossLinkVertex *vex;
    int vexNum;
    int edgeNum;
}CrossLinkGraph;

// 产生n个顶点的十字链表
CrossLinkGraph *createCrossLinkGraph(int n);
// 释放十字链表
void releaseCrossLinkGraph(CrossLinkGraph* G);
// 初始化图，设置节点信息
void initCrossLinkGraph(CrossLinkGraph* G, int num, char *names[]);
// 添加边，从tail到head
void addCrossLinkEdge(CrossLinkGraph* G, int tail, int head, int weight);
// 计算v节点的入度
int inDegreeCrossLink(CrossLinkGraph* G, int v);
// 计算v节点的出度
int outDegreeCrossLink(CrossLinkGraph* G, int v);
#endif //CROSSLINKGRAPH_H
