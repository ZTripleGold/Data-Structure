#include <stdio.h>
#include "KeyPath.h"

static AGraph *setupAGraph() {
    char *names[] = {"V0", "V1", "V2", "V3","V4",
                     "V5", "V6", "V7","V8"};
    int n = sizeof(names) / sizeof(names[0]);
    AGraph *G = createAGraph(n);
    initAGraph(G, n, names, 1);
    addAGraphEdge(G, 0, 1, 6);
    addAGraphEdge(G, 0, 2, 4);
    addAGraphEdge(G, 0, 3, 5);
    addAGraphEdge(G, 1, 4, 1);
    addAGraphEdge(G, 2, 4, 1);
    addAGraphEdge(G, 3, 5, 2);
    addAGraphEdge(G, 4, 6, 9);
    addAGraphEdge(G, 4, 7, 7);
    addAGraphEdge(G, 5, 7, 4);
    addAGraphEdge(G, 6, 8, 2);
    addAGraphEdge(G, 7, 8, 4);
    return G;
}

int main() {
    AGraph *G = setupAGraph();
    keyPath(G);
    releaseAGraph(G);
    return 0;
}