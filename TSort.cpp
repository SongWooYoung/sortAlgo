#include <iostream>
#include <vector>
#include <climits>
#include "Eval.h"

using namespace std;

// 트리 초기화 함수
void buildTTree(vector<int>& tree, int size) {
    for (int i = size - 1; i > 0; --i)
        tree[i] = min(tree[i * 2], tree[i * 2 + 1]);
}

// 값 갱신 함수
void updateTree(vector<int>& tree, int index) {
    tree[index] = INT_MAX;
    while (index > 1) {
        index /= 2;
        tree[index] = min(tree[2 * index], tree[2 * index + 1]);
    }
}

// 토너먼트 정렬 함수
vector<int> TSort(vector<int>& data) {
    int originalLen = data.size();
    int size = 1;
    while (size < originalLen) size *= 2;

    // 패딩 추가
    for (int i = data.size(); i < size; ++i)
        data.push_back(INT_MAX);

    // 트리 구성
    vector<int> tree(2 * size);
    for (int i = 0; i < size; ++i)
        tree[size + i] = data[i];

    buildTTree(tree, size);

    vector<int> result;
    for (int i = 0; i < originalLen; ++i) {
        int minVal = tree[1];
        result.push_back(minVal);

        // 최소값 인덱스 추적
        int idx = 1;
        while (idx < size) {
            if (tree[2 * idx] == tree[idx])
                idx = 2 * idx;
            else
                idx = 2 * idx + 1;
        }
        int dataIndex = idx - size;

        // 실제 데이터와 트리 모두 무효화
        data[dataIndex] = INT_MAX;
        updateTree(tree, idx);
    }

    // 결과 복사
    data = result;
    return data;
}

int main(int argc, char** argv) {
    return runEvaluation("Tournament Sort", argc, argv, TSort);
}


/*

*/

/*
==================== Tournament Sort Evaluation (size=1000000) ====================
ListType       Iter    Time (avg ms)    Memory (avg KB)   Valid     
--------------------------------------------------------------------
ascending      10      206.30           21993.20          ✔️    
descending     10      201.60           26146.00          ✔️    
partial        10      294.20           26136.00          ✔️    
random         10      378.80           26136.00          ✔️    
====================================================================
Results saved to: result/2025-04-10_Tournament Sort_1000000.csv
*/