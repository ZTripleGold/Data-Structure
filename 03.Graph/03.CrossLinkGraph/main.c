#include <stdio.h>
#include "crossLinkGraph.h"

static void setupGraph(CrossLinkGraph *graph) {
    char *nodeName[] = {"V0", "V1", "V2", "V3"};
    initCrossLinkGraph(graph, sizeof(nodeName) / sizeof(nodeName[0]), nodeName);
    addCrossLinkEdge(graph, 0, 3, 1);
    addCrossLinkEdge(graph, 1, 0, 1);
    addCrossLinkEdge(graph, 1, 2, 1);
    addCrossLinkEdge(graph, 2, 0, 1);
    addCrossLinkEdge(graph, 2, 1, 1);
}

int main() {
    int n = 4;
    CrossLinkGraph *G = createCrossLinkGraph(n);
    if (G == NULL) {
        return -1;
    }
    setupGraph(G);
    printf("V0的入度为: %d\n", inDegreeCrossLink(G, 0));
    printf("V0的出度为: %d\n", outDegreeCrossLink(G, 0));
    releaseCrossLinkGraph(G);
    return 0;
}