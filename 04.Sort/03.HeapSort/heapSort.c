#include "heapSort.h"

void heapSort(SortTable* table) {
    MiniHeap *miniHeap = createMiniHeap(table->length);
    if (miniHeap == NULL) {
        printf("fail to malloc!\n");
        return;
    }
    for (int i = 0; i < table->length; ++i) {
        insertMiniHeap(miniHeap, table->data[i].key);
    }
    for (int i = 0; i < table->length; ++i) {
        table->data[i].key = extractMiniHeap(miniHeap);
    }
    releaseMiniHeap(miniHeap);
}