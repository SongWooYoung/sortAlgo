#include <iostream>

using namespace std;

// Heap Sort : make array into a heap and then sort it.
// Time Complexity : O(nlogn)
// 1. put all things into an array
// 2. build max heap
// 3. swap the first and last element
// 4. heapify the array
// 5. repeat 3 and 4 until the array is sorted




int main() {

    int array[10] = {1, -1, 9, 6, 8, 7, -4, 50, 8, 10};

    heapSort(array, 5);

    for (int i = 0; i < 10; i++) {
        cout << array[i] << " ";
    }

    cout << endl;

    return 0;
}