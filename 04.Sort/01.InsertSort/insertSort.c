#include "insertSort.h"

// 直接插入排序（扑克牌的交换）
void insertSortV1(SortTable *table) {
    // 默认第一个元素有序，遍历从 i = 1 开始，往后遍历无序的区域
    for (int i = 1; i < table->length; ++i) {
        // 遍历无序的区域，取到无序区域的值，然后不断往前与有序区域的值比较
        // 如果小于有序区域的值就交换，退出循环时的位置就是插入的位置
        Element e = table->data[i];
        int j;
        for (j = i; j > 0 && e.key < table->data[j - 1].key; j--) {
            swapElement(&table->data[j], &table->data[j - 1]);
        }
        table->data[j] = e;
    }
}

/* 插入排序的共同点 第一个循环往后遍历无序的区域，第二个循环往前与有序区域的值比较
 * 即 i++ j--
 * */

// 直接插入排序（找位置插入），相比于交换，效率更高
/* 1. 默认第一个元素有序，遍历从 i = 1 开始，从第二个元素开始和前面有序的区域进行比较
 * 2. 待插入的元素从后往前依次与有序区域的元素比较，
 *    若待插入元素 < 有序区域元素，那么将有序区域的值向后移一位
 *    插入查找的位置范围 [0 ... i-1]*/
void insertSort(SortTable *table) {
    for (int i = 1; i < table->length; ++i) {
        if (table->data[i].key < table->data[i - 1].key) {
            // 用j来辅助寻找待插入元素的真正插入位置
            int j = i - 1;
            Element temp = table->data[i]; // 备份待插入元素
            // 在 [0 ... i-1] 范围内查找，直到找到一个位置，待插入值比这个位置的值大
            while (j > -1 && temp.key < table->data[j].key) {
                table->data[j + 1] = table->data[j];
                j--;
            }
            table->data[j + 1] = temp;
        }
        // 未进 if 说明待插入的元素比之前有序区域元素都大，那么此时的i位置就是这个元素插入的位置
    }
}

// shell排序（希尔排序）
void shellSort(SortTable *table) {
    int gap;
    // gap为步长，每一组都执行插入排序；当 gap = 1 时，对整个序列进行插入排序，然后退出循环
    for (gap = table->length / 2; gap > 0; gap /= 2) { // 对每个步长分别进行插入排序
        // 共gap个组，每一组都执行插入排序；例如 gap = 1，就只有一组为整个序列，进行插入排序
        for (int i = gap; i < table->length; ++i) {
            Element temp = table->data[i];
            int j;
            // 遍历的跨度为 gap；当 gap = 1时，即是对整个序列排序
            for (j = i; j >= gap && temp.key < table->data[j - gap].key; j -= gap) {
                swapElement(&table->data[j], &table->data[j - gap]);
            }
            table->data[j] = temp;
        }
    }
}