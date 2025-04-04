#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int binarySearch(vector<int>& array, int l_idx, int lim, int targetVal) {
    while (l_idx < lim) {
        int mid = (l_idx + lim) / 2;
        if (array[mid] < targetVal)
            l_idx = mid + 1;
        else
            lim = mid;
    }
    return l_idx;
}

int galloping(vector<int>& array, vector<int>& merged, int i, int j, int lim) {
    if (i < j){ // left -> lim = Rstart;
        return binarySearch(array, i, lim, array[j]);
    }
          // right -> lim = Mend;
    return binarySearch(array, j, lim, array[i]);
}

void merge(vector<int>& array, vector<int>& runNum_list, vector<int>& run_start_list, int left, int right) {

    // cout << "runNum_list_before_merge : ";
    // for (int i : runNum_list) cout << i << " ";
    // cout << endl;

    int Llen = runNum_list[left];
    int Rlen = runNum_list[right];
    int Ldir = runNum_list[left + 1];
    int Rdir = runNum_list[right + 1];

    int Lstart = run_start_list[left / 2];
    int Rstart = Lstart + Llen;
    int Mend = Rstart + Rlen;

    if (Ldir == -1)
        reverse(array.begin() + Lstart, array.begin() + Rstart);
    if (Rdir == -1)
        reverse(array.begin() + Rstart, array.begin() + Mend);

    vector<int> merged;
    int i = Lstart, j = Rstart;
    int consec_L = 0, consec_R = 0;
    
    while (i < Rstart && j < Mend) {
        if (consec_R >= 7) {
            int next_j = galloping(array, merged, j, i, Mend);
            while (j < next_j) merged.push_back(array[j++]);
            consec_L = 0;
            consec_R = 0;
            continue;
        }

        if (consec_L >= 7) {
            int next_i = galloping(array, merged, i, j, Rstart);
            while (i < next_i) merged.push_back(array[i++]);
            consec_L = 0;
            consec_R = 0;
            continue;
        }
        if (array[i] <= array[j]) {
            merged.push_back(array[i++]);
            consec_L++;
            consec_R = 0;
        } 
        else if (array[i] > array[j]) {
            merged.push_back(array[j++]);
            consec_R++;
            consec_L = 0;
        }
    }
    while (i < Rstart) {merged.push_back(array[i++]);}
    while (j < Mend)   merged.push_back(array[j++]);

    copy(merged.begin(), merged.end(), array.begin() + Lstart);

    runNum_list[left] = Llen + Rlen;
    runNum_list[left + 1] = 1;
    runNum_list.erase(runNum_list.begin() + right, runNum_list.begin() + right + 2);
    run_start_list[left / 2] = Lstart;
    run_start_list.erase(run_start_list.begin() + right / 2);

    // cout << "runNum_list_after_merge : ";
    // for (int i : runNum_list) cout << i << " ";
    // cout << endl;
}

void merge_collapse_force(vector<int>& array, vector<int>& runNum_list, vector<int>& run_start_list) {
    while (runNum_list.size() > 3) {  // sentinel 제외하고 2개 이상의 run이 있을 때
        int len = runNum_list.size();

        int A = runNum_list[len - 4];
        int B = runNum_list[len - 2];

        int left = len - 4;
        int right = len - 2;
        int merge_start_index = run_start_list[run_start_list.size() - 2]; // 두 번째 마지막 run의 시작점

        merge(array, runNum_list, run_start_list, left, right);
    }
}

void merge_collapse(vector<int>& array, vector<int>& runNum_list, vector<int>& run_start_list, bool is_final = false) {
    while (true) {
        int len = (int) runNum_list.size();
        int num = (len - 1) / 2;

        if (num <= 1) return;

        int left, right;

        if (num >= 3) {
            int A = runNum_list[len - 6];
            int B = runNum_list[len - 4];
            int C = runNum_list[len - 2];
            bool condA = A <= B + C;
            bool condB = B <= C;

            if (!(condA || condB)) return;

            if (condA && (!condB || A < C)) {
                left = len - 6;
                right = len - 4;
            } else {
                left = len - 4;
                right = len - 2;
            }
        } else if (num == 2) {
            int A = runNum_list[len - 4];
            int B = runNum_list[len - 2];

            if (!is_final && A > B) return;

            left = len - 4;
            right = len - 2;
        } else return;

        merge(array, runNum_list, run_start_list, left, right);
    }
}

vector<int> timSort(vector<int>& array) {
    int order = 0;
    int elsinRun = 0;
    int len = (int) array.size();
    vector<int> runNum_list;
    vector<int> run_start_list;
    runNum_list.push_back(-1); // sentinel

    for (int i = 0; i < len; i++) {
        if (elsinRun == 0) {
            run_start_list.push_back(i);
            elsinRun++;
            //cout << "current Index: " << i << endl;
            continue;
        }
        if (elsinRun == 1 && order == 0) {
            order = (array[i - 1] <= array[i]) ? 1 : -1;
            elsinRun++;
            //cout << "current Index: " << i << endl;
            continue;
        }
        if ((order == 1 && array[i - 1] <= array[i]) || (order == -1 && array[i - 1] > array[i])) {
            elsinRun++;
            //cout << "current Index: " << i << endl;
            continue;
        }
        runNum_list.push_back(elsinRun);
        runNum_list.push_back(order);
        merge_collapse(array, runNum_list, run_start_list);
        elsinRun = 1;
        order = 0;
        run_start_list.push_back(i);
        //cout << "current Index: " << i << endl;

    }
    runNum_list.push_back(elsinRun);
    runNum_list.push_back(order);
    merge_collapse(array, runNum_list, run_start_list, true);
    // cout << "runNum_list_last : ";
    // for (int i : runNum_list) cout << i << " ";
    // cout << endl;

    merge_collapse_force(array, runNum_list, run_start_list);

    return array;
}

// #include <random>


// vector<int> generateRandomNumbers(int count, int minVal = 0, int maxVal = 9999) {
//     vector<int> result;
//     result.reserve(count);

//     // 랜덤 엔진 및 분포 설정
//     random_device rd;                         // 시드
//     mt19937 gen(rd());                        // Mersenne Twister 엔진
//     uniform_int_distribution<> dist(minVal, maxVal); // 균등 분포

//     for (int i = 0; i < count; ++i) {
//         result.push_back(dist(gen));
//     }

//     return result;
// }


// int main() {
//     vector<int> data = {1325, 24, 443, 53, 15, 6, 77, 7, 6, 5, 76, 5, 56, 6, 5, 5, 7, 6, 89, 8, 7, 6, 5, 44, 35346, 62, 6, 354, 35, 345};
//     vector<int> sorted_data = timSort(data);
//     for (int i : sorted_data) cout << i << " ";
//     cout << endl;

//     if (is_sorted(sorted_data.begin(), sorted_data.end())) {
//         cout << "✅ 정렬 성공!" << endl;
//     } else {
//         cout << "❌ 정렬 실패..." << endl;
//     }

//     cout << "===============================================================================================" << endl;
//     vector<int> array = generateRandomNumbers(100);
//     vector<int> sorted_array = timSort(array);

//     for (int i : sorted_array) cout << i << " ";
//     cout << endl;
//     if (is_sorted(sorted_array.begin(), sorted_array.end())) {
//         cout << "✅ 정렬 성공!" << endl;
//     } else {
//         cout << "❌ 정렬 실패..." << endl;
//     }

//     return 0;
// }
