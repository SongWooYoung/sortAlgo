// Eval.cpp
#include "Eval.h"
#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <filesystem>
#include <random>
#include <iomanip>
#include <ctime>
#include <sstream>

using namespace std;
namespace fs = std::filesystem;

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
            return value; // Return in KB
        }
    }
    return 0;
}

int runEvaluation(const string& algorithmName, int argc, char** argv,
                  function<void(vector<int>&)> sortFunction) {
    if (argc < 3) {
        cerr << "Usage: <program> <list_size> <repeat_count>" << endl;
        return 1;
    }

    int listSize = stoi(argv[1]);
    int repeatCount = stoi(argv[2]);
    vector<string> listTypes = {"ascending", "descending", "partial", "random"};

    // 날짜 기반 결과 파일명
    auto t = time(nullptr);
    auto tm = *localtime(&t);
    ostringstream oss;
    oss << put_time(&tm, "%Y-%m-%d");
    string dateStr = oss.str();
    fs::create_directory("result");
    string filename = "result/" + dateStr + "_" + algorithmName + ".csv";
    ofstream outFile(filename);

    outFile << "ListType,Iteration,Duration(ms),Memory(KB)" << endl;

    for (const auto& type : listTypes) {
        for (int rep = 0; rep < repeatCount; rep++) {
            vector<int> data = generateList(listSize, type);

            auto start = chrono::high_resolution_clock::now();
            sortFunction(data);
            auto end = chrono::high_resolution_clock::now();

            auto duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();
            size_t memUsage = getMemoryUsage();

            cout << "[ " << type << " #" << rep + 1 << " ] "
                 << "Time: " << duration << "ms, "
                 << "Memory: " << memUsage << " KB" << endl;

            outFile << type << "," << rep + 1 << "," << duration << "," << memUsage << endl;
        }
    }

    outFile.close();
    return 0;
}