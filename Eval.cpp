// Eval.cpp
#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <filesystem>
#include <random>
#include <iomanip>
#include <ctime>
#include <sstream>
#include <numeric>
#include <algorithm>

using namespace std;
namespace fs = std::filesystem;


// ========================= List Generator =========================
vector<int> generateList(size_t size, const string& type) {
    vector<int> list(size);
    iota(list.begin(), list.end(), 0);
    random_device rd;
    mt19937 gen(rd());

    if (type == "ascending") {
        return list;
    } else if (type == "descending") {
        reverse(list.begin(), list.end());
    } else if (type == "partial") {
        shuffle(list.begin(), list.begin() + size / 2, gen);
    } else if (type == "random") {
        shuffle(list.begin(), list.end(), gen);
    }

    return list;
}

// ========================= Memory Usage =========================
size_t getMemoryUsage() {
    ifstream status("/proc/self/status");
    string line;
    while (getline(status, line)) {
        if (line.substr(0, 6) == "VmRSS:") {
            istringstream iss(line);
            string key;
            size_t value;
            string unit;
            iss >> key >> value >> unit;
            return value; // KB
        }
    }
    return 0;
}

// ========================= Evaluation Function =========================
int runEvaluation(const string& algorithmName, int argc, char** argv,
                  function<void(vector<int>&)> sortFunction) {
    if (argc < 3) {
        cerr << "\n[Error] Usage: <program> <list_size> <repeat_count>" << endl;
        cerr << "Example: ./sort 10000 5\n" << endl;
        return 1;
    }

    int listSize, repeatCount;
    try {
        listSize = stoi(argv[1]);
        repeatCount = stoi(argv[2]);
        if (listSize <= 0 || repeatCount <= 0) throw invalid_argument("non-positive input");
    } catch (...) {
        cerr << "\n[Error] Invalid input. Both list size and repeat count must be positive integers.\n" << endl;
        return 1;
    }

    vector<string> listTypes = {"ascending", "descending", "partial", "random"};

    auto t = time(nullptr);
    auto tm = *localtime(&t);
    ostringstream oss;
    oss << put_time(&tm, "%Y-%m-%d");
    string dateStr = oss.str();
    fs::create_directory("result");
    string filename = "result/" + dateStr + "_" + algorithmName + "_" + to_string(listSize) + ".csv";
    ofstream outFile(filename);

    outFile << "ListType,Iteration,Duration(ms),Memory(KB)" << endl;

    cout << "\n==================== " << algorithmName << " Evaluation ====================\n";
    cout << left << setw(15) << "ListType"
         << setw(8) << "Iter"
         << setw(17) << "Time (avg ms)"
         << setw(18) << "Memory (avg KB)"
         << setw(10) << "Valid" << endl;
    cout << string(68, '-') << endl;

    for (const auto& type : listTypes) {
        vector<long long> durations;
        vector<size_t> memories;
        bool allSortedCorrectly = true;

        for (int rep = 0; rep < repeatCount; rep++) {
            vector<int> data = generateList(listSize, type);

            auto start = chrono::high_resolution_clock::now();
            sortFunction(data);
            auto end = chrono::high_resolution_clock::now();

            long long duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();
            size_t memUsage = getMemoryUsage();

            durations.push_back(duration);
            memories.push_back(memUsage);
            outFile << type << "," << rep + 1 << "," << duration << "," << memUsage << endl;

            if (!is_sorted(data.begin(), data.end())) {
                allSortedCorrectly = false;
            }
        }

        double avgTime = accumulate(durations.begin(), durations.end(), 0.0) / durations.size();
        double avgMem = accumulate(memories.begin(), memories.end(), 0.0) / memories.size();

        cout << left << setw(15) << type
             << setw(8) << repeatCount
             << setw(17) << fixed << setprecision(2) << avgTime
             << setw(18) << fixed << setprecision(2) << avgMem
             << setw(10) << (allSortedCorrectly ? "✔️" : "❌") << endl;
    }

    cout << "====================================================================\n";
    cout << "Results saved to: " << filename << endl << endl;

    outFile.close();
    return 0;
}


