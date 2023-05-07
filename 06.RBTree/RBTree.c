#include <stdio.h>
#include <stdlib.h>
#include "RBTree.h"

RBTree *createRBTree() {
    RBTree *tree = (RBTree*) malloc(sizeof(RBTree));
    if (tree == NULL) {
        printf("fail to malloc!\n");
        return NULL;
    }
    tree->root = NULL;
    tree->cnt = 0;
    return tree;
}

/* 将x进行左旋，将左、右、父节点进行更新
 *      px                              px
 *     /                               /
 *    x                               y
 *   /  \      --(左旋)-->           / \
 *  lx   y                          x  ry
 *     /   \                       /  \
 *    ly   ry                     lx  ly
*/
static void leftRotate(RBTree *tree, RBNode *x) {
    RBNode *y = x->right;   // 备份y
    // 将ly连接到x的右孩子，更新其父节点
    x->right = y->left;
    if (y->left) {
        y->left->parent = x;
    }
    // 更新左旋后x,y的父节点关系
    y->parent = x->parent;
    if (x->parent) {
        if (x->parent->left == x) {
            x->parent->left = y;
        }
        else {
            x->parent->right = y;
        }
    }
    else {  // 父节点不存在，表明当前节点是根节点
        tree->root = y;
    }
    // 更新x,y关系
    y->left = x;
    x->parent = y;
}

/* 将y进行左旋，将左、右、父节点进行更新
 *           py                               py
 *           /                                /
 *          y                                x
 *         /  \      --(右旋)-->            /  \
 *        x   ry                           lx   y
 *       / \                                   / \
 *      lx  rx                                rx  ry
 * */
static void rightRotate(RBTree *tree, RBNode *y) {
    RBNode *x = y->left;
    y->left = x->right;
    if (x->right) {
        x->right->parent = y;
    }
    x->parent = y->parent;
    if (y->parent) {
        if (y->parent->left == y) {
            y->parent->left = x;
        }
        else {
            y->parent->right = x;
        }
    }
    else {
        tree->root = x;
    }
    x->right = y;
    y->parent = x;
}

// 创建红节点
static RBNode *createRBNode(keyType key) {
    RBNode *node = (RBNode*) malloc(sizeof(RBNode));
    if (node == NULL) {
        printf("fail to malloc!\n");
        return NULL;
    }
    node->left = node->right = node->parent = NULL;
    node->color = RED;  // 初始都为红节点
    node->key = key;
    return node;
}

// 修正红黑树
/* 1. 插入节点，如果父节点是黑色的，那么就不用调整
 * 2. 如果父节点是红色，就出现红红现象
 * 2.1 叔叔节点是红色：
 * 		重新调整颜色（g->红，p->黑，u->黑），g节点当做新节点，再次循环判断
 * 2.2 叔叔节点是黑色：
 * 		2.2.1 cur是左孩子，par是左孩子
 * 			g右旋，g->红，p->黑
 * 		2.2.2 cur是右孩子，par是右孩子
 * 			g左旋，g->红，p->黑
 * 		2.2.3 cur是右孩子，par是左孩子
 * 			p左旋，cur和par交换，然后重复2.2.1
 * 		2.2.4 cur是左孩子，par是右孩子
 * 			p右旋，cur和par交换，然后重复2.2.2
 * */
static void insertFixUp(RBTree *tree, RBNode *node) {
    RBNode *parent, *grandPa, *uncle;       // 父节点，祖父节点，叔叔节点
    RBNode *temp;

    parent = node->parent;
    while (parent && parent->color == RED) {    // 父节点存在，且父节点是红节点（即红红节点的情况）
        // 根据祖父节点找到叔叔节点
        grandPa = parent->parent;
        if (grandPa->left == parent) {
            uncle = grandPa->right;
        }
        else {
            uncle = grandPa->left;
        }
        if (uncle && uncle->color == RED) {     // 叔叔节点存在，且是红节点的情况
            parent->color = BLACK;
            uncle->color = BLACK;
            grandPa->color = RED;
            node = grandPa;     // 因为将祖父节点置为红节点，将祖父节点看作插入的新节点再次循环
            parent = node->parent;
            continue;
        }
        // 叔叔节点不存在，或者叔叔节点为黑节点的情况
        if (grandPa->left == parent) {          // L
            if (parent->right == node) {        // R
                // 左旋为LL的情况
                leftRotate(tree, parent);
                // 交换node指针和parent指针的指向
                temp = node;
                node = parent;
                parent = temp;
            }
            // 处理LL的情况
            rightRotate(tree, grandPa);
            parent->color = BLACK;
            grandPa->color = RED;
        }
        else {                                  // R
            if (parent->left == node) {         // L
                rightRotate(tree, parent);
                temp = node;
                node = parent;
                parent = temp;
            }
            // RR
            leftRotate(tree, grandPa);
            parent->color = BLACK;
            grandPa->color = RED;
        }
    }
    // 可能在修正红黑树的过程中将根节点变为红节点，因此在此处统一重新置根节点为黑节点
    tree->root->color = BLACK;
}

// 插入节点
void insertRBTree(RBTree *tree, keyType key) {
    // 1.创建红节点（创建的新节点都是红节点，避免出现黑高不一样的情况）
    RBNode *node = createRBNode(key);
    // 2.根据二叉搜索树的规则找到要插入的位置
    RBNode *cur = tree->root;
    RBNode *pre = NULL;
    while (cur) {
        pre = cur;      // 小弟跟着大哥
        if (key < cur->key) {
            cur = cur->left;
        }
        else if (key > cur->key) {
            cur = cur->right;
        }
        else {      // 树中节点已经与插入值相等
            printf("Key: %d has existed!\n", key);
            return;
        }
    }
    // 3.若插入的位置是根节点，更新tree->root；反之插入红黑树
    node->parent = pre;     //  不论是否是根节点，都可以先给父节点赋值
    if (pre) {      // pre存在，说明树不为空，插入位置不是根节点
        if (key < pre->key) {
            pre->left = node;
        }
        else {
            pre->right = node;
        }
    }
    else {
        tree->root = node;
        tree->root->color = BLACK;
        tree->cnt++;
        return;     // 插入根节点无需修正红黑树，直接返回
    }
    // 4.修正红黑树（即处理红红节点的情况）
    insertFixUp(tree, node);
    tree->cnt++;
}

// 显示红黑树，先序遍历
void printRBTree(RBNode *node, int key, int dir) {
    if (node) {
        if (dir == 0) {     // 根节点的情况
            printf("%d[%c] is root\n", node->key, (node->color == RED)? 'R': 'B');
        }
        else {
            printf("%d[%c] is %d's %s\n", node->key, (node->color == RED) ? 'R' : 'B',
                   key, (dir == 1) ? "right child" : "left child");
        }
        printRBTree(node->left, node->key, -1);
        printRBTree(node->right, node->key, 1);
    }
}

static void freeNode(RBTree *tree, RBNode *node) {
    if (node) {
        freeNode(tree, node->left);
        freeNode(tree, node->right);
        tree->cnt--;
        free(node);
    }
}

// 释放红黑树，后序遍历
void releaseRBTree(RBTree *tree) {
    if (tree) {
        freeNode(tree, tree->root);
        free(tree);
    }
}

static void deleteFixUp(RBTree *tree, RBNode *x, RBNode *parent) {
    RBNode *w;  // 要删除节点的兄弟节点，主要就是分析该节点
    while ((tree->root != x) && (x == NULL || x->color == BLACK)) {
        // 当要删除的节点为根节点时，即是树中只有一个节点或者没有节点的情况，无需再调整
        // 当要删除的节点不为空且节点颜色为红色时，也无需再调整
        if (parent->left == x) {    // x是父节点的左孩子
            w = parent->right;      // 那么兄弟节点就是父节点的右孩子，即是  R
            if (w->color == RED) {
                // case1 兄弟节点w是红色节点，将其转换为黑色节点的情况处理
                w->color = BLACK;
                parent->color = RED;
                leftRotate(tree, parent);
                w = parent->right;
            }
            // 兄弟节点的孩子都是黑色节点
            if ((!w->left && w->left->color == BLACK) && (!w->right && w->right->color == BLACK)) {
                /* 兄弟节点孩子不存在，或者孩子为黑节点
                * case2 x的兄弟的两个孩子都是黑色
                * 递归，把双黑节点的兄弟变为红，修正当前节点为父节点，即将父节点看作双黑节点进行判断
                */
                w->color = RED;
                x = parent;
                parent = x->parent;
            }
            else {  // 兄弟节点的孩子至少有一个红节点
                if (!w->right || w->right->color == BLACK) {    // RL
                    // case3 x的兄弟节点左孩子为红色，右孩子为黑色
                    w->color = RED;
                    w->left->color = BLACK;
                    rightRotate(tree, w);
                    w = parent->right;
                }
                // case4 RR
                w->color = parent->color;
                w->right->color = BLACK;
                parent->color = BLACK;
                leftRotate(tree, parent);
                break;  // 处理完RR的情况就满足红黑树的性质，可以退出循环
            }
        }
        else {      // x是父节点的右孩子
            w = parent->left;       // L
            if (w->color == RED) {
                w->color = BLACK;
                parent->color = RED;
                rightRotate(tree, parent);
                w = parent->left;
            }
            if ((!w->left || w->left->color == BLACK) && (!w->right || w->right->color == BLACK)) {
                w->color = RED;
                x = parent;
                parent = x->parent;
            }
            else {
                if (!w->left || w->left->color == BLACK) {    // LR
                    w->color = RED;
                    w->right->color = BLACK;
                    leftRotate(tree, w);
                    w = parent->left;
                }
                // LL
                w->color = parent->color;
                parent->color = BLACK;
                w->left->color = BLACK;
                rightRotate(tree, parent);
                break;
            }
        }
    }
    // 最后将根节点的颜色置为黑色，防止出现一系列变换将根节点颜色变为红色的情况
    if (tree->root) {
        tree->root->color = BLACK;
    }
}

static void deleteRBNode(RBTree *tree, RBNode *node) {
    RBNode *y;      // 真正删除的节点地址
    RBNode *x;      // 替换节点
    RBNode *parent; // 备份y的父节点，以免删除y时找不到y的父节点
    if (node->left == NULL || node->right == NULL) {    // 有一个孩子或者没有孩子，即度为1或者度为0
        // 只处理度为1和0的情况，如果删除的节点度为2，就将其转换为度为1或0的情况
        y = node;       // 此时node位置就是要删除的节点位置
    }
    else {      // 将度为2的情况转换为度为1或0的情况
        // 与AVL树类似，找到前驱或后继节点，这里找后继节点即右节点的最左边
        y = node->right;
        while (y->left) {
            y = y->left;
        }
    }
    // 此时找到真正删除的节点，接下来寻找替换节点
    if (y->left) {  // 这里的y节点经过上面的转换，必然是度为1或者0的情况
        x = y->left;
    }
    else {
        x = y->right;
    }
    parent = y->parent;     // 备份y的父节点
    // 处理删除节点后的连接关系
    if (x) {    // x存在，即是删除节点度为1的情况
        x->parent = parent;
    }
    if (y->parent == NULL) {    // 父节点为空，即是y是根节点
        tree->root = x;
    }
    else if (y->parent->left == y) {    // y在其父节点的左边
        y->parent->left = x;
    }
    else {
        y->parent->right = x;
    }
    // 更新有左右孩子的节点的值
    if (y != node) {    // y不等于node，说明是由度为2的节点转换而来，将值交换
        node->key = y->key;
    }
    /* 度为1的节点由两种情况：红黑 黑红
     * 不可能出现黑黑的情况（黑高会不等）
     * 红黑直接替换即可，黑红则需要调整
     * 度为0的节点，红直接删除，黑需要调整
     * */
    // 如果删除的节点是黑色节点，那么需要调整，需要分为多种情况
    if (y->color == BLACK) {
        deleteFixUp(tree, x, parent);
    }
    // 调整完或者删除节点为红色节点，无需其他操作，直接释放
    free(y);
}

// 删除红黑树的一个节点
void deleteRBTree(RBTree *tree, keyType key) {
    RBNode *node = searchRBNode(tree, key);
    if (node == NULL) return;
    deleteRBNode(tree, node);
}

// 查找红黑树的节点
RBNode *searchRBNode(RBTree *tree, keyType key) {
    RBNode *node = tree->root;
    while (node) {
        if (key < node->key) {
            node = node->left;
        }
        else if (key > node->key) {
            node = node->right;
        }
        else {
            return node;
        }
    }
    return NULL;
}