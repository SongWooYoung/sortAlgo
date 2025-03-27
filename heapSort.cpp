#include <iostream>
#include <vector>

#define stl 1<<31

using namespace std;

void heapSort(vector<int>& array) {
// Heap Sort : make array into a heap and then sort it.
// Time Complexity : O(nlogn)
// 1. build max heap => asceding order, min heap => descending order
//    why? because when we swaps the last element with the first element, we want the largest element to be at the last index
//    then, what is max heap? => the parent node is always larger than the child node
    maxHeapify();

    for (int i = array.size(); i > 0; i--) {

        // 2. swap the first and last element // fix the max element to the last index
        swap(array[1], array[i - 1]);
        
        // 3. heapify the array
        heapify(); // root node has next largest element
    }
// 4. repeat 3 and 4 until the array is sorted

}




int main() {

    vector<int> array = {stl, 1, -1, 9, 6, 8, 7, -4, 50, 8, 10};

    heapSort(array);

    for (int i = 0; i < 10; i++) {
        cout << array[i] << " ";
    }

    cout << endl;

    return 0;
}