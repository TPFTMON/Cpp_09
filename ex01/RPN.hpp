#ifndef RPN_HPP
# define RPN_HPP

// Includes:
# include <iostream>
# include <sstream>
# include <stack>
# include <cstdlib>

// Classes:
class RPN{

    private:
        std::stack<int> _RPNStack;

    public:
        // Orthodox Canonical Form:
        RPN();
        RPN(const RPN &other);
        RPN& operator=(const RPN &other);
        ~RPN();

        // Other member functions:
        enum Status {
            OKI,
            ERROR
        };

        Status  doRPN(const char *argv[]);

};


#endif
