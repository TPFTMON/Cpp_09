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

std::string BitcoinExchange::_trim(const std::string& str) const{

    size_t first = str.find_first_not_of(" \t\n\r\f\v");
    if (first == std::string::npos)
        return ("");

    size_t last = str.find_last_not_of(" \t\n\r\f\v");
    return (str.substr(first, (last - first + 1)));
}

bool BitcoinExchange::_parseValue(const std::string& valStr, float& value, bool isInput) const{

}

void BitcoinExchange::loadDatabase(const std::string& dbPath){

}


// ================================================================
//                  OTHER BITCOINEXCHANGE FUNCTIONS
// ================================================================

// ... other functions
