#include "BitcoinExchange.hpp"

int main(int argc, char const *argv[]){

    if (argc != 2){
        std::cerr << "Error: could not open file." << "\n";
        return (1);
    }

    try {
        BitcoinExchange btc;
        btc.loadDatabase("data.csv");
        btc.processInput(argv[1]);
    } catch (const std::exception& e) {
        std::cerr << e.what() << "\n";
        return (1);
    }
    
    return (0);
}


