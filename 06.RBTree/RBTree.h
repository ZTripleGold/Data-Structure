#ifndef RBTREE_H
#define RBTREE_H
enum RBColors {RED, BLACK};
typedef int keyType;
// 红黑树的节点结构
typedef struct RBNode {
    char color;
    keyType key;
    struct RBNode *left;
    struct RBNode *right;
    struct RBNode *parent;      // 当前节点的父节点
}RBNode;
// 红黑树的树结构
typedef struct {
    RBNode *root;
    int cnt;
}RBTree;

RBTree *createRBTree();

// 向红黑树插入值
void insertRBTree(RBTree *tree, keyType key);
// 删除红黑树的一个节点
void deleteRBTree(RBTree *tree, keyType key);
// 显示红黑树
void printRBTree(RBNode *node, int key, int dir);
// 释放红黑树
void releaseRBTree(RBTree *tree);
// 查找红黑树的节点
RBNode *searchRBNode(RBTree *tree, keyType key);
#endif //RBTREE_H
