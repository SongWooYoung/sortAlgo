#include <iostream>
#include <vector>

using namespace std;

ostream& operator<<(ostream& os, vector<int>& array) {
    for (size_t i = 0; i < array.size(); i++) {
        os << array[i] << " ";
    }
    return os;
}

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

int main() {

    vector<int> array = {1, -1, 9, 6, 8, 7, -4, 50, 8, 10};
    vector<int> array1 = {1, 2, 3, 4, 5};
    vector<int> array2 = {7, 7, 7, 7, 7, 7};
    vector<int> array3 = {3, 2, 1, 0, -1, 99};
    vector<int> array4 = {4, -5, 0, 4, 4, -10, 20, 3};
    vector<int> array5 = {2, 1, 3};
    bubbleSort(array);
    bubbleSort(array1);
    bubbleSort(array2);
    bubbleSort(array3);
    bubbleSort(array4);
    bubbleSort(array5);

    cout << array << endl;
    cout << array1 << endl;
    cout << array2 << endl;
    cout << array3 << endl;
    cout << array4 << endl;
    cout << array5 << endl;

    cout << endl;

    return 0;
}