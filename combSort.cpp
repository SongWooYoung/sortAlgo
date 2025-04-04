#include <iostream>
#include <vector>
using namespace std;

void combSort(vector<int>& array) {
    int gap = array.size() / 2;
    while (gap > 1) {
        for (size_t i = 0; i + gap < array.size(); ++i) {
            if (array[i] > array[i + gap]) {
                swap(array[i], array[i + gap]);
            }
        }
        gap = (gap / 1.3);
    }

    // 어느 정도 정렬됨

    for (size_t q = array.size()- 1; q > 0; --q) {
        for (size_t i = 0; i < q; ++i) {
            if (array[i] > array[i + 1]) {
                swap(array[i], array[i + 1]);
            }
        }
    }
}

#include "Eval.h"

int main(int argc, char** argv) {
    return runEvaluation("combSort", argc, argv, combSort);
}