#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>
#include "Eval.h"

using namespace std;

struct Run {
    int start;
    int length;
    int order; // 1: ascending, -1: descending
};

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

vector<int> timSort(vector<int>& array) {
    vector<Run> runs;
    int order = 0, len = array.size(), elsinRun = 0;

    for (int i = 0; i < len; ++i) {
        if (elsinRun == 0) {
            runs.push_back({i, 1, 0});
            elsinRun++;
            continue;
        }
        if (elsinRun == 1 && order == 0) {
            order = (array[i - 1] <= array[i]) ? 1 : -1;
            runs.back().order = order;
            runs.back().length++;
            elsinRun++;
            continue;
        }
        if ((order == 1 && array[i - 1] <= array[i]) || (order == -1 && array[i - 1] > array[i])) {
            runs.back().length++;
            elsinRun++;
            continue;
        }
        merge_collapse(array, runs);
        runs.push_back({i, 1, 0});
        order = 0;
        elsinRun = 1;
    }
    merge_collapse(array, runs, true);
    merge_collapse_force(array, runs);
    return array;
}

#include "Eval.h"

int main(int argc, char** argv) {
    return runEvaluation("TimSort", argc, argv, timSort);
}