#include <iostream>
#include <vector>
using namespace std;

void combSort(vector<int>& array) {
    int n = array.size();
    //double shrinkFactor = 1.24733;
    int gap = n;
    bool swapped = true;

    while (gap > 1 || swapped) {
        gap = gap / 1.3; // Shrink the gap
        if (gap < 1) gap = 1;

        swapped = false;
        for (int i = 0; i + gap < n; ++i) {
            if (array[i] > array[i + gap]) {
                swap(array[i], array[i + gap]);
                swapped = true;
            }
        }
    }
}

// #include <cmath>

// void combSort(vector<int>& array) {
//     int n = array.size();
//     double baseFactor = 1.15;  // 시작할 때 느리게 줄이고
//     double growth = 0.02;      // 점점 증가시킴
//     double factor = baseFactor;
//     int gap = n;
//     bool swapped = true;

//     while (gap > 1 || swapped) {
//         factor += growth;  // shrink factor를 점점 키운다
//         gap = int(gap / factor);
//         if (gap < 1) gap = 1;

//         swapped = false;
//         for (int i = 0; i + gap < n; ++i) {
//             if (array[i] > array[i + gap]) {
//                 swap(array[i], array[i + gap]);
//                 swapped = true;
//             }
//         }
//     }
// }



#include "Eval.h"

int main(int argc, char** argv) {
    return runEvaluation("combSort", argc, argv, combSort);
}

/*
==================== combSort Evaluation ====================
ListType       Iter    Time (avg ms)    Memory (avg KB)   Valid     
--------------------------------------------------------------------
ascending      2       153.50           2024.00           ✔️    
descending     2       145.50           2024.00           ✔️    
partial        2       140.00           2024.00           ✔️    
random         2       135.00           2024.00           ✔️    
====================================================================
Results saved to: result/2025-04-05_combSort_10000.csv
*/

/*
without useless bubble sort
==================== combSort Evaluation ====================
ListType       Iter    Time (avg ms)    Memory (avg KB)   Valid     
--------------------------------------------------------------------
ascending      2       1.00             2024.00           ✔️    
descending     2       1.00             2024.00           ✔️    
partial        2       4.00             2024.00           ✔️    
random         2       6.50             2024.00           ✔️    
====================================================================
Results saved to: result/2025-04-05_combSort_10000.csv
*/

/*
with 1.27~~ gap
==================== combSort Evaluation ====================
ListType       Iter    Time (avg ms)    Memory (avg KB)   Valid     
--------------------------------------------------------------------
ascending      2       0.50             2052.00           ✔️    
descending     2       1.00             2052.00           ✔️    
partial        2       1.00             2052.00           ✔️    
random         2       5.50             2052.00           ✔️    
====================================================================
Results saved to: result/2025-04-05_combSort_10000.csv
*/

/*
with decreasing gap
==================== combSort Evaluation ====================
ListType       Iter    Time (avg ms)    Memory (avg KB)   Valid     
--------------------------------------------------------------------
ascending      2       1.00             2020.00           ✔️    
descending     2       2.00             2020.00           ✔️    
partial        2       17.50            2020.00           ✔️    
random         2       60.00            2020.00           ✔️    
====================================================================
Results saved to: result/2025-04-05_combSort_10000.csv
*/