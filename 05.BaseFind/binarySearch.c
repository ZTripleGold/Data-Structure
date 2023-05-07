#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef int Element;

// 二分查找
int binarySearch(Element *data, int n, Element target) {
    int left = 0;
    int right = n - 1;
    int mid;
    while (left <= right) {
        mid  = (right - left) / 2 + left;
        if (data[mid] == target) {
            return mid;
        }
        else if (data[mid] < target) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
    return -1;
}

// 顺序查找
int SeqSearch(Element *data, int n, Element target) {
    // 可以创建n + 1个空间，下标为0即第一个位置为哨兵放target，从后往前遍历，如果返回值是0即找不到
    for (int i = 0; i < n; ++i) {
        if (data[i] == target) {
            return i;
        }
    }
    return -1;
}

// 产生有n个元素的有序序列
Element *generateSeqTable(int n) {
    Element *data = (Element*) malloc(sizeof(Element) * n);
    if (data == NULL) {
        printf("fail to malloc!\n");
        return NULL;
    }
    for (int i = 0; i < n; ++i) {
        data[i] = i;
    }
    return data;
}

int main() {
    int n = 10000;
    Element *data = generateSeqTable(n);
    if (data == NULL) {
        return -1;
    }
    clock_t start = clock();
    for (int i = 0; i < n; ++i) {
        if (binarySearch(data, n, n + 10) != -1) {
            printf("Binary Search failed!\n");
        }
    }
    clock_t end = clock();
    printf("Binary Search cost: %f s\n", (double)(end - start) / CLOCKS_PER_SEC);

    start = clock();
    for (int i = 0; i < n; ++i) {
        if (SeqSearch(data, n, n + 10) != -1) {
            printf("Sequence Search failed!\n");
        }
    }
    end = clock();
    printf("Sequence Search cost: %f s\n", (double)(end - start) / CLOCKS_PER_SEC);
    free(data);
    return 0;
}