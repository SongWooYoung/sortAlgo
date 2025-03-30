#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
size_t binarySearch(const vector<pair<int, char>>& array, size_t *lastIndex, int input) {
    size_t left = 0, right = *lastIndex;

    while (left < right) {
        size_t mid = (left + right) / 2;

        // Skip 'X' by checking nearest valid 'O'
        size_t midValid = mid;
        bool found = false;

        if (array[mid].second == 'X') {
            // Search left
            size_t l = mid;
            while (l > left) {
                l--;
                if (array[l].second == 'O') {
                    midValid = l;
                    found = true;
                    break;
                }
            }

            // Search right if left failed
            if (!found) {
                size_t r = mid;
                while (r + 1 < right) {
                    r++;
                    if (array[r].second == 'O') {
                        midValid = r;
                        found = true;
                        break;
                    }
                }
            }

            if (!found) {
                // 전체가 빈칸이면 그냥 삽입 지점 반환
                return left;
            }
        } else {
            midValid = mid;
        }

        if (array[midValid].first < input)
            left = midValid + 1;
        else
            right = midValid;
    }
    return left;
}


void insert(vector<pair<int, char>>& array, size_t num, size_t* lastIndex) { // array(정렬된 부분분) 크기 안변함
    // array는 현재 rebalancing이 된 상태라 가정
    // 근데 만약 들어오는 개수가 1개면 이미 정렬되어 있다 가정 => 위에서 처리리

    size_t n = num;
    while(n > 0) {

        int input = array.at(*lastIndex).first;
        //cout << "FUCK YOU" << endl;
        size_t currentIdx = binarySearch(array, lastIndex, input);

        if (array.at(currentIdx).second == 'X') {
            array.at(currentIdx) = {input, 'O'};
        }
        else {
            size_t wheretoPut = currentIdx+1;
            while(true) {
                if (wheretoPut == *lastIndex - 1) {
                    array.insert(array.begin() + wheretoPut, make_pair(0, 'X'));
                    *lastIndex = *lastIndex + 1;
                    break;
                }
                if (array.at(wheretoPut).second == 'X') break;
                wheretoPut++;
            } 
            array.at(wheretoPut).second = 'O';
            rotate(array.begin() + currentIdx, array.begin() + wheretoPut, array.begin() + wheretoPut + 1);
            array.at(currentIdx).first = input;
        }
        array.erase(array.begin() + (int)(*lastIndex));

        // for (size_t i = 0; i < *lastIndex; i++) {
        //     cout <<"(" <<array.at(i).first<< ", " << array.at(i).second << ")";
        // }
        // cout << endl;
        n--;
    }
}

void rebalancing(vector<pair<int, char>>& array, size_t* lastIndex) {

    if (*lastIndex == 1) {
        array.insert(array.begin()+1, make_pair<int, char> (0,'X'));
        array.insert(array.begin()+1, make_pair<int, char> (0,'X'));
        *lastIndex += 2;
        return;
    }
    // lastIndex부터 빈칸을 lastindex+1개 만큼 만들어줌
    // lastIndex-1의 원소부터 내려가면서 second가 'O'면 index 두배에 집어넣기
    for (size_t i = 0; i < *lastIndex+1; i++) {
        array.insert(array.begin()+*lastIndex, make_pair<int, char>(0,'X'));
    }
    for (int i = (int) *lastIndex; i > 0; i--) {
        if (array.at(i).second == 'O') {
            array.at(2 * i).first   = array.at(i).first;
            array.at(2 * i).second  = 'O';
            array.at(i).second      = 'X';
            array.at(i).first       =  0;
        }
    }
    *lastIndex = *lastIndex * 2 + 1;
}

void deleteBlank(vector<pair<int, char>>& array) {
    for (size_t i = 0; i < array.size(); ) {
        if (array[i].second == 'X') {
            array.erase(array.begin() + i);
        } else {
            i++; //삭제하면 증가시키지말아야함...
        }
    }
}

void librarySort(vector<pair<int, char>>& array) {
    size_t NumbersofNextInput = 1;
    size_t lastIndex = 0; // 정렬된 부분의 array 크기 추적
    while (true) {
        if (lastIndex == 0) {
            cout << "first" << endl;
            lastIndex++;
            rebalancing(array, &lastIndex);
            NumbersofNextInput  = NumbersofNextInput << 1;
            continue;
        }
        size_t remainingInputs = array.size() - lastIndex;
        if (NumbersofNextInput > remainingInputs) {
            cout << "LAST" << endl;
            insert(array, remainingInputs, &lastIndex);
            break;
        }
        cout << "WeAre PLAYING" << endl;
        insert(array, NumbersofNextInput, &lastIndex);
        cout << "After insertion" << endl;
        rebalancing(array, &lastIndex);
        cout << "After rebal" << endl;
        NumbersofNextInput  = NumbersofNextInput << 1;
        cout << "After increaseNNI" << endl;

    }
    deleteBlank(array);
}

ostream& operator<<(ostream& os, const vector<pair<int, char>> array) {
    for (const auto& set : array) os << set.first << " ";
    cout << endl;
    return os;
}

#include <random>   // modern C++ random
using namespace std;

vector<int> generateRandomNumbers(int count, int minVal = 0, int maxVal = 9999) {
    vector<int> result;
    result.reserve(count);

    // 랜덤 엔진 및 분포 설정
    random_device rd;                         // 시드
    mt19937 gen(rd());                        // Mersenne Twister 엔진
    uniform_int_distribution<> dist(minVal, maxVal); // 균등 분포

    for (int i = 0; i < count; ++i) {
        result.push_back(dist(gen));
    }

    return result;
}

int main() {
    
    vector<int> array = generateRandomNumbers(1000);

    vector<pair<int, char>> arr1;
    for (size_t i = 0; i < array.size(); i++) {
        arr1.push_back(make_pair(array[i], 'O'));
    }

    librarySort(arr1);
    cout << arr1 << endl;
    cout << "=================================================================================================" << endl;

    vector<int> data = {
        100, 199, 298, 397, 496, 595, 694, 793, 892, 991,
        1090, 1189, 1288, 1387, 1486, 1585, 1684, 1783, 1882, 1981,
        2080, 2179, 2278, 2377, 2476, 2575, 2674, 2773, 2872, 2971,
        3070, 3169, 3268, 3367, 3466, 3565, 3664, 3763, 3862, 3961,
        4060, 4159, 4258, 4357, 4456, 4555, 4654, 4753, 4852, 4951,
        5050, 5149, 5248, 5347, 5446, 5545, 5644, 5743, 5842, 5941,
        6040, 6139, 6238, 6337, 6436, 6535, 6634, 6733, 6832, 6931,
        7030, 7129, 7228, 7327, 7426, 7525, 7624, 7723, 7822, 7921,
        8020, 8119, 8218, 8317, 8416, 8515, 8614, 8713, 8812, 8911,
        9010, 9109, 9208, 9307, 9406, 9505, 9604, 9703, 9802, 9901,
    };
    vector<pair<int, char>> arr2;
    for (size_t i = 0; i < data.size(); i++) {
        arr2.push_back(make_pair(data[i], 'O'));
    }
    librarySort(arr2);

    cout << arr2 << endl;

    return 0;
}