#pragma once

#include "data-reader.hpp"
#include <cmath>

struct SeaTree {

    Reader reader;
    Vector target;
    Matrix ranges;
    Matrix predictors;

    static Vector range(Vector& x) {

        Vector result = {0, 0};
        bool first;

        for (float& i : x) {

            if (first) {
                result = {i, i};
                first = false;
                continue;
            }
            
            if (i < result[0]) {
                result[0] = i;
            }

            if (i > result[1]) {
                result[1] = i;
            }
        }

        return result;
    } 

    SeaTree(int argc, char* argv[]) {

        reader.validate(argc, argv);
        reader.read_predictors(predictors);
        reader.read_targets(target, predictors[0].size());
        
        for (Vector& x : predictors) {
            ranges.push_back(range(x));
        }
    }

    static float mean(Vector x) {

        float total;
        float n;

        for (float& i : x) {
            total += i;
            n += 1;
        }

        return total / n;
    }

    static float sd(Vector x) {

        float avg = mean(x);
        float total;
        float n;

        for (float& i : x) {
            total += pow(i - avg, 2);
            n += 1;
        }

        return sqrt(total / n);
    }

    float information_gain(Vector x, float split, float original) {

        Vector below;
        Vector above;

        for (int i = 0; i < x.size(); i++) {
            if (x[i] < split) {
                below.emplace_back(target[i]);
            } else {
                above.emplace_back(target[i]);
            }
        }

        return original; // - (sd(below) + sd(above));
    }

    void find_best_split() {

        for (int i = 0; i < predictors.size(); i++) {

            float original = sd(predictors[i]);

            float lo = ranges[i][0] * 0.05;
            float hi = ranges[i][1] * 0.95;
            float delta = (lo - hi) / 10;

            for (int j = 1; j < 9; j++) {

                float split = lo + delta * float(j);
                float gain = information_gain(predictors[i], split, original);

                std::cout << "(Column: " + std::to_string(i);
                std::cout << ", Split: " + std::to_string(split);
                std::cout << ", Gain: " + std::to_string(gain) + ")\n";

            }
        }
    }
    
};
