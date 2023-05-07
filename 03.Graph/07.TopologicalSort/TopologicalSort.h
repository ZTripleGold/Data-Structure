#ifndef TOPOLOGICALSORT_H
#define TOPOLOGICALSORT_H
#include "../02.AdjacentGraph/adjacentGraph.h"
/* 拓扑排序，一般用于有向图，用邻接表来表示AOV网
 * 1.根据邻接表初始化入度表，遍历入度表，找出入度表中度为0的顶点，压入任务栈中（用栈来实现，就不用每次都遍历入度表，增加时间损耗）
 * 2.从任务栈中弹出一个顶点，更新入度表，如果有度为0的顶点，也压入任务栈中（其他顶点的入度不会变化，只用关心弹出顶点的出边）
 * 3.直到任务栈为空*/

// 返回0为无环，返回1为有环，返回-1错误
int TopologicalSortAGraph(AGraph* G);
#endif //TOPOLOGICALSORT_H
