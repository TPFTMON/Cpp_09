#ifndef PMERGEME_HPP
# define PMERGEME_HPP

// Includes:
# include <iostream>


// Messages:
# define PMERGEME_MSG "\e[0;32mPmergeMe\n\e[0m"

# define DEF_CONSTR_MSG "\e[0;33mDefault Constructor\e[0m called of "
# define COPY_CONSTR_MSG "\e[0;33mCopy Constructor\e[0m called of "
# define COPY_ASSIGN_OP_MSG "\e[0;35mCopy assignment operator\e[0m called of "
# define DESTR_MSG "\e[0;31mDestructor\e[0m called of "


// Classes:
class PmergeMe{

    private:
        // ... some private stuff

    public:
        // Orthodox Canonical Form:
        PmergeMe();
        PmergeMe(const PmergeMe &to_copy);
        PmergeMe& operator=(const PmergeMe &assign);
        ~PmergeMe();

        // Other member functions:
        // ... some members

};


// Other:
// ...

#endif
