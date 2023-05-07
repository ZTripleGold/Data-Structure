#ifndef KRUSKAL_H
#define KRUSKAL_H
#include "../common.h" // 包含边集数组的结构
#include "../01.MatrixGraph/matrixGraph.h" // 包含邻接矩阵的结构
/* Kruskal算法
 * 从边的角度求图的最小生成树，更适合求边稀疏的图
 * 算法思路：
 * A.将所有的边按照权值的大小进行排序，然后从小到大一一判断
 * 判断条件：
 * 如果这条边不会和之前的所有边形成回路（利用并查集），将边加入结果数组；反之，舍弃这条边
 * B.循环A，直到结果数组中有n - 1个元素，结束循环
 * 引入一个数据结构，边集数组，保存边和节点的关系
 * */

// 使用邻接矩阵表示无向图，再通过邻接矩阵初始化边集数组，返回边集数组存储的边的数量
int initEdgeSet(MGraph* G, EdgeSet* edgeSet);
// 排序边集数组，按权值的大小从小到大排序
void sortEdgeSet(MGraph* G, EdgeSet* edgeSet, int num);
// Kruskal算法，返回权值的总和
int KruskalMiniTree(const MGraph* G, const EdgeSet* edgeSet, int num, EdgeSet* result);
#endif //KRUSKAL_H
