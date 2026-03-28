#include "PmergeMe.hpp"

// ================================================================
//                         ORTHODOX BASE
// ================================================================

PmergeMe::PmergeMe(){

    std::cout << DEF_CONSTR_MSG << PMERGEME_MSG;

}

PmergeMe::PmergeMe(const PmergeMe &to_copy){

    std::cout << COPY_CONSTR_MSG << PMERGEME_MSG;
    // ... copying

}

PmergeMe& PmergeMe::operator=(const PmergeMe &assign){

    std::cout << COPY_ASSIGN_OP_MSG << PMERGEME_MSG;
    if (this != &assign){
        // ... assigning
    }
    return (*this);

}

PmergeMe::~PmergeMe(){

    std::cout << DESTR_MSG << PMERGEME_MSG;

}



// ================================================================
//                OTHER PMERGEME MEMBER FUNCTIONS
// ================================================================

// ... other members



// ================================================================
//                  OTHER PMERGEME FUNCTIONS
// ================================================================

// ... other functions
