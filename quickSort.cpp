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
    int pvalue = array[(p+r)/2];
    int left = p;
    int right = r;

    while(true) {
        while (array[left] < pvalue) left++;
        while (array[right] > pvalue) right--;
        if (left >= right) return right;
        swap(array[left], array[right]);
        left++;
        right--;
    } 

    return right;
}

void quickSort(vector<int>& array, int p, int r) {
    if (p<r) {
    if (r - p + 1 <= 10) {
        insertionSort(array, p, r);
        return;
    }

    int pivotIndex= partition(array, p, r); // partition does fix the pivot index q
    quickSort(array, p, pivotIndex);
    quickSort(array, pivotIndex+1, r);
    }
}

void quickSortWrapper(vector<int>& array) {
    vector<int> tempArray((int) array.size());
    quickSort(array, 0, (int) array.size() - 1);
}

#include "Eval.h"
int main(int argc, char** argv) {
    return runEvaluation("quickSort", argc, argv, quickSortWrapper);
}

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

/*
==================== quickSort Evaluation (size=1000000) ====================
ListType       Iter    Time (avg ms)    Memory (avg KB)   Valid     
--------------------------------------------------------------------
ascending      10      25.40            11140.40          ✔️    
descending     10      28.50            11539.60          ✔️    
partial        10      117.60           11540.80          ✔️    
random         10      132.40           11544.00          ✔️    
====================================================================
Results saved to: result/2025-04-10_quickSort_1000000.csv
*/

/*
==================== quickSort Evaluation (size=10000000) ====================
ListType       Iter    Time (avg ms)    Memory (avg KB)   Valid     
--------------------------------------------------------------------
ascending      10      289.40           42971.60          ✔️    
descending     10      320.00           43096.00          ✔️    
partial        10      1400.90          43104.40          ✔️    
random         10      1541.00          43108.00          ✔️    
====================================================================
Results saved to: result/2025-04-10_quickSort_10000000.csv
*/