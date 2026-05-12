#include "PmergeMe.hpp"

PmergeMe::PmergeMe()
{}

PmergeMe::PmergeMe(const PmergeMe &other)
{
    *this = other;
}

PmergeMe &PmergeMe::operator=(const PmergeMe &other)
{
    if (this != &other)
    {
        _vec = other._vec;
        _deq = other._deq;
    }
    return *this;
}

PmergeMe::~PmergeMe()
{}

static long long getJacobsthal(int n)
{
    if (n == 0)
        return 0;
    if (n == 1)
        return 1;
    return getJacobsthal(n - 1) + 2 * getJacobsthal(n - 2);
}

// IMPLEMENTARE VECTOR
std::vector<int> PmergeMe::fordJohnsonVector(std::vector<int> &v)
{
    if (v.size() <= 1)
        return v;

    int straggler = -1;
    bool hasStraggler = false;
    if (v.size() % 2 != 0)
    {
        straggler = v.back();
        v.pop_back();
        hasStraggler = true;
    }

    std::vector<std::pair<int, int> > pairs;
    for (size_t i = 0; i < v.size(); i += 2)
    {
        if (v[i] < v[i + 1])
            pairs.push_back(std::make_pair(v[i + 1], v[i]));
        else
            pairs.push_back(std::make_pair(v[i], v[i + 1]));
    }

    std::vector<int> largerOnes;
    for (size_t i = 0; i < pairs.size(); ++i)
        largerOnes.push_back(pairs[i].first);

    std::vector<int> mainChain = fordJohnsonVector(largerOnes);

    for (size_t i = 0; i < pairs.size(); ++i)
    {
        if (std::find(mainChain.begin(), mainChain.end(), pairs[i].first) != mainChain.end())
        {
            std::vector<int>::iterator it = std::lower_bound(mainChain.begin(), mainChain.end(), pairs[i].second);
            mainChain.insert(it, pairs[i].second);
        }
    }

    if (hasStraggler)
    {
        std::vector<int>::iterator it = std::lower_bound(mainChain.begin(), mainChain.end(), straggler);
        mainChain.insert(it, straggler);
    }

    return mainChain;
}

// IMPLEMENTARE DEQUE
std::deque<int> PmergeMe::fordJohnsonDeque(std::deque<int> &d)
{
    if (d.size() <= 1)
        return d;

    int straggler = -1;
    bool hasStraggler = false;
    if (d.size() % 2 != 0)
    {
        straggler = d.back();
        d.pop_back();
        hasStraggler = true;
    }

    std::deque<std::pair<int, int> > pairs;
    for (size_t i = 0; i < d.size(); i += 2)
    {
        if (d[i] < d[i + 1])
            pairs.push_back(std::make_pair(d[i + 1], d[i]));
        else
            pairs.push_back(std::make_pair(d[i], d[i + 1]));
    }

    std::deque<int> largerOnes;
    for (size_t i = 0; i < pairs.size(); ++i)
        largerOnes.push_back(pairs[i].first);

    std::deque<int> mainChain = fordJohnsonDeque(largerOnes);

    for (size_t i = 0; i < pairs.size(); ++i)
    {
        std::deque<int>::iterator it = std::lower_bound(mainChain.begin(), mainChain.end(), pairs[i].second);
        mainChain.insert(it, pairs[i].second);
    }

    if (hasStraggler)
    {
        std::deque<int>::iterator it = std::lower_bound(mainChain.begin(), mainChain.end(), straggler);
        mainChain.insert(it, straggler);
    }
    return mainChain;
}

void PmergeMe::sort(int argc, char **argv)
{
    for (int i = 1; i < argc; ++i)
    {
        std::string s = argv[i];
        for (size_t j = 0; j < s.length(); ++j)
        {
            if (!isdigit(s[j]))
            {
                std::cerr << "Error" << std::endl;
                return;
            }
        }
        
        int val = std::atoi(argv[i]);
        
        if (val < 0)
        {
            std::cerr << "Error" << std::endl;
            return;
        }
        _vec.push_back(val);
        _deq.push_back(val);
    }

    std::cout << "Before: ";
    for (size_t i = 0; i < _vec.size(); ++i)
        std::cout << _vec[i] << " ";
    std::cout << std::endl;

    clock_t startVec = clock();
    _vec = fordJohnsonVector(_vec);
    clock_t endVec = clock();

    clock_t startDeq = clock();
    _deq = fordJohnsonDeque(_deq);
    clock_t endDeq = clock();

    std::cout << "After:  ";
    for (size_t i = 0; i < _vec.size(); ++i)
        std::cout << _vec[i] << " ";
    std::cout << std::endl;

    double timeVec = static_cast<double>(endVec - startVec) / CLOCKS_PER_SEC * 1000000;
    double timeDeq = static_cast<double>(endDeq - startDeq) / CLOCKS_PER_SEC * 1000000;

    std::cout << "Time to process a range of " << _vec.size() << " elements with std::vector : " << std::fixed << std::setprecision(5) << timeVec << " us" << std::endl;
    std::cout << "Time to process a range of " << _deq.size() << " elements with std::deque : " << std::fixed << std::setprecision(5) << timeDeq << " us" << std::endl;
}
