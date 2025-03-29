#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include <filesystem>
#include <iomanip>
#include <algorithm>
#include <unordered_map>
#include <regex>  // ✅ 정규식 추가

using namespace std;
namespace fs = std::filesystem;

// 정렬 알고리즘 구현 파일 포함
#include "bubbleSort.cpp"
#include "heapSort.cpp"
#include "insertionSort.cpp"
#include "mergeSort.cpp"
#include "quickSort.cpp"
#include "selectionSort.cpp"
#include "TSort.cpp"
#include "combSort.cpp"
#include "CSSort.cpp"

// 정렬 래퍼 함수
void TSort_wrapper(vector<int>& v) {
    vector<Node> array;
    for (int val : v) {
        array.push_back({val, {}});
    }
    v = TSort(array);
}

void quickSort_wrapper(vector<int>& v) {
    if (!v.empty()) quickSort(v, 0, v.size() - 1);
}
void mergeSort_wrapper(vector<int>& v) {
    if (!v.empty()) mergeSort(&v[0], 0, v.size() - 1);
}
void insertionSort_wrapper(vector<int>& v) {
    insertionSort(v, v.size());
}

typedef void (*SortFunction)(vector<int>&);

bool isSorted(const vector<int>& v) {
    for (size_t i = 1; i < v.size(); ++i)
        if (v[i - 1] > v[i]) return false;
    return true;
}

vector<int> loadData(const string& path) {
    vector<int> v;
    ifstream in(path);
    int x;
    while (in >> x) v.push_back(x);
    return v;
}

size_t estimateMemoryUsage(const vector<int>& v) {
    return v.capacity() * sizeof(int);
}

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

    // ✅ 단위 포함 문자열로 변환
    string timeStr = to_string((int)(total / runs)) + " ms";
    string memStr = to_string((int)(memoryUsed / 1024)) + " KB";

    cout << left << setw(16) << algoName
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
        {"insertionSort", insertionSort_wrapper},
        {"mergeSort", mergeSort_wrapper},
        {"quickSort", quickSort_wrapper},
        {"selectionSort", selectionSort},
        {"TSort", TSort_wrapper},
        {"combSort", combSort},
        {"CSSort", CSSort}
    };

    string algo, fileChoice;
    cout << "🔍 정렬 알고리즘 이름 입력 (예: quickSort): ";
    cin >> algo;

    if (sort_map.find(algo) == sort_map.end()) {
        cerr << "❌ 해당 정렬 알고리즘은 존재하지 않습니다.\n";
        return 1;
    }

    cout << "📂 파일 이름 또는 키워드를 입력하세요 (예: sorted_1000.txt 또는 1000): ";
    cin >> ws;
    getline(cin, fileChoice);

    vector<string> matchedFiles;
    string folder = "sorting_datasets_txt";

    // ✅ 정규식 패턴: 정확히 `_1000.txt` 등으로 끝나는 경우만 매칭
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
         << setw(8) << "Sorted"
         << setw(10) << "Time"
         << setw(10) << "Memory"
         << "\n--------------------------------------------------------------\n";

    for (const auto& path : matchedFiles) {
        cout << "🔄 Now testing file: " << fs::path(path).filename() << "...\n";
        evaluate(sort_map[algo], algo, path);
    }

    return 0;
}
