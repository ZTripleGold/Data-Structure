#ifndef QUICKSORT_H
#define QUICKSORT_H
#include "../sortHelper.h"
/* 快速排序
 * 冒泡排序在每一轮中，只把1个元素冒泡到数组的一端
 * 快速排序则是每一轮挑选一个基准元素即奇点，大的元素在奇点的右边，小的元素在奇点的左边
 * 基准元素的选择：随机选择一个元素作为基准元素，并让基准元素和第一个元素进行交换*/

// 双边循环法
void quickSortV1(SortTable *table);
// 单边循环法
void quickSortV2(SortTable *table);
#endif //QUICKSORT_H
