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

size_t PmergeMe::_binarySearchBlocksVector(const std::vector<int> &chain, int target, size_t endBlockIdx, size_t blockSize){
    size_t left = 0;
    size_t right = endBlockIdx;

    while (left < right){
        size_t mid = left + (right - left) / 2;
        // Extract the primary value of the block being evaluated
        int mid_val = chain[mid * blockSize + blockSize - 1];

        if (mid_val < target){
            left = mid + 1;
        } else{
            right = mid;
        }
    }
    return left;
}

void PmergeMe::_insertSecondariesVector(size_t blockSize){
    std::vector<int> mainChain;
    std::vector<size_t> mainIDs;
    std::vector<int> pendingChain;
    std::vector<size_t> pendingIDs;

    size_t num_blocks = _vectorData.size() / blockSize;
    size_t pair_size = blockSize * 2;
    size_t num_pairs = num_blocks / 2;

    if (num_pairs == 0) return;

    // 1. Initialize chains with the first pair
    // The first secondary (b1) is automatically pushed to mainChain. It has no upper bound dependency.
    mainChain.insert(mainChain.end(), _vectorData.begin(), _vectorData.begin() + blockSize);
    mainIDs.push_back(0);

    // The first primary (a1)
    mainChain.insert(mainChain.end(), _vectorData.begin() + blockSize, _vectorData.begin() + pair_size);
    mainIDs.push_back(1);

    // 2. Extract remaining paired chunks
    for (size_t i = 1; i < num_pairs; ++i){
        size_t start = i * pair_size;

        // Secondary chunk (b_i)
        pendingChain.insert(pendingChain.end(), _vectorData.begin() + start, _vectorData.begin() + start + blockSize);
        pendingIDs.push_back(i + 1);

        // Primary chunk (a_i)
        mainChain.insert(mainChain.end(), _vectorData.begin() + start + blockSize, _vectorData.begin() + start + pair_size);
        mainIDs.push_back(i + 1);
    }

    // 3. Handle a potential straggler block
    if (num_blocks % 2 != 0){
        size_t start = num_pairs * pair_size;
        pendingChain.insert(pendingChain.end(), _vectorData.begin() + start, _vectorData.begin() + start + blockSize);
        pendingIDs.push_back(num_pairs + 1); // ID larger than any primary, allows searching the full chain
    }

    // 4. Generate Jacobsthal sequence
    std::vector<size_t> J;
    J.push_back(1);
    J.push_back(3);
    while (J.back() < pendingIDs.size() + 1){
        J.push_back(J.back() + 2 * J[J.size() - 2]);
    }

    // 5. Jacobsthal Insertion Loop
    size_t last_inserted = 0;
    for (size_t i = 1; i < J.size(); ++i){
        size_t target_idx = J[i] - 1;
        if (target_idx > pendingIDs.size()) target_idx = pendingIDs.size();

        // Iterate backwards through the Jacobsthal block
        for (size_t j = target_idx; j > last_inserted; --j){
            size_t p_idx = j - 1; // 0-based index in the pending vector
            size_t id_to_find = pendingIDs[p_idx];

            // 5a. Find dynamic upper bound using the ID array
            size_t upper_bound_idx = mainIDs.size();
            for (size_t k = 0; k < mainIDs.size(); ++k){
                if (mainIDs[k] == id_to_find){
                    upper_bound_idx = k;
                    break;
                }
            }

            // 5b. Binary Search and Insertion
            int target_val = pendingChain[p_idx * blockSize + blockSize - 1];
            size_t insert_pos = _binarySearchBlocksVector(mainChain, target_val, upper_bound_idx, blockSize);

            mainChain.insert(mainChain.begin() + insert_pos * blockSize,
                             pendingChain.begin() + p_idx * blockSize,
                             pendingChain.begin() + (p_idx + 1) * blockSize);

            mainIDs.insert(mainIDs.begin() + insert_pos, id_to_find);
        }
        last_inserted = target_idx;
    }

    // 6. Overwrite original data with the sorted chain
    for (size_t i = 0; i < mainChain.size(); ++i){
        _vectorData[i] = mainChain[i];
    }
}

void PmergeMe::_sortVector(size_t blockSize){
    size_t pair_size = blockSize * 2;

    // Base Case: If the block pair size exceeds total elements, stop recursing.
    if (pair_size > _vectorData.size()) return;

    // Step 1: Pair up blocks and sort them so the primary (larger) block is on the right.
    for (size_t i = 0; i + pair_size <= _vectorData.size(); i += pair_size){
        int left_max = _vectorData[i + blockSize - 1];
        int right_max = _vectorData[i + pair_size - 1];

        if (left_max > right_max){
            // Swap the memory blocks
            for (size_t k = 0; k < blockSize; ++k){
                std::swap(_vectorData[i + k], _vectorData[i + blockSize + k]);
            }
        }
    }

    // Step 2: Recursively sort the primary blocks at the next depth level
    _sortVector(pair_size);

    // Step 3: Extract and insert secondary blocks
    _insertSecondariesVector(blockSize);
}















// void PmergeMe::_sortVector(size_t blockSize){

    // Step 1: If the size of the block is bigger than all elements, return.

    // Step 2: Pair up adjacent elements. If the collection size is odd, cache the last item as a straggler.

    // Step 3: Compare elements within each pair. Store them as a std::vector<std::pair<int, int> >
            // where pair.first holds the larger value (Primary) and pair.second holds the smaller value (Secondary).

    // Step 4: Recursively call Ford-Johnson sort on this vector of pairs, defining custom comparison logic that sorts the structures based strictly on pair.first.
            // Be ready to catch straggler at any time

    // Step 5: Once the recursive call unwinds, the pairs are sorted by their primaries. Extract all pair.first elements to initialize MainChain vector.

    // Step 6: Insert the first secondary element (pairs[0].second) at the very beginning of MainChain (index 0).

    // Step 7: Iterate through the remaining secondary elements using the reverse Jacobsthal block index chunks ($b_3, b_2$, then $b_5, b_4$, etc.).
            // For each element, find its associated primary's position in the current MainChain to set the upper search limit, execute std::lower_bound, and call MainChain.insert().

    // Step 8: If a straggler was cached in step 2, perform a final binary search across the entire MainChain and insert it.

//     size_t totalElements = _vectorData.size();
//     size_t blockSpan = blockSize * 2;

//     // Base condition: cannot form pairs if total memory space is too small
//     // Step 1:
//     if (blockSpan > totalElements) return ;

//     // Step 2: Pair up blocks and ensure the larger primary block is placed first
//     for (size_t i = 0; i + blockSpan <= totalElements; i += blockSpan){
//         size_t primaryLI = i + blockSize;  // LI = Lead Index
//         size_t secondaryLI = i;

//         // Step 3: Compare the absolute final values of the current blocks
//         if (_vectorData[secondaryLI + blockSize - 1] > _vectorData[primaryLI + blockSize - 1]){
//             _swapBlocks(_vectorData, secondaryLI, primaryLI, blockSize);
//         }
//     }

//     // Step 4: Recursively sort the primary blocks
//     _sortVector(blockSpan);

//     // Step 5-8: Implement Jacobsthal binary insertion back into the chain
//     _insertSecondariesVector(blockSize);
//     // Extract your block references, calculate Jacobsthal indexes,
//     // and use std::lower_bound with a custom range comparator over the block intervals.
// }


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

// void PmergeMe::_insertSecondariesVector(size_t blockSize){
//     // 1. Separate current memory layout into discrete block vectors
//     std::vector<std::vector<int> > mainChain;
//     std::vector<std::vector<int> > pendingChain;

//     // The first pair's secondary is safely pushed to mainChain immediately
//     // Followed by pushing all sorted primaries to the mainChain...

//     // 2. Generate Jacobsthal sequence dynamically based on pendingChain.size()
//     std::vector<size_t> jacob;
//     jacob.push_back(1);
//     jacob.push_back(3);
//     while (jacob.back() < pendingChain.size()){
//         jacob.push_back(jacob.back() + 2 * jacob[jacob.size() - 2]);
//     }

//     // 3. Insertion Loop
//     size_t lastInsertedIdx = 0;
//     for (size_t i = 1; i < jacob.size(); ++i){
//         size_t targetJacob = jacob[i];
//         // Ensure we don't overshoot the size of our pending elements
//         size_t startIdx = std::min(targetJacob, pendingChain.size()) - 1;
//         size_t endIdx = lastInsertedIdx;

//         // Iterate backwards from the Jacobsthal boundary down to the last inserted index
//         for (size_t j = startIdx; j > endIdx; --j){
//             // Calculate upper bound: where is this secondary's primary located in mainChain?
//             // Perform std::lower_bound up to that upper bound index
//             // mainChain.insert(iterator, pendingChain[j]);
//         }
//         lastInsertedIdx = startIdx + 1;
//     }

//     // 4. Handle Straggler block if one existed at this level

//     // 5. Flatten mainChain back into the original _vectorData
// }




//                ========== DEQUE ==========






// Public:

// ================================================================
//                  OTHER PMERGEME FUNCTIONS
// ================================================================

// ... other functions
