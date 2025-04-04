#ifndef EVAL_H
#define EVAL_H

#include <vector>
#include <string>
#include <functional>

int runEvaluation(
    const std::string& algorithmName,
    int argc,
    char** argv,
    std::function<void(std::vector<int>&)> sortFunction
);

#endif
