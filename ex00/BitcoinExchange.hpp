#ifndef BITCOIN_EXCHANGE_HPP
#define BITCOIN_EXCHANGE_HPP

#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <iomanip>

class BitcoinExchange{
    public:
        BitcoinExchange();
        BitcoinExchange(const BitcoinExchange &other);
        BitcoinExchange &operator=(const BitcoinExchange &other);

        void run(const std::string &inputFilename);

        ~BitcoinExchange();
    private:
        std::map<std::string, double> data;
        void loadDatabase(const std::string &filename);
        bool isValidDate(const std::string &date);
        double getRate(const std::string &date);
};

#endif