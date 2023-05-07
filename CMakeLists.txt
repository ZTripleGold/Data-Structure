cmake_minimum_required(VERSION 3.24)
project(Data_Structure C)

set(CMAKE_C_STANDARD 11)

# 控制台中文
IF(WIN32)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fexec-charset=GBK")        # C语言中文
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fexec-charset=GBK")    # C++中文
ENDIF()

# 测试
add_executable(0-1test 00.test/main.c 00.test/common.h 00.test/adjacentList.c 00.test/adjacentList.h 04.Sort/02.SwapSort/bubbleSort.c 04.Sort/02.SwapSort/bubbleSort.h)

# 线性顺序存储表
add_executable(1-1SeqList 01.linear/01.SeqList/seqList.c 01.linear/01.SeqList/seqList.h 01.linear/01.SeqList/main.c)
# 单向链表
add_executable(1-2LinkList 01.linear/02.LinkList/linkList.c 01.linear/02.LinkList/linkList.h 01.linear/02.LinkList/main.c)
# 顺序栈、链式栈
add_executable(1-3Stack 01.linear/03.Stack/arrayStack.c 01.linear/03.Stack/arrayStack.h 01.linear/03.Stack/common.h
                        01.linear/03.Stack/linkStack.c 01.linear/03.Stack/linkStack.h 01.linear/03.Stack/main.c)
# 顺序队列、链式队列
add_executable(1-4Queue 01.linear/04.Queue/arrayQueue.c 01.linear/04.Queue/arrayQueue.h 01.linear/04.Queue/common.h
                        01.linear/04.Queue/linkQueue.c 01.linear/04.Queue/linkQueue.h 01.linear/04.Queue/main.c)



# 二叉树的遍历
add_executable(2-1BinaryTree 02.TreeStruct/01.BinaryTree/arrayQueue.c 02.TreeStruct/01.BinaryTree/arrayQueue.h
                             02.TreeStruct/01.BinaryTree/arrayStack.c 02.TreeStruct/01.BinaryTree/arrayStack.h
                             02.TreeStruct/01.BinaryTree/binaryTree.c 02.TreeStruct/01.BinaryTree/binaryTree.h 02.TreeStruct/01.BinaryTree/main.c)
# 线索二叉树
add_executable(2-2ThreadedTree 02.TreeStruct/02.ThreadedTree/threadedBTree.c 02.TreeStruct/02.ThreadedTree/threadedBTree.h 02.TreeStruct/02.ThreadedTree/main.c)
# 二叉搜索树
add_executable(2-3BinarySearchTree 02.TreeStruct/03.BinarySearchTree/BSearchTree.c 02.TreeStruct/03.BinarySearchTree/BSearchTree.h 02.TreeStruct/03.BinarySearchTree/main.c)
# AVL（平衡）树
add_executable(2-4AVLTree 02.TreeStruct/04.AVLTree/avlTree.c 02.TreeStruct/04.AVLTree/avlTree.h 02.TreeStruct/04.AVLTree/main.c)
# 并查集
add_executable(2-5UnionFindSet 02.TreeStruct/05.UnionFindSet/base.h 02.TreeStruct/05.UnionFindSet/main.c
                               02.TreeStruct/05.UnionFindSet/quickFindSet.c 02.TreeStruct/05.UnionFindSet/quickFindSet.h
                               02.TreeStruct/05.UnionFindSet/quickUnionSet.c 02.TreeStruct/05.UnionFindSet/quickUnionSet.h)
# Huffman树
add_executable(2-6HuffmanTree 02.TreeStruct/06.HuffmanTree/huffmanTree.c 02.TreeStruct/06.HuffmanTree/huffmanTree.h 02.TreeStruct/06.HuffmanTree/main.c)



# 图的邻接矩阵表示
add_executable(3-1MatrixGraph 03.Graph/01.MatrixGraph/matrixGraph.c 03.Graph/01.MatrixGraph/matrixGraph.h 03.Graph/01.MatrixGraph/main.c 03.Graph/common.h)
# 图的邻接表表示
add_executable(3-2AdjacentGraph 03.Graph/02.AdjacentGraph/adjacentGraph.c 03.Graph/02.AdjacentGraph/adjacentGraph.h 03.Graph/common.h 03.Graph/02.AdjacentGraph/main.c)
# 图的十字链表表示
add_executable(3-3CrossLinkGraph 03.Graph/03.CrossLinkGraph/crossLinkGraph.c 03.Graph/03.CrossLinkGraph/crossLinkGraph.h 03.Graph/common.h 03.Graph/03.CrossLinkGraph/main.c)
# 图的邻接多重表表示
add_executable(3-4AdjacencyMultiList 03.Graph/04.AdjacencyMultiList/adjacencyMultiList.c 03.Graph/04.AdjacencyMultiList/adjacencyMultiList.h 03.Graph/04.AdjacencyMultiList/main.c)
# 最小生成树
add_executable(3-5MiniTree 03.Graph/05.MiniTree/Kruskal.c 03.Graph/05.MiniTree/Kruskal.h 03.Graph/05.MiniTree/main.c
                           03.Graph/01.MatrixGraph/matrixGraph.c 03.Graph/01.MatrixGraph/matrixGraph.h
                           03.Graph/05.MiniTree/Prim.c 03.Graph/05.MiniTree/Prim.h)
# 最短路径
add_executable(3-6ShortestPath 03.Graph/06.ShortestPath/DijkstraShortestPath.c 03.Graph/06.ShortestPath/DijkstraShortestPath.h 03.Graph/06.ShortestPath/main.c
                               03.Graph/01.MatrixGraph/matrixGraph.c 03.Graph/01.MatrixGraph/matrixGraph.h)
# 拓扑排序
add_executable(3-7TopologicalSort 03.Graph/07.TopologicalSort/TopologicalSort.c 03.Graph/07.TopologicalSort/TopologicalSort.h 03.Graph/07.TopologicalSort/main.c
                                  03.Graph/02.AdjacentGraph/adjacentGraph.c 03.Graph/02.AdjacentGraph/adjacentGraph.h)
# 关键路径
add_executable(3-8KeyPath 03.Graph/08.KeyPath/KeyPath.c 03.Graph/08.KeyPath/KeyPath.h 03.Graph/08.KeyPath/main.c
                          03.Graph/02.AdjacentGraph/adjacentGraph.c 03.Graph/02.AdjacentGraph/adjacentGraph.h)

# 排序
add_subdirectory(04.Sort)

# 查找
add_subdirectory(05.BaseFind)

# 红黑树
add_subdirectory(06.RBTree)

# B树
add_subdirectory(07.DiskTree)

# 动态规划
add_subdirectory(08.DP)

# KMP算法
add_subdirectory(09.KMP)