#ifndef KEYPATH_H
#define KEYPATH_H
/* 关键路径在AOE网中，边表示活动，顶点表示事件
 * 关键路径就是AOE网看做整个项目，完成整个项目至少需要多少时间？
 * 解决这个问题，关键在于从AOE网中，找到一条从起始点到结束点长度的最大值
 * */
#include "../02.AdjacentGraph/adjacentGraph.h"

// 关键路径
void keyPath(AGraph* G);
#endif //KEYPATH_H
