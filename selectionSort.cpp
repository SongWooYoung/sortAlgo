#include <iostream>
#include <vector>
#include <climits>

using namespace std;


void selectionSort(vector<int>& array) {
    // one of the in-place sorting algorithms
    // Time Complexity : O(n^2)
    // find the minimun element in the unsorted part
    // swap the minimum element with the first element in the unsorted part
    size_t len = array.size();
    for (size_t i = 0 ; i < len-1; i++) { // lotaiton number;
        int min = INT_MAX;
        size_t minIndex;
        for (size_t j = i; j < len; j++) {
            if (array.at(j) < min) {
                min = array.at(j);
                minIndex = j;
            }
        }
        swap(array.at(i), array.at(minIndex));
    }
}

#include "Eval.h"
int main(int argc, char** argv) {
    return runEvaluation("selectionSort", argc, argv, selectionSort); 
}


/*
==================== selectionSort Evaluation ====================
ListType       Iter    Time (avg ms)    Memory (avg KB)   Valid     
--------------------------------------------------------------------
ascending      3       176.33           2136.00           ✔️    
descending     3       286.00           2136.00           ✔️    
partial        3       284.00           2136.00           ✔️    
random         3       401.00           2136.00           ✔️    
====================================================================
Results saved to: result/2025-04-09_selectionSort_10000.csv
*/