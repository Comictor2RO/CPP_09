#include "PmergeMe.hpp"

int main(int argc, char **argv) {
    if (argc < 2)
    {
        std::cerr << "Error: provide positive integers as arguments." << std::endl;
        return 1;
    }
    PmergeMe pm;
    pm.sort(argc, argv);
    return 0;
}
