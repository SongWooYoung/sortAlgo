#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

int up(vector<int>& array, int left, int right) { // 0 1 2-3  4-7   8-15 최초에만 사용
    if (left == 1) return 1;
    for (int i = left; i <= right; i++) {
        if (array.at(i/2) > array.at(i)) array.at(i/2) = array.at(i); 
    }
    int n = up(array, left/2, left-1);
    if (array.at(2 * n) == array.at(n))     return 2 * n;
    else                                    return 2 * n + 1;
}

int update(vector<int>& array, int minIdx) {
    int idx = minIdx;
    array.at(idx) = INT_MAX;

    // 부모 노드 업데이트
    while (idx > 1) {
        int sibling = (idx % 2 == 0) ? idx + 1 : idx - 1;
        int parent = idx / 2;

        if (sibling < array.size() && array.at(idx) < array.at(sibling))
            array.at(parent) = array.at(idx);
        else if (sibling < array.size())
            array.at(parent) = array.at(sibling);
        else
            array.at(parent) = array.at(idx);  // sibling이 없을 수도 있음

        idx = parent;
    }

    // 루트부터 내려가서 현재 최소값 인덱스 찾기
    int n = 1;
    while (2 * n < array.size()) {
        if (array.at(2 * n) <= array.at(2 * n + 1))
            n = 2 * n;
        else
            n = 2 * n + 1;
    }
    return n;
}


vector<int> TSort(vector<int>& data) {
    // list를 확장 -> 2^k개 
    int originalLen = data.size(); // 원래 길이 저장
    int len = data.size();
    int padNum = 1;
    while(padNum < len) padNum *= 2;
    for (int i = len; i < padNum; i++) data.push_back(INT_MAX);
    len = data.size();

    //
    vector<int> newList(2 * len);
    for (int i = 0; i < len; i++) newList.at(i) = INT_MAX; // 
    for (int i = 0; i < len; i++) newList.at(len + i) = data.at(i); // 

    // up -> 각 홀수번째와 짝수번째를 비교해서 더 작은 값 올기
    // update () -> 최소값을 찾고 변경했으면 해당 인덱스만 변경 후 비교교
    // root에 도달한값 result vector에 push_back => 해당 자리 INT_MAX로 채우고 다시 up진행
    vector<int> result;
    int minIdx = up(newList, (int) len, (int) len*2-1);
    result.push_back(newList.at(minIdx));

    for (int i = 0 ; i < len-1; i++) {
        int n = update(newList, minIdx);
        result.push_back(newList.at(1)); 
        minIdx = n;
    }

    while (result.size() > originalLen) result.pop_back();
    return result;
}


int main() {
    vector<int> data = {10, 4, 3, 7, 9, 6, 5, 1, 100, 83, 27, 2, 11};
    vector<int> result = TSort(data);

    for (int i = 0 ; i < result.size(); i++) {
        cout << result.at(i) << endl;
    }

    return 0;
}