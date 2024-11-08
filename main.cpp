#include "src/algorithm.hpp"

int main(int argc, char* argv[]) {
    SeaTree tree(argc, argv);
    tree.find_best_split();
}
