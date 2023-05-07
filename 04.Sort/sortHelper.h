#ifndef SORTHELPER_H
#define SORTHELPER_H
#include <stdio.h>
#include <stdlib.h>

typedef int keyType;
typedef struct {
    keyType key;        // 查找表中每个数据元素的关键值
    void *data;         // 数据的其他区域，存储数据的其他信息
}Element;

typedef struct {
    Element *data;      // 存放查找表中数据元素的首地址，即是存储数据元素的数组
    int length;         // 查找表的元素个数
}SortTable;

enum sortStatus {success, failed};  // 枚举出排序的情况


void swapElement(Element *a, Element *b);                       // 将两个元素交换
SortTable *generateRandomArray(int n, int low, int high);       // 产生n个范围在[low, high]的随机数
SortTable *generateLinearArray(int n, int swapTimes);           // 参数顺序空间，随机交换swapTimes次
SortTable *copySortTable(SortTable *oldTable);                  // 拷贝和oldTable一样值的顺序表
void releaseSortTable(SortTable *table);

// 排序算法函数的别名，传递的是一个指针
typedef void (*sortHandler)(SortTable *table);
// 测试sortName的排序算法，打印出算法所需要的时间
void testSort(const char *sortName, sortHandler sort, SortTable *table);
#endif //SORTHELPER_H
