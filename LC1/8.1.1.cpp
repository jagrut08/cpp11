#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

//O(2^N + NlogN)
//O(N) recursive calls, but size of returned data = number of subsets = 2^N, so O(2^N) space
std::vector<std::vector<int>> findSubsetsHelper(const std::vector<int>& v, int idx) {
	std::vector<std::vector<int>> res;

	if(idx < 0) {
		res.emplace_back(std::vector<int>()); // Empty subset. Insert an empty vector; completely empty res doesn't work.
		return res;
	}

	const int elem = v[idx--];
	res = findSubsetsHelper(v, idx);
	const std::vector<std::vector<int>> ssWithout{res};


	for(auto& s : res) {
		s.emplace_back(elem);
	}

	res.insert(res.end(), ssWithout.begin(), ssWithout.end());
	return res;
}

std::vector<std::vector<int>> findSubsets(const std::vector<int>& v) {
	std::vector<int> tIn {v};
	std::sort(tIn.begin(), tIn.end(), std::less<int>());
	return findSubsetsHelper(tIn, tIn.size() - 1);
}

void printVector(const std::vector<int>& v) {
	auto printFn = [](const int i) {std::cout << i << " ";};
	std::cout << "{";
	for_each(v.begin(), v.end(), printFn);
	std::cout << "}, ";
}

void printVectorOfVectors(const std::vector<std::vector<int>>& v) {
	for(const auto& elem : v) {
		printVector(elem);
		std::cout << " ";
	}
	std::cout << '\n';
}

int main() {
	const std::vector<std::vector<int>> v{
		{},
		{1},
		{1, 2},
		{1, 2, 3},
		{3, 1, 2},
	};
	for(const auto& elem : v) {
		const auto res = findSubsets(elem);
		std::cout << "Input: ";
		printVector(elem);
		std::cout << " subsets are: ";
		printVectorOfVectors(res);
	}
}
