#include <stdio.h>
#include <stdlib.h>
#include "Kruskal.h"
#include "Prim.h"

static void setupMGraph(MGraph* G, int edgeValue) {
    char* names[] = {"A", "B", "C", "D",
                     "E", "F", "G"};
    initMGraph(G, sizeof(names) / sizeof(names[0]), names, edgeValue, 0);
    addEdge(G, 0, 1, 12);
    addEdge(G, 0, 5, 16);
    addEdge(G, 0, 6, 14);
    addEdge(G, 1, 2, 10);
    addEdge(G, 1, 5, 7);
    addEdge(G, 2, 3, 3);
    addEdge(G, 2, 4, 5);
    addEdge(G, 2, 5, 6);
    addEdge(G, 3, 4, 4);
    addEdge(G, 4, 5, 2);
    addEdge(G, 4, 6, 8);
    addEdge(G, 5, 6, 9);
}

// Kruskal算法
int test01() {
    MGraph G;
    EdgeSet *edgeSet;
    setupMGraph(&G, 0); // 初始化边的权值为0

    // 初始化边集数组
    edgeSet = (EdgeSet*) malloc(sizeof(EdgeSet) * G.edgeNum);
    if (edgeSet == NULL) return 0;
    int num = initEdgeSet(&G, edgeSet);
    printf("edgeSet num: %d\n", num);
    // 排序边集数组
    sortEdgeSet(&G, edgeSet, num);
    // Kruskal算法
    EdgeSet *result = (EdgeSet*)malloc(sizeof (EdgeSet) * (G.nodeNum - 1));
    if (result == NULL) return 0;
    int sumWeight = KruskalMiniTree(&G, edgeSet, num, result);
    for (int i = 0; i < G.nodeNum - 1; ++i) {
        printf("edge %d: [%s] --- <%d> --- [%s]\n",
               i + 1, G.vex[result[i].begin].show, result[i].weight, G.vex[result[i].end].show);
    }
    printf("Kruskal sum of weight: %d\n", sumWeight);
    free(edgeSet);
    free(result);
    return 0;
}

// Prim算法
int test02() {
    MGraph G;
    EdgeSet *edgeSet;
    setupMGraph(&G, INF); // 初始化边权值为无穷大

    EdgeSet *result = (EdgeSet*)malloc(sizeof (EdgeSet) * (G.nodeNum - 1));
    if (result == NULL) return 0;
    int sumWeight = Prim(&G, 0, result);

    for (int i = 0; i < G.nodeNum - 1; ++i) {
        printf("edge %d: [%s] --- <%d> --- [%s]\n",
               i + 1, G.vex[result[i].begin].show, result[i].weight, G.vex[result[i].end].show);
    }
    printf("Prim sum of weight: %d\n", sumWeight);
    free(result);
    return 0;
}

int main() {
    test02();
    return 0;
}