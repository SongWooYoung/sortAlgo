#include <iostream>

using namespace std;

// Idea
// 1. divide the array into two halves
//    stop when the array has only one element
// 2. merge the two halves
//    merge the two halves by comparing the elements of the two halves


void merge(int* array, int left, int mid, int right){ 
    //the idea of merge
    // 0. we need of course a variable that indicates the index of the array that we are going to put the value
    // 1. we know the left, mid, and right index of the array
    // 2. we declare indexL and indexR which are the indices that have lowest value of each array
    int wheretoPut = left;
    int indexL = left;
    int indexR = mid + 1;
    // 3. we compare the value of the indexLV and indexRV and put the smaller value into the array
    // 4. we increase the indexL or indexR by 1
    while (indexL <= mid && indexR <= right) {
        if (array[indexL] < array[indexR]) {
            array[wheretoPut] = array[indexL];
            indexL++;
        } else {
            array[wheretoPut] = array[indexR];
            indexR++;
        }
        wheretoPut++;
    }
    
    while (indexL <= mid) {
        array[wheretoPut] = array[indexL];
        indexL++;
        wheretoPut++;
    }
    while (indexR <= right) {
        array[wheretoPut] = array[indexR];
        indexR++;
        wheretoPut++;
    }
}


void mergeSort(int* array, int left, int right) { // I want it to be in-place sorting

    if (left >= right) { // when left >= right, there is only one element, which means we have to merge
        //cout << array[left] << endl; => for debuging purpose
        return;
    }
    
    int mid = (left + right) / 2;
    mergeSort(array, left, mid);
    mergeSort(array, mid + 1, right);
    merge(array, left, mid, right);
}

int main() {

    int array[10] = {1, 3, 5, 7, 9, 2, 4, 6, 8, 10};

    mergeSort(array, 0, 9);

    for (int i = 0; i < 10; i++) {
        cout << array[i] << " ";
    }

    return 0;
}