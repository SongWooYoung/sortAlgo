#include <iostream>
#include <vector>
#include <queue>
#include "Eval.h"
using namespace std;


void runBasedSort(vector<int>& array) {
    vector<vector<int>> runs;
    size_t n = array.size();
    if (n == 0) return;

    // Step 1: Detect runs (strictly ascending sequences)
    size_t i = 0;
    while (i < n) {
        vector<int> run;
        run.push_back(array[i]);
        while (i + 1 < n && array[i] <= array[i + 1]) {
            i++;
            run.push_back(array[i]);
        }
        runs.push_back(run);
        i++;
    }

    // Step 2: Merge all runs
    // Use k-way merge with priority queue
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    vector<size_t> indices(runs.size(), 0);
    vector<int> result;

    // Initialize PQ
    for (int r = 0; r < runs.size(); r++) {
        pq.push({runs[r][0], r});
    }

    while (!pq.empty()) {
        auto [val, from] = pq.top(); pq.pop();
        result.push_back(val);
        if (++indices[from] < runs[from].size()) {
            pq.push({runs[from][indices[from]], from});
        }
    }
    array = result;
}

#include "Eval.h"
int main(int argc, char** argv) {
    return runEvaluation("RBsort", argc, argv, runBasedSort);  // ✨ 원하는 정렬 이름만 전달
}

/*
==================== RBsort Evaluation ====================
ListType       Iter    Time (avg ms)    Memory (avg KB)   Valid     
--------------------------------------------------------------------
ascending      1       1.00             4048.00           ✔️    
descending     1       18.00            4648.00           ✔️    
partial        1       5.00             4648.00           ✔️    
random         1       9.00             4648.00           ✔️    
====================================================================
Results saved to: result/2025-04-04_RBsort_10000.csv
*/

