#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
size_t binarySearch(const vector<pair<int, char>>& array, size_t *lastIndex, int input) {
    size_t left = 0, right = *lastIndex;

    while (left < right) {
        size_t mid = (left + right) / 2;
        size_t midValid = mid;
        bool found = false;
        if (array[mid].second == 'X') {
            // Search left
            size_t l = mid;
            while (l > left && l < array.size()) {
                l--;
                if (array[l].second == 'O') {
                    midValid = l;
                    found = true;
                    break;
                }
            }
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
            if (!found) return left;
        } else midValid = mid;
        if (array[midValid].first < input)
            left = midValid + 1;
        else
            right = midValid;
    }
    return left;
}

size_t searchingPlace(vector<pair<int,char>>& array, size_t* lastIndex, size_t currentIdx) {
    int input = array[*lastIndex].first;
    size_t left = currentIdx-1;
    size_t right = currentIdx+1;


    while(true){
        if(array[left].second == 'X') {//종료조건
            for (size_t i = left; i < currentIdx-1; i++) {
                array[i] = array[i+1];
            }
            return currentIdx-1;
        }
        if(array[right].second == 'X') {//종료조건
            for (size_t i = right; i > currentIdx; i--) {
                array[i] = array[i-1];
            } 
            return currentIdx;
        }

        if (left <= 0) {
            right++;
            continue;
        }
        if (right >= *lastIndex-1){
            left--;
            continue;
        }
        left--;
        right++;        
    } 
}

void insert(vector<pair<int, char>>& array, size_t num, size_t* lastIndex) {
    size_t n = num;
    while(n > 0) {
        int input = array.at(*lastIndex).first;
        size_t currentIdx = binarySearch(array, lastIndex, input);

        if (array.at(currentIdx).second == 'O') {
            int idxToInsert = (int) searchingPlace(array, lastIndex, currentIdx);
            array[idxToInsert] = {input, 'O'};
        } else {
            array[currentIdx] = {input, 'O'};
        }
        array.erase(array.begin() + (int)(*lastIndex));
        n--;
    }
}

void rebalancing(vector<pair<int, char>>& array, size_t* lastIndex) {
    size_t originalSize = *lastIndex;

    // 초기 단계: 한 번만 확장
    if (originalSize == 1) {
        array.insert(array.begin() + 1, {0, 'X'});
        array.insert(array.begin() + 1, {0, 'X'});
        *lastIndex += 2;
        return;
    }

    // 필요한 최종 크기 계산
    size_t newSize = array.size() + originalSize;
    array.resize(newSize, {0, 'X'}); // 전체 공간 확보

    // 뒤에서부터 기존 값을 2*i 위치로 재배치
    for (int i = (int)originalSize - 1; i >= 0; i--) {
        if (array[i].second == 'O') {
            array[2 * i] = array[i];              // 값 복사
            array[i] = {0, 'X'};                  // 원래 자리 비우기
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
            lastIndex++;
            rebalancing(array, &lastIndex);
            NumbersofNextInput  = NumbersofNextInput << 1;
            continue;
        }
        size_t remainingInputs = array.size() - lastIndex;
        if (NumbersofNextInput > remainingInputs) {
            insert(array, remainingInputs, &lastIndex);
            break;
        }
        insert(array, NumbersofNextInput, &lastIndex);
        rebalancing(array, &lastIndex);
        NumbersofNextInput  = NumbersofNextInput << 1;
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
        100, 199, 1909 , 496, 2, 3,4,5,6,6,7,9, 595, 694, 298, 793, 892, 991, 397
    };
    vector<pair<int, char>> arr2;
    for (size_t i = 0; i < data.size(); i++) {
        arr2.push_back(make_pair(data[i], 'O'));
    }

    librarySort(arr2);

    cout << arr2 << endl;

    return 0;
}