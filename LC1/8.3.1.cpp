#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>

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

void getPermutationsHelper(
	std::vector<bool>& used,
	std::vector<std::vector<int>>& res,
	std::vector<int>& curRes,
	const int curIdx,
	const std::vector<int>& v
) {
	if(curIdx >= v.size()) {
		res.emplace_back(curRes);
	} else {
		for(size_t i = 0; i < v.size(); ++i) {
			if(used[i]) {
				continue;
			}
			used[i] = true;
			curRes[curIdx] = v[i];
			getPermutationsHelper(used, res, curRes, curIdx + 1, v);
			used[i] = false;
		}
	}
}

// Time and space O(N!) as N! permutations of N unique items
// Assumes unique input values
// Idea is to try each character of the input array v in each location of a permutation
// curRes is a permutation, and curIdx tracks its characters. For each value of curIdx, consider
// using each character of v.
std::vector<std::vector<int>> getPermutations(const std::vector<int>& v) {
	std::vector<bool> used(v.size(), false);
	std::vector<std::vector<int>> res;
	std::vector<int> curRes(v.size());

	getPermutationsHelper(used, res, curRes, 0, v);
	return res;
}

int main() {
	const std::vector<std::vector<int>> v {
		{},
		{1},
		{1, 2},
		{1, 2, 3},
		{1, 2, 3, 4}
	};

	for(const auto& arr : v) {
		printVector(arr);
		auto perms = getPermutations(arr);
		std::cout << " perms: total - " << perms.size() << " ";
		for(const auto& p : perms) {
			printVector(p);
			std::cout << " ";
		}
		std::cout << '\n';
	}
}
