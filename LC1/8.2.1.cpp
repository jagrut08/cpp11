/*
 * difference between auto and auto& ? check your notes first.
document opt solution
unordered_set of std::vector<int> doesn't work out of the box, need to define VectorHasher() functor?
--


 */
#include <vector>
#include <unordered_set>
#include <iostream>
#include <algorithm>
#include <functional>

struct VectorHash {
    size_t operator()(const std::vector<int>& v) const {
    	size_t i;
    	std::for_each(v.begin(), v.end(), [&i](int val) {i = i * 10 + val;});
//    	std::cout << i << '\n';
    	return i;
    }
};

// O(2^n) time and space, BF as we create all subsets and discard dups
std::unordered_set<std::vector<int>, VectorHash> findSubsetsHelper(const int i, const std::vector<int>& v) {
	std::unordered_set<std::vector<int>, VectorHash> res{};

	if(i == v.size()) {
		res.insert(std::vector<int>{});
		return res;
	}

	const int x = v[i];
	auto ss = findSubsetsHelper(i + 1, v);
	auto ss2 = std::unordered_set<std::vector<int>, VectorHash>{};

	for(const auto& elem : ss) {
		auto y = elem;
		y.emplace_back(x);
		ss.insert(y);
	}
	return ss;
}

std::unordered_set<std::vector<int>, VectorHash> findSubsets(const std::vector<int>& v) {
	auto t{v};
	std::sort(t.begin(), t.end(), std::less<int>());

	return findSubsetsHelper(0, t);
}

void printVector(const std::vector<int>& v) {
	if(v.empty()) {
		std::cout << "{}";
		return;
	}

	std::cout << "{";
	for(const auto & val : v) {
		std::cout << val << ", ";
	}
	std::cout << "}";
}

int main() {
	const std::vector<std::vector<int>> v {
		{},
	//	{1},
	//	{1, 2},
	//	{1, 1},
	//	{2, 1, 2},
	//	{1, 1, 1},
	};

	for(const auto& arr : v) {
		printVector(arr);
		std::cout << " subsets:\n" ;
		auto ss = findSubsets(arr);
		std::for_each(ss.begin(),ss.end(), printVector());
		std::cout << '\n';
	}
}


