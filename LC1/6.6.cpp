#include <iostream>
#include <vector>

void printVector(const std::vector<int>& v) {
	if(v.empty()) {
		std::cout << "{}\n";
		return;
	}

	for(const auto & val : v) {
		std::cout << val << " ";
	}
	std::cout << '\n';
}
// From LC Discuss
// O(N) time, O(1) space
// Despite the while() inside the for() loop, the operations under the while() loop happen at most once
// E.g., after an element is swapped once, it will never be swapped again due to this check: nums[nums[i] - 1] != nums[i]
int firstMissingPositive(std::vector<int>& nums) {
        int n = nums.size();
        for (int i = 0; i < n; ++i)
            while (nums[i] > 0 && nums[i] <= n && nums[nums[i] - 1] != nums[i])
                std::swap(nums[i], nums[nums[i] - 1]);

        std::cout << "After bucket sort: ";
        printVector(nums);
        for (int i = 0; i < n; i++)
            if (nums[i] != i + 1)
                return i + 1;
        return n + 1;
    }
int main() {
	std::vector<std::vector<int>> v{
			{1, 2, 0},
			{3, 4, -1, 1},
			{},
			{-1},
			{1},
			{1, 6, 7, 8},
			{1, 2, 2, 2},
			{-1, 2, -1, 4},
			{3, 4, -1, 1},
		};

		for(auto& arr : v) {
			printVector(arr);
			std::cout << "Missing: " << firstMissingPositive(arr) << '\n' << '\n';
		}
}
