#pragma once

#include "data-reader.hpp"
#include <map>

struct Branch {

};

struct SeaTree {

    FileData predictors;
    Target target;
    Reader reader;

    std::map<int, Branch> tree_splits;

    SeaTree(int argc, char* argv[]) {
        reader.validate(argc, argv);
        reader.read_predictors(predictors);
        reader.read_targets(target, predictors.size());
    }

    void information_gain() {};
    void find_best_split() {};
    void fit_model() {};
    
};
