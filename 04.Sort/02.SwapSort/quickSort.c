// #include <stdlib.h>
#include <time.h>
#include "quickSort.h"

// 双边循环法
/* 1. 设置左、右标记，认为最左边元素为基准元素
 * 2. 先从右元素开始，让right标记指向的元素和基准元素比较，
 *    如果大于pivot，则左移；如果小于，则停止right，切换到left标记移动
 * 3. 在left标记中，如果小于，则右移；如果大于，则停止left
 * 4. 此时交换左右的值
 * 5. 一直循环到left与right相等，则找到基准元素的位置，将基准元素放入该位置*/

static int partitionDouble(SortTable *table, int startIndex, int endIndex) {
    int pivot = startIndex;
    int left = startIndex;
    int right = endIndex;
    // 随机取一个位置与基准元素交换
    srand((unsigned )time(NULL) + 1);
    swapElement(&table->data[pivot], &table->data[rand() % (endIndex - startIndex) + startIndex]);
    while (left != right) {
        // 从右边找到小于基准元素的值，左边找到大于基准元素的值，然后将二者交换
        while (left < right && table->data[right].key > table->data[pivot].key) right--;
        while (left < right && table->data[left].key <= table->data[pivot].key) left++;
        if (left < right) {
            swapElement(&table->data[left], &table->data[right]);
        }
    }
    // left和right相等，确定基准元素位置，交换
    swapElement(&table->data[left], &table->data[pivot]);
    return left;
}

static void quickSort1(SortTable *table, int startIndex, int endIndex) {
    if (startIndex >= endIndex) {
        return;
    }
    int pivot = partitionDouble(table, startIndex, endIndex);
    // 递归分为两部分处理
    quickSort1(table, startIndex, pivot - 1);
    quickSort1(table, pivot + 1, endIndex);
}

void quickSortV1(SortTable *table) {
    quickSort1(table, 0, table->length - 1);
}


// 单边循环法，设置一个mark标记，表示小于基准元素的区域边界
/* 1. 从基准元素的下一个位置开始遍历数组
 * 2. 如果遍历到的元素大于基准元素，则继续往后遍历
 * 3. 如果遍历到的元素小于基准元素
 *  3.1 则mark++
 *  3.2 将遍历到的元素与当前的mark对应元素值（是大于基准元素的，也有可能与自身交换）
 * 4. 最后把mark与基准元素交换位置*/
static int partitionSingle(SortTable *table, int startIndex, int endIndex) {
    srand((unsigned )time(NULL) + 1);
    swapElement(&table->data[startIndex], &table->data[rand() % (endIndex - startIndex) + startIndex]);
    int mark = startIndex;
    keyType temp = table->data[startIndex].key;
    for (int i = startIndex + 1; i <= endIndex; ++i) {
        // 发现比基准元素小的值，mark++，交换mark和i对应的元素
        if (table->data[i].key < temp) {
            mark++;
            swapElement(&table->data[i], &table->data[mark]);
        }
    }
    // 最后将mark与基准元素交换位置，此时mark左边都比它小，右边都比它大
    swapElement(&table->data[mark], &table->data[startIndex]);
    return mark;
}

static void quickSort2(SortTable *table, int startIndex, int endIndex) {
    if (startIndex >= endIndex) {
        return;
    }
    int pivot = partitionSingle(table, startIndex, endIndex);
    quickSort1(table, startIndex, pivot - 1);
    quickSort1(table, pivot + 1, endIndex);
}

void quickSortV2(SortTable *table) {
    quickSort2(table, 0, table->length - 1);
}