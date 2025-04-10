#include <iostream>
#include <vector>

using namespace std;

// I've tried to implement insertion sort with array
// However, the limitation of array requires me to use heap memory
// => I will use vector instead of array

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




// void insertionSort(vector<int>& array, int len) { // call by reference
//     // Insertion Sort : sort the array by inserting the element into the sorted part of the array
//     // Time Complexity : O(n^2)
//     // Do not use online sort the array
//     // Make temparray to store the sorted part of the array
//     // move the elements to the temparray
//     // then, insert the element into the temparray
//     // finally, copy the temparray to the original array
//     vector<int> tempArray;

//     for (int i = 0; i < len; i++) {
//         bool inserted = false;

//         // if tempArray is empty, push
//         if (tempArray.empty()) {
//             tempArray.push_back(array[i]);
//             continue;
//         }

//         for (int j = 0; j < tempArray.size(); j++) {
//             if (array[i] < tempArray[j]) {
//                 tempArray.insert(tempArray.begin() + j, array[i]);
//                 inserted = true;
//                 break;
//             }
//         }

//         if (!inserted) {
//             // if the element is larger than all elements in tempArray
//             tempArray.push_back(array[i]);
//         }
//     }
//     for (int i = 0; i < len; i++) {
//         array[i] = tempArray[i];
//     }
// }

#include "Eval.h"
int main(int argc, char** argv) {
    return runEvaluation("insertionSort", argc, argv, insertionSort);  // ✨ 원하는 정렬 이름만 전달
}

/*
==================== insertionSort Evaluation (size=100000) ====================
ListType       Iter    Time (avg ms)    Memory (avg KB)   Valid     
--------------------------------------------------------------------
ascending      10      0.00             4290.40           ✔️    
descending     10      14698.50         4288.00           ✔️    
partial        10      5392.00          4288.00           ✔️    
random         10      7133.80          4288.00           ✔️    
====================================================================
Results saved to: result/2025-04-10_insertionSort_100000.csv
*/


/*
==================== insertionSort Evaluation (size=1000000) ====================
ListType       Iter    Time (avg ms)    Memory (avg KB)   Valid     
--------------------------------------------------------------------
ascending      10      2.90             7749.60           ✔️    
descending     10      1410074.00       7768.00           ✔️    
partial        10      515323.90        7768.00           ✔️    
random         10      695550.80        7768.00           ✔️    
====================================================================
Results saved to: result/2025-04-10_insertionSort_1000000.csv
*/