#ifndef PRIM_H
#define PRIM_H
#include "../01.MatrixGraph/matrixGraph.h"
/* Prim算法：
 * 动态维护一个所有激活顶点的边权值数组
 * 从图任取一个顶点，激活这个顶点，发现相关的边
 * 1. 找到激活顶点后，找相关边中最小的边，激活另外一个顶点
 * 2. 每激活一个顶点，更新这个权值数组，找里面最小的边
 * 3. 直到所有的顶点都激活*/
// Prim算法，返回最小生成树的权值之和
int Prim(MGraph* G, int startV, EdgeSet* result);
#endif //PRIM_H
