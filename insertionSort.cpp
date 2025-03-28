#include <iostream>
#include <vector>

using namespace std;

// I've tried to implement insertion sort with array
// However, the limitation of array requires me to use heap memory
// => I will use vector instead of array

void insertionSort(vector<int>& array, size_t len) {
    if (len == 0) return;

    for (size_t i = 1; i < len; i++) {
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


// void insertionSort(vector<int>& array, size_t len) { // call by reference
//     // Insertion Sort : sort the array by inserting the element into the sorted part of the array
//     // Time Complexity : O(n^2)
//     // Do not use online sort the array
//     // Make temparray to store the sorted part of the array
//     // move the elements to the temparray
//     // then, insert the element into the temparray
//     // finally, copy the temparray to the original array
//     vector<int> tempArray;

//     for (size_t i = 0; i < len; i++) {
//         bool inserted = false;

//         // if tempArray is empty, push
//         if (tempArray.empty()) {
//             tempArray.push_back(array[i]);
//             continue;
//         }

//         for (size_t j = 0; j < tempArray.size(); j++) {
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
//     for (size_t i = 0; i < len; i++) {
//         array[i] = tempArray[i];
//     }
// }

