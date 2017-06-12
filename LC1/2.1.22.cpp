#include <iostream>
#include <stdexcept>
#include <vector>

void printVector(const std::vector<int>& v) {
	for(const auto& val : v) {
		std::cout << val << " ";	
	}
	std::cout << '\n';
}

// O(N) space, O(N) time.
unsigned long long totCandies(const std::vector<unsigned long>& ranks) {
	std::vector<unsigned long long> res(ranks.size(), 1);
	
	for(size_t i = 0; i < ranks.size() - 1; ++i) {
		if(ranks[i + 1] > ranks[i] && res[i + 1] <= res[i]) {
			res[i + 1] = res[i] + 1;
		}
	}
	for(int i = ranks.size() - 1; i > 0; --i) {
		if(ranks[i - 1] > ranks[i] && res[i - 1] <= res[i]) {
			res[i - 1] = res[i] + 1;
		}
	}
	//printVector(res);
	return std::accumulate(res.begin(), res.end(), 0);
}

int main() {
    size_t sz;
    std::cin >> sz;
    std::vector<unsigned long> ranks(sz, 1);
    for(size_t i = 0; i < sz; ++i) {
        std::cin >> ranks[i];
    }
    std::cout << totCandies(ranks);
    return 0;
}
