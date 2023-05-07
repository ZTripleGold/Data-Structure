#include <stdio.h>
#include "adjacentGraph.h"

static void setupAGraph(AGraph *G) {
    char* names[] = {"A", "B", "C", "D", "E"};
    initAGraph(G, sizeof(names) / sizeof(names[0]), names, 1);
    addAGraphEdge(G, 0, 4, 1);
    addAGraphEdge(G, 0, 3, 1);
    addAGraphEdge(G, 0, 1, 1);
    addAGraphEdge(G, 1, 4, 1);
    addAGraphEdge(G, 1, 2, 1);
    addAGraphEdge(G, 2, 0, 1);
    addAGraphEdge(G, 3, 2, 1);
}

int main() {
    int n = 5;
    AGraph *G = createAGraph(n);
    setupAGraph(G);
    printf("边数：%d\n", G->edgeNum);
    printf("深度搜索DFS：");
    DFSAGraph(G, 0);
    resetVisited(G);
    printf("\n广度遍历BFS：");
    BFSAGraph(G, 0);
    printf("\n");
    releaseAGraph(G);
}