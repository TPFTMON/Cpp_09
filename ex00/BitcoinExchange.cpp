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

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange &assign){

    std::cout << COPY_ASSIGN_OP_MSG << BITCOINEXCHANGE_MSG;
    if (this != &assign){
        // ... assigning
    }
    return (*this);

}

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
