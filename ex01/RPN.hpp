#ifndef RPN_HPP
# define RPN_HPP

// Includes:
# include <iostream>


// Messages:
# define RPN_MSG "\e[0;32mRPN\n\e[0m"

# define DEF_CONSTR_MSG "\e[0;33mDefault Constructor\e[0m called of "
# define COPY_CONSTR_MSG "\e[0;33mCopy Constructor\e[0m called of "
# define COPY_ASSIGN_OP_MSG "\e[0;35mCopy assignment operator\e[0m called of "
# define DESTR_MSG "\e[0;31mDestructor\e[0m called of "


// Classes:
class RPN{

    private:
        // ... some private stuff

    public:
        // Orthodox Canonical Form:
        RPN();
        RPN(const RPN &to_copy);
        RPN& operator=(const RPN &assign);
        ~RPN();

        // Other member functions:
        // ... some members

};


// Other:
// ...

#endif
