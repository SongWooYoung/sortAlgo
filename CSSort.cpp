#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 성능저하의 원인
// vector.at() -> vecotr[i]
// LeftRight-> logic이 너무 복잡해지는 문제 

// void CSSort(vector<int>& array) {
//     bool LeftorRight = true; //true -> left / false -> right
//     size_t len = array.size();
//     size_t Llimit = 0;
//     size_t Rlimit = len-1;

//     if(array.at(Llimit) >= array.at((Rlimit + Rlimit)/2) && array.at((Rlimit + Rlimit)/2) >= array.at(Rlimit))
//         LeftorRight = false;
//     //내림차순 해결해 보려고 넣어지만 다른 예제를 10퍼 더 빨리 해결할뿐 24번째 줄이 오름차순을 정하고 있어 불가능...

//     while(Llimit < Rlimit) {
//         // swap이 발생하지 않으면 while 탈출 필요
//         bool occurSwap = false;

//         if (LeftorRight == true) {
//             for(size_t i = Llimit; i < Rlimit; i++) {
//                 if (array.at(i) > array.at(i+1)){
//                     swap(array.at(i), array.at(i+1));
//                     occurSwap = true;
//                 }
//             }
//             Rlimit--;
//             LeftorRight = false;
//         }

//         else {
//             for(size_t i = Rlimit; i > Llimit; i--) {
//                 if (array.at(i) < array.at(i-1)){
//                     swap(array.at(i), array.at(i-1));
//                     occurSwap = true;
//                 }
//             }
//             Llimit++;
//             LeftorRight = true;
//         }

//         if (occurSwap == false) break;
//     }
// }


void CSSort(vector<int>& array) {
    bool swapped = true;
    size_t left = 0;
    size_t right = array.size() - 1;

    while (swapped) {
        swapped = false;

        // left to right
        for (size_t i = left; i < right; i++) {
            if (array[i] > array[i + 1]) {
                swap(array[i], array[i + 1]);
                swapped = true;
            }
        }

        if (!swapped) break;
        swapped = false;
        right--;

        // right to left pass + 내림차순 확인
        bool descendingLikely = true;

        for (size_t i = right; i > left; i--) {
            if (array[i] < array[i - 1]) {
                swap(array[i], array[i - 1]);
                swapped = true;
            }
            else descendingLikely = false;
        }
        left++;

        // 내림차순이면 대칭 정렬 (양쪽에서 중앙까지 교환)
        if (descendingLikely) {
            size_t mid = (left + right) / 2;
            for (size_t i = 0; i <= mid - left; i++) {
                swap(array[left + i], array[right - i]);
            }
            break;  // 정렬 완료 가능성 높으므로 종료
        }
    }
}


#include "Eval.h"

int main(int argc, char** argv) {
    return runEvaluation("CSSort", argc, argv, CSSort);
}

/*
first
==================== CSSort Evaluation ====================
ListType       Iter    Time (avg ms)    Memory (avg KB)   Valid     
--------------------------------------------------------------------
ascending      2       0.00             2020.00           ✔️    
descending     2       2514.50          2020.00           ✔️    
partial        2       670.50           2020.00           ✔️    
random         2       1578.50          2020.00           ✔️    
====================================================================
Results saved to: result/2025-04-05_CSSort_10000.csv
*/

/*
after optimization
==================== CSSort Evaluation ====================
ListType       Iter    Time (avg ms)    Memory (avg KB)   Valid     
--------------------------------------------------------------------
ascending      2       0.00             2052.00           ✔️    
descending     2       600.50           2052.00           ✔️    
partial        2       188.50           2052.00           ✔️    
random         2       605.00           2052.00           ✔️    
====================================================================
Results saved to: result/2025-04-05_CSSort_10000.csv
*/

/*
descending 추가가
==================== CSSort Evaluation ====================
ListType       Iter    Time (avg ms)    Memory (avg KB)   Valid     
--------------------------------------------------------------------
ascending      5       0.00             2020.00           ✔️    
descending     5       0.00             2020.00           ✔️    
partial        5       141.40           2020.00           ✔️    
random         5       432.20           2020.00           ✔️    
====================================================================
Results saved to: result/2025-04-05_CSSort_10000.csv
*/

