#include <iostream>
#include <vector>
#include <climits>

using namespace std;

// 트리 초기화 함수 (한번만 수행)
void buildTournamentTree(vector<int>& tree, int size) {
    for (int i = size - 1; i > 0; --i)
        tree[i] = min(tree[i * 2], tree[i * 2 + 1]);
}

// 값 갱신 함수 (최솟값 제거 후 트리 업데이트)
void updateTree(vector<int>& tree, int index) {
    tree[index] = INT_MAX;
    while (index > 1) {
        index /= 2;
        tree[index] = min(tree[2 * index], tree[2 * index + 1]);
    }
}

// 토너먼트 정렬 메인 함수
vector<int> TSort(vector<int>& data) {
    int originalLen = data.size();
    int size = 1;
    while (size < originalLen) size *= 2; // 2의 거듭제곱으로 맞춤

    // 패딩 추가
    for (int i = data.size(); i < size; ++i)
        data.push_back(INT_MAX);

    // 트리 구성 (인덱스 1 ~ 2*size)
    vector<int> tree(2 * size);
    for (int i = 0; i < size; ++i)
        tree[size + i] = data[i];

    buildTournamentTree(tree, size);

    vector<int> result;
    for (int i = 0; i < size; ++i) {
        result.push_back(tree[1]); // 현재 최소값 추가

        // 최소값 위치 찾기
        int idx = 1;
        while (idx < size) {
            if (tree[2 * idx] == tree[idx]) idx = 2 * idx;
            else idx = 2 * idx + 1;
        }
        updateTree(tree, idx); // 해당 인덱스를 제거
    }

    // 패딩 제거
    while (result.size() > originalLen)
        result.pop_back();

    return result;
}

// // 테스트용 메인
// int main() {
//     vector<int> data = {10, 4, 3, 7, 9, 6, 5, 1, 100, 83, 27, 2, 11};
//     vector<int> result = TSort(data);

//     for (int x : result)
//         cout << x << " ";
//     cout << endl;
//     return 0;
// }