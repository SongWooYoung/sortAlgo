#include <iostream>
#include <vector>
#include <cmath>
#include <climits>

using namespace std;

#include "quickSort.cpp"


void Nheapify(vector<int>& heap, size_t i, size_t len) {
    if (i >= heap.size()) return;

    int parent = heap[i];
    int left = (2 * i <= len ? heap[2 * i] : INT_MIN);
    int right = (2 * i + 1 <= len ? heap[2 * i + 1] : INT_MIN);

    if (parent >= left && parent >= right) return;

    if (right < left) {
        swap(heap[i], heap[2 * i]);
        Nheapify(heap, 2 * i, len);
    } else {
        swap(heap[i], heap[2 * i + 1]);
        Nheapify(heap, 2 * i + 1, len);
    }
}

void maxNHeapify(vector<int>& heap, size_t len) {
    for (int i = len / 2; i >= 1; i--) {
        Nheapify(heap, i, len);
    }
}


void HeapSort(vector<int>& array, int left, int right) {
    // 1. 구간 추출 + sentinel
    vector<int> heap;
    heap.push_back(INT_MAX);  // dummy at index 0
    for (int i = left; i <= right; i++) {
        heap.push_back(array[i]);
    }

    int len = right - left + 1;

    // 2. maxNHeapify
    maxNHeapify(heap, len);

    // 3. 정렬 수행
    for (int i = len; i > 1; i--) {
        swap(heap[1], heap[i]);
        Nheapify(heap, 1, i - 1);
    }

    // 4. 정렬된 결과 복사 back
    for (int i = 0; i < len; i++) {
        array[left + i] = heap[i + 1];  // skip heap[0]
    }
}

void InsertionSort(vector<int>& array, int left, int right) {
    for (int i = left + 1; i <= right; i++) {
        int key = array[i];
        int j = i - 1;

        while (j >= left && array[j] > key) {
            array[j + 1] = array[j];
            j--;
        }
        array[j + 1] = key;
    }
}

// 내 함수들이 depth 인자를 안받는게 문제, 재구성 할까, 아니면 어떻게 우회할 수 있지 않을까
// 
void introSort(vector<int>& array, int left, int right, int maxDepth) {
    int len = right - left + 1;
    if (len <= 10)  {
        InsertionSort(array,left,right); //Sedgewick, R. (1978). Implementing quicksort programs. -> 10 has higher ability
        return;
    }
    if(maxDepth == 0) {
        HeapSort(array,left,right);
        return;
    }

    int pivot = partition(array, left, right); 
    introSort(array, left, pivot, maxDepth - 1);
    introSort(array, pivot + 1, right, maxDepth - 1);
} 

void intro_wrapper(vector<int>& array) {
    int maxDepth = 2 * log2(array.size());
    introSort(array, 0, array.size() - 1, maxDepth);
}

#include "Eval.h"

int main(int argc, char** argv) {
    return runEvaluation("introSort", argc, argv, intro_wrapper);
}

/*
==================== introSort Evaluation ====================
ListType       Iter    Time (avg ms)    Memory (avg KB)   Valid     
--------------------------------------------------------------------
ascending      3       39.67            7677.33           ✔️    
descending     3       47.33            7752.00           ✔️    
partial        3       150.00           7752.00           ✔️    
random         3       229.00           7752.00           ✔️    
====================================================================
Results saved to: result/2025-04-05_introSort_1000000.csv
*/