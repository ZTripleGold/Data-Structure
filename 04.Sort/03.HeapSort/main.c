#include "heapSort.h"

void test01() {
    int data[] = {9, 3, 7, 6, 5, 1, 10, 2};
    int n = 20;
    MiniHeap *miniHeap = createMiniHeap(n);
    for (int i = 0; i < sizeof(data) / sizeof(data[0]); ++i) {
        insertMiniHeap(miniHeap, data[i]);
    }
    printf("array: ");
    for (int i = 0; i < sizeof(data) / sizeof(data[0]); ++i) {
        printf("\t%d", data[i]);
    }
    printf("\nextract: ");
    for (int i = 0; i < sizeof(data) / sizeof(data[0]); ++i) {
        printf("\t%d", extractMiniHeap(miniHeap));
    }
    releaseMiniHeap(miniHeap);
}

// 随机序列的堆排序测试
void test02() {
    int n = 10000000;
    SortTable *table = generateRandomArray(n, 0, n);
    testSort("Heap Sort: ", heapSort, table);
    releaseSortTable(table);
}

int main() {
    // test01();
    test02();
    return 0;
}