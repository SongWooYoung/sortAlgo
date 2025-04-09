#include <iostream>
#include <vector>
#include <climits>

using namespace std;

struct element {
    int num;
    bool ishere;
};

int binarySearch(const vector<element>& result, int input, int resultLen) {
    int left = 0, right = resultLen;
    while (left < right) {
        int mid = (left + right) / 2;
        int realMid = mid;

        if (!result[realMid].ishere) {
            int l = mid - 1, r = mid + 1;
            while (true) {
                if (l < left && r >= right) {
                    realMid = -1;
                    break;
                }
                if (l >= left && result[l].ishere) {
                    realMid = l;
                    break;
                }
                if (r < right && result[r].ishere) {
                    realMid = r;
                    break;
                }
                l--; r++;
            }
        }

        if (realMid == -1) {
            right = mid;
        } else if (result[realMid].num < input) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    return left;
}

int SearchingEmpty(vector<element>& result, int cur_idx, int resultLen) {
    int left = cur_idx - 1, right = cur_idx + 1;
    while (left >= 0 && right < resultLen) {
        if (!result[left].ishere) return left;
        if (!result[right].ishere) return right;
        left--; right++;
    }
    while (right < resultLen) {
        if (!result[right].ishere) return right;
        right++;
    }
    while (left >= 0) {
        if (!result[left].ishere) return left;
        left--;
    }
    return -1;
}

bool insert(vector<int>& array, vector<element>& result, int& array_ptr, int insertCount, int resultLen, int& tailInsertCount) {
    int count = 0;
    while (array_ptr < array.size() && count < insertCount) {
        int input = array[array_ptr];
        int cur_idx = binarySearch(result, input, resultLen);
        if (cur_idx == resultLen) cur_idx--;

        if (cur_idx >= resultLen * 0.9) tailInsertCount++;

        if (!result[cur_idx].ishere) {
            result[cur_idx] = {input, true};
        } else {
            int empty = SearchingEmpty(result, cur_idx, resultLen);
            if (empty == -1) return false;

            if (input < result[cur_idx].num) {
                if (empty < cur_idx) {
                    for (int i = empty; i < cur_idx - 1; i++) {
                        result[i] = result[i + 1];
                    }
                    result[cur_idx - 1] = {input, true};
                } else {
                    for (int i = empty; i > cur_idx; i--) {
                        result[i] = result[i - 1];
                    }
                    result[cur_idx] = {input, true};
                }
            } else {
                if (empty < cur_idx) {
                    for (int i = empty; i < cur_idx; i++) {
                        result[i] = result[i + 1];
                    }
                    result[cur_idx] = {input, true};
                } else {
                    for (int i = empty; i > cur_idx + 1; i--) {
                        result[i] = result[i - 1];
                    }
                    result[cur_idx + 1] = {input, true};
                }
            }
        }
        array_ptr++;
        count++;
    }
    return true;
}

void rebalance(vector<element>& result, int& resultLen, int insertCount, int tailInsertCount) {
    float ratio = (float)tailInsertCount / insertCount;
    if (ratio > 0.85) {
        int extra = resultLen / 2 + 1;
        result.resize(resultLen + extra, {INT_MIN, false});
        resultLen += extra;
        return;
    }

    int newLen = resultLen * 2 + 1;
    if ((int)result.size() < newLen) {
        result.resize(newLen, {INT_MIN, false});
    }

    if (resultLen == 1) {
        result[1] = {INT_MIN, false};
        result[2] = {INT_MIN, false};
    } else {
        for (int i = resultLen - 1; i > 0; i--) {
            result[2 * i]     = result[i];
            result[2 * i + 1] = {INT_MIN, false};
            result[i]         = {INT_MIN, false};
        }
    }
    resultLen = newLen;
}

void deleteBlanks(const vector<element>& result, vector<int>& array) {
    array.clear();
    for (const auto& e : result) {
        if (e.ishere) array.push_back(e.num);
    }
}

void librarySort(vector<int>& array) {
    if (array.empty()) return;
    vector<element> result(array.size() * 2);
    result[0] = {array[0], true};

    int insertCount = 1;
    int array_ptr = 1;
    int resultLen = 1;

    rebalance(result, resultLen, 1, 0);
    insertCount *= 2;

    while (insertCount < (int)array.size()) {
        int tailInsertCount = 0;
        insert(array, result, array_ptr, insertCount, resultLen, tailInsertCount);
        rebalance(result, resultLen, insertCount, tailInsertCount);
        insertCount *= 2;
    }

    int remain = array.size() - insertCount / 2;
    int dummy = 0;
    insert(array, result, array_ptr, remain, resultLen, dummy);

    deleteBlanks(result, array);
}

#include "Eval.h"
int main(int argc, char** argv) {
    return runEvaluation("library Sort", argc, argv, librarySort);
}

/*
==================== library Sort Evaluation ====================
ListType       Iter    Time (avg ms)    Memory (avg KB)   Valid     
--------------------------------------------------------------------
ascending      1       9741.00          4096.00           ✔️    
descending     1       8185.00          5780.00           ✔️    
partial        1       4196.00          8876.00           ✔️    
random         1       49.00            8876.00           ✔️    
====================================================================
Results saved to: result/2025-04-06_library Sort_100000.csv
*/