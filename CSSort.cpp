#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


void CSSort(vector<int>& array) {
    bool LeftorRight = true; //true -> left / false -> right
    size_t len = array.size();
    size_t Llimit = 0;
    size_t Rlimit = len-1;
    while(Llimit < Rlimit) {
        // swap이 발생하지 않으면 while 탈출 필요요
        bool occurSwap = false;
        if (LeftorRight == true) {
            for(size_t i = Llimit; i < Rlimit; i++) {
                if (array.at(i) > array.at(i+1)){
                    swap(array.at(i), array.at(i+1));
                    occurSwap = true;
                }
            }
            Rlimit--;
            LeftorRight = false;
        }
        else {
            for(size_t i = Rlimit; i > Llimit; i--) {
                if (array.at(i) < array.at(i-1)){
                    swap(array.at(i), array.at(i-1));
                    occurSwap = true;
                }
            }
            Llimit++;
            LeftorRight = true;
        }
        if (occurSwap == false) break;
    }
}


// int main() {

//     vector<int> data = {5, 3, 8, 6, 2, 7, 4, 1};
//     CSSort(data);
//     for (int num : data) {
//         cout << num << " ";
//     }


//     return 0;
// }