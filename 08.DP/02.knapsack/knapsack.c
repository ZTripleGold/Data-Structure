#include <stdio.h>
#include <stdlib.h>

static int goodsW[] = {1, 2, 3};
static int goodsVal[] = {6, 10, 12};
static int bag_capacity = 5;

static int max(int a, int b) {
    return (a > b) ? a : b;
}

// 用[0...index]的物品，填充容积为C的背包的最大值
static int bestValue01(int index, int C) {
    if (index < 0 || C <= 0) {
        return 0;
    }
    // index处的物品不放入背包，即考虑[0...index - 1]的物品填充背包
    int res = bestValue01(index - 1, C);
    // 放入背包
    if (C >= goodsW[index]) {   // 当index处物品可以放入背包
        res = max(res, goodsVal[index] + bestValue01(index - 1, C - goodsW[index]));
    }
    return res;
}

// 暴力递归
int knapsack01() {
    bestValue01(sizeof(goodsW) / sizeof(goodsW[0]) - 1, bag_capacity);
}

static int bestValue02(int index, int C, void *data) {
    int (*memory)[bag_capacity + 1] = (int (*)[bag_capacity + 1])data;
    if (index < 0 || C <= 0) {
        return 0;
    }
    // 不等于-1说明之前已经计算过这种情况，直接返回即可
    if (memory[index][C] != -1) {
        return memory[index][C];
    }
    // 没有计算过，递归计算
    int res = bestValue02(index - 1, C, memory);
    if (C >= goodsW[index]) {   // 当index处物品可以放入背包
        res = max(res, goodsVal[index] + bestValue02(index - 1, C - goodsW[index], memory));
    }
    memory[index][C] = res;
    return res;
}

// 备忘录，记忆化搜索
int knapsack02() {
    // 容量为0与C都要考虑，定义时大小为C + 1
    int n = sizeof(goodsW) / sizeof(goodsW[0]);
    int (*memory)[bag_capacity + 1] = (int (*)[bag_capacity + 1]) malloc(sizeof(int) * n * (bag_capacity + 1));
    if (memory == NULL) {
        printf("fail to malloc!\n");
        return 0;
    }
    // 初始化备忘录
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j <= bag_capacity; ++j) {
            memory[i][j] = -1;
        }
    }
    int res = bestValue02(n - 1, bag_capacity, memory);
    free(memory);
    return res;
}

// DP
int knapsackDP(int n, int C) {
    // 同样要考虑0和C
    int (*dp)[C + 1] = (int (*)[C + 1]) malloc(sizeof(int) * n * (C + 1));
    if (dp == NULL) {
        printf("fail to malloc!\n");
        return 0;
    }
    // 初始化第一个物品，即将第一个物品放入背包，第0行
    for (int i = 0; i <= C; ++i) {
        // 背包容量大于第一个物品的质量时赋值，否则为0
        dp[0][i] = (i >= goodsW[0]) ? goodsVal[0] : 0;
    }
    // 从第二个物品开始
    for (int i = 1; i < n; ++i) {
        for (int j = 0; j <= C; ++j) {
            dp[i][j] = dp[i - 1][j];    // 不放入背包
            if (j >= goodsW[i]) {
                // 不放入背包与放入背包中最大的
                dp[i][j] = max(dp[i - 1][j], goodsVal[i] + dp[i - 1][j - goodsW[i]]);
            }
        }
    }
    return dp[n - 1][C];
}

int main() {
    int res = knapsackDP(sizeof(goodsW) / sizeof(goodsW[0]), bag_capacity);
    printf("res = %d\n", res);
    return 0;
}