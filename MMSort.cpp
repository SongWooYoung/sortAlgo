#include <iostream>
#include <vector>
#include <climits>
#include <algorithm> // for std::swap
#include <cstdlib>  // for std::abs

using namespace std;

void minMaxSelectionSort(vector<int>& array) {
    size_t left = 0;
    size_t right = array.size() - 1;

    while (left < right) {
        size_t minIndex = left;
        size_t maxIndex = left;

        // Find both min and max in current range
        for (size_t i = left; i <= right; i++) {
            if (array[i] < array[minIndex]) minIndex = i;
            if (array[i] > array[maxIndex]) maxIndex = i;
        }

        // Swap min to the left
        if (minIndex != left) {
            swap(array[left], array[minIndex]);
            // If maxIndex was at left, it has moved to minIndex
            if (maxIndex == left) maxIndex = minIndex;
        }

        // Swap max to the right
        if (maxIndex != right) {
            swap(array[right], array[maxIndex]);
        }

        left++;
        if (right == 0) break; // To prevent underflow
        right--;
    }
}
#include "Eval.h"
int main(int argc, char** argv) {
    return runEvaluation("MMS", argc, argv, minMaxSelectionSort);  // ✨ 원하는 정렬 이름만 전달
}


/*
==================== MMS Evaluation ====================
ListType       Iter    Time (avg ms)    Memory (avg KB)   Valid     
--------------------------------------------------------------------
ascending      3       90.67            2020.00           ✔️    
descending     3       90.67            2020.00           ✔️    
partial        3       97.67            2020.00           ✔️    
random         3       105.33           2020.00           ✔️    
====================================================================
Results saved to: result/2025-04-09_MMS_10000.csv
*/