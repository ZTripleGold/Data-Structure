#include "diskTree.h"

int main() {
    DiskTree *tree = createDiskBTree();

    insertKey(tree, 8);
    insertKey(tree, 9);
    insertKey(tree, 10);
    insertKey(tree, 11);
    insertKey(tree, 15);
    insertKey(tree, 16);
    insertKey(tree, 17);
    insertKey(tree, 18);
    insertKey(tree, 20);
    insertKey(tree, 23);

    printBTree(tree->root, 1);

    printf("========================\n");
    deleteKey(tree, 15);
    printBTree(tree->root, 1);
    releaseDiskBTree(tree);

    releaseDiskBTree(tree);

    return 0;
}