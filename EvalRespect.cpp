#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include <filesystem>
#include <iomanip>
#include <algorithm>
#include <unordered_map>
#include <regex>

using namespace std;
namespace fs = std::filesystem;

// 정렬 알고리즘 구현 파일 포함
#include "bubbleSort.cpp"
#include "heapSort.cpp"
#include "insertionSort.cpp"
#include "mergeSort.cpp"
#include "selectionSort.cpp"
#include "TSort.cpp"
#include "combSort.cpp"
#include "CSSort.cpp"
#include "introSort.cpp"
#include "librarySort.cpp"

// TSort 래퍼
void TSort_wrapper(vector<int>& v) {
    vector<int> array = TSort(v);
    v = move(array);
}

// mergeSort 래퍼
void mergeSort_wrapper(vector<int>& v) {
    if (!v.empty()) mergeSort(&v[0], 0, v.size() - 1);
}

// quickSort 래퍼
void quickSort_wrapper(vector<int>& v) {
    if (!v.empty()) quickSort(v, 0, v.size() - 1);
}

typedef void (*SortFunction)(vector<int>&);

// 정렬 확인
bool isSorted(const vector<int>& v) {
    for (size_t i = 1; i < v.size(); ++i)
        if (v[i - 1] > v[i]) return false;
    return true;
}

// 데이터 로딩
vector<int> loadData(const string& path) {
    vector<int> v;
    ifstream in(path);
    int x;
    while (in >> x) v.push_back(x);
    return v;
}

// 메모리 측정
size_t estimateMemoryUsage(const vector<int>& v) {
    return v.capacity() * sizeof(int);
}

// ✅ 일반 알고리즘 평가 (librarySort 제외)
void evaluate(SortFunction func, const string& algoName, const string& filePath, int runs = 10) {
    double total = 0.0;
    bool correct = true;
    size_t memoryUsed = 0;

    for (int i = 0; i < runs; ++i) {
        vector<int> data = loadData(filePath);
        memoryUsed = max(memoryUsed, estimateMemoryUsage(data));

        auto start = chrono::high_resolution_clock::now();
        func(data);
        auto end = chrono::high_resolution_clock::now();

        if (!isSorted(data)) correct = false;

        chrono::duration<double, milli> elapsed = end - start;
        total += elapsed.count();
    }

    string timeStr = to_string((int)(total / runs)) + " ms";
    string memStr = to_string((int)(memoryUsed / 1024)) + " KB";

    cout << left << setw(16) << algoName
         << setw(28) << fs::path(filePath).filename().string()
         << setw(8)  << (correct ? "✅" : "❌")
         << setw(10) << timeStr
         << setw(10) << memStr
         << endl;
}

// ✅ librarySort 전용 평가 함수 (정렬 시간만 측정)
void evaluate_librarySort(const string& filePath, int runs = 10) {
    double total = 0.0;
    bool correct = true;
    size_t memoryUsed = 0;

    for (int i = 0; i < runs; ++i) {
        vector<int> data = loadData(filePath);
        memoryUsed = max(memoryUsed, estimateMemoryUsage(data));

        vector<pair<int, char>> arr;
        for (int val : data)
            arr.emplace_back(val, 'O');

        auto start = chrono::high_resolution_clock::now();
        librarySort(arr);  // ❗ 정렬만 측정
        auto end = chrono::high_resolution_clock::now();

        // 측정 제외: 복사
        data.clear();
        for (const auto& p : arr) {
            if (p.second == 'O')
                data.push_back(p.first);
        }

        if (!isSorted(data)) correct = false;

        chrono::duration<double, milli> elapsed = end - start;
        total += elapsed.count();
    }

    string timeStr = to_string((int)(total / runs)) + " ms";
    string memStr = to_string((int)(memoryUsed / 1024)) + " KB";

    cout << left << setw(16) << "libSort"
         << setw(28) << fs::path(filePath).filename().string()
         << setw(8)  << (correct ? "✅" : "❌")
         << setw(10) << timeStr
         << setw(10) << memStr
         << endl;
}

int main() {
    unordered_map<string, SortFunction> sort_map = {
        {"bubbleSort", bubbleSort},
        {"heapSort", heapSort},
        {"insertionSort", insertionSort},  // 이미 래핑 필요 없음
        {"mergeSort", mergeSort_wrapper},
        {"quickSort", quickSort_wrapper},
        {"selectionSort", selectionSort},
        {"TSort", TSort_wrapper},
        {"combSort", combSort},
        {"CSSort", CSSort},
        {"introSort", intro_wrapper}
        // libSort는 별도로 처리하므로 제외
    };

    string algo, fileChoice;
    cout << "🔍 정렬 알고리즘 이름 입력 (예: quickSort): ";
    cin >> algo;

    bool isLibSort = (algo == "libSort");

    if (!isLibSort && sort_map.find(algo) == sort_map.end()) {
        cerr << "❌ 해당 정렬 알고리즘은 존재하지 않습니다.\n";
        return 1;
    }

    cout << "📂 파일 이름 또는 키워드를 입력하세요 (예: sorted_1000.txt 또는 1000): ";
    cin >> ws;
    getline(cin, fileChoice);

    vector<string> matchedFiles;
    string folder = "sorting_datasets_txt";

    string pattern = ".*[_\\-]" + fileChoice + "\\.txt$";
    regex re(pattern);

    for (const auto& entry : fs::directory_iterator(folder)) {
        string filename = entry.path().filename().string();
        if (regex_match(filename, re)) {
            matchedFiles.push_back(entry.path().string());
        }
    }

    if (matchedFiles.empty()) {
        cerr << "❌ '" << fileChoice << "'을(를) 포함하는 파일을 찾을 수 없습니다.\n";
        return 1;
    }

    cout << "\n📊 Evaluation for [" << algo << "] on files matching '" << fileChoice << "':\n";
    cout << left << setw(16) << "Algorithm"
         << setw(28) << "Dataset"
         << setw(8)  << "Sorted"
         << setw(10) << "Time"
         << setw(10) << "Memory"
         << "\n--------------------------------------------------------------\n";

    for (const auto& path : matchedFiles) {
        cout << "🔄 Now testing file: " << fs::path(path).filename() << "...\n";

        if (isLibSort) {
            evaluate_librarySort(path);  // ⏱ librarySort 전용
        } else {
            evaluate(sort_map[algo], algo, path);
        }
    }

    return 0;
}
