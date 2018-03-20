/*
multiple hits? no hits?
revise bsearch
document Opt if different
document idea that you can skip an entire row if next row's first elem is <=n
const std::vector<const std::vector<int>> or just const std::vector<std::vector<int>> ?
*/


#include <iostream>
#include <vector>

bool bSearchHelper(const int n, const std::vector<int>& m) {
	if(m.empty() || m[0] > n || m[m.size() - 1] < n) {
		return false;
	}

	int l = 0, h = m.size() - 1;

	while(l <= h) {
		const int mid = l + (h - l) / 2;

		if(m[mid] == n) {
			return true;
		} else if(n < m[mid]) {
			h = mid - 1;
		} else {
			l = mid + 1;
		}
	}

	return false;
}

// O(N) + logM, N rows and M cols
bool searchSortedMatrix(const int n, const std::vector<std::vector<int>>& m) {
	if(m.empty() || m[0][0] > n) {
		return false;
	}

	int r = 0;
	const int mRows = m.size() - 1, mCols = m[0].size() - 1;

	if(m[mRows][mCols] < n) {
		return false;
	}

	while(r + 1 <= mRows && m[r + 1][0] <= n) {
		++r;
	}

	return bSearchHelper(n, m[r]);
}

// O(log(N*M)). Treat 2D array like 1D array, as it consists of elements sorted that way
// Similar to how Bit Vector works - identify the byte first, then offset within the byte
bool searchSortedMatrixOpt(const int n, const std::vector<std::vector<int>>& m) {
	if(m.empty() || m[0][0] > n) {
			return false;
	}

	int r = 0;
	const int mRows = m.size() - 1, mCols = m[0].size() - 1;

	if(m[mRows][mCols] < n) {
		return false;
	}

	int l = 0, h = mRows*mCols - 1;

	while(l <= h) {
		const int mid = l + (h - l) / 2;

	}
}
int main() {
	const std::vector<std::vector<int>> m{
		{3, 5, 7},
		{10, 15, 19},
		{45, 89, 99}
	};

	const std::vector<int> vals{3, 5, 7, 10, 15, 19, 45, 89, 99, -1, 100, 4, 6, 12, 16, 50, 90};
	for(const auto v : vals) {
		std::cout << v << ": " << std::boolalpha << searchSortedMatrix(v, m) << '\n';
	}
}
