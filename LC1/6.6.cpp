#include <iostream>
#include <vector>
#include <limits>
#include <algorithm> // std::min ?

int findFirstMissingPositive(const std::vector<int>& v) {
	if(v.empty()) {
		return -1;
	}

	int minR = std::numeric_limits<int>::max(), maxR = std::numeric_limits<int>::min(), cnt = 0;
	long long int cs = 0;

	for(const auto& val : v) {
		if(val <= 0) {
			continue;
		}
		minR = std::min(minR, val);
		maxR = std::max(maxR, val);
		++cnt;
		cs += val;
	}

	//std::cout << '\n' << minR << ", " << maxR << ", " << cnt << ", " << cs << '\n';
	if(minR > 1) {
		return 1;
	} else  {
		++cnt;
		return (cnt * (cnt + 1) / 2) - cs;
	}
}

void printVector(const std::vector<int>& v) {
	if(v.empty()) {
		std::cout << "{}";
		return;
	}

	for(const auto& val : v) {
		std::cout << val << " ";
	}
}

int main() {
	const std::vector<std::vector<int>> v{
		{1, 2, 0},
		{3, 4, -1, 1},
		{},
		{-1},
		{1},
		{1, 6, 7, 8},

//		{1, 2, 2, 2},
	};

	for(const auto & arr : v) {
		printVector(arr);
		std::cout << " Missing: " << findFirstMissingPositive(arr) << '\n';
	}
}
