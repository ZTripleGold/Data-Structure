#include "RBTree.h"

int main() {
    RBTree *tree = createRBTree();
    int data[] = {55, 49, 65, 69, 75, 57,63, 56};
    for (int i = 0; i < sizeof(data) / sizeof(data[0]); ++i) {
        insertRBTree(tree, data[i]);
    }
    deleteRBTree(tree, 49);
    printRBTree(tree->root, tree->root->key, 0);
    releaseRBTree(tree);

    return 0;
}