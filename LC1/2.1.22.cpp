#include <iostream>
#include <stdexcept>
#include <vector>

// O(N) space, O(N) time.
int totCandies(const std::vector<int>& ranks) {
	if(ranks.empty()) {
		throw std::runtime_error("Empty input");
	}
	std::vector<int> res(ranks.size(), 1);
	
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
	return std::sum(res.begin(), res.end());
}

int main() {
	std::vector<int> ranks{1, 2, 3};
	std::cout << "\nAnswer: " << totCandies(ranks);
}
