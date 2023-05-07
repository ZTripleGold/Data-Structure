#ifndef FINDSTR_H
#define FINDSTR_H

#include <stdio.h>
#include <stdlib.h>

// 定义串的结构
typedef struct {
    char *str;
    int length;
}StrType;

int strAssign(StrType *str, const char *ch);
void releaseStr(StrType *str);

// 暴力匹配
int index_simple(const StrType *str, const StrType *subStr);

// 求next数组
void getNext(const StrType *subStr, int next[]);
int indexKMP(const StrType *str, const StrType *subStr, const int next[]);
#endif //FINDSTR_H
