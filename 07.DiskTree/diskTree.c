#include <string.h>
#include "diskTree.h"

// 初始化B树
DiskTree *createDiskBTree() {
    DiskTree *tree = (DiskTree*) malloc(sizeof(DiskTree));
    if (tree == NULL) {
        printf("fail to malloc!\n");
        return NULL;
    }
    tree->root = NULL;
    tree->cnt = 0;
    return tree;
}

// 释放B树
static void releaseBTNode(DiskTree *tree, BTNode *node) {
    // 类似图的释放
    if (node) {
        for (int i = 0; i <= node->num; ++i) {
            releaseBTNode(tree, node->ptr[i]);
        }
        free(node);
    }
}

void releaseDiskBTree(DiskTree *tree) {
    if (tree) {
        releaseBTNode(tree, tree->root);
        free(tree);
    }
}

// 从节点中搜索符合条件的key的位序
static int searchNodePos(BTNode *node, KeyType key) {
    int i = 1;      // 0号位置无效，从1号索引开始搜索
    while (i <= node->num && key > node->key[i]) {
        // 当i小于等于节点中的元素个数，并且i对应的元素值小于key继续循环
        i++;
    }
    /* B树的阶3，说明最大有3棵子树，那么节点最大键值2
    * 在插入节点时，当键值为3时，才会触发分离，申请的时候多申请一个
    * | k0 | k1 | k2 | k3 |		k0是无效的  k3为了防止越界
    * | p0 | p1 | p2 | p3 |		p0 < k1   k1 < p1 < k2  p2 > k2  p3是不访问
    * */
    /* 当循环退出时有两种情况，可同上面的图理解
     * 1.  key <= node->key[i] 此时若是小于，下一节点位置为小于key[i]的节点，即 i - 1
     * 2. i > node->num 此时i越界，且key比该节点中所有元素都大，下一节点位置是最大节点的最右边子树，即 i - 1
     */
    return i;   // 因此外面的下一节点位置 pos = i - 1
}

/* 从节点node的pos处，插入key
 * 若是上移，child就非空，（将中间的元素上移，其右边的子树需要连接上，即child非空）
 * 在叶子节点插入，child就为null
 * */
static void insertNode(BTNode *node, int pos, KeyType key, BTNode *child) {
    // 将pos及pos后的元素后移一位，最后再更新pos位置的值
    int i;
    int n = node->num;
    for (i = n; i >= pos; --i) {
        node->key[i + 1] = node->key[i];
        node->ptr[i + 1] = node->ptr[i];
    }
    node->key[pos] = key;
    node->ptr[pos] = child;
    if (child) {    // 如果child存在，更新其父节点的连接
        child->parent = node;
    }
    node->num++;
}

// 创建一个根节点
BTNode *createRootNode(KeyType key, BTNode *p0, BTNode *p1) {
    // 根节点的左右子树可能不为空
    BTNode *node = (BTNode*) malloc(sizeof(BTNode));
    if (node == NULL) {
        printf("fail to malloc!\n");
        return NULL;
    }
    node->key[1] = key;
    node->num = 1;
    node->ptr[0] = p0;
    node->ptr[1] = p1;
    // 如果子树不为空，更新父节点
    if (p0) {
        p0->parent = node;
    }
    if (p1) {
        p1->parent = node;
    }
    node->parent = NULL;
    return node;
}

// ******************* B树的插入 *******************//

/* 将node节点分裂成为两个节点，前一半保留在原节点，后一半移动到other节点
 * 1. 申请新节点，将后半部分信息拷贝到新节点上
 * 2. 新申请的节点的子节点也更新
 * */
static void split(BTNode **node, int s, BTNode **other) {
    int i = s + 1;      // node节点的搬移位置
    int j = 1;          // 新节点的放入位置
    int n = (*node)->num;
    BTNode *splitNode = (BTNode*) malloc(sizeof(BTNode));
    if (splitNode == NULL) {
        printf("fail to malloc!\n");
        return;
    }
    memset(splitNode, 0, sizeof(BTNode));
    *other = splitNode;     // 将splitNode的地址给*other
    // s + 1位置的节点左边子树需要连接，key从1开始，而ptr从0开始
    splitNode->ptr[0] = (*node)->ptr[s];
    for (; i <= n; ++i, ++j) {
        splitNode->key[j] = (*node)->key[i];
        splitNode->ptr[j] = (*node)->ptr[i];
        (*node)->key[i] = 0;
        (*node)->ptr[i] = NULL;
    }
    splitNode->num = MaxOrder - s;
    splitNode->parent = (*node)->parent;
    // 更新子树的父节点
    for (int k = 0; k <= n - s; ++k) {
        if (splitNode->ptr[k]) {
            splitNode->ptr[k]->parent = splitNode;
        }
    }
    (*node)->num = s - 1;
}
// 根据找到的待插入位置插入元素，再根据B树的规则来判断是否需要分离
static void insertBTree(DiskTree *tree, KeyType key, BTNode *node, int pos) {
    int mid;
    BTNode *child = NULL;
    KeyType x = key;
    int finish = 0;             // 判断是否需要分离
    int needNewRoot = 0;        // 可能出现分离根节点的特殊情况
    if (node) {     // 有父节点，要么直接插入，要么进行分离
        // 节点分离后，父节点中的元素增多，需要循环判断
        while (!finish && !needNewRoot) {
            insertNode(node, pos, x, child);
            if (node->num < MaxOrder) {     // 当节点中元素小于阶数时，不用分离
                finish = 1;
            }
            else {      // 超过了最大的有效位置，分离节点
                mid = (MaxOrder + 1) / 2;
                x = node->key[mid];     // 更新x以便下次循环
                split(&node, mid, &child);
                // 更新指针指向，再次循环
                if (node->parent) {     // 分离节点不是根节点
                    node = node->parent;
                    // 此时中间元素还没有插入，需找到在父节点的插入位置
                    pos = searchNodePos(node, x);
                }
                else {  // 需要分离还是根节点，需要特殊处理，根节点没有父节点，也不用再循环直接退出
                    needNewRoot = 1;
                }
            }
        }
    }
    else {      // 没有父节点，B树是空树，要插入的节点是根节点
        tree->root = createRootNode(key, NULL, NULL);
        tree->cnt = 1;
    }
    if (needNewRoot) {  // 分离根节点
        tree->root = createRootNode(x, node, child);
    }
}

// 将key值插入到B树
void insertKey(DiskTree *tree, KeyType key) {
    Result res;
    // 1. 查找key在B树中的待插入位置
    searchBTree(tree, key, &res);
    if (res.tag == 1) {     // tag == 1表明查找成功，B树中已经有key值
        printf("key %d has existed!\n", key);
    }
    else {      // 反之没有找到，根据返回的待插入位置插入元素
        // ptr为待插入位置的父节点，因为待插入位置是空，然后根据pos来插入
        insertBTree(tree, key, res.ptr, res.pos);
        tree->cnt++;
    }
}

// ================================================
static void restoreBTree(DiskTree *tree, BTNode *node);
// 向兄弟节点借关键字
static void borrowFromBrother(BTNode *node, BTNode *leftBrother, BTNode *rightBrother, BTNode *parent, int pos) {
    if (leftBrother && leftBrother->num >= ((MaxOrder + 1) / 2)) {
        for (int i = node->num; i > 0; --i) {
            // 关键字和指针后移，腾出第一个位置
            if (i > 1) {
                node->key[i] = node->key[i - 1];
            }
            node->ptr[i] = node->ptr[i - 1];
        }
        node->ptr[0] = leftBrother->ptr[leftBrother->num];
        if (node->ptr[0]) {
            node->ptr[0]->parent = node;
        }
        leftBrother->ptr[leftBrother->num] = NULL;
        node->key[1] = parent->key[pos];
        parent->key[pos] = leftBrother->key[leftBrother->num];
        leftBrother->num--;
        node->num++;
    }
    else if (rightBrother && rightBrother->num >= ((MaxOrder + 1) / 2)) {
        node->key[node->num + 1] = parent->key[pos + 1];
        node->ptr[node->num + 1] = rightBrother->ptr[0];
        if (node->ptr[node->num + 1]) {
            node->ptr[node->num + 1]->parent = node;
        }
        node->num++;
        parent->key[pos + 1] = rightBrother->key[1];
        for (int i = 0; i < rightBrother->num; ++i) {
            if (i > 0) {
                rightBrother->key[i] = rightBrother->key[i + 1];
            }
            rightBrother->ptr[i] = rightBrother->ptr[i + 1];
        }
        rightBrother->ptr[rightBrother->num] = NULL;
        rightBrother->num--;
    }
}

// 与左兄弟合并
static void mergerWithLeftBrother(BTNode *leftBrother, BTNode *parent, BTNode *node, DiskTree *tree, int pos) {
    // 与左兄弟合并
    leftBrother->key[leftBrother->num + 1] = parent->key[pos];  // 从父节点拿下分割本节点与左兄弟的关键字
    leftBrother->ptr[leftBrother->num + 1] = node->ptr[0];
    if (leftBrother->ptr[leftBrother->num + 1]) {
        // 给左兄弟的节点，当此节点存在时，需要把其父亲指向左节点
        leftBrother->ptr[leftBrother->num + 1]->parent = leftBrother;
    }
    leftBrother->num++;     // 左兄弟关键字加1
    for (int i = 1; i <= node->num; ++i) {
        // 把本节点的关键字和子树指针赋给左兄弟
        leftBrother->key[leftBrother->num + i] = node->key[i];
        leftBrother->ptr[leftBrother->num + i] = node->ptr[i];
        if (leftBrother->ptr[leftBrother->num + i]) {
            leftBrother->ptr[leftBrother->num + i]->parent = leftBrother;
        }
    }
    leftBrother->num += node->num;
    parent->ptr[pos] = NULL;
    free(node);
    for (int i = pos; i < parent->num; ++i) {   // 父节点下去一个，需要将后面的节点左移
        parent->key[i] = parent->key[i + 1];
        parent->ptr[i] = parent->ptr[i + 1];
    }
    parent->ptr[parent->num] = NULL;
    parent->num--;      // 父节点关键字个数减1
    if (tree->root == parent) {
        // 如果此时父节点为根，则当父节点没有关键字时才调整
        if (parent->num == 0) {
            for (int i = 0; i <= parent->num + 1; ++i) {
                if (parent->ptr[i]) {
                    tree->root = parent->ptr[i];
                    break;
                }
            }
            tree->root->parent = NULL;
        }
    }
    else {
        // 如果父节点不为根，则需要判断是否需要重新调整
        if (parent->num < ((MaxOrder - 1) / 2)) {
            restoreBTree(tree, parent);
        }
    }
}

/* 与右兄弟合并 */
static void mergerWithRightBrother(BTNode *rightBrother, BTNode *parent, BTNode *node, DiskTree *tree, int pos) {
    for (int i = rightBrother->num; i > 0; --i) {
        if (i > 0) {
            rightBrother->key[i + 1 + node->num] = rightBrother->key[i];
        }
        rightBrother->ptr[i + 1 + node->num] = rightBrother->ptr[i];
    }
    rightBrother->key[node->num + 1] = parent->key[pos + 1];     // 把父节点分割两个本兄弟和右兄弟的关键字拿下来使用
    for (int i = 0; i <= node->num; ++i) {
        // 把本结点的关键字及子树指针移动到右兄弟中去
        if (i > 0) {
            rightBrother->key[i] = node->key[i];
        }
        rightBrother->ptr[i] = node->ptr[i];
        if (rightBrother->ptr[i]) {
            rightBrother->ptr[i]->parent = rightBrother;        // 给右兄弟的节点需要把其父节点指向右兄弟
        }
    }
    rightBrother->num += (node->num + 1);
    parent->ptr[pos] = NULL;
    free(node);
    for (int i = pos; i < parent->num; ++i) {
        if (i > pos) {
            parent->key[i] = parent->key[i + 1];
        }
        parent->ptr[i] = parent->ptr[i + 1];
    }
    if (parent->num == 1) {
        // 如果父结点在关键字减少之前只有一个结点，那么需要把父结点的右孩子赋值给左孩子
        parent->ptr[0] = parent->ptr[1];
    }
    parent->ptr[parent->num] = NULL;
    parent->num--;           // 父节点关键字数减1
    if (tree->root == parent) {
        //如果此时父结点为根，则当父结点没有关键字时才调整
        if (parent->num == 0) {
            for (int i = 0; i <= parent->num; ++i) {
                if (parent->ptr[i]) {
                    tree->root = parent->ptr[i];
                    break;
                }
            }
            tree->root->parent = NULL;
        }
    } else {
        // 如果父结点不为根，则需要判断是否需要重新调整
        if (parent->num < ((MaxOrder - 1) / 2)) {
            restoreBTree(tree, parent);
        }
    }
}

// 调整B树
static void restoreBTree(DiskTree *tree, BTNode *node) {
    BTNode *parent, *leftBrother, *rightBrother;
    parent = node->parent;
    if (parent) {       // 不为根节点
        // 寻找左右兄弟
        int i;
        for (i = 0; i <= parent->num; ++i) {
            if (parent->ptr[i] == node) {
                break;
            }
        }
        // 给左右兄弟赋值
        if (i > 0) {
            leftBrother = parent->ptr[i - 1];
        }
        else {
            leftBrother = NULL;
        }
        if (i < parent->num) {
            rightBrother = parent->ptr[i + 1];
        }
        else {
            rightBrother = NULL;
        }
        // 左兄弟或有兄弟有富余的关键字（可以再拆分）
        if ((leftBrother && leftBrother->num >= (MaxOrder + 1) / 2) ||
             (rightBrother && rightBrother->num >= (MaxOrder + 1) / 2)) {       // MaxOrder = 3， 即 >= 2
            borrowFromBrother(node, leftBrother, rightBrother, parent, i);
        }
        // 左右兄弟都没有富余的关键字，需要合并
        else {
            if (leftBrother) {
                // 与左兄弟合并
                mergerWithLeftBrother(leftBrother, parent, node, tree, i);
            }
            else if (rightBrother) {
                // 与右兄弟合并
                mergerWithRightBrother(rightBrother, parent, node, tree, i);
            }
            else {
                // 左右子树都不存在，改变根节点
                for (int j = 0; j < node->num; ++j) {
                    if (node->ptr[j]) {
                        tree->root = node->ptr[j];
                        break;
                    }
                }
                tree->root->parent = NULL;
            }
        }
    }
    else {  // 为根节点
        BTNode *a;
        for (int i = 0; i <= node->num; ++i) {
            if (node->ptr[i]) {
                a = node;
                node = node->ptr[i];
                a->ptr[i] = NULL;
                free(a);
                break;
            }
        }
        tree->root = node;
        tree->root->parent = NULL;
    }
}

// 找到node节点的后继节点，交换key值，把这个节点通过node反馈给上层
static void successor(BTNode **node, int pos) {
    // 寻找当前节点的后继节点
    BTNode *leaf = *node;
    if (leaf == NULL) {
        return;
    }
    leaf = leaf->ptr[pos];
    while (leaf->ptr[0]) {
        leaf = leaf->ptr[0];
    }
    (*node)->key[pos] = leaf->key[1];
    (*node) = leaf;
}

// 从节点node的pos位序中移除关键字key
static void removeNode(BTNode *node, int pos) {
    for (int i = pos; i < node->num; ++i) {
        node->key[i] = node->key[i + 1];
        node->ptr[i] = node->ptr[i + 1];
    }
    node->num--;
}

// 删除节点
static void deleteNode(DiskTree *tree, BTNode *node, int pos) {
    // 不为空，为内部节点，将删除内部节点的问题转换为删除叶子节点
    if (node->ptr[pos]) {
        successor(&node, pos);
        deleteNode(tree, node, 1);
    }
    // 为空说明是叶子节点（B树的叶子节点都在最后一层即同一层）
    else {
        // 从node节点中删除pos
        removeNode(node, pos);
        // 当节点中元素少于一定数量，就需要调整B树
        if (node->num <= ((MaxOrder - 1) / 2)) {    // MaxOrder = 3 即 <= 2
            // 调整B树
            restoreBTree(tree, node);
        }
    }
}

/* B树的删除
 * 1. 找到节点
 * 2. 判断节点是否是叶子节点，如果不是，找后继(前驱)节点，替换节点后，转为删除这个前驱或后继节点(叶子节点)
 * 3. 最终都是删除这个叶子节点
 * 3.1 删除这个节点里的元素后，该节点的m是否小于临界值（m/2），如果不小于，成功返回
 * 3.2 先找兄弟，看兄弟的节点的m值是否有多余，有多余，借（借的人变父，原父下沉）
 * 3.3 兄弟没有结余，和父节点进行合并，重新再判断新的父节点关系
 * */
void deleteKey(DiskTree *tree, KeyType key) {
    Result res;
    // 查找key在B树中的位置
    searchBTree(tree, key, &res);
    if (res.tag == 1) {     // 删除元素，只有找到才做处理
        deleteNode(tree, res.ptr, res.pos);
        tree->cnt--;
    }
    else {      // 在B树中找不到该元素
        printf("the key %d don't exist", key);
    }
}

// ***************** B树的辅助函数 *********************//

// 查找B树中key的位置，分查找成功和失败两种情况，将信息更新到res
void searchBTree(DiskTree *tree, KeyType key, Result *res) {
    BTNode *cur = tree->root;       // 定义当前节点索引，大哥
    BTNode *pre = NULL;             // 定义当前节点父节点的索引，小弟
    int pos;
    int tag = 0;                    // 用于标记是否查找成功
    while (cur && !tag) {
        // 遍历当前节点中的所有key值，确定是否在这个节点上
        // 如果不在这个节点上，还要标记出下一个节点的位置
        pos = searchNodePos(cur, key);
        if (pos <= cur->num && cur->key[pos] == key) {      // 说明找到了
            tag = 1;
        }
        else {      // 没有找到，标记出下一个节点的位置
            pre = cur;
            cur = pre->ptr[pos - 1];    // 经函数searchNodePos分析，下一节点位置为 pos - 1
        }
    }
    // 更新res
    if (tag) {  // 查找成功
        res->tag = 1;
        res->ptr = cur;
        res->pos = pos;
    }
    else {     // 查找失败，说明cur为空，树中找不到该元素值key，把父节点信息更新
        res->tag = 0;
        res->ptr = pre;
        res->pos = pos;
    }
}

// 打印B树
void printBTree(const BTNode *node, int tab) {
    if (node == NULL) {
        return;
    }
    int i;
    for (i = 0; i <= tab; i++) {
        printf("    ");
    }
    for (i = 1; i <= node->num; i++) {
        printf("%d", node->key[i]);
        if (i != node->num) {
            printf(", ");
        }
    }
    printf("\n");
    for (i = 0; i <= node->num; i++) {
        printBTree(node->ptr[i], tab + 1);
    }
}