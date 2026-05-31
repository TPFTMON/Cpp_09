#include "BitcoinExchange.hpp"

// ================================================================
//                         ORTHODOX BASE
// ================================================================

BitcoinExchange::BitcoinExchange(){

    std::cout << DEF_CONSTR_MSG << BITCOINEXCHANGE_MSG;

}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &to_copy){

    std::cout << COPY_CONSTR_MSG << BITCOINEXCHANGE_MSG;
    // ... copying

}

void BitcoinExchange::swap(BitcoinExchange &other){

    this->_database.swap(other._database);
}


BitcoinExchange& BitcoinExchange::operator=(BitcoinExchange other){

    swap(other);
    return (*this);
};

BitcoinExchange::~BitcoinExchange(){

    std::cout << DESTR_MSG << BITCOINEXCHANGE_MSG;

}



// ================================================================
//                OTHER BITCOINEXCHANGE MEMBER FUNCTIONS
// ================================================================

// ... other members



// ================================================================
//                  OTHER BITCOINEXCHANGE FUNCTIONS
// ================================================================

// ... other functions
