#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "sortHelper.h"

// 将两个元素交换
void swapElement(Element *a, Element *b) {
    Element temp;
    memcpy(&temp, a, sizeof(Element));
    memcpy(a, b, sizeof(Element));
    memcpy(b, &temp, sizeof(Element));
}

// 产生n个范围在[low, high]的随机数
SortTable *generateRandomArray(int n, int low, int high) {
    SortTable *table = (SortTable*) malloc(sizeof(SortTable));
    if (table == NULL) {
        fprintf(stderr, "fail to malloc!\n");
        return NULL;
    }
    table->length = n;
    table->data = (Element*) malloc(sizeof(Element) * n);
    if (table->data == NULL) {
        fprintf(stderr, "fail to malloc!\n");
        free(table);
        return NULL;
    }
    srand((unsigned )time(NULL) + 1);
    for (int i = 0; i < n; ++i) {
        table->data[i].key = (rand() % (high - low + 1)) + low;
        table->data[i].data = NULL;     // 后面数据有其他信息可以修改
    }
    return table;
}

// 参数顺序空间，随机交换swapTimes次
SortTable *generateLinearArray(int n, int swapTimes) {
    SortTable *table = (SortTable*) malloc(sizeof(SortTable));
    if (table == NULL) {
        fprintf(stderr, "fail to malloc!\n");
        return NULL;
    }
    table->data = (Element*) malloc(sizeof(Element) * n);
    if (table->data == NULL) {
        fprintf(stderr, "fail to malloc!\n");
        free(table);
        return NULL;
    }
    table->length = n;
    for (int i = 0; i < n; ++i) {   // 产生顺序表
        table->data[i].key = i;
        table->data[i].data = NULL;
    }
    // 在已经有序的排序表中，随机选择两个元素，交换swapTimes次
    srand((unsigned ) time(NULL) + 2);
    for (int i = 0; i < swapTimes; ++i) {
        int pos1 = rand() % n;
        int pos2 = rand() % n;
        swapElement(&table->data[pos1], &table->data[pos2]);
    }
    return table;
}

// 拷贝和oldTable一样值的顺序表
SortTable *copySortTable(SortTable *oldTable) {
    SortTable *newTable = (SortTable*) malloc(sizeof(SortTable));
    if (newTable == NULL) {
        fprintf(stderr, "fail to malloc!\n");
        return NULL;
    }
    newTable->length = oldTable->length;
    newTable->data = (Element*) malloc(sizeof(Element) * oldTable->length);
    if (newTable->data == NULL) {
        fprintf(stderr, "fail to malloc!\n");
        free(newTable);
        return NULL;
    }
    for (int i = 0; i < oldTable->length; ++i) {
        newTable->data[i].key = oldTable->data[i].key;
        newTable->data[i].data = oldTable->data[i].data;
    }
    return newTable;
}

// 释放table
void releaseSortTable(SortTable *table) {
    if (table) {
        if (table->data) {
            free(table->data);
        }
        free(table);
    }
}

// 检查排序表里的数据，是否是从小到大排序，这里的排序算法都选择从小到大排序
static enum sortStatus checkData(SortTable *table) {
    for (int i = 0; i < table->length - 1; ++i) {
        if (table->data[i].key > table->data[i + 1].key) {
            printf("Check Sort Data Failed: %d : %d\n", table->data[i].key, table->data[i + 1].key);
            return failed;
        }
    }
    return success;
}

// 测试sortName的排序算法，打印出算法所需要的时间
void testSort(const char *sortName, sortHandler sort, SortTable *table) {
    // 计算排序算法所需要的时间
    clock_t start = clock();        // 开始
    sort(table);
    clock_t end = clock();          // 结束
    // 当排序成功时，打印消耗的时间
    if (checkData(table) == failed) {
        printf("%s failed!\n", sortName);
        return;
    }
    printf("%s cost time: %fs\n", sortName, (double)(end - start) / CLOCKS_PER_SEC);
}