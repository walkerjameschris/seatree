#pragma once

#include <filesystem>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using Vector = std::vector<float>;
using Matrix = std::vector<Vector>;

struct Reader {

    std::string predictors_path;
    std::string target_path;

    static void check_path(std::string path, std::string file) {

        if (std::filesystem::is_regular_file(path)) {
            return;
        }

        std::cout << file + " path is not a regular file!\n";
        std::cout << "You must provide valid CSV paths\n";
        std::exit(1);
    }

    void validate(int argc, char* argv[]) {

        if (argc < 3) {
            std::cout << "Invalid data arguments\n";
            std::cout << "The commands follow this order:\n";
            std::cout << "./seatree <predictors> <target>\n";
            std::exit(1);
        }

        predictors_path = argv[1];
        target_path = argv[2];
        
        check_path(predictors_path, "Predictors");
        check_path(target_path, "Target");
    }

    static float str_to_num(std::string x, std::string file_name, int index) {

        try {
            return std::stof(x);
        } catch (...) {
            std::cout << file_name + " file is malformed on ";
            std::cout << "line " + std::to_string(index) + "\n";
            std::cout << "Cannot convert " + x + " to number!\n";
            std::exit(1);
        }
    }

    void read_predictors(Matrix& data) {

        std::ifstream file(predictors_path);
        std::string line;

        int n_predictors = 0;
        int index = 0;

        while (std::getline(file, line)) {

            std::stringstream stream(line);
            std::string value;
            Vector row;

            while (std::getline(stream, value, ',')) {
                row.push_back(str_to_num(value, "Predictors", index));
            }

            if (index == 0) {
                for (float i : row) {
                    n_predictors += 1;
                    Vector column = {i};
                    data.push_back(column);
                }
            }

            if (index > 0 && row.size() != n_predictors) {
                std::cout << "Row " + std::to_string(index + 1);
                std::cout << " is malformed! It contains ";
                std::cout << std::to_string(row.size()) + " columns";
                std::cout << " whereas the first row contains ";
                std::cout << std::to_string(n_predictors) + " columns\n";
                std::exit(1);
            }

            if (index > 0) {
                for (int i = 0; i < n_predictors; i++) {
                    data[i].push_back(row[i]);
                }
            }

            index += 1;
        }

        if (data.size() == 0) {
            std::cout << "Predictor did not contain readable records!";
            std::exit(1);
        }

        file.close();
    }

    void read_targets(Vector& data, int n_record) {

        std::ifstream file(target_path);
        std::string line;
        int index = 0;

        while (std::getline(file, line)) {
            std::stringstream stream(line);
            data.push_back(str_to_num(line, "Targets", index));
            index += 1;
        }

        if (data.size() != n_record) {
            std::cout << "Target file is misaligned! The ";
            std::cout << "predictors file contains ";
            std::cout << std::to_string(n_record) + " records";
            std::cout << " whereas the target file contains ";
            std::cout << std::to_string(data.size()) + " records!\n";
            std::exit(1);
        }

        file.close();
    }
};