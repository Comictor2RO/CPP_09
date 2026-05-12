#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{
    loadDatabase("data.csv");
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other)
{
    *this = other;
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other)
{
    if(this != &other)
    {
        this->data = other.data;
    }

    return *this;
}

void BitcoinExchange::run(const std::string &inputFilename)
{
    std::ifstream input(inputFilename.c_str());
    if(!input.is_open())
    {
        std::cout << "Error: couldn't open the input file.\n";
        return;
    }

    std::string line;
    std::getline(input, line);
    
    while(std::getline(input, line))
    {
        if(line.empty())
            continue;

        size_t pipePos = line.find('|');
        if(pipePos == std::string::npos)
        {    
            std::cout << "Error: bad input => " << line << '\n';
            continue;
        }

        std::string dateStr = line.substr(0, pipePos);
        std::string valStr = line.substr(pipePos + 1);

        // curatam spatiu pt date
        size_t firstSpace = dateStr.find_first_not_of(" \t");
        size_t secondSpace = dateStr.find_last_not_of(" \t");
        if(firstSpace != std::string::npos && secondSpace != std::string::npos)
            dateStr = dateStr.substr(firstSpace, (secondSpace - firstSpace + 1));

        //curatam spatiu pt val
        firstSpace = valStr.find_first_not_of(" \t");
        secondSpace = valStr.find_last_not_of(" \t");
        if(firstSpace != std::string::npos && secondSpace != std::string::npos)
            valStr = valStr.substr(firstSpace, (secondSpace - firstSpace + 1));

        //verificam daca date este valid
        if(!isValidDate(dateStr))
        {
            std::cout << "Error: bad input => " << dateStr << '\n';
            continue;
        }

        double val = atof(valStr.c_str());
        if(val < 0)
        {
            std::cout << "Error: not a positive number\n";
        }
        else if(val > 1000)
        {
            std::cout << "Error: too large number\n";
        }
        else
        {
            double rate = getRate(dateStr);
            std::cout << dateStr << " => " << val << " = " << rate * val << '\n';
        }

    }
}

void BitcoinExchange::loadDatabase(const std::string &filename)
{
    std::ifstream file(filename.c_str());
    if(!file.is_open())
    {
        std::cout << "Error: couldn't open the file.\n";
        return;
    }
    else
    {
        std::string line;
        std::getline(file, line);               //Sare peste header
        while(std::getline(file, line))         //Ia fiecare linie pe rand le adauga intr-un stream
        {
            std::stringstream ss(line);
            std::string date;
            std::string rateStr;

            if(std::getline(ss, date, ',') && std::getline(ss, rateStr)) //citeste tot pana da de virgula
            {
                double rate = std::atof(rateStr.c_str()); //transforma un string in float

                this->data[date] = rate;   //insereaza automat perechea key/value
            }
        }
    }
}

bool BitcoinExchange::isValidDate(const std::string &date)
{
    if(date.length() != 10 || date[4] != '-' || date[7] != '-') //verifica daca sirul are exact 10 caractere si daca are - unde trebuie
        return false;

    for(size_t i = 0; i < date.length(); ++i)   //verifica daca caracterele inafara de cele 2 '-' sunt numere
    {
        if(i == 4 || i == 7)
            continue;
        if(!isdigit(date[i]))
            return false;
    }

    std::stringstream ss(date); //salvez toata data intr-un stream
    std::string year, month, day;
    int y, m, d;
    int days[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    
    std::getline(ss, year, '-'); //iei din stream pana cand intalnesti '-'
    std::getline(ss, month, '-'); //iei din stream pana cand intalnesti al doilea '-'
    std::getline(ss, day); //restul pana cand se termina


    //transforma din str in int
    y = std::atoi(year.c_str());
    m = std::atoi(month.c_str());
    d = std::atoi(day.c_str());

    if(m < 1 || m > 12) //daca sunt luni de la 1 pana la 12
        return false;

    if(m == 2 && ((y % 4 == 0 && y % 100 != 0) || (y % 400 == 0)))  //daca este an bisect feb se fac 29
        days[2] = 29;

    if(d < 1 || d > days[m]) //daca ziua este in intervalul (1, nr de zile ale lunii)
        return false;

    return true;
}

double BitcoinExchange::getRate(const std::string &date)
{
    std::map<std::string, double>::iterator it = data.lower_bound(date);

    if(it != data.end() && it->first == date) //am exact aceeasi data
        return it->second;

    if(it == data.begin()) //data este mai mica decat tot ce avem
        return 0;

    --it;
    return it->second;
}

BitcoinExchange::~BitcoinExchange()
{}