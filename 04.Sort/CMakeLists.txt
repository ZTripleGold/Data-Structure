# 插入排序、希尔排序
add_executable(4-1InsertSort 01.InsertSort/insertSort.c 01.InsertSort/insertSort.h 01.InsertSort/main.c
        sortHelper.c sortHelper.h 03.HeapSort/main.c)
# 交换排序、快速排序
add_executable(4-2SwapSort 02.SwapSort/bubbleSort.c 02.SwapSort/bubbleSort.h 02.SwapSort/main.c
        02.SwapSort/quickSort.c 02.SwapSort/quickSort.h sortHelper.c sortHelper.h)
# 堆排序
add_executable(4-3HeapSort 03.HeapSort/miniHeap.c 03.HeapSort/miniHeap.h 03.HeapSort/main.c sortHelper.c sortHelper.h
                           03.HeapSort/heapSort.c 03.HeapSort/heapSort.h)
# 归并排序
add_executable(4-4MergeSort 04.MergeSort/mergeSort.c 04.MergeSort/mergeSort.h 04.MergeSort/main.c
                            sortHelper.c sortHelper.h)
