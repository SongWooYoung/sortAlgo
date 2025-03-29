#include <iostream>
#include <vector>

using namespace std;

ostream& operator<<(ostream& os, const vector<int> array) {
    for (size_t i : array) cout << array.at(i) << " ";
    cout << endl;
    return os;
}

void insert(vector<pair<int, char>>& array, size_t num, size_t lastIndex) {
    // array는 현재 rebalancing이 된 상태라 가정
    // 근데 만약 들어오는 개수가 1개면 이미 정렬되어 있다 가정하므로 탈출
    if (num == 1) return;
    for (size_t i = 0; i < num; i++) {
        // 중간으로 이동(?), 빈공간이면 좌측으로 만날때까지 내려가자
        // => 채워진 자리의 원소가 주어진 값보다 크다면, 계속 내려가서 나보다 작은 값을 만나는 위치확인
        // 그 위치의 옆자리가 공백이면 채우고, 공백이 아니라면 옆에 애를 빈칸을 만날때까지 밈
        // => 채워진 자리의 원소가 주어진 값보다 작으면 오른쪽으로 이동해서 커지는 순간을 확인
        size_t currentIdx = (lastIndex)/2;
        while(array.at(currentIdx).first > array.at(lastIndex + i).first || array.at(currentIdx).second == 'X' ) {
            currentIdx--;
        }
        if (array.at(currentIdx).second == 'X') array.at(currentIdx).first = array.at(lastIndex + i).first;
        else {
            size_t wheretoPut = currentIdx;
            while(array.at(wheretoPut).second == 'O') {
                wheretoPut++;
            } //현재 wheretoPut은 빈곳 위치를 담음
            array.at(wheretoPut).second = 'O';
            for (size_t i = wheretoPut-1; i < currentIdx; i--) {
                array.at(i+1) = array.at(i);
            }
            array.at(currentIdx).first = array.at(lastIndex + i).first;
        }
    } 
}

void librarySort(vector<pair<int, char>>& array) {
    size_t len = array.size();
    size_t NumbersofNextInput = 1;
    size_t lastIndex = 0;
    while (true) {
        if (NumbersofNextInput < len && (NumbersofNextInput<<1) > len) {
            insert(array, (NumbersofNextInput<<1) - NumbersofNextInput, lastIndex);
            break;
        }
        insert(array, NumbersofNextInput, 0);
        rebalancing(array);
        lastIndex           = NumbersofNextInput + lastIndex; // 현재 정렬된 개수수
        NumbersofNextInput  = NumbersofNextInput << 1;
    }
    deleteBlank(array);
}


int main() {

    vector<int> array = {1, -1, 9, 6, 8, 7, -4, 50, 8, 10};
    vector<pair<int, char>> arr;
    for (size_t i : array) {
        arr.push_back(make_pair(array.at(i), 'O'));
    }

    librarySort(array);

    cout << array << endl;



    return 0;
}