#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int binarySearch(const vector<int>& array, int key, int start, int end) {
    while (start <= end) {
        int mid = (start + end) / 2;
        if (array[mid] > key)
            end = mid - 1;
        else
            start = mid + 1;
    }
    return start; // insertion point
}

void insertionSort(vector<int>& array) {
    int len = (int) array.size();
    if (len == 0) return;

    for (int i = 1; i < len; i++) {
        int key = array[i];
        int j = i - 1;

        // 정렬된 부분 배열에서 key보다 큰 원소를 오른쪽으로 밀기
        while (j >= 0 && array[j] > key) {
            array[j + 1] = array[j];
            j--;
        }
        array[j + 1] = key;
    }
}


void binaryInsertionSort(vector<int>& array) {
    int len = array.size();
    const int THRESHOLD = 32;

    for (int i = 1; i < len; i++) {
        int key = array[i];
        int j = i - 1;
        int insertPos;

        if (i < THRESHOLD) {
            // Regular insertion sort for first 10 elements
            while (j >= 0 && array[j] > key) {
                array[j + 1] = array[j];
                j--;
            }
            insertPos = j + 1;
        } else {
            // Binary search insertion from 10th element onward
            insertPos = binarySearch(array, key, 0, i - 1);
            for (j = i - 1; j >= insertPos; j--) {
                array[j + 1] = array[j];
            }
        }
        array[insertPos] = key;
    }
}

#include "Eval.h"
int main(int argc, char** argv) {
    return runEvaluation("biSort", argc, argv, binaryInsertionSort);  // ✨ 원하는 정렬 이름만 전달
}

/*
==================== biSort Evaluation ====================
ListType       Iter    Time (avg ms)    Memory (avg KB)   Valid     
--------------------------------------------------------------------
ascending      1       0.00             2076.00           ✔️    
descending     1       316.00           2076.00           ✔️    
partial        1       51.00            2076.00           ✔️    
random         1       183.00           2076.00           ✔️    
====================================================================
Results saved to: result/2025-04-04_biSort_10000.csv
*/
