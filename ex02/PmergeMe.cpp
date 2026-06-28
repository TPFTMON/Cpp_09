#include "PmergeMe.hpp"
#include <sstream>

// ================================================================
//                         ORTHODOX BASE
// ================================================================

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe &other)
    : _vectorData(other._vectorData), _dequeData(other._dequeData) {}

PmergeMe& PmergeMe::operator=(const PmergeMe &other){
    if (this != &other){
        _vectorData = other._vectorData;
        _dequeData = other._dequeData;
    }
    return (*this);
}

PmergeMe::~PmergeMe() {}



// Private, SORTING:

// ================================================================
//                      VECTOR PMERGEME
// ================================================================

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


// ================================================================
//                      DEQUE PMERGEME
// ================================================================

size_t PmergeMe::_binarySearchBlocksDeque(const std::deque<int> &chain, int target, size_t endBlockIdx, size_t blockSize){
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

void PmergeMe::_insertSecondariesDeque(size_t blockSize){
    std::deque<int> mainChain;
    std::deque<size_t> mainIDs;
    std::deque<int> pendingChain;
    std::deque<size_t> pendingIDs;

    size_t num_blocks = _dequeData.size() / blockSize;
    size_t pair_size = blockSize * 2;
    size_t num_pairs = num_blocks / 2;

    if (num_pairs == 0) return;

    // 1. Initialize chains with the first pair
    // The first secondary (b1) is automatically pushed to mainChain. It has no upper bound dependency.
    mainChain.insert(mainChain.end(), _dequeData.begin(), _dequeData.begin() + blockSize);
    mainIDs.push_back(0);

    // The first primary (a1)
    mainChain.insert(mainChain.end(), _dequeData.begin() + blockSize, _dequeData.begin() + pair_size);
    mainIDs.push_back(1);

    // 2. Extract remaining paired chunks
    for (size_t i = 1; i < num_pairs; ++i){
        size_t start = i * pair_size;

        // Secondary chunk (b_i)
        pendingChain.insert(pendingChain.end(), _dequeData.begin() + start, _dequeData.begin() + start + blockSize);
        pendingIDs.push_back(i + 1);

        // Primary chunk (a_i)
        mainChain.insert(mainChain.end(), _dequeData.begin() + start + blockSize, _dequeData.begin() + start + pair_size);
        mainIDs.push_back(i + 1);
    }

    // 3. Handle a potential straggler block
    if (num_blocks % 2 != 0){
        size_t start = num_pairs * pair_size;
        pendingChain.insert(pendingChain.end(), _dequeData.begin() + start, _dequeData.begin() + start + blockSize);
        pendingIDs.push_back(num_pairs + 1); // ID larger than any primary, allows searching the full chain
    }

    // 4. Generate Jacobsthal sequence
    std::deque<size_t> J;
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
            size_t p_idx = j - 1; // 0-based index in the pending deque
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
            size_t insert_pos = _binarySearchBlocksDeque(mainChain, target_val, upper_bound_idx, blockSize);

            mainChain.insert(mainChain.begin() + insert_pos * blockSize,
                             pendingChain.begin() + p_idx * blockSize,
                             pendingChain.begin() + (p_idx + 1) * blockSize);

            mainIDs.insert(mainIDs.begin() + insert_pos, id_to_find);
        }
        last_inserted = target_idx;
    }

    // 6. Overwrite original data with the sorted chain
    for (size_t i = 0; i < mainChain.size(); ++i){
        _dequeData[i] = mainChain[i];
    }
}

void PmergeMe::_sortDeque(size_t blockSize){
    size_t pair_size = blockSize * 2;

    // Base Case: If the block pair size exceeds total elements, stop recursing.
    if (pair_size > _dequeData.size()) return;

    // Step 1: Pair up blocks and sort them so the primary (larger) block is on the right.
    for (size_t i = 0; i + pair_size <= _dequeData.size(); i += pair_size){
        int left_max = _dequeData[i + blockSize - 1];
        int right_max = _dequeData[i + pair_size - 1];

        if (left_max > right_max){
            // Swap the memory blocks
            for (size_t k = 0; k < blockSize; ++k){
                std::swap(_dequeData[i + k], _dequeData[i + blockSize + k]);
            }
        }
    }

    // Step 2: Recursively sort the primary blocks at the next depth level
    _sortDeque(pair_size);

    // Step 3: Extract and insert secondary blocks
    _insertSecondariesDeque(blockSize);
}




// ================================================================
//                  PUBLIC PMERGEME FUNCTIONS
// ================================================================

//          Input and Execution:

static void printSequence(const std::vector<int> &container){
    size_t size = container.size();
    size_t limit = (size > 5) ? 5 : size;
    // size_t limit = size;    // uncomment this to see the full sequence

    for (size_t i = 0; i < limit; ++i){
        std::cout << container[i] << (i == limit - 1 ? "" : " ");
    }
    if (size > 5){
        std::cout << " [...]";  // and comment this to see the full sequence
    }
    std::cout << std::endl;
}

void PmergeMe::parseInput(int argc, const char* argv[]){
    if (argc < 2){
        throw std::runtime_error("Error");
    }

    for (int i = 1; i < argc; ++i){
        std::string arg(argv[i]);

        // Catch completely empty string arguments (e.g., ./PmergeMe "")
        if (arg.find_first_not_of(' ') == std::string::npos){
            throw std::runtime_error("Error");
        }

        std::stringstream ss(arg);
        std::string token;

        while (ss >> token){
            // Edge Case 1: Handle optional leading '+' sign
            size_t startIdx = 0;
            if (token[0] == '+'){
                if (token.length() == 1) throw std::runtime_error("Error");
                startIdx = 1;
            }

            // Edge Case 2: Strictly verify all characters are numeric digits
            for (size_t j = startIdx; j < token.length(); ++j){
                if (!std::isdigit(token[j])){
                    throw std::runtime_error("Error");
                }
            }

            // Edge Case 3: Overflow verification against INT_MAX
            long val = std::atol(token.c_str());
            if (val <= 0 || val > 2147483647){
                throw std::runtime_error("Error");
            }

            int intVal = static_cast<int>(val);

            // Edge Case 4: Duplicate Detection
            if (std::find(_vectorData.begin(), _vectorData.end(), intVal) != _vectorData.end()){
                throw std::runtime_error("Error");
            }

            _vectorData.push_back(intVal);
            _dequeData.push_back(intVal);
        }
    }

    if (_vectorData.empty()){
        throw std::runtime_error("Error");
    }
}

void PmergeMe::executeAndTiming(){
    struct timeval start, end;

    // --- 1. Display Unsorted Sequence ---
    std::cout << "Before: ";
    printSequence(_vectorData);

    // --- 2. Benchmark std::vector ---
    gettimeofday(&start, NULL);
    _sortVector(1);
    gettimeofday(&end, NULL);

    double timeVector = (end.tv_sec - start.tv_sec) * 1000000.0
                      + (end.tv_usec - start.tv_usec);

    // --- 3. Display Sorted Sequence ---
    std::cout << "After:  ";
    printSequence(_vectorData);

    // --- 4. Benchmark std::deque ---
    gettimeofday(&start, NULL);
    _sortDeque(1);
    gettimeofday(&end, NULL);

    double timeDeque = (end.tv_sec - start.tv_sec) * 1000000.0
                     + (end.tv_usec - start.tv_usec);

    // --- 5. Display Metrics ---
    std::cout << "Time to process a range of " << _vectorData.size()
              << " elements with std::vector : " << timeVector << " us" << std::endl;

    std::cout << "Time to process a range of " << _dequeData.size()
              << " elements with std::deque  : " << timeDeque << " us" << std::endl;
}
