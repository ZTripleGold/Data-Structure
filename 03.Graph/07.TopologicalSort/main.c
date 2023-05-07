#include <stdio.h>
#include <stdlib.h>
#include "TopologicalSort.h"

// 无环图
AGraph *setupAGraph1() {
    char *names[] = {"0", "1", "2", "3",
                     "4", "5", "6"};
    int n = sizeof(names) / sizeof(names[0]);
    AGraph *G = createAGraph(n);
    if (G == NULL) {
        return NULL;
    }
    initAGraph(G, n, names, 1);
    addAGraphEdge(G, 0, 1, 1);
    addAGraphEdge(G, 0, 2, 1);
    addAGraphEdge(G, 0, 3, 1);
    addAGraphEdge(G, 1, 2, 1);
    addAGraphEdge(G, 1, 4, 1);
    addAGraphEdge(G, 2, 4, 1);
    addAGraphEdge(G, 2, 5, 1);
    addAGraphEdge(G, 3, 5, 1);
    addAGraphEdge(G, 4, 6, 1);
    addAGraphEdge(G, 5, 4, 1);
    addAGraphEdge(G, 5, 6, 1);
    return G;
}

// 有环图
AGraph *setupAGraph2() {
    char *names[] = {"A", "B", "C", "D", "E"};
    int n = sizeof(names) / sizeof(names[0]);
    AGraph *G = createAGraph(n);
    if (G == NULL) {
        return NULL;
    }
    initAGraph(G, n, names, 1);
    addAGraphEdge(G, 0, 1, 1);
    addAGraphEdge(G, 0, 2, 1);
    addAGraphEdge(G, 1, 3, 1);
    addAGraphEdge(G, 2, 4, 1);
    addAGraphEdge(G, 3, 4, 1);
    addAGraphEdge(G, 4, 1, 1);
    return G;
}

int main() {
    // AGraph *G = setupAGraph1();
    AGraph *G = setupAGraph2();
    int result = TopologicalSortAGraph(G);
    printf("\nresult = %d\n", result);
    releaseAGraph(G);
    return 0;
}