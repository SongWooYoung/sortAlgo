#include <iostream>

using namespace std;

// Idea
// 1. divide the array into two halves
//    stop when the array has only one element
// 2. merge the two halves
//    merge the two halves by comparing the elements of the two halves


void merge(int* array, int left, int mid, int right){ // ascedning order
    //the idea of merge
    // 0. we need of course a variable that indicates the index of the array that we are going to put the value
    // 1. we know the left, mid, and right index of the array
    // 2. we declare indexL and indexR which are the indices that have lowest value of each array
    int tempArray[right - left + 1];
    int wheretoPut = 0;
    int indexL = left;
    int indexR = mid + 1;

    // 3. we compare the value of the indexLV and indexRV and put the smaller value into the array
    // 4. we increase the indexL or indexR by 1

    // 5. results are screwed up => because we have to consider the change in the array....
    //    Like, if we change the value of indexL then, the original value has gone.
    //    So, i want to make another variable holding the original value of the array in that index

    // I considered the possibility of in-place implementation, but it is impossible because it overwrites the original value of the array
    while (indexL <= mid && indexR <= right) {
        if (array[indexL] < array[indexR]) {
            tempArray[wheretoPut] = array[indexL];
            indexL++;
        } else {
            tempArray[wheretoPut] = array[indexR];
            indexR++;
        }
        wheretoPut++;
    }
    while (indexL <= mid) {
        tempArray[wheretoPut] = array[indexL];
        indexL++;
        wheretoPut++;
    }
    while (indexR <= right) {
        tempArray[wheretoPut] = array[indexR];
        indexR++;
        wheretoPut++;
    }
    for (int i = 0; i < wheretoPut; i++) {
        array[left + i] = tempArray[i];
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