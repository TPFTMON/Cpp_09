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
        RPN(const RPN &to_copy);
        RPN& operator=(const RPN &assign);
        ~RPN();

        // Other member functions:
        // ... some members

};


// Other:
// ...

#endif
