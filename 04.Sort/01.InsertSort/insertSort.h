#ifndef INSERTSORT_H
#define INSERTSORT_H
#include "../sortHelper.h"

// 直接插入排序（找位置插入）
void insertSort(SortTable *table);
// 直接插入排序（扑克牌的交换）
void insertSortV1(SortTable *table);
// shell排序（希尔排序）
void shellSort(SortTable *table);
#endif //INSERTSORT_H
