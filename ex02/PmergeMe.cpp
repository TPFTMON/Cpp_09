#include "PmergeMe.hpp"

// ================================================================
//                         ORTHODOX BASE
// ================================================================

PmergeMe::PmergeMe(){}

PmergeMe::PmergeMe(const PmergeMe &other){

    // ... copying
}

PmergeMe& PmergeMe::operator=(const PmergeMe &other){

    if (this != &other){
        // ... assigning
    }
    return (*this);
}

PmergeMe::~PmergeMe(){}



// ================================================================
//                OTHER PMERGEME MEMBER FUNCTIONS
// ================================================================

// Private:
void PmergeMe::_swapBlocks(std::vector<int>& target, size_t i, size_t j, size_t size){
    for (size_t k = 0; k < size; ++k){
        std::swap(target[i + k], target[j + k]);
    }
}

void PmergeMe::_sortVector(size_t blockSize){
    size_t totalElements = _vectorData.size();
    size_t blockSpan = blockSize * 2;

    // Base condition: cannot form pairs if total memory space is too small
    if (blockSpan > totalElements) return;

    // Step 1: Pair up blocks and ensure the larger primary block is placed first
    for (size_t i = 0; i + blockSpan <= totalElements; i += blockSpan){
        size_t primaryLeadIndex = i + blockSize;
        size_t secondaryLeadIndex = i;

        // Compare the absolute final values of the current blocks
        if (_vectorData[secondaryLeadIndex + blockSize - 1] > _vectorData[primaryLeadIndex + blockSize - 1]){
            _swapBlocks(_vectorData, secondaryLeadIndex, primaryLeadIndex, blockSize);
        }
    }

    // Step 2: Recursively sort the primary blocks
    _sortVector(blockSpan);

    // Step 3: Implement Jacobsthal binary insertion back into the chain
    // Extract your block references, calculate Jacobsthal indexes,
    // and use std::lower_bound with a custom range comparator over the block intervals.
}



// ================================================================
//                  OTHER PMERGEME FUNCTIONS
// ================================================================

// ... other functions
