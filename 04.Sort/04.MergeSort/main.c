#include "mergeSort.h"

int main() {
    int n = 10000000;
    SortTable *table = generateRandomArray(n, 0, n);
    testSort("Merge Sort", mergeSort, table);
    releaseSortTable(table);
    return 0;
}