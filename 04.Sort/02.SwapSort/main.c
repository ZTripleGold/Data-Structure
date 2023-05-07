#include "bubbleSort.h"
#include "quickSort.h"

int main() {
    int n = 100000;
    SortTable *table1 = generateRandomArray(n, 0, n);
    SortTable *table2 = copySortTable(table1);
    SortTable *table3 = copySortTable(table1);
    SortTable *table4 = copySortTable(table1);
    SortTable *table5 = copySortTable(table1);

    testSort("Bubble Sort V1", bubbleSortV1, table1);
    testSort("Bubble Sort V2", bubbleSortV2, table2);
    testSort("Bubble Sort V3", bubbleSortV3, table3);
    testSort("Quick Sort V1", quickSortV1, table4);
    testSort("Quick Sort V2", quickSortV2, table5);

    releaseSortTable(table1);
    releaseSortTable(table2);
    releaseSortTable(table3);
    releaseSortTable(table4);
    releaseSortTable(table5);
    return 0;
}