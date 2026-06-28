#include "RPN.hpp"

int main(int argc, const char *argv[]){

    if (argc != 2){
        std::cerr << "Error" << "\n";
        return (1);
    }

    RPN rpn;
    RPN::Status status = rpn.doRPN(argv);
    return (status);
}
