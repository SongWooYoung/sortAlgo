#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include <filesystem>
#include <iomanip>
#include <algorithm>

using namespace std;
namespace fs = std::filesystem;

// 정렬 알고리즘 헤더 포함
#include "bubbleSort.cpp"
#include "heapSort.cpp"
#include "insertionSort.cpp"
#include "mergeSort.cpp"
#include "quickSort.cpp"
#include "selectionSort.cpp"

// 함수 포인터 정의
typedef void (*SortFunction)(vector<int>&);

// 래퍼: mergeSort.cpp는 int* 기반이라 vector로 래핑
void mergeSort_wrapper(vector<int>& v) {
    if (!v.empty()) mergeSort(&v[0], 0, v.size() - 1);
}

// 래퍼: quickSort.cpp는 범위 기반이라 vector로 래핑
void quickSort_wrapper(vector<int>& v) {
    if (!v.empty()) quickSort(v, 0, v.size() - 1);
}

// 래퍼: insertionSort는 size 파라미터 필요
void insertionSort_wrapper(vector<int>& v) {
    insertionSort(v, v.size());
}

// 구조체 정의
struct SortInfo {
    string name;
    SortFunction function;

    SortInfo(string n, SortFunction f) : name(std::move(n)), function(f) {}
};

// 정렬 여부 확인
bool isSorted(const vector<int>& v) {
    for (size_t i = 1; i < v.size(); ++i)
        if (v[i - 1] > v[i]) return false;
    return true;
}

// 메모리 사용량 측정 (단순 추정)
size_t estimateMemoryUsage(const vector<int>& v) {
    return sizeof(int) * v.capacity();
}

// 데이터 로딩
vector<int> loadData(const string& filename) {
    vector<int> data;
    ifstream in(filename);
    int value;
    while (in >> value) data.push_back(value);
    return data;
}

// 평가 수행
void evaluate(const SortInfo& algo, const string& path, int runs = 10) {
    double totalTime = 0.0;
    bool correct = true;
    size_t maxMem = 0;

    for (int i = 0; i < runs; ++i) {
        vector<int> data = loadData(path);
        maxMem = max(maxMem, estimateMemoryUsage(data));

        auto start = chrono::high_resolution_clock::now();
        algo.function(data);
        auto end = chrono::high_resolution_clock::now();

        if (!isSorted(data)) correct = false;

        chrono::duration<double, milli> elapsed = end - start;
        totalTime += elapsed.count();
    }

    cout << left << setw(16) << algo.name
         << setw(28) << fs::path(path).filename().string()
         << setw(8) << (correct ? "✅" : "❌")
         << setw(10) << fixed << setprecision(2) << (totalTime / runs) << "ms"
         << setw(10) << (maxMem / 1024) << "KB"
         << endl;
}

// 메인 실행
int main() {
    string folder = "sorting_datasets_txt";

    vector<SortInfo> algos = {
        SortInfo("BubbleSort", bubbleSort),
        SortInfo("HeapSort", heapSort),
        SortInfo("InsertionSort", insertionSort_wrapper),
        SortInfo("MergeSort", mergeSort_wrapper),
        SortInfo("QuickSort", quickSort_wrapper),
        SortInfo("SelectionSort", selectionSort)
    };

    cout << "📊 Sorting Performance Evaluation\n";
    cout << left << setw(16) << "Algorithm"
         << setw(28) << "Dataset"
         << setw(8) << "Sorted"
         << setw(10) << "Time"
         << setw(10) << "Memory"
         << "\n--------------------------------------------------------------\n";

    for (const auto& entry : fs::directory_iterator(folder)) {
        if (entry.path().extension() == ".txt") {
            for (const auto& algo : algos) {
                evaluate(algo, entry.path().string());
            }
        }
    }

    return 0;
}
