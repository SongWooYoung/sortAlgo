#include <iostream>

using namespace std;

// Idea
// 1. divide the array into two halves
//    stop when the array has only one element
// 2. merge the two halves
//    merge the two halves by comparing the elements of the two halves




void mergeSort(int* array, int left, int right) {

    if (left >= right) { // when left >= right, there is only one element, which means we have to merge
        //cout << array[left] << endl; => for debuging purpose
        return;
    }
    
    int mid = (left + right) / 2;
    mergeSort(array, left, mid);
    mergeSort(array, mid + 1, right);
    //merge(array, left, mid, right);

}

int main() {

    int array[10] = {1, 3, 5, 7, 9, 2, 4, 6, 8, 10};

    mergeSort(array, 0, 9);

    return 0;
}