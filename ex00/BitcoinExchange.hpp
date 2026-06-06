#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

// Includes:
# include <iostream>
# include <string>
# include <map>
# include <fstream>
# include <sstream>
# include <cstdlib>
# include <cctype>

// Messages:
# define BAD_INPUT "Error: bad input => "

// Classes:
class BitcoinExchange{

    private:
        std::map<std::string, float> _database;

        std::string _trim(const std::string &str) const;
        bool _isValidDate(const std::string &date) const;
        // bool _parseValue(const std::string &valStr, float &value, bool isInput) const;

        enum ParseStatus {
            VALID,
            NOT_POSITIVE,
            TOO_LARGE,
            BAD_FORMAT
        };
        ParseStatus _parseValue(const std::string &valStr, float &value, bool isInput) const;

        public:
        // Orthodox Canonical Form:
        BitcoinExchange();
        BitcoinExchange(const BitcoinExchange &other);

        void swap(BitcoinExchange &other);
        BitcoinExchange& operator=(BitcoinExchange other);

        ~BitcoinExchange();


        // Enum for distincting statuses

        // Other member functions:
        void loadDatabase(const std::string &dbPath);
        void processInput(const std::string &inputPath) const;

};


#endif
