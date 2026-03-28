#include "RPN.hpp"

// ================================================================
//                         ORTHODOX BASE
// ================================================================

RPN::RPN(){

    std::cout << DEF_CONSTR_MSG << RPN_MSG;

}

RPN::RPN(const RPN &to_copy){

    std::cout << COPY_CONSTR_MSG << RPN_MSG;
    // ... copying

}

RPN& RPN::operator=(const RPN &assign){

    std::cout << COPY_ASSIGN_OP_MSG << RPN_MSG;
    if (this != &assign){
        // ... assigning
    }
    return (*this);

}

RPN::~RPN(){

    std::cout << DESTR_MSG << RPN_MSG;

}



// ================================================================
//                OTHER RPN MEMBER FUNCTIONS
// ================================================================

// ... other members



// ================================================================
//                  OTHER RPN FUNCTIONS
// ================================================================

// ... other functions
