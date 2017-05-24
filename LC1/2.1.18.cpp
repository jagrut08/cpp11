#include <iostream>
#include <vector>
#include <limits>

// BF time complexity is O(2^N). With memo, it becomes O(N). Space O(N) due to recursion stack.
unsigned long long int findWays(const int s, std::vector<unsigned long long int>& memo) {
	if(s <= 0) {
		return 0;
	} else if(s == 1) {
		return 1;
	} else {

		if(memo[s] == 0) {
			memo[s] = findWays(s - 1, memo) + findWays(s - 2, memo);
		}
		return memo[s];
	}
}

// Opt. Fibonacci! O(N) time, O(1) space - three variables
unsigned long long int findWaysOpt(const int n) {
	unsigned long long int x = 0, y = 1, z = 1;
	for(int i = 0; i < n; ++i) { // If n < 0, size_t i < n will always be true!
		x = y;
		y = z;
		z = x + y;
	}
	return x;
}

int main() {
	const int n = 18;
	std::vector<unsigned long long int> memo(n + 1, 0);
	std::cout << findWays(n, memo) << " : " << findWaysOpt(n);
}
