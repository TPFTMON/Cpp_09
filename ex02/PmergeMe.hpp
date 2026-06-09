#ifndef PMERGEME_HPP
# define PMERGEME_HPP

// Includes:
# include <iostream>


// Messages:


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
