#include <iostream>
#include <vector>

using namespace std;

struct Node {
    int key;
    vector<int> history;
};

int compare(int a, int b, vector<Node>& nodes) {
    if (nodes[a].key <= nodes[b].key) {
        nodes[a].history.push_back(b);
        return a;
    } else {
        nodes[b].history.push_back(a);
        return b;
    }
}

// Tournament 정렬의 비교 단계: 인접 쌍끼리 비교해서 승자를 올림
int tournamentPhase(vector<Node>& nodes) {
    vector<int> current;
    for (int i = 0; i < nodes.size(); ++i) current.push_back(i);

    while (current.size() > 1) {
        vector<int> next;
        for (int i = 0; i + 1 < current.size(); i += 2) {
            int winner = compare(current[i], current[i+1], nodes);
            next.push_back(winner);
        }
        if (current.size() % 2 == 1) next.push_back(current.back()); // 부전승
        current = next;
    }
    return current[0]; // 최종 승자 인덱스 반환
}

vector<int> TSort(vector<Node>& array) {
    int winnerIndex = tournamentPhase(array);
    cout <<"winner index: "<<winnerIndex << endl;

    return ;
}

int main() {

    vector<int> data = {10, 4, 3, 7, 9, 6, 5, 1};
    vector<Node> nodes;
    for (int i = 0; i < data.size(); ++i) {
        nodes.push_back({data[i], {}});
    }
    TSort(nodes);


    return 0;
}