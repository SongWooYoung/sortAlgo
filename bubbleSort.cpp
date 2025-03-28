#include <iostream>
#include <vector>

using namespace std;
void bubbleSort(vector<int>& array) { // ascending order
    // Time Complexity : O(n^2)
    // change two elements => current and next element
    // bigger one goes to the right
    // at first completion, the largest element goes to the last index
    // at second completion, the second largest element goes to the second last index
    // in the end, the smallest element goes to the first index
    size_t len = array.size();
    for (size_t j = 0; j < len-1; j++) { // last iteration is useless because there is only one that is unsorted
        for (size_t i = 0; i < len-1-j; i++) { // every iteration, there is one element that is sorted
            if (array[i] > array[i+1]) {
                swap(array[i], array[i+1]);
            }
        }
    }

    // if possible, we can reduce the number of iterations
    // because there are elemets already sorted
}
