#include <stdio.h>
#include <stdlib.h>
#include "DijkstraShortestPath.h"

void setupMGraph(MGraph* G) {
    char* names[] = {"0", "1", "2", "3",
                    "4", "5", "6"};
    initMGraph(G, sizeof(names) / sizeof(names[0]), names, INF, 1); // 初始化边的权值为无穷大
    addEdge(G, 0, 1, 4);
    addEdge(G, 0, 2, 6);
    addEdge(G, 0, 3, 6);
    addEdge(G, 1, 4, 7);
    addEdge(G, 1, 2, 1);
    addEdge(G, 2, 4, 6);
    addEdge(G, 2, 5, 4);
    addEdge(G, 3, 2, 2);
    addEdge(G, 3, 5, 5);
    addEdge(G, 4, 6, 6);
    addEdge(G, 5, 4, 1);
    addEdge(G, 5, 6, 8);
}

int main() {
    MGraph G;
    int* dis;           // 存储源节点到其他节点的最小权值和
    int* path;          // 存储源节点到该节点pos的最短路径的前一个节点

    setupMGraph(&G);
    dis = (int*) malloc(sizeof(int) * G.nodeNum);
    path = (int*) malloc(sizeof(int) * G.nodeNum);
    if (dis == NULL || path == NULL) {
        printf("fail to malloc!\n");
        return -1;
    }

    DijkstraMGraph(&G, 0, dis, path);
    printf("0节点到6节点的路径权值和：%d\n", dis[6]);
    showPath(path, G.nodeNum, 6);

    free(dis);
    free(path);
    return 0;
}