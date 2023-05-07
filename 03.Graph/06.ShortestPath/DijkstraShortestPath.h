#ifndef DIJKSTRASHORTESTPATH_H
#define DIJKSTRASHORTESTPATH_H
#include "../01.MatrixGraph/matrixGraph.h"

/* 最短路径 Dijkstra算法
 * 以start为源点，上层空间分配dis数组，用于记录源节点到其他节点的最小权值和
 * 上层空间分配path数组，用于每个节点从哪个节点来访问到的，相当于这个顶点的父节点
 * */
void DijkstraMGraph(const MGraph* G, int start, int dis[], int path[]);

// 从path信息里打印出 start为源点到其他节点pos的最短路径
void showPath(const int path[], int num, int pos);
#endif //DIJKSTRASHORTESTPATH_H
