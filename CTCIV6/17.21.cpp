#include <iostream>
#include <stdexcept>
#include <vector>
#include <limits>
#include <algorithm>

int findHighestIndex(const std::vector<int>& emap, const int start, const int end, const int indexToIgnore) {
	int maxVal = std::numeric_limits<int>::min(), maxIndex = -1;
	for(int i = start; i <= end; ++i) {
		if(emap[i] > maxVal && indexToIgnore != i) {
			maxIndex = i;
			maxVal = emap[i];
		}
	}
	return maxIndex;
}

long long int calcVol(const std::vector<int>& emap, const int start, const int end) {
	int res = 0, level = std::min(emap[start], emap[end]);
	for(int i = start + 1; i < end; ++i) {
		res += level - emap[i];
	}
	return res;
}

long long int findVolRecur(const std::vector<int>& emap, const int start, const int end, const int highestIndexKnown) {
	if(emap.empty() || start >= end) {
		return 0;
	}

	int highestIndex = highestIndexKnown;

	if(-1 == highestIndex) {
		highestIndex = findHighestIndex(emap, start, end, -1);
	}
	const int secHighestIndex = findHighestIndex(emap, start, end, highestIndex);

	//std::cout << highestIndex << ", " << secHighestIndex << '\n';

	if(highestIndex == -1 || secHighestIndex == -1) {
		throw std::runtime_error("Could not calculate highest and second highest indexes!");
	}

	const size_t lower = std::min(secHighestIndex, highestIndex);
	const size_t higher = std::max(secHighestIndex, highestIndex);

	long long int res = calcVol(emap, lower, higher);
	return res + findVolRecur(emap, start, lower, lower) + findVolRecur(emap, higher, end, higher);
}

// O(N^2) as in the worst case, each bar i is examined N - i times to determine max. Space O(N) due to recursive calls.
long long int findVolBF(const std::vector<int>& emap) {
	return findVolRecur(emap, 0, emap.size() - 1, -1);
}

// O(N) time, O(N) space. long long to avoid overflow.
long long int findVolOpt(const std::vector<int>& emap) {
	std::vector<int> maxToRight(emap.size()), maxToLeft(emap.size());

	maxToRight[maxToRight.size() - 1] = emap[emap.size() - 1];
	for(int i = maxToRight.size() - 2; i >= 0; --i) {
		maxToRight[i] = std::max(maxToRight[i + 1], emap[i]);
	}

	maxToLeft[0] = emap[0];
	for(size_t j = 1; j < maxToLeft.size(); ++j) {
		maxToLeft[j] = std::max(maxToLeft[j - 1], emap[j]);
	}

	long long int res = 0;
	for(size_t k = 0; k < emap.size(); ++k) {
		res += std::min(maxToLeft[k], maxToRight[k]) - emap[k];
	}
	return res;
}

int main() {
//	const std::vector<int> levels{0, 1, 0, 2, 1, 0, 1, 3}; // 5
//	const std::vector<int> levels{0, 0, 4, 0, 0, 6, 0, 0, 3, 0, 8, 0, 2, 0, 5, 2, 0, 3, 0, 0}; // 46
	const std::vector<int> levels{0, 0, 4, 0, 0, 6, 0, 0, 3, 0, 5, 0, 1, 0, 0, 0}; // 26

	std::cout << findVolBF(levels) << ", " << findVolOpt(levels) << '\n';
}
