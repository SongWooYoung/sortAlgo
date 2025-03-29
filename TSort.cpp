#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

struct Node {
    int key;
    vector<int> history;
    int originalIndex;
};

int compare(int a, int b, vector<Node>& array) {
    if (array[a].key <= array[b].key) {
        array[a].history.push_back(b);
        return a;
    } else {
        array[b].history.push_back(a);
        return b;
    }
}

int tournamentPhase(vector<Node>& array) {
    vector<int> current;
    for (size_t i = 0; i < array.size(); ++i) current.push_back(i);

    while (current.size() > 1) {
        vector<int> next;
        for (size_t i = 0; i + 1 < current.size(); i += 2) {
            int winner = compare(current[i], current[i + 1], array);
            next.push_back(winner);
        }
        if (current.size() % 2 == 1) {
            next.push_back(current.back());
        }
        current = next;
    }

    return current[0];
}

vector<int> TSort(vector<Node> array) {
    vector<int> sorted;

    while (!array.empty()) {
        // 토너먼트 트리에서 최소값 인덱스 찾기
        int winnerIndex = tournamentPhase(array);
        int minValue = array[winnerIndex].key;
        sorted.push_back(minValue);

        // winner의 history를 순차 비교하여 다음 후보 찾기
        vector<int> candidates = array[winnerIndex].history;
        array.erase(array.begin() + winnerIndex); // 최소값 제거

        for (int i = 0; i < candidates.size(); ++i) {
            // 삭제로 인해 인덱스가 밀렸을 수 있으므로 보정
            if (candidates[i] > winnerIndex) {
                candidates[i] -= 1;
            }
        }

        // history 후보군으로 새 array 재구성
        vector<Node> newArray;
        for (int idx : candidates) {
            newArray.push_back(array[idx]);
        }

        // 나머지 요소들 추가
        for (int i = 0; i < array.size(); ++i) {
            if (find(candidates.begin(), candidates.end(), i) == candidates.end()) {
                newArray.push_back(array[i]);
            }
        }

        array = newArray;
    }

    return sorted;
}


// int main() {
//     vector<int> data = {10, 4, 3, 7, 9, 6, 5, 1};
//     vector<Node> array;
//     for (int val : data) {
//         array.push_back({val, {}, 0});
//     }

//     vector<int> result = TSort(array);

//     cout << "Sorted Result: ";
//     for (int val : result) {
//         cout << val << " ";
//     }
//     cout << endl;

//     return 0;
// }