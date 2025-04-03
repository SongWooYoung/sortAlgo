#include <iostream>
#include <vector>
#include <climits>

using namespace std;

void heapify(vector<int>& array, size_t i, size_t len) { // i must not be 0 and index of leaf node
    if (i >= array.size()) return;
    
    int parent = array.at(i);                                             
    int left = (2*i <= len ? array[2*i] : INT_MIN);              // it can be out of range
    // = is for last element
    int right = (2*i+1 <= len ? array[2*i+1] : INT_MIN);         // it can be out of range    
    // = is for last element

    if (parent >= left && parent >= right) {
        return;
    }
    if (right < left) {
        swap(array[i],array[2*i]);
        heapify(array, 2*i, len);
    } 
    else {
        swap(array[i], array[2*i+1]);
        heapify(array, 2*i + 1, len);
    }
}

void maxHeapify(vector<int>& array, size_t index) {
    for (size_t i = index; i >= 1; i--) {
        heapify(array, i, index);
    }
} 

void heapSort(vector<int>& array) {
    // add sentinel
    array.insert(array.begin(), INT_MAX);

// Heap Sort : make array into a heap and then sort it.
// Time Complexity : O(nlogn)
// 1. build max heap => asceding order, min heap => descending order
//    why? because when we swaps the last element with the first element, we want the largest element to be at the last index
//    then, what is max heap? => the parent node is always larger than the child node
    maxHeapify(array, array.size()-1); // make max heap => wrapper function using heapify(array, i)
    //cout << array << endl;

    for (int i = array.size()-1; i > 1; i--) {

        // 2. swap the first and last element // fix the max element to the last index
        swap(array[1], array[i]);
        //cout <<"after Swap: " << array << endl;
        // 3. heapify the array
        heapify(array, 1, i-1); // we have to deal with ith element => parameter
        //cout << "after heapify: " << array << endl;
    }
// 4. repeat 3 and 4 until the array is sorted

    array.erase(array.begin());
}


// int main() {


//     vector<int> data = {5, 3, 8, 6, 2, 7, 4, 1, 1001,235,32,3,24,324,23,5,3,4,2,5,25,45,436,65,6,356,4,79,8,767,5,86,7,100};

//     heapSort(data);
//     for (int num : data) {
//         cout << num << " ";
//     }
//     cout << endl;


//     return 0;
// }
