#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct Node {
    int key;                  // value in array
    vector<int> history;      // losers' indices
};

/*
    Comparison (a, b):
        The smaller one is the winner by comparing the key values.
        The winner adds the loser's index to history.
        This comparison proceeds sequentially as a repeat sentence.

    Full proess:
        Configure the Node container with the input array.
        Tournament-style comparison and history filling.
        Create a set aligned along history like DFS at each node.
        If there are multiple sorted sets, Merge to generate the final sorted result.
*/