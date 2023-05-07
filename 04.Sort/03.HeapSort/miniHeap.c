#include "miniHeap.h"

MiniHeap *createMiniHeap(int n) {
    MiniHeap *miniHeap = (MiniHeap*) malloc(sizeof(MiniHeap));
    if (miniHeap == NULL) {
        printf("fail to malloc!\n");
        return NULL;
    }
    // 元素初始下标为1，下标为0的位置空出方便用顺序数组表示完全二叉树，所以创建n + 1个空间
    miniHeap->data = (keyType*) malloc(sizeof(keyType) * (n + 1));
    if (miniHeap->data == NULL) {
        printf("fail to malloc!\n");
        return NULL;
    }
    miniHeap->capacity = n;
    miniHeap->len = 0;      // 每次插入元素，len先++再插入
    return miniHeap;
}
void releaseMiniHeap(MiniHeap* miniHeap) {
    if (miniHeap) {
        if (miniHeap->data) {
            free(miniHeap->data);
            miniHeap->data = NULL;
        }
        free(miniHeap);
    }
}

// 元素上浮
static void shiftUp(MiniHeap* miniHeap, int k) {
    keyType temp;
    while (k > 1 && miniHeap->data[k / 2] > miniHeap->data[k]) {     // 与父节点的值比较，当k循环到第一个位置时，或父节点值比当前位置值小时退出循环
        temp = miniHeap->data[k];
        miniHeap->data[k] = miniHeap->data[k / 2];
        miniHeap->data[k / 2] = temp;
        k /= 2;
    }
}

// 插入元素
/* 在最后的位置插入元素，再与父节点进行判断，如果小于父节点，则交换；将插入元素上浮，直到每个根节点都是子节点中的最小值*/
void insertMiniHeap(MiniHeap* miniHeap, keyType e) {
    if (miniHeap->len + 1 > miniHeap->capacity) {   // 元素满的情况
        printf("MiniHeap is full!\n");
        return;
    }
    miniHeap->data[++miniHeap->len] = e;
    // 元素上浮操作
    shiftUp(miniHeap, miniHeap->len);
}

// 下沉元素
static void shiftDown(MiniHeap* miniHeap, int k) {
    keyType temp;
    while (2 * k <= miniHeap->len) {     // 当前位置有左孩子，因为堆是完全二叉树，不存在有右孩子而没有左孩子的情况
        int index = 2 * k;
        if (index + 1 <= miniHeap->len && miniHeap->data[index + 1] < miniHeap->data[index]) {
            // 有右孩子的情况，比较左右孩子取较小的值的下标；如果没有右孩子就直接取左孩子
            index = index + 1;
        }
        if (miniHeap->data[k] <= miniHeap->data[index]) {
            // 当前元素小于等于左右孩子值，符合最小堆定义，退出
            break;
        }
        temp = miniHeap->data[k];
        miniHeap->data[k] = miniHeap->data[index];
        miniHeap->data[index] = temp;
        k = index;
    }
}

// 提取元素
/* 备份第一个元素即堆顶元素，将最后一个元素赋给第一个元素，len--；然后根据规则下沉元素*/
keyType extractMiniHeap(MiniHeap* miniHeap) {
    if (miniHeap->len <= 0) {       // 堆内没有元素
        printf("MiniHeap is empty!\n");
        return 0;
    }
    keyType temp = miniHeap->data[1];
    miniHeap->data[1] = miniHeap->data[miniHeap->len--];
    // 下沉元素操作
    shiftDown(miniHeap, 1);
    return temp;
}