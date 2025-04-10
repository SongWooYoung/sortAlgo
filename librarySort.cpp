#include <iostream>
#include <vector>
#include <climits>

using namespace std;

struct element {
    int num;
    bool ishere;
};

// binarySearch (lower_bound + 빈칸 선형 보정)
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

// 주변 빈칸 탐색
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

// 삽입 함수
void insert(vector<int>& array, vector<element>& result, int& array_ptr, int insertCount, int resultLen) {
    int count = 0;
    while (array_ptr < array.size() && count < insertCount) {
        int input = array[array_ptr];
        int cur_idx = binarySearch(result, input, resultLen);
        if (cur_idx == resultLen) cur_idx--;

        if (!result[cur_idx].ishere) {
            result[cur_idx] = {input, true};
        } else {
            int empty = SearchingEmpty(result, cur_idx, resultLen);
            if (empty == -1) return; // 공간이 없다면 skip

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
}

// rebalance 함수
void rebalance(vector<element>& result, int& resultLen) {
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

// 빈빈칸 제거 후 결과 복사
void deleteBlanks(const vector<element>& result, vector<int>& array) {
    array.clear();
    for (const auto& e : result) {
        if (e.ishere) array.push_back(e.num);
    }
}

// 메인 Library Sort
void librarySort(vector<int>& array) {
    if (array.empty()) return;
    vector<element> result(array.size() * 2); // 충분한 초기 크기
    result[0] = {array[0], true};

    int insertCount = 1;
    int array_ptr = 1;
    int resultLen = 1;

    rebalance(result, resultLen);
    insertCount *= 2;

    while (insertCount < (int)array.size()) {
        insert(array, result, array_ptr, insertCount, resultLen);
        rebalance(result, resultLen);
        insertCount *= 2;
    }

    int remain = array.size() - insertCount / 2;
    insert(array, result, array_ptr, remain, resultLen);

    deleteBlanks(result, array);
}



#include "Eval.h"
int main(int argc, char** argv) {
    return runEvaluation("library Sort", argc, argv, librarySort);
}



