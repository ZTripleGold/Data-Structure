#include <stdlib.h>
#include "mergeSort.h"

// 归并排序
/* 将一个大任务细分成两个小任务，直到不能划分，分治思想*/

static void merge(SortTable *table, int left, int mid, int right) {
    int nLeft = mid - left + 1;         // 左边部分的元素个数
    int nRight = right - mid;           // 右边部分的元素个数
    // 创建两个临时数组，进行排序
    Element *aux1 = (Element*) malloc(sizeof(Element) * nLeft);
    Element *aux2 = (Element*) malloc(sizeof(Element) * nRight);
    if (aux1 == NULL || aux2 == NULL) {
        printf("fail to malloc!\n");
        return;
    }
    // 将左右任务的子空间进行拷贝
    for (int i = 0; i < nLeft; ++i) {
        aux1[i] = table->data[left + i];
    }
    for (int i = 0; i < nRight; ++i) {
        aux2[i] = table->data[mid + 1 + i];
    }
    // 比较两个有序数组，整合成一个有序数组
    int i = 0;          // 左数组的索引，即左空间的最小值位置
    int j = 0;          // 右数组的索引，即右空间的最小值位置
    int k = left;       // 合并数组的索引，即table->data
    while (i < nLeft && j < nRight) {
        if (aux1[i].key <= aux2[j].key) {
            table->data[k] = aux1[i++];
        }
        else {
            table->data[k] = aux2[j++];
        }
        k++;
    }
    // 可能有一个数组已经遍历完，另一个数组还有元素
    while (i < nLeft) {
        table->data[k++] = aux1[i++];
    }
    while (j < nRight) {
        table->data[k++] = aux2[j++];
    }
    // 释放临时数组
    free(aux1);
    free(aux2);
}

static void mergeLoop(SortTable *table, int left, int right) {
    if (left >= right) {
        return;
    }
    int mid = (right - left) / 2 + left;
    // 二等分成两份进行排序
    mergeLoop(table, left, mid);
    mergeLoop(table, mid + 1, right);
    // 将排序好的两部分进行合并
    merge(table, left, mid, right);
}

void mergeSort(SortTable *table) {
    mergeLoop(table, 0, table->length - 1);
}