#include <iostream>
#include <vector>

using namespace std;

ostream& operator<<(ostream& os, const vector<int>& v) {
    for (int i = 0; i < v.size(); i++) {
        os << v[i] << " ";
    }
    return os;
}

void quickSort(vector<int>& array, size_t p, size_t r) {
    // Time Complexity: O(n log n) on average, O(n^2) worst case
    // I would follow the expression in CLRS 
    // 1. Divide: Partition (reaarrange the array)
    //    => Choose a pivot element q, and the numbers less than or equal to q should be on the left and bigget on the right
    partition();

    // 2. Sort the two subarrays A[p,,, q-1] and A[q+1,,,r] by recursive calls
    quickSort(array, p, q-1);
    quickSort(array, q+1, r);

    // 3. Combine: because the subarrays are realdy sorted, no work is needed to combine them
}

int main() {


    vector<int> array = {1, -1, 9, 6, 8, 7, -4, 50, 8, 10};
    vector<int> array1 = {1, 2, 3, 4, 5};
    vector<int> array2 = {7, 7, 7, 7, 7, 7};
    vector<int> array3 = {3, 2, 1, 0, -1, 99};
    vector<int> array4 = {4, -5, 0, 4, 4, -10, 20, 3};
    vector<int> array5 = {2, 1, 3};
    quickSort(array);
    quickSort(array1);
    quickSort(array2);
    quickSort(array3);
    quickSort(array4);
    quickSort(array5);

    cout << array << endl;
    cout << array1 << endl;
    cout << array2 << endl;
    cout << array3 << endl;
    cout << array4 << endl;
    cout << array5 << endl;

    cout << endl;


    return 0;
}