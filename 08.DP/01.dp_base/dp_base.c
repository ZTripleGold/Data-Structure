#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static unsigned int cnt;
unsigned int fib01(unsigned int n) {
    ++cnt;
    if (n == 0)
        return 0;
    if (n == 1)
        return 1;
    return fib01(n - 1) + fib01(n - 2);
}

void test01() {
    cnt = 0;
    clock_t start = clock();
    unsigned int x = fib01(50);
    clock_t end = clock();
    printf("cost time : %f s. fib01 = %u\n", (double )(end - start) / CLOCKS_PER_SEC, x);
    printf("run fib01 %d times\n", cnt);
}

// 记忆化搜索（备忘录）
static unsigned int *memory1;
unsigned int fib02(unsigned int n) {
    ++cnt;
    if (n == 0)
        return 0;
    if (n == 1)
        return 1;
    if (memory1[n] == -1) {
        memory1[n] = fib02(n - 1) + fib02(n - 2);
    }
    return memory1[n];
}

void test02() {
    cnt = 0;
    int n = 50;
    memory1 = (unsigned int*) malloc(sizeof(unsigned int) * (n + 1));
    if (memory1 == NULL) {
        printf("fail to malloc!\n");
        return;
    }
    for (int i = 0; i <= n; ++i) {
        memory1[i] = -1;        // 以子问题中不会出现的状态，这里如-1，作为记忆化搜索表的初始值
    }
    clock_t start = clock();
    unsigned int x = fib02(n);
    clock_t end = clock();
    printf("cost time : %f s. fib02 = %u\n", (double )(end - start) / CLOCKS_PER_SEC, x);
    printf("run fib02 %d times\n", cnt);
    free(memory1);
}

// DP table
unsigned int fib03(unsigned int n) {
    cnt = 0;
    unsigned int res;
    unsigned int *memory = (unsigned int *) malloc(sizeof(unsigned int) * (n + 1));
    if (memory == NULL) {
        printf("fail to malloc!\n");
        return -1;
    }
    memory[0] = 0;
    memory[1] = 1;
    for (int i = 2; i <= n; ++i) {
        memory[i] = memory[i - 1] + memory[i - 2];
    }
    res = memory[n];
    free(memory);
    return res;
}

void test03() {
    int n = 50;
    clock_t start = clock();
    unsigned int x = fib03(n);
    clock_t end = clock();
    printf("cost time : %f s. fib03 = %u\n", (double )(end - start) / CLOCKS_PER_SEC, x);
    printf("run fib03 %d times\n", cnt);
}

int main() {
    test01();
    test02();
    test03();
    return 0;
}