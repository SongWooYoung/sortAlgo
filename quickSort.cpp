#include <iostream>
#include <vector>

using namespace std;

void insertionSort(vector<int>& array, int left, int right) {
    for (int i = left + 1; i <= right; i++) {
        int key = array[i];
        int j = i - 1;
        while (j >= left && array[j] > key) {
            array[j + 1] = array[j];
            j--;
        }
        array[j + 1] = key;
    }
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
    if (r - p + 1 <= 10) {
        insertionSort(array, p, r);
        return;
    }

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

void quickSortWrapper(vector<int>& array) {
    vector<int> tempArray(array.size());
    quickSort(array, 0, array.size() - 1);
}


// #include "Eval.h"
// int main(int argc, char** argv) {
//     return runEvaluation("quickSort", argc, argv, quickSortWrapper);
// }

/*
only quick
==================== quickSort Evaluation ====================
ListType       Iter    Time (avg ms)    Memory (avg KB)   Valid     
--------------------------------------------------------------------
ascending      2       97.00            9670.00           ✔️    
descending     2       57.00            11468.00          ✔️    
partial        2       147.50           11468.00          ✔️    
random         2       261.50           11468.00          ✔️    
====================================================================
Results saved to: result/2025-04-04_quickSort_1000000.csv
*/

/*
quick + insert
==================== quickSort Evaluation ====================
ListType       Iter    Time (avg ms)    Memory (avg KB)   Valid     
--------------------------------------------------------------------
ascending      5       37.80            10709.60          ✔️    
descending     5       48.00            11570.40          ✔️    
partial        5       132.20           11572.00          ✔️    
random         5       233.00           11572.00          ✔️    
====================================================================
Results saved to: result/2025-04-04_quickSort_1000000.csv
*/


