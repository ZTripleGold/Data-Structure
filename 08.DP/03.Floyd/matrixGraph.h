#ifndef MATRIXGRAPH_H
#define MATRIXGRAPH_H

/* 邻接矩阵的存储方式
 * 顶点用一维数组描述，边用二维数组表示
 */
#define MaxNodeNum 10 // 节点的最大数量
#define INF 1E4       // 节点的最大权值
// 邻接矩阵的顶点结构
typedef struct {
    int index;         // 顶点的编号
    char *show;        // 顶点所对应的字符串，如 V1， V2， V3
}MatrixVertex;
// 邻接矩阵边的类型，用int来表示，即可以描述权值，也可以描述是否有边
typedef int MatrixEdge;
// 邻接矩阵的图结构
typedef struct {
    MatrixVertex vex[MaxNodeNum];   // 存储顶点的信息
    int nodeNum;                    // 约束实际顶点的数量，也是遍历时的最大值
    MatrixEdge edges[MaxNodeNum][MaxNodeNum];   // 邻接矩阵定义边的情况
    int edgeNum;                    // 定义边的个数
    int direction;                  // 是否是有向图
}MGraph;

/* 邻接矩阵的初始化，初始化顶点集和边集
 * num:         顶点的个数
 * names:       顶点显示的字符串，以字符指针来保存，上层空间他的值有效
 * edgeValue:   初始化边的权值
 * direction:   是否是有向图
 */
void initMGraph(MGraph *G, int num, char *names[], int edgeValue, int direction);

/* 添加边的信息
 * x:       边的起始编号
 * y:       边的终止编号
 * weight:  边的权值
 */
void addEdge(MGraph *G, int x, int y, int weight);

// 访问节点
void visitedNode(MatrixVertex *node);
// 清空Visited数组
void clearVisited();
// 深度搜索
void DFSMGraph(MGraph *G, int v);
// 广度搜索
void BFSMGraph(MGraph *G, int v);
#endif //MATRIXGRAPH_H
