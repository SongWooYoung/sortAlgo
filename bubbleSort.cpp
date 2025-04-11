#include <iostream>
#include <vector>
#include "Eval.h"

using namespace std;
void bubbleSort(vector<int>& array) { // ascending order
    // Time Complexity : O(n^2)
    // change two elements => current and next element
    // bigger one goes to the right
    // at first completion, the largest element goes to the last index
    // at second completion, the second largest element goes to the second last index
    // in the end, the smallest element goes to the first index
    // size_t len = array.size();
    // for (size_t j = 0; j < len-1; j++) { // last iteration is useless because there is only one that is unsorted
    //     for (size_t i = 0; i < len-1-j; i++) { // every iteration, there is one element that is sorted
    //         if (array[i] > array[i+1]) {
    //             swap(array[i], array[i+1]);
    //         }
    //     }
    // }

    /* 
    ==================== bubbleSort Evaluation ====================
    ListType       Iter      Time (ms)      Memory (KB)    
    -------------------------------------------------------
    ascending      1         114            2020           
    descending     1         499            2020           
    partial        1         189            2020           
    random         1         465            2020           
    ===============================================================
    Results saved to: result/2025-04-04_bubbleSort_10000.csv
    */
   size_t len = array.size();

    for (size_t j = 0; j < len-1; j++) { // last iteration is useless because there is only one that is unsorted
        bool swapped = false;   
        for (size_t i = 0; i < len-1-j; i++) { // every iteration, there is one element that is sorted
           if (array[i] > array[i+1]) {
               swap(array[i], array[i+1]);
               swapped = true;
            }
        }
       if (!swapped)  break; // No swaps means the array is sorted
    }
    /*
    ==================== bubbleSort Evaluation ====================
    ListType       Iter    Time (avg ms)    Memory (avg KB)   Valid     
    --------------------------------------------------------------------
    ascending      3       0.00             2072.00           ✔️    
    descending     3       560.00           2072.00           ✔️    
    partial        3       180.00           2072.00           ✔️    
    random         3       472.00           2072.00           ✔️    
    ====================================================================
    Results saved to: result/2025-04-04_bubbleSort_10000.csv
    */
    // asceding order 에서 기막힌 향상

    // if possible, we can reduce the number of iterations
    // because there are elemets already sorted
}

#include "Eval.h"
int main(int argc, char** argv) {
    return runEvaluation("bubbleSort", argc, argv, bubbleSort);  // ✨ 원하는 정렬 이름만 전달
}

/*
==================== bubbleSort Evaluation (size=1000000) ====================
ListType       Iter    Time (avg ms)    Memory (avg KB)   Valid     
--------------------------------------------------------------------
ascending      10      1.30             7728.00           ✔️    
descending     10      4464868.70       7740.00           ✔️    
partial        10      3053618.00       7740.00           ✔️    
random         10      4414500.20       7740.00           ✔️    
====================================================================
Results saved to: result/2025-04-10_bubbleSort_1000000.csv
*/