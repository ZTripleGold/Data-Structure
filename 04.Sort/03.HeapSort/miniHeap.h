#ifndef MINIHEAP_H
#define MINIHEAP_H
#include "../sortHelper.h"

// 最小堆结构，用顺序数组表示的完全二叉树来存储
typedef struct {
    keyType *data;      // 用顺序存储动态保存堆的数据
    int len;            // 约束数据的个数
    int capacity;       // 堆的最大容量
}MiniHeap;

// 产生n个元素的堆空间
MiniHeap *createMiniHeap(int n);
void releaseMiniHeap(MiniHeap* miniHeap);

// 插入元素
void insertMiniHeap(MiniHeap* miniHeap, keyType e);
// 提取元素
keyType extractMiniHeap(MiniHeap* miniHeap);
#endif //MINIHEAP_H
