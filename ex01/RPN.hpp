#ifndef RPN_HPP
# define RPN_HPP

// Includes:
# include <iostream>
# include <sstream>
# include <stack>
# include <cstdlib>


// Messages:
// ...


// Classes:
class RPN{

    private:
        // ... some private stuff

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

        Status  doRPN(char **argv);

};


// Other:
// ...

#endif
