#include <iostream>
#include <vector>
#include <algorithm>
#include <list>

// O(N^2).
int findLargestRect(const std::vector<int>& v) {
	int res = 0;

	for(size_t i = 0; i < v.size(); ++i) {
		const int val = v[i];
		int left = i, right = i;

		while(left >= 0 && v[left] >= val) {
			--left;
		}
		++left;

		while(right < v.size() && v[right] >= val) {
			++right;
		}
		--right;

		const int tmpRes = (right - left + 1) * val;
		res = std::max(res, tmpRes);
	}
	return res;
}

void printStack(const std::string& str, const std::list<int>& stk) {
	std::cout << str << " ";
	for(const auto & val : stk) {
		std::cout << val << " ";
	}
	std::cout << '\n';
}

// O(N) time, O(N) space
// http://www.geeksforgeeks.org/largest-rectangle-under-histogram/

int findCurRect(std::list<int>& stk, const std::vector<int>& v, const int i, const int res) {
//	printStack("\nStack Before", stk);
	const int height = v[stk.back()];
	stk.pop_back();

	// What is the max possible area by popped bar? The bar before the popped bar will be considered subsequently

	const int endIndex = i;
	int startIndex = (stk.empty() ? -1 : stk.back()), tmpRes;
	tmpRes = height * (endIndex - startIndex - 1); // end - start + 1, but endIndex and startIndex are both off by 1

//	printStack("\nStack After", stk);
//	std::cout << "\nres and tmpRes are: " << res << " " << tmpRes << '\n';
	return std::max(res, tmpRes);
}

int findLargestRectOpt(const std::vector<int>& v) {
	std::list<int> stk; // Always has set of bars in increasing heights
	int res = 0, i = 0; // i used outside the loop, down below
	while(i < v.size()) {
		if(stk.empty() || v[i] > v[stk.back()]) {
			stk.push_back(i);
			++i;
		} else {
				// Note that i is not incremented here
			res = findCurRect(stk, v, i, res);
		}
	}

	while(!stk.empty()) {
		res = findCurRect(stk, v, i, res);
	}

	return res;
}

int main() {
	const std::vector<std::vector<int>> v {
		{},
		{2},
		{2, 3},
		{3, 3, 3},
		{2, 1, 5, 6, 2, 3},
		{3, 4, 5, 3, 4, 7},
		{2, 3, 5, 6, 8, 9, 9, 6},
		{2, 1, 5, 6, 2, 3},
		{6, 2, 5, 4, 5, 1, 6},
		{1, 2, 3, 4, 5},
		{5, 4, 3, 2, 1}

	};

	for(const auto& arr : v) {
		for(const auto& val : arr) {
			std::cout << val << " ";
		}

		std::cout <<". nmaxRect : " << findLargestRect(arr) << ", maxRectOpt : " << findLargestRectOpt(arr) << '\n';
	}
}
