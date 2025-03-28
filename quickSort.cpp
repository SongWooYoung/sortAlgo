#include <iostream>
#include <vector>

using namespace std;

ostream& operator<<(ostream& os, const vector<int>& v) {
    for (int i = 0; i < v.size(); i++) {
        os << v[i] << " ";
    }
    return os;
}

int partition(vector<int>& array, int p, int r) {
    // I would put the pivot in the middle of the array
    int pvalue = array.at((p+r)/2);
    int left = p;
    int right = r;
    //cout << "pivot index: " << pivot <<" pivot: "  << array.at(pivot) << endl;
    //cout << "array: " << array << endl;

    // if left >= right, the location of pivot is determinded
    while(true) {
        // if the left element is less than the pivot, move to the right
        while (array[left] < pvalue) left++;
        // if the right element is greater than the pivot, move to the left
        while (array[right] > pvalue) right--;

        if (left >= right) return right;
        
        swap(array.at(left), array.at(right));
        left++;
        right--;
    } 

    //cout << "pivot index: " << returnIndex <<" pivot: "  << array.at(returnIndex) << endl;
    //cout << "array: " << array << endl;
    //cout << endl;
    return right;
}

void quickSort(vector<int>& array, int p, int r) {
    // end condition
    if (p<r) {
    // Time Complexity: O(n log n) on average, O(n^2) worst case
    // I would follow the expression in CLRS 
    // 1. Divide: Partition (reaarrange the array)
    //    => Choose a pivot element q, and the numbers less than or equal to q should be on the left and bigget on the right
    int pivotIndex= partition(array, p, r); // partition does fix the pivot index q
    

    // 2. Sort the two subarrays A[p,,, q-1] and A[q+1,,,r] by recursive calls
    quickSort(array, p, pivotIndex);
    quickSort(array, pivotIndex+1, r);

    // 3. Combine: because the subarrays are realdy sorted, no work is needed to combine them
        
    }
}

int main() {

    vector<int> array = {1, -1, 9, 6, 8, 7, -4, 50, 8, 10};
    vector<int> array1 = {2, 8, 7, 1, 3, 5, 6, 4};
    vector<int> array2 = {7, -7, -7, 7, -7, 7};
    vector<int> array3 = {3, 2, 1, 0, -1, 99,-4, 0, 8, 7, 11};
    vector<int> array4 = {4, -5, 0, 4, 4, -10, 20, 3};
    vector<int> array5 = {2, 1, 3};
    quickSort(array, 0, 9);
    quickSort(array1, 0, 7);
    quickSort(array2, 0, 5);
    quickSort(array3, 0, 10);
    quickSort(array4, 0, 7);
    quickSort(array5, 0, 2);

    cout << array << endl;
    cout << array1 << endl;
    cout << array2 << endl;
    cout << array3 << endl;
    cout << array4 << endl;
    cout << array5 << endl;

    cout << endl;


    return 0;
}