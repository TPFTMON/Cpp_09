#ifndef PMERGEME_HPP
# define PMERGEME_HPP

// Includes:
# include <iostream>
# include <vector>
# include <deque>
# include <sys/time.h>
# include <cstdlib>
# include <algorithm>


// Messages:


// Classes:
class PmergeMe{

    private:
        std::vector<int> _vectorData;
        std::deque<int>  _dequeData;

        // Helpers to swap chunks of memory of variable block sizes
        void _swapBlocks(std::vector<int> &target, size_t i, size_t j, size_t size);
        void _swapBlocks(std::deque<int> &target, size_t i, size_t j, size_t size);

        // Helper to insert the secondary chain into the primary with Jacobsthal numbers:
        void _insertSecondariesVector(size_t blockSize);
        void _insertSecondariesDeque (size_t blockSize);

        // Separate, distinct execution trees. I MIGHT just do each of the containers differently.
        void _sortVector(size_t blockSize);
        void _sortDeque(size_t blockSize);

    public:
        // Orthodox Canonical Form:
        PmergeMe();
        PmergeMe(const PmergeMe &other);
        PmergeMe& operator=(const PmergeMe &other);
        ~PmergeMe();

        // Other member functions:
        void parseInput(int argc, char** argv);
        void executeAndTiming();

};


// Other:
// ...


#endif
