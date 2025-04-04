#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "Eval.h"

using namespace std;

// // Merge two halves of the vector in ascending order
// void merge(vector<int>& array, int left, int mid, int right) {
//     vector<int> tempArray(right - left + 1);
//     int indexL = left;
//     int indexR = mid + 1;
//     int wheretoPut = 0;

//     while (indexL <= mid && indexR <= right) {
//         if (array[indexL] <= array[indexR]) {
//             tempArray[wheretoPut++] = array[indexL++];
//         } else {
//             tempArray[wheretoPut++] = array[indexR++];
//         }
//     }

//     while (indexL <= mid) {
//         tempArray[wheretoPut++] = array[indexL++];
//     }

//     while (indexR <= right) {
//         tempArray[wheretoPut++] = array[indexR++];
//     }

//     for (int i = 0; i < wheretoPut; ++i) {
//         array[left + i] = tempArray[i];
//     }
// }

// // Recursive vector-based merge sort
// void mergeSort(vector<int>& array, int left, int right) {
//     if (left >= right) return;

//     int mid = (left + right) / 2;
//     mergeSort(array, left, mid);
//     mergeSort(array, mid + 1, right);
//     merge(array, left, mid, right);
// }

/*
==================== MergeSort Evaluation ====================
ListType       Iter    Time (avg ms)    Memory (avg KB)   Valid     
--------------------------------------------------------------------
ascending      2       868.50           10564.00          ✔️    
descending     2       912.00           11646.00          ✔️    
partial        2       1141.00          11652.00          ✔️    
random         2       1207.50          11652.00          ✔️    
====================================================================
Results saved to: result/2025-04-04_MergeSort_1000000.csv
*/
// Merge using external reusable tempArray

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

void merge(vector<int>& array, int left, int mid, int right, vector<int>& tempArray) {
    int indexL = left;
    int indexR = mid + 1;
    int wheretoPut = left;  // Use global index in tempArray

    while (indexL <= mid && indexR <= right) {
        if (array[indexL] <= array[indexR]) {
            tempArray[wheretoPut++] = array[indexL++];
        } else {
            tempArray[wheretoPut++] = array[indexR++];
        }
    }

    while (indexL <= mid) {
        tempArray[wheretoPut++] = array[indexL++];
    }

    while (indexR <= right) {
        tempArray[wheretoPut++] = array[indexR++];
    }

    // Copy back to original array
    for (int i = left; i <= right; ++i) {
        array[i] = tempArray[i];
    }
}

void mergeSort(vector<int>& array, int left, int right, vector<int>& tempArray) {
    if (left >= right) return;
    if (right - left + 1 <=11) {
        insertionSort(array, left, right);
        return;
    }

    int mid = (left + right) / 2;
    mergeSort(array, left, mid, tempArray);
    mergeSort(array, mid + 1, right, tempArray);
    merge(array, left, mid, right, tempArray);
}

void mergeSortWrapper(vector<int>& array) {
    vector<int> tempArray(array.size());
    mergeSort(array, 0, array.size() - 1, tempArray);
}

int main(int argc, char** argv) {
    return runEvaluation("MergeSort", argc, argv, mergeSortWrapper);
}


/*
tempArray 
==================== MergeSort Evaluation ====================
ListType       Iter    Time (avg ms)    Memory (avg KB)   Valid     
--------------------------------------------------------------------
ascending      2       341.50           9428.00           ✔️    
descending     2       345.00           11632.00          ✔️    
partial        2       571.00           11640.00          ✔️    
random         2       1127.00          11640.00          ✔️    
====================================================================
Results saved to: result/2025-04-04_MergeSort_1000000.csv
*/

/*
insertion: 길이가 9일때
==================== MergeSort Evaluation ====================
ListType       Iter    Time (avg ms)    Memory (avg KB)   Valid     
--------------------------------------------------------------------
ascending      2       281.50           9690.00           ✔️    
descending     2       249.50           11612.00          ✔️    
partial        2       283.00           11616.00          ✔️    
random         2       455.00           11616.00          ✔️    
====================================================================
Results saved to: result/2025-04-04_MergeSort_1000000.csv
*/

/*
insertion: 길이가 10일때
==================== MergeSort Evaluation ====================
ListType       Iter    Time (avg ms)    Memory (avg KB)   Valid     
--------------------------------------------------------------------
ascending      2       216.50           9514.00           ✔️    
descending     2       263.00           11432.00          ✔️    
partial        2       397.50           11436.00          ✔️    
random         2       475.00           11436.00          ✔️    
====================================================================
Results saved to: result/2025-04-04_MergeSort_1000000.csv
*/

/*
insertion: 길이가 11일때
==================== MergeSort Evaluation ====================
ListType       Iter    Time (avg ms)    Memory (avg KB)   Valid     
--------------------------------------------------------------------
ascending      2       225.50           9670.00           ✔️    
descending     2       247.00           11468.00          ✔️    
partial        2       337.00           11468.00          ✔️    
random         2       516.50           11468.00          ✔️    
====================================================================
Results saved to: result/2025-04-04_MergeSort_1000000.csv
*/
