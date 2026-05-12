#ifndef RPN_HPP
#define RPN_HPP

#include <stack>
#include <string>
#include <iostream>

class RPN{
    public:
        RPN();
        RPN(const RPN &other);
        RPN &operator=(const RPN &other);

        void calculate(const std::string &expression);

        ~RPN();
    private:
        std::stack<int> stack;
};

#endif