#include <iostream>
#include <vector>
#include <climits>

using namespace std;

ostream& operator<<(ostream& os, vector<int>& array) {
    for (size_t i = 0; i < array.size(); i++) {
        os << array[i] << " ";
    }
    return os;
}

void heapify(vector<int>& array, size_t i, size_t len) { // i must not be 0 and index of leaf node
    if (i >= array.size()) return;
    
    int parent = array.at(i);                                             
    int left = (2*i <= len ? array.at(2*i) : INT_MIN);              // it can be out of range
    // = is for last element
    int right = (2*i+1 <= len ? array.at(2*i+1) : INT_MIN);         // it can be out of range    
    // = is for last element

    if (parent >= left && parent >= right) {
        return;
    }
    if (right < left) {
        swap(array[i], array[2*i]);
        heapify(array, 2*i, len);
    } 
    else {
        swap(array[i], array[2*i + 1]);
        heapify(array, 2*i + 1, len);
    }
}

void maxHeapify(vector<int>& array, size_t index) {
    for (size_t i = index; i >= 1; i--) {
        heapify(array, i, index);
    }
} 

void heapSort(vector<int>& array) {
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

}

int main() {

    vector<int> array = {INT_MAX, 1, -1, 9, 6, 8, 7, -4, 50, 8, 10};
    vector<int> array1 = {INT_MAX, 1, 2, 3, 4, 5};
    vector<int> array2 = {INT_MAX, 7, 7, 7, 7, 7, 7};
    vector<int> array3 = {INT_MAX, 3, 2, 1, 0, -1, 99};
    vector<int> array4 = {INT_MAX, 4, -5, 0, 4, 4, -10, 20, 3};
    vector<int> array5 = {INT_MAX, 2, 1, 3};
    heapSort(array);
    heapSort(array1);
    heapSort(array2);
    heapSort(array3);
    heapSort(array4);
    heapSort(array5);

    cout << array << endl;
    cout << array1 << endl;
    cout << array2 << endl;
    cout << array3 << endl;
    cout << array4 << endl;
    cout << array5 << endl;

    cout << endl;

    return 0;
}