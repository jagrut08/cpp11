#include <iostream>
#include <vector>
#include <utility> // std::pair

int findEndOfRange(const std::vector<int>& v, const int x){
	int low = 0, high = v.size() - 1, mid = 0;

	while(low <= high) {
		mid = low + (high - low) / 2;

		// if v[mid] == x, mid could be end of range if either one of the below is true.
		// 1. The range ends in the middle of the array, and there's an element after v[mid] that's greater than x. v[mid + 1] > x.
		// 2. Or, the range ends at the end of the array, mid == v.size() - 1
		if(v[mid] == x && (mid == v.size() - 1 || v[mid + 1] > x)) {
			return mid;
		}

		if(x >= v[mid]) { // Note >= here. If x > v[mid] or even x == v[mid], we increment low as we want to reach the end of the range
			low = mid + 1;
		} else {
			high = mid - 1;
		}
	}

	return - 1;
}


int findStartOfRange(const std::vector<int>& v, const int x){
	int low = 0, high = v.size() - 1, mid = 0;

	while(low <= high) {
		mid = low + (high - low) / 2;

		// if v[mid] == x, mid could be beginning of range if either one of the below is true.
		// 1. The range begins at v[mid], and there's an element before v[mid] that's lesser than x. v[mid + 1] < x.
		// 2. Or, the range begins at the beginning of the array, mid == 0
		if(v[mid] == x && (mid == 0 || v[mid - 1] < x)) {
					return mid;
		}

		if(x > v[mid]) {  // Node > here. Only if x is more than v[mid], we move low. If x == v[mid], we bring high leftwards to reach the left end of the range.
			low = mid + 1;
		} else {
			high = mid - 1;
		}
	}

	return -1;
}

// O(logN) time, O(1) space
std::pair<int, int> findRangeOpt(const std::vector<int>& v, const int x) {
	// The below works even if v is empty
	int beg = findStartOfRange(v, x);
	int end = findEndOfRange(v, x);
	return std::make_pair(beg, end);
}

//O(N) time complexity, though it tries binary search
// O(1) space
std::pair<int, int> findRange(const std::vector<int>& v, const int x) {
	if(v.empty()) {
		return std::make_pair(-1, -1);
	}

	int low = 0, high = v.size() - 1, mid = 0; // using size_t here will cause infinite loop for inputs {11, 12}, 8

	while(low <= high) {
		mid = low + (high - low) / 2;
		if(v[mid] == x) {
			break;
		} else if(x > v[mid]) {
			low = mid + 1;
		} else {
			high = mid - 1;
		}
	}

	if(low > high) {
		return std::make_pair(-1, -1);
	} else {
		int start = mid, end = mid;
		while(start >= 0 && v[start] == x) {
			--start;
		}
		++start;

		while(end < v.size() && v[end] == x) {
			++end;
		}
		--end;
		return std::make_pair(start, end);
	}
}

void printVector(const std::vector<int>& v) {
	if(v.empty()){
		std::cout << "{}";
	} else {
		for(const auto& val : v) {
			std::cout << val << " ";
		}
	}
	std::cout << '\n';
}

int main() {
	const int x = 8;
	const std::vector<std::vector<int>> v {
		{5, 7, 7, 8, 8, 10},
		{8, 8, 9, 10, 11},
		{6, 7, 8, 8},
		{6, 7},
		{11, 12},
		{5, 7, 8, 9},
		{8, 8, 8}
	};

	for(const auto& arr : v) {
		printVector(arr);
		try {
//			const std::pair<int, int> r = findRange(arr, x);
			const std::pair<int, int> r = findRangeOpt(arr, x);

			std::cout << r.first << ", " << r.second << '\n';
		} catch(const std::exception& e) {
			std::cout << e.what() << '\n';
			return 1;
		}

	}
}

