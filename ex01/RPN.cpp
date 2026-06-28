#include "RPN.hpp"

// ================================================================
//                         ORTHODOX BASE
// ================================================================

RPN::RPN() {}

RPN::RPN(const RPN &other) : _RPNStack(other._RPNStack) {}

RPN& RPN::operator=(const RPN &other){

    if (this != &other){
        _RPNStack = other._RPNStack;
    }
    return (*this);
}

RPN::~RPN() {}



// ================================================================
//                OTHER RPN MEMBER FUNCTIONS
// ================================================================

RPN::Status    RPN::doRPN(const char *argv[]){

    std::stringstream ss(argv[1]);
    std::string token;

    while (ss >> token){
        if (token.length() == 1 && std::isdigit(token[0])){
            _RPNStack.push(token[0] - '0');
        } else if (token == "+" || token == "-" || token == "*" || token == "/"){
            if (_RPNStack.size() < 2){
                std::cerr << "Error" << "\n";
                return (ERROR);
            }
            int rhs = _RPNStack.top(); _RPNStack.pop(); // RIGHT Hand Side
            int lhs = _RPNStack.top(); _RPNStack.pop(); // LEFT Hand Side

            long result = 0;
            if (token == "+") result = static_cast<long>(lhs) + static_cast<long>(rhs);
            else if (token == "-") result = static_cast<long>(lhs) - static_cast<long>(rhs);
            else if (token == "*") result = static_cast<long>(lhs) * static_cast<long>(rhs);
            else if (token == "/"){
                if (rhs == 0){
                    std::cerr << "Error: Division by zero." << "\n";
                    return (ERROR);
                }
                result = static_cast<long>(lhs) / static_cast<long>(rhs);
            }

            if (result > 2147483647 || result < -2147483648) {
                std::cerr << "Error: Integer overflow detected." << std::endl;
                return (ERROR);
            }
            _RPNStack.push(static_cast<int>(result));

        } else{
            std::cerr << "Error" << "\n";
            return (ERROR);
        }
    }

    if (_RPNStack.size() != 1){
        std::cerr << "Error" << "\n";
        return (ERROR);
    }

    std::cout << _RPNStack.top() << "\n";
    return (OKI);
}
