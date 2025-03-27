#include <iostream>
#include <vector>

using namespace std;

ostream& operator<<(ostream& os, vector<int>& array) {
    for (size_t i = 0; i < array.size(); i++) {
        os << array[i] << " ";
    }
    return os;
}

void selectionSort(vector<int>& array) {
    // one of the in-place sorting algorithms
    // Time Complexity : O(n^2)
    // find the minimun element in the unsorted part
    // swap the minimum element with the first element in the unsorted part

    

}




int main() {

    vector<int> array = {1, -1, 9, 6, 8, 7, -4, 50, 8, 10};
    vector<int> array1 = {1, 2, 3, 4, 5};
    vector<int> array2 = {7, 7, 7, 7, 7, 7};
    vector<int> array3 = {3, 2, 1, 0, -1, 99};
    vector<int> array4 = {4, -5, 0, 4, 4, -10, 20, 3};
    vector<int> array5 = {2, 1, 3};
    selectionSort(array);
    selectionSort(array1);
    selectionSort(array2);
    selectionSort(array3);
    selectionSort(array4);
    selectionSort(array5);

    cout << array << endl;
    cout << array1 << endl;
    cout << array2 << endl;
    cout << array3 << endl;
    cout << array4 << endl;
    cout << array5 << endl;

    cout << endl;

    return 0;
}