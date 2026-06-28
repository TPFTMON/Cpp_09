#include "BitcoinExchange.hpp"

// ================================================================
//                         ORTHODOX BASE
// ================================================================

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other){
    this->_database = other._database;
}


void BitcoinExchange::swap(BitcoinExchange &other){
    this->_database.swap(other._database);
}

BitcoinExchange& BitcoinExchange::operator=(BitcoinExchange &other){
    if (this != &other) {
        BitcoinExchange temp(other);
        this->swap(temp);
    }
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
        if (i == 4 || i == 7) continue ;
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

BitcoinExchange::ParseStatus BitcoinExchange::_parseValue(const std::string &valStr, float &value, bool isInput) const{

    if (valStr.empty()) return (BAD_FORMAT);

    char* endptr;
    double val = std::strtod(valStr.c_str(), &endptr);

    while (*endptr != '\0' && std::isspace(*endptr)) endptr++;

    if (*endptr != '\0') return (BAD_FORMAT); // Contains non-numeric junk

    if (isInput){
        if (val < 0) return (NOT_POSITIVE);

        if (val > 1000.0) return (TOO_LARGE);
    } else {
        if (val < 0) return (BAD_FORMAT); // DB shouldn't have negative prices
    }

    value = static_cast<float>(val);
    return (VALID);
}



void BitcoinExchange::loadDatabase(const std::string &dbPath){

    std::ifstream file(dbPath.c_str());
    if (!file.is_open()){
        throw std::runtime_error("Error: could not open database file.");
    }

    std::string line;
    std::getline(file, line); // Skip header

    while (std::getline(file, line)){
        if (line.empty()) continue ;

        size_t commaPos = line.find(',');
        if (commaPos == std::string::npos) continue ;

        std::string date = _trim(line.substr(0, commaPos));
        std::string rateStr = _trim(line.substr(commaPos + 1));

        float rate;
        if (_isValidDate(date) && (_parseValue(rateStr, rate, false) == VALID)){
            _database[date] = rate;
        }
    }

    if (_database.empty()){
        throw std::runtime_error("Error: database is empty or corrupted.");
    }
}

void BitcoinExchange::processInput(const std::string &inputPath) const{

    std::ifstream file(inputPath.c_str());
    if (!file.is_open()){
        std::cerr << "Error: could not open file." << "\n";
        return ;
    }

    std::string line;
    bool isFirstLine = true;

    while (std::getline(file, line)){
        if (line.empty()) continue ;

        if (isFirstLine){
            isFirstLine = false;
            if (_trim(line) != "date | value"){
                std::cerr << "Error: first line is of invalid format.\n";
            }
            continue ;
        }

        size_t pipePos = line.find('|');
        if (pipePos == std::string::npos){
            std::cerr << BAD_INPUT << line << "\n";
            continue ;
        }

        std::string date = _trim(line.substr(0, pipePos));
        std::string valStr = _trim(line.substr(pipePos + 1));

        if (!_isValidDate(date)){
            std::cerr << BAD_INPUT << date << "\n";
            continue ;
        }


        float value;
        ParseStatus status = _parseValue(valStr, value, true);

        if (status == NOT_POSITIVE) {
            std::cerr << "Error: not a positive number.\n";
            continue ;
        } else if (status == TOO_LARGE) {
            std::cerr << "Error: too large a number.\n";
            continue ;
        } else if (status == BAD_FORMAT) {
            std::cerr << BAD_INPUT << line << "\n";
            continue ;
        }

        std::map<std::string, float>::const_iterator it = _database.upper_bound(date);
        if (it == _database.begin()){
            std::cerr << "Error: date predates historical records => " << date << "\n";
            continue ;
        }

        --it;
        float rate = it->second;
        std::cout << date << " => " << value << " = " << (value * rate) << "\n";
    }
}
