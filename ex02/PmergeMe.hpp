#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <deque>
#include <string>
#include <algorithm>
#include <ctime>
#include <iomanip>

class PmergeMe {
public:
    PmergeMe();
    PmergeMe(const PmergeMe &other);
    PmergeMe &operator=(const PmergeMe &other);
    ~PmergeMe();

    void sort(int argc, char **argv);

private:
    std::vector<int> _vec;
    std::deque<int> _deq;

    // Logica pentru Vector
    std::vector<int> fordJohnsonVector(std::vector<int> &v);

    // Logica pentru Deque
    std::deque<int> fordJohnsonDeque(std::deque<int> &d);
};

#endif
