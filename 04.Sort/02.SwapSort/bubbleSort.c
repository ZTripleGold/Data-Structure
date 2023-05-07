#include "bubbleSort.h"

/* 找最大值，把最大的放在右边，两层循环*/

// 冒泡排序
void bubbleSortV1(SortTable *table) {
    for (int i = 0; i < table->length; ++i) {
        // 每轮循环找到一个最大值，下轮排序就减少一个
        for (int j = 0; j < table->length - i - 1; ++j) {
            if (table->data[j].key > table->data[j + 1].key) {
                swapElement(&table->data[j], &table->data[j + 1]);
            }
        }
    }
}

// 优化，引入有序标记，当发现某一轮冒泡有序时，就退出循环
void bubbleSortV2(SortTable *table) {
    for (int i = 0; i < table->length; ++i) {
        int isSorted = 1;
        for (int j = 0; j < table->length - i - 1; ++j) {
            if (table->data[j].key > table->data[j + 1].key) {
                swapElement(&table->data[j], &table->data[j + 1]);
                isSorted = 0;
            }
        }
        // 当isSorted为1，即一轮下来没有发生交换，则序列已经有序，退出循环
        if (isSorted) {
            break;
        }
    }
}

// 再优化，引入newIndex，标记最后一次交换的位置，下次冒泡排序时，只需要遍历到这个newIndex位置
void bubbleSortV3(SortTable *table) {
    int newIndex;
    int n = table->length;
    do {
        newIndex = 0;
        for (int i = 0; i < n - 1; ++i) {
            if (table->data[i].key > table->data[i + 1].key) {
                swapElement(&table->data[i], &table->data[i + 1]);
                newIndex = i + 1;
            }
        }
        // 下轮循环遍历到最后一次交换的位置，后面没有交换的即是有序的
        n = newIndex;
    }
    while (newIndex > 0);
    // 同理，当newIndex为0时，没有发生交换，序列已经有序退出循环
}