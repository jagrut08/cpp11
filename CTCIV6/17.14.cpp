#include <vector>
#include <iostream>
#include <stdexcept>
#include <unordered_set>
#include <limits>
#include <cmath>
#include <set>

// Time O(N * K), space O(K)
std::vector<int> findSmallestKBF(const std::vector<int>& v, const int k) {

	if(v.empty()) {
		throw std::runtime_error("Empty input");
	}

	if(k < 0 || k > v.size()) {
		throw std::runtime_error("Invalid value for k");
	}

	std::unordered_set<size_t> indexes;
	std::vector<int> result(k);
	size_t resIndex = 0;

	for(size_t j = 0; j < k; ++j) {
		int minSeen = std::numeric_limits<int>::max();
		size_t minIndex = 0;

		for(size_t i = 0; i < v.size(); ++i) {
			if(indexes.count(i)) {
				continue;
			}

			if(v[i] < minSeen) {
				minSeen = v[i];
				minIndex = i;
			}
		}

		result[resIndex++] = minSeen;
		indexes.insert(minIndex);
	}

	return result;
}

std::vector<int> convertHeapToVector(const std::multiset<int>& maxHeap) {

	std::vector<int> result(maxHeap.size());
	size_t resultIndex = 0;

	for(const auto& val : maxHeap) {
		result[resultIndex++] = val;
	}

	return result;
}

// Time O(N * log(K)), space O(K)
std::vector<int> findSmallestKMaxHeap(const std::vector<int>& v, const int k) {

	if(v.empty()) {
		throw std::runtime_error("Empty input");
	}

	if(k < 0 || k > v.size()) {
		throw std::runtime_error("Invalid value for k");
	}

	std::multiset<int> maxHeap;

	for(const int& elem : v) {
		if(maxHeap.empty() || maxHeap.size() < k) { // Should be < k and not <= k as size will increase by 1 in the next statement
			std::cout << "Inserting " << elem << '\n';
			maxHeap.insert(elem);

		} else if(*maxHeap.rbegin() > elem) {
			std::cout << "Erasing " << *maxHeap.rbegin() << '\n';
			maxHeap.erase(*maxHeap.rbegin());
			std::cout << "Inserting " << elem << '\n';
			maxHeap.insert(elem);
		}
	}

	return convertHeapToVector(maxHeap);
}

// Selection Rank can do it in avg case O(N), worst case O(N^2). The algo for arrays with dupes is more complicated.

int main() {

	std::vector<int> v{5, 1, 17, -9, 7, -9};
	const int k = 2;
//	const auto& res = findSmallestKBF(v, k);
	const auto& res = findSmallestKMaxHeap(v, k);

	for(const auto& r : res) {
		std::cout << r << " ";

	}
}
