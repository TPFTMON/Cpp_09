#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

// Includes:
# include <iostream>


// Messages:
# define BITCOINEXCHANGE_MSG "\e[0;32mBitcoinExchange\n\e[0m"

# define DEF_CONSTR_MSG "\e[0;33mDefault Constructor\e[0m called of "
# define COPY_CONSTR_MSG "\e[0;33mCopy Constructor\e[0m called of "
# define COPY_ASSIGN_OP_MSG "\e[0;35mCopy assignment operator\e[0m called of "
# define DESTR_MSG "\e[0;31mDestructor\e[0m called of "


// Classes:
class BitcoinExchange{

    private:
        // ... some private stuff

    public:
        // Orthodox Canonical Form:
        BitcoinExchange();
        BitcoinExchange(const BitcoinExchange &to_copy);
        BitcoinExchange& operator=(const BitcoinExchange &assign);
        ~BitcoinExchange();

        // Other member functions:
        // ... some members

};


// Other:
// ...

#endif
