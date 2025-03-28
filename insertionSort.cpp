#include <iostream>
#include <vector>

using namespace std;

// I've tried to implement insertion sort with array
// However, the limitation of array requires me to use heap memory
// => I will use vector instead of array


void insertionSort(vector<int>& array, int num) { // call by reference

    int len = array.size();
    for (int i = 0; i < len; i++) {
        if (num < array[i]) {
            array.insert(array.begin() + i, num); // insert have to use iteration
            return;
        }
    }
    array.push_back(num);

    // previous code unnecessarily used if statement
}
