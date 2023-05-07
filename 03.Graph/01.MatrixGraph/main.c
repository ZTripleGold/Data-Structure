#include <stdio.h>
#include "matrixGraph.h"

static void setupMatrixGraph(MGraph *G) {
    char *nodeName[] = {"V1", "V2", "V3", "V4",
                        "V5", "V6", "V7", "V8"};
    initMGraph(G, sizeof(nodeName) / sizeof(nodeName[0]), nodeName, 0, 0);
    addEdge(G, 0, 1, 1);
    addEdge(G, 0, 2, 1);
    addEdge(G, 1, 3, 1);
    addEdge(G, 1, 4, 1);
    addEdge(G, 2, 5, 1);
    addEdge(G, 2, 6, 1);
    addEdge(G, 3, 7, 1);
    addEdge(G, 4, 7, 1);
    addEdge(G, 5, 6, 1);
}

int main() {
    MGraph G1;
    setupMatrixGraph(&G1);
    printf("have %d num!\n", G1.edgeNum);

    printf("深度搜索DFS： ");
    DFSMGraph(&G1, 0);
    clearVisited();
    printf("\n广度搜素BFS：");
    BFSMGraph(&G1, 0);
    return 0;
}