#include "BitcoinExchange.hpp"

// ================================================================
//                         ORTHODOX BASE
// ================================================================

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other){

    *this = other;
}


void BitcoinExchange::swap(BitcoinExchange &other){
    this->_database.swap(other._database);
}

BitcoinExchange& BitcoinExchange::operator=(BitcoinExchange other){
    swap(other);
    return (*this);
};


BitcoinExchange::~BitcoinExchange() {}



// ================================================================
//                OTHER BITCOINEXCHANGE MEMBER FUNCTIONS
// ================================================================

std::string BitcoinExchange::_trim(const std::string &str) const{

    size_t first = str.find_first_not_of(" \t\n\r\f\v");
    if (first == std::string::npos)
        return ("");

    size_t last = str.find_last_not_of(" \t\n\r\f\v");
    return (str.substr(first, (last - first + 1)));
}

bool BitcoinExchange::_isValidDate(const std::string &date) const{

    if (date.length() != 10) return (false);
    if (date[4] != '-' || date[7] != '-') return (false);

    for (int i = 0; i < 10; ++i){
        if (i == 4 || i == 7) continue;
        if (!std::isdigit(date[i])) return (false);
    }

    int year = std::atoi(date.substr(0, 4).c_str());
    int month = std::atoi(date.substr(5, 2).c_str());
    int day = std::atoi(date.substr(8, 2).c_str());

    if (month < 1 || month > 12) return (false);

    int daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)){
        daysInMonth[2] = 29;
    }

    if (day < 1 || day > daysInMonth[month]) return (false);

    return (true);
}

bool BitcoinExchange::_parseValue(const std::string &valStr, float &value, bool isInput) const{

    if (valStr.empty()) return (false);

    char* endptr;
    double val = std::strtod(valStr.c_str(), &endptr);

    while (*endptr != '\0' && std::isspace(*endptr)){
        endptr++;
    }

    if (*endptr != '\0'){
        return (false); // Contains non-numeric junk
    }

    if (isInput){
        if (val < 0){
            std::cerr << "Error: not a positive number." << std::endl;
            return (false);
        }
        if (val > 1000.0){
            std::cerr << "Error: a number is too large." << std::endl;
            return (false);
        }
    } else {
        if (val < 0){
            return (false); // DB shouldn't have negative prices
        }
    }

    value = static_cast<float>(val);
    return (true);
}



void BitcoinExchange::loadDatabase(const std::string& dbPath){

    std::ifstream file(dbPath.c_str());
    if (!file.is_open()){
        std::cerr << "Error: could not open database file." << std::endl;
        std::exit(1); // For now with exit. But I'm thinking about exceptions
    }

    std::string line;
    std::getline(file, line); // Skip header

    while (std::getline(file, line)){
        if (line.empty()) continue;

        size_t commaPos = line.find(',');
        if (commaPos == std::string::npos) continue;

        std::string date = _trim(line.substr(0, commaPos));
        std::string rateStr = _trim(line.substr(commaPos + 1));

        float rate;
        if (_isValidDate(date) && _parseValue(rateStr, rate, false)){
            _database[date] = rate;
        }
    }

    if (_database.empty()){
        std::cerr << "Error: database is empty or corrupted." << std::endl;
        std::exit(1);
    }
}

void BitcoinExchange::processInput(const std::string& inputPath) const{

    std::ifstream file(inputPath.c_str());
    if (!file.is_open()){
        std::cerr << "Error: could not open file." << std::endl;
        return ;
    }

    std::string line;
    bool isFirstLine = true;

    while (std::getline(file, line)){
        if (line.empty()) continue;

        if (isFirstLine){
            isFirstLine = false;
            if (_trim(line) == "date | value") continue;
        }

        size_t pipePos = line.find('|');
        if (pipePos == std::string::npos){
            std::cerr << "Error: bad input => " << line << std::endl;
            continue;
        }

        std::string date = _trim(line.substr(0, pipePos));
        std::string valStr = _trim(line.substr(pipePos + 1));

        if (!_isValidDate(date)){
            std::cerr << "Error: bad input => " << date << std::endl;
            continue;
        }

        float value;
        // _parseValue returns false and prints the specific value errors internally if needed
        if (!_parseValue(valStr, value, true)){
            // If it failed but didn't print "not a positive number" or "too large",
            // it means it was completely invalid syntax.
            if (value != -1 && valStr.find_first_not_of(" \t\n\r\f\v") != std::string::npos){
               char* endptr;
               double val = std::strtod(valStr.c_str(), &endptr);
               while (*endptr != '\0' && std::isspace(*endptr)) endptr++;
               if (*endptr != '\0'){
                   std::cerr << "Error: bad input => " << line << std::endl;
               }
            }
            continue;
        }

        std::map<std::string, float>::const_iterator it = _database.upper_bound(date);
        if (it == _database.begin()){
            std::cerr << "Error: date predates historical records => " << date << std::endl;
            continue;
        }

        --it;
        float rate = it->second;
        std::cout << date << " => " << value << " = " << (value * rate) << std::endl;
    }
}
