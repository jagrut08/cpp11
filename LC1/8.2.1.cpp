#include <vector>
#include <unordered_set>
#include <iostream>
#include <algorithm>
#include <functional>

void printVector(const std::vector<int>& v) {
	if(v.empty()) {
		std::cout << "{} ";
		return;
	}
	size_t i = 0;
	std::cout << "{";
	std::for_each(v.cbegin(), v.cend(), [&i, &v](int val) {std::cout << val << (++i == v.size() ? "" : ", ");} );
	std::cout << "} ";
}

struct VectorHash {
    size_t operator()(const std::vector<int>& v) const {
    	size_t i = 0;
    	std::for_each(v.begin(), v.end(), [&i](int val) {i = i * 10 + val;});
    	return i;
    }
};

void printSet(const std::unordered_set<std::vector<int>, VectorHash>& s) {
	std::for_each(s.cbegin(), s.cend(), printVector);
	std::cout << '\n';
}

// O(2^n) time and space, BF as we create all subsets and discard dups
std::unordered_set<std::vector<int>, VectorHash> findSubsetsHelper(const int i, const std::vector<int>& v) {
	std::unordered_set<std::vector<int>, VectorHash> res{};

	if(i == static_cast<int>(v.size())) {
		res.insert(std::vector<int>{});
		return res;
	}

	const int x = v[i];
	auto ss = findSubsetsHelper(i + 1, v);
	auto ss2 = std::unordered_set<std::vector<int>, VectorHash>{};

	// use auto y below as y is a copy of the elements of s
	for(auto y : ss) {
		y.emplace_back(x);
		ss2.insert(y);
	}

	ss.insert(ss2.begin(), ss2.end());
	return ss;
}

std::unordered_set<std::vector<int>, VectorHash> findSubsets(const std::vector<int>& v) {
	auto t{v};
	std::sort(t.begin(), t.end(), std::greater<int>());

	return findSubsetsHelper(0, t);
}

int main() {
	const std::vector<std::vector<int>> v {
		{},
		{1},
		{1, 2},
		{1, 1},
		{2, 1},
		{2, 1, 2},
		{1, 1, 1},
		{1, 2, 2}
	};

	for(const auto& arr : v) {
		printVector(arr);
		std::cout << " subsets:\n" ;
		auto ss = findSubsets(arr);
		std::for_each(ss.cbegin(),ss.cend(), printVector);
		std::cout << '\n';
	}
}


