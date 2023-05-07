#ifndef DISKTREE_H
#define DISKTREE_H
#include <stdio.h>
#include <stdlib.h>
#define MaxOrder 3      // B树的阶
/* 则B树的阶为3，最多子树为3棵子树，那么节点的最大元素个数为2
* 在插入节点时，当键值为3时，才会触发分离，申请的时候多申请一个
* | k0 | k1 | k2 | k3 |		k0是无效的  k3为了防止越界
* | p0 | p1 | p2 | p3 |		p0 < k1   k1 < p1 < k2  p2 > k2  p3是不访问
* */
typedef int KeyType;
/* 申明空间为 MaxOrder + 1， 回溯法*/
// B树的节点结构
typedef struct BTNode {
    KeyType key[MaxOrder + 1];          // 有效空间 [1, ..., MaxOrder - 1]， 0处无效，MaxOrder处防止溢出（这里用的是回溯法，先插入再判断是否分离）
    struct BTNode *ptr[MaxOrder + 1];     // 有效空间 [0, ..., MaxOrder - 1]， MaxOrder处无效
    struct BTNode *parent;              // 父节点
    int num;                            // 当前节点中的元素个数，即遍历时的右边边界
}BTNode;
// B树的树结构
typedef struct {
    BTNode *root;
    int cnt;
}DiskTree;

/* B树查找的结果集，包含查找成功和失败的信息
 * ptr : 查找成功，标记当前键值所在的节点地址
 * 		 查找失败，标记待插入节点（NULL）的父节点
 * pos : 查找成功，标记键值所在节点的位序索引号
 * 		 查找失败，标记待插入节点（NULL）的父节点位序索引号
 * tag : 1表示查找成功，0表示查找失败
 * */
typedef struct {
    BTNode *ptr;
    int pos;
    int tag;
}Result;

DiskTree *createDiskBTree();
void releaseDiskBTree(DiskTree *tree);
// 将key值插入到B树
void insertKey(DiskTree *tree, KeyType key);
// 将树中值为key的元素删除
void deleteKey(DiskTree *tree, KeyType key);
// 查找B树中key的位置，分查找成功和失败两种情况，将信息更新到res
void searchBTree(DiskTree *tree, KeyType key, Result *res);
// 打印B树
void printBTree(const BTNode *node, int tab);

#endif //DISKTREE_H
