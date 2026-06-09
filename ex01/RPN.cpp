#include "RPN.hpp"

// ================================================================
//                         ORTHODOX BASE
// ================================================================

RPN::RPN(){}

RPN::RPN(const RPN &other){

    (void)other;
    // ... copying

}

RPN& RPN::operator=(const RPN &other){

    if (this != &other){
        // ... assigning
    }
    return (*this);

}

RPN::~RPN(){}



// ================================================================
//                OTHER RPN MEMBER FUNCTIONS
// ================================================================

RPN::Status    RPN::doRPN(char **argv){

    std::stringstream ss(argv[1]);
    std::stack<int> rpnStack;
    std::string token;

    while (ss >> token){
        if (token.length() == 1 && std::isdigit(token[0])){
            rpnStack.push(token[0] - '0');
        } else if (token == "+" || token == "-" || token == "*" || token == "/"){
            if (rpnStack.size() < 2){
                std::cerr << "Error" << "\n";
                return (ERROR);
            }
            int rhs = rpnStack.top(); rpnStack.pop();
            int lhs = rpnStack.top(); rpnStack.pop();

            if (token == "+") rpnStack.push(lhs + rhs);
            else if (token == "-") rpnStack.push(lhs - rhs);
            else if (token == "*") rpnStack.push(lhs * rhs);
            else if (token == "/"){
                if (rhs == 0){
                    std::cerr << "Error: Division by zero." << "\n";
                    return (ERROR);
                }
                rpnStack.push(lhs / rhs);
            }
        } else{
            std::cerr << "Error" << "\n";
            return (ERROR);
        }
    }

    if (rpnStack.size() != 1){
        std::cerr << "Error" << "\n";
        return (ERROR);
    }

    std::cout << rpnStack.top() << "\n";
    return (OKI);
}



// ================================================================
//                  OTHER RPN FUNCTIONS
// ================================================================

// ... other functions
