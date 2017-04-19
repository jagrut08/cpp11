#include <iostream>
#include <vector>
#include <stdexcept>

std::vector<int> initN(const int n) {
	std::vector<int> res(n);
	for(size_t i = 0; i < res.size(); ++i) {
		res[i] = i + 1;
	}
	return res;
}

std::vector<int> getFactorials(const int n) {
	std::vector<int> res(n + 1, 1);
	for(size_t i = 2; i < res.size(); ++i) {
		res[i] = res[i - 1] * i;
	}
	return res;
}

std::vector<int> findKthPerm(const int n, int k) {
	if(n < 0 || n > 9 || k < 1) {
		throw std::runtime_error("Invalid inputs");
	}
	std::vector<int> nums = initN(n), res(n);
	const std::vector<int> facts = getFactorials(n);
	size_t resIndex = 0;
	k %= facts[n]; // When k > n!
	--k;
	for(int i = 1; i <= n; ++i) {

		size_t index = k / facts[n - i];
		res[resIndex++] = nums[index];

		std::cout << "Processing " << index << '\n';
		if(index >= nums.size()) {
			throw std::runtime_error("Out of bounds!");
		}

		nums.erase(nums.begin() + index);
		k -= index * facts[n - i];
	}
	return res;
}

int main() {
	const auto res = findKthPerm(3, 5);

	for(const auto& v : res) {
		std::cout << v;
	}
}
