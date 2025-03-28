#include <iostream>
#include <vector>

using namespace std;


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
