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
    // Median-of-three: pick first, middle, and last elements
    int mid = (p + r) / 2;

    // Sort the three elements to find the median
    if (array[p] > array[mid]) swap(array[p], array[mid]);
    if (array[p] > array[r]) swap(array[p], array[r]);
    if (array[mid] > array[r]) swap(array[mid], array[r]);

    // Use the median value as pivot (now in array[mid])
    int pvalue = array[mid];

    int left = p;
    int right = r;

    while (true) {
        while (array[left] < pvalue) left++;
        while (array[right] > pvalue) right--;

        if (left >= right) return right;

        swap(array[left], array[right]);
        left++;
        right--;
    }

    return right;
}


void mtquickSort(vector<int>& array, int p, int r) {
    if (p<r) {
    if (r - p + 1 <= 10) {
        insertionSort(array, p, r);
        return;
    }

    int pivotIndex= partition(array, p, r); // partition does fix the pivot index q
    mtquickSort(array, p, pivotIndex);
    mtquickSort(array, pivotIndex+1, r);
    }
}

void mtquickSortWrapper(vector<int>& array) {
    vector<int> tempArray((int) array.size());
    mtquickSort(array, 0, (int) array.size() - 1);
}

#include "Eval.h"
int main(int argc, char** argv) {
    return runEvaluation("mtqSort", argc, argv, mtquickSortWrapper);
}

/*
==================== mtquickSort Evaluation (size=1000000) ====================
ListType       Iter    Time (avg ms)    Memory (avg KB)   Valid     
--------------------------------------------------------------------
ascending      10      25.00            11100.40          ✔️    
descending     10      29.00            11507.60          ✔️    
partial        10      118.80           11508.00          ✔️    
random         10      135.00           11508.00          ✔️    
====================================================================
Results saved to: result/2025-04-10_mtquickSort_1000000.csv
*/

/*
==================== mtquickSort Evaluation (size=10000000) ====================
ListType       Iter    Time (avg ms)    Memory (avg KB)   Valid     
--------------------------------------------------------------------
ascending      10      309.90           42923.60          ✔️    
descending     10      350.10           42964.00          ✔️    
partial        10      1403.30          42964.00          ✔️    
random         10      1610.10          42964.00          ✔️    
====================================================================
Results saved to: result/2025-04-10_mtquickSort_10000000.csv
*/
