
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include "Eval.h"

using namespace std;

struct Run {
    int start;
    int length;
    int order; // 1: ascending, -1: descending
};

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

void extend_run_with_insertion(vector<int>& array, int start, int min_run_len) {
    int end = min((int)array.size() - 1, start + min_run_len - 1);
    insertionSort(array, start, end);
}

int exponentialBinarySearch(vector<int>& array, int start, int limit, int targetVal) {
    int bound = 1;
    while (start + bound < limit && array[start + bound] < targetVal)
        bound *= 2;

    int l = start + bound / 2;
    int r = min(start + bound, limit);

    while (l < r) {
        int mid = (l + r) / 2;
        if (array[mid] < targetVal) l = mid + 1;
        else                        r = mid;
    }
    return l;
}

int galloping(vector<int>& array, vector<int>& merged, int i, int j, int lim) {
    if (i < j)
        return exponentialBinarySearch(array, i, lim, array[j]);
    else
        return exponentialBinarySearch(array, j, lim, array[i]);
}

void merge(vector<int>& array, vector<Run>& runs, int left, int right) {
    int Lstart = runs[left].start;
    int Rstart = runs[right].start;
    int Llen = runs[left].length;
    int Rlen = runs[right].length;
    int Ldir = runs[left].order;
    int Rdir = runs[right].order;

    int Mend = Rstart + Rlen;

    if (Ldir == -1)
        reverse(array.begin() + Lstart, array.begin() + Rstart);
    if (Rdir == -1)
        reverse(array.begin() + Rstart, array.begin() + Mend);

    vector<int> merged;
    merged.reserve(Llen + Rlen); // push_back 때문에 병목

    int i = Lstart, j = Rstart;
    int consec_L = 0, consec_R = 0;

    while (i < Rstart && j < Mend) {
        if (consec_R >= 7) {
            int next_j = galloping(array, merged, j, i, Mend);
            while (j < next_j) merged.push_back(array[j++]);
            consec_L = 0;
            consec_R = 0;
            continue;
        }
        if (consec_L >= 7) {
            int next_i = galloping(array, merged, i, j, Rstart);
            while (i < next_i) merged.push_back(array[i++]);
            consec_L = 0;
            consec_R = 0;
            continue;
        }
        if (array[i] <= array[j]) {
            merged.push_back(array[i++]);
            consec_L++;
            consec_R = 0;
        } else {
            merged.push_back(array[j++]);
            consec_R++;
            consec_L = 0;
        }
    }
    while (i < Rstart) merged.push_back(array[i++]);
    while (j < Mend) merged.push_back(array[j++]);

    copy(merged.begin(), merged.end(), array.begin() + Lstart);

    runs[left].length += runs[right].length;
    runs[left].order = 1;
    runs.erase(runs.begin() + right);
}

void merge_collapse_force(vector<int>& array, vector<Run>& runs) {
    while (runs.size() > 1) {
        int left = runs.size() - 2;
        int right = runs.size() - 1;
        merge(array, runs, left, right);
    }
}

void merge_collapse(vector<int>& array, vector<Run>& runs, bool is_final = false) {
    while (true) {
        int n = runs.size();
        if (n <= 1) return;

        int left, right;
        if (n >= 3) {
            int A = runs[n - 3].length;
            int B = runs[n - 2].length;
            int C = runs[n - 1].length;
            bool condA = A <= B + C;
            bool condB = B <= C;

            if (!(condA || condB)) return;
            if (condA && (!condB || A < C)) {
                left = n - 3;
                right = n - 2;
            } else {
                left = n - 2;
                right = n - 1;
            }
        } else {
            int A = runs[n - 2].length;
            int B = runs[n - 1].length;
            if (!is_final && A > B) return;
            left = n - 2;
            right = n - 1;
        }
        merge(array, runs, left, right);
    }
}

int computeMinRun(int n) {
    int r = 0;
    while (n >= 64) {
        r |= n & 1;
        n >>= 1;
    }
    return n + r;
}

vector<int> timSort(vector<int>& array) {

    int MIN_MERGE = computeMinRun((int) array.size());

    vector<Run> runs;
    int len = array.size();

    for (int i = 0; i < len;) {
        int run_start = i;
        int run_len = 1;
        int order = 0;

        while (i + 1 < len) {
            if (array[i] < array[i + 1]) {
                if (order == 0) order = 1;
                else if (order == -1) break;
            } else if (array[i] > array[i + 1]) {
                if (order == 0) order = -1;
                else if (order == 1) break;
            }
            i++;
            run_len++;
        }

        if (order == -1) {
            reverse(array.begin() + run_start, array.begin() + run_start + run_len);
        }

        if (run_len < MIN_MERGE) {
            extend_run_with_insertion(array, run_start, MIN_MERGE);
            run_len = min(MIN_MERGE, len - run_start);
            i = run_start + run_len - 1;
        }

        runs.push_back({run_start, run_len, 1});
        i++;
        merge_collapse(array, runs);
    }

    if (!runs.empty() && runs.back().order == -1) {
        int start = runs.back().start;
        int end = start + runs.back().length;
        reverse(array.begin() + start, array.begin() + end);
        runs.back().order = 1;
    }

    merge_collapse(array, runs, true);
    merge_collapse_force(array, runs);

    return array;
}

int main(int argc, char** argv) {
    return runEvaluation("TimSort", argc, argv, timSort);
}

/*
initial 
==================== TimSort Evaluation ====================
ListType       Iter    Time (avg ms)    Memory (avg KB)   Valid     
--------------------------------------------------------------------
ascending      3       19.00            10229.33          ✔️    
descending     3       32.00            11666.67          ✔️    
partial        3       366.00           11798.67          ✔️    
random         3       710.33           11684.00          ✔️    
====================================================================
Results saved to: result/2025-04-05_TimSort_1000000.csv
*/

/*
reserve 사용
==================== TimSort Evaluation ====================
ListType       Iter    Time (avg ms)    Memory (avg KB)   Valid     
--------------------------------------------------------------------
ascending      3       5.00             10293.33          ✔️    
descending     3       16.67            11492.00          ✔️    
partial        3       159.33           11560.00          ✔️    
random         3       331.33           11560.00          ✔️    
====================================================================
Results saved to: result/2025-04-05_TimSort_1000000.csv
*/

/*
reserve + Minmerge 48
==================== TimSort Evaluation ====================
ListType       Iter    Time (avg ms)    Memory (avg KB)   Valid     
--------------------------------------------------------------------
ascending      3       8.00             10300.00          ✔️    
descending     3       15.67            11538.67          ✔️    
partial        3       174.67           11604.00          ✔️    
random         3       342.33           11604.00          ✔️    
====================================================================
Results saved to: result/2025-04-05_TimSort_1000000.csv
*/

/*
reserve + Minmerge 52
==================== TimSort Evaluation ====================
ListType       Iter    Time (avg ms)    Memory (avg KB)   Valid     
--------------------------------------------------------------------
ascending      3       4.00             10289.33          ✔️    
descending     3       16.33            11488.00          ✔️    
partial        3       193.33           11556.00          ✔️    
random         3       367.67           11556.00          ✔️    
====================================================================
Results saved to: result/2025-04-05_TimSort_1000000.csv
*/

/*
reserve + Minmerge 64
==================== TimSort Evaluation ====================
ListType       Iter    Time (avg ms)    Memory (avg KB)   Valid     
--------------------------------------------------------------------
ascending      3       3.33             10305.33          ✔️    
descending     3       14.33            11546.67          ✔️    
partial        3       165.00           11616.00          ✔️    
random         3       337.67           11616.00          ✔️    
====================================================================
Results saved to: result/2025-04-05_TimSort_1000000.csv
*/


// why it works well on the min merge 2 to the power of n??
// => I found the reason on Timsort paper-> https://github.com/python/cpython/blob/main/Objects/listsort.txt line 271

/*
Dinamic Min Merge => 큰 차이는 없는듯..? 데이터가 작아서 그럴수도도
==================== TimSort Evaluation ====================
ListType       Iter    Time (avg ms)    Memory (avg KB)   Valid     
--------------------------------------------------------------------
ascending      10      4.70             11103.20          ✔️    
descending     10      14.60            11738.40          ✔️    
partial        10      175.10           11808.00          ✔️    
random         10      346.60           11808.00          ✔️    
====================================================================
Results saved to: result/2025-04-05_TimSort_1000000.csv
*/
