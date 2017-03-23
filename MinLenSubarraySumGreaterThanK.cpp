http://www.geeksforgeeks.org/minimum-length-subarray-sum-greater-given-value/

#include <iostream>
#include <limits>
#include <vector>
#include <algorithm>

int findMinSubArrayLen(const std::vector<int>& v, const int k) {

	long long int sum = 0;
	size_t minLen = std::numeric_limits<size_t>::max();

	for(size_t end = 0, start = 0; end < v.size(); ++end) {

		sum += v[end];

		if(sum <= 0 && k > 0) {

			sum = 0;
			start = end + 1;
		}

		while(sum > k && start <= end) {

			minLen = std::min(minLen, end - start + 1);

			if(1 == minLen) {

				return 1;
			}

			sum -= v[start++];
		}

	}

	return (std::numeric_limits<size_t>::max() == minLen ? -1 : minLen);
}


int main() {

	const std::vector<int> v{- 8, 1, 4, 2, -6};
	const int k = 6;

	std::cout << "Result: " << findMinSubArrayLen(v, k) << '\n';
}
