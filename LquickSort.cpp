#include <iostream>
#include <vector>

using namespace std;

void insertionSort(vector<int>& array, int left, int right) {
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

int partition(vector<int>& array, int p, int r) {
    int pivot = array[p];
    int i = p + 1;

    for (int j = p + 1; j <= r; j++) {
        if (array[j] < pivot) {
            swap(array[i], array[j]);
            i++;
        }
    }

    swap(array[p], array[i - 1]);
    return i - 1;
}

void LquickSort(vector<int>& array, int p, int r) {
    if (p < r) {
        if (r - p + 1 <= 10) {
            insertionSort(array, p, r);
            return;
        }

        int pivotIndex = partition(array, p, r);
        LquickSort(array, p, pivotIndex - 1);
        LquickSort(array, pivotIndex + 1, r);
    }
}

void LquickSortWrapper(vector<int>& array) {
    LquickSort(array, 0, array.size() - 1);
}

#include "Eval.h"
int main(int argc, char** argv) {
    return runEvaluation("LquickSort", argc, argv, LquickSortWrapper);
}

/*
==================== LquickSort Evaluation (size=100000) ====================
ListType       Iter    Time (avg ms)    Memory (avg KB)   Valid     
--------------------------------------------------------------------
ascending      1       5575.00          8636.00           ✔️    
descending     1       16029.00         8928.00           ✔️    
partial        1       14.00            8928.00           ✔️    
random         1       13.00            8928.00           ✔️    
====================================================================
Results saved to: result/2025-04-10_LquickSort_100000.csv
*/