#include "RPN.hpp"

RPN::RPN()
{}

RPN::RPN(const RPN &other)
{
    *this = other;
}

RPN &RPN::operator=(const RPN &other)
{
    if(this != &other)
    {
        this->stack = other.stack;
    }

    return *this;
}

void RPN::calculate(const std::string &expression)
{
    for(size_t i = 0; i < expression.length(); i++)
    {
        char c = expression[i];
        if(isdigit(c))
        {
            if(i + 1 < expression.length() && isdigit(expression[i + 1]))
            {
                std::cout << "Error: Number bigger then 10.\n";
                return;
            }
            
            stack.push(c - '0');
        }
        else if(c == '+' || c == '-' || c == '*' || c == '/')
        {
            if(stack.size() < 2)
            {
                std::cout << "Error: Stack have to less arguments\n";
                return;
            }

            int b = stack.top();
            stack.pop();
            int a = stack.top();
            stack.pop();

            if(c == '+')
                stack.push(a + b);
            
            if(c == '-')
                stack.push(a - b);
            
            if(c == '*')
                stack.push(a * b);
            
            if(c == '/')
            {
                if(b == 0)
                {
                    std::cout << "Error: Dividing by 0\n";
                    return;
                }
                stack.push(a / b);
            }
        }
        else if(isspace(c))
        {
            continue;
        }
        else
        {
            std::cout << "Error: Couldn't perform the calculus\n";
            return;
        }
    }

    if(stack.size() != 1)
        std::cout << "Error: Invalid result!\n";
    else
        std::cout << stack.top() << '\n';
}

RPN::~RPN()
{}