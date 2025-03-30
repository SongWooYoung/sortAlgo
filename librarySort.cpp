#include <iostream>
#include <vector>

using namespace std;

void insert(vector<pair<int, char>>& array, size_t num, size_t* lastIndex) { // array(정렬된 부분분) 크기 안변함
    // array는 현재 rebalancing이 된 상태라 가정
    // 근데 만약 들어오는 개수가 1개면 이미 정렬되어 있다 가정하므로 탈출
    if (num == 1) return;
    
    size_t n = num;
    while(n > 0) {
        // 중간으로 이동(?), 빈공간이면 좌측으로 만날때까지 내려가자
        // => 채워진 자리의 원소가 주어진 값보다 크다면, 계속 내려가서 나보다 작은 값을 만나는 위치확인
        // 그 위치의 옆자리가 공백이면 채우고, 공백이 아니라면 옆에 애를 빈칸을 만날때까지 밈
        // => 채워진 자리의 원소가 주어진 값보다 작으면 오른쪽으로 이동해서 커지는 순간을 확인
        int input = array.at(*lastIndex).first;
        size_t currentIdx = (*lastIndex)/2;
        while(currentIdx > 0 &&
            (array.at(currentIdx).first > input || array.at(currentIdx).second == 'X')) {
            currentIdx--;
        }
        if (array.at(currentIdx + 1).second == 'X') {
            array.at(currentIdx + 1).first = input;
            array.at(currentIdx + 1).second = 'O';
        }
        else {
            currentIdx++;
            size_t wheretoPut = currentIdx;
            while(array.at(wheretoPut).second == 'O') {
                wheretoPut++;
            } //현재 wheretoPut은 빈곳 위치를 담음
            array.at(wheretoPut).second = 'O';
            for (int j = (int) wheretoPut-1; j > (int) currentIdx; j--) {
                array.at(j+1) = array.at(j);
            }
            array.at(currentIdx).first = array.at(*lastIndex).first;
        }
        array.erase(array.begin() + (int)(*lastIndex));
        n--;
    }
}

void rebalancing(vector<pair<int, char>>& array, size_t* lastIndex) {

    if (*lastIndex == 1) {
        array.insert(array.begin()+1, make_pair<int, char> (0,'X'));
        array.insert(array.begin()+2, make_pair<int, char> (0,'X'));
        *lastIndex += 2;
    }
    // lastIndex부터 빈칸을 lastindex+1개 만큼 만들어줌
    // lastIndex-1의 원소부터 내려가면서 second가 'O'면 index 두배에 집어넣기
    for (size_t i = 0; i < *lastIndex+1; i++) {
        array.insert(array.begin()+*lastIndex, make_pair<int, char>(0,'X'));
    }
    for (int i = (int)(*lastIndex) - 1; i > 0; i++) {
        if (array.at(i).second == 'O') {
            array.at(2 * i).first       = array.at(i).first;
            array.at(2 * i).second      = 'O';
            array.at(i).second          = 'X';
        } 
    }
    *lastIndex = *lastIndex * 2 + 1;
}

void deleteBlank(vector<pair<int, char>>& array) {
    size_t len = array.size();
    for (size_t i = 0 ; i < len; i++){
        if (array.at(i).second == 'X') array.erase(array.begin()+i);
    }
}

void librarySort(vector<pair<int, char>>& array) {
    size_t len = array.size();
    size_t NumbersofNextInput = 1;
    size_t lastIndex = 0; // 정렬된 부분의 array 크기 추적
    while (true) {
        if (NumbersofNextInput < len && (NumbersofNextInput<<1) > len) {
            insert(array, (NumbersofNextInput<<1) - NumbersofNextInput, &lastIndex);
            break;
        }
        insert(array, NumbersofNextInput, &lastIndex);
        rebalancing(array, &lastIndex);
        NumbersofNextInput  = NumbersofNextInput << 1;
    }
    deleteBlank(array);
}

ostream& operator<<(ostream& os, const vector<pair<int, char>> array) {
    for (pair<int, char> set : array) cout << set.first << " ";
    cout << endl;
    return os;
}

int main() {
    
    vector<int> array = {1, -1, 9, 6, 8, 7, -4, 50, 8, 10};
    vector<pair<int, char>> arr;
    for (size_t i : array) {
        arr.push_back(make_pair(array.at(i), 'O'));
    }

    librarySort(arr);

    cout << arr << endl;

    return 0;
}