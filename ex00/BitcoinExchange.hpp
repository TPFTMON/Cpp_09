#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

// Includes:
#include <iostream>
#include <string>
#include <map>
// #include <fstream>
// #include <sstream>
// #include <cstdlib>
// #include <cctype>


// Messages:
# define BITCOINEXCHANGE_MSG "\e[0;32mBitcoinExchange\n\e[0m"

# define DEF_CONSTR_MSG "\e[0;33mDefault Constructor\e[0m called of "
# define COPY_CONSTR_MSG "\e[0;33mCopy Constructor\e[0m called of "
# define COPY_ASSIGN_OP_MSG "\e[0;35mCopy assignment operator\e[0m called of "
# define DESTR_MSG "\e[0;31mDestructor\e[0m called of "


// Classes:
class BitcoinExchange{

    private:
        std::map<std::string, float> _database;

        std::string _trim(const std::string &str) const;
        bool _isValidDate(const std::string &date) const;
        bool _parseValue(const std::string &valStr, float &value, bool isInput) const;

    public:
        // Orthodox Canonical Form:
        BitcoinExchange();
        BitcoinExchange(const BitcoinExchange &other);

        void swap(BitcoinExchange &other);
        BitcoinExchange& operator=(BitcoinExchange other);

        ~BitcoinExchange();

        // Other member functions:
        void loadDatabase(const std::string &dbPath);
        void processInput(const std::string &inputPath) const;

};


// Other:
// ...

#endif
