#include <iostream>
#include <vector>
#include <climits>

using namespace std;

// void heapify(vector<int>& array, size_t i, size_t len) { // i must not be 0 and index of leaf node
//     if (i >= array.size()) return;
    
//     int parent = array.at(i);                                             
//     int left = (2*i <= len ? array[2*i] : INT_MIN);              // it can be out of range
//     // = is for last element
//     int right = (2*i+1 <= len ? array[2*i+1] : INT_MIN);         // it can be out of range    
//     // = is for last element

//     if (parent >= left && parent >= right) {
//         return;
//     }
//     if (right < left) {
//         swap(array[i],array[2*i]);
//         heapify(array, 2*i, len);
//     } 
//     else {
//         swap(array[i], array[2*i+1]);
//         heapify(array, 2*i + 1, len);
//     }
// }

// void maxHeapify(vector<int>& array, size_t index) {
//     for (size_t i = index; i >= 1; i--) {
//         heapify(array, i, index);
//     }
// } 

// void heapSort(vector<int>& array) {
//     // add sentinel
//     array.insert(array.begin(), INT_MAX);

// // Heap Sort : make array into a heap and then sort it.
// // Time Complexity : O(nlogn)
// // 1. build max heap => asceding order, min heap => descending order
// //    why? because when we swaps the last element with the first element, we want the largest element to be at the last index
// //    then, what is max heap? => the parent node is always larger than the child node
//     maxHeapify(array, array.size()-1); // make max heap => wrapper function using heapify(array, i)
//     //cout << array << endl;

//     for (int i = array.size()-1; i > 1; i--) {

//         // 2. swap the first and last element // fix the max element to the last index
//         swap(array[1], array[i]);
//         //cout <<"after Swap: " << array << endl;
//         // 3. heapify the array
//         heapify(array, 1, i-1); // we have to deal with ith element => parameter
//         //cout << "after heapify: " << array << endl;
//     }
// // 4. repeat 3 and 4 until the array is sorted

//     array.erase(array.begin());
// }

#include <iostream>
#include <vector>
#include "Eval.h"

using namespace std;

void heapify(vector<int>& array, size_t n, size_t i) {
    while (true) {
        size_t largest = i;
        size_t left = 2 * i + 1;
        size_t right = 2 * i + 2;

        largest = (left < n && array[left] > array[largest]) ? left : largest;
        largest = (right < n && array[right] > array[largest]) ? right : largest;

        if (largest == i) break;

        swap(array[i], array[largest]);
        i = largest;
    }
}

// Build max heap in bottom-up manner
void buildMaxHeap(vector<int>& array) {
    size_t n = array.size();
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(array, n, i);
    }
}

void heapSort(vector<int>& array) {
    size_t n = array.size();
    buildMaxHeap(array);

    for (int i = n - 1; i > 0; i--) {
        swap(array[0], array[i]);
        heapify(array, i, 0);
    }
}

int main(int argc, char** argv) {
    return runEvaluation("heapSort", argc, argv, heapSort);
}

/*
first implement: 
==================== heapSort Evaluation ====================
ListType       Iter    Time (avg ms)    Memory (avg KB)   Valid     
--------------------------------------------------------------------
ascending      5       521.80           12389.60          ✔️    
descending     5       754.40           13108.00          ✔️    
partial        5       911.80           13108.00          ✔️    
random         5       1209.40          13108.00          ✔️    
====================================================================
Results saved to: result/2025-04-04_heapSort_1000000.csv
*/

/*
following pseudo code
==================== heapSort Evaluation ====================
ListType       Iter    Time (avg ms)    Memory (avg KB)   Valid     
--------------------------------------------------------------------
ascending      5       604.40           7672.80           ✔️    
descending     5       561.00           7708.00           ✔️    
partial        5       769.00           7708.00           ✔️    
random         5       918.00           7708.00           ✔️    
====================================================================
Results saved to: result/2025-04-04_heapSort_1000000.csv
*/

/*
braanch-less heapify
==================== heapSort Evaluation ====================
ListType       Iter    Time (avg ms)    Memory (avg KB)   Valid     
--------------------------------------------------------------------
ascending      5       478.60           7616.80           ✔️    
descending     5       546.80           7652.00           ✔️    
partial        5       681.60           7652.00           ✔️    
random         5       731.60           7652.00           ✔️    
====================================================================
Results saved to: result/2025-04-04_heapSort_1000000.csv
*/

