#include "PmergeMe.hpp"

int main(int argc, char const *argv[]){

    try {
        PmergeMe sorter;
        sorter.parseInput(argc, argv);
        sorter.executeAndTiming();
    } catch (const std::exception& e){
        std::cerr << "Error" << '\n';
        return (1);
    }

    return (0);
}

// ./PmergeMe $(shuf -i 1-100000 -n 3000 | tr "\n" " ")    --- Test with 3000 numbers
