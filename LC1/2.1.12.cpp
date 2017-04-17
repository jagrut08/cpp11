#include <vector>
#include <iostream>
#include <stdexcept>
#include <algorithm>    // std::next_permutation

void reverseVector(std::vector<int>& v, int begin) {
	if(v.empty()) {
		return;
	}

	for(int end = v.size() - 1; begin < end; ++begin, --end) {
		std::swap(v[begin], v[end]);
	}
}

void printVector(const std::vector<int>& v) {
	for(const auto& val : v) {
		std::cout << val << ", ";
	}
}

void findNextPerm(std::vector<int>& v) {
	if(v.empty()) {
			throw std::runtime_error("Empty input");
	}

	int i = v.size() - 1, j = i;

	for(; i > 0; --i) {
		if(v[i - 1] < v[i]) {
			break;
		}
	}

	// This could be binary search instead of linear search as we've established an increasing pattern until index i
	for(;i && j > i - 1; --j) {
		if(v[j] > v[i - 1]) {
			std::swap(v[i - 1], v[j]);
			break;
		}
	}

	reverseVector(v, i);
}

int main() {
	std::vector<int> v{1, 2, 3, 4};
	std::vector<int> r{v};

	for(size_t i = 0; i < 10000; ++i) {
		findNextPerm(v);
		std::next_permutation(r.begin(), r.end());

		if(!std::equal(v.begin(), v.end(), r.begin())) {
			printVector(v);
			std::cout << " ||||| ";
			printVector(r);
			std::cout << '\n';
			break;
		}
	}
	std::cout << "All good\n";
}
