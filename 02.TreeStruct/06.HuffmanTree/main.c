#include <stdio.h>
#include "huffmanTree.h"

int main() {
	int w[] = {5, 29, 7, 8,
			   14, 23, 3, 11};
	char show[] = {'A', 'B', 'C', 'D',
				   'E', 'F', 'G', 'H'};
	HuffmanTree tree = createHuffmanTree(w, sizeof(w) / sizeof(w[0]));
	// if (tree) {
	// 	for (int i = 1; i <= 15; ++i) {
	// 		printf("%d %d %d %d %d\n", i, tree[i].weight, tree[i].parent,
	// 			   tree[i].lChild, tree[i].rChild);
	// 	}
	// }
	HuffmanCode *code = createHuffmanCode(tree, sizeof(w) / sizeof(w[0]));
	for (int i = 0; i < sizeof(w) / sizeof(w[0]); ++i) {
		printf("%c: %s\n", show[i], code[i]);
	}
	releaseHuffmanCode(code, sizeof(w) / sizeof(w[0]));
	releaseHuffmanTree(tree);
	return 0;
}