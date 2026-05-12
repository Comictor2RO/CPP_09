#include "BitcoinExchange.hpp"

int main(int argc, char **argv)
{
    if(argc != 2)
    {
        std::cout << "Usage: ./btc [input file]\n";
        return 1;
    }
    else
    {
        BitcoinExchange btc;
        btc.run(argv[1]);
    }
    return 0;
}