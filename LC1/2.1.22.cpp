
#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>

void printVector(const std::vector<int>& v) {
	for(const auto& val : v) {
		std::cout << val << " ";
	}
	std::cout << '\n';
}

void printVector(const std::vector<unsigned long long>& v) {
	for(const auto& val : v) {
		std::cout << val << " ";
	}
	std::cout << '\n';
}

// O(N) space, O(N) time.
unsigned long long totCandies(const std::vector<int>& ranksInput) {
    std::vector<int> ranks(ranksInput.size() + 2);
    std::copy(ranksInput.begin(), ranksInput.end(), ranks.begin() + 1);
    // Sentinels
    ranks[0] = std::numeric_limits<int>::max();
    ranks[ranks.size() - 1] = std::numeric_limits<int>::max();
    // Result
    std::vector<unsigned long long> res(ranksInput.size() + 1, 0);
    // Populate valleys. Note <= and <=
	for(size_t i = 1; i < ranks.size() - 1; ++i) {
        if(ranks[i - 1] >= ranks[i] && ranks[i] <= ranks[i + 1]) {
            res[i] = 1;
        }
	}
//    printVector(res);
    // Populate rises, from l->r. Note < and <=
	for(size_t i = 1; i < ranks.size() - 1; ++i) {
        if(ranks[i - 1] < ranks[i] && ranks[i] <= ranks[i + 1]) {
            res[i] = res[i - 1] + 1;
        }
	}
 //    printVector(res);

    // Populate falls, from l->r, but processed r->l. Note >= and >
    for(int i = ranks.size() - 2; i >= 1; --i) {
        if(ranks[i - 1] >= ranks[i] && ranks[i] > ranks[i + 1])
            res[i] = res[i + 1] + 1;
    }
   //  printVector(res);

    // Populate peaks
	for(size_t i = 1; i < ranks.size() - 1; ++i) {
        if(ranks[i - 1] < ranks[i] && ranks[i] > ranks[i + 1]) {
            res[i] = std::max(res[i - 1], res[i + 1]) + 1;
        }
	}
 //   printVector(res);
    return std::accumulate(res.begin(), res.end(), 0L); // Careful - just 0 will cause integer accumulation!
}

int main() {
    size_t sz;
    std::cin >> sz;
    std::vector<int> ranks(sz);
    for(size_t i = 0; i < sz; ++i) {
        std::cin >> ranks[i];
    }
    std::cout << totCandies(ranks);
    return 0;
}
