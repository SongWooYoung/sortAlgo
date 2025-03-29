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
    vector<int> arr;
    return arr;
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