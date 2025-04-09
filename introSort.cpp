#include <iostream>
#include <vector>
#include <cmath>
#include <climits>

using namespace std;

/*
#include "quickSort.cpp"

void heapify(vector<int>& array, size_t start, size_t n, size_t i) {
    while (true) {
        size_t largest = i;
        size_t left = 2 * (i - start) + 1 + start;
        size_t right = 2 * (i - start) + 2 + start;

        if (left < start + n && array[left] > array[largest]) {
            largest = left;
        }
        if (right < start + n && array[right] > array[largest]) {
            largest = right;
        }

        if (largest == i) break;

        swap(array[i], array[largest]);
        i = largest;
    }
}

void buildMaxHeap(vector<int>& array, size_t start, size_t end) {
    size_t n = end - start + 1;
    for (int i = static_cast<int>(start + n / 2 - 1); i >= static_cast<int>(start); --i) {
        heapify(array, start, n, i);
    }
}

void heapSort(vector<int>& array, size_t left, size_t right) {
    if (left >= right) return;

    size_t n = right - left + 1;
    buildMaxHeap(array, left, right);

    for (size_t i = right; i > left; --i) {
        swap(array[left], array[i]);
        heapify(array, left, i - left, left);
    }
}

int partition(vector<int>& array, int p, int r) {
    // I would put the pivot in the middle of the array
    int pvalue = array.at((p+r)/2);
    int left = p;
    int right = r;
    //cout << "pivot index: " << pivot <<" pivot: "  << array.at(pivot) << endl;
    //cout << "array: " << array << endl;

    // if left >= right, the location of pivot is determinded
    while(true) {
        // if the left element is less than the pivot, move to the right
        while (array[left] < pvalue) left++;
        // if the right element is greater than the pivot, move to the left
        while (array[right] > pvalue) right--;

        if (left >= right) return right;
        
        swap(array.at(left), array.at(right));
        left++;
        right--;
    } 

    //cout << "pivot index: " << returnIndex <<" pivot: "  << array.at(returnIndex) << endl;
    //cout << "array: " << array << endl;
    //cout << endl;
    return right;
}

void quickSort(vector<int>& array, int p, int r) {
    // end condition
    if (p<r) {
    if (r - p + 1 <= 10) {
        insertionSort(array, p, r);
        return;
    }

    // Time Complexity: O(n log n) on average, O(n^2) worst case
    // I would follow the expression in CLRS 
    // 1. Divide: Partition (reaarrange the array)
    //    => Choose a pivot element q, and the numbers less than or equal to q should be on the left and bigget on the right
    int pivotIndex= partition(array, p, r); // partition does fix the pivot index q
    

    // 2. Sort the two subarrays A[p,,, q-1] and A[q+1,,,r] by recursive calls
    quickSort(array, p, pivotIndex);
    quickSort(array, pivotIndex+1, r);

    // 3. Combine: because the subarrays are realdy sorted, no work is needed to combine them
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
        heapSort(array,left,right);
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
*/

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

void heapify(vector<int>& array, size_t start, size_t n, size_t i) {
    while (true) {
        size_t largest = i;
        size_t left = 2 * (i - start) + 1 + start;
        size_t right = 2 * (i - start) + 2 + start;

        if (left < start + n && array[left] > array[largest]) {
            largest = left;
        }
        if (right < start + n && array[right] > array[largest]) {
            largest = right;
        }

        if (largest == i) break;

        swap(array[i], array[largest]);
        i = largest;
    }
}

void buildMaxHeap(vector<int>& array, size_t start, size_t end) {
    size_t n = end - start + 1;
    for (int i = static_cast<int>(start + n / 2 - 1); i >= static_cast<int>(start); --i) {
        heapify(array, start, n, i);
    }
}

void heapSort(vector<int>& array, size_t left, size_t right) {
    if (left >= right) return;

    buildMaxHeap(array, left, right);

    for (size_t i = right; i > left; --i) {
        swap(array[left], array[i]);
        heapify(array, left, i - left, left);
    }
}

int partition(vector<int>& array, int p, int r) {
    int pvalue = array.at((p+r)/2);
    int left = p;
    int right = r;
    while(true) {
        while (array[left] < pvalue) left++;
        while (array[right] > pvalue) right--;
        if (left >= right) return right;
        swap(array.at(left), array.at(right));
        left++;
        right--;
    } 
    return right;
}
void HQI(vector<int>& array, int left, int right, int depthLimit) {
    int len = right - left + 1;
    if (len <= 10) {
        InsertionSort(array, left, right);
        return;
    }
    if (depthLimit == 0) {
        heapSort(array, left, right);
        return;
    }

    int pivot = partition(array, left, right);
    HQI(array, left, pivot, depthLimit - 1);
    HQI(array, pivot + 1, right, depthLimit - 1);
}

void introSort(vector<int>& array) {
    int depthLimit = 2 * log2(array.size());
    HQI(array, 0, array.size() - 1, depthLimit);
}

#include "Eval.h"

int main(int argc, char** argv) {
    return runEvaluation("introSort", argc, argv, introSort);
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

/*
==================== introSort Evaluation ====================
ListType       Iter    Time (avg ms)    Memory (avg KB)   Valid     
--------------------------------------------------------------------
ascending      10      2.10             4038.80           ✔️    
descending     10      2.80             4036.00           ✔️    
partial        10      14.90            4036.00           ✔️    
random         10      17.40            4036.00           ✔️    
====================================================================
Results saved to: result/2025-04-06_introSort_100000.csv
*/

/*
==================== introSort Evaluation ====================
ListType       Iter    Time (avg ms)    Memory (avg KB)   Valid     
--------------------------------------------------------------------
ascending      10      25.20            7674.40           ✔️    
descending     10      32.20            7696.00           ✔️    
partial        10      139.30           7696.00           ✔️    
random         10      156.70           7696.00           ✔️    
====================================================================
Results saved to: result/2025-04-06_introSort_1000000.csv
*/

/*
==================== introSort Evaluation ====================
ListType       Iter    Time (avg ms)    Memory (avg KB)   Valid     
--------------------------------------------------------------------
ascending      10      29.30            7640.40           ✔️    
descending     10      34.10            7664.00           ✔️    
partial        10      143.50           7664.00           ✔️    
random         10      159.10           7664.00           ✔️    
====================================================================
Results saved to: result/2025-04-06_introSort_1000000.csv
*/