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

//                 ========== VECTOR ==========
// I don't want to do the version with whole blocks swapping. I will do the classic way. More or less pure Ford-Johnson and Jacobsthal

void PmergeMe::_insertSecondariesVector(size_t blockSize){
    // 1. Separate current memory layout into discrete block vectors
    std::vector<std::vector<int> > mainChain;
    std::vector<std::vector<int> > pendingChain;

    // The first pair's secondary is safely pushed to mainChain immediately
    // Followed by pushing all sorted primaries to the mainChain...

    // 2. Generate Jacobsthal sequence dynamically based on pendingChain.size()
    std::vector<size_t> jacob;
    jacob.push_back(1);
    jacob.push_back(3);
    while (jacob.back() < pendingChain.size()){
        jacob.push_back(jacob.back() + 2 * jacob[jacob.size() - 2]);
    }

    // 3. Insertion Loop
    size_t lastInsertedIdx = 0;
    for (size_t i = 1; i < jacob.size(); ++i){
        size_t targetJacob = jacob[i];
        // Ensure we don't overshoot the size of our pending elements
        size_t startIdx = std::min(targetJacob, pendingChain.size()) - 1;
        size_t endIdx = lastInsertedIdx;

        // Iterate backwards from the Jacobsthal boundary down to the last inserted index
        for (size_t j = startIdx; j > endIdx; --j){
            // Calculate upper bound: where is this secondary's primary located in mainChain?
            // Perform std::lower_bound up to that upper bound index
            // mainChain.insert(iterator, pendingChain[j]);
        }
        lastInsertedIdx = startIdx + 1;
    }

    // 4. Handle Straggler block if one existed at this level

    // 5. Flatten mainChain back into the original _vectorData
}

void PmergeMe::_sortVector(size_t blockSize){

    // Step 1: If the size of the block is bigger than all elements, return.

    // Step 2: Pair up adjacent elements. If the collection size is odd, cache the last item as a straggler.

    // Step 3: Compare elements within each pair. Store them as a std::vector<std::pair<int, int> >
    //         where pair.first holds the larger value (Primary) and pair.second holds the smaller value (Secondary).

    // Step 4: Recursively call Ford-Johnson sort on this vector of pairs, defining custom comparison logic that sorts the structures based strictly on pair.first.
    //         Be ready to catch straggler at any time

    // Step 5: Once the recursive call unwinds, the pairs are sorted by their primaries. Extract all pair.first elements to initialize MainChain vector.

    // Step 6: Insert the first secondary element (pairs[0].second) at the very beginning of MainChain (index 0).

    // Step 7: Iterate through the remaining secondary elements using the reverse Jacobsthal block index chunks ($b_3, b_2$, then $b_5, b_4$, etc.).
    //         For each element, find its associated primary's position in the current MainChain to set the upper search limit, execute std::lower_bound, and call MainChain.insert().

    // Step 8: If a straggler was cached in step 2, perform a final binary search across the entire MainChain and insert it.

    size_t totalElements = _vectorData.size();
    size_t blockSpan = blockSize * 2;

    // Base condition: cannot form pairs if total memory space is too small
    // Step 1:
    if (blockSpan > totalElements) return ;

    // Step 2: Pair up blocks and ensure the larger primary block is placed first
    for (size_t i = 0; i + blockSpan <= totalElements; i += blockSpan){
        size_t primaryLI = i + blockSize;  // LI = Lead Index
        size_t secondaryLI = i;

        // Step 3: Compare the absolute final values of the current blocks
        if (_vectorData[secondaryLI + blockSize - 1] > _vectorData[primaryLI + blockSize - 1]){
            _swapBlocks(_vectorData, secondaryLI, primaryLI, blockSize);
        }
    }

    // Step 4: Recursively sort the primary blocks
    _sortVector(blockSpan);

    // Step 5-8: Implement Jacobsthal binary insertion back into the chain
    _insertSecondariesVector(blockSize);
    // Extract your block references, calculate Jacobsthal indexes,
    // and use std::lower_bound with a custom range comparator over the block intervals.
}



















// The purpose of this function is to swap as many parts of the containers as we want.
// void PmergeMe::_swapBlocks(std::vector<int>& target, size_t i, size_t j, size_t size){
    // for (size_t k = 0; k < size; ++k){
        // std::swap(target[i + k], target[j + k]);
    // }
// }


// void PmergeMe::_sortVector(size_t blockSize){
//     size_t totalElements = _vectorData.size();
//     size_t blockSpan = blockSize * 2;

//     // Base condition: cannot form pairs if total memory space is too small
//     if (blockSpan > totalElements) return ;

//     // Step 1: Pair up blocks and ensure the larger primary block is placed first
//     for (size_t i = 0; i + blockSpan <= totalElements; i += blockSpan){
//         size_t primaryLeadIndex = i + blockSize;
//         size_t secondaryLeadIndex = i;

//         // Compare the absolute final values of the current blocks
//         if (_vectorData[secondaryLeadIndex + blockSize - 1] > _vectorData[primaryLeadIndex + blockSize - 1]){
//             _swapBlocks(_vectorData, secondaryLeadIndex, primaryLeadIndex, blockSize);
//         }
//     }

//     // Step 2: Recursively sort the primary blocks
//     _sortVector(blockSpan);

//     // Step 3: Implement Jacobsthal binary insertion back into the chain
//     // Extract your block references, calculate Jacobsthal indexes,
//     // and use std::lower_bound with a custom range comparator over the block intervals.
// }






//                ========== DEQUE ==========






// Public:

// ================================================================
//                  OTHER PMERGEME FUNCTIONS
// ================================================================

// ... other functions
