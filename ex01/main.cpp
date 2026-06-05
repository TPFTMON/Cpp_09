#include "RPN.hpp"

int main(int argc, char **argv){
    if (argc != 2){
        std::cerr << "Error" << "\n";
        return (1);
    }

    std::stringstream ss(argv[1]);
    std::stack<int> rpnStack;
    std::string token;

    while (ss >> token){
        if (token.length() == 1 && std::isdigit(token[0])){
            rpnStack.push(token[0] - '0');
        } else if (token == "+" || token == "-" || token == "*" || token == "/"){
            if (rpnStack.size() < 2){
                std::cerr << "Error" << "\n";
                return (1);
            }
            int rhs = rpnStack.top(); rpnStack.pop();
            int lhs = rpnStack.top(); rpnStack.pop();

            if (token == "+") rpnStack.push(lhs + rhs);
            else if (token == "-") rpnStack.push(lhs - rhs);
            else if (token == "*") rpnStack.push(lhs * rhs);
            else if (token == "/"){
                if (rhs == 0){
                    std::cerr << "Error: Division by zero." << "\n";
                    return (1);
                }
                rpnStack.push(lhs / rhs);
            }
        } else{
            std::cerr << "Error" << "\n";
            return (1);
        }
    }

    if (rpnStack.size() != 1){
        std::cerr << "Error" << "\n";
        return (1);
    }

    std::cout << rpnStack.top() << "\n";
    return (0);
}